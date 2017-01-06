#include "iMenu.h"

#define SIZE_OF_KEYBD_MENU  (5)

static uint8_t keymenu_curr_state = 0;
static uint8_t KeyValue=0;

KeyMenuTableStruct KeyMenuTable[SIZE_OF_KEYBD_MENU] =
{
	{0,0,0,0,main_window_proc},
        {1,0,0,0,run_window_proc},
	{2,0,0,0,image_debug_proc},
	{3,0,0,0,speed_window_proc},
	{4,0,0,0,direction_window_proc},
};

#define MAIN_MENU_LEN (4)
int8_t * MainMenuStrings[]={"Run!!!","ImageDebug","Speed","Direction"};

#define RUN_MENU_LEN  (1)
int8_t * RunMenuStrings[]={"RedyToRun???"};

#define SPEED_MENU_LEN	(5)
int8_t * SpeedPIDMenuStrings[] = {"SpeedP", "SpeedI", "SpeedD","SpeedMax","SpeedMin"};
uint32_t  SpeedParam[SPEED_MENU_LEN]={160,16,0,110,100};//180,72,0(bu jia bang bang kong zhi);324,28,0
uint32_t  SpeedParamMin[SPEED_MENU_LEN]={0,0,0,0,0};
uint32_t  SpeedParamMax[SPEED_MENU_LEN]={1200,512,2048,200,200};
uint32_t  SpeedParamAdj[SPEED_MENU_LEN]={10,8,32,5,5};

void Show_Debug(void)
{
	u8 tmp;
	if(RTAngle>=0)
	{
		LCD5110_write_english_string(0,0,"*Angle*:");
		LCD5110_Write_Num(48,0,(int16_t)(RTAngle));
		if(RTAngle<10)
		{
			LCD5110_write_english_string(54,0,".");
			tmp=(int16_t)(RTAngle*10)%10;
			LCD5110_Write_Num(60,0,tmp);
			LCD5110_write_english_string(66,0,"  ");
		}
		else
		{
			LCD5110_write_english_string(60,0,".");
			tmp=(int16_t)(RTAngle*10)%10;
			LCD5110_Write_Num(66,0,tmp);
			LCD5110_write_english_string(72,0," ");
		}
	}
	else
	{
		LCD5110_write_english_string(0,0,"*Angle*:-");
		LCD5110_Write_Num(54,0,(int16_t)(-RTAngle));
		if(RTAngle>-10)
		{
			LCD5110_write_english_string(60,0,".");
			tmp=(int16_t)(-RTAngle*10)%10;
			LCD5110_Write_Num(66,0,tmp);
			LCD5110_write_english_string(72,0," ");
		}
		else
		{
			LCD5110_write_english_string(66,0,".");
			tmp=(int16_t)(-RTAngle*10)%10;
			LCD5110_Write_Num(72,0,tmp);
			LCD5110_write_english_string(78,0,"");
		}
	}
#if Show_Debug_Info
	if(EncoderLeft>=0)
	{
		LCD5110_write_english_string(0,1,"VLeft:");
		LCD5110_Write_Num(36,1,EncoderLeft);
		if(EncoderLeft<10)
			LCD5110_write_english_string(42,1,"   ");
		else if(EncoderLeft<100)
			LCD5110_write_english_string(48,1,"  ");
	}
	else
	{
		LCD5110_write_english_string(0,1,"VLeft:-");
		LCD5110_Write_Num(42,1,-EncoderLeft);
		if(EncoderLeft>-10)
			LCD5110_write_english_string(48,1,"   ");
		else if(EncoderLeft>-100)
			LCD5110_write_english_string(54,1,"  ");
	}
	if(EncoderRight>=0)
	{
		LCD5110_write_english_string(0,2,"VRight:");
		LCD5110_Write_Num(42,2,EncoderRight);
		if(EncoderRight<10)
			LCD5110_write_english_string(48,2,"   ");
		else if(EncoderRight<100)
			LCD5110_write_english_string(54,2,"  ");
	}
	else
	{
		LCD5110_write_english_string(0,2,"VRight:-");
		LCD5110_Write_Num(48,2,-EncoderRight);
		if(EncoderRight>-10)
			LCD5110_write_english_string(54,2,"   ");
		else if(EncoderRight>-100)
			LCD5110_write_english_string(60,2,"  ");
	}
#endif
}

void main_window_proc(void)
{
    uint8_t i=0;
    switch (KeyValue)
    {
      case 0x01:        //上下选择键
        {
            KeyMenuTable[keymenu_curr_state].MenuSubstate++;
            if (KeyMenuTable[keymenu_curr_state].MenuSubstate > (MAIN_MENU_LEN-1))
                    KeyMenuTable[keymenu_curr_state].MenuSubstate = 0;
        }
        break;
      case 0x02:       //确认键
        {
            keymenu_curr_state = KeyMenuTable[keymenu_curr_state].MenuSubstate+1;
            KeyMenuTable[keymenu_curr_state].MenuSetup = 0;
            LCD5110_clear();
        }
        break;
      case 0x04:      //返回键
        {
            //keymenu_curr_state = KeyMenuTable[keymenu_curr_state].KeyEscState;
        }
        break;
      default:
        {
			Show_Debug();
			#if !Show_Debug_Info
            for(i=0;i<MAIN_MENU_LEN;i++)
            {
              LCD5110_write_english_string(6,i+1,MainMenuStrings[i]);
            }
            for (i=0; i<MAIN_MENU_LEN; i++)
            {
              if (KeyMenuTable[keymenu_curr_state].MenuSubstate == i)
                    LCD5110_write_english_string(0,i+1,">");
              else
                    LCD5110_write_english_string(0,i+1," ");
            }
			#endif
        }
        break;
    }
    KeyValue=0;
}

void run_window_proc(void)
{
    uint8_t i=0;
    switch (KeyValue)
    {
      case 0x01:
        {
            //该窗口下只有一个项目,什么也不做
        }
        break;
      case 0x02:
        {
            LCD5110_clear();
            for(i=0;i<3;i++)
            {
                LCD5110_write_english_string(0,i,"Good Luck!!!");
            }
        }
        break;
      case 0x04:
        {
            keymenu_curr_state = KeyMenuTable[keymenu_curr_state].KeyEscState;
            KeyMenuTable[keymenu_curr_state].MenuSetup = 0;
            LCD5110_clear();
        }
        break;
      default:
        {
            for(i=0;i<RUN_MENU_LEN;i++)
            {
              LCD5110_write_english_string(6,i+1,MainMenuStrings[i]);
            }
            for (i=0; i<RUN_MENU_LEN; i++)
            {
              if (KeyMenuTable[keymenu_curr_state].MenuSubstate == i)
                    LCD5110_write_english_string(0,i,">");
              else
                    LCD5110_write_english_string(0,i," ");
            }
        }
        break;
    }
}

void image_debug_proc(void)
{
    
}

void speed_window_proc(void)
{
    uint8_t i=0;
    switch (KeyValue)
    {
      case 0x01:
        {
            if (0 == KeyMenuTable[keymenu_curr_state].MenuSetup)
            {
                KeyMenuTable[keymenu_curr_state].MenuSubstate++;
                if (KeyMenuTable[keymenu_curr_state].MenuSubstate > (SPEED_MENU_LEN-1))
                    KeyMenuTable[keymenu_curr_state].MenuSubstate = 0;
            }
            else
            {
                if (SpeedParam[KeyMenuTable[keymenu_curr_state].MenuSubstate] < SpeedParamMax[KeyMenuTable[keymenu_curr_state].MenuSubstate] )
                {
                    SpeedParam[KeyMenuTable[keymenu_curr_state].MenuSubstate] += SpeedParamAdj[KeyMenuTable[keymenu_curr_state].MenuSubstate];
                }
                else
                {
                    LCD5110_clear();
                    SpeedParam[KeyMenuTable[keymenu_curr_state].MenuSubstate] = SpeedParamMin[KeyMenuTable[keymenu_curr_state].MenuSubstate];
                }       
            }                   
        }
        break;
      case 0x02:
        {
            KeyMenuTable[keymenu_curr_state].MenuSetup = !KeyMenuTable[keymenu_curr_state].MenuSetup;
        }
        break;
      case 0x04:
        {
            keymenu_curr_state = KeyMenuTable[keymenu_curr_state].KeyEscState;
            KeyMenuTable[keymenu_curr_state].MenuSetup = 0;
            LCD5110_clear();
        }
        break;
      default:
        {
            for(i=0;i<SPEED_MENU_LEN;i++)
            {
              LCD5110_write_english_string(6,i,SpeedPIDMenuStrings[i]);
              LCD5110_Write_Num(60,i,SpeedParam[i]);
            }
            for (i=0; i<SPEED_MENU_LEN; i++)
            {
              if (KeyMenuTable[keymenu_curr_state].MenuSubstate == i)
              {
                  if (0 == KeyMenuTable[keymenu_curr_state].MenuSetup)
                      LCD5110_write_english_string(0,i,">");
                  else
                      LCD5110_write_english_string(0,i,"*");
              }
              else
                  LCD5110_write_english_string(0,i," ");
            }
        }
        break;
    }
    KeyValue=0;
}

void direction_window_proc(void)
{
    
}

void display_proc(void)
{
	//LCD5110_clear();
    KeyMenuTable[keymenu_curr_state].WindowProc();
}

/*----------------------------------按键部分-------------------------------------*/
/*uint32_t time=0;
uint8_t KeyFlag=0;
uint32_t fac_us;
static void PORTB_Isr(uint32_t pinx)
{
    //GPIO_ToggleBit(HW_GPIOB,11);
    if(pinx &(1<<10))
    {
        if(GPIO_ReadBit(HW_GPIOB,10))
        {
            PIT_ResetCounter(HW_PIT_CH0);
        }
        else
        {
            time=1000*1000*10-PIT_GetCounterValue(HW_PIT_CH0)/fac_us;
            KeyFlag=1;
        }
    }
}

void init_kbd(void)
{
    GPIO_QuickInit(HW_GPIOB,10,kGPIO_Mode_IFT);
    GPIO_ITDMAConfig(HW_GPIOB,10,kGPIO_IT_RisingFallingEdge,true);
    GPIO_CallbackInstall(HW_GPIOB,PORTB_Isr);
    PIT_QuickInit(HW_PIT_CH0,1000*1000*10);
    fac_us = GetClock(kBusClock);
    fac_us /= 1000000;
}

void keyboard_scan(void)
{
    if(KeyFlag==1)
    {
        KeyFlag=0;
        if(time<1000*1000*1)
            KeyValue=0x01;
        else if(time<1000*1000*2)
            KeyValue=0x02;
        else
            KeyValue=0x04;
        LCD5110_write_english_string(0,5,"KeyValue=");
        LCD5110_Write_Num(54,5,KeyValue);
    }
}
*/



