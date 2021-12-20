#include <IRremote.h>

int ledPins[] = {7};
int lightPin = 7;
int reciever = 11;
int setting;

unsigned long hourToMillis = 3600000;
unsigned long mils;

IRrecv irrecv(reciever);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'


void setup() {
  // put your setup code here, to run once:
  Serial.println("IR Receiver Button Decode");
   pinMode(lightPin, OUTPUT);
   digitalWrite(lightPin, HIGH);

    //reciever enabled
   irrecv.enableIRIn();

   mils = millis() + hourToMillis;
   setting = 1;
}

void loop() {

  // put your main code here, to run repeatedly:

   if (irrecv.decode(&results)) // have we received an IR signal?
  {
    readIRInput();
    irrecv.resume(); // receive the next value
  }
  
 
checkSettings();
delay(100);  


}

void checkSettings(){
  if(setting == 0){
    turnOffPin();
  }else if(setting == 1){
    turnOnPin();
  }else if(setting == 2){
    
    unsigned long current = millis();
    if(mils <= current){
      turnOffPin();
    }else{
      turnOnPin();

      
    }

    
  }


  
}

void readIRInput(){

int n = 0;
 switch(results.value)
  {
  case 0xFFA25D:{
   
    setting = setting >= 1 ? 0 : 1;
    mils = millis();
  }
  return;
  case 0xFFE21D: break;
  case 0xFF629D: break;
  case 0xFF22DD: break;
  case 0xFF02FD: break;
  case 0xFFC23D: break;
  case 0xFFE01F: break;
  case 0xFFA857: break;
  case 0xFF906F: break;
  case 0xFF9867: break;
  case 0xFFB04F: break;
  case 0xFF6897: break;
  case 0xFF30CF: n = 1; break;
  case 0xFF18E7: n = 2; break;
  case 0xFF7A85: n = 3; break;
  case 0xFF10EF: n = 4; break;
  case 0xFF38C7: n = 5; break;
  case 0xFF5AA5: n = 6; break;
  case 0xFF42BD: n = 7; break;
  case 0xFF4AB5: n = 8; break;
  case 0xFF52AD: n = 9; break;
  case 0xFFFFFFFF: break;  
  default: 
    return;

}

if(mils > millis()){
  unsigned long t = n * hourToMillis;
  mils += t;
  
  
}else{
  mils = millis() + n * hourToMillis;
}

setting = 2;


  
}

void turnOnPin(){
  int val = digitalRead(lightPin);
  if(val == LOW){
    digitalWrite(lightPin, HIGH);
    
  }
  
}

void turnOffPin(){
   int val = digitalRead(lightPin);
    if(val == HIGH){
    digitalWrite(lightPin, LOW);
    
  }

  
}
