/**
============================             
  www.kingstonhack.space    
=============================
  
  edited from Simple Read programme on processing.org
  created on: 9/8/18
  
  This script will play one of three movies when a certain value is reaad from the 
  serial port.

  The sketch requires that the movies be loaded into a folder called 'data' within the 
  sketch folder.

 */

import processing.video.*;
import processing.serial.*;

Serial myPort;  // Create object from Serial class
String val;      // Data received from the serial port
int lf = 10;

Movie myMovie1;
Movie myMovie2;
Movie myMovie3;


boolean isplaying1 = false;
boolean isplaying2 = false;
boolean isplaying3 = false;

void setup() 
{
  size(1000, 800);
  // I know that the first port in the serial list on my mac
  // is always my  FTDI adaptor, so I open Serial.list()[0].
  // On Windows machines, this generally opens COM1.
  // Open whatever port is the one you're using.
  printArray(Serial.list());
  String portName = Serial.list()[1];
  myPort = new Serial(this, portName, 9600);
  
  myMovie1 = new Movie(this, "movie1.mp4");
  myMovie2 = new Movie(this, "movie2.mp4");
  myMovie3 = new Movie(this, "movie3.mp4");
        
  delay(200);
}

void draw()
{
  
  
  if ( myPort.available() > 0) {  // If data is available,
   val = myPort.readStringUntil(' '); 
   if(val!=null){
     background(125);
   String[] sensor_cut = split(val,':');
   String reading_1 = trim(sensor_cut[0]);
   String reading_2 = trim(sensor_cut[1]);
   String reading_3 = trim(sensor_cut[2]);   
   
   if(reading_1.equals("1")&&isplaying1==false){
     myMovie1.play();myMovie1.jump(0);
     isplaying1 = true; 
 }
 if(isplaying1){
 play_movie_once(myMovie1,1);
 }
 
   if(reading_2.equals("1")&&isplaying2==false){
     myMovie2.play();myMovie2.jump(0);
     isplaying2 = true;
 }
 if(isplaying2){
 play_movie_once(myMovie2,2);
       }  
       
       
     if(reading_3.equals("1")&&isplaying3==false){
     myMovie3.play();myMovie3.jump(0);
     isplaying3 = true;
 }
 if(isplaying3){
 play_movie_once(myMovie3,3);
       }    
     }
   }
}

void movieEvent(Movie m) {
  m.read();
}

void play_movie_once(Movie this_movie, int which_button){
  float md = this_movie.duration();
  float mt = this_movie.time();
  
  if(int(mt)>=int(md)){print("vid off");
      if(which_button==1){isplaying1 = false;}
      else if(which_button==2){isplaying2 = false;}
      else if(which_button==3){isplaying3 = false;}

}
  else if (mt<md){
    print("duration"+mt+"time"+md);
    image(this_movie, 0, 0);}
    }
  
  
