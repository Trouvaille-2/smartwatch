#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Menu.h"


/**
  * 坐标轴定义：
  * 左上角为(0, 0)点
  * 横向向右为X轴，取值范围：0~127
  * 纵向向下为Y轴，取值范围：0~63
  * 
  *       0             X轴           127 
  *      .------------------------------->
  *    0 |
  *      |
  *      |
  *      |
  *  Y轴 |
  *      |
  *      |
  *      |
  *   63 |
  *      v
  * 
  */

int main(void)
{
	/*OLED初始化*/
	OLED_Init();
	OLED_Clear();
	Menu_Init();
	
	
	while (1)
	{
		
	Show_clock_ui();
		OLED_Update();
	}
}
