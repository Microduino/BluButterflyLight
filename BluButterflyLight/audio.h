#include "arduino.h"
#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>

#define PIN 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(14, PIN, NEO_GRB + NEO_KHZ800);

//SoftwareSerial mySerial(2, 3);
//JQ6500 AUDIO(&mySerial);
JQ6500 AUDIO(&Serial1);

uint8_t color[8][3]= {
  {0,0,0},
  {2, 0, 0},
  {2, 1, 0},
  {2, 2, 0},
  {0, 2, 0},
  {0, 2, 1},
  {0, 0, 2},
  {2, 0, 2},
};

void led_on(int num, int on_time) {
    for(int i = 0; i<32; i++) {
          //for14 light
          strip.setPixelColor(2*num-2, color[num][0]*i*4, color[num][1]*i*4, color[num][2]*i*4); 
          strip.setPixelColor(2*num-1, color[num][0]*i*4, color[num][1]*i*4, color[num][2]*i*4);

        //for 7 light
        //strip.setPixelColor(num-1, color[num][0]*i*4, color[num][1]*i*4, color[num][2]*i*4);
          strip.show();
           //delay(on_time);   
      }
}

void led_off(int num, int off_time) {
    for(int i = 31; i>=0; i--) {
        //for14 light
        strip.setPixelColor(2*num-2, color[num][0]*i*4, color[num][1]*i*4, color[num][2]*i*4); 
        strip.setPixelColor(2*num-1, color[num][0]*i*4, color[num][1]*i*4, color[num][2]*i*4);

        //for 7 light
      //strip.setPixelColor(num-1, color[num][0]*i*4, color[num][1]*i*4, color[num][2]*i*4);
        strip.show();
        //delay(off_time);   
    }  
}

void audio_play(int num, int on_time, int delay_time) {
      AUDIO.choose(num+7);

      led_on(num, on_time);
      delay(delay_time);
}


