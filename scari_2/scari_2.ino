//control scari  19.01.2015

// Variables
int ledPinSolid = 13; // choose the pin for the LED
int ledPinFade = 11; //
int pirSus = 2; // choose the input pin (for PIR sensor)
int pirJos = 4; // choose the input pin (for PIR sensor)
int pirState = LOW; // we start, assuming no motion detected
int sus = 0; // variable for reading the pin status
int jos = 0; // variable for reading the pin status

void setup() {
  pinMode(ledPinSolid, OUTPUT); // declare Solid LEDs as output
  pinMode(ledPinFade, OUTPUT); // declare Fader LEDs as output
  pinMode(pirSus, INPUT); // declare sensor as input
  pinMode(pirJos, INPUT); // declare sensor as input
}

// Begin Motion Detection
void loop() {
  sus = digitalRead(pirSus); // reading input value
  jos = digitalRead(pirJos); // reading input value
  
  if (sus == HIGH || jos == HIGH) { // if the input is HIGH
    digitalWrite(ledPinSolid, HIGH); // turn LED ON
    // sets the value (range from 0 to 255):
    analogWrite(ledPinFade, HIGH); // turn LED ON
    // fade in from min to max in increments of 5 points:
    for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=10) {
      analogWrite(ledPinFade, fadeValue);
      // wait for 30 milliseconds to see the fade in effect
      delay(50);
    }
    
    
    delay(3000);
    
    
    // fade out from max to min in increments of 5 points:
    for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -=10) {
      // sets the value (range from 0 to 255):
      analogWrite(ledPinFade, fadeValue);
      // wait for 10 milliseconds to see the dimming effect
      delay(50);
      digitalWrite(ledPinSolid, LOW); // turn LED OFF
      analogWrite (ledPinFade, LOW); //turn LED OFF
    }
  }
 
  
}
