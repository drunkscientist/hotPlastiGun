#include <Arduino.h>
#include <U8g2lib.h>
#include <AccelStepper.h>



#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R2, /* reset=*/ U8X8_PIN_NONE);


const int step = 8;
const int dir = 9;
AccelStepper extruder(1, step, dir);

const int ThermPin = 0;
const int stepEnPin = 10;
const int fetPin = 7;
const int switchButt = 11;
const int heaterSwtch = 5;
int heatSetting = 100;

bool heatMode;

int Vo;
const float R1 = 4700;
float logR2, R2, T;
//float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07; //10k ntc thermisistor, works with salvage
//float c1 = 1.125308852122e-03, c2 = 2.34711863267e-04, c3 = 8.5663516e-07; //100k?
//float c1 = 1.484778004e-03, c2 = 2.348962910e-04, c3 = 1.006037158e-07;  // Steinhart-Hart and Hart Coefficients
const float c1 = 0.8269846691e-03, c2 = 2.088175627e-04, c3 = 0.8055701799e-07;  // another try at 100k, seems to work


/*
*/

void readTemp(){

  Vo = analogRead(ThermPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T = T - 273.15;//convert kelvin(i think) to celcius
  //T = (T * 9.0)/ 5.0 + 32.0; //convert celcius to farenheight


}

void updateLcd(){
  char Tchar[5];
  char Tset[4];
  dtostrf(T, 4, 2, Tchar);//translate temp value into something the lcd can display
  dtostrf(heatSetting, 3, 0, Tset);

/*


  Serial.print("Temperature: "); 
  Serial.print(T);
  Serial.println(" F"); 

*/
  u8g2.clearBuffer();					// clear the internal memory
  u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
  u8g2.drawStr(0,10,"temp reading");	// write something to the internal memory
  u8g2.drawStr(50, 20, Tset);
  u8g2.drawStr(60,60,Tchar);
  
  
  if(heatMode){
    u8g2.drawStr(30,30, "HEATER ON");
    if(digitalRead(fetPin) == 1){
      u8g2.drawStr(40, 50, "!!!");
  }
  }
  
  
  u8g2.sendBuffer();


}

void heatMng(){
  if (T <heatSetting){
    digitalWrite(fetPin, 1);
  }
  if (T >= heatSetting ){
    digitalWrite(fetPin, 0);
  }
  else if(T < 0){
    digitalWrite(fetPin, 0);
  }
  
}

void setup() {
  Serial.begin(9600);
  pinMode(stepEnPin, OUTPUT);
  digitalWrite(stepEnPin, 0);
  pinMode(fetPin, OUTPUT);
  digitalWrite(fetPin, 0);
  pinMode(switchButt , INPUT_PULLUP);
  pinMode(heaterSwtch, INPUT_PULLUP);

  u8g2.begin();

  extruder.setMaxSpeed(500);
  extruder.setAcceleration(300);
  //extruder.moveTo(1000000);
}


void loop() {

  heatMode = !digitalRead(heaterSwtch);
  
  if (heatMode){
    heatMng();
  }
  if (!heatMode){
    digitalWrite(fetPin, 0);
  }

  readTemp(); //read thermistor value, do maths to determine temp
  extruder.runSpeed(); //still need to get trigger to update speed by...
  updateLcd(); //update i2c lcd, display things on it
  
  if (digitalRead(switchButt) == LOW){
    digitalWrite(stepEnPin, 1);
    extruder.setSpeed(300);
    Serial.println("button press recvd");
  }

  if (digitalRead(switchButt) == 1){
    digitalWrite(stepEnPin, 0);
  }



  //delay(500);
}


