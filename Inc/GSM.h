#ifndef __GSM__H
#define __GSM__H
#include <stdio.h>
#include <string.h>
#include "stm32f4xx_hal.h"
#define CMD_NUM  2
typedef unsigned char u8;
typedef struct _GSM_TYPE{
u8* phone;
u8* psw;
u8 status;
}GSM_TYPE;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart3;
extern void init_gsm(GSM_TYPE* gsm);
extern void sendpsw(void);

#endif

