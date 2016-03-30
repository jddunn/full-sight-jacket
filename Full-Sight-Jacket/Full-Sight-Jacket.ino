//  Software for the Full-Sight Jacket
//  By: Johnny Dunn
 
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define leftPIN            11
#define leftNUMPIXELS      16
#define rightPIN           9
#define rightNUMPIXELS     16

Adafruit_NeoPixel leftpixels = Adafruit_NeoPixel(leftNUMPIXELS, leftPIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel rightpixels = Adafruit_NeoPixel(rightNUMPIXELS, rightPIN, NEO_GRB + NEO_KHZ800);

int delayval = 500; // delay for half a second

 
int ledPin = 13;                // choose the pin for the LED
int leftInputPin = 3;               // choose the input pin (for PIR sensor)
int rightInputPin = 5;
int leftPIRState = LOW;             // we start, assuming no motion detected
int rightPIRState = LOW;
int leftPIRVal = 0;                    // variable for reading the pin status
int rightPIRVal = 0;
bool leftMotionDetected = false;
bool rightMotionDetected = false;

void setup() {
 
  Serial.begin(9600);
  #if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code
  leftpixels.begin(); // This initializes the NeoPixel library.
  rightpixels.begin();
}

void showPixels() {
  
  if (rightMotionDetected == true) {
    for (int i=0; i < rightNUMPIXELS; i++) {
      rightpixels.setPixelColor(i, rightpixels.Color(0,150,0)); // Moderately bright green color.
      rightpixels.show(); // This sends the updated pixel color to the hardware.
    }
  } else {
    if (rightMotionDetected == false) {
      for (int i = 0; i <rightNUMPIXELS; i++) {
        rightpixels.setPixelColor(i, leftpixels.Color(0, 0, 0));
        rightpixels.show();
      }
    }
  }
  
  if (leftMotionDetected == true) {
    for(int i=0;i<leftNUMPIXELS;i++){
      // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
      leftpixels.setPixelColor(i, leftpixels.Color(0,150,0)); // Moderately bright green color.
      leftpixels.show(); // This sends the updated pixel color to the hardware.
    }
  } else {
    if (leftMotionDetected == false) {
      for (int i = 0; i <leftNUMPIXELS; i++) {
        leftpixels.setPixelColor(i, leftpixels.Color(0, 0, 0));
        leftpixels.show();
      }
    }
  }
}
  
 
void loop(){
//  Code below is for when the voltage is only 3.3V, but it's very unreliable, so stick with 5V if you can
//  int sensorValue = analogRead(A5);
//  float voltage = sensorValue * (5.0 / 1023.0);
//  Serial.println("Voltage:  ");
//  Serial.print(voltage);
//  delay(500);
//  if (voltage <= 4.79) {
//    motionDetected = true;
//    if (motionDetected == true) {
//      Serial.println("Motion detected!");
//      delay(1000);
//      Serial.println("Motion ended!");
//      motionDetected = false;
//    }
//  }
//  
  showPixels();
  leftPIRVal = digitalRead(leftInputPin);  // read input value
  rightPIRVal = digitalRead(rightInputPin);

  if (leftPIRVal == HIGH) {            // check if the input is HIGH
    leftMotionDetected = true;
    if (leftPIRState == LOW) {
      
      // we have just turned on
      Serial.println("Left motion detected!");
      // We only want to print on the output change, not state
      leftPIRState = HIGH;
      delay(1000);
      leftMotionDetected = false;
    }
  } else {
    if (leftPIRState == HIGH){
      // we have just turned of
      Serial.println("Left motion reset!");
      // We only want to print on the output change, not state
      leftPIRState = LOW;
      leftMotionDetected = false;
    }
  }
  
  if (rightPIRVal == HIGH) {            // check if the input is HIGH
    rightMotionDetected = true;
    if (rightPIRState == LOW) {
      // we have just turned on
      Serial.println("Right motion detected!");
      // We only want to print on the output change, not state
      rightPIRState = HIGH;
      delay(1000);
      rightMotionDetected = false;
    }
  } else {
    if (rightPIRState == HIGH){
      // we have just turned of
      Serial.println("Right motion reset!");
      // We only want to print on the output change, not state
      rightPIRState = LOW;
      rightMotionDetected = false;
    }
  }
}
