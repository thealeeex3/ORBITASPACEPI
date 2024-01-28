#include <SPI.h>
#include <LoRa.h>

#define LORA_SS_PIN 10
#define LORA_RST_PIN 9
#define LORA_DIO0_PIN 2

void setup() {
  Serial.begin(115200);
  while (!Serial);

  LoRa.setPins(LORA_SS_PIN, LORA_RST_PIN, LORA_DIO0_PIN);
  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa initialization failed!");
    while (1);
  }
}

void loop() {
  int num1 = 0;
  int num2 = 0;
  bool keyFound = false;

  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    while (LoRa.available()) {
      char c = LoRa.read();
      if (c == 'k') {
        keyFound = true;
      } else if (keyFound && isDigit(c)) {
        num1 = num1 * 10 + (c - '0');
      } else if (keyFound && c == 's') {
        keyFound = false;
      }
    }
  }

  if (num1 != 0) {
    Serial.print("Number 1: ");
    Serial.println(num1);
  }

  delay(1000);
}
