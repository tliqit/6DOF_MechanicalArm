#include "stm32f10x.h"
#include "sys.h"

u8 Flag_Way=0,Flag_Show=0;                                             //ֹͣ��־λ�� ��ʾ��־λ Ĭ��ֹͣ ��ʾ��
int Servo1,Servo2,Servo3,Servo4,Servo5;                                //���PWM����
float Velocity1,Velocity2,Velocity3,Velocity4,Velocity5,Velocity6;     //���PWM����
float Position1=750,Position2=750,Position3=750,Position4=750,Position5=750,Position6=750;    
float Speed=10;                                                        //�˶��ٶ�����
int Voltage;                                                           //��ص�ѹ������صı���
u8 delay_50,delay_flag,Bi_zhang=0,PID_Send,Flash_Send;                 //��ʱ�͵��εȱ���
float Balance_Kp=350,Balance_Kd=0,Velocity_Kp=70,Velocity_Ki=0.7;      //PID����
u16 PID_Parameter[10],Flash_Parameter[10];                             //Flash������� 
float Target_X=750,Target_Y=750	,Target_Z=750;                     
float Target1=750,Target2=735,Target3=717,Target4=750,Target5=750,Target6=800;     //�趨�����ʼֵ
float TargetX=0.2,TargetY=0,Target_Beta=-45,Target_Alpha=0,Target_Gamma=0;     					//���Ŀ��ֵ
float	Position_KP=6,Position_KI=0,Position_KD=3;                        //λ�ÿ���PID����
int PS2_LX,PS2_LY,PS2_RX,PS2_RY,PS2_KEY;
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
		TIM2_Int_Init(99,7199);         //=====��ʱ��10ms�ж�
		TIM1_PWM_Init(9999,143);        //=====PWM��ʼ��(144��Ƶ��T=1/(72000000/144)=2us,10000*2us=20ms)
		TIM4_PWM_Init(9999,143);        //=====PWM��ʼ��		
		
		while(1)
		{
			temp=KEY_Scan();
			if(temp==1)
			{
        Target3=Target3+10;
				Target4=Target4+10;
				USART_RX_STA=0;
			}	
			OLED_ShowString(1,0,"Targe1:");
			OLED_ShowNumber(40,0,Target1,4,12);
			OLED_ShowString(1,12,"Targe2:");
			OLED_ShowNumber(40,12,Target2,4,12);	
			OLED_ShowString(1,24,"Targe3:");
			OLED_ShowNumber(40,24,Target3,4,12);	
			OLED_ShowString(1,36,"Targe4:");
			OLED_ShowNumber(40,36,Target4,4,12);	
			OLED_ShowString(1,48,"Targe5:");
			OLED_ShowNumber(40,48,Target5,4,12);	
			OLED_ShowString(80,0,"Targe6:");
			OLED_ShowNumber(80,12,Target6,4,12);	
		 OLED_Refresh_Gram();	
//			oled_show();
		}

  }

