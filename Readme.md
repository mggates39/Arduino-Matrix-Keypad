# Keypad Lock 
An electronic lock with display, keypad and buzzer

## Description 
This demo project is just a simple keypad with display to drive a lock relay.  It also has
a buzzer to generate tones for keypress, success and failure.

The pass codde is hard coded in the application.

## Parts 
- 1 Arduino Uno
- 1 SSD1306 0.91" 128x32 OLED screen w/I2C 128x32
- 1 4x4 Universial 16 Key Switch Keypad Keyboard
- 1 JBtek 4 Channel DC 5V Relay Module 
- 1 Piezo buzzer
- 1 Breadboard
- 1 100 Ohm resistor, optional
- Assorted Jumper wires

## Libraries
- SPI
- Wire
- Adafruit_GFX
- Adafruit_SSD1306
- Key
- Keypad

## Wiring
Wire the OLED Display to the Arduino

| I2C Pin | Usage | Arduino Pin |
| ------- | ----- | ----------- |
| Vcc | 3.3 volts | 3.3V
| GND | Ground | GND |
| SCL | Serial Clock | SCL - A5 |
| SDA | Serial Data | SDA - A4 |

Wire the Keypad to the Arduino

| Enc Pin | Usage | Arduino Pin |
| ------- | ----- | ----------- |
| R1 | Row 1 | D2 |
| R2 | Row 2 | D3 |
| R3 | Row 3 | D4 |
| R4 | Row 4 | D5 |
| C1 | Column 1 | D6 |
| C2 | Column 2 | D7 |
| C3 | Column 3 | D8 |
| C4 | Column 4 | D9 |

Wire the first relay on the relay board to the Arduino

| Enc Pin | Usage | Arduino Pin |
| ------- | ----- | ----------- |
| GND | Ground | GND |
| Vcc | 5 Volts | 5v |
| INT1 | Active on LOW | D10 |

Wire the buzzer to the Arduino

| Enc Pin | Usage | Arduino Pin |
| ------- | ----- | ----------- |
| GND | Ground | GND |
| sig | through 100 ohm resistor | D11 |

## References
- Initial Keypad code came from [How to setup a keypad on an Arduino](https://www.circuitbasics.com/how-to-set-up-a-keypad-on-an-arduino/)

- Documentation for the [Keypad Library for Arduino](https://playground.arduino.cc/Code/Keypad/)

- Use a Buzzer Module (Piezo Speaker) [Aduino Projects](https://create.arduino.cc/projecthub/SURYATEJA/use-a-buzzer-module-piezo-speaker-using-arduino-uno-89df45)

- Adafruit display libraries can be found in the IDE Library Manager