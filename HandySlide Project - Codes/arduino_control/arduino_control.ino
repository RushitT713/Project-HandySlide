// Arduino Code - MAIN
#include <Wire.h>
#include <SoftwareSerial.h>

// Define the Bluetooth TX and RX pins
#define BT_TX 2
#define BT_RX 3

// Define Bluetooth object
SoftwareSerial BTSerial(BT_TX, BT_RX);

const int MPU_addr = 0x68; // I2C address of the MPU-6050
int16_t AcX, AcY, AcZ; // Accelerometer values
double angle_x, angle_y; // Calculated angles

const int buttonPin = 5; // Button pin
int buttonState = 0; // Button state

void setup() {
  pinMode(buttonPin, INPUT);
  Wire.begin(); // Initialize I2C communication
  Wire.beginTransmission(MPU_addr); // Start communication with MPU6050
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // Set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(9600); // Start serial communication at 9600 baud rate
  BTSerial.begin(9600); // Initialize Bluetooth communication
}

void calculateAngles() {
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B); // Starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 6, true); // Request 6 registers (Accel X,Y,Z)
  
  AcX = Wire.read() << 8 | Wire.read(); // 16-bit values
  AcY = Wire.read() << 8 | Wire.read();
  AcZ = Wire.read() << 8 | Wire.read();

  angle_x = atan2(AcY, AcZ) * 180 / PI;
  angle_y = atan2(AcX, AcZ) * 180 / PI;
}

void loop() {
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {
    calculateAngles(); // Calculate the current angles

    // Adjust the control logic based on the hand orientation and the desired actions
    if (angle_y > 30) { // Tilt hand backward (upwards)
      BTSerial.println("Next Slide");
    } else if (angle_y < -30) { // Tilt hand forward (downwards)
      BTSerial.println("Previous Slide");
    } else if (angle_x > 30) { // Tilt hand to the right
      BTSerial.println("End Slideshow");
    } else if (angle_x < -30) { // Tilt hand to the left
      BTSerial.println("Start Slideshow");
    }

    delay(400); // Delay to avoid too frequent reads
  } else {
    BTSerial.println("Button Released!!!");
    delay(400);
  }
}

/*
    if (angle_y > 30) { // Tilt hand backward (upwards)
      BTSerial.println("Start Slideshow");
    } else if (angle_y < -30) { // Tilt hand forward (downwards)
      BTSerial.println("End Slideshow");
    } else if (angle_x > 30) { // Tilt hand to the right
      BTSerial.println("Next Slide");
    } else if (angle_x < -30) { // Tilt hand to the left
      BTSerial.println("Previous Slide");
    }
*/

// MPU6050 Sensor Data on Bluetooth HC - 06
/*
#include <Wire.h>
#include <SoftwareSerial.h>

#define BT_TX 2
#define BT_RX 3

SoftwareSerial BTSerial(BT_TX, BT_RX);

const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

int minVal=265;
int maxVal=402;

double x;
double y;
double z;
 
void setup(){
Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(9600);
  BTSerial.begin(9600);
}
void loop(){
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);
  AcX=Wire.read()<<8|Wire.read();
  AcY=Wire.read()<<8|Wire.read();
  AcZ=Wire.read()<<8|Wire.read();
  int xAng = map(AcX,minVal,maxVal,-90,90);
  int yAng = map(AcY,minVal,maxVal,-90,90);
  int zAng = map(AcZ,minVal,maxVal,-90,90);
  
  x= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
  y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
  z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);
  
  BTSerial.print("AngleX= ");
  BTSerial.println(x);
  
  BTSerial.print("AngleY= ");
  BTSerial.println(y);
  
  BTSerial.print("AngleZ= ");
  BTSerial.println(z);
  BTSerial.println("-----------------------------------------");

  delay(400);
}
*/