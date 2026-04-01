 #include <LPC21xx.h>
 #include "delay.h"
 #include "types.h"
 #include "defines.h"
 #include "lcd.h"
 #include "lcd_defines.h"
 #include "pindefines.h"
 #include "rtc.h"
extern s32 hour,min,sec,date,month,year,day;
void InitLCD(void)
{
	  IODIR0 |= (0xff<<LCD_data)|(1<<RS)|(1<<RW)|(1<<EN);
	  delay_ms(20);
	  CmdLCD(MODE_8BIT_1LINE);
	  delay_ms(8);
	  CmdLCD(MODE_8BIT_1LINE);
	  delay_ms(1);
	  CmdLCD(MODE_8BIT_1LINE);
	  delay_ms(1);
	  CmdLCD(MODE_8BIT_2LINE);
	  CmdLCD(DSP_OFF);
	  CmdLCD(CLEAR_LCD );
	  CmdLCD(SHIFT_CUR_RIGHT);
	  CmdLCD(DSP_ON_CUR_OFF);
}

void DispLCD(u8 val)
{
	    IOCLR0 = 1<<RW;
	    WRITEBYTE(IOPIN0,LCD_data,val);
	    IOSET0 = 1<<EN;
	    delay_ms(2);
	    IOCLR0 =1<<EN;
	    delay_us(2);
}

void CmdLCD(u8 cmd)
{
	     IOCLR0 = 1<<RS;
	     DispLCD(cmd);
	     delay_ms(2);
}

void CharLCD(s8 data)
{
	     IOSET0 = 1<<RS;
	     DispLCD(data);
	     delay_ms(2);
} 

void StrLCD(s8 *ptr)
{
	while(*ptr!='\0')
	{
		 CharLCD(*ptr);
		 ptr++;
	}
}

void IntLCD(s32 num)
{
	  s8 a[10],i=0;
	  if(num==0)
		{
			CharLCD(0+48);
		}
		else{
			if(num<0)
			{
				  CharLCD('-');
				  num=-num;
			}
			while(num)
			{
				  a[i++]=(num%10)+48;
				  num=num/10;
			}
			--i;
			for(;i>=0;i--)
			{
				   CharLCD(a[i]);
			}
		}
}

void WriteToCGRAM(void)
{
	   s8 i,a[]={0x00,0x1f,0x11,0x11,0x11,0x1f,0x00,0x00};
		 CmdLCD(0x60);
		 for(i=0;i<8;i++)
		    CharLCD(a[i]);
}

void FloatLCD(f32 fN,u32 nDP)
{
	  u32 n;
	  s32 i;
	  if(fN<0.0)
		{
			  CharLCD('-');
			  fN = -fN;
		}
		n=fN;
		IntLCD(n);
		CharLCD('.');
		for(i=0;i<nDP;i++)
		{
			   fN = (fN-n)*10;
			   n=fN;
			   CharLCD(n+48);
		}
}
void Diplay_medicine_time()
{
            	CmdLCD(CLEAR_LCD);
						  CmdLCD(GOTO_LINE1_POS0);
							StrLCD("TAKE MEDCINE");
}
void Diplay()
{
      //CmdLCD(0x80);
		  GetRTCTimeInfo(&hour,&min,&sec);
			DisplayRTCTime(hour,min,sec);
			GetRTCDateInfo(&date,&month,&year);
			DisplayRTCDate(date,month,year);
			GetRTCDay(&day);
			DisplayRTCDay(day);
}
void Disp_medicine_fail()
{
                CmdLCD(CLEAR_LCD);
								CmdLCD(GOTO_LINE1_POS0);
								StrLCD("FAILED TO TAKE");
								CmdLCD(GOTO_LINE2_POS0);
								StrLCD("MEDICINE");									
}
void Disp_menu()
{
	         CmdLCD(CLEAR_LCD);
						CmdLCD(GOTO_LINE1_POS0);
						StrLCD("MENU: 1:RTC ");
						CmdLCD(GOTO_LINE2_POS0);
						StrLCD("2:MED 3:EXIT");
						delay_s(1);
}

