//#include "MM32SPIN2xx_p.h"

#include "hal_conf.h"

void SHIEH_GPIO_Init(void);


//void SystemInit(void);

int main(void)
{
  
  SHIEH_GPIO_Init();
  while(true)
  {
    GPIO_SetBits(GPIOB, GPIO_Pin_13);
    for (uint32_t i = 100000; i>0; i--);
    
    GPIO_ResetBits(GPIOB, GPIO_Pin_13);
    for (uint32_t i = 100000; i>0; i--);
  }
}

//void SystemInit(void){}



void SHIEH_GPIO_Init(void)
{
  RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOB, ENABLE);
  
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}