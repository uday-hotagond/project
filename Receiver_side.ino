#include <RH_ASK.h>
#include <SPI.h>

RH_ASK rf_driver;

const int relayPin = 6;
const int buzzerPin = 5;

void setup() {
  Serial.begin(9600);
  rf_driver.init();
  pinMode(relayPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  digitalWrite(relayPin, HIGH);  // Motor OFF by default
  digitalWrite(buzzerPin, LOW);  // Buzzer off
}

void loop() {
  uint8_t buf[4];
  uint8_t buflen = sizeof(buf);

  if (rf_driver.recv(buf, &buflen)) {
    char message = buf[0];
    Serial.print("Received: ");
    Serial.println(message);

    if (message == 'A') {
      // Helmet worn & awake
      digitalWrite(relayPin, LOW);  // Motor ON
      digitalWrite(buzzerPin, LOW); // Buzzer OFF
    } 
    else if (message == 'B') {
      // Helmet worn & sleepy
      digitalWrite(relayPin, HIGH); // Motor OFF
      digitalWrite(buzzerPin, HIGH); // Buzzer ON
    } 
    else if (message == 'C') {
      // Helmet not worn
      digitalWrite(relayPin, HIGH); // Motor OFF
      digitalWrite(buzzerPin, LOW); // Buzzer OFF
    }
  } 
  else {
    // Fail-safe: no signal
    digitalWrite(relayPin, HIGH);
    digitalWrite(buzzerPin, LOW);
  }

  delay(500);
}
