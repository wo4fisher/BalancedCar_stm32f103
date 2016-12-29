#include "Mpu6050.h"

void MPU_Init(void)
{
    u8 value;
    value=0x80;
    MPU6050_WR(0x6B, &value);   //????
    delay_ms(500);
	
    value=0x00;
    MPU6050_WR(0x6B, &value);//wake up
    value=0x00;
    MPU6050_WR(0x6C, &value);
    value=0x06;
    MPU6050_WR(0x1A, &value);  //MPU_9150 Config
    value=0x08;
    MPU6050_WR(0x1B, &value);   //???????
    value=0x08;
    MPU6050_WR(0x1C, &value);   //????????
    
    value=0x02;
    MPU6050_WR(0x37,&value); 
    value=0x00;
    MPU6050_WR(0x6A,&value);
}

int16_t MPU6050_GetDoubleData(u8 reg,u8 * value)
{
    int16_t data;
    i2cread(0x68,reg,1,value);
    data=(*value);
    data=(data<<8);
    i2cread(0x68,reg+1,1,value);
    data=data|(*value);
    return (int16_t)data;//????,???????
}

int16_t accel_Xdata_raw,accel_Zdata_raw,gyro_Ydata_raw;
u8 read_MPUdata_flag=0;
void Get_MPUdata(void)
{
    u8 value;
    accel_Xdata_raw=MPU6050_GetDoubleData(0x3B,&value);
    accel_Zdata_raw=MPU6050_GetDoubleData(0x3F,&value);
    gyro_Ydata_raw=MPU6050_GetDoubleData(0x43,&value);
    printf("gy=%d  \n",accel_Xdata_raw);
}
