#ifndef MPU6050_H
#define MPU6050_H

#include "include.h"

#define Mpu6050Addr 0X68 //0xD0  //0X68
#define MPU6050_WR(reg,value)   i2cWrite(Mpu6050Addr,reg,1,value)

extern int16_t accel_Xdata_raw,accel_Zdata_raw,gyro_Ydata_raw;
extern void MPU_Init(void);
extern void Get_MPUdata(void);

#endif
