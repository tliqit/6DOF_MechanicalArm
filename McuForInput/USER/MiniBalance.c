#include "stm32f10x.h"
#include "sys.h"

float pitch,roll,yaw; 
void oled_show();
int TempTarget;
	
int main(void)
  { 
	  u8 tmp_buf[33]="T1 1234 T2 0735 T6 0534";		
//		u8 tmp_buf[33]="T1 800 T2 900";		
//	uart_init(115200);
		delay_init();
		JTAG_Set(SWD_ENABLE);//jtag,swdģʽȫʹ��
		KEY_Init();//PA5��Ϊ��������
		LED_Init();//PA4��ΪLED���
		delay_ms(100);
		OLED_Init();//OLED��ʼ��
		delay_ms(100);	
		MPU_Init();
		NRF24L01_Init();
		while(mpu_dmp_init())
 	{
		OLED_ShowString(1,0,"MPU6050 Error");
		OLED_Refresh_Gram();	
		delay_ms(200);
	}  
	OLED_ShowString(1,0,"MPU6050 OK");
	
	while(NRF24L01_Check())//��ⲻ��24L01
		{
						
			OLED_ShowString(1,48,"24L01 Check Failed!");
		  OLED_Refresh_Gram();	
			delay_ms(200);						
		}
		OLED_ShowString(1,48,"24L01 Ready!");
		NRF24L01_TX_Mode();
		delay_ms(500);			
		while(1)
		{
			if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)
		 { 
			  oled_show();	
			 	if(NRF24L01_TxPacket(tmp_buf)==TX_OK)
			{
				TempTarget=1200+pitch*5;
				tmp_buf[3]=TempTarget/1000+'0';
				tmp_buf[4]=TempTarget/100%10+'0';
				tmp_buf[5]=TempTarget/10%10+'0';
				tmp_buf[6]=TempTarget%10+'0';
				
				
//				OLED_ShowNumber(1,48,TempTarget,5,12);
				tmp_buf[32]=0;//���������		   
				OLED_ShowString(0,48,"Send SUCCESS "); 
			}else
			{										   	
				OLED_ShowString(0,48,"Send Failed "); 
			};	
			
		 }
		
		}
  }

void oled_show()
{
			int temp=0;
			OLED_ShowString(1,12,"pitch:");
			OLED_ShowString(1,24,"roll:");
			OLED_ShowString(1,36,"yaw:");
			
			  temp=pitch*10;
				if(temp<0)
				{
					OLED_ShowChar(40,12,'-',12,1);		//��ʾ����
					temp=-temp;		//תΪ����
				}else 
					OLED_ShowChar(40,12,' ',12,1);		//ȥ������ 
				OLED_ShowNumber(40+12,12,temp/10,3,12);		//��ʾ��������
        OLED_ShowChar(40+12+18,12,'.',12,1);				
				OLED_ShowNumber(40+24+12,12,temp%10,1,12);		//��ʾС������ 
				
				temp=roll*10;
				if(temp<0)
				{
					OLED_ShowChar(40,24,'-',12,1);		//��ʾ����
					temp=-temp;		//תΪ����
				}else 
					OLED_ShowChar(40,24,' ',12,1);		//ȥ������ 
				OLED_ShowNumber(52,24,temp/10,3,12);		//��ʾ��������	
        OLED_ShowChar(40+12+18,24,'.',12,1);					
				OLED_ShowNumber(76,24,temp%10,1,12);		//��ʾС������ 
				
				temp=yaw*10;
				if(temp<0)
				{
					OLED_ShowChar(40,36,'-',12,1);		//��ʾ����
					temp=-temp;		//תΪ����
				}else 
					OLED_ShowChar(40,36,' ',12,1);		//ȥ������ 
				OLED_ShowNumber(52,36,temp/10,3,12);		//��ʾ��������	
        OLED_ShowChar(40+12+18,36,'.',12,1);					
				OLED_ShowNumber(76,36,temp%10,1,12);		//��ʾС������  
			  OLED_Refresh_Gram();	
}