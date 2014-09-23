#include <Servo.h>
#include <Password.h>
#include <Keypad.h> 

Password password = Password( "A76" );
int pin1 = 14;
int pin2 = 15;
int sPin = 16;
const byte ROWS = 4; 
const byte COLS = 4; 
Servo s1;
// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = { 12,11,9,8 };// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte colPins[COLS] = { 5,4,2,1 };// Connect keypad COL0, COL1 and COL2 to these Arduino pins.


// Create the Keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
   pinMode(pin1, OUTPUT); 
   pinMode(pin2, OUTPUT);   
   digitalWrite(pin1, LOW);
   digitalWrite(pin2, HIGH);
   Serial.begin(9600);
   keypad.addEventListener(keypadEvent); //add an event listener for this keypad
   servoWrite(20);  
}


void loop(){
  keypad.getKey();
}

//take care of some special events
void keypadEvent(KeypadEvent eKey){
  switch (keypad.getState()){
    case PRESSED:
	Serial.print("Pressed: ");
	Serial.println(eKey);
        if(eKey == '#'){
          digitalWrite(pin1, LOW);
          digitalWrite(pin2, HIGH);
         servoWrite(180);  
      }
	switch (eKey){
	  case '*': checkPassword(); break;
	  case '#': password.reset(); break;digitalWrite(pin1, LOW);digitalWrite(pin2, HIGH);
	  default: password.append(eKey);
     }
  }
}

void checkPassword(){
  if (password.evaluate()){
    digitalWrite(pin2, LOW);
    digitalWrite(pin1, HIGH);
    servoWrite(20);
    Serial.println("Success");
    //Add code to run if it works
  }else{
    Serial.println("Wrong");
    //add code to run if it did not work
  }
}
void servoWrite(int angle){
   s1.attach(sPin);
   s1.write(angle);
   Serial.println("turning servo to angle " + angle);
   delay(1000);
   s1.detach();  

}

