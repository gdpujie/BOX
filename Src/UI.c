#include "UI.h"
#define LEN  100
typedef unsigned char u8;
static BOX_TYPE *m_box = NULL;
static u8 rcv[LEN] ={0};
//static u8 tx[LEN] = {0};
static int rcv_index = -1;
static STATUS_TYPE status = IDLE;
static void set_box_number(int num)
{
	if(NULL == m_box)  return ;
	m_box->box_number = num;
	m_box->number_seted = 1;
}
static void set_phone_number(u8* data,u8 len)
{
	if(NULL == m_box)  return ;
  
	memcpy(m_box->phone,data,len);
	m_box->phone[len] = '\0';
	m_box->phone_len = len+1;
	m_box->phone_seted = 1;
}

extern void init_box(BOX_TYPE* box)
{
		m_box = box;
	  m_box->number_seted = 0;
	  m_box->phone_seted = 0;
	  HAL_UART_Receive_IT(&huart2,rcv,14);

}
extern void wait_psw()
{
HAL_UART_Receive_IT(&huart2,rcv,6);
}
static int get_ui_data()
{
	  int boxnumber_index,phone_index = -1;
		for(int i = 0; i != 14 ; ++i)
	{
			if(rcv[i] == 0xf0)
			{
				boxnumber_index = i;
			}else if(rcv[i] == 0xf1)
			{
				phone_index = i;
			}
			else
			{
				continue;
			}
	
	}
		set_box_number(rcv[boxnumber_index+1] - 0x30);
	  set_phone_number(&rcv[phone_index+1],11);
	  
}
extern void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
		
		if(huart->Instance == USART2)
		{
			if(rcv[0] != SEND_PSW)
			{		seted_flag = 1;
			   get_ui_data();
				 HAL_UART_Receive_IT(&huart2,rcv,6);
			}
			else{
			psw_flag = 1;
		  memcpy(m_box->input_psw,&rcv[1],5);
			m_box->psw_len = 5;
			}
				
		}
}
