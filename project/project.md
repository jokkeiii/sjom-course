## Alustava listaus komponenteista

Saatavilla:
-	numpad
-	lcd-screen
-	vibration motor
-	capacitive touch sensor

Tilattava:
-	RTC-module

## Karkean tason speksi harjoitustyön ohjelmiston toiminnoista

**Kello:**

Startup view:
-   instructions how to use
-   eg. press a to continue

View 1:
-   main clock (real time)

View 2:
-   timer
    -   start/stop
    -   reset
-   when timer goes to 0, vibration motor goes off

View 3:
-   setup screen
    -   change timer
    -   set RTC

View 4:
-   read eeprom

Keypad functions:
1. 

**Prio:**

1. RTC
   1. LCD
   2. Keypad
   3. RTC-module
   4. 2 views, clock and setup
2. Timer
   1. Timer-view
   2. When timer goes to 0, light up internal led
   3. EEPROM-view
3. Timer alarm
   1. Vibration motor
   2. Capasitive touch sensor