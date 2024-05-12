const int blinkPin = 2;
const int motorPin = 13; 
const int buzzerPin = 12; 

int TimeDelay(long startTime) {
    long t = millis() - startTime; 
    t = t / 1000; 
    return t;
}

void setup() {
    pinMode(motorPin, OUTPUT);
    pinMode(buzzerPin, OUTPUT); 
    pinMode(blinkPin, INPUT); 
    digitalWrite(motorPin, HIGH); 
} 

void loop() { 
    long time = 0; // Declare 'time' locally
    
    if (digitalRead(blinkPin)) {
        time = millis(); 
        while (digitalRead(blinkPin)) { 
            digitalWrite(buzzerPin, LOW); 
            digitalWrite(motorPin, LOW); 
            delay(1000); 
        } 
    } else {
        if (TimeDelay(time) >= 3) {
            digitalWrite(buzzerPin, HIGH); 
        }
        if (TimeDelay(time) >= 4) {
            digitalWrite(motorPin, HIGH); 
        }
    } 
}