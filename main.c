#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "delay.h"
#include "gpio_conf.h"
#include "usart_conf.h"
#include <stdio.h>

#define LED_PORT  GPIOB
#define LED0_PIN  GPIO_Pin_0
#define LED1_PIN  GPIO_Pin_1

//#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
//#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
	
void NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);				//中断分组1：1位抢占优先级，3位响应优先级
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;			//中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;		//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;			//子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//使能中断
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);				//中断分组1：1位抢占优先级，3位响应优先级
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;			//中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;		//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;			//子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//使能中断
	NVIC_Init(&NVIC_InitStructure);
}


int main(void){
	int i = 0;
	GPIO_Conf(LED_PORT,LED0_PIN|LED1_PIN);
	USART1_Init();
	USART2_Init();
	NVIC_Config();
	while(1){
	GPIO_SetBits(LED_PORT, LED0_PIN);
	GPIO_ResetBits(LED_PORT, LED1_PIN);
	delay(30);
	GPIO_SetBits(LED_PORT, LED1_PIN);
	GPIO_ResetBits(LED_PORT, LED0_PIN);
	delay(10);
	i = USART1_RecNum();
	while(i--){
		USART2_SendChar(USART1_ReadByte());
	}
	
	i = USART2_RecNum();
	while(i--){
		USART1_SendChar(USART2_ReadByte());
	}
	
	//printf("\n\rUSART Printf Example: retarget the C library printf function to the USART\n\r");
	//USART1_SendChar('B');
	}
}



#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif
