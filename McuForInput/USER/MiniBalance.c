#include "stm32f10x.h"
#include "sys.h"

float pitch,roll,yaw; 
	
int main(void)
  { 
		int temp=0;
		uart_init(115200);
		delay_init();
		JTAG_Set(SWD_ENABLE);//jtag,swdģʽȫʹ��
		KEY_Init();//PA5��Ϊ��������
		LED_Init();//PA4��ΪLED���
		delay_ms(100);
		OLED_Init();//OLED��ʼ��
		delay_ms(100);	
		MPU_Init();
			while(mpu_dmp_init())
 	{
		OLED_ShowString(1,0,"MPU6050 Error");
		OLED_Refresh_Gram();	
		delay_ms(200);
	}  
	OLED_ShowString(1,0,"MPU6050 OK");
		while(1)
		{
			if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)
		{ 
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
				
		}

		  OLED_Refresh_Gram();	
//			oled_show();
		}

  }

