#include "Wire.h"
#include "Adafruit_LiquidCrystal.h"

// initialize the library with the numbers of the interface pins
Adafruit_LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int i=0;
int j=-1;
int k=-1;
float v=0;
float logc=0;
float c=0;
float maxv=0;
float vals[250];

//PINS
int sensor=0;
int motor_output=7;
int prompt=7;
void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Breathalyzer");
  lcd.setCursor(0,1);
  lcd.print("Are you sober?");
  Serial.begin(9600);
  pinMode(sensor,INPUT);
  pinMode(prompt,INPUT);
  //pinMode(motor_output,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(prompt)==HIGH)
  {
    j=0;
  }

  if((j>=0)&&(k>=0))
  {
    j=-1;
  }

  
  if(j>=0)
  {
    if(j==1)
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Reading values");
      lcd.setCursor(0,1);
      lcd.print("Hold on !!");
    }
    float reading = analogRead(sensor);
    if(j%3==0)
    {
      v=(reading/1024)*5;
      vals[(int)(j/3)]=v;
    }
    Serial.println("vals");
    Serial.println(j);
    if(j==750)
    {
      j=-1;
      k=0;
    }
    else
    {
      j=j+1;
    }
  }

  if(k>=0)
  {
    if(k==0)
    {
      for(int f=0;f<250;f++)
      {
        if(vals[f]>maxv)
        {
          maxv=vals[f];
        }
      }
      logc=3.23*log10(maxv)+3.92;
      c=pow(10,logc);
      c=(c/(0.7*0.786))*pow(10,-4);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("C(%):");
      lcd.setCursor(8,0);
      lcd.print(c);
      if(c>20)
      {
        lcd.setCursor(0,1);
        lcd.print("DRUNK");
      }
      else
      {
        lcd.setCursor(0,1);
        lcd.print("NOT DRUNK"); 
      }
    }
    Serial.println(k);
    k=k+1;
    if(k==2000)
    {
      k=-1;
      maxv=0;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Breathalyzer");
      lcd.setCursor(0,1);
      lcd.print("Are you sober?");
    }
  }
}
