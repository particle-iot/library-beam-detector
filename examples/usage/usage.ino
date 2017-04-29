// Example usage for beam-detector library by Julien Vanier <jvanier@gmail.com>.

#include "beam-detector.h"

SYSTEM_THREAD(ENABLED);

const auto LIGHT_PIN = A0;
const auto LASER_PIN = D0;
BeamDetector detector(LIGHT_PIN, LASER_PIN);

void setup() {
  Serial.begin();
  detector.begin();
}

void loop() {
  Serial.printlnf("%d,%d,%d",
    millis(),
    detector.beamBroken(),
    detector.detectionCount()
  );
}
