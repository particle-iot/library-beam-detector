/* beam-detector library by Julien Vanier <jvanier@gmail.com>
 */

#include "beam-detector.h"

BeamDetector::BeamDetector(pin_t lightPin, pin_t powerPin) :
  lightPin(lightPin),
  powerPin(powerPin),
  debounceTime(DEBOUNCE_TIME)
{
}

void BeamDetector::begin()
{
  // Setup pins
  pinMode(powerPin, OUTPUT);
  digitalWrite(powerPin, HIGH);
  pinMode(lightPin, INPUT);

  // Setup interrupt
  attachInterrupt(lightPin, &BeamDetector::interruptHandler, this, DETECTION_EDGE);
}

bool BeamDetector::beamBroken() {
  return digitalRead(lightPin) == BEAM_BROKEN;
}

uint32_t BeamDetector::detectionCount() {
  return count;
}

void BeamDetector::setDebounceTime(uint16_t ms) {
  debounceTime = ms;
}

void BeamDetector::interruptHandler() {
  // Debounce the edge transistion to avoid counting multiple detections
  // when the light level is close to the transition point
  auto now = millis();
  if (now - lastToggleTime < debounceTime) {
    return;
  }
  lastToggleTime = now;
  count++;
}
