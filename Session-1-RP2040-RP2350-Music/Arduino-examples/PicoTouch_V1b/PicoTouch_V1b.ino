//PicoTouch MIDI controller


#include <Adafruit_TinyUSB.h> // Set USB Stack to Adafruit TinyUSB in Tools menu
#include <MIDI.h>             // Include MIDI Library.  Use Library manager to download it
#include <Control_Surface.h>  //Include the Control Surface library.  Use Library manager to download it

// Create a filtered analog object on pin A0:
FilteredAnalog<12,      // Output precision in bits
               8,       // The amount of filtering
               uint32_t // The integer type for the calculations
               >
  analog0 = A0;


// Create a filtered analog object on pin A0:
FilteredAnalog<12,      // Output precision in bits
               8,       // The amount of filtering
               uint32_t // The integer type for the calculations
               >
  analog1 = A1;



// Create a filtered analog object on pin A0:
FilteredAnalog<12,      // Output precision in bits
               8,       // The amount of filtering
               uint32_t // The integer type for the calculations
               >
  analog2 = A2;


#include "TouchyTouch.h" //Include the TouchyTouch library. Use Library manager to download it

const u_int8_t touch_pins[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22 };  //GPIO pin numbering
u_int8_t touch_velocity[] = { 100,100,100,100,100,100,100,100,100,100,100,100,100,100, 100,100,100,100,100,100,100}; // MIDI velocity values when touched
int touch_threshold[]={ 1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000, 1000,1000,1000,1000,1000,1000,1000}; //Threshold values of touch pins

const int touch_count = sizeof(touch_pins) / sizeof(int);

TouchyTouch touches[touch_count];

// USB MIDI object
Adafruit_USBD_MIDI usb_midi;

// Create a new instance of the Arduino MIDI Library,
// and attach usb_midi as the transport.
MIDI_CREATE_INSTANCE(Adafruit_USBD_MIDI, usb_midi, usbMIDI);
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

const uint16_t pentatonicTable[54] = { 0,1,3,6,8,10,13,15,18,20,22,25,27,30,32,34,37,39,42,44,46,49,51,54,56,58,61,63,66,68,70,73,75,78,80,82,85,87,90,92,94,97,99,102,104,106,109,111,114,116,118,121,123,126 };

u_int8_t midiChannelA = 1;  //The channel we send MIDI messages to
u_int8_t midiChannelB = 2;  //The channel we send MIDI messages to

const u_int8_t controlChannel = 16; //The MIDI channel we are listing on for commands

u_int8_t controlNo1 = 10; // CC number controller 1
u_int8_t controlNo2 = 11; // CC number controller 2
u_int8_t controlNo3 = 12; // CC number controller 3

u_int8_t cctNo = 14; // CC number of touch value

u_int8_t transpose = 24;  //Number of notes to transpose up

u_int8_t scale = 0 ; //Defaults to chromatic ( 0), 1 = pentatonic

u_int8_t split = 127;

bool enablePot0 = false; // Enable/disable analog 0
bool enablePot1 = false; // Enable/disable analog 1
bool enablePot2 = false; // Enable/disable analog 2

bool aftEnable = true; // Enable/disable aftertouch
bool cctEnable = true; // Enable/disable control change touch
bool noteEnable = true; // Enable/disable note beeing played at touch

bool calibrated = 0; //Callibration flag

u_int8_t channel,note,lastAftertouch;

bool debug = false;  //Enable/disable serial port debuging info

void setup() {

  if(debug){
  Serial.begin(115200);
  Serial.println("PicoTouch");
  }

  setupAnalogFilters();
  setMidiHandlers();

  pinMode(LED_BUILTIN, OUTPUT);

  startTouch();

  delay(2000);
  doCalibrate();
  calibrated = 1;
  
}

void loop() {
  if(BOOTSEL) doCalibrate();

  checkAnalogPorts();
  checkTouch();

  MIDI.read(); // read any incoming MIDI messages on hardware serial port
  usbMIDI.read(); // read any incoming MIDI messages on usb port

  delay(5);
}


