#include "stm32f10x.h"                  // Device header
#include "MyRTC.h"
#include "OLED.h"
#include "LED.h"
#include "Key.h"
#include "SetTime.h"

uint8_t KeyNum;

void Menu_Init(void)
{
	 MyRTC_Init();
	Key_Init();
	LED_Init();
}

/*-------------------首页时钟------------------------*/

void Show_clock_ui(void)
{
    MyRTC_ReadTime();
    OLED_Clear(); 

    // 日期用小字体（顶部）
    OLED_Printf(0, 0, OLED_6X8, "%04d-%02d-%02d", MyRTC_Time[0], MyRTC_Time[1], MyRTC_Time[2]);

    // 时间用12x24大字体，注意Y坐标改为16，避免和日期重叠（16+24=40，不超屏幕）
    OLED_Printf(16, 16, OLED_12X24, "%02d:%02d:%02d", MyRTC_Time[3], MyRTC_Time[4], MyRTC_Time[5]);

    // 底部文字（注意Y坐标改为48，在大字体下方）
    OLED_ShowString(0, 48, "菜单", OLED_8X16);   // 先换成英文，避免中文乱码
    OLED_ShowString(96, 48, "设置", OLED_8X16);
}
 
int clkflg=1;

int First_Page_Clock(void)
{
	while(1)
	{
		KeyNum=Key_GetNum();
		if(KeyNum==1)//上一项
		{
			clkflg--;
			if(clkflg<=0) clkflg=2;
			
		}
		else if(KeyNum==2)//下一项
		{
			clkflg++;
			if(clkflg>=3) clkflg=1;
			
		}
		else if(KeyNum==3)//确认
		{
			OLED_Clear();
			OLED_Update();
			return clkflg;
		}
		
		switch(clkflg)
		{
			case 1:
				Show_clock_ui();
				OLED_ReverseArea(0,48,32,16);
				OLED_Update();
				break;
			
			case 2:
				Show_clock_ui();
				OLED_ReverseArea(96,48,32,16);
				OLED_Update();
				break;
			
		}
	}
	
	
}
/*-------------------设置页面------------------------*/
void SettingPage_ui()
{
	OLED_ShowImage(0,0,16,16,Return);
	OLED_ShowString(0,16,"日期时间设置",OLED_8X16);
	
	
}

int setflg=2;
int SettingPage(void)
{
	while(1)
	{
		KeyNum=Key_GetNum();
		uint8_t setflag_temp=0;
		if(KeyNum==1)//上一项
		{
			setflg--;
			if(setflg<=0) setflg=2;
			
		}
		else if(KeyNum==2)//下一项
		{
			setflg++;
			if(setflg>=3) setflg=1;
			
		}
		else if(KeyNum==3)//确认
		{
			OLED_Clear();
			OLED_Update();
			setflag_temp=setflg;
			
		}
		
		if(setflag_temp==1){return 0;}
		else if(setflag_temp==2){SetTime();}
		
		
		switch(setflg)
		{
			case 1:
				SettingPage_ui();
				OLED_ReverseArea(0,0,16,16);
				OLED_Update();
				break;
			
			case 2:
				SettingPage_ui();
				OLED_ReverseArea(0,16,96,16);
				OLED_Update();
				break;
			
		}
	}
	
	
}