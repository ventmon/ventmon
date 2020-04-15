#include <stdint.h>
#include <stdbool.h>
#include "config.h"

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

// ----- Algorithm Output -----

// whether there is an alarm condition
extern alarm_t alarm_raised;
// display code for raised alarm
extern char *alarm_code;
// disable alarm for N seconds when system turned on
extern bool alarm_disabled;
// value that caused alarm to be raised
extern float alarm_value;
// recursive filter max/min pressure readings
extern float p_max;
extern float p_min;
// breath respiration_rate (breaths/min)
extern uint16_t respiration_rate;

// ----- Config -----

// alarm condition thresholds
extern uint16_t THRESH_NC; // s
extern uint16_t THRESH_LP; // cm H20
extern uint16_t THRESH_HP; // cm H20
extern uint16_t THRESH_LR; // breaths/min
extern uint16_t THRESH_HR; // breaths/min

// ----- Functions -----

// take in single sample at SAMPLE_RATE and update algorithm state
void run_algorithm(float p);