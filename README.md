# Arduino LED Controller
This project is a RGB LED controller for Arduino UNO R3, using WS2812B LEDs, and it is used in combination with [lights-manager](https://github.com/jgutschon/lights-manager).

## Getting Started
- Besides an Arduino UNO board, all that is needed is the [Arduino IDE](https://www.arduino.cc/en/software)
- Select `Arduino UNO` under `Tools` > `Board` > `Arduino AVR Boards`
- Select the port belonging to the UNO under `Tools` > `Port`

### CLI
The [arduino-cli](https://arduino.github.io/arduino-cli/latest/installation/) may also optionally be used.

## Powershell scripts
The scripts located in `powershell/` are to be used on Windows in the Group Policy Editor in order to automatically turn on and off the lights upon startup/shutdown, otherwise they will always be on.