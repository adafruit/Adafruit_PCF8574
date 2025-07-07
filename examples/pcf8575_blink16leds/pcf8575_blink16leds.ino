#include <Adafruit_PCF8575.h>

/* Example for 16 output LEDs that are connected from power to the GPIO expander pins
 * Note the LEDs must be connected with the CATHODES to the expander, to SINK current!
 * The PCF8575 cannot SOURCE current!
 */

Adafruit_PCF8575 pcf;

void setup() {
  Serial.begin(115200);
  while (!Serial) { delay(10); }
  Serial.println("Adafruit PCF8575 LED blink test");

  if (!pcf.begin(0x20, &Wire)) {
    Serial.println("Couldn't find PCF8575");
    while (1);
  }
  for (uint8_t p=0; p<16; p++) {
    pcf.pinMode(p, OUTPUT);
  }
}

void loop() {
  for (uint8_t p=0; p<16; p++) {
    pcf.digitalWrite(p, LOW);  // turn LED on by sinking current to ground
    delay(100);
    pcf.digitalWrite(p, HIGH); // turn LED off by turning off sinking transistor
  }
}
