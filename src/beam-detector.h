#pragma once

/* beam-detector library by Julien Vanier <jvanier@gmail.com>
 */

#include "Particle.h"

class BeamDetector
{
public:
  static constexpr auto DEBOUNCE_TIME = 5;
  static constexpr auto POWER_ON_DEBOUNCE_TIME = 20;
  static constexpr auto POWER_ON = HIGH;
  static constexpr auto POWER_OFF = LOW;
  static constexpr auto BEAM_BROKEN = LOW;
  static constexpr auto DETECTION_EDGE = FALLING;

  BeamDetector(pin_t lightPin, pin_t powerPin);

  void begin(bool enablePower = true);

  void enable(bool enablePower);

  bool beamBroken();
  uint32_t detectionCount();

  void setDebounceTime(uint16_t ms);

private:
  void interruptHandler();

private:
  bool enabled;
  pin_t lightPin;
  pin_t powerPin;
  uint16_t debounceTime;
  system_tick_t lastToggleTime;
  uint32_t count;
};
