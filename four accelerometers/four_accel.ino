/*
============================             
  www.kingstonhack.space    
=============================

 edited from original script by 
 Jordan McConnell (SparkFun Electronics)
 created on: 4/6/19

 This script is designed to read data from 4 accelerometers 
 attached to one arduino board

 Analog input 4 I2C SDA
 Analog input 5 I2C SCL
*/

#include <Wire.h> //I2C Arduino Library

#define address 0x1E //0011110b, I2C 7bit address of HMC5883

int state = 1; 

int nunPin1 = 7;  
int nunPin2 = 8;
int nunPin3 = 9;
int nunPin4 = 10;

int nun_1_x =0;int nun_1_y =0;int nun_1_z =0;
int nun_2_x =0;int nun_2_y =0;int nun_2_z =0;
int nun_3_x =0;int nun_3_y =0;int nun_3_z =0;
int nun_4_x =0;int nun_4_y =0;int nun_4_z =0;

void setup(){

   pinMode(nunPin1, OUTPUT);
   pinMode(nunPin2, OUTPUT);
   pinMode(nunPin3, OUTPUT);
   pinMode(nunPin4, OUTPUT);
 
  //Initialize Serial and I2C communications
  Serial.begin(9600);
  Wire.begin();
  
  //Put the HMC5883 IC into the correct operating mode
  // both accelerometers must start out high

  //accelerometer 1
  digitalWrite(nunPin1, HIGH);   
  digitalWrite(nunPin2, LOW);
  digitalWrite(nunPin3, LOW);
  digitalWrite(nunPin4, LOW);
    
  Wire.beginTransmission(address); 
  Wire.write(0x02); 
  Wire.write(0x00); 
  Wire.endTransmission();

  //accelerometer 2
  digitalWrite(nunPin1, LOW);  
  digitalWrite(nunPin2, HIGH);
  digitalWrite(nunPin3, LOW);
  digitalWrite(nunPin4, LOW);

  Wire.beginTransmission(address); 
  Wire.write(0x02); 
  Wire.write(0x00); 
  Wire.endTransmission();

  //accelerometer 3  
  digitalWrite(nunPin1, LOW);   
  digitalWrite(nunPin2, LOW);
  digitalWrite(nunPin3, HIGH);
  digitalWrite(nunPin4, LOW);

  Wire.beginTransmission(address); 
  Wire.write(0x02); 
  Wire.write(0x00); 
  Wire.endTransmission();

  //accelerometer 4  
  digitalWrite(nunPin1, LOW);   
  digitalWrite(nunPin2, LOW);
  digitalWrite(nunPin3, LOW);
  digitalWrite(nunPin4, HIGH);

  Wire.beginTransmission(address); 
  Wire.write(0x02); 
  Wire.write(0x00); 
  Wire.endTransmission();
}

void loop(){
  
  int x,y,z; //triple axis data

  //Tell the HMC5883 where to begin reading data
  Wire.beginTransmission(address);
  Wire.write(0x03); //select register 3, X MSB register
  Wire.endTransmission();
   
 //Read data from each axis, 2 registers per axis
  Wire.requestFrom(address, 6);
  if(6<=Wire.available()){
    x = Wire.read()<<8; //X msb
    x |= Wire.read(); //X lsb
    z = Wire.read()<<8; //Z msb
    z |= Wire.read(); //Z lsb
    y = Wire.read()<<8; //Y msb
    y |= Wire.read(); //Y lsb
  }
    //For debugging
    //Print out values of each axis
    //  Serial.print("x: ");
    //  Serial.print(x);
    //  Serial.print("  y: ");
    //  Serial.print(y);
    //  Serial.print("  z: ");
    //  Serial.println(z);
    //  Serial.print (state);
  switch(state){
    case 1:
        nun_1_x =x; nun_1_y =y; nun_1_z =z;
    break;

    case 2:
        nun_2_x =x; nun_2_y =y; nun_2_z =z;
    break;

    case 3:
        nun_3_x =x; nun_3_y =y; nun_3_z =z;
    break;

    case 4:
        nun_4_x =x; nun_4_y =y; nun_4_z =z;
    break;
    }
  
  int l_x_diff = nun_1_x-nun_2_x;
  int l_y_diff = nun_1_y-nun_2_y;
  int l_z_diff = nun_1_z-nun_2_z;

  int r_x_diff = nun_3_x-nun_4_x;
  int r_y_diff = nun_3_y-nun_4_y;
  int r_z_diff = nun_3_z-nun_4_z;

//If sufficient difference between reading write to the serial port
  if(nun_1_x-nun_2_x<200 && 
      nun_1_y-nun_2_y<200 && 
        nun_1_z-nun_2_z<200)
        {Serial.print("0");}
        else{Serial.print("1");}
Serial.print(",");
   if(nun_3_x-nun_4_x<200 && 
      nun_3_y-nun_4_y<200 && 
        nun_3_z-nun_4_z<200)
        {Serial.println("0");}
        else{Serial.println("1");}
  change_accel();
  delay(100);
}

void change_accel()      // Swaps between accellerometers
{
  if (state == 1)
  {
    digitalWrite(nunPin1, HIGH);
    digitalWrite(nunPin2,LOW);
    digitalWrite(nunPin3,LOW);
    digitalWrite(nunPin4,LOW);
    state = 2;

  }
  else if (state == 2)
  {
    
    digitalWrite(nunPin1, LOW);
    digitalWrite(nunPin2,HIGH);
    digitalWrite(nunPin3, LOW);
    digitalWrite(nunPin4, LOW);
    state = 3;
  }
  else if (state == 3)
  {
    digitalWrite(nunPin1, LOW);
    digitalWrite(nunPin2,LOW);
    digitalWrite(nunPin3,HIGH);
    digitalWrite(nunPin4,LOW);
    state = 4;
  }
  else if (state == 4)
  {
    digitalWrite(nunPin1, LOW);
    digitalWrite(nunPin2,LOW);
    digitalWrite(nunPin3,LOW);
    digitalWrite(nunPin4,HIGH);
    state = 1;
  }
  return;
}

void begintransmission(){
Wire.begin();
  Wire.beginTransmission(address); //open communication with HMC5883
  Wire.write(0x02); //select mode register
  Wire.write(0x00); //continuous measurement mode
  Wire.endTransmission();
}
