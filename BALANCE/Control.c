#include "Control.h"

int EncoderLeft=0,EncoderRight=0;
int16_t BalancePwm,VelocityPwm;
int16_t MotorL=0,MotorR=0;

/*--------------ֱ������-----------------------*/
float AngleBias=0,AngleBiasLast=0,AngleBiasIntegral=0,GyroBias=0,GyroBiasLast=0,GyroBiasIntegral=0;
float AngleKp=4,AngleKi=0.5,AngleKd=0,GyroKp=-36,GyroKi=-4.2,GyroKd=14;
//float AngleKp=0,AngleKi=0,AngleKd=0,GyroKp=0,GyroKi=0,GyroKd=0;
#define CascadePid 0
float BalabceAngle=6.2; 
int16_t Balance_Control(float Angle,float Gyro)
{   
	float AimGyro=0;
	int16_t balance;
	//�ǶȻ�
	AngleBias=VelocityPwm-Angle;       //===���ƽ��ĽǶ���ֵ �ͻ�е���
	AngleBiasIntegral+=AngleBias;
	if(AngleBiasIntegral>1000)    //�����޷�
		AngleBiasIntegral=1000;
	if(AngleBiasIntegral<-1000)
		AngleBiasIntegral=-1000;
#if CascadePid
	AimGyro=AngleKp*AngleBias+AngleKi*AngleBiasIntegral+AngleKd*(AngleBias-AngleBiasLast);   //===����ƽ����Ƶĵ��PWM  PD����   kp��Pϵ�� kd��Dϵ�� 
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
	AngleKp=-270,AngleKi=0,AngleKd=30;
	balance=AngleKp*AngleBias+AngleKi*AngleBiasIntegral+AngleKd*Gyro;
#endif
	return balance;
}

int AimSpeed=0,EncoderBias,EncoderBiasIntegral;
//float VelocityKp=0.004,VelocityKi=0.0005;
float VelocityKp=0,VelocityKi=0;
int velocity(int encoder_left,int encoder_right)
{
	float Velocity=0,EncoderTotal=0;
	EncoderTotal=encoder_left + encoder_right;
	EncoderBias=EncoderTotal-AimSpeed;
	EncoderBiasIntegral+=EncoderBias;
	if(EncoderBiasIntegral>10000)
		EncoderBiasIntegral=10000;
	if(EncoderBiasIntegral<-10000)
		EncoderBiasIntegral=-10000;
	Velocity=VelocityKp*EncoderBias+VelocityKi*EncoderBiasIntegral;
	return Velocity+BalabceAngle;
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
	EncoderLeft=-Read_Encoder(EncoderLeftTim);
	EncoderRight=Read_Encoder(EncoderRightTim);
	VelocityPwm=velocity(EncoderLeft,EncoderRight);
	BalancePwm=Balance_Control(RTAngle,RTGyro);
	MotorL=BalancePwm;
	MotorR=BalancePwm;
	Xianfu_Pwm();
	Set_Pwm(MotorL,MotorR);
}
