#include "control.h"	
#include "filter.h"	
  /**************************************************************************
×÷Õß£ºÆ½ºâÐ¡³µÖ®¼Ò
ÎÒµÄÌÔ±¦Ð¡µê£ºhttp://shop114407458.taobao.com/
**************************************************************************/

void vcan_sendware(u8 *wareaddr, u32 waresize)
{
#define CMD_WARE     3
    u8 cmdf[2] = {CMD_WARE, ~CMD_WARE};    
    u8 cmdr[2] = {~CMD_WARE, CMD_WARE};   

    usart1_sendbuff(cmdf, sizeof(cmdf));    

    usart1_sendbuff(wareaddr, waresize); 

    usart1_sendbuff(cmdr, sizeof(cmdr));    
}

int Balance_Pwm=0,Velocity_Pwm=0,Turn_Pwm=0;
u8 Flag_Target;
/**************************************************************************
º¯Êý¹¦ÄÜ£ºËùÓÐµÄ¿ØÖÆ´úÂë¶¼ÔÚÕâÀïÃæ
         5ms¶¨Ê±ÖÐ¶ÏÓÉMPU6050µÄINTÒý½Å´¥·¢
         ÑÏ¸ñ±£Ö¤²ÉÑùºÍÊý¾Ý´¦ÀíµÄÊ±¼äÍ¬²½				 
**************************************************************************/
int EXTI9_5_IRQHandler(void) 
{    
	 //if(PBin(5)==0)		
	//{   
		//printf("exti9\n");
		  //EXTI->PR=1<<5;                                                      //Çå³ýLINE5ÉÏµÄÖÐ¶Ï±êÖ¾Î»   
		  Flag_Target=!Flag_Target;
		  /*if(delay_flag==1)
			 {
				 if(++delay_50==100)	 delay_50=0,delay_flag=0;                     //¸øÖ÷º¯ÊýÌá¹©50msµÄ¾«×¼ÑÓÊ±
			 }*/
		    if(Flag_Target==1)                                                  //5ms¶ÁÈ¡Ò»´ÎÍÓÂÝÒÇºÍ¼ÓËÙ¶È¼ÆµÄÖµ£¬¸ü¸ßµÄ²ÉÑùÆµÂÊ¿ÉÒÔ¸ÄÉÆ¿¨¶ûÂüÂË²¨ºÍ»¥²¹ÂË²¨µÄÐ§¹û
			{
				Get_Angle(Way_Angle);                                               //===¸üÐÂ×ËÌ¬	
				return 0;	                                               
			}                                                                   //10ms¿ØÖÆÒ»´Î£¬ÎªÁË±£Ö¤M·¨²âËÙµÄÊ±¼ä»ù×¼£¬Ê×ÏÈ¶ÁÈ¡±àÂëÆ÷Êý¾Ý
			Get_Angle(Way_Angle);
			Encoder_Left=-Read_Encoder(4);                                      //===¶ÁÈ¡±àÂëÆ÷µÄÖµ£¬ÒòÎªÁ½¸öµç»úµÄÐý×ªÁË180¶ÈµÄ£¬ËùÒÔ¶ÔÆäÖÐÒ»¸öÈ¡·´£¬±£Ö¤Êä³ö¼«ÐÔÒ»ÖÂ
			Encoder_Right=Read_Encoder(2);                                      //===¶ÁÈ¡±àÂëÆ÷µÄÖµ
	  	//Get_Angle(Way_Angle);                                               //===¸üÐÂ×ËÌ¬	
			//Read_Distane();                                                     //===»ñÈ¡³¬Éù²¨²âÁ¿¾àÀëÖµ
  		//if(Bi_zhang==0)Led_Flash(100);                                      //===LEDÉÁË¸;³£¹æÄ£Ê½ 1s¸Ä±äÒ»´ÎÖ¸Ê¾µÆµÄ×´Ì¬	
			//if(Bi_zhang==1)Led_Flash(0);                                        //===LEDÉÁË¸;±ÜÕÏÄ£Ê½ Ö¸Ê¾µÆ³£ÁÁ	
  		//Voltage=Get_battery_volt();                                         //===»ñÈ¡µç³ØµçÑ¹	          
			//Key();                                                              //===É¨Ãè°´¼ü×´Ì¬ µ¥»÷Ë«»÷¿ÉÒÔ¸Ä±äÐ¡³µÔËÐÐ×´Ì¬
 			//velocity(Encoder_Left,Encoder_Right);                  //===ËÙ¶È»·PID¿ØÖÆ	 ¼Ç×¡£¬ËÙ¶È·´À¡ÊÇÕý·´À¡£¬¾ÍÊÇÐ¡³µ¿ìµÄÊ±ºòÒªÂýÏÂÀ´¾ÍÐèÒªÔÙÅÜ¿ìÒ»µ
			Balance_Pwm =balance(Angle_Balance,Gyro_Balance);                   //===Æ½ºâPID¿ØÖÆ	
 	    //Turn_Pwm    =turn(Encoder_Left,Encoder_Right,Gyro_Turn);            //===×ªÏò»·PID¿ØÖÆ     
 		  Moto1=Balance_Pwm-Velocity_Pwm+Turn_Pwm;                            //===¼ÆËã×óÂÖµç»ú×îÖÕPWM
 	  	  Moto2=Balance_Pwm-Velocity_Pwm-Turn_Pwm;                            //===¼ÆËãÓÒÂÖµç»ú×îÖÕPWM
   		  Xianfu_Pwm();                                                       //===PWMÏÞ·ù
			//if(Pick_Up(Acceleration_Z,Angle_Balance,Encoder_Left,Encoder_Right))//===¼ì²éÊÇ·ñÐ¡³µ±»ÄÇÆð
			//Flag_Stop=1;	                                                      //===Èç¹û±»ÄÃÆð¾Í¹Ø±Õµç»ú
			//if(Put_Down(Angle_Balance,Encoder_Left,Encoder_Right))              //===¼ì²éÊÇ·ñÐ¡³µ±»·ÅÏÂ
			//Flag_Stop=0;	                                                      //===Èç¹û±»·ÅÏÂ¾ÍÆô¶¯µç»ú
      //if(Turn_Off(Angle_Balance,Voltage)==0)                              //===Èç¹û²»´æÔÚÒì³£
 			Set_Pwm(Moto1,Moto2);                                               //===¸³Öµ¸øPWM¼Ä´æÆ÷  
	//}       	
	 return 0;	  
} 

/**************************************************************************
º¯Êý¹¦ÄÜ£ºÖ±Á¢PD¿ØÖÆ
Èë¿Ú²ÎÊý£º½Ç¶È¡¢½ÇËÙ¶È
·µ»Ø  Öµ£ºÖ±Á¢¿ØÖÆPWM
×÷    Õß£ºÆ½ºâÐ¡³µÖ®¼Ò
**************************************************************************/
float AngleBias=0,AngleBiasLast=0,GyroBias=0,GyroBiasLast=0,GyroBiasIntegral=0;
float AngleKp=-12,AngleKd=-40,GyroKp=-4,GyroKi=-0.8,GyroKd=-0.2;
#define CascadePid 1
float AimAngle=-1.5;
int balance(float Angle,float Gyro)
{   
	float AimGyro=0;
	int balance;
	//½Ç¶È»·
	AngleBias=AimAngle-Angle;       //===Çó³öÆ½ºâµÄ½Ç¶ÈÖÐÖµ ºÍ»úÐµÏà¹Ø
#if CascadePid
	AimGyro=AngleKp*AngleBias+AngleKd*(AngleBias-AngleBiasLast);   //===¼ÆËãÆ½ºâ¿ØÖÆµÄµç»úPWM  PD¿ØÖÆ   kpÊÇPÏµÊý kdÊÇDÏµÊý 
	//½ÇËÙ¶È»·
	GyroBias=AimGyro-Gyro;
	GyroBiasIntegral+=GyroBias;
	if(GyroBiasIntegral>10000)    //»ý·ÖÏÞ·ù
		GyroBiasIntegral=10000;
	if(GyroBiasIntegral<-10000)
		GyroBiasIntegral=-10000;
	balance=GyroKp*GyroBias+GyroKi*GyroBiasIntegral+GyroKd*(GyroBias-GyroBiasLast);
	//¸³Öµ¸ø±äÁ¿
	AngleBiasLast=AngleBias,GyroBias=GyroBiasLast;
#else
	balance=320*AngleBias+1.5*Gyro;
#endif
	return balance;
}

/**************************************************************************
º¯Êý¹¦ÄÜ£ºËÙ¶ÈPI¿ØÖÆ ÐÞ¸ÄÇ°½øºóÍËËÙ¶È£¬ÇëÐÞTarget_Velocity£¬±ÈÈç£¬¸Ä³É60¾Í±È½ÏÂýÁË
Èë¿Ú²ÎÊý£º×óÂÖ±àÂëÆ÷¡¢ÓÒÂÖ±àÂëÆ÷
·µ»Ø  Öµ£ºËÙ¶È¿ØÖÆPWM
×÷    Õß£ºÆ½ºâÐ¡³µÖ®¼Ò
**************************************************************************/
void velocity(int encoder_left,int encoder_right)
{  
     static float Encoder_Least,Encoder,Movement;
	  static float Encoder_Integral,Target_Velocity=0;
	  float kp=0,ki=0;//d=0.31
	  //=============Ò£¿ØÇ°½øºóÍË²¿·Ö=======================// 
	  //if(Bi_zhang==1&&Flag_sudu==1)  Target_Velocity=45;                 //Èç¹û½øÈë±ÜÕÏÄ£Ê½,×Ô¶¯½øÈëµÍËÙÄ£Ê½
    //else 	                         Target_Velocity=110;                 
		if(1==Flag_Qian)    	Movement=Target_Velocity/Flag_sudu;	         //===Ç°½ø±êÖ¾Î»ÖÃ1 
		else if(1==Flag_Hou)	Movement=-Target_Velocity/Flag_sudu;         //===ºóÍË±êÖ¾Î»ÖÃ1
	  else  Movement=0;	
	  //if(Bi_zhang==1&&Distance<500&&Flag_Left!=1&&Flag_Right!=1)        //±ÜÕÏ±êÖ¾Î»ÖÃ1ÇÒ·ÇÒ£¿Ø×ªÍäµÄÊ±ºò£¬½øÈë±ÜÕÏÄ£Ê½
	  //Movement=-Target_Velocity/Flag_sudu;
   //=============ËÙ¶ÈPI¿ØÖÆÆ÷=======================//	
	Encoder_Least =(Encoder_Left+Encoder_Right)-0;                    //===»ñÈ¡×îÐÂËÙ¶ÈÆ«²î==²âÁ¿ËÙ¶È£¨×óÓÒ±àÂëÆ÷Ö®ºÍ£©-Ä¿±êËÙ¶È£¨´Ë´¦ÎªÁã£© 
	Encoder *= 0.8;		                                                //===Ò»½×µÍÍ¨ÂË²¨Æ÷       
	Encoder += Encoder_Least*0.2;	                                    //===Ò»½×µÍÍ¨ÂË²¨Æ÷    
	//if(Encoder_Least>0) LED=1;
	//else LED=0;
	Encoder_Integral +=Encoder;                                       //===»ý·Ö³öÎ»ÒÆ »ý·ÖÊ±¼ä£º10ms
	//Encoder_Integral=Encoder_Integral-Movement;                       //===½ÓÊÕÒ£¿ØÆ÷Êý¾Ý£¬¿ØÖÆÇ°½øºóÍË
	if(Encoder_Integral>10000)  	Encoder_Integral=10000;             //===»ý·ÖÏÞ·ù
	if(Encoder_Integral<-10000)	Encoder_Integral=-10000;              //===»ý·ÖÏÞ·ù	
	AimAngle=Encoder*kp+Encoder_Integral*ki;                          //===ËÙ¶È¿ØÖÆ	
	if(Turn_Off(Angle_Balance,Voltage)==1||Flag_Stop==1)   Encoder_Integral=0;      //===µç»ú¹Ø±ÕºóÇå³ý»ý·Ö
}

/**************************************************************************
º¯Êý¹¦ÄÜ£º×ªÏò¿ØÖÆ  ÐÞ¸Ä×ªÏòËÙ¶È£¬ÇëÐÞ¸ÄTurn_Amplitude¼´¿É
Èë¿Ú²ÎÊý£º×óÂÖ±àÂëÆ÷¡¢ÓÒÂÖ±àÂëÆ÷¡¢ZÖáÍÓÂÝÒÇ
·µ»Ø  Öµ£º×ªÏò¿ØÖÆPWM
×÷    Õß£ºÆ½ºâÐ¡³µÖ®¼Ò
**************************************************************************/
int turn(int encoder_left,int encoder_right,float gyro)//×ªÏò¿ØÖÆ
{
	 static float Turn_Target,Turn,Encoder_temp,Turn_Convert=0.9,Turn_Count;
	  float Turn_Amplitude=88/Flag_sudu,Kp=42,Kd=0;     
	  //=============Ò£¿Ø×óÓÒÐý×ª²¿·Ö=======================//
  	if(1==Flag_Left||1==Flag_Right)                      //ÕâÒ»²¿·ÖÖ÷ÒªÊÇ¸ù¾ÝÐý×ªÇ°µÄËÙ¶Èµ÷ÕûËÙ¶ÈµÄÆðÊ¼ËÙ¶È£¬Ôö¼ÓÐ¡³µµÄÊÊÓ¦ÐÔ
		{
			if(++Turn_Count==1)
			Encoder_temp=myabs(encoder_left+encoder_right);
			Turn_Convert=50/Encoder_temp;
			if(Turn_Convert<0.6)Turn_Convert=0.6;
			if(Turn_Convert>3)Turn_Convert=3;
		}	
	  else
		{
			Turn_Convert=0.9;
			Turn_Count=0;
			Encoder_temp=0;
		}			
		if(1==Flag_Left)	           Turn_Target-=Turn_Convert;
		else if(1==Flag_Right)	     Turn_Target+=Turn_Convert; 
		else Turn_Target=0;
    if(Turn_Target>Turn_Amplitude)  Turn_Target=Turn_Amplitude;    //===×ªÏòËÙ¶ÈÏÞ·ù
	  if(Turn_Target<-Turn_Amplitude) Turn_Target=-Turn_Amplitude;
		if(Flag_Qian==1||Flag_Hou==1)  Kd=0.5;        
		else Kd=0;   //×ªÏòµÄÊ±ºòÈ¡ÏûÍÓÂÝÒÇµÄ¾ÀÕý ÓÐµãÄ£ºýPIDµÄË¼Ïë
  	//=============×ªÏòPD¿ØÖÆÆ÷=======================//
		Turn=-Turn_Target*Kp -gyro*Kd;                 //===½áºÏZÖáÍÓÂÝÒÇ½øÐÐPD¿ØÖÆ
	  return Turn;
}

/**************************************************************************
º¯Êý¹¦ÄÜ£º¸³Öµ¸øPWM¼Ä´æÆ÷
Èë¿Ú²ÎÊý£º×óÂÖPWM¡¢ÓÒÂÖPWM
·µ»Ø  Öµ£ºÎÞ
**************************************************************************/
void Set_Pwm(int moto1,int moto2)
{
	if(moto1>0)			PWMRB=0,			PWMRF=1100+moto1;  //ÓÒÂÖ
	else 	          PWMRB=1100-moto1,			PWMRF=0;
	if(moto2>0)	PWMLB=0,			PWMLF=1100+moto2;
	else        PWMLB=1100-moto2,			PWMLF=0;	
}

/**************************************************************************
º¯Êý¹¦ÄÜ£ºÏÞÖÆPWM¸³Öµ 
Èë¿Ú²ÎÊý£ºÎÞ
·µ»Ø  Öµ£ºÎÞ
**************************************************************************/
void Xianfu_Pwm(void)
{	
	  int Amplitude=6900;    //===PWMÂú·ùÊÇ7200 ÏÞÖÆÔÚ6900
	  if(Flag_Qian==1)  Moto1-=DIFFERENCE;  //DIFFERENCEÊÇÒ»¸öºâÁ¿Æ½ºâÐ¡³µµç»úºÍ»úÐµ°²×°²îÒìµÄÒ»¸ö±äÁ¿¡£Ö±½Ó×÷ÓÃÓÚÊä³ö£¬ÈÃÐ¡³µ¾ßÓÐ¸üºÃµÄÒ»ÖÂÐÔ¡£
	  if(Flag_Hou==1)   Moto2+=DIFFERENCE;
    if(Moto1<-Amplitude) Moto1=-Amplitude;	
		if(Moto1>Amplitude)  Moto1=Amplitude;	
	  if(Moto2<-Amplitude) Moto2=-Amplitude;	
		if(Moto2>Amplitude)  Moto2=Amplitude;		
	
}
/**************************************************************************
º¯Êý¹¦ÄÜ£º°´¼üÐÞ¸ÄÐ¡³µÔËÐÐ×´Ì¬ 
Èë¿Ú²ÎÊý£ºÎÞ
·µ»Ø  Öµ£ºÎÞ
**************************************************************************/
void Key(void)
{	
	u8 tmp,tmp2;
	tmp=click_N_Double(50); 
	if(tmp==1)Flag_Stop=!Flag_Stop;//µ¥»÷¿ØÖÆÐ¡³µµÄÆôÍ£
	if(tmp==2)Flag_Show=!Flag_Show;//Ë«»÷¿ØÖÆÐ¡³µµÄÏÔÊ¾×´Ì¬
	tmp2=Long_Press();                   
  if(tmp2==1) Bi_zhang=!Bi_zhang;		//³¤°´¿ØÖÆÐ¡³µÊÇ·ñ½øÈë³¬Éù²¨±ÜÕÏÄ£Ê½ 
}

/**************************************************************************
º¯Êý¹¦ÄÜ£ºÒì³£¹Ø±Õµç»ú
Èë¿Ú²ÎÊý£ºÇã½ÇºÍµçÑ¹
·µ»Ø  Öµ£º1£ºÒì³£  0£ºÕý³£
**************************************************************************/
u8 Turn_Off(float angle, int voltage)
{
	    u8 temp;
			if(angle<-40||angle>40||1==Flag_Stop||voltage<1110)//µç³ØµçÑ¹µÍÓÚ11.1V¹Ø±Õµç»ú
			{	                                                 //===Çã½Ç´óÓÚ40¶È¹Ø±Õµç»ú
      temp=1;                                            //===Flag_StopÖÃ1¹Ø±Õµç»ú
			/*AIN1=0;                                            
			AIN2=0;
			BIN1=0;
			BIN2=0;*/
      }
			else
      temp=0;
      return temp;			
}
	
/**************************************************************************
º¯Êý¹¦ÄÜ£º»ñÈ¡½Ç¶È ÈýÖÖËã·¨¾­¹ýÎÒÃÇµÄµ÷Ð££¬¶¼·Ç³£ÀíÏë 
Èë¿Ú²ÎÊý£º»ñÈ¡½Ç¶ÈµÄËã·¨ 1£ºDMP  2£º¿¨¶ûÂü 3£º»¥²¹ÂË²¨
·µ»Ø  Öµ£ºÎÞ
**************************************************************************/
#define Rgyro 0.36f
int8_t angleArr[2]={0};
void Get_Angle(u8 way)
{ 
	float Accel_Y,Accel_X,Accel_Z,Gyro_Y,Gyro_Z;
	Temperature=Read_Temperature();      //===¶ÁÈ¡MPU6050ÄÚÖÃÎÂ¶È´«¸ÐÆ÷Êý¾Ý£¬½üËÆ±íÊ¾Ö÷°åÎÂ¶È¡£
	if(way==1)                           //===DMPµÄ¶ÁÈ¡ÔÚÊý¾Ý²É¼¯ÖÐ¶ÏÌáÐÑµÄÊ±ºò£¬ÑÏ¸ñ×ñÑ­Ê±ÐòÒªÇó
	{	
			Read_DMP();                      //===¶ÁÈ¡¼ÓËÙ¶È¡¢½ÇËÙ¶È¡¢Çã½Ç
			Angle_Balance=Pitch;             //===¸üÐÂÆ½ºâÇã½Ç
			Gyro_Balance=gyro[1];            //===¸üÐÂÆ½ºâ½ÇËÙ¶È
			Gyro_Turn=gyro[2];               //===¸üÐÂ×ªÏò½ÇËÙ¶È
		  Acceleration_Z=accel[2];         //===¸üÐÂZÖá¼ÓËÙ¶È¼Æ
	}			
	else
	{
		/****ÓÉÓÚ6050°²×°·½Ïò²»Ò»Ñù£¬ËùÒÔÐÞ¸ÄÁË¶ÁÊý********/
		Gyro_Y=(I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_XOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_XOUT_L);    //¶ÁÈ¡YÖáÍÓÂÝÒÇ
		Gyro_Z=(I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_ZOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_ZOUT_L);    //¶ÁÈ¡ZÖáÍÓÂÝÒÇ
		Accel_X=(I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_YOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_YOUT_L); //¶ÁÈ¡XÖá¼ÓËÙ¶È¼Æ
		Accel_Z=(I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_ZOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_ZOUT_L); //¶ÁÈ¡ZÖá¼ÓËÙ¶È¼Æ
		if(Gyro_Y>32768)  Gyro_Y-=65536;                       //Êý¾ÝÀàÐÍ×ª»»  Ò²¿ÉÍ¨¹ýshortÇ¿ÖÆÀàÐÍ×ª»»
		if(Gyro_Z>32768)  Gyro_Z-=65536;                       //Êý¾ÝÀàÐÍ×ª»»
		if(Accel_X>32768) Accel_X-=65536;                      //Êý¾ÝÀàÐÍ×ª»»
		if(Accel_Z>32768) Accel_Z-=65536;                      //Êý¾ÝÀàÐÍ×ª»»
		Accel_Y=atan2(Accel_X,Accel_Z)*180/PI;                 //¼ÆËãÇã½Ç	
		//printf("Accel_Y=%.0f\n",Accel_Y);
		Gyro_Y=Gyro_Y/16.4*Rgyro;                                    //ÍÓÂÝÒÇÁ¿³Ì×ª»»	
		if(Way_Angle==2)		  	Kalman_Filter(Accel_Y,Gyro_Y);//¿¨¶ûÂüÂË²¨	
		else if(Way_Angle==3)   Yijielvbo(Accel_Y,-Gyro_Y);    //»¥²¹ÂË²¨
		Angle_Balance=angle;                                   //¸üÐÂÆ½ºâÇã½Ç
		Gyro_Balance=-Gyro_Y;                                  //¸üÐÂÆ½ºâ½ÇËÙ
		//angleArr[0]=(int8_t)Accel_Y,angleArr[1]=(int8_t)angle;
		//vcan_sendware((u8 *)angleArr,2);
		Gyro_Turn=Gyro_Z;                                      //¸üÐÂ×ªÏò½ÇËÙ¶È
		Acceleration_Z=Accel_Z;                                //===¸üÐÂZÖá¼ÓËÙ¶È¼Æ	
	}
}
/**************************************************************************
º¯Êý¹¦ÄÜ£º¾ø¶ÔÖµº¯Êý
Èë¿Ú²ÎÊý£ºint
·µ»Ø  Öµ£ºunsigned int
**************************************************************************/
int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}
/**************************************************************************
º¯Êý¹¦ÄÜ£º¼ì²âÐ¡³µÊÇ·ñ±»ÄÃÆð
Èë¿Ú²ÎÊý£ºint
·µ»Ø  Öµ£ºunsigned int
**************************************************************************/
int Pick_Up(float Acceleration,float Angle,int encoder_left,int encoder_right)
{ 		   
	 static u16 flag,count0,count1,count2;
	if(flag==0)                                                                   //µÚÒ»²½
	 {
	      if(myabs(encoder_left)+myabs(encoder_right)<30)                         //Ìõ¼þ1£¬Ð¡³µ½Ó½ü¾²Ö¹
				count0++;
        else 
        count0=0;		
        if(count0>10)				
		    flag=1,count0=0; 
	 } 
	 if(flag==1)                                                                  //½øÈëµÚ¶þ²½
	 {
		    if(++count1>200)       count1=0,flag=0;                                 //³¬Ê±²»ÔÙµÈ´ý2000ms
	      if(Acceleration>26000&&(Angle>(-20+ZHONGZHI))&&(Angle<(20+ZHONGZHI)))   //Ìõ¼þ2£¬Ð¡³µÊÇÔÚ0¶È¸½½ü±»ÄÃÆð
		    flag=2; 
	 } 
	 if(flag==2)                                                                  //µÚÈý²½
	 {
		  if(++count2>100)       count2=0,flag=0;                                   //³¬Ê±²»ÔÙµÈ´ý1000ms
	    if(myabs(encoder_left+encoder_right)>135)                                 //Ìõ¼þ3£¬Ð¡³µµÄÂÖÌ¥ÒòÎªÕý·´À¡´ïµ½×î´óµÄ×ªËÙ   
      {
				flag=0;                                                                                     
				return 1;                                                               //¼ì²âµ½Ð¡³µ±»ÄÃÆð
			}
	 }
	return 0;
}
/**************************************************************************
º¯Êý¹¦ÄÜ£º¼ì²âÐ¡³µÊÇ·ñ±»·ÅÏÂ
Èë¿Ú²ÎÊý£ºint
·µ»Ø  Öµ£ºunsigned int
**************************************************************************/
int Put_Down(float Angle,int encoder_left,int encoder_right)
{ 		   
	 static u16 flag,count;	 
	 if(Flag_Stop==0)                           //·ÀÖ¹Îó¼ì      
   return 0;	                 
	 if(flag==0)                                               
	 {
	      if(Angle>(-10+ZHONGZHI)&&Angle<(10+ZHONGZHI)&&encoder_left==0&&encoder_right==0)         //Ìõ¼þ1£¬Ð¡³µÊÇÔÚ0¶È¸½½üµÄ
		    flag=1; 
	 } 
	 if(flag==1)                                               
	 {
		  if(++count>50)                                          //³¬Ê±²»ÔÙµÈ´ý 500ms
		  {
				count=0;flag=0;
		  }
	    if(encoder_left>3&&encoder_right>3&&encoder_left<60&&encoder_right<60)                //Ìõ¼þ2£¬Ð¡³µµÄÂÖÌ¥ÔÚÎ´ÉÏµçµÄÊ±ºò±»ÈËÎª×ª¶¯  
      {
				flag=0;
				flag=0;
				return 1;                                             //¼ì²âµ½Ð¡³µ±»·ÅÏÂ
			}
	 }
	return 0;
}


