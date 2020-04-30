#include "rgb3.h"
#include "delay.h"
#include "led.h"
#include "movements.h"
u8 amount=1;
u8 Rgena=0x09,Ggena=0x09,Bgena=0x09;     //��ƽ��rgb   ��̬
extern double Ramount=0,Gamount=0,Bamount=0;     					//��ɫrgb
u8  Rj=0x26, Gj=0x26, Bj=0x26;     //��ƽ�� 				��̬
u8  Rj2, Gj2, Bj2;  

/*******************************************
*
*		  ��ƽ��
*
*******************************************/
void whitebalance(void)											//baipingheng
{ 		 
	GPIO_ResetBits(GPIOD,GPIO_Pin_10|GPIO_Pin_11);//��ɫͨ��
	delay_ms(20);
	amount=0;			 //��ʼ����
	delay_ms(10);
	Rgena = amount;   //�����ɫ����      
	amount=0;
//----------------------------------
	GPIO_SetBits(GPIOD,GPIO_Pin_10|GPIO_Pin_11);//��ɫͨ��
	delay_ms(20);
	amount=0;
	delay_ms(10);
	Ggena = amount;	 //�����ɫ����
	amount=0;
//----------------------------------
	GPIO_SetBits(GPIOD,GPIO_Pin_11);
	GPIO_ResetBits(GPIOD,GPIO_Pin_10);;//��ɫͨ��
	delay_ms(20);
	amount=0;
	delay_ms(10);
	Bgena = amount;	  //�����ɫ����
	amount=0;
}  
void duqui(void)        							//duqu  rgb
{
	GPIO_ResetBits(GPIOD,GPIO_Pin_10|GPIO_Pin_11);
	delay_ms(20);
	amount=0;
	delay_ms(10);
	Ramount= amount*255/Rj;	 //ȡRֵ
	if(Ramount>255) Ramount = 255;
	

//	GPIO_SetBits(GPIOD,GPIO_Pin_10|GPIO_Pin_11);
//	delay_ms(20);
//	amount=0;
//	delay_ms(10);
//	Gamount= amount*255/Gj;	//ȡGֵ
//	if(Gamount>255) Gamount = 255;
//	

//	GPIO_SetBits(GPIOD,GPIO_Pin_11);
//	GPIO_ResetBits(GPIOD,GPIO_Pin_10);
//	delay_ms(20);
//	amount=0;
//	delay_ms(10);
//	Bamount= amount*255/Bj;//ȥBֵ
//	if(Bamount>255) Bamount = 255;
	
}

void USART1_IRQHandler(void)    		//tongxin   fanhuizhi
{	
	int p;
	USART_ClearFlag(USART1,USART_FLAG_TC);
	
	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=Bit_RESET)
	{
			p=USART_ReceiveData(USART1);}
		
		if(p==1)
		{
			Rj=Rgena;  Gj=Ggena;Bj=Bgena;
		USART_SendData(USART1,Rgena);       		//hong
			while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==Bit_RESET);
				
				USART_SendData(USART1,Ggena);
			while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==Bit_RESET);
			
				USART_SendData(USART1,Bgena);
			while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==Bit_RESET);			
		}
		
		if(p==2)
		{Rj2=Ramount;  Gj2=Gamount;  Bj2=Bamount;
			
		USART_SendData(USART1,Rj2);       		//hong
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==Bit_RESET);
					delay_ms(10);
		USART_SendData(USART1,Gj2);      //��
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==Bit_RESET);
			delay_ms(10);
		USART_SendData(USART1,Bj2);   				//��		
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==Bit_RESET);
		delay_ms(10);
		}
		USART_ClearFlag(USART1,USART_FLAG_TC);
}

	void EXTI2_IRQHandler(void)     //waibuzhongduan2    duquzhi
{
	
	amount++;		 
	EXTI_ClearITPendingBit(EXTI_Line2);  //���LINE2�ϵ��жϱ�־λ  

}
void yanse_init()
{
//	GPIO_InitTypeDef GPIO_InitStructure;	//����һ���ṹ�������������ʼ��GPIO

//	USART_InitTypeDef  USART_InitStructure;	  //���ڽṹ�嶨��

	NVIC_InitTypeDef NVIC_InitStructure;//�жϽṹ�嶨��
	
	EXTI_InitTypeDef EXTI_InitStructure;			//waibuzhongduan
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);		//a9  a10 tongxin
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);  //tongxin
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	 //��ʱ��`
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);   //s0-s3
	
	/*  ����GPIO��ģʽ��IO�� */
//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;//TX			   //�������PA9
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;	    //�����������
//	GPIO_Init(GPIOA,&GPIO_InitStructure);  /* ��ʼ����������IO */
//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;//RX			 //��������PA10
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;		  //ģ������
//	GPIO_Init(GPIOA,&GPIO_InitStructure); /* ��ʼ��GPIO */

//	USART_InitStructure.USART_BaudRate=115200;   //����������Ϊ9600	//������
//	USART_InitStructure.USART_WordLength=USART_WordLength_8b;		//���ݳ�8λ
//	USART_InitStructure.USART_StopBits=USART_StopBits_1;			//1λֹͣλ
//	USART_InitStructure.USART_Parity=USART_Parity_No;				//��Ч��
//	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None; //ʧ��Ӳ����
//	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;	 //�������ͺͽ���ģʽ
//	USART_Init(USART1,&USART_InitStructure);	/* ��ʼ��USART1 */
//	USART_Cmd(USART1, ENABLE);		   /* ʹ��USART1 */
//	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//ʹ�ܻ���ʧ��ָ����USART�ж� �����ж�
//	USART_ClearFlag(USART1,USART_FLAG_TC);//���USARTx�Ĵ������־λ

  GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource2);//p2 yingshedao xianlu2 shang   OUT  PE2
	
  EXTI_InitStructure.EXTI_Line=EXTI_Line2;                //waibuzhongduan
  EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;  		//xiajiangyanchufa
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);					//��EXTI2��ȫ���ж�
	NVIC_InitStructure.NVIC_IRQChannel=EXTI2_IRQn;					//dakaiquanjuzhongduan
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;	//qiangzhanyouxianji0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;				//xiangyingyouxianji0
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* ����NVIC���� */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);    
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; 	   //��USART1��ȫ���ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 	 //��ռ���ȼ�Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 			//��Ӧ���ȼ�Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 			 //ʹ��
	NVIC_Init(&NVIC_InitStructure);

}
