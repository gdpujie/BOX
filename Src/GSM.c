#include "GSM.h"
static unsigned char check_OK[10] = {0x3e,0x20};
static unsigned char OK[] = {"OK"};
static GSM_TYPE m_gsm;
static int Contain(u8* des,u8* contain,int des_len, int contain_len)
{
	
	for(int i = 0 ; i != des_len; ++i)
	{
	   if(des[i] == contain[0])
		 {
			 for(int j = 1 ; j != contain_len ; ++j)
			 {
			    if(des[++i] != contain[j])
					{
						i--;
						break;
					}else if(j == contain_len -1)
					{
						return 1;
					}
			 }
		 }
	}
	return 0;
}
static int send_gsm_cmd(char *data,char length,int time,int time_rcv)
{
	u8 temp[30];
	u8 len = length;
//	u8 successful = 0;
	u8 rcv[100] = {0};
	memset(rcv,0,100);
	memcpy(temp,data,len);
	temp[len] = 0x0D;
	temp[len+1] =0x0a;
	len+=2;
	HAL_UART_Transmit(&huart1,(uint8_t*)(&temp),len,time);
  HAL_UART_Receive(&huart1,(uint8_t*)&rcv,50,time_rcv);
  HAL_Delay(200);
  if(Contain(rcv,OK,50,2) || Contain(rcv,check_OK,50,2))
	{
		return 1;
	}else
	{
		return  0;
	}
}

void init_gsm(GSM_TYPE* gsm)
{
	 m_gsm.phone = gsm->phone;
	 m_gsm.psw   = gsm->psw;
	 m_gsm.status = gsm->status;
	 return ;
}

void sendpsw()
{
	u8 data[100] = {0};
	u8 cmd[] = "AT+CMGS=\"";
	u8 len = strlen((char*)cmd);
	memcpy(data,cmd,len);
	memcpy(data+len,m_gsm.phone,strlen((char*)m_gsm.phone));
	len+=strlen((char*)m_gsm.phone);
	data[len] = '\"';
	len++;
//	data[len] = 0x0d;
//	len++;
//	data[len]=0x0a;
//	len++;
	while(!send_gsm_cmd((char*)&data,len,100,3000))
	{
		HAL_Delay(1000);
	}
	len = strlen((char*)(m_gsm.psw));
	memcpy(data,m_gsm.psw,len);
//  data[len] = 0x0d;
//	len++;
//	data[len]=0x0a;
  send_gsm_cmd((char*)&data,len,100,3000);
	data[0] = 0x1A;
	send_gsm_cmd((char*)&data,1,500,3000);	
  m_gsm.status = 1;
}
