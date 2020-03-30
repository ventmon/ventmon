- alarm - SFM-27 https://www.youtube.com/watch?v=LLGMlErc0yQ
- esp8266 bulk US - https://www.ebay.com/itm/5X-ESP8266-ESP-12E-802-11n-WIFI-USB-Development-Board-Arduino-MicroPython-5-Pack/132532596048?hash=item1edb8eed50:g:Z3QAAOSwsnVdyOf-

- esp8266 bulk 
  - https://www.aliexpress.com/item/32665100123.html?spm=a2g0o.productlist.0.0.3ffc15495JaD23&algo_pvid=1e29147f-2a71-40df-94b8-4b58d9622e4f&algo_expid=1e29147f-2a71-40df-94b8-4b58d9622e4f-0&btsid=0ab6d69f15850880382543898e3676&ws_ab_test=searchweb0_0,searchweb201602_,searchweb201603_
  
- esp02 bulk
  - https://www.mouser.com/ProductDetail/Espressif-Systems/ESP-WROOM-02?qs=sGAEpiMZZMsRr7brxAGoXSSUPDSAjAiVc55QyFq0cPAl59eVNM2ypQ%3D%3D
  - https://www.digikey.com/product-detail/en/espressif-systems/ESP-WROOM-02/1904-1009-1-ND/8544304
  
- esp32 bulk
  - https://www.mouser.com/ProductDetail/Espressif-Systems/ESP32-WROOM-32-16MB?qs=sGAEpiMZZMsRr7brxAGoXSSUPDSAjAiVWYDCG5gOE4CudLdUnuGgeQ%3D%3D
  - https://www.mouser.com/ProductDetail/Espressif-Systems/ESP32-SOLO-1?qs=sGAEpiMZZMsRr7brxAGoXSSUPDSAjAiVLQnuuMBfLkMt7n12ghVrZw%3D%3D
  - https://www.digikey.com/product-detail/en/espressif-systems/ESP32-WROVER/1904-1007-1-ND/8544302

- kivy signed build - https://groups.google.com/forum/#!topic/kivy-users/pBtbg8aSlNo
- kivy listview update - https://groups.google.com/forum/#!topic/kivy-users/D7kaXll-rj8

huge dirs:

- ~/.local/share/python-for-android
- ~/.buildozer

### when to raise alarm

- respiratory rate too high or too low

### Definitions

- [ventilator control modes](https://www.youtube.com/watch?v=gk_Qf-JAL84)
- [respiratory cycle example](https://www.youtube.com/watch?v=K0maLgTzIto)
- [pressure control ventilation](https://www.youtube.com/watch?v=h-I6XE6EfMY)

- WOB - work of breathing - 
- compliance - ΔV/ΔP - analogous to stiffness constant of spring (inverted)
- restrictive lung disease - condition in which compliance of lung is reduced.  Greater pressure needed to deliver same volume of air
- FIO2 - fractional inspiration of oxygen - percent of air volume oxygen
- CMV - continuous mandatory control
- IMV - intermittent mandatory control
- TCT - total cycle time (60 / rate)
- Ti - inspiration time
- Te - expiration time
- PC - pressure control
- AC - assist control
- PEEP - positive-end expiratory pressure


- ventilator modes
  - AC - assist control - ventilator control mode where specific volume is delivered to patient in each cycle
    - patient triggers ventilator
    - set tidal volume, instantaneous pressure dependent on lung compliance
    - e.g. 500-600cc of air delivered (8mL/kg bodyweight)
  - PC - pressure control - 
    - patient or ventilator trigger inspiration
    - set tidal pressure, instantaneous volume dependent on lung compliance
    - if compliance of lungs changes, inspired volume can change
  - CPAP - non-invasive ventilation, facemask instead of tracheal tube, sleep apnea
    - devices often have a PEEP setting
    - PEEP - positive-end expiratory pressure - positive pressure setting after expiration
      - prevents sleep apnea, tongue back
      - keeps alveoli open
      - set pressure (cm water pressure, e.g. 5-20 cm)
  - PS - pressure support
    - patient initiates all breaths (e.g. 5-15 cm pressure)
    
- 

### Example Orders for Ventilator
- AC 16 - assist control, backup rate 16 breaths per minute
  - rate: 16
  - tidal volume: 550mL
  - FIO2: 50%
  - PEEP: 5
  - optional: inspiratory flow
  
- PC
  - pressure control level (defined absolutely or amount above PEEP)
  - rate
  - Ti (amount of time pressure held high?)
  - PEEP
  - FiO2
  - Sensitivity
  

### Problems in AC Mode Ventilation

- [detecting respiratory cycle problems](https://www.youtube.com/watch?v=6Bdv7QhNNy4)

- assist control
  - high peak pressure (poor airway flow) (also called Pplat, MAP mean error press., Paw peak airway)
    - bronchiospasms
    - secretions
    - mucus plug
    - tracheal tube occlusion
  - high plateau pressure (low lung compliance)
    - pneumothorax
    - pulmonary edema
    - ARDS
    - pneumonia

### Things to Order
- displays
    - https://www.digikey.com/product-detail/en/lite-on-inc/LTC-4627JF/160-1548-5-ND/408221
- transducers
    - https://www.digikey.com/product-detail/en/nxp-usa-inc/MP3V5004GP/MP3V5004GP-ND/2186181
    - https://www.digikey.com/product-detail/en/nxp-usa-inc/MPXV5004DP/MPXV5004DP-ND/1168429
    - https://www.digikey.com/product-detail/en/nxp-usa-inc/MP3V5004DP/MP3V5004DP-ND/2186178
- buzzers
    - https://www.digikey.com/product-detail/en/pui-audio-inc/AI-3035-TWT-3V-R/668-1204-ND/1745457
    - https://www.digikey.com/product-detail/en/murata-electronics/PKM13EPYH4002-B0/490-4697-ND/1219328
- microcontrollers
    - https://www.digikey.com/product-detail/en/espressif-systems/ESP32-WROOM-32/1904-1010-1-ND/8544305
    - https://www.digikey.com/product-detail/en/microchip-technology/ATMEGA328P-PU/ATMEGA328P-PU-ND/1914589
    - https://www.digikey.com/product-detail/en/microchip-technology/ATMEGA328P-AUR/ATMEGA328P-AURCT-ND/3789455
- tactile switch
    - https://www.digikey.com/product-detail/en/omron-electronics-inc-emc-div/B3FS-1000P/SW423CT-ND/277814
    
- old
    - https://www.digikey.com/product-detail/en/varitronix/VI-201-DP-RC-S/153-1003-ND/2375
    - https://www.digikey.com/product-detail/en/matrix-orbital/MOP-AL162A-BBTW-25J-3IN/635-1206-ND/9602839
    - https://www.digikey.com/product-detail/en/adafruit-industries-llc/1001/1528-1513-ND/5774239
    - https://www.digikey.com/product-detail/en/newhaven-display-intl/NHD-C0216CZ-FSW-FBW-3V3/NHD-C0216CZ-FSW-FBW-3V3-ND/2059234

### Power Supply
- https://www.digikey.com/products/en/power-supplies-external-internal-off-board/ac-dc-desktop-wall-adapters/130?k=power+supply&k=&pkeyword=power+supply&sv=0&sf=0&FV=-8%7C130&quantity=&ColumnSort=1000011&page=1&stock=1&pageSize=25

### Display Modules
- 3.3V, Serial, $8 - https://www.digikey.com/product-detail/en/newhaven-display-intl/NHD-C0216CZ-FSW-FBW-3V3/NHD-C0216CZ-FSW-FBW-3V3-ND/2059234
-


### Differential pressure sensors

##### Single-Ended
| Part        | Price | Quantity | Voltage | Range | Notes      |
| MPXV4006GC6 |       |          | 5V      | 60cm  | Integrated |
| MP3V5004GP  |       | 5000     | 3V      | 40cm  | Integrated |
| MPX5010GP   |       |          |         |       |            |

##### Differential

| Part        | Price | Quantity | Voltage | Range | Notes         |
| MP3V5004DP  |       |          | 3V      | 40cm  | Integrated    |
| MPX10DP     |       |          | 3V      | 100cm | Uncompensated |
| MP3V5010DP  |       |          | 3V      | 100cm | Integrated    |
| MPXV5010DP  |       |          | 5V      | 100cm | Integrated    |
| MP3V5004GC6 |       |          |         | 40    |               |
| MP3V5010GC6 |       |          | 3V      | 100cm | Integrated    |