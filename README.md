# Axe Fx II - Arduinon Controller
This code is largely based on the excellent work from:
https://forum.fractalaudio.com/threads/diy-axe-fx-foot-controller-for-50-open-project.119882/page-3

The initital starting point can be found:
https://www.dropbox.com/s/01bhe11yddlfffg/AxeController_V6.9.ino?dl=0

# Installation:
Need to also install Adafruit LED Backpack Libaries and MIDI
(By install, I downloaded the zips from git hub and put them in ~/Documents/Arduino/libraries)
* https://github.com/adafruit/Adafruit_LED_Backpack
* https://github.com/adafruit/Adafruit-GFX-Library
* https://github.com/FortySevenEffects/arduino_midi_library/ (I installed 4.3.1)
* https://playground.arduino.cc/uploads/Code/Array.zip

Note: When compiling need to have the correct board "Arduino/Genuino Mega or Mega 2560"!!

#Button funciton
This program was written so that you could easily assign buttons to differnet funciton. In order to keep the coding simple the following list of numbers corresponding to the different function cababilty was used:
*  101 - extAmpSwitchingCh1  
*  102 - extAmpSwitchingCh2
*  103 - extAmpSwitchingCh3
*  104 - extAmpSwitchingSolo
*  105 - extAmpSwitchingFxLoop
*    1 - Scene 01
*    2 - Scene 02
*    3 - Scene 03
*    4 - Scene 04
*    5 - Scene 05
*    6 - Scene 06
*    7 - Scene 07
*    8 - Scene 08
*    9 - Preset Up
*   10 - Preset Down
*   11 - Tap Tempo // little flakey and needs some work
*   12 - Tuner 
*   13 - Favorites
*   14 - LooperRecord
*   15 - LooperPlay
*   16 - LooperOnce
*   17 - LooperDub
*   18 - LooperRev
*   19 - LooperBypass
*   20 - LooperHalf
*   21 - LooperUndo

Each switch's behavior is programmed in the int array: buttonFunction