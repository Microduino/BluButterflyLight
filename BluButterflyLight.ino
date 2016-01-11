#include "key.h"
#include "JQ6500.h"
//#include "JQ6500_def.h"
#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
#include "audio.h"


int songs[3][84] = {
  {1,200,1,200,5,200,5,200,6,200,6,200,5,1000,
   4,200,4,200,3,200,3,200,2,200,2,200,1,1000,
   5,200,5,200,4,200,4,200,3,200,3,200,2,1000,
   5,200,5,200,4,200,4,200,3,200,3,200,2,1000,
   1,200,1,200,5,200,5,200,6,200,6,200,5,1000,
   4,200,4,200,3,200,3,200,2,200,2,200,1,1000},

  {1,200,2,200,3,200,1,200,1,200,2,200,3,200,
   1,200,3,200,4,200,5,400,3,200,4,200,5,400,
   5,200,6,200,5,200,4,200,3,200,1,300,5,200,
   6,200,5,200,4,200,3,200,1,300,2,200,-2,200,
   1,500,2,200,-2,200,1,500},

   {3,400,1,400,2,400,-1,400,3,200,2,200,1,200,
    2,200,-1,800,3,400,1,400,2,400,2,400,5,200,
    3,200,0,400,1,400,1,200,0,200,-1,400,0,200,
    1,200,2,400,-2,400,6,200,5,200,3,400,3,500,
    2,200,1,400,2,400,2,200,3,200,2,200,5,600,
    5,200,5,200,5,200,5,200,5,200}
 };


                



  ///==========================
//   int sensor_pin[7]= {
//   A6,8,10,12,A0,A2,13
// };


  int sensor_pin[7]= {
  A6,8,10,12,A0,A2,0
};


unsigned long time_play;
int led_num = 0;

String currentInfo;

bool bleEnable=false;

SoftwareSerial mySerial(4, 5); //RX,TX

#define my_Serial mySerial  //core

void setup()
{
  Serial.begin(38400);


  my_Serial.begin(9600); 


  for(int a=0;a<7;a++)
    pinMode(sensor_pin[a],INPUT);

  key_init();
  strip.begin();	//初始化LED
  strip.show(); // Initialize all pixels to 'off'

  AUDIO.init(DEVICE_FLASH, MODE_ONE_STOP, 28);
  delay(500);
  

  for(int a=1;a<8;a++)
  {
    audio_play(a, 5, 500);
  }

  for(int a=1;a<8;a++)
  {
    led_off(a, 5);
  }

  delay(2000);

  Serial.println("OK");
}

void loop() 
{


    int temp;
    if(millis()>time_play+3000)
    {
        if(led_num)
        {
            led_off(led_num,20);
            led_num = 0;  
        }
        else
        {
          led_num = random(8);
          led_on(led_num,20); 
        }
        time_play = millis();
    }
     

    for(int key_num=1; key_num<8; key_num++) {

      ble();
      //Serial.println(digitalRead(4));
      //Serial.println(bleEnable);

      if(!bleEnable) {
        temp = key_get(sensor_pin[key_num-1], 1);
        if(temp == 1)
        {
            led_off(key_num, 5);  
        }
        else if(temp == 2)
        {
            if(led_num)
            {
              led_off(led_num,1);
              led_num = 0;  
            }
            audio_play(key_num, 5 ,200);
            time_play = millis();  
        }
      }
    }  

}




void ble() {
    if (my_Serial.available() > 0) {
      currentInfo = my_Serial.readStringUntil('\n');
      Serial.println(currentInfo);

      if(currentInfo=="ERROR") {
        return;
      } else if (currentInfo.startsWith("Connected")) {
        bleEnable=true;
      } else if (currentInfo.startsWith("Disconnected")) {
        bleEnable=false;
      } 

      if(!bleEnable) {
        return;
      }

      if (currentInfo.startsWith("do")) {
        audio_play(1, 5, 500);
        led_off(1, 5); 
      }else if (currentInfo.startsWith("re")) {
        audio_play(2, 5, 500);
        led_off(2, 5); 
      }else if (currentInfo.startsWith("mi")) {
        audio_play(3, 5, 500);
        led_off(3, 5); 
      }else if (currentInfo.startsWith("fa")) {
        audio_play(4, 5, 500);
        led_off(4, 5); 
      }else if (currentInfo.startsWith("so")) {
        audio_play(5, 5, 500);
        led_off(5, 5); 
      }else if (currentInfo.startsWith("la")) {
        audio_play(6, 5, 500);
        led_off(6, 5); 
      }else if (currentInfo.startsWith("si")) {
        audio_play(7, 5, 500);
        led_off(7, 5); 
      } else if (currentInfo.startsWith("xxx")) {
          for(int a=0;a<42;a++) {
            audio_play(songs[0][a*2], 5, songs[0][a*2+1]);
            led_off(songs[0][a*2],5);  
          }
      } else if (currentInfo.startsWith("lzlh")) {
          for(int a=0;a<42;a++) {
            audio_play(songs[1][a*2], 5, songs[1][a*2+1]);
            led_off(songs[1][a*2],5);  
          }
      }else if (currentInfo.startsWith("apple")) {
          for(int a=0;a<42;a++) {
            audio_play(songs[2][a*2], 5, songs[2][a*2+1]);
            led_off(songs[2][a*2],5);  
          }
      }





  }
}



























