#ifndef __USART_CONF_H
#define __USART_CONF_H

#include "stm32f10x.h"
#include "stm32f10x_usart.h"
#include <stdio.h>

//USART1  -->USART1_IRQn
#define USART1_GPIO 			GPIOA
#define USART1_TX 				GPIO_Pin_9
#define USART1_RX 				GPIO_Pin_10
#define USART1_GPIO_CLK 	RCC_APB2Periph_GPIOA
#define USART1_PORT_CLK 	RCC_APB2Periph_USART1
#define RXBUF1_MAX 256 //定义为256时，uint8_t不用判断是否溢出，自动从0开始

//USART2  -->USART2_IRQn
#define USART2_GPIO 			GPIOA
#define USART2_TX 				GPIO_Pin_2
#define USART2_RX 				GPIO_Pin_3
#define USART2_GPIO_CLK 	RCC_APB2Periph_GPIOA
#define USART2_PORT_CLK 	RCC_APB1Periph_USART2
#define RXBUF2_MAX 256 //定义为256时，uint8_t不用判断是否溢出，自动从0开始

void USART1_Init(void);
char USART1_SendChar(char ch);
uint8_t USART1_RecNum(void);
char USART1_ReadByte(void);

void USART2_Init(void);
char USART2_SendChar(char ch);
uint8_t USART2_RecNum(void);
char USART2_ReadByte(void);

#endif /*__USART_CONF_H*/
