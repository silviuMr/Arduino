//VARS
//the time we give the sensor to calibrate (10-60 secs according to the datasheet)
//int calibrationTime = 30;     

//the time when the sensor outputs a low impulse
long unsigned int timp_low;         

//the amount of milliseconds the sensor has to be low 
//before we assume all motion has stopped
long unsigned int pause = 1000;  

boolean blocat_low = true;
boolean start_ceas;  

int pirPinSus = 2;    //the digital pin connected to the PIR sensor's output
int pirPinJos = 4;    //the digital pin connected to the PIR sensor's output
int ledPin = 11;

#define miscare ((digitalRead(pirPinJos)) || (digitalRead(pirPinSus)) == HIGH)
#define stationare ((digitalRead(pirPinJos)) && (digitalRead(pirPinSus) == LOW))

/////////////////////////////
//SETUP
void setup(){
  Serial.begin(115200);
  pinMode(pirPinSus, INPUT);
  pinMode(pirPinJos, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(pirPinSus, LOW);
  digitalWrite(pirPinJos, LOW);
  analogWrite(ledPin, LOW);
  //give the sensor some time to calibrate
  /*Serial.print("calibrating sensor ");
    for(int i = 0; i < calibrationTime; i++){
      Serial.print(".");
      delay(1000);
      }
    Serial.println(" done");
    Serial.println("SENSOR ACTIVE");
    delay(50);
  */
}

////////////////////////////
//LOOP
void loop(){

  
  
     //if(digitalRead(pirPinJos) == HIGH)
     if (miscare)
     {
       fadeUp;
     /*for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -=5) 
        {
        // sets the value (range from 0 to 255):
        analogWrite(ledPin, fadeValue);  
        // wait for 30 milliseconds to see the dimming effect    
        delay(30); 
       
        }*/
      
          
      //digitalWrite(ledPin, HIGH);   //the led visualizes the sensors output pin state
       if(blocat_low){  
         //makes sure we wait for a transition to LOW before any further output is made:
         blocat_low = false;            
         Serial.println("---");
         Serial.print("motion detected at ");
         Serial.print(millis()/1000);
         Serial.println(" sec"); 
         delay(50);
         }         
         start_ceas = true;
     }

     //if(digitalRead(pirPinJos) == LOW)
     if (stationare)
     {       
       /*for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -=5) 
        {
        // sets the value (range from 0 to 255):
        analogWrite(ledPin, fadeValue);  
        // wait for 30 milliseconds to see the dimming effect    
        delay(30); 
       
        }*/
        
                  
       //digitalWrite(ledPin, LOW);  //the led visualizes the sensors output pin state

       if(start_ceas){
        timp_low = millis();          //save the time of the transition from high to LOW
        start_ceas = false;       //make sure this is only done at the start of a LOW phase
        }
       //if the sensor is low for more than the given pause, 
       //we assume that no more motion is going to happen
       if(!blocat_low && millis() - timp_low > pause)
       {  
           //makes sure this block of code is only executed again after 
           //a new motion sequence has been detected
           blocat_low = true;                        
           Serial.print("motion ended at ");      //output
           Serial.print((millis() - pause)/1000);
           Serial.println(" sec");
           delay(50);
           }
       }
}
