#include <Servo.h> // include the Servo library
#include "SevSeg.h"
#include <SPI.h>
#include <MFRC522.h>
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         5          // Configurable, see typical pin layout above
#define SS_PIN          53         // Configurable, see typical pin layout above

byte readCard[4];
String MasterTag = "A0134C20";
String tagID = "";

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
SevSeg sevseg; //Initiate a seven segment controller object

// define the pins for the servos and the buttons
const int SERVO1_PIN = 9;
const int SERVO2_PIN = 8;
const int BUTTON1_PIN = 7;
const int BUTTON2_PIN = 6;


//NFC CODES:
//DISK: 13 41 19 A0
//CARD: A0 13 4C 20


//for disp

int a=14; 
int b=15; 
int c=16; 
int d=11; 
int e=4; 
int f=2; 
int g=3; 
int dp=17; 


// create Servo objects
Servo myServo1;
Servo myServo2;

// variables to store the states of the buttons
int button1State = LOW;
int previousButton1State = LOW; // add a variable to store the previous button state
int button2State = LOW;
int previousButton2State = LOW; // add a variable to store the previous button state

//display number 1
void display1(void) 
{ 
    digitalWrite(b,HIGH);
    digitalWrite(c,HIGH);
} 
//display number2
void display2(void) 
{
    digitalWrite(a,HIGH);
    digitalWrite(b,HIGH);
    digitalWrite(g,HIGH);
  digitalWrite(e,HIGH);
    digitalWrite(d,HIGH);
} 
// display number3
void display3(void) 
{ 
    digitalWrite(a,HIGH);
    digitalWrite(b,HIGH);
    
  digitalWrite(c,HIGH);
    digitalWrite(d,HIGH);
    digitalWrite(g,HIGH);
} 
// display number4
void display4(void) 
{ 
    digitalWrite(f,HIGH);
    digitalWrite(b,HIGH);
    digitalWrite(g,HIGH);
  digitalWrite(c,HIGH);
  
} 
// display number5
void display5(void) 
{ 
    digitalWrite(a,HIGH);
    digitalWrite(f,HIGH);
    digitalWrite(g,HIGH);
  digitalWrite(c,HIGH);
    digitalWrite(d,HIGH);
} 
// display number6
void display6(void) 
{ 
    digitalWrite(a,HIGH);
    digitalWrite(f,HIGH);
    digitalWrite(g,HIGH);
  digitalWrite(c,HIGH);
    digitalWrite(d,HIGH);  
    digitalWrite(e,HIGH);  
} 
// display number7
void display7(void) 
{   
   digitalWrite(a,HIGH);
    digitalWrite(b,HIGH);
    digitalWrite(c,HIGH);
} 
// display number8
void display8(void) 
{ 
    digitalWrite(a,HIGH);
    digitalWrite(b,HIGH);
    digitalWrite(g,HIGH);
  digitalWrite(c,HIGH);
    digitalWrite(d,HIGH);  
    digitalWrite(e,HIGH);  
  digitalWrite(f,HIGH);  
} 
void clearDisplay(void) 
{ 
    digitalWrite(a,LOW);
    digitalWrite(b,LOW);
    digitalWrite(g,LOW);
  digitalWrite(c,LOW);
    digitalWrite(d,LOW);  
    digitalWrite(e,LOW);  
  digitalWrite(f,LOW);  
} 
void display9(void) 
{ 
    digitalWrite(a,HIGH);
    digitalWrite(b,HIGH);
    digitalWrite(g,HIGH);
  digitalWrite(c,HIGH);
    digitalWrite(d,HIGH);  
  digitalWrite(f,HIGH);  
} 
void display0(void) 
{ 
    digitalWrite(a,HIGH);
    digitalWrite(b,HIGH);
  digitalWrite(c,HIGH);
    digitalWrite(d,HIGH);  
    digitalWrite(e,HIGH);  
  digitalWrite(f,HIGH);  
} 

void setup() {
  Serial.begin(9600);
  // attach the servos to the defined pins
  myServo1.attach(SERVO1_PIN);
  myServo2.attach(SERVO2_PIN);
  // set the button pins as inputs
  pinMode(BUTTON1_PIN, INPUT);
  pinMode(BUTTON2_PIN, INPUT);
  //display
  pinMode(a,OUTPUT);
  pinMode(b,OUTPUT);
  pinMode(c,OUTPUT);
  pinMode(d,OUTPUT);
  pinMode(e,OUTPUT);
  pinMode(f,OUTPUT);
  pinMode(g,OUTPUT);
  pinMode(dp,OUTPUT);
  
  // set the servos to their starting positions
  myServo1.write(90);
  myServo2.write(90);

  //nfc
  while (!Serial);		// Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
	SPI.begin();			// Init SPI bus
	mfrc522.PCD_Init();		// Init MFRC522
	delay(4);				// Optional delay. Some board do need more time after init to be ready, see Readme
	mfrc522.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details
   Serial.println("--------------------------");
  Serial.println(" eVibe Vending ");
  Serial.println("Scan Your Card to Purchase>>");
   Serial.println("--------------------------");
}

void loop() {
  clearDisplay();
  // read the states of the buttons
  button1State = digitalRead(BUTTON1_PIN);
  button2State = digitalRead(BUTTON2_PIN);
   //Wait until new tag is available
  while (getID()) {
    //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
    if (tagID == MasterTag){
      Serial.println("--------------------------");
      Serial.println(" Card Detected, choose item!");
      Serial.println("--------------------------");
       //You can write any code here like, opening doors, 
       rotateItem();

  Serial.println("----Back Inside ID check-----");
    }
    //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
    else{
      Serial.println("--------------------------");
      Serial.println(" Wrong Card");
      Serial.println("--------------------------");
    }
    //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
    delay(2000);
   
  }

  

  // update the previous button states
  previousButton1State = button1State;
  previousButton2State = button2State;
}
boolean getID() 
{
  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
  // Getting ready for Reading PICCs
  //If a new PICC placed to RFID reader continue
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return false;
  }
  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
  //Since a PICC placed get Serial and continue
  if ( ! mfrc522.PICC_ReadCardSerial()) {
  return false;
  }
  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
  tagID = "";
  // The MIFARE PICCs that we use have 4 byte UID
  for ( uint8_t i = 0; i < 4; i++) {
  //readCard[i] = mfrc522.uid.uidByte[i];
  // Adds the 4 bytes in a single String variable
  tagID.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
  tagID.toUpperCase();
  mfrc522.PICC_HaltA(); // Stop reading
  return true;
  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
}

bool rotateItem(){
  // if the first button's state has changed, print a message to the console
  
  Serial.println("----Inside rotation-----");
  bool hasChosen=0;
  while(hasChosen==0){
  button1State = digitalRead(BUTTON1_PIN);
  button2State = digitalRead(BUTTON2_PIN);
  delay(20);
    //Serial.println("----Inside rotation while loop-----");
     if (button1State != previousButton1State) {
    Serial.print("Button1 state changed: ");
    Serial.println(button1State);
  }

  // if the first button is pressed, rotate the first servo 360 degrees
  if (button1State == HIGH) {

  Serial.println("----Inside BNT1-----");
    display1();
    myServo1.write(170); // rotate to the end position
    delay(800); // add a delay to allow the servo to complete its movement
    myServo1.write(90); // rotate back to the starting position
    delay(2000);
    clearDisplay();

    hasChosen=1;
  }

  // if the second button's state has changed, print a message to the console
  if (button2State != previousButton2State) {
    Serial.print("Button2 state changed: ");
    Serial.println(button2State);
  }

  // if the second button is pressed, rotate the second servo 360 degrees
  if (button2State == HIGH) {

  Serial.println("----Inside BTN2-----");
    display2();
    myServo2.write(170); // rotate to the end position
    delay(800); // add a delay to allow the servo to complete its movement
    myServo2.write(90); // rotate back to the starting position
    delay(2000);
    clearDisplay();
    hasChosen=1;
  }
  
    
  }

  Serial.println("----OUTSIDE WHILE-----");
  previousButton1State = button1State;
  previousButton2State = button2State;
 
}

