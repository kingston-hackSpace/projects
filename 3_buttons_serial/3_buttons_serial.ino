/*
============================             
  www.kingstonhack.space    
=============================
 
 edited from original script by DojoDave <http://www.0j0.org>
 modified 30 Aug 2011 by Tom Igoe
 modified 15/07/19

 This script will read push button states the output to string 
 dat to the serial port

 pushbutton attached to pin 2 from +5V
 pushbutton attached to pin 3 from +5V
 pushbutton attached to pin 4 from +5V
 10K resistor attached to pins from ground
*/

// constants won't change. They're used here to
// set pin numbers:

const int buttonPin2 = 2;
const int buttonPin3 = 3;
const int buttonPin4 = 4;

// the number of the pushbutton pin

// variables will change:
// variable for reading the pushbutton status
int buttonState2 = 0;  
int buttonState3 = 0;  
int buttonState4 = 0;  

String value_2;
String value_3;
String value_4;

String output;

void setup() {
  Serial.begin(9600);
  // initialize the pushbutton pin as an input:

  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(buttonPin4, INPUT);
  
}

void loop() {
  // read the state of the pushbutton value:

  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
  buttonState4 = digitalRead(buttonPin4);
  
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:

  if (buttonState2 == HIGH) {
    value_2="1";
    // turn LED on:
  } else {
    value_2="0";
    // turn LED off: 
  }


  if (buttonState3 == HIGH) {
    value_3="1";
    // turn LED on:
  } else {
    value_3="0";
    // turn LED off:
  }


  if (buttonState4 == HIGH) {
    value_4="1";
    // turn LED on:
  } else {
    value_4="0";
    // turn LED off:
  }

String val_lable = " ";
String val_lable1 =":";

output =  value_2+val_lable1+
          value_3+val_lable1+
          value_4+val_lable1+
          val_lable;
Serial.println(output);

delay(100);
  
}
