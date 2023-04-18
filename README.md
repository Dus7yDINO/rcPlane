# Arduino controlled remote control plane

## Project aims
The main aim is to be able to effectively control a remote control plane with two arduino nanos, using two NRF24L01 wireless modules.
The secondary aim is to implement a PID controlled auto-level system, although this is a long way off...
See [my spreadsheet](https://docs.google.com/spreadsheets/d/1AqZf3EmFratxWStfT653ApI9o3uzO_wXOzFvKitIQiA/edit?usp=sharing) for details

## Specifications and features
### Critical
- 4 analog inputs: throttle, alierons, elevators and rudder.
- 1 digital input: flaps toggle
- Range 600m
- Less than 50ms sustained downtime in open air and within range
- Display controller and plane battery voltage on the controller screen

### Optional
- 9 axis attitude tracking
- Log the inputs and attitude information onto an SD card
- Autolevel mode
- Airspeed measure

## Bill of materials
- The controller is a hacked Spektrum DX5E, with all the internal electronics removed.
- The plane is a DIY foamcore model, with a 1.4m wingspan.
- 2X Wireless module, NRF24l01
- 2X Arduino nano
- 2X Arduino I2C 128x64 OLED display
- 6X 9g servo
- Brushless motor
- Electronic speed controller (ESC)
