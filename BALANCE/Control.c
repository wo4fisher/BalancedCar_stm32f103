#include "Control.h"

int16_t BalancePwm;
int16_t MotorL=0,MotorR=0;

/*--------------直立控制-----------------------*/
float AngleBias=0,AngleBiasLast=0,GyroBias=0,GyroBiasLast=0,GyroBiasIntegral=0;
float AngleKp=0,AngleKd=0,GyroKp=0,GyroKi=0,GyroKd=0;
#define CascadePid 0
float AimAngle=6.5;
int16_t Balance_Control(float Angle,float Gyro)
{   
	float AimGyro=0;
	int16_t balance;
	//角度环
	AngleBias=AimAngle-Angle;       //===求出平衡的角度中值 和机械相关
#if CascadePid
	AimGyro=AngleKp*AngleBias+AngleKd*(AngleBias-AngleBiasLast);   //===计算平衡控制的电机PWM  PD控制   kp是P系数 kd是D系数 
	//角速度环
	GyroBias=AimGyro-Gyro;
	GyroBiasIntegral+=GyroBias;
	if(GyroBiasIntegral>10000)    //积分限幅
		GyroBiasIntegral=10000;
	if(GyroBiasIntegral<-10000)
		GyroBiasIntegral=-10000;
	balance=GyroKp*GyroBias+GyroKi*GyroBiasIntegral+GyroKd*(GyroBias-GyroBiasLast);
	//赋值给变量
	AngleBiasLast=AngleBias,GyroBias=GyroBiasLast;
#else
	AngleKp=-360,AngleKd=36;
	balance=AngleKp*AngleBias+AngleKd*Gyro;
#endif
	return balance;
}

#define DIFFERENCE 18
void Xianfu_Pwm(void)
{	
	  int Amplitude=6900;    //===PWM满幅是7200 限制在6900
	  MotorL+=DIFFERENCE;  //DIFFERENCE是一个衡量平衡小车电机和机械安装差异的一个变量。直接作用于输出，让小车具有更好的一致性。
	  MotorR-=DIFFERENCE;
    if(MotorL<-Amplitude) MotorL=-Amplitude;	
		if(MotorL>Amplitude)  MotorL=Amplitude;	
	  if(MotorR<-Amplitude) MotorR=-Amplitude;	
		if(MotorR>Amplitude)  MotorR=Amplitude;		
	
}

void Set_Pwm(int16_t ml,int16_t mr)
{
	if(mr>0)			PWMRB=0,			PWMRF=1100+mr;  //右轮
	else 	          PWMRB=1100-mr,			PWMRF=0;
	if(ml>0)	PWMLB=0,			PWMLF=1100+ml;
	else        PWMLB=1100-ml,			PWMLF=0;	
}

void Car_Control(void)
{
	BalancePwm=Balance_Control(RTAngle,RTGyro);
	MotorL=BalancePwm;
	MotorR=BalancePwm;
	Xianfu_Pwm();
	Set_Pwm(MotorL,MotorR);
}
