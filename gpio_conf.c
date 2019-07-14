#include "gpio_conf.h"

#define ID_GPIOA (uint32_t)GPIOA-APB2PERIPH_BASE
#define ID_GPIOB (uint32_t)GPIOB-APB2PERIPH_BASE
#define ID_GPIOC (uint32_t)GPIOC-APB2PERIPH_BASE
#define ID_GPIOD (uint32_t)GPIOD-APB2PERIPH_BASE
#define ID_GPIOE (uint32_t)GPIOE-APB2PERIPH_BASE
#define ID_GPIOF (uint32_t)GPIOF-APB2PERIPH_BASE
#define ID_GPIOG (uint32_t)GPIOG-APB2PERIPH_BASE

void GPIO_Conf(GPIO_TypeDef * port,uint16_t pin){
	GPIO_InitTypeDef  GPIO_InitStructure;
	uint32_t GPIO_CLK = RCC_APB2Periph_GPIOB;
  /* Enable the GPIO Clock */
	switch((uint32_t)port-APB2PERIPH_BASE){
		case ID_GPIOA:GPIO_CLK = RCC_APB2Periph_GPIOA;break;
		case ID_GPIOB:GPIO_CLK = RCC_APB2Periph_GPIOB;break;
		case ID_GPIOC:GPIO_CLK = RCC_APB2Periph_GPIOC;break;
		case ID_GPIOD:GPIO_CLK = RCC_APB2Periph_GPIOD;break;
		case ID_GPIOE:GPIO_CLK = RCC_APB2Periph_GPIOE;break;
		case ID_GPIOF:GPIO_CLK = RCC_APB2Periph_GPIOF;break;
		case ID_GPIOG:GPIO_CLK = RCC_APB2Periph_GPIOG;break;
		default: break;
	}	
  RCC_APB2PeriphClockCmd(GPIO_CLK, ENABLE);
  /* Configure the GPIO pin */
  GPIO_InitStructure.GPIO_Pin = pin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}

