#include <RH_ASK.h> // Include RadioHead Amplitude Shift Keying Library
#include <SPI.h> // Include dependant SPI Library
 
// Create Amplitude Shift Keying Object
RH_ASK rf_driver;


 int IR = 8;
 int IR_result;                                                                                                                                                                                                                                                 

 int relay = 6;

void setup() {
  Serial.begin(9600);
  rf_driver.init();
  pinMode(relay, OUTPUT);
  pinMode(IR, INPUT);
  digitalWrite(relay, HIGH);
  
}

void loop() {

IR_result = digitalRead(IR);

Serial.print("IR:");
Serial.println(IR_result);

uint8_t buf[11];
uint8_t buflen = sizeof(buf);
if (rf_driver.recv(buf, &buflen))
{
Serial.print("Message Received: ");
Serial.println((char*)buf);

if((buf[0] == 'a') && (IR_result == 0))
{
  Serial.println("Vehicle is STOP");
  digitalWrite(relay, HIGH);
}
else if((buf[0] == 'a') && (IR_result == 1))
{
  Serial.println("Vehicle is strat");
  digitalWrite(relay, LOW);
}
else if(buf[0] == 'b')
{
  digitalWrite(relay, HIGH);
}


}
else
{
  digitalWrite(relay, HIGH);
}
delay(1000);
}
