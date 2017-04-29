# Beam Detector

A Particle firmware library for a laser break beam detector.

## Usage

Connect the laser beam to an NPN transistor on an output pin, connect the photoresistor to a pull down resistor and an input pin.

```
#include "beam-detector.h"

const auto LIGHT_PIN = A0;
const auto LASER_PIN = D0;
BeamDetector detector(LIGHT_PIN, LASER_PIN);

void setup() {
  detector.begin();
}

void loop() {
  if (detector.beamBroken()) {
    // do stuff
  }
  // event count is in detector.detectionCount()
}
```

See the [examples](examples) folder for more details.

## LICENSE
Copyright 2017 Particle Industries

Licensed under the LGPL3 license
