#include "Control.h"

int16_t BalancePwm;
int16_t MotorL=0,MotorR=0;

/*--------------ֱ������-----------------------*/
float AngleBias=0,AngleBiasLast=0,GyroBias=0,GyroBiasLast=0,GyroBiasIntegral=0;
float AngleKp=0,AngleKd=0,GyroKp=0,GyroKi=0,GyroKd=0;
#define CascadePid 0
float AimAngle=6.5;
int16_t Balance_Control(float Angle,float Gyro)
{   
	float AimGyro=0;
	int16_t balance;
	//�ǶȻ�
	AngleBias=AimAngle-Angle;       //===���ƽ��ĽǶ���ֵ �ͻ�е���
#if CascadePid
	AimGyro=AngleKp*AngleBias+AngleKd*(AngleBias-AngleBiasLast);   //===����ƽ����Ƶĵ��PWM  PD����   kp��Pϵ�� kd��Dϵ�� 
	//���ٶȻ�
	GyroBias=AimGyro-Gyro;
	GyroBiasIntegral+=GyroBias;
	if(GyroBiasIntegral>10000)    //�����޷�
		GyroBiasIntegral=10000;
	if(GyroBiasIntegral<-10000)
		GyroBiasIntegral=-10000;
	balance=GyroKp*GyroBias+GyroKi*GyroBiasIntegral+GyroKd*(GyroBias-GyroBiasLast);
	//��ֵ������
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
	  int Amplitude=6900;    //===PWM������7200 ������6900
	  MotorL+=DIFFERENCE;  //DIFFERENCE��һ������ƽ��С������ͻ�е��װ�����һ��������ֱ���������������С�����и��õ�һ���ԡ�
	  MotorR-=DIFFERENCE;
    if(MotorL<-Amplitude) MotorL=-Amplitude;	
		if(MotorL>Amplitude)  MotorL=Amplitude;	
	  if(MotorR<-Amplitude) MotorR=-Amplitude;	
		if(MotorR>Amplitude)  MotorR=Amplitude;		
	
}

void Set_Pwm(int16_t ml,int16_t mr)
{
	if(mr>0)			PWMRB=0,			PWMRF=1100+mr;  //����
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
