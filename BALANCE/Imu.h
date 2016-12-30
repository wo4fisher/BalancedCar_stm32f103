#ifndef IMU_H
#define IMU_H

#include "include.h"

#define PI 3.14159265

extern float RTAngle,RTGyro;

extern void Get_RT_Att(void);
extern void Get_Angle_Init(void);
void Kalman_Filter(float angleACC, int16_t gyro);
void vcan_sendware(u8 *wareaddr, u32 waresize);

#endif
