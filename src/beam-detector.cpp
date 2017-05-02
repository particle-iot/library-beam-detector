/* beam-detector library by Julien Vanier <jvanier@gmail.com>
 */

#include "beam-detector.h"

BeamDetector::BeamDetector(pin_t lightPin, pin_t powerPin) :
  enabled(false),
  lightPin(lightPin),
  powerPin(powerPin),
  debounceTime(DEBOUNCE_TIME)
{
}

void BeamDetector::begin(bool enablePower)
{
  // Setup pins
  pinMode(powerPin, OUTPUT);
  pinMode(lightPin, INPUT);

  // Turn on power if required
  enable(enablePower);

  // Setup interrupt
  attachInterrupt(lightPin, &BeamDetector::interruptHandler, this, DETECTION_EDGE);
}

void BeamDetector::enable(bool enablePower) {
  if (enablePower != enabled) {
    auto now = millis();
    {
      AtomicSection atomic; // this block cannot be interrupted

      // set a lastToggleTime in the future to avoid false interrupts
      // when turning the power on and off
      lastToggleTime = now + POWER_ON_DEBOUNCE_TIME;
      enabled = enablePower;
    }
    digitalWrite(powerPin, enabled ? POWER_ON : POWER_OFF);
  }
}

bool BeamDetector::beamBroken() {
  if (!enabled) {
    return false;
  }
  return digitalRead(lightPin) == BEAM_BROKEN;
}

uint32_t BeamDetector::detectionCount() {
  return count;
}

void BeamDetector::setDebounceTime(uint16_t ms) {
  debounceTime = ms;
}

void BeamDetector::interruptHandler() {
  if (!enabled) {
    return;
  }
  // Debounce the edge transistion to avoid counting multiple detections
  // when the light level is close to the transition point
  auto now = millis();
  if (now - lastToggleTime < debounceTime) {
    return;
  }
  lastToggleTime = now;
  count++;
}
