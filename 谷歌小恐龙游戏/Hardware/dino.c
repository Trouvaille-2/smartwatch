#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Key.h"

int Score;
void Show_Score(void)
{
	OLED_ShowNum(98,0,Score,5,OLED_6X8);
}

uint16_t Ground_Pos;
void Show_Ground(void)
{
	if(Ground_Pos<128)
	{
		for(uint8_t i=0;i<128;i++)
		{
			OLED_DisplayBuf[7][i]=Ground[i+Ground_Pos];
		}
	}
	else 
	{
		for(uint8_t i=0;i<255-Ground_Pos;i++)
		{
			OLED_DisplayBuf[7][i]=Ground[i+Ground_Pos];
				
		}
		for(uint8_t i=255-Ground_Pos;i<128;i++)
		{
			
			OLED_DisplayBuf[7][i]=Ground[i-(255-Ground_Pos)];
		}
	}
	
}

void DinoGame_Animation(void)
{
	OLED_Clear();
	Show_Score();
	Show_Ground();
	OLED_Update();
}

void Dino_Tick(void)
{
	static uint16_t Score_Count,Ground_Count;
	Score_Count++;
	Ground_Count++;
	if(Score_Count>=1000)
	{
		Score_Count=0;
		Score++;
	}
	
	if(Ground_Count>=200)
	{
		Ground_Count=0;
		Ground_Pos++;
		if(Ground_Pos>=256)Ground_Pos=0;
		
	}
}