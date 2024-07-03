/*------------------------------------------------------------------------------*/
//Author:Alperen Ekinci -> https://github.com/AlperenEkinciDev
//2024 Hacettepe University Term Project I, RStick prototype driver
/*------------------------------------------------------------------------------*/

#include<SoftwareSerial.h>
#include <stdio.h>
#include <Wire.h>  // Wire library - used for I2C communication

SoftwareSerial BTSerial(10,11);//BT ConnectionPins

int ADXL345_Bottom = 0x53; // The ADXL345_Bottom sensor I2C address
int ADXL345_Top = 0x1D; // The ADXL345_Top sensor I2C address

float XBottom, YBottom, ZBottom;
float XBottom_OFFSET, YBottom_OFFSET, ZBottom_OFFSET = 0;// Offset values -> Bottom ADXL345
float XTop, YTop, ZTop;
float XTop_OFFSET, YTop_OFFSET, ZTop_OFFSET = 0;// Offset values -> Top ADXL345
float bottomScaleFactor = 0.9524;//Accelerometer correction -> Bottom ADXL345
float topScaleFacTor = 0.8547;//Accelerometer correction -> Top ADXL345
float offsetMultiplier = 1;
float actionState = 0;
float indexState = 0;
float middleState = 0;
float ringState = 0;
float pinkyState = 0;

float oldAcc[6] = {0, 0, 0, 0 , 0 ,0};
float delta[6] = {0, 0, 0, 0 , 0 ,0};

int zeroingPin = 2; 
int actionPin = 3; 

int indexPin = 9; 
int middlePin = 10; 
int ringPin = 11; 
int pinkyPin = 12; 

float roll,pitch,XRot,ZRot = 0;

void setup() {
  Serial.begin(9600); // Initiate serial communication for printing the results on the Serial monitor
  Wire.begin(); // Initiate the Wire library



  /*------------------------------------------------------------------------------*/
  // Set ADXL345_Bottom in measuring mode
  Wire.beginTransmission(ADXL345_Bottom); // Start communicating with the device 
  Wire.write(0x2D); // Access/talk to POWER_CTL Register - 0x2D
  // Enable measurement
  Wire.write(8); // (8dec -> 0000 1000 binary) Bit D3 High for measuring enable 
  Wire.endTransmission();
  Wire.beginTransmission(ADXL345_Bottom); // Start communicating with the device 
  Wire.write(0x31); // Access/talk to DATA_FORMAT Register - 0x31
  Wire.write(1); // -+4g Resolution
  Wire.endTransmission();
  /*------------------------------------------------------------------------------*/


  
  /*------------------------------------------------------------------------------*/
  // Set ADXL345_Top in measuring mode
  Wire.beginTransmission(ADXL345_Top); // Start communicating with the device 
  Wire.write(0x2D); // Access/talk to POWER_CTL Register - 0x2D
  // Enable measurement
  Wire.write(8); // (8dec -> 0000 1000 binary) Bit D3 High for measuring enable 
  Wire.endTransmission();
  Wire.beginTransmission(ADXL345_Top); // Start communicating with the device 
  Wire.write(0x31); // Access/talk to DATA_FORMAT Register - 0x31
  Wire.write(1); // -+4g Resolution
  Wire.endTransmission();
  /*------------------------------------------------------------------------------*/


  /*------------------------------------------------------------------------------*/
  //SetUp Related Utility Buttons
  pinMode(zeroingPin, INPUT);
  pinMode(actionPin, INPUT);
  pinMode(indexPin, INPUT);
  pinMode(middlePin, INPUT);
  pinMode(ringPin, INPUT);
  pinMode(pinkyPin, INPUT);
  /*------------------------------------------------------------------------------*/



  /*------------------------------------------------------------------------------*/
  //SetUp Blutooth -> HC05 Module
  Serial.begin(9600);
  BTSerial.begin(9600);
  /*------------------------------------------------------------------------------*/

  delay(100);
}

void loop() {

  updateVectors();
  if(digitalRead(zeroingPin) == HIGH){setZeroingOffset();} else{offsetMultiplier = 1;} // User input flat offset value
  calculateDelta();
  if(digitalRead(actionPin) == HIGH){actionState = 1;}else{actionState = 0;}//Action Buttons
  if(digitalRead(indexPin) == HIGH){indexState = 1;}else{indexState = 0;}
  if(digitalRead(middlePin) == HIGH){middleState = 1;}else{middleState = 0;}
  if(digitalRead(ringPin) == HIGH){ringState = 1;}else{ringState = 0;}
  if(digitalRead(pinkyPin) == HIGH){pinkyState = 1;}else{pinkyState = 0;}


  //Form Serial Output String
  String outData = "";
  for (int i = 0; i < 6; i++) {
    outData += oldAcc[i];
    outData += " ";
  }
  outData += offsetMultiplier;
  outData += " ";
  outData += actionState;
  outData += " ";
  outData += indexState;
  outData += " ";
  outData += middleState;
  outData += " ";
  outData += ringState;
  outData += " ";
  outData += pinkyState;


  //Send to both Serial outputs
  BTSerial.println(outData);
  Serial.println(outData);

  delay(5);
}

void setZeroingOffset(){
  if(abs(offsetMultiplier) <= 1e-7f){
    XBottom_OFFSET = XBottom;
    YBottom_OFFSET = YBottom;
    ZBottom_OFFSET = ZBottom;
    
    XTop_OFFSET = XTop;
    YTop_OFFSET = YTop;
    ZTop_OFFSET = ZTop;
  }
  else{
    offsetMultiplier = 0;
  }
}

//Delta values are unsent but avaliable
float * calculateDelta(){ //Returns {Bottom(Z, Y, X), Top(Z,Y,X)}. Swapped because prototype orientation

  delta[0] = oldAcc[0] - ZBottom;
  delta[1] = oldAcc[1] - XBottom;
  delta[2] = oldAcc[2] - YBottom;
  
  delta[3] = oldAcc[3] - ZTop;
  delta[4] = oldAcc[4] - XTop;
  delta[5] = oldAcc[5] - YTop;
  
  oldAcc[0] =  ZBottom;
  oldAcc[1] =  XBottom;
  oldAcc[2] =  YBottom;
  
  oldAcc[3] = ZTop;
  oldAcc[4] = XTop;
  oldAcc[5] = YTop;

  return delta;
}

void updateVectors(){

 /*------------------------------------------------------------------------------*/
  // === Read ADXL_Bottom data === //
  Wire.beginTransmission(ADXL345_Bottom);
  Wire.write(0x32); // Start with register 0x32 (ACCEL_XOUT_H)
  Wire.endTransmission(true);
  Wire.requestFrom(ADXL345_Bottom, 6, true); // Read 6 registers total, each axis value is stored in 2 registers
  XBottom = ( Wire.read()| Wire.read() << 8);
  XBottom = (XBottom/128) * bottomScaleFactor - XBottom_OFFSET * offsetMultiplier; //For a range of +-4g, we need to divide the raw values by 128, according to the datasheet
  YBottom = ( Wire.read()| Wire.read() << 8);
  YBottom = (YBottom/128) * bottomScaleFactor - YBottom_OFFSET * offsetMultiplier;
  ZBottom = ( Wire.read()| Wire.read() << 8);
  ZBottom = (ZBottom/128) * bottomScaleFactor - ZBottom_OFFSET * offsetMultiplier;
  /*------------------------------------------------------------------------------*/
  
  /*------------------------------------------------------------------------------*/
  // === Read ADXL_Top data === //
  Wire.beginTransmission(ADXL345_Top);//X-Y Switched
  Wire.write(0x32);
  Wire.endTransmission(true);
  Wire.requestFrom(ADXL345_Top, 6, true);
  XTop = ( Wire.read()| Wire.read() << 8);
  XTop = (YTop/128)  - YTop_OFFSET * offsetMultiplier;
  YTop = ( Wire.read()| Wire.read() << 8);
  YTop = (XTop/128) * topScaleFacTor - XTop_OFFSET * offsetMultiplier;
  ZTop = ( Wire.read()| Wire.read() << 8);
  ZTop = (ZTop/128) * topScaleFacTor - ZTop_OFFSET * offsetMultiplier;
  /*------------------------------------------------------------------------------*/
  
}