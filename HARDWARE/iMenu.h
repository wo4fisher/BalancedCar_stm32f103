#ifndef IMENU_H
#define IMENU_H

#include "include.h"

typedef struct
{
	uint8_t KeyStateIndex; 				//  ��ǰ״̬������
	uint8_t KeyEscState;				//  ���¡��˻ء���ʱת���״̬������
	uint8_t MenuSubstate;                            //��ǰ��������Ŀ������
	uint8_t MenuSetup;                               //��Ŀ�Ƿ�ѡ��
	void (*WindowProc)( );		               //  ��ǰ״̬Ӧ��ִ�еĹ��ܲ���
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
