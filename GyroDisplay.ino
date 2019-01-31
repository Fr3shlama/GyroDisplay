#include <Adafruit_GFX.h>  
#include <Adafruit_SSD1306.h>
#include<Wire.h>

Adafruit_SSD1306 display;

const int MPU6050_addr=0x68;
int16_t AccX,AccY,AccZ,Temp,GyroX,GyroY,GyroZ;
long MiddleX, MiddleY, MiddleZ;
int i = 0;

void setup() 
{                
  delay(100);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setRotation(0);
  display.setTextWrap(false);
  display.dim(0);  //Set brightness (0 is maximun and 1 is a little dim)

  Wire.begin();
  Wire.beginTransmission(MPU6050_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
}  

void loop(){
  Wire.beginTransmission(MPU6050_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_addr,14,true);
  
  AccX=Wire.read()<<8|Wire.read();
  AccY=Wire.read()<<8|Wire.read();
  AccZ=Wire.read()<<8|Wire.read();
  Temp=Wire.read()<<8|Wire.read();
  GyroX=Wire.read()<<8|Wire.read();
  GyroY=Wire.read()<<8|Wire.read();
  GyroZ=Wire.read()<<8|Wire.read();

  MiddleX = MiddleX + GyroX;
  MiddleY = MiddleY + GyroY;
  MiddleZ = MiddleZ + GyroZ;
  
  if (i == 200){
    MiddleX = MiddleX / 200;
    MiddleY = MiddleY / 200;
    MiddleZ = MiddleZ / 200;
    delay(50);
    display.clearDisplay();
    display.setTextSize(1); 
    display.setCursor(0, 10);
    display.print("X:"); display.print(MiddleX); display.print("  ");
    display.print("Y:"); display.print(MiddleY); display.print("  ");
    display.print("Z:"); display.print(MiddleZ); display.print("  ");
    display.display();
    i = MiddleX = MiddleY = MiddleZ = 0;
  }
  else Serial.println(i);
  i++;
  delay(1);

}
