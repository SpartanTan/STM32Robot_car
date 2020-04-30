#include "rgb3.h"
#include "delay.h"
#include "led.h"
#include "movements.h"
u8 amount=1;
u8 Rgena=0x09,Ggena=0x09,Bgena=0x09;     //白平衡rgb   动态
extern double Ramount=0,Gamount=0,Bamount=0;     					//颜色rgb
u8  Rj=0x26, Gj=0x26, Bj=0x26;     //白平衡 				静态
u8  Rj2, Gj2, Bj2;  

/*******************************************
*
*		  白平衡
*
*******************************************/
void whitebalance(void)											//baipingheng
{ 		 
	GPIO_ResetBits(GPIOD,GPIO_Pin_10|GPIO_Pin_11);//红色通道
	delay_ms(20);
	amount=0;			 //开始计数
	delay_ms(10);
	Rgena = amount;   //求出红色因子      
	amount=0;
//----------------------------------
	GPIO_SetBits(GPIOD,GPIO_Pin_10|GPIO_Pin_11);//绿色通道
	delay_ms(20);
	amount=0;
	delay_ms(10);
	Ggena = amount;	 //求出绿色因子
	amount=0;
//----------------------------------
	GPIO_SetBits(GPIOD,GPIO_Pin_11);
	GPIO_ResetBits(GPIOD,GPIO_Pin_10);;//蓝色通道
	delay_ms(20);
	amount=0;
	delay_ms(10);
	Bgena = amount;	  //求出蓝色因子
	amount=0;
}  
void duqui(void)        							//duqu  rgb
{
	GPIO_ResetBits(GPIOD,GPIO_Pin_10|GPIO_Pin_11);
	delay_ms(20);
	amount=0;
	delay_ms(10);
	Ramount= amount*255/Rj;	 //取R值
	if(Ramount>255) Ramount = 255;
	

//	GPIO_SetBits(GPIOD,GPIO_Pin_10|GPIO_Pin_11);
//	delay_ms(20);
//	amount=0;
//	delay_ms(10);
//	Gamount= amount*255/Gj;	//取G值
//	if(Gamount>255) Gamount = 255;
//	

//	GPIO_SetBits(GPIOD,GPIO_Pin_11);
//	GPIO_ResetBits(GPIOD,GPIO_Pin_10);
//	delay_ms(20);
//	amount=0;
//	delay_ms(10);
//	Bamount= amount*255/Bj;//去B值
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
		USART_SendData(USART1,Gj2);      //绿
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==Bit_RESET);
			delay_ms(10);
		USART_SendData(USART1,Bj2);   				//蓝		
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==Bit_RESET);
		delay_ms(10);
		}
		USART_ClearFlag(USART1,USART_FLAG_TC);
}

	void EXTI2_IRQHandler(void)     //waibuzhongduan2    duquzhi
{
	
	amount++;		 
	EXTI_ClearITPendingBit(EXTI_Line2);  //清除LINE2上的中断标志位  

}
void yanse_init()
{
//	GPIO_InitTypeDef GPIO_InitStructure;	//声明一个结构体变量，用来初始化GPIO

//	USART_InitTypeDef  USART_InitStructure;	  //串口结构体定义

	NVIC_InitTypeDef NVIC_InitStructure;//中断结构体定义
	
	EXTI_InitTypeDef EXTI_InitStructure;			//waibuzhongduan
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);		//a9  a10 tongxin
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);  //tongxin
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	 //打开时钟`
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);   //s0-s3
	
	/*  配置GPIO的模式和IO口 */
//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;//TX			   //串口输出PA9
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;	    //复用推挽输出
//	GPIO_Init(GPIOA,&GPIO_InitStructure);  /* 初始化串口输入IO */
//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;//RX			 //串口输入PA10
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;		  //模拟输入
//	GPIO_Init(GPIOA,&GPIO_InitStructure); /* 初始化GPIO */

//	USART_InitStructure.USART_BaudRate=115200;   //波特率设置为9600	//波特率
//	USART_InitStructure.USART_WordLength=USART_WordLength_8b;		//数据长8位
//	USART_InitStructure.USART_StopBits=USART_StopBits_1;			//1位停止位
//	USART_InitStructure.USART_Parity=USART_Parity_No;				//无效验
//	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None; //失能硬件流
//	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;	 //开启发送和接受模式
//	USART_Init(USART1,&USART_InitStructure);	/* 初始化USART1 */
//	USART_Cmd(USART1, ENABLE);		   /* 使能USART1 */
//	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//使能或者失能指定的USART中断 接收中断
//	USART_ClearFlag(USART1,USART_FLAG_TC);//清除USARTx的待处理标志位

  GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource2);//p2 yingshedao xianlu2 shang   OUT  PE2
	
  EXTI_InitStructure.EXTI_Line=EXTI_Line2;                //waibuzhongduan
  EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;  		//xiajiangyanchufa
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);					//打开EXTI2的全局中断
	NVIC_InitStructure.NVIC_IRQChannel=EXTI2_IRQn;					//dakaiquanjuzhongduan
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;	//qiangzhanyouxianji0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;				//xiangyingyouxianji0
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* 设置NVIC参数 */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);    
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; 	   //打开USART1的全局中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 	 //抢占优先级为0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 			//响应优先级为0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 			 //使能
	NVIC_Init(&NVIC_InitStructure);

}
