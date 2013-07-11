# MotionSensor

An Arduino sketch for ATtinys. Controls lighting using a PIR motion sensor.

## Hardware

* ATtiny85 or similar. The pin change interrupt library this sketch uses
  only works with ATtiny processors. But it should be fairly trivial to
  swap in the [PinChangeInt](http://playground.arduino.cc/Main/PinChangeInt)
  library and attach to the CHANGE trigger. Or move the sensor input to
  pin 2 and use an external interrupt.
* A PIR motion sensor on pin 0. The sensors I'm using have "H8157" on the
  label, and seem to be very similar to the ones ladyada uses:
  http://www.ladyada.net/learn/sensors/pir.html
* N-channel MOSFET attached to pin 1. This then switches the lights on
  and off.

## Circuit

The circuit directory contains a [KiCad](http://www.kicad-pcb.org/) project
for the PCB I built for this project. It was intended to be etched using
toner transfer, so lots of big tracks and large gaps.

The current revision of the schematic and PCB layout have changed since I
etched my board. I had to update the schematic to fix a couple of bugs, and
hand-patched my board. The schematic is correct, but the current PCB hasn't
been tested. YMMV.

### Part list

* C1: 100uF electrolytic capacitor
* C2: 10uF electrolytic capacitor
* D1: IN4004 diode
* D2: 3mm LED
* IC1: ATtiny85
* Q1: IRF540N N-channel MOSFET
* R1: 100 1/4W resistor
* R1: 10K 1/4W resistor
* U1: LM7805 voltage regulator

## Software dependencies

* This sketch uses the [DigiSpark TinyPinChange](https://github.com/digistump/DigisparkArduinoIntegration/tree/master/libraries/DigisparkTinyPinChange)
  library to handle the pin change interrupts.
