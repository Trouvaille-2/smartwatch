#include "stm32f10x.h"                  // Device header
#include "MyRTC.h"
#include "OLED.h"
#include "LED.h"
#include "Key.h"

void Show_SetTime_FirstUI()
{
	OLED_ShowImage(0,0,16,16,Return);
	OLED_Printf(0,16,OLED_8X16,"年:%4d",MyRTC_Time[0]);
	OLED_Printf(0,32,OLED_8X16,"月:%2d",MyRTC_Time[1]);
	OLED_Printf(0,48,OLED_8X16,"日:%2d",MyRTC_Time[2]);
	
}
void Show_SetTime_SecondUI()
{
	OLED_Printf(0,0,OLED_8X16,"时:%2d",MyRTC_Time[3]);
	OLED_Printf(0,16,OLED_8X16,"分:%2d",MyRTC_Time[4]);
	OLED_Printf(0,32,OLED_8X16,"秒:%2d",MyRTC_Time[5]);
	
}

extern int KeyNum;
int set_time_flag=1;
int SetTime(void)
{
	while(1)
	{
		KeyNum=Key_GetNum();
		if(KeyNum==1)//上一项
		{
			set_time_flag--;
			if(set_time_flag<=0) set_time_flag=7;
			
		}
		else if(KeyNum==2)//下一项
		{
			set_time_flag++;
			if(set_time_flag>=8) set_time_flag=1;
			
		}
		else if(KeyNum==3)//确认
		{
			OLED_Clear();
			OLED_Update();
			
		}
		
		switch(set_time_flag)
		{
			case 1:
				OLED_Clear();
				Show_SetTime_FirstUI();
				OLED_ReverseArea(0,0,16,16);
				OLED_Update();
				break;
			
			case 2:
				Show_SetTime_FirstUI();
				OLED_ReverseArea(0,16,16,16);
				OLED_Update();
				break;
			
			case 3:
				Show_SetTime_FirstUI();
				OLED_ReverseArea(0,32,16,16);
				OLED_Update();
				break;
			
			case 4:
				Show_SetTime_FirstUI();
				OLED_ReverseArea(0,48,16,16);
				OLED_Update();
				break;
			
			case 5:
				OLED_Clear();
				Show_SetTime_SecondUI();
				OLED_ReverseArea(0,0,16,16);
				OLED_Update();
				break;
			
			case 6:
				Show_SetTime_SecondUI();
				OLED_ReverseArea(0,16,16,16);
				OLED_Update();
				break;
		}
	}
	
}