# eeprom-rw
A simple project that demontrates how to read and write to the EEPROM on an Arduino

This simple application will print out the current first 10bytes of the ROM to the serial port, and prompt the user to enter 10 characters to be stored in the ROM.
If you user reboots/resets the device, the user can see that the value is still persistent.

This projects doesn't really do anything to show off to your friends, but is a usefull start if you need to save settings or other values to EEPROM

## Prerequisites
You need to have platformio installed to run this code (If you feel like it, you can adapt it to run in the usual Arduino IDE)
Initialise the project with
```platformio init```

## Running the code
```platformio run```
