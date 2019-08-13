#include <SPI.h>           // SPI library
#include <SdFat.h>         // SDFat Library
#include <SFEMP3Shield.h>  // Mp3 Shield Library
#include <Wire.h>

SdFat sd; // Create object to handle SD functions

SFEMP3Shield MP3player; // Create Mp3 library object
// These variables are used in the MP3 initialization to set up
// some stereo options:
const uint8_t volume = 0; // MP3 Player volume 0=max, 255=lowest (off)
const uint16_t monoMode = 1;  // Mono setting 0=off, 3=max

//Ultrasonic Sensor 1 
int trigPin1 = 16;    // Trigger
int echoPin1 = 17;    // Echo
long duration, cm;

//Ultrasonic Sensor 2
int trigPin = 19;    // Trigger
int echoPin = 18;    // Echo
long duration1, cm1;

/*MP3 Shield - Pins setup */
#define TRIGGER_COUNT 9
int triggerPins[TRIGGER_COUNT] = {0, 1, 5, 10, A0, A1, A2, A3, A4};
int stopPin = A5; // This pin triggers a track stop.
int lastTrigger = 0; // This variable keeps track of which tune is playing

void setup(){
  Serial.begin (9600);
  
  initSD();  // Initialize the SD card
  initMP3Player(); // Initialize the MP3 Shield
  
  //Define inputs and outputs for both Ultrasonic Sensors
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
}


void loop(){
  
  //Ultrasonic Sensor 1 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  //Ultrasonic Sensor 2 
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
 
  pinMode(echoPin1, INPUT);
  duration1 = pulseIn(echoPin1, HIGH);
 
  // Convert the time into a distance
  // Divide by 29.1 or multiply by 0.0343
  cm = (duration/2) / 29.1; 
  cm1 = (duration1/2) / 29.1; 

// if Ultrasonic Sensor number 1 is grater than 5 play track 1
if(cm>=5){
  MP3player.playTrack(1);
}

// if Ultrasonic Sensor number 2 is grater than 5 play track2
if (cm1>=5){
  MP3player.playTrack(2);
}

// if track is playing and both sensors are less then 4 top the music
if (MP3player.isPlaying()&& cm<=4 && cm1<=4){
        MP3player.stopTrack(); 
}

  // Display both values in the Serial Monitor
  Serial.print(cm);
  Serial.print("cm  , ");
  Serial.print(cm1);
  Serial.println("cm1  ");
  delay(500);
}

void initSD(){
  //Initialize the SdCard.
  if(!sd.begin(SD_SEL, SPI_HALF_SPEED)) 
    sd.initErrorHalt();
  if(!sd.chdir("/")) 
    sd.errorHalt("sd.chdir");
}

// initMP3Player() sets up all of the initialization for the
// MP3 Player Shield. It runs the begin() function, checks
// for errors, applies a patch if found, and sets the volume/
// stero mode.

void initMP3Player(){
  uint8_t result = MP3player.begin(); // init the mp3 player shield
  if(result != 0) // check result, see readme for error codes.
  {
    // Error checking can go here!
  }
  MP3player.setVolume(volume, volume);
  MP3player.setMonoMode(monoMode);
}
