## IR Remote Control Simulation
#### Program that simulates IR remote control signals when a sensor is triggered
---
This code sends IR signals (3 times for stability)
*ON* - when motion is detected
*OFF* - after 10 seconds

In this case is realized the control of Night-Light which uses IR remote control, 
- #### Components Required
	- **Board** (e.g., ESP, Pico, Arduino Uno, Nano)
	- **HC-SR501** Motion Sensor
	- **TL1838** IR Receiver
	- **IR TX** (e.g. [this one](https://www.amazon.co.uk/gp/product/B07BFNGF53/ref=ask_ql_qh_dp_hza))

- #### Before we get started
Connect TL1838 (or equivalent) in place of HC-SR501 (D2) and use the standard example IRremote.hpp v4.4.1
`File -> Examples -> IRremote` to capture and hardcode the necessary signals
- #### Wiring Connection

| Component               | Pin on Board                                         |
|-------------------------|------------------------------------------------------|
| **HC-SR501**            |                                                      |
| OUT                     | D2                                                   |
| VCC                     | 5V                                                   |
| GND                     | GND                                                  |
| **Infrared TX**         |                                                      |
| OUT (Anode)             | D3                                                   |
| GND (Cathode)           | GND (Resistor required, typically 220Ω)              |
