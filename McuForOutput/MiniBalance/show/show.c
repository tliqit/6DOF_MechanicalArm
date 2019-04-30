#include "show.h"
  /**************************************************************************
���ߣ�ƽ��С��֮��
�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
**************************************************************************/
unsigned char i;          //��������
unsigned char Send_Count; //������Ҫ���͵����ݸ���
float Vol;
/**************************************************************************
�������ܣ�OLED��ʾ
��ڲ�������
����  ֵ����
**************************************************************************/
void oled_show(void)
{                         

			OLED_ShowString(1,0,"T1:");
			OLED_ShowNumber(20,0,Target1,4,12);
			OLED_ShowString(60,0,"T2:");
			OLED_ShowNumber(80,0,Target2,4,12);	
			OLED_ShowString(1,12,"T3:");
			OLED_ShowNumber(20,12,Target3,4,12);	
			OLED_ShowString(60,12,"T4:");
			OLED_ShowNumber(80,12,Target4,4,12);	
			OLED_ShowString(1,24,"T5:");
			OLED_ShowNumber(20,24,Target5,4,12);	
			OLED_ShowString(60,24,"T6:");
			OLED_ShowNumber(80,24,Target6,4,12);	
		 OLED_Refresh_Gram();	
	}
/**************************************************************************
�������ܣ���APP��������
��ڲ�������
����  ֵ����
��    �ߣ�ƽ��С��֮��
**************************************************************************/
void APP_Show(void)
{    
		static u8 flag;
	  int app_2,app_3,app_4;
		app_4=(Voltage-1110)*2/3;		if(app_4<0)app_4=0;if(app_4>100)app_4=100;   //�Ե�ѹ���ݽ��д���
//    app_3=Moto1/50; if(app_3<0)app_3=-app_3;			                           //�Ա��������ݾ������ݴ������ͼ�λ�
//		app_2=Moto2/50;  if(app_2<0)app_2=-app_2;
	  flag=!flag;
	if(PID_Send==1)//����PID����
	{
		printf("{C%d:%d:%d:%d:%d:%d:%d:%d:%d}$",(int)(Balance_Kp*100),(int)(Balance_Kd*100),(int)(Velocity_Kp*100),(int)(Velocity_Ki*100),0,0,0,0,0);//��ӡ��APP����	
		PID_Send=0;	
	}	
   else	if(flag==0)// 
   printf("{A%d:%d:%d:%d}$",(u8)app_2,(u8)app_3,(u8)app_4,0);//��ӡ��APP����
	 else
	 printf("{B%d:%d:%d:%d:%d}$",(int)Position1,(int)Position2,(int)Position3,(int)Position4,(int)Position5);//��ӡ��APP���� ��ʾ����
}
/**************************************************************************
�������ܣ�����ʾ��������λ���������� �ر���ʾ��
��ڲ�������
����  ֵ����
��    �ߣ�ƽ��С��֮��
**************************************************************************/
void DataScope(void)
{   
    Vol=(float)Voltage/100;
		DataScope_Get_Channel_Data(Position1, 1 );   //��ʾ�Ƕ� ��λ���ȣ��㣩
		DataScope_Get_Channel_Data(Position2, 2 );   //��ʾ�����������ľ��� ��λ��CM 
		DataScope_Get_Channel_Data(Position3, 3 );   //��ʾ��ص�ѹ ��λ��V
		DataScope_Get_Channel_Data(Position4, 4 );   
		DataScope_Get_Channel_Data(Position5, 5 ); //����Ҫ��ʾ�������滻0������
//		DataScope_Get_Channel_Data(0 , 6 );//����Ҫ��ʾ�������滻0������
//		DataScope_Get_Channel_Data(0, 7 );
//		DataScope_Get_Channel_Data( 0, 8 ); 
//		DataScope_Get_Channel_Data(0, 9 );  
//		DataScope_Get_Channel_Data( 0 , 10);
		Send_Count = DataScope_Data_Generate(5);
		for( i = 0 ; i < Send_Count; i++) 
		{
		while((USART1->SR&0X40)==0);  
		USART1->DR = DataScope_OutPut_Buffer[i]; 
		}
}
