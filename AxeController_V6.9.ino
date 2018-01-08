// Axe-FX midi.controller 23-Oct-2016 V6.9
#include <MIDI.h>
#include <LiquidCrystal.h>

#include <SoftwareSerial.h>


#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"


//#include <AxeFX.h>

//MIDI_CREATE_INSTANCE(Type, SerialPort, Name)
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI); 

//Debugging flags
bool printAllMidiMessages = false;

#define LED1    23
#define SWITCH1 25 

#define LED2    27
#define SWITCH2 29

#define LED3    31
#define SWITCH3 33

#define LED4    35
#define SWITCH4 37

#define LED5    39
#define SWITCH5 41

#define LED6    22
#define SWITCH6 24

#define LED7    26
#define SWITCH7 28 

#define LED8    30
#define SWITCH8 32

#define LED9    34
#define SWITCH9 36 

#define LED10    38
#define SWITCH10 40

#define LED11    42
#define SWITCH11 44

#define LED12    46
#define SWITCH12 48


#define LED13    50
#define SWITCH13 52

#define LED14    43
#define SWITCH14 45




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

#define BOUNCEDELAY 75 //was 25ms

/* LCD definition
 * lcd(RS, Enable, D4, D5, D6, D7, BL)
 * KEY pin to analogl pin 0
 */
//LiquidCrystal lcd(8, 13, 9, 4, 5, 6, 7);
const int rs = 3, e = 2, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal   lcd(rs,  e,  d4, d5, d6, d7);
//LiquidCrystal lcd(8,  13, 9,  4,  5,  6, 7);
//LiquidCrystal lcd2(8, 10, 9, 4, 5, 6); //Strange characters on Lcd1 when defining lcd2. Pending debug


Adafruit_7segment matrix = Adafruit_7segment();


// constants
static const unsigned ttt = 50;      // tempo led illumination time (ms)
static const unsigned ledPin = 12;   // tempoLED pin

// Variables: 
const int switchCount = 14;
int switches[switchCount] = { SWITCH1, SWITCH2, SWITCH3,  SWITCH4,  SWITCH5,  SWITCH6,  SWITCH7, 
                              SWITCH8, SWITCH9, SWITCH10, SWITCH11, SWITCH12, SWITCH13, SWITCH14};
int switchState[switchCount] = { LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW}; 
int leds[16] = { LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8, LED9, LED10, LED11, LED12, LED13, LED14};

int currentSwitch = 0;
int pedalActiveFlash = 50; // Delay for flash when pedal is pressed

int bank = 0;
int PresetNumb = 0; //Initial preset number for preset selection
int currentPresetNumber = 0; //Variable for storing current preset
bool tunerStatus = false; // Tuner on/off

int sceneLedCount 		= 3;
int sceneLeds[3] 		= { LED1, LED2, LED3};
int scenesToChangeTo[3] = { 1,    2,    3};

unsigned long tt;      // time tempo sysex pulse detected
char pname[32];
byte pdata[12];
int initial = 0;
int preset = 0;
int currentScene = 1;
int ppreset = 0;
int blk = 0;
int cc = 0;
int byp = 0;
bool updLCD = false;
unsigned long ct;      // call time of FX request in millis
int screenDelayTime = 1500;

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
byte RQSTSCENE[6] = { 0x00, 0x01, 0x74, 0x06, 0x29, 0x2A };

byte GET_FRIMWARE_VERSION[6] = { 0x00, 0x01, 0x74, 0x06, 0x08, 0x0B };

void setup() {
  //Set MIDI baud rate:
  Serial.begin(115200);
  
  Serial.println("Initializing AxeFx Controller");
  //LCD Initial Message
  lcd.clear(); 
  lcd.begin(16, 2);
  lcd.setCursor(0,0); 
  lcd.print("AxeFX Controller"); 

  //Setup MIDI
  MIDI.begin(0);
  MIDI.turnThruOff();
  MIDI.setHandleSystemExclusive(HandleSysEx);

  //Request Number (which will request name)  
  MIDI.sendSysEx(6,RQSTNUM);
  delay(50);

  //Request a scene change so we know what scene it's on. Can't query it through sysex
  MIDI.sendControlChange(SceneSelect_CC, 0, MIDICHAN); 

// Setup Switches and activation LEDs
  for( currentSwitch = 0; currentSwitch < switchCount; currentSwitch++ ) {
//    pinMode( switches[currentSwitch], INPUT_PULLUP);          // Set pin for switch
//    digitalWrite( switches[currentSwitch], HIGH );      // Turn on internal pullup
    pinMode(switches[currentSwitch], INPUT);
    pinMode( leds[currentSwitch], OUTPUT );             // Set pin for LED
  flashPin( leds[currentSwitch], 100 ); // Flash LED
  }

  // 7Seg
  matrix.begin(0x70);  // pass in the address
  for (int i=0; i<=5; i++) {
    matrix.writeDigitNum(i, 0);
    matrix.drawColon(false);
    delay(100);
    matrix.writeDisplay();
  }
  Serial.print("7 Seg Line: ");
  Serial.println(currentPresetNumber);
  matrix.print(currentPresetNumber ,DEC);
  matrix.writeDisplay();

  updLCD = true;
  requestSceneChangeToScene(0);
  
  Serial.println("Finished setup");

}

void loop() {

  MIDI.read();
// update tempo led
//    if ((millis() - tt) > ttt) {
//        digitalWrite(ledPin, LOW);
//       tt = 0; // reset tempo pulse detected time
//    }

  // check if FX block status needs updating
  if (ct > 0 && (ct + 100) < millis()) {
      MIDI.sendSysEx(6,RQSTCC);
      ct = 0;
      updLCD = true;
  }

  // update LCD display
  if (updLCD == true) {
      Serial.println("LCD update");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(pname);
      lcd.setCursor(0,1);
      lcd.print("Prog:");
      lcd.print(preset);
      lcd.setCursor(8,1);
      lcd.print("Scn:");
      lcd.print(currentScene);
      updLCD = false;
      matrix.print(currentPresetNumber ,DEC);
      matrix.writeDisplay();
  }
  
  for( currentSwitch = 0; currentSwitch < switchCount; currentSwitch++ ) {
    if((digitalRead(switches[currentSwitch]) != switchState[currentSwitch] )&&(switchState[currentSwitch] == HIGH)){
      Serial.print("SWITCH PRESSED: ");
      Serial.println(currentSwitch+1);
      switch( currentSwitch ) {
        case 0:          // Switch 1.                            Select preset on switch 1 
          requestSceneChangeToScene(currentSwitch);
  			  Serial.println("Switch-1 ");
        break;
    		case 1:          // Switch 2.                            Select preset on switch 1 
      	  requestSceneChangeToScene(currentSwitch);
  			  Serial.println("Switch-2 ");
        break;
  		  case 2:          // Switch 3.                            Select preset on switch 1 
      	  requestSceneChangeToScene(currentSwitch);
			    Serial.println("Switch-3 ");
        break;
        case 3:          // Switch 4                            Preset down
          currentPresetNumber--;
          requestPresetChangeToPreset(currentPresetNumber, leds[currentSwitch]);
          Serial.println("Switch-4 ");
        break;
        case 4:          // Switch 5                            Preset up
          Serial.print("Preset: "); Serial.println(currentPresetNumber);
          currentPresetNumber++;
          Serial.print("Preset: "); Serial.println(currentPresetNumber);
          requestPresetChangeToPreset(currentPresetNumber, leds[currentSwitch]);
          Serial.println("Switch-5 ");
        break;        
        case 5:
          toggleTuner(currentSwitch);
          Serial.println("Switch-6 ");
        break;
        case 6:
          toggleTuner(currentSwitch);
          Serial.println("Switch-7 ");
        break;
        case 7:
          toggleTuner(currentSwitch);
          Serial.println("Switch-8 ");
        break;   
        case 8:
          toggleTuner(currentSwitch);
          Serial.println("Switch-9 ");
        break;
        case 9:
          toggleTuner(currentSwitch);
          Serial.println("Switch-10 ");
        break;    
        case 10:
          toggleTuner(currentSwitch);
          Serial.println("Switch-11 ");
        break;
        case 11:
          toggleTuner(currentSwitch);
          Serial.println("Switch-12 ");
        break;    
        case 12:
          toggleTuner(currentSwitch);
          Serial.println("Switch-13 ");
        break;
        case 13:
          toggleTuner(currentSwitch);
          Serial.println("Switch-14 ");
        break;            
       }
      delay( BOUNCEDELAY );
      
    }
    switchState[currentSwitch] = digitalRead( switches[currentSwitch] );
  }  
}
       
        
      //         
//         case 0:          // Switch 1.                            Select preset on switch 1 
//         	  requestSceneChangeToScene(currentSwitch);
// 			  Serial.println("Switch-1 ");
//         break;

// Switch 2.                            Select preset on switch 2  
//         case 1:
//           requestSceneChangeToScene(currentSwitch);
//              MIDI.sendProgramChange(PresetNumb+1,MIDICHAN);
//              digitalWrite( LED1, LOW);
//              digitalWrite( LED2, HIGH);
//              digitalWrite( LED3, LOW);
//              digitalWrite( LED4, LOW);
//              digitalWrite( LED5, LOW);
//              lcd.clear();   lcd.begin(16, 2);  lcd.setCursor(0,0); lcd.print(PresetNumb); lcd.print("-");lcd.print(PresetNumb+4);
//              lcd.setCursor(7,0);   lcd.print("Preset "); lcd.print(PresetNumb+1);
//               Serial.println("Switch-2 ");
//         break;

        
// Switch 3.                          Select preset on switch 3 
//         case 2:
//               MIDI.sendProgramChange(PresetNumb+2,MIDICHAN); 
//               digitalWrite( LED1, LOW);
//               digitalWrite( LED2, LOW);
//               digitalWrite( LED3, HIGH);
//               digitalWrite( LED4, LOW);
//               digitalWrite( LED5, LOW);
//               lcd.clear();   lcd.begin(16, 2);  lcd.setCursor(0,0); lcd.print(PresetNumb); lcd.print("-");lcd.print(PresetNumb+4);
//               lcd.setCursor(7,0);   lcd.print("Preset "); lcd.print(PresetNumb+2);
//               Serial.println("Switch-3 ");
//         break;

// Switch 4.                            Select preset on switch 4  
//         case 3:
//               MIDI.sendProgramChange(PresetNumb+3,MIDICHAN);
//               digitalWrite( LED1, LOW);
//               digitalWrite( LED2, LOW);
//               digitalWrite( LED3, LOW);
//               digitalWrite( LED4, HIGH);
//               digitalWrite( LED5, LOW);
//               lcd.clear();   lcd.begin(16, 2);  lcd.setCursor(0,0); lcd.print(PresetNumb); lcd.print("-");lcd.print(PresetNumb+4);
//               lcd.setCursor(7,0);   lcd.print("Preset "); lcd.print(PresetNumb+3);
//               Serial.println("Switch-4 ");
//         break;

// Switch 5.                            Select preset on switch 5
//         case 4:
//               MIDI.sendProgramChange(PresetNumb+4,MIDICHAN);
//               digitalWrite( LED1, LOW);
//               digitalWrite( LED2, LOW);
//               digitalWrite( LED3, LOW);
//               digitalWrite( LED4, LOW);
//               digitalWrite( LED5, HIGH);
//               lcd.clear();   lcd.begin(16, 2);  lcd.setCursor(0,0); lcd.print(PresetNumb); lcd.print("-");lcd.print(PresetNumb+4);
//               lcd.setCursor(7,0);   lcd.print("Preset "); lcd.print(PresetNumb+4);
//               Serial.println("Switch-5 ");
//         break;


        
// Switch 6.                            Scene 1  
//        case 5:
//              MIDI.sendControlChange(SceneSelect_CC, 0, MIDICHAN); 
//              digitalWrite( LED6, HIGH);
//              digitalWrite( LED7, LOW);
//              digitalWrite( LED8, LOW);
//              digitalWrite( LED9, LOW);
//              lcd.setCursor(7,1);   lcd.print("Scene 1");
//              Serial.println("Switch-6 ");
//        break;
        
// Switch 7.                            Scene 2 
//        case 6:
//              MIDI.sendControlChange(SceneSelect_CC, 1, MIDICHAN);
//              digitalWrite( LED6, LOW);
//              digitalWrite( LED7, HIGH);
//              digitalWrite( LED8, LOW);
//              digitalWrite( LED9, LOW);
//              lcd.setCursor(7,1);   lcd.print("Scene 2");
//              Serial.println("Switch-7 ");
//          break;
          
// Switch 8.                            Scene 3          
//        case 7:
//              MIDI.sendControlChange(SceneSelect_CC, 2, MIDICHAN);
//              digitalWrite( LED6, LOW);
//              digitalWrite( LED7, LOW);
//              digitalWrite( LED8, HIGH);
//              digitalWrite( LED9, LOW);
//              lcd.setCursor(7,1);   lcd.print("Scene 3");
//              Serial.println("Switch-8 ");
//        break;

// Switch 9.                            Scene 4            

//        case 8:
//               MIDI.sendControlChange(SceneSelect_CC, 3, MIDICHAN); 
//              digitalWrite( LED6, LOW);
//              digitalWrite( LED7, LOW);
//              digitalWrite( LED8, LOW);
//              digitalWrite( LED9, HIGH);
//              lcd.setCursor(7,1);   lcd.print("Scene 4");
//              Serial.println("Switch-9 ");
//          break;

// Switch 10.                         Bank Down
//        case 9:  
//         //PresetNumb=PresetNumb-95;
//         if (PresetNumb<5) PresetNumb=95; else if (PresetNumb=PresetNumb-5);
//         flashPin( leds[currentSwitch], pedalActiveFlash );
//         lcd.clear();lcd.setCursor(0,0); lcd.print(PresetNumb); lcd.print("-");lcd.print(PresetNumb+4);
//         Serial.println("Switch-10 ");
//          break;

// Switch 11.                         Loop Record
//        case 10:
//          MIDI.sendControlChange(LooperRecord_CC, 0, MIDICHAN);
//          flashPin( leds[currentSwitch], pedalActiveFlash );
//          lcd.setCursor(0,2); lcd.print("                 ");
//          lcd.setCursor(0,2); lcd.print("Loop RECORD");
//           Serial.println("Switch-11 ");
//          break;

// Switch 12.                         Loop Play      
//        case 11:
//        MIDI.sendControlChange(LooperPlay_CC, 0, MIDICHAN);
//        flashPin( leds[currentSwitch], pedalActiveFlash );
//        lcd.setCursor(0,2); lcd.print("                 ");
//        lcd.setCursor(0,2); lcd.print("Loop PLAY");
//         Serial.println("Switch-12 ");
//        break;

// Switch 13.                         Loop Dub      
//        case 12:
//        MIDI.sendControlChange(LooperDub_CC, 0, MIDICHAN);
//        flashPin( leds[currentSwitch], pedalActiveFlash );
//        lcd.setCursor(0,2); lcd.print("                 ");
//        lcd.setCursor(0,2); lcd.print("Loop DUB");
//         Serial.println("Switch-13 ");
//        break;

// Switch 14.                       Loop Bypass        
//        case 13:
//        MIDI.sendControlChange(LooperBypass_CC, 0, MIDICHAN);
//        flashPin( leds[currentSwitch], pedalActiveFlash );
//        lcd.setCursor(0,2); lcd.print("                 ");
//        lcd.setCursor(0,2); lcd.print("Loop BYPASS");
//         Serial.println("Switch-14 ");
//        break;

// Switch 15.                       Bank UP   
//        case 14:
//         if (PresetNumb>94) PresetNumb=0; else if (PresetNumb=PresetNumb+5);
//         flashPin( leds[currentSwitch], pedalActiveFlash );
//         lcd.clear(); lcd.setCursor(0,0); lcd.print(PresetNumb); lcd.print("-");lcd.print(PresetNumb+4);
//          Serial.println("Switch-15 ");
//          break;

// Switch 16.        
//        case 15:
//
//        flashPin( leds[currentSwitch], pedalActiveFlash );
//         Serial.println("Switch-16 ");
//        break;
//  

////////// UTILITY FUNCTIONS ////////////////////////////////////////////
void requestPresetChangeToPreset(int presetToChangeTo, int ledToFlash){
  MIDI.sendControlChange(0,2,MIDICHAN);
  Serial.println("BANK B");
  MIDI.sendProgramChange(2,MIDICHAN);
//  MIDI.sendProgramChange(presetToChangeTo-127,MIDICHAN);  
  currentPresetNumber;
  digitalWrite(ledToFlash,HIGH);
  delay(500);
  digitalWrite(ledToFlash,LOW);
  requestSceneChangeToScene(0);
}

void requestSceneChangeToScene(int switchNumber) {
	currentScene = scenesToChangeTo[switchNumber] - 1;
	MIDI.sendControlChange(SceneSelect_CC, currentScene, MIDICHAN); 
	
	for( int i = 0; i <= sceneLedCount; i++ ) {
		digitalWrite(sceneLeds[i],LOW);
	}
	digitalWrite(sceneLeds[switchNumber],HIGH);
	lcd.setCursor(7,1);   lcd.print("Scene Change");
}

void flashPin( int ledPin, int flashDelay ) {
  digitalWrite( ledPin, HIGH );
  delay( flashDelay );
  digitalWrite( ledPin, LOW );
}

void toggleTuner(int tunerSwitchNumber){
    if (tunerStatus == false)
    {
      MIDI.sendControlChange(Tuner_CC,127,MIDICHAN);
      tunerStatus = true;
      digitalWrite(leds[tunerSwitchNumber],HIGH);
      lcd.clear();
      lcd.write("Tuner ON");
    }
    else
    {
      tunerStatus = false;
      MIDI.sendControlChange(Tuner_CC,0,MIDICHAN);
      digitalWrite(leds[tunerSwitchNumber],LOW);
      updLCD = true;
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
        pname[i] = 0x20;
    }
    // get sysex data into char array pname
    for(byte i = 0x00; i < 0x14; i++) {
        //char p = sysex[i + 6];
        pname[i] = sysex[i + 6];
        
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
                updLCD = true;
                break;
            }
            case 0x29: { // scene
              Serial.println("case 0x29 scene - ");
                currentScene = SysExArray[6] + 1;
                updLCD = true;

                break;
                
            }
            case 0x21: { // MIDI event ACK??
              Serial.println("Case 0x21 MIDI event ACK?? - ");
                ct = millis();
                MIDI.sendSysEx(6,RQSTNUM);
                MIDI.sendSysEx(6,RQSTNAME);
                updLCD = true;
                break;
            }
            
            case 0x14: {  // preset num
              Serial.println("case 0x14 preset num - ");
                const byte *sys = MIDI.getSysExArray();
                sizear = MIDI.getData1();


                preset = parseNum(sys,sizear);
                if (preset != currentPresetNumber){
                    currentPresetNumber = preset;
                    //Reqeuest change to scene 1
                    MIDI.sendControlChange(SceneSelect_CC, 0, MIDICHAN); 

                    //Get updated name
                    MIDI.sendSysEx(6,RQSTNAME);
                    delay(50);
                }

                

                updLCD = true;
                break;
              
            }

           
            case 0x0E: { // FX data
              Serial.println("case 0x0E FX data - ");
                const byte *sys = MIDI.getSysExArray();
                sizear = MIDI.getData1();
                break;
            }
            
//            case 0x10: { // tempo
//                tt = millis();
//                digitalWrite(ledPin, HIGH);
//Serial.print("case 0x10 Tempo - ");Serial.println(pname);
//                break;
//            }
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

