/***************************************************
 This is a library for the Multi-Touch Kit
 Designed and tested to work with Arduino Uno, MEGA2560, LilyPad(ATmega 328P)
 Note: Please remind to disconnect AREF pin from AVCC on Lilypad
 
 For details on using this library see the tutorial at:
 ----> https://hci.cs.uni-saarland.de/multi-touch-kit/
 
 Written by Narjes Pourjafarian, Jan Dickmann, Juergen Steimle (Saarland University), 
            Anusha Withana (University of Sydney), Joe Paradiso (MIT)
 MIT license, all text above must be included in any redistribution
 ****************************************************/

 // This example shows how to use the Multi-Touch Kit library with an Arduino Uno/LilyPad and a 6x6 sensor
 // Connect pin 3 on the Uno and pin 9 on the Mega to the Signal pin of the multiplexer
 // Note: Please remind to disconnect AREF pin from AVCC on Lilypad

#include <MultiTouchKit.h>
#include <ezButton.h>

//----- Multiplexer input pins (for UNO) -----
int s0 = 7;
int s1 = 8;
int s2 = 9;
int s3 = 10;

int muxPins[4] = {s3, s2, s1, s0};

//----- Number of receiver (RX) and transmitter (TX) lines -----
int RX_num = 4;
int TX_num = 5;

//----- Receive raw capacitance data or touch up/down states -----
boolean raw_data = true;  // true: receive raw capacitance data, false: receive touch up/down states
int threshold = 1;  // Threshold for detecting touch down state (only required if raw_data = false). 
                    // Change this variable based on your sensor. (for more info. check the tutorial)


// Button DEFINITION
bool isRunning = false;
#define BUTTON_PIN 4
#define DEBOUNCETIME 50
ezButton button(BUTTON_PIN);

// LED DEFINITION
#define LED_PIN 5


//COUNTER
int counter = 0;

MultiTouchKit mtk;

void setup() {
  //Serial connection, make sure to use the same baud rate in the processing sketch
  Serial.begin(115200);

  //setup the Sensor
  mtk.setup_sensor(RX_num,TX_num,muxPins,raw_data,threshold);

  //Set Pin for Button with internal Pullup resistor
  //Set debouncetime to 50 ms
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  button.setDebounceTime(DEBOUNCETIME);

  //Set Pin for LED
  pinMode(LED_PIN, OUTPUT);


}

void loop() {
  button.loop();

// Change running-state on button press
// Output Counter at start and end of a run
  if(button.isPressed()){
    if(isRunning){
        /*
        Serial.print(counter);
        Serial.println(" Ende");
        */
        counter++;
    }
    /*
    else{
        Serial.print(counter);
        Serial.println(" Start");
    }
    */
    isRunning = !isRunning;
    
  }

// Write MTK Data to serial monitor and turn LED on if running-state==true
// Else turn LED off
  if (isRunning) {
    digitalWrite(LED_PIN, HIGH);
    mtk.read(counter);
    //Serial.println("Running");
  }
  else {
    digitalWrite(LED_PIN, LOW);
    //Serial.println("Not Running");
  }
}
