// ----- Types -----

// alarm types
typedef enum {
    // no alarm
    ALARM_NONE,
    // ventilator not cycling
    ALARM_NC,
    // PEEP below threshold
    ALARM_LP,
    // PIP above threshold
    ALARM_HP,
    // respiratory rate below threshold
    ALARM_LR,
    // respiratory rate above threshold
    ALARM_HR
} alarm_t;

// ----- Algorithm State -----

// whether there is an alarm condition
alarm_t alarm_raised = ALARM_NONE;
// display code for raised alarm
char *alarm_code = "  ";
float alarm_value = 0;
// number of samples since last PEEP attack sample
uint16_t last_peep = 0;
// number of samples since last PIP attack sample
uint16_t last_pip = 0;
// disable alarm for N seconds when system turned on
bool alarm_disabled = true;
uint16_t alarm_counter = 0;
bool reached_min = false;
uint16_t last_first_max = 0;
// breath respiration_rate (breaths/min)
uint16_t respiration_rate = 0;
// recursive filter max/min pressure readings
float p_max = 0;
float p_min = 100;

// ----- Config -----

const float ATTACK_COEFF = .9;
const float RELEASE_COEFF = .999;

// alarm condition thresholds
uint16_t THRESH_NC = 10; // s
uint16_t THRESH_LP = 2; // cm H20
uint16_t THRESH_HP = 40; // cm H20
uint16_t THRESH_LR = 6; // breaths/min
uint16_t THRESH_HR = 35; // breaths/min
/* uint16_t ALARM_RATIO = 1.5; */
/* uint16_t ALARM_DIFF = 86; */

// ----- Functions -----

// take in single sample at SAMPLE_RATE and update algorithm state
void run_algorithm(float p) {

    // if current sample is PIP attack
    if (p > p_max) {
        p_max = p_max * ATTACK_COEFF + p * (1 - ATTACK_COEFF);
        last_pip = 0;
        if (reached_min) {
            respiration_rate = 60 * SAMPLE_RATE / last_first_max;

            last_first_max = 0;
            reached_min = false;
        }
    }
    // if current sample is PIP release
    else {
        p_max = p_max * RELEASE_COEFF + p * (1 - RELEASE_COEFF);
        last_pip++;
    }
    // if current sample is PEEP attack
    if (p < p_min) {
        p_min = p_min * ATTACK_COEFF + p * (1 - ATTACK_COEFF);
        last_peep = 0;
        reached_min = true;
    }
    // if current sample is PEEP release
    else {
        p_min = p_min * RELEASE_COEFF + p * (1 - RELEASE_COEFF);
        last_peep++;
    }

    // ----- Alarm conditions -----

    if (!alarm_disabled) {
        // non-cycling alarm
        if (
            last_pip > SAMPLE_RATE * THRESH_NC ||
            last_peep > SAMPLE_RATE * THRESH_NC
            ){
            alarm_raised = ALARM_NC;
            alarm_code = "nc";
            alarm_value = (SAMPLE_RATE * THRESH_NC) / 1000;
        }
        /* else if (p_max < (p_min * ALARM_RATIO)){ */
        /*     // FIXME - add ratio alarm condition */
        /*     alarm_raised = NON_CYCLING; */
        /*     alarm_code = "nc"; */
        /*     // FIXME */
        /*     alarm_value = 11; */
        /* } */
        /* else if ((p_max - p_min) < ALARM_DIFF){ */
        /*     // FIXME - add diff alarm condition */
        /*     alarm_raised = NON_CYCLING; */
        /* } */
        // low-pressure alarm
        else if (p_min < THRESH_LP){
            alarm_raised = ALARM_LP;
            alarm_code = "LP";
            alarm_value = p_min;
        }
        else if (p_max > THRESH_HP){
            alarm_raised = ALARM_HP;
            alarm_code = "HP";
            alarm_value = p_max;
        }
        else if (respiration_rate > THRESH_HR) {
            alarm_raised = ALARM_HR;
            alarm_code = "Hr";
            alarm_value = respiration_rate;
        }
        else if (respiration_rate < THRESH_LR) {
            alarm_raised = ALARM_LR;
            alarm_code = "Lr";
            alarm_value = respiration_rate;
        }
    }

    // enable alarms after 5 seconds
    if (alarm_disabled && alarm_counter > 5 * SAMPLE_RATE) {
        alarm_disabled = false;
        alarm_counter = 0;
    } else {
        alarm_counter++;
    }

    last_first_max++;
}
