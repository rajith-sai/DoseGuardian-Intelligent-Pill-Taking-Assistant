#include <LPC21xx.h>
#include "defines.h"
#include "lcd.h"
#include "lcd_defines.h"
#include "kpm.h"
#include "rtc.h"
#include "delay.h"
#include "edit.h"
#include "pindefines.h"
s32 M_HOUR=10,M_MIN,M_SEC;
s32 hour,min,sec,date,month,year,day;
int main()
{
	u8 choice;
	IODIR0|=3<<LED; 	     //for setting BUZZER and LED as output direction
//IntLCD(1);
	RTC_Init();
	InitLCD();
	KeyadInit();
	while(1)
	{
		  //CmdLCD(CLEAR_LCD);
		  Diplay();
			if((((IOPIN0>>SW1)&1)==0))
				{
					  Disp_menu();
						WRITENIBBLE(IOPIN1,16,0);//rows are cleared
						while(ColStat()); //waiting for key press
            choice=ReadKeyVal();
   					switch(choice)
						{
								case '1':CmdLCD(CLEAR_LCD);
									       edit_RTC();
												  break;
								case '2':CmdLCD(CLEAR_LCD);
									       edit_MED(&M_HOUR,&M_MIN,&M_SEC);//for setting medicine time
												 break;
								case '3': CmdLCD(CLEAR_LCD);
													break;
							  default:CmdLCD(CLEAR_LCD);
												StrLCD("WRONG INPUT");
							           delay_s(30);
									       CmdLCD(CLEAR_LCD);
						}
					}
				  if(((hour==M_HOUR)&&(min==M_MIN)))
					{
							Diplay_medicine_time();
						  SETBIT(IOSET0,BUZZER);
							delay_ms(30);
						  SETBIT(IOCLR0,BUZZER);
							if(!(((IOPIN0>>SW2)&1)==0))//active low switch
							{
								SETBIT(IOSET0,LED);
							  Disp_medicine_fail();
								while(!(((IOPIN0>>SW2)&1)==0));//active low switch
                SETBIT(IOCLR0,LED);
                CmdLCD(CLEAR_LCD);								
							}
					}
		   }
	}	
