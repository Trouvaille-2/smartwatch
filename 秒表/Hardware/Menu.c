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

/*-------------------滑动菜单界面------------------------*/

uint8_t pre_selection;//上次选择的选项
uint8_t target_selection;//目标选项
uint8_t x_pre=48;//上次选项的x坐标
uint8_t Speed=4;
uint8_t move_flag;//开始移动的标志位，1表示开始移动，0表示停止移动

void Menu_Animation(void)
{
	OLED_Clear();
	OLED_ShowImage(42,10,44,44,Frame);
	
	if(pre_selection<target_selection)//切换到下一项
	{
		x_pre-=Speed;
		if(x_pre==0)
		{
			pre_selection++;
			move_flag=0;
			x_pre=48;
		}
	}
	if(pre_selection>target_selection)//切换到上一项
	{
		 x_pre+=Speed;
		if(x_pre==96)
		{
			pre_selection--;
			move_flag=0;
			x_pre=48;
		}
	}
	
	if(pre_selection>=1)
	{
		OLED_ShowImage(x_pre-48,16,32,32,Menu_Graph[pre_selection-1]);
	}
	
	if(pre_selection>=2)
	{
		OLED_ShowImage(x_pre-96,16,32,32,Menu_Graph[pre_selection-2]);
	}
	OLED_ShowImage(x_pre,16,32,32,Menu_Graph[pre_selection]);
	OLED_ShowImage(x_pre+48,16,32,32,Menu_Graph[pre_selection+1]);
	OLED_ShowImage(x_pre+96,16,32,32,Menu_Graph[pre_selection+2]);
	
	OLED_Update();
		
}

void  MenuToFunction(void)
{
	for(uint8_t i=0;i<=6;i++)
	{
		OLED_Clear();
	if(pre_selection>=1)
	{
		OLED_ShowImage(x_pre-48,16+8*i,32,32,Menu_Graph[pre_selection-1]);
	}
	
	
	OLED_ShowImage(x_pre,16+8*i,32,32,Menu_Graph[pre_selection]);
	OLED_ShowImage(x_pre+48,16+8*i,32,32,Menu_Graph[pre_selection+1]);
	
	
	OLED_Update();
}
}

void Set_Selection(uint8_t move_flag,uint8_t Pre_Selection,uint8_t Target_Selection)
{
	if(move_flag==1)
	{
		pre_selection=Pre_Selection;
		target_selection=Target_Selection;
		
	}
	Menu_Animation();
	
}



uint8_t menu_flag=1;
int Menu(void)
{
	move_flag=1;
	uint8_t DirectFlag=2;
	while(1)
	{
		KeyNum=Key_GetNum();
		uint8_t menu_flag_temp=0;
		if(KeyNum==1)//上一项
		{
			DirectFlag=1;
			move_flag=1;
			menu_flag--;
			if(menu_flag<=0) menu_flag=7;
			
		}
		else if(KeyNum==2)//下一项
		{
			DirectFlag=2;
			move_flag=1;
			menu_flag++;
			if(menu_flag>=8) menu_flag=1;
			
		}
		else if(KeyNum==3)//确认
		{
			OLED_Clear();
			OLED_Update();
			menu_flag_temp=menu_flag;
			
		}
		
		if(menu_flag_temp==1){return 0;}
		else if(menu_flag_temp==2){StopWatch();}
		else if(menu_flag_temp==3){}
		else if(menu_flag_temp==4){}
		else if(menu_flag_temp==5){}
		else if(menu_flag_temp==6){}
		
		
	
		
		if(menu_flag==1)
		{
			if(DirectFlag==1)Set_Selection(move_flag,1,0);
			else if(DirectFlag==2)Set_Selection(move_flag,0,0);
		}
		else 
		{
			if(DirectFlag==1)Set_Selection(move_flag,menu_flag,menu_flag-1);
			else if(DirectFlag==2)Set_Selection(move_flag,menu_flag-2,menu_flag-1);
		}
	}
}

/*------------------秒表界面------------------------*/

uint8_t hour,min,sec;
void Show_StopWatch_ui(void)
{
	OLED_ShowImage(0,0,16,16,Return);
	OLED_Printf(32,20,OLED_8X16,"%02d:%02d:%02d",hour,min,sec);
	OLED_ShowString(8,44,"开始",OLED_8X16);
	OLED_ShowString(48,44,"停止",OLED_8X16);
	OLED_ShowString(88,44,"结束",OLED_8X16);
}

uint8_t start_timing_flag;//1.开始，0停止。
void StopWatch_Tick(void)
{
	static uint16_t Count;
	Count++;
	if(Count>=1000)
	{
		Count=0;
	if(start_timing_flag==1)
	{
		sec++;
		if(sec>=60)
		{
			sec=0;
			min++;
			if(min>=60)
			{
				min=0;
				hour++;
				if(hour>99)hour=0;
				
			}
			
		}
	}
}
}

uint8_t stopwatch_flag=1;
int StopWatch(void)
{
	while(1)
	{
		KeyNum=Key_GetNum();
		uint8_t stopwatch_flag_temp=0;
		if(KeyNum==1)//上一项
		{
			stopwatch_flag--;
			if(stopwatch_flag<=0) stopwatch_flag=4;
			
		}
		else if(KeyNum==2)//下一项
		{
			stopwatch_flag++;
			if(stopwatch_flag>=5) stopwatch_flag=1;
			
		}
		else if(KeyNum==3)//确认
		{
			OLED_Clear();
			OLED_Update();
			stopwatch_flag_temp=stopwatch_flag;
			
		}
		
		if(stopwatch_flag_temp==1){return 0;}
		
		
		
		switch(stopwatch_flag)
		{
			case 1:
				Show_StopWatch_ui();
				OLED_ReverseArea(0,0,16,16);
				OLED_Update();
				break;
			
			case 2:
				Show_StopWatch_ui();
				start_timing_flag=1;
				OLED_ReverseArea(8,44,32,16);
				OLED_Update();
				break;
			
			case 3:
				Show_StopWatch_ui();
				start_timing_flag=0;
				OLED_ReverseArea(48,44,32,16);
				OLED_Update();
				break;
			
			case 4:
				Show_StopWatch_ui();
				start_timing_flag=0;
				hour=min=sec=0;
				OLED_ReverseArea(88,44,32,16);
				OLED_Update();
				break;
			
		}
	}
	
}