# Flappy Birds on LCD w/ Arduino

**Materials List**

- Arduino – I'm using the Limited Edition Arduino Uno Mini
- 16x2 LCD screen
- I2C module (that either comes with the LCD screen or get separetly)
- x2 Buttons
- Jumper wires

## **1. Wire Diagram**

| Arduino  | LCD Screen with I2C Module  | Game Button | Reset Button  |
| ---------|-----------------------------|-------------|---------------|
| 5V       | VCC                         |             |               |
| GND      | GND                         | Left Leg    | Left Leg      |
| A4       | SDA                         |             |               |
| A5       | SCL                         |             |               |
| PIN 8    |                             | Right Leg   |               |
| RESET    |                             |             | Right Leg     |

## **2. Install LiquidCrystal I2C Library**
This code uses the **LiquidCrystal Library by Frank de Brabander** to control the LCD screen. The library can be installed from the Arduino IDE by going to **Sketch > Include Library > Manage Libraries.**
