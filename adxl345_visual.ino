#include <Wire.h>  

int ADXL345 = 0x53; 
float X_out, Y_out, Z_out;  // Outputs
float roll,pitch,rollF,pitchF=0;

void setup()
{
  Serial.begin(9600); 
 
  Wire.begin();
  Wire.beginTransmission(ADXL345); 
  Wire.write(0x2D); 
  Wire.write(8);
  Wire.endTransmission();
  delay(10);

  //Off-set Calibration
  //X-axis
  Wire.beginTransmission(ADXL345);
  Wire.write(0x1E);
  Wire.write(1);
  Wire.endTransmission();
  delay(10);
  //Y-axis
  Wire.beginTransmission(ADXL345);
  Wire.write(0x1F);
  Wire.write(-2);
  Wire.endTransmission();
  delay(10);

  //Z-axis
  Wire.beginTransmission(ADXL345);
  Wire.write(0x20);
  Wire.write(-9);
  Wire.endTransmission();
  delay(10);
}

void loop()
{
  //Read acceleromter data 
  Wire.beginTransmission(ADXL345);
  Wire.write(0x32); 
  Wire.endTransmission(false);
  Wire.requestFrom(ADXL345, 6, true); 
  X_out = ( Wire.read() | Wire.read() << 8); // X-axis value
  X_out = X_out / 256; 
  Y_out = ( Wire.read() | Wire.read() << 8); // Y-axis value
  Y_out = Y_out / 256;
  Z_out = ( Wire.read() | Wire.read() << 8); // Z-axis value
  Z_out = Z_out / 256;

  
  roll = atan(Y_out / sqrt(pow(X_out, 2) + pow(Z_out, 2))) * 180 / PI;
  pitch = atan(-1 * X_out / sqrt(pow(Y_out, 2) + pow(Z_out, 2))) * 180 / PI;

 
  rollF = 0.94 * rollF + 0.06 * roll;
  pitchF = 0.94 * pitchF + 0.06 * pitch;

  Serial.print(rollF);
  Serial.print("/");
  Serial.println(pitchF);
}
