# sensor-monitor-switch-interrupt
A simple project that makes use of the [SensorMonitor](https://github.com/trojanc/SensorMonitor) library to poll a switch's state and uses an interrupt to force an immediate update.


## Prerequisites
You need to have platformio installed to run this code (If you feel like it, you can adapt it to run in the usual Arduino IDE). This code is also provided in the `examples` of the SensorMonitor library and can be opened in Arduino IDE directly.

Initialise the project with
```platformio init```

Change the board in `platformio.ini` to match your device

## Running the code
```platformio run --target upload```

## Monitor output
```platformio device monitor```