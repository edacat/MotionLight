// Switch a light on and off based on input from a motion sensor.
//
// Hardware:
// * ATtiny85. The power management and (probably) PC interrupt
//   stuff is specific to this chip.
// * PIR motion sensor on pin 0. The sensors I'm using have
//   H8157 on the label, and seem to be very similar to the ones
//   ladyada uses: http://www.ladyada.net/learn/sensors/pir.html
// * N-channel MOSFET attached to pin 1. This then switches some
//   lights on and off.
//
// Dependencies:
// * This sketch uses the DigiSpark TinyPinChange library to
//   handle the pin change interrupts.
//   https://github.com/digistump/DigisparkArduinoIntegration/tree/master/libraries/DigisparkTinyPinChange
// Peter Hardy <peter@hardy.dropbear.id.au>

#include <avr/power.h>
#include <avr/sleep.h>
#include <TinyPinChange.h>

// The pin that's attached to the motion sensor.
static const byte inPin = 0;
// The pin that's attached to the light.
static const byte outPin = 1;

// How long to wait after stillness before turning the light off.
// Note that this needs to be adjusted to account for prescaler shenanigans.
static const long idleTimeout = 10000;

// How much to step the light level during fading.
// TODO: Fading not yet implemented.
static const int lightStep = 10;
// How long to wait between light steps during fading.
// Note that this needs to be adjusted to account for prescaler shenanigans.
// TODO: Fading not yet implemented.
static const int fadeDelay = 10;

// Whether the motion sensor is currently tracking movement.
boolean hasMotion = false;

// If idle, this is the time we should switch off.
long offTime = 0;

// Used by TinyPinChange to hold the Virtual Port for the interrupt function.
int PCVirtualPort;

void inputInterrupt() {
  if (digitalRead(inPin) == HIGH) {
    digitalWrite(outPin, HIGH);
    hasMotion = true;
  } else {
    hasMotion = false;
    offTime = millis() + idleTimeout;
  }
}

void setup() {
  power_all_disable();
  power_timer0_enable();

  pinMode(inPin, INPUT);
  pinMode(outPin, OUTPUT);

  TinyPinChange_Init();
  PCVirtualPort = TinyPinChange_RegisterIsr(inPin, inputInterrupt);
  TinyPinChange_EnablePin(inPin);
}

void loop() {
  if (hasMotion == false && millis() > offTime) {
    digitalWrite(outPin, LOW);
    // Deepest sleep mode - can only be woken by an interrupt
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_mode();
    // Chill for a little to make sure the interrupt handler has run
    delay(100);
  } else {
    // TODO: Got to sleep here and let the watchdog wake us up.
    delay(100);
  }
}
