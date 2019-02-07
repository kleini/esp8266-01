#define FW_NAME "esp8266-01"
#define FW_VERSION "0.2.0"

#include "Homie.h"

void onHomieEvent(const HomieEvent& event) {
  switch(event.type) {
    case HomieEventType::MQTT_READY:
      Homie.prepareToSleep();
      break;
    case HomieEventType::READY_TO_SLEEP:
      Homie.doDeepSleep(60*1000000);
      break;
    default:
      break;
  }
}

void setup() {
  Serial.begin(115200);
  Serial << endl << endl;

  WiFi.forceSleepWake();

  Homie_setFirmware(FW_NAME, FW_VERSION);
  Homie.disableResetTrigger();
  Homie.disableLedFeedback();

  Homie.onEvent(onHomieEvent);

  Homie.setup();
}

void loop() {
  Homie.loop();
}
