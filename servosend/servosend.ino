#include <Servo.h>

#define SERVOPIN	(9)
#define VOLUMEPIN	(0)

Servo g_servo;
boolean sendSerial=false;
int sw=LOW,last_sw=HIGH;
void setup() 
{       
  Serial.begin(9600);
  g_servo.attach(SERVOPIN);
  pinMode(2,INPUT);
} 

int Map( int iIn, int iIn1, int iIn2, int iOut1, int iOut2, boolean bConstrain = false )
{
  double dValue = (double)(iIn - iIn1) * (iOut2 - iOut1) / (iIn2 - iIn1) + iOut1;
  int iValue = (0 < dValue) ? (int)(dValue + 0.5) : (int)(dValue - 0.5);
  if( bConstrain )
  {
    int iOutMin, iOutMax;
    if( iOut1 < iOut2 )
    {
      iOutMin= iOut1;
      iOutMax= iOut2;
    }
    else
    {
      iOutMin= iOut2;
      iOutMax= iOut1;
    }
    if( iOutMin > iValue )
    {
      return iOutMin;
    }
    if( iOutMax < iValue )
    {
      return iOutMax;
    }
  }
  return iValue;
}

void loop() 
{ 
  sw=digitalRead(2);

  int iValue = analogRead(VOLUMEPIN);
  int iAngle = Map(iValue, 0, 1023, 0, 180, true);
  g_servo.write(iAngle);

  if(sw==HIGH&&last_sw==LOW){
    sendSerial=!sendSerial;
  }

  if(sendSerial){
    Serial.println(iAngle);
  }
  byte data=0;
  if(Serial.available()){
    data=Serial.read();
    int Idata=data;
    g_servo.write(Idata);
  }
  last_sw=sw;
  delay(100);
} 






