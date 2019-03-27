#ifndef __UI__H
#define __UI__H
#include <stdio.h>
#include <string.h>
#include "stm32f4xx_hal.h"
typedef enum{
 SET_BOX_NUMBER = 0xf0,
 SET_PHONE,
 SEND_PSW,
 IDLE
}STATUS_TYPE;
typedef enum{
	SET_BOX_bframe = 0x0f,
	SET_PHONE_bframe,
	SEND_PSW_bframe
}TYPE_BFRAME;
typedef unsigned char u8;
typedef struct{
	int box_number;
	u8 *phone;
	u8 phone_len;
	u8 number_seted;
	u8 phone_seted;
	u8 *input_psw;
	u8 psw_len;
}BOX_TYPE; 
extern UART_HandleTypeDef huart2;
extern void init_box(BOX_TYPE* box);
extern void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
//extern STATUS_TYPE check_status(void);
extern int seted_flag;
extern int psw_flag;
extern void wait_psw();
//extern int get_ui_data();
#endif



