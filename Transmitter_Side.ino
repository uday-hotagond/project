#include <RH_ASK.h>
#include <SPI.h>

RH_ASK rf_driver;

const int touchPin = 7;
const int irPin = 8;

void setup() {
  Serial.begin(9600);
  rf_driver.init();
  pinMode(touchPin, INPUT);
  pinMode(irPin, INPUT);
}

void loop() {
  int touchState = digitalRead(touchPin);
  int irState = digitalRead(irPin);

  char *msg;

  if (touchState == HIGH && irState == HIGH) {
    msg = "A";  // Helmet worn & awake
  } else if (touchState == HIGH && irState == LOW) {
    msg = "B";  // Helmet worn but sleepy
  } else {
    msg = "C";  // Helmet not worn
  }

  rf_driver.send((uint8_t *)msg, strlen(msg));
  rf_driver.waitPacketSent();

  Serial.print("Sent: ");
  Serial.println(msg);

  delay(500);
}
