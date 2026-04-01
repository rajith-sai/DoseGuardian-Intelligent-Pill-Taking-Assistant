#include<LPC21xx.h>
#include "kpm.h"
#include "lcd.h"
#include "defines.h"
#include "rtc.h" 
#include "delay.h"
#include "lcd_defines.h"
void set_values(int*varible,int min,int max);
s32 hr,mn,sc,dy,dd,mm,yy;
void edit_RTC()
{ 
	u8 choice;
	s32 flag=0;
	while(1)
	{
		//CmdLCD(CLEAR_LCD);
		CmdLCD(GOTO_LINE1_POS0);
		StrLCD("1:H 2:M 3:S 4:DY");
		CmdLCD(GOTO_LINE2_POS0);
		StrLCD("5:D 6:MM 7:Y 8:E");
		WRITENIBBLE(IOPIN1,16,0);//rows are cleared
		while(ColStat());//waiting for key press
		choice=ReadKeyVal();
		CmdLCD(CLEAR_LCD);
		CmdLCD(GOTO_LINE1_POS0);
		switch(choice)
		{
			case '1':StrLCD("set_HOUR(0-23)");
				       set_values(&hr,0,23);
			         SetRTCTimeInfo(hr,mn,sc,1);
				         break;		
			case '2':StrLCD("set_MIN(0-59)");
				      set_values(&mn,0,59);
			        SetRTCTimeInfo(hr,mn,sc,2);
				         break;
			case'3':StrLCD("set_SEC(0-59)");
							set_values(&sc,0,59);
							SetRTCTimeInfo(hr,mn,sc,3);
				         break;
			case '4':StrLCD("set_WEEK(0-6)");
				      set_values(&dy,0,6);
			        SetRTCDay(dy);
				         break;
			case '5':StrLCD("set_DAY(0-31)");
				      set_values(&dd,1,31);
			        SetRTCDateInfo(dd,mm,yy,5);
				         break;
			case '6':StrLCD("set_MONTH(0-12)");
							set_values(&mm,1,12);
							SetRTCDateInfo(dd,mm,yy,6);
				         break;
			case '7':StrLCD("setYEAR(2020-99)");
							set_values(&yy,2020,2099);
			        SetRTCDateInfo(dd,mm,yy,7);
				         break;
			case '8':flag=1;
			         break;
		}
		if(flag==1)
		{
			break;
		}
	}
 
}
void edit_MED(s32*HH, s32*MM, s32*SS)
{
	u8 choice;
	while(1)
	{
		CmdLCD(CLEAR_LCD);
		CmdLCD(GOTO_LINE1_POS0);
		StrLCD("1:HOUR 2:MIN");
		CmdLCD(GOTO_LINE2_POS0);
		StrLCD("3:SEC 4:EXT");
		WRITENIBBLE(IOPIN1,16,0);//rows are cleared
		while(ColStat());//waiting for key press
		choice=ReadKeyVal();
		CmdLCD(CLEAR_LCD);
		CmdLCD(GOTO_LINE1_POS0);
		switch(choice)
		{
			
			case'1':StrLCD("SET MED HOUR");
			        delay_ms(200);
							set_values(HH,0,23);
				         break;		
			case'2':StrLCD("SET MED MIN");
			        delay_ms(200);
							set_values(MM,0,59);
				         break;
			case'3':StrLCD("SET MED SEC");
			        delay_ms(200);
							set_values(SS,0,59);
				         break;
			case'4':CmdLCD(CLEAR_LCD);
							goto BREAK;
		}
		BREAK:if(choice=='4')
		{
			break;
		}
	}
}
void set_values(int *varible,int min,int max)
{
	u32 num=0;
  char digit;

lable:while(1)
			{
					WRITENIBBLE(IOPIN1,16,0);   
					while(ColStat());          
					digit = ReadKeyVal();
					delay_ms(150);             
					if(digit=='#')
					break;
					else if(digit=='*')
					{
							  if(num>0)
								num = num / 10;  
								CmdLCD(GOTO_LINE2_POS0);
								StrLCD("                ");
					}
					else 
					{
							num=(num*10)+(digit-'0');
					}
					CmdLCD(GOTO_LINE2_POS0);
					IntLCD(num);
    }

				 if(((num>=min)&&(num<=max)))
				 {
						 *varible=num;
					   CmdLCD(CLEAR_LCD);
					   CmdLCD(GOTO_LINE1_POS0);
						 StrLCD("VALUE UPDATED");
						 delay_ms(500);
					}
					else
					{
						 CmdLCD(CLEAR_LCD);//clearing Lcd
						 CmdLCD(GOTO_LINE1_POS0);
						 StrLCD("WRONG INPUT");
						 delay_ms(500);
						 CmdLCD(CLEAR_LCD);
						 CmdLCD(GOTO_LINE1_POS0);
						 StrLCD("set agian");
						 num=0;
						 goto lable;
					}
}
