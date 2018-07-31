// Axe-FX midi.controller 23-Oct-2016 V6.9
// Updated 29 Dec 2017, Jeff Anderson

#include <MIDI.h>
#include <LiquidCrystal.h>

#include <SoftwareSerial.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

//Debugging flags
bool printAllMidiMessages = true;

// MIDI Setup
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI); 
#define MIDICHAN 1 //MIDI channel
#define InputVolume_CC 10
#define Out1Volume_CC 11
#define Out2Volume_CC 12
#define Bypass_CC 13
#define Tempo_CC 14
#define Tuner_CC 15
#define ExternalControl1_CC 16
#define ExternalControl2_CC 17
#define ExternalControl3_CC 18
#define ExternalControl4_CC 19
#define ExternalControl5_CC 20
#define ExternalControl6_CC 21
#define ExternalControl7_CC 22
#define ExternalControl8_CC 23
#define ExternalControl9_CC 24
#define ExternalControl10_CC 25
#define ExternalControl11_CC 26
#define ExternalControl12_CC 27
#define LooperRecord_CC 28
#define LooperPlay_CC 29
#define LooperOnce_CC 30
#define LooperDub_CC 31
#define LooperRev_CC 32
#define LooperBypass_CC 33
#define LooperHalf_CC 120
#define LooperUndo_CC 121
#define SceneSelect_CC 34
#define VolumeIncrement_CC 35
#define VolumeDecrement_CC 36
#define Amp1Bypass_CC 37
#define Amp2Bypass_CC 38
#define Cab1Bypass_CC 39
#define Cab2Bypass_CC 40
#define Chorus1Bypass_CC 41
#define Chorus2Bypass_CC 42
#define Compressor1Bypass_CC 43
#define Compressor2Bypass_CC 44
#define Crossover1Bypass_CC 45
#define Crossover2Bypass_CC 46
#define Delay1Bypass_CC 47
#define Delay2Bypass_CC 48
#define Drive1Bypass_CC 49
#define Drive2Bypass_CC 50
#define EnhancerBypass_CC 51
#define Filter1Bypass_CC 52
#define Filter2Bypass_CC 53
#define Filter3Bypass_CC 54
#define Filter4Bypass_CC 55
#define Flanger1Bypass_CC 56
#define Flanger2Bypass_CC 57
#define Formant1Bypass_CC 58
#define FXLoopBypass_CC 59
#define Gate/Expander1Bypass_CC 60
#define Gate/Expander2Bypass_CC 61
#define GraphicEQ1Bypass_CC 62
#define GraphicEQ2Bypass_CC 63
#define GraphicEQ3Bypass_CC 64
#define GraphicEQ4Bypass_CC 65
#define MegatapDelayBypass_CC 66
#define MultibandComp1Bypass_CC 67
#define MultibandComp2Bypass_CC 68
#define Multi-Delay2Bypass_CC 69
#define Multi-Delay2Bypass_CC 70
#define ParametricEQ1Bypass_CC 71
#define ParametricEQ2Bypass_CC 72
#define ParametricEQ3Bypass_CC 73
#define ParametricEQ4Bypass_CC 74
#define Phaser1Bypass_CC 75
#define Phaser2Bypass_CC 76
#define PitchShifter1Bypass_CC 77
#define PitchShifter2Bypass_CC 78
#define QuadChorus1Bypass_CC 79
#define QuadChorus2Bypass_CC 80
#define Resonator1Bypass_CC 81
#define Resonator2Bypass_CC 82
#define Reverb1Bypass_CC 83
#define Reverb2Bypass_CC 84
#define RingModulatorBypass_CC 85
#define Rotary1Bypass_CC 86
#define Rotary2Bypass_CC 87
#define Synth1Bypass_CC 88
#define Synth2Bypass_CC 89
#define Tremolo1Bypass_CC 90
#define Tremolo2Bypass_CC 91
#define VocoderBypass_CC 92
#define Volume/Pan1Bypass_CC 93
#define Volume/Pan2Bypass_CC 94
#define Volume/Pan3Bypass_CC 95
#define Volume/Pan4Bypass_CC 96
#define Wahwah1Bypass_CC 97
#define Wahwah2Bypass_CC 98
#define ToneMatching_CC 99
#define Amp1X/Y_CC 100
#define Amp2X/Y_CC 101
#define Cab1X/Y_CC 102
#define Cab2X/Y_CC 103
#define Chorus1X/Y_CC 104
#define Chorus2X/Y_CC 105
#define Delay1X/Y_CC 106
#define Delay2X/Y_CC 107
#define Drive1X/Y_CC 108
#define Drive2X/Y_CC 109
#define Flanger1X/Y_CC 110
#define Flanger2X/Y_CC 111
#define Phaser1X/Y_CC 112
#define Phaser2X/Y_CC 113
#define Pitch1X/Y_CC 114
#define Pitch2X/Y_CC 115
#define Reverb1X/Y_CC 116
#define Reverb2X/Y_CC 117
#define Wahwah1X/Y_CC 118
#define Wahwah2X/Y_CC 119
#define LooperHalf_CC 120
#define LooperUndo_CC 121
#define Metronome_CC 122
#define SceneIncrement_CC 123
#define SceneDecrement_CC 124
#define Rotary1X/Y_CC 125
#define Rotary2X/Y_CC 126

// sysex requests
  //Doc on header 
    // 0x00 Manf. ID byte0
    // 0x01 Manf. ID byte1
    // 0x74 Manf. ID byte2
    // 0xdd Model # : 0x03 Axe FX II, 0x06 Axe FX II XL
  //Need to update checksums - this is XOR of the first 0xF0 (isn't in this call) through the header and stops w/ the fcn call
  //    then and this number with the final byte (handled by arduino) 0x7F. 
  //    For the Axe FX XL the xor of the checksum through the header is 0x83
  //               byte0  byte1 byte2 model fcn   checksum
byte RQSTNAME[6]  = { 0x00, 0x01, 0x74, 0x06, 0x0F, 0x0C }; 
byte RQSTNUM[6]   = { 0x00, 0x01, 0x74, 0x06, 0x14, 0x17 };
byte RQSTCC[6]    = { 0x00, 0x01, 0x74, 0x06, 0x0E, 0x0D };
byte RQSTSCENE[6] = { 0x00, 0x01, 0x74, 0x06, 0x29, 0x7F};//0x2A };

byte GET_FRIMWARE_VERSION[6] = { 0x00, 0x01, 0x74, 0x06, 0x08, 0x0B };

// Switch setup
#define BOUNCEDELAY 100 //was 25ms
const int nSwitches = 14;
                                //  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13   Button/Switch numbers
const int ledPins[nSwitches]    = {23, 27, 31, 35, 39, 22, 26, 30, 34, 38, 42, 46, 50, 43};
const int switchPins[nSwitches] = {25, 29, 33, 37, 41, 24, 28, 32, 36, 40, 44, 48, 52, 45};
int ledState[nSwitches]         = {LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW};
int switchState[nSwitches] = { LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW};
int buttonSetupMode = 1;// 1 is 4CT, 2 is NORMAL
int buttonFunction[nSwitches]= {1, 2, 3, 4, 5, 104, 14, 15, 17, 21, 13, 12, 10, 9}; // Used to define the function of each switch in the code for different operating modes
// int setupButtonFunctions4CT[nSwitches] = {1, 2, 3, 4, 5, 104, 101, 102, 103, 105, 13, 12, 10, 9};
// Possible 
// *  101 - extAmpSwitchingCh1  
// *  102 - extAmpSwitchingCh2
// *  103 - extAmpSwitchingCh3
// *  104 - extAmpSwitchingSolo
// *  105 - extAmpSwitchingFxLoop
// *    1 - Scene 01
// *    2 - Scene 02
// *    3 - Scene 03
// *    4 - Scene 04
// *    5 - Scene 05
// *    6 - Scene 06
// *    7 - Scene 07
// *    8 - Scene 08
// *    9 - Preset Up
// *   10 - Preset Down
// *   11 - Tap Tempo // little flakey and needs some work
// *   12 - Tuner 
// *   13 - Favorites
// *   14 - LooperRecord 
// *   15 - LooperPlay 
// *   16 - LooperOnce // NOT CODED YET
// *   17 - LooperDub // NOT CODED YET
// *   18 - LooperRev // NOT CODED YET
// *   19 - LooperBypass // NOT CODED YET
// *   20 - LooperHalf // NOT CODED YET
// *   21 - LooperUndo // NOT CODED YET

//LCD & 7seg
const int rs = 3, e = 2, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal   lcd(rs,  e,  d4, d5, d6, d7);
Adafruit_7segment matrix = Adafruit_7segment(); //communicating over i2c bus
bool updateLcd = false;

//External switching setup - for mesa tripple rect external switching, need two T/S cables. Shorting ch1 or ch3 will switch to either and both open will choose ch2
int externalAmpChannelRelayPins[2] = {9,10};
int externalAmpCurrentChannel = 0;
int externalSoloModeRelayPin = 11;
bool externalSoloModeState = false;
int externalFxLoopRelayPin = 12;
bool externalFxLoopState = false;

//Tuner
bool tunerStatus = false; // Tuner on/off
int tunerSwitch = 11; // What switch the tuner is assigned to 
unsigned long lastTunerUpdate = 0;
bool updTunerLCD = false;
char currentNote[2] = "XX";
int fineTune = 0;
int noteOctave = 0;

//Tempo
unsigned long currentTempo = 0;
unsigned long lastTempoSysExMillis;
unsigned long lastUserTempoPulse = 0;

//Presets
int favoritePresets[3] = {0,1,463};
int currentPresetNumber = 0; //Variable for storing current preset
char presetName[32];
int currentScene = 0;

unsigned long currentTime;      // call time of FX request in millis

void setup() {
  // Button functions
  // memcpy(buttonFunction,setupButtonFunctions4CT,nSwitches);

  //Set MIDI baud rate:
  Serial.begin(115200);
  
  Serial.println("Initializing AxeFx Controller");
  //LCD Initial Message
  lcd.clear(); 
  lcd.begin(16, 2);
  lcd.setCursor(0,0); 
  lcd.print("AxeFX Controller"); 

  //Setup external amp pins
  pinMode(     externalAmpChannelRelayPins[0],OUTPUT);
  digitalWrite(externalAmpChannelRelayPins[0],HIGH);
  pinMode(     externalAmpChannelRelayPins[1],OUTPUT);
  digitalWrite(externalAmpChannelRelayPins[1],HIGH);
  pinMode(     externalSoloModeRelayPin,      OUTPUT);
  digitalWrite(externalSoloModeRelayPin,      HIGH);
  pinMode(     externalFxLoopRelayPin,        OUTPUT);
  digitalWrite(externalFxLoopRelayPin,        HIGH);

  //Setup MIDI
  MIDI.begin(0);
  MIDI.turnThruOff();
  MIDI.setHandleSystemExclusive(HandleSysEx);

  //Request Number (which will request name)  
  MIDI.sendSysEx(6,RQSTNUM);
  // MIDI.sendSysEx(6,RQSTSCENE);
  delay(250);
  // Serial.print("Current Scene is: ");
  // Serial.println(currentScene);
  // requestSceneChangeToScene(currentScene);
  requestSceneChangeToScene(1);

  // Setup Switches and activation LEDs
  for( int iSwitch = 0; iSwitch < nSwitches; iSwitch++ ) {
    pinMode(switchPins[iSwitch], INPUT);
    pinMode( ledPins[iSwitch], OUTPUT );             // Set pin for LED
    digitalWrite( ledPins[iSwitch], HIGH );
    delay( 100 );
    digitalWrite( ledPins[iSwitch], LOW );
  }



  // 7Seg setup
  matrix.begin(0x70);  // pass in the address       
  for (int i=0; i<=5; i++) {
    matrix.writeDigitNum(i, 0);
    matrix.drawColon(false);
    delay(100);
    matrix.writeDisplay();
  }
  updateLcd = true;
  Serial.println("Finished setup");
  lcd.clear(); 
}

void loop() {
  // Update MIDI and check if FX block status needs updating
  MIDI.read();
  if (currentTime > 0 && (currentTime + 100) < millis()) {
      MIDI.sendSysEx(6,RQSTCC);
      currentTime = 0;
      updateLcd = true;
  }


  // Are we in tuner mode?
  if (tunerStatus == true){
    for (int iSwitch=0;iSwitch<nSwitches;iSwitch++){
      if (buttonFunction[iSwitch]==12){
        digitalWrite(ledPins[iSwitch],HIGH); 
      }
      else {
        digitalWrite(ledPins[iSwitch], LOW);
      }
    }
    //Record how long it's been since last update, since no specific flag is thrown if user presses button on axe fx, rely on how much time has past
    unsigned long ellapsedTime = millis() - lastTunerUpdate ;
    // If it's been a while, turn the tuner off (after ~100ms)
    if (ellapsedTime > 100){
      tunerStatus = false;
      Serial.println("EXITING TUNER");
      for (int iSwitch=0;iSwitch<nSwitches;iSwitch++){
        if (buttonFunction[iSwitch]==12){
          digitalWrite(ledPins[iSwitch],LOW); ledState[iSwitch] = LOW;
        }
        else {
          digitalWrite(ledPins[iSwitch], ledState[iSwitch]);
        }
      }
      lcd.clear();
      updateLcd = true;
    }

    if (updTunerLCD == true){
      lcd.setCursor(0,0);
      lcd.print("TUNER ON        ");
      lcd.setCursor(0,1);
      if      (fineTune <=25 ){lcd.print(" >>    "); lcd.setCursor(10,1); lcd.print("      ");}
      else if (fineTune <=40 ){lcd.print("  >>   "); lcd.setCursor(10,1); lcd.print("      ");}
      else if (fineTune <=50 ){lcd.print("   >>  "); lcd.setCursor(10,1); lcd.print("      ");}
      else if (fineTune <=57 ){lcd.print("    >> "); lcd.setCursor(10,1); lcd.print("      ");}
      else if (fineTune <=60 ){lcd.print("     >>"); lcd.setCursor(10,1); lcd.print("      ");}
      else if (fineTune <=62 ){lcd.print("      >"); lcd.setCursor(10,1); lcd.print("      ");}
      else if (fineTune <=63 ){lcd.print(" >>>>>>"); lcd.setCursor(10,1); lcd.print("<<<<<<");}
      else if (fineTune <=76 ){lcd.print("       "); lcd.setCursor(10,1); lcd.print("<     ");}
      else if (fineTune <=70 ){lcd.print("       "); lcd.setCursor(10,1); lcd.print("<<    ");}
      else if (fineTune <=78 ){lcd.print("       "); lcd.setCursor(10,1); lcd.print(" <<   ");}
      else if (fineTune <=89 ){lcd.print("       "); lcd.setCursor(10,1); lcd.print("  <<  ");}
      else if (fineTune <=104){lcd.print("       "); lcd.setCursor(10,1); lcd.print("   << ");}
      else                    {lcd.print("       "); lcd.setCursor(10,1); lcd.print("    <<");}    
      lcd.setCursor(7,1);
      lcd.print(currentNote);
      lcd.setCursor(9,1);
      lcd.print(noteOctave);
      updTunerLCD = false;
    }

    //Make sure tuner light is on
    digitalWrite(tunerSwitch,HIGH);
  }


  // update LCD display
  if (updateLcd == true) {
    Serial.println("LCD update");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(presetName);
    lcd.setCursor(0,1);
    lcd.print("Ch: "); lcd.print(externalAmpCurrentChannel);

    matrix.writeDigitNum(0, (currentPresetNumber / 100) % 10, false);
    matrix.writeDigitNum(1, (currentPresetNumber / 10) % 10, false);
    matrix.drawColon(false);
    matrix.writeDigitNum(3, (currentPresetNumber / 1) % 10, true);
    matrix.writeDigitNum(4, currentScene, false);
    matrix.writeDisplay();
    updateLcd = false;
  }
  
  for( int iSwitch = 0; iSwitch < nSwitches; iSwitch++ ) {
    if((digitalRead(switchPins[iSwitch]) != switchState[iSwitch]) && (switchState[iSwitch] == HIGH)){
      Serial.print("SWITCH PRESSED: ");
      Serial.println(iSwitch);
      Serial.print("Button function: ");
      Serial.println(buttonFunction[iSwitch]);
      
      switch(buttonFunction[iSwitch]) {
        case 101:
          requestExtAmpChanngelChangeToChannel(1); 
        break;
        case 102:
          requestExtAmpChanngelChangeToChannel(2); 
        break;
        case 103:
          requestExtAmpChanngelChangeToChannel(3); 
        break;  
        case 104:
          externalSoloModeState = !externalSoloModeState;
          if (externalSoloModeState == true){
            digitalWrite(externalSoloModeRelayPin,LOW);
            digitalWrite(ledPins[iSwitch], LOW); ledState[iSwitch] = LOW;
          }
          else {
            digitalWrite(externalSoloModeRelayPin,HIGH);
            digitalWrite(ledPins[iSwitch], HIGH); ledState[iSwitch] = HIGH;
          }
        break;
        case 105:
          externalFxLoopState = !externalFxLoopState;
          if (externalFxLoopState == true){
            digitalWrite(externalFxLoopRelayPin,LOW);
            digitalWrite(ledPins[iSwitch], LOW); ledState[iSwitch] = LOW;
          }
          else {
            digitalWrite(externalFxLoopRelayPin,HIGH);
            digitalWrite(ledPins[iSwitch], HIGH); ledState[iSwitch] = HIGH;
          }
        break;              
        case 1: 
          requestSceneChangeToScene(1);
        break;
    		case 2: 
          requestSceneChangeToScene(2);
        break;
  		  case 3: 
          requestSceneChangeToScene(3);
        break;
        case 4: 
          requestSceneChangeToScene(4);
        break;
        case 5: 
          requestSceneChangeToScene(5);
        break;
        case 6: 
          requestSceneChangeToScene(6);
        break;
        case 7: 
          requestSceneChangeToScene(7);
        break;
        case 8: 
          requestSceneChangeToScene(8);
        break;     
        case 9:
          currentPresetNumber++;
          requestPresetChangeToPreset(currentPresetNumber);          
          digitalWrite(ledPins[iSwitch],HIGH);
          delay(250);
          digitalWrite(ledPins[iSwitch], LOW);
        break;    
        case 10:
          currentPresetNumber--;
          requestPresetChangeToPreset(currentPresetNumber);          
          digitalWrite(ledPins[iSwitch],HIGH);
          delay(250);
          digitalWrite(ledPins[iSwitch], LOW);
        break;     
        case 11: // Tempo
          currentTempo = 1.0/((millis() - lastUserTempoPulse)/1000.0/60.0);
          lastUserTempoPulse = millis();
          Serial.print("Current Tempo: ");
          Serial.println(currentTempo);
          MIDI.sendControlChange(Tempo_CC,currentTempo , MIDICHAN);  
          digitalWrite(ledPins[iSwitch],HIGH);
          delay(5);
          digitalWrite(ledPins[iSwitch], LOW);
        break;      
        case 12: // Tuner
          Serial.println("toggle tunerStatus");
          if (tunerStatus == false) {
            MIDI.sendControlChange(Tuner_CC,127,MIDICHAN);
            // tunerStatus = true;
          }
          else {
            // tunerStatus = false;
            MIDI.sendControlChange(Tuner_CC,0,MIDICHAN);
          }        
          delay(100);       
        break;                                 
        case 14:          
          //Turn the LEDS all off excpet this one
          for (int i=0;i<nSwitches;i++){
            if (i != iSwitch){
              digitalWrite(ledPins[i],LOW); 
            }
            else {
              digitalWrite(ledPins[i], HIGH);
            }
          }          
          //Start the recording
          Serial.println("Looper Record started");
          MIDI.sendControlChange(LooperRecord_CC, 127, MIDICHAN);   
          delay(200);
          //Wait for the button to become high again to stip it
          while (digitalRead(switchPins[iSwitch]) == LOW){
            delay(1);
            Serial.println("WATING");
          }
          Serial.println("Looper Record finished");
          MIDI.sendControlChange(LooperRecord_CC, 0, MIDICHAN);   
          //Put lights back to normal
          for (int i=0;i<nSwitches;i++){
            if (buttonFunction[i] == 15) { // playback case
              digitalWrite(ledPins[i], HIGH); ledState[i] = HIGH;
            }
            digitalWrite(ledPins[i],ledState[i]); 
          } 
          delay(100);
        break;
        case 15:
          Serial.println("Toggle looper play");
          if (ledState[iSwitch] == false) {
            MIDI.sendControlChange(LooperPlay_CC,127,MIDICHAN);
            digitalWrite(ledPins[iSwitch], HIGH); ledState[iSwitch] = HIGH;
          }
          else {
            MIDI.sendControlChange(LooperPlay_CC,0,MIDICHAN);
            digitalWrite(ledPins[iSwitch], LOW); ledState[iSwitch] = LOW;
          }        
          delay(100);          
        break;
        case 17:
          //Turn the LEDS all off excpet this one
          for (int i=0;i<nSwitches;i++){
            if (i != iSwitch){
              digitalWrite(ledPins[i],LOW); 
            }
            else {
              digitalWrite(ledPins[i], HIGH);
            }
          }          
          //Start the recording
          Serial.println("Looper Record started");
          MIDI.sendControlChange(LooperDub_CC, 127, MIDICHAN);   
          delay(200);
          //Wait for the button to become high again to stip it
          while (digitalRead(switchPins[iSwitch]) == LOW){
            delay(1);
            Serial.println("WATING");
          }
          Serial.println("Looper Record finished");
          MIDI.sendControlChange(LooperDub_CC, 0, MIDICHAN);   
          //Put lights back to normal
          for (int i=0;i<nSwitches;i++){
            if (buttonFunction[i] == 15) { // playback case
              digitalWrite(ledPins[i], HIGH); ledState[i] = HIGH;
            }
            digitalWrite(ledPins[i],ledState[i]); 
          } 
          delay(100);
        break;
        case 21:
          digitalWrite(ledPins[iSwitch], HIGH);
          MIDI.sendControlChange(LooperUndo_CC,127,MIDICHAN);
          delay(100);
          digitalWrite(ledPins[iSwitch], LOW);
        break;

        case 13: // Favorites - I guess because of how I'm allocating nFavorites, this case need to be last
          digitalWrite(ledPins[iSwitch], HIGH);
          // We're not on a favorite, so go to the closet one
          Serial.println("FAVORITES________________________<");
          int nFavorites = sizeof favoritePresets/sizeof favoritePresets[0];
          int distToFavorite; 
          int minDistance = 1000; //Arbitarily big number to get lower than
          int indexMin;
          int specialCaseIntOfZeroDistance = 1000; //Arbitrairly big number

          //Calculate the min distance to a favorite 
          for (int i=0; i<nFavorites; i++){
            distToFavorite = abs(currentPresetNumber - favoritePresets[i]);
            if (distToFavorite < minDistance) {
              minDistance = distToFavorite;
              indexMin = i;
            }
          } 
          // Case that we're already on a favorite, toggle to the next one
          if (minDistance == 0){
            indexMin++;
            if (indexMin > nFavorites-1){
              indexMin = 0;
            }
          }
          requestPresetChangeToPreset(favoritePresets[indexMin]);
          delay(100);
          digitalWrite(ledPins[iSwitch], LOW);
        break;                   
      }
      delay(BOUNCEDELAY);
    }
    switchState[iSwitch] = digitalRead( switchPins[iSwitch] );
  }
}

////////// UTILITY FUNCTIONS ////////////////////////////////////////////
void requestExtAmpChanngelChangeToChannel( int channelToChangeTo) { 
  switch( channelToChangeTo ) {  
    case 1:  
      digitalWrite(externalAmpChannelRelayPins[1],HIGH);
      digitalWrite(externalAmpChannelRelayPins[0],LOW);
    break;
    case 2:  
      digitalWrite(externalAmpChannelRelayPins[1],HIGH);
      digitalWrite(externalAmpChannelRelayPins[0],HIGH);  
    break;
    case 3:  
      digitalWrite(externalAmpChannelRelayPins[0],HIGH);    
      digitalWrite(externalAmpChannelRelayPins[1],LOW);
    break;
  }  
  for (int iSwitch=0;iSwitch<nSwitches;iSwitch++){
    if ((buttonFunction[iSwitch] == 101) || (buttonFunction[iSwitch] == 102) || (buttonFunction[iSwitch] == 103)){
      digitalWrite(ledPins[iSwitch], LOW); ledState[iSwitch] = LOW;
    }
    if ((buttonFunction[iSwitch] == 101) && (channelToChangeTo == 1)){
      digitalWrite(ledPins[iSwitch], HIGH); ledState[iSwitch] = HIGH;
    }
    else if ((buttonFunction[iSwitch] == 102) && (channelToChangeTo == 2)){
      digitalWrite(ledPins[iSwitch], HIGH); ledState[iSwitch] = HIGH;
    }
    else if ((buttonFunction[iSwitch] == 103) && (channelToChangeTo == 3)){
      digitalWrite(ledPins[iSwitch], HIGH); ledState[iSwitch] = HIGH;
    }
  }
  externalAmpCurrentChannel = channelToChangeTo;
  updateLcd = true;
}

void requestPresetChangeToPreset(int presetToChangeTo){
  Serial.print("REQUEST PRESET: ");
  Serial.println(presetToChangeTo);

  if (presetToChangeTo < 0) {
    MIDI.sendControlChange(0, 5, MIDICHAN);
    MIDI.sendProgramChange(127, MIDICHAN);    
  }
  else if (presetToChangeTo < 128) {
    MIDI.sendControlChange(0, 0, MIDICHAN);
    MIDI.sendProgramChange(presetToChangeTo, MIDICHAN);
  }
  else if (presetToChangeTo < 256) {
    MIDI.sendControlChange(0, 1, MIDICHAN);
    MIDI.sendProgramChange(presetToChangeTo - 128, MIDICHAN);
  }
  else if (presetToChangeTo < 384) {
    MIDI.sendControlChange(0, 2, MIDICHAN);
    MIDI.sendProgramChange(presetToChangeTo - 256, MIDICHAN);
  }
  else if (presetToChangeTo <  512) {
    MIDI.sendControlChange(0, 3, MIDICHAN);
    MIDI.sendProgramChange(presetToChangeTo - 384, MIDICHAN);
  }
  else if (presetToChangeTo <  640) {
    MIDI.sendControlChange(0, 4, MIDICHAN);
    MIDI.sendProgramChange(presetToChangeTo - 512, MIDICHAN);
  }
  else if (presetToChangeTo < 767) {
    MIDI.sendControlChange(0, 5, MIDICHAN);
    MIDI.sendProgramChange(presetToChangeTo - 640, MIDICHAN);    
  }
  else {
    MIDI.sendControlChange(0, 0, MIDICHAN);
    MIDI.sendProgramChange(0, MIDICHAN);  
  }
  lcd.clear();
  updateLcd = true;
  requestSceneChangeToScene(1);
}

void requestSceneChangeToScene(int sceenToChangeTo) {
  Serial.print("Request Scene: ");
  Serial.println(sceenToChangeTo);
  if (currentScene != sceenToChangeTo){
    MIDI.sendControlChange(SceneSelect_CC, sceenToChangeTo-1, MIDICHAN); //Sometimes we'll just call for the LED update
  }
  
  for (int iSwitch=0; iSwitch<nSwitches; iSwitch++){
    if (buttonFunction[iSwitch]>=1 && buttonFunction[iSwitch]<=8) {// Make sure the button is a scene button
      if (buttonFunction[iSwitch] == sceenToChangeTo){ //Since the first 8 funcitons are the scene changes see 
        digitalWrite(ledPins[iSwitch],HIGH); ledState[iSwitch] = HIGH;
      }
      else {
        digitalWrite(ledPins[iSwitch],LOW); ledState[iSwitch] = LOW;
      }
    }
  }

  if (sceenToChangeTo<3){
    requestExtAmpChanngelChangeToChannel(1);
  }
  else if (sceenToChangeTo<4){
    requestExtAmpChanngelChangeToChannel(2);
  }
  else if (sceenToChangeTo<9){
    requestExtAmpChanngelChangeToChannel(3);
  }

}




////////// MIDI FUNCTIONS ////////////////////////////////////////////
// parse preset number from sysex data
int parseNum(const byte * sysex, int l) {
    int out = 0;
    if (sysex[6] == 0x00) {
        out = int(sysex[7]);
    } else {
        out = int(sysex[7]) + 128 * int(sysex[6]);
    }
    return out;
}

// parse preset name from sysex data
void parseName(const byte * sysex, int l) {
    // reset char array to spaces
    for(byte i = 0x00; i < 0x14; i++) {
        presetName[i] = 0x20;
    }
    // get sysex data into char array presetName
    for(byte i = 0x00; i < 0x14; i++) {
        //char p = sysex[i + 6];
        presetName[i] = sysex[i + 6];
        
    }
}

// callback -  handle sysex
void HandleSysEx(byte *SysExArray, unsigned int size) {

  int sizear = 0;
  if(SysExArray[0]==0xF0) {
    if(printAllMidiMessages){
      Serial.print("With uint8_t scalar: "); PrintHex8(SysExArray,size); Serial.print("\n"); 
    }
    switch (SysExArray[5]) {
      case 0x0F: { // preset name 
        Serial.println("case 0x0F preset name - ");
          const byte *sys = MIDI.getSysExArray();
          sizear = MIDI.getSysExArrayLength();
          parseName(sys,sizear);
          updateLcd = true;
          break;
      }
      case 0x29: { // scene
        Serial.println("case 0x29 scene - ");
        Serial.print("SCENE NUMBER CHNAGE TO: ");
          currentScene = SysExArray[6] + 1;
          Serial.println(currentScene);
          updateLcd = true;
          requestSceneChangeToScene(currentScene);//Update LEDS
          break;
          
      }
      case 0x21: { // MIDI event ACK??
        Serial.println("Case 0x21 MIDI event ACK?? - ");
          currentTime = millis();
          MIDI.sendSysEx(6,RQSTNUM);
          MIDI.sendSysEx(6,RQSTNAME);
          updateLcd = true;
          break;
      }
      
      case 0x14: {  // preset num
        Serial.println("case 0x14 preset num - ");
        const byte *sys = MIDI.getSysExArray();
        sizear = MIDI.getData1();


        int preset = parseNum(sys,sizear);
        if (preset != currentPresetNumber){
            currentPresetNumber = preset;
        }
        MIDI.sendSysEx(6,RQSTNAME);
        delay(50);
        
        updateLcd = true;
        break;
      }
      case 0x0E: { // FX data
        Serial.println("case 0x0E FX data - ");
          const byte *sys = MIDI.getSysExArray();
          sizear = MIDI.getData1();
          break;
      }
      case 0x0D: { // tuner on
        //Grab what time the last update was (will use to turn tuner off after)
        lastTunerUpdate = millis();

        tunerStatus = true;
        updTunerLCD = true;

        //Pasrse the note value
        switch (SysExArray[6]) {
          case 0x00:{
          currentNote[0] = 'A'; currentNote[1] = ' '; break;          }
          case 0x01:{
          currentNote[0] = 'B'; currentNote[1] = 'b'; break;          }
          case 0x02:{
          currentNote[0] = 'B'; currentNote[1] = ' '; break;          }
          case 0x03:{
          currentNote[0] = 'C'; currentNote[1] = ' '; break;          }
          case 0x04:{
          currentNote[0] = 'D'; currentNote[1] = 'b'; break;          }
          case 0x05:{
          currentNote[0] = 'D'; currentNote[1] = ' '; break;          }
          case 0x06:{
          currentNote[0] = 'E'; currentNote[1] = 'b'; break;          }
          case 0x07:{
          currentNote[0] = 'E'; currentNote[1] = ' '; break;          }
          case 0x08:{
          currentNote[0] = 'F'; currentNote[1] = ' '; break;          }
          case 0x09:{
          currentNote[0] = 'G'; currentNote[1] = 'b'; break;          }
          case 0x0A:{
          currentNote[0] = 'G'; currentNote[1] = ' '; break;          }
          case 0x0B:{
          currentNote[0] = 'A'; currentNote[1] = 'b'; break;          }
          default: {
          currentNote[0] = 'X'; currentNote[1] = ' '; break;          }
        }

        //Parse note octave
        switch (SysExArray[7]){
          case 0x00:{
          noteOctave = 1; break;          }
          case 0x01:{
          noteOctave = 2; break;          }
          case 0x02:{
          noteOctave = 3; break;          }
          case 0x03:{
          noteOctave = 4; break;          }
          case 0x04:{
          noteOctave = 5; break;          }
          case 0x05:{
          noteOctave = 6; break;          }
          case 0x06:{
          noteOctave = 6; break;          }
          case 0x07:{
          noteOctave = 8; break;          }
          default: {
           noteOctave = 0; break;          }
        }

        //Parse fine tune
        fineTune = SysExArray[8];
      break;
      }
      case 0x10: { // TEMPO
        unsigned long currentMillis = millis();
        unsigned long measuredTempo = 1/((currentMillis - lastTempoSysExMillis)/1000.0/60.0);
        lastTempoSysExMillis = currentMillis;
        currentTempo = measuredTempo;
        for (int iSwitch=0;iSwitch<nSwitches;iSwitch++){
          if (buttonFunction[iSwitch] == 11){
            digitalWrite(ledPins[iSwitch], HIGH);
            delay(50);
            digitalWrite(ledPins[iSwitch], LOW);
          }
        }
      break;  
      }
    }          
  }
}



void PrintHex8(uint8_t *data, uint8_t length) // prints 8-bit data in hex with leading zeroes
{
  char tmp[16];
   for (int i=0; i<length; i++) { 
     sprintf(tmp, "0x%.2X",data[i]); 
     Serial.print(tmp); Serial.print(" ");
   }
}

void PrintHex16(uint16_t *data, uint8_t length) // prints 16-bit data in hex with leading zeroes
{
  char tmp[16];
  for (int i=0; i<length; i++)
  { 
   sprintf(tmp, "0x%.4X",data[i]); 
   Serial.print(tmp); Serial.print(" ");
  }
}
int getIndexOfMaximumValue(int* array, int size){
 int maxIndex = 0;
 int max = array[maxIndex];
 for (int i=1; i<size; i++){
   if (max<array[i]){
     max = array[i];
     maxIndex = i;
   }
 }
 return maxIndex;
}