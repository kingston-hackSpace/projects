/*
============================             
  www.kingstonhack.space    
============================

 edited from original script by Sparkfun

 This script is designed to play an mp3 when the push button is first pressed down.

 Digital input 11 push button

 https://learn.sparkfun.com/tutorials/mp3-player-shield-hookup-guide-v15/all
 
*/
#include <SPI.h>           // SPI library
#include <SdFat.h>         // SDFat Library

#include <SFEMP3Shield.h>  // Mp3 Shield Library

// constants won't change. They're used here to
// set pin numbers:
const int buttonPin = 11;     // the number of the pushbutton pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

SdFat sd;
SFEMP3Shield MP3player;

const uint8_t volume = 0; // MP3 Player volume 0=max, 255=lowest (off)
const uint16_t monoMode = 1;  // Mono setting 0=off, 3=max

void setup() {
  // initialize the LED pin as an output:
  
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);

  initSD();  // Initialize the SD card
  initMP3Player(); // Initialize the MP3 Shield
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
    
  if (buttonState == HIGH) {
   } else {
      if(MP3player.isPlaying()){
      return;
      }else{
        MP3player.playTrack(1);
        return;
        }
      }
    }

void initSD()
{
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
void initMP3Player()
{
  uint8_t result = MP3player.begin(); // init the mp3 player shield
  if(result != 0) // check result, see readme for error codes.
  {
    // Error checking can go here!
  }
  MP3player.setVolume(volume, volume);
  MP3player.setMonoMode(monoMode);
}
