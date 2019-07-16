/*
============================             
  www.kingstonhack.space    
=============================
  
  based on script created by Tom Igoe
  created on: 6/8/18
  
  This script read data String data from serial port and play different mov files based on
  this reading.
  
  Use this script with the arduino in the serial report 
  
  The sketch requires that the mov files be loaded into a folder called 'data' within the 
  sketch folder.

 */
 
import processing.video.*;
import processing.serial.*; 
 
Serial myPort;    // The serial port
PFont myFont;     // The display font
String inString;  // Input string from serial port
int lf = 10;      // ASCII linefeed 
int val;
 
Movie myMovie1;
Movie myMovie2;
Movie myMovie3;

boolean isplaying1 = false;
boolean isplaying2 = false;
boolean isplaying3 = false;
 
void setup() { 
  size(1000,800); 
  // List all the available serial ports: 
  printArray(Serial.list()); 
  // I know that the first port in the serial list on my mac 
  // is always my  Keyspan adaptor, so I open Serial.list()[0]. 
  // Open whatever port is the one you're using. 
  myPort = new Serial(this, Serial.list()[1], 9600); 
  myPort.bufferUntil(lf); 
  
  //place movie files matching the names below in a folder called 'data'
  myMovie1 = new Movie(this, "mov1.mp4");
  myMovie2 = new Movie(this, "mov2.mp4");
  myMovie3 = new Movie(this, "mov.mp4");
  
} 
 
void draw() { 
 background(125); 
  
 println(val);
//MOV 1=====================================
  if(val>200&&isplaying1==false){
       myMovie1.play();myMovie1.jump(0);
       isplaying1 = true;
      }
     
  if(isplaying1){
   play_movie_once(myMovie1,1,0,0);
   }
   
//MOV 2=====================================
     if(val>200&&val<300&&isplaying2==false){
       myMovie2.play();myMovie2.jump(0);
       isplaying2 = true;
      }
     
  if(isplaying2){
   play_movie_once(myMovie2,1,100,200);
   }

   
//MOV 3=====================================
      if(val>300&&isplaying3==false){
       myMovie3.play();myMovie3.jump(0);
       isplaying1 = true;
      }
     
  if(isplaying3){
   play_movie_once(myMovie3,1,0,300);
   }   
} 
 
void movieEvent(Movie m) {
  m.read();
}
 
void serialEvent(Serial p) { 
  inString = p.readString(); 
  val = int(trim((inString)));
} 

void play_movie_once(Movie this_movie, int which_button, int xx, int yy){
  float md = this_movie.duration();
  float mt = this_movie.time();
    if(int(mt)>=int(md)){print("vid off");
        if(which_button==1){isplaying1 = false;}
        else if(which_button==2){isplaying2 = false;}
        else if(which_button==3){isplaying3 = false;}
    }
    
    else if (mt<md){
    print("duration"+mt+"time"+md);
    image(this_movie, xx, yy);}
}
