#include <RH_ASK.h> // Include RadioHead Amplitude Shift Keying Library
#include <SPI.h>    // Include dependant SPI Library
RH_ASK rf_driver;
char *data;

int Switch = 7;

int switch_result;


void setup() {
  Serial.begin(9600);
  rf_driver.init();
  pinMode(Switch, INPUT);
}

void loop()
{

  switch_result = digitalRead(Switch);

  Serial.print("switch:");
  Serial.println(switch_result);


  if (switch_result == 1)
  {

    data = "a";
    rf_driver.send((uint8_t *)data, strlen(data));
    rf_driver.waitPacketSent();
    {
      Serial.println("Message Transmitted: a");
      delay(500);
    }
  }
  else
  {
    data = "b";
    rf_driver.send((uint8_t *)data, strlen(data));
    rf_driver.waitPacketSent();
    {
      Serial.println("Message Transmitted: b");
      delay(500);
    }
    
  }

}
