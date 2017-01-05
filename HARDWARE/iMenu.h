#ifndef IMENU_H
#define IMENU_H

#include "include.h"

typedef struct
{
	uint8_t KeyStateIndex; 				//  当前状态索引号
	uint8_t KeyEscState;				//  按下“退回”键时转向的状态索引号
	uint8_t MenuSubstate;                            //当前窗口下项目索引号
	uint8_t MenuSetup;                               //项目是否被选中
	void (*WindowProc)( );		               //  当前状态应该执行的功能操作
}
KeyMenuTableStruct;

#define Show_Debug_Info 1

void main_window_proc(void);
void run_window_proc(void);
void image_debug_proc(void);
void speed_window_proc(void);
void direction_window_proc(void);

/*extern void init_kbd(void);
extern void keyboard_scan(void);*/
extern void display_proc(void);

#endif
