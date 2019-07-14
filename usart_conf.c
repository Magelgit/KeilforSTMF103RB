#include "usart_conf.h"

#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */


	
char RxUBuf1[RXBUF1_MAX];	
static uint8_t Num_U1RxByte = 0;	
static uint8_t U1RxF = 0;
static uint8_t U1RxL = 0;
	
char RxUBuf2[RXBUF2_MAX];	
static uint8_t Num_U2RxByte = 0;	
static uint8_t U2RxF = 0;
static uint8_t U2RxL = 0;
	
	struct __FILE
{
	int a;
};
 
FILE __stdout;
void _sys_exit(int x)
{	
}




void USART1_Init(void){
	
	USART_InitTypeDef USART_InitStructure;
	
	GPIO_InitTypeDef GPIO_InitStructure;
  /* Enable GPIO clock */
  RCC_APB2PeriphClockCmd(USART1_GPIO_CLK, ENABLE);

  /* Configure USART Tx as alternate function push-pull */
  //GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Pin = USART1_TX;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(USART1_GPIO, &GPIO_InitStructure);
  /* Configure USART Rx as input floating */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Pin = USART1_RX;
  GPIO_Init(USART1_GPIO, &GPIO_InitStructure);
	
	  /* Enable UART clock */
  RCC_APB2PeriphClockCmd(USART1_PORT_CLK, ENABLE); 
	USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	/* USART configuration */
  USART_Init(USART1, &USART_InitStructure); 
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);							//开启接收中断
	//USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);		
  /* Enable USART */
  USART_Cmd(USART1, ENABLE);
}

void USART2_Init(void){
	
	USART_InitTypeDef USART_InitStructure;
	
	GPIO_InitTypeDef GPIO_InitStructure;
  /* Enable GPIO clock */
  RCC_APB2PeriphClockCmd(USART2_GPIO_CLK, ENABLE);

  /* Configure USART Tx as alternate function push-pull */
  //GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Pin = USART2_TX;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(USART2_GPIO, &GPIO_InitStructure);
  /* Configure USART Rx as input floating */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Pin = USART2_RX;
  GPIO_Init(USART2_GPIO, &GPIO_InitStructure);
	
	  /* Enable UART clock */
  RCC_APB1PeriphClockCmd(USART2_PORT_CLK, ENABLE); 
	USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	/* USART configuration */
  USART_Init(USART2, &USART_InitStructure); 
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);							//开启接收中断
	//USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);		
  /* Enable USART */
  USART_Cmd(USART2, ENABLE);
}

char USART1_ReadByte(void){
	if(Num_U1RxByte == 0) return '\0';	
	Num_U1RxByte--;
	return RxUBuf1[U1RxF++];
}
uint8_t USART1_RecNum(void){
		return Num_U1RxByte;
}

char USART1_SendChar(char ch){
	  USART_SendData(USART1, (uint8_t) ch);

  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
  {}
  return ch;
}

void USART1_IRQHandler(void){
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)		//判断是否为接收中断
	{
		RxUBuf1[U1RxL++] = USART_ReceiveData(USART1);				  //读取接收到的字节数据
		if(Num_U1RxByte < 255)Num_U1RxByte++;
		else{
			U1RxF++; //当buffer满了丢弃最先收到的1个数据
		}
	}

	/*
	if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)		//判断是否为空闲中断
	{
		USART1->DR;						//读DR，清标志
		
		printf("%d characters:\r\n", n);
		for(i=0; i<n; i++)
		{
			printf("buff[%d] = 0x%02hhx\r\n", i, buff[i]);	//输出十六进制，保留最低两位，不够补0
		}
		n = 0;
	}
	*/
}

char USART2_ReadByte(void){
	if(Num_U2RxByte == 0) return '\0';	
	Num_U2RxByte--;
	return RxUBuf2[U2RxF++];
}
uint8_t USART2_RecNum(void){
		return Num_U2RxByte;
}
char USART2_SendChar(char ch){
	  USART_SendData(USART2, (uint8_t) ch);

  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
  {}
  return ch;
}

void USART2_IRQHandler(void){
	
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)		//判断是否为接收中断
	{
		RxUBuf2[U2RxL++] = USART_ReceiveData(USART2);				  //读取接收到的字节数据
		if(Num_U2RxByte < 255)Num_U2RxByte++;
		else{
			U2RxF++; //当buffer满了丢弃最先收到的1个数据
		}
	}

	/*
	if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)		//判断是否为空闲中断
	{
		USART1->DR;						//读DR，清标志
		
		printf("%d characters:\r\n", n);
		for(i=0; i<n; i++)
		{
			printf("buff[%d] = 0x%02hhx\r\n", i, buff[i]);	//输出十六进制，保留最低两位，不够补0
		}
		n = 0;
	}
	*/
}

PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(USART1, (uint8_t) ch);

  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
  {}

  return ch;
}

