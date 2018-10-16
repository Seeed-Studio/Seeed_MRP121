#include "Seeed_MPR121_driver.h"

#ifdef ARDUINO_SAMD_VARIANT_COMPLIANCE
  #define SERIAL SerialUSB
#else
  #define SERIAL Serial
#endif

Mpr121 mpr121;

String str1[]={"Screwdriver is touched",
                "Spanner is touched",
                "Wrench is touched",
                "Banana is touched",
                "Peach is touched", 
                "Pear is touched",
                "Pomegranate is touched",
                "Apple is touched",
                };
String str2[]={"Screwdriver is released",
                "Spanner is released",
                "Wrench is released",
                "Banana is released", 
                "Peach is released",
                "Pear is released",
                "Pomegranate is released",
                "Apple is released",
                };        

u16 touch_status_flag[CHANNEL_NUM]={0};
void setup()
{
  s32 ret=0;
  SERIAL.begin(115200);
  if(mpr121.begin()<0)
  {
    SERIAL.println("Can't detect device!!!!");
  }
  else
  {
    SERIAL.println("mpr121 init OK!");
  }
  //set 0x00~0xFF to sensitivity,the value 
  //The higher the value, the higher the sensitivity
  mpr121.set_sensitivity(0xF0); 
  delay(100);
}
void loop()
{
  u16 result=0;
  u16 filtered_data_buf[CHANNEL_NUM]={0};
  u8 baseline_buf[CHANNEL_NUM]={0};
  
  result=mpr121.check_status_register();

  mpr121.get_fruits_data(&result,filtered_data_buf);

  for(int i=0;i<CHANNEL_NUM;i++)
  {
    if(result&(1<<i))                             /*key i is pressed!!*/
    {
      if(0==touch_status_flag[i])             
      { 
        touch_status_flag[i]=1;
        
        //Serial.print("key ");
        //Serial.print(i);
        if(i<=3)
        {
          switch(i){
            case 0:SERIAL.println(str2[0]);break;
            case 1:SERIAL.println(str2[1]);break;
            case 2:SERIAL.println(str2[2]);break;
            case 3:SERIAL.println(str2[3]);break;
          }
        }
        else if(i==8)
        {
          SERIAL.println(str2[4]);
        }
        else if(i==9)
        {
          SERIAL.println(str2[5]);
        }
        else if(i==10)
        {
          SERIAL.println(str2[6]);
        }
        else if(i==11)
        {
          SERIAL.println(str2[7]);
        }
      }
    }
    else
    {
      if(1==touch_status_flag[i])
      {
        touch_status_flag[i]=0;
        //SERIAL.print("key ");
        //SERIAL.print(i);
        if(i<=3)
        {
          switch(i){
            case 0:SERIAL.println(str1[0]);break;
            case 1:SERIAL.println(str1[1]);break;
            case 2:SERIAL.println(str1[2]);break;
            case 3:SERIAL.println(str1[3]);break;
          }
        }
        else if(i==8)
        {
          SERIAL.println(str1[4]);
        }
        else if(i==9)
        {
          SERIAL.println(str1[5]);
        }
        else if(i==10)
        {
          SERIAL.println(str1[6]);
        }
        else if(i=11)
        {
          SERIAL.println(str1[7]);
        }
      }
    }
  }
  delay(50); 
}
