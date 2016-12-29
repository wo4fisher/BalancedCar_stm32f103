#ifndef I2C_H
#define I2C_H

#include "include.h"

#define SCL  PBout(8)
#define SDA  PBout(9)
#define SDA_read  PBin(9)

#define false    0
#define	true     1
	
#define TRUE  0
#define FALSE -1

//0表示写
#define	I2C_Direction_Transmitter   0
//１表示读
#define	I2C_Direction_Receiver      1	 
/*====================================================================================================*/
/*====================================================================================================*/
extern u8 i2cWriteBuffer(u8 addr_, u8 reg_, u8 len_, u8 *data);
u8 i2cWrite(u8 addr_, u8 reg_, u8 data);
u8 i2cRead(u8 addr_, u8 reg_, u8 len, u8* buf);
extern void i2cInit(void);
u16 i2cGetErrorCounter(void);
static void i2cUnstick(void);

extern int i2cwrite(u8 addr, u8 reg, u8 len, u8 * data);
extern int i2cread(u8 addr, u8 reg, u8 len, u8 *buf);
/*====================================================================================================*/
/*====================================================================================================*/
#endif
