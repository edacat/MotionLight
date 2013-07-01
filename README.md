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

Note that this board used the wrong pinout for the MOSFET. The board I
etched has been patched by hand, but I haven't yet updated the PCB layout.

## Software dependencies

* This sketch uses the [DigiSpark TinyPinChange](https://github.com/digistump/DigisparkArduinoIntegration/tree/master/libraries/DigisparkTinyPinChange)
  library to handle the pin change interrupts.
