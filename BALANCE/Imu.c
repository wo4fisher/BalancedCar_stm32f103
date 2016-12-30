#include "Imu.h"

float RTAngle,RTGyro;
float AngleAccelXZ;
int8_t SendArr[3]={0};
void Get_RT_Att(void)
{
	Get_MPUdata();
	//获取由加速度计算出的角度
	AngleAccelXZ=atan2(accel_Xdata_raw,accel_Zdata_raw)*180/PI;
	if(AngleAccelXZ>90)
		AngleAccelXZ=90.00;
	if(AngleAccelXZ<-90)
		AngleAccelXZ=-90.00;
	Kalman_Filter(AngleAccelXZ,-gyro_Ydata_raw);
	//SendArr[0]=(int8_t)AngleAccelXZ,SendArr[1]=(int8_t)RTAngle,SendArr[2]=(int8_t)RTGyro;
	//vcan_sendware((u8 *)SendArr,2);
}

/*---------------卡尔曼滤波--------------------*/
#define Q_angle    0.00000005
#define Q_gyro	   0.00000001
#define R_angle    0.0001
#define dt         0.005
#define Rgyro   0.505f

static float P[2][2] = {
    { 0.5, 0 },
    { 0, 0.5 }
};
static float Pdot[4] ={0,0,0,0};
static double q_bias=0, angle_err, PCt_0, PCt_1, E, K_0, K_1, t_0, t_1;
void Kalman_Filter(float angleACC, int16_t gyro)
{
	float gyro_m;
	gyro_m=gyro/32768.0f*GYRO_SCALE;
	RTAngle+=(gyro_m-q_bias) * dt;           	

    Pdot[0]=Q_angle - P[0][1] - P[1][0];  
    Pdot[1]=0- P[1][1];
    Pdot[2]=0- P[1][1];
    Pdot[3]=Q_gyro;

    P[0][0] += Pdot[0] * dt;			
    P[0][1] += Pdot[1] * dt;
    P[1][0] += Pdot[2] * dt;
    P[1][1] += Pdot[3] * dt;

    angle_err = angleACC - RTAngle;		

    PCt_0 = P[0][0];//C_0 * P[0][0];
    PCt_1 = P[1][0];//C_0 * P[1][0];

    E = R_angle + PCt_0;//C_0 * PCt_0;

    K_0 = PCt_0 / E;
    K_1 = PCt_1 / E;

    t_0 = PCt_0;
    t_1 = P[0][1];//C_0 * P[0][1];

    P[0][0] -= K_0 * t_0;		
    P[0][1] -= K_0 * t_1;
    P[1][0] -= K_1 * t_0;
    P[1][1] -= K_1 * t_1;

    RTAngle+= K_0 * angle_err;
    q_bias+= K_1 * angle_err;      		
    RTGyro=(gyro_m-q_bias);
}
/*---------------卡尔曼滤波--------------------*/

void vcan_sendware(u8 *wareaddr, u32 waresize)
{
#define CMD_WARE     3
    u8 cmdf[2] = {CMD_WARE, ~CMD_WARE};    
    u8 cmdr[2] = {~CMD_WARE, CMD_WARE};   

    usart1_sendbuff(cmdf, sizeof(cmdf));    

    usart1_sendbuff(wareaddr, waresize); 

    usart1_sendbuff(cmdr, sizeof(cmdr));    
}

