#include "arduino.h"

boolean key[7];			//按键
boolean key_cache[7];		//检测按键松开缓存
int sensor_vol_cache[7];

void key_init()
{
  for(int a=0;a<7;a++)
  {
    key[a]=LOW;
    key_cache[a]=HIGH;
  }
}

byte key_get(int _key_pin,boolean _key_type)
{
  key_cache[_key_pin]=key[_key_pin];		//缓存作判断用

  key[_key_pin]=!digitalRead(_key_pin);	//触发时

  switch(_key_type)
  {
  case 0:
    if(!key[_key_pin] && key_cache[_key_pin])		//按下松开后
      return 2;
    else if(key[_key_pin] && !key_cache[_key_pin])
      return 1;
    else
      return 0;
    break;
  case 1:
    if(key[_key_pin] && !key_cache[_key_pin])		//按下松开后
      return 2;
    else if(!key[_key_pin] && key_cache[_key_pin])
      return 1;
    else
      return 0;
    break;
  }
}




