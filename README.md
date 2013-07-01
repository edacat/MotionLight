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

Note that the PCB layout currently has a couple of errors. My initial
schematic had R1 and D2 in series with the gate of Q1, which meant it
wasn't getting enough voltage to saturate, and due to some confusion on
my part and wonkiness in the component library the MOSFET's footprint is
messed up. I've corrected the schematic, but my PCB was hand-patched, and
the Pcbnew board file in this repository is currently a bit wrong.

## Software dependencies

* This sketch uses the [DigiSpark TinyPinChange](https://github.com/digistump/DigisparkArduinoIntegration/tree/master/libraries/DigisparkTinyPinChange)
  library to handle the pin change interrupts.
