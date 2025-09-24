#include "main.h"

#define BTN_PIN LL_GPIO_PIN_0
#define LED_PIN LL_GPIO_PIN_13
#define BTN_PORT GPIOA
#define LED_PORT GPIOC

void SystemClock_Config(void);
static void GPIO_Init(void);

int main(void)
{
  SystemClock_Config();
  GPIO_Init();

  while (1)
  {
	 if (LL_GPIO_IsInputPinSet(BTN_PORT, BTN_PIN))
		 LL_GPIO_ResetOutputPin(LED_PORT, LED_PIN);
	 else
		 LL_GPIO_SetOutputPin(LED_PORT, LED_PIN);

  }
}

static void GPIO_Init(void)
{
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);

	LL_GPIO_InitTypeDef GPIO_InitSturct = {
			.Pin = BTN_PIN,
			.Mode = LL_GPIO_MODE_INPUT,
			.Speed = LL_GPIO_SPEED_FREQ_LOW,
			.OutputType = LL_GPIO_OUTPUT_PUSHPULL,
			.Pull = LL_GPIO_PULL_DOWN,
			.Alternate = LL_GPIO_AF_0
	};
	LL_GPIO_Init(BTN_PORT, &GPIO_InitSturct);

	GPIO_InitSturct.Pin = LED_PIN;
	GPIO_InitSturct.Mode = LL_GPIO_MODE_OUTPUT;
	GPIO_InitSturct.Pull = LL_GPIO_PULL_NO;
	LL_GPIO_Init(LED_PORT, &GPIO_InitSturct);
}

SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_0);
  while(LL_FLASH_GetLatency()!= LL_FLASH_LATENCY_0)
  {
  }
  LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE1);
  LL_RCC_HSI_SetCalibTrimming(16);
  LL_RCC_HSI_Enable();

  while(LL_RCC_HSI_IsReady() != 1)
  {

  }
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);

  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI)
  {

  }
  LL_Init1msTick(16000000);
  LL_SetSystemCoreClock(16000000);
  LL_RCC_SetTIMPrescaler(LL_RCC_TIM_PRESCALER_TWICE);
}


void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {

  }
}
#ifdef USE_FULL_ASSERT

void assert_failed(uint8_t *file, uint32_t line)
{

}
#endif
