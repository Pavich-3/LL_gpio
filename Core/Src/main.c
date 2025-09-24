#include "main.h"

#define BTN_PIN LL_GPIO_PIN_0       // Button is connected to Pin 0
#define LED_PIN LL_GPIO_PIN_13      // LED is connected to Pin 13
#define BTN_PORT GPIOA              // Button is on GPIO Port A
#define LED_PORT GPIOC              // LED is on GPIO Port C

/* Forward declarations for functions defined later in the file */
void SystemClock_Config(void);
static void GPIO_Init(void);

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* Initialize the system clock to its configured frequency */
  SystemClock_Config();

  /* Initialize all configured GPIO pins */
  GPIO_Init();

  /* Infinite loop - the main body of an embedded application */
  while (1)
  {
	 /* Check the state of the input pin where the button is connected */
	 if (LL_GPIO_IsInputPinSet(BTN_PORT, BTN_PIN))
	 {
		 /* If the button is pressed (input is HIGH), set the LED pin to LOW.
		  * On many development boards (like Blue Pill or Nucleo), the onboard LED
		  * is connected in a "current-sinking" configuration, so a LOW signal turns it ON.
		  */
		 LL_GPIO_ResetOutputPin(LED_PORT, LED_PIN);
	 }
	 else
	 {
		 /* If the button is not pressed (input is LOW), set the LED pin to HIGH,
		  * which turns the LED OFF.
		  */
		 LL_GPIO_SetOutputPin(LED_PORT, LED_PIN);
	 }
  }
}

/**
  * @brief  Configures the GPIO pins for the Button and LED.
  * @param  None
  * @retval None
  */
static void GPIO_Init(void)
{
	/* To use a peripheral like a GPIO port, its clock must be enabled first. */
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA); // Enable clock for Port A
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC); // Enable clock for Port C

	/* Declare a GPIO Init structure to hold the configuration settings. */
	LL_GPIO_InitTypeDef GPIO_InitSturct = {0};

	/*
	 * Configure the Button Pin (PA0) as an input with a pull-down resistor.
	 */
	GPIO_InitSturct.Pin = BTN_PIN;                      // Select the pin to configure
	GPIO_InitSturct.Mode = LL_GPIO_MODE_INPUT;          // Set the pin as a digital input
	GPIO_InitSturct.Speed = LL_GPIO_SPEED_FREQ_LOW;     // Set the GPIO speed (low is fine for a button)
	GPIO_InitSturct.OutputType = LL_GPIO_OUTPUT_PUSHPULL; // Not used for input mode, but good to define
	GPIO_InitSturct.Pull = LL_GPIO_PULL_DOWN;           // Enable the internal pull-down resistor.
	                                                    // This ensures the pin reads a stable LOW when the button is not pressed.
	GPIO_InitSturct.Alternate = LL_GPIO_AF_0;           // Not used for simple GPIO mode

	/* Apply the configuration defined in the structure to the button pin */
	LL_GPIO_Init(BTN_PORT, &GPIO_InitSturct);

	/*
	 * Reuse the same structure to configure the LED Pin (PC13) as an output.
	 * We only need to change the fields that are different.
	 */
	GPIO_InitSturct.Pin = LED_PIN;                      // Change the target pin to the LED's pin
	GPIO_InitSturct.Mode = LL_GPIO_MODE_OUTPUT;         // Set the mode to digital output
	GPIO_InitSturct.Pull = LL_GPIO_PULL_NO;             // No pull-up or pull-down is needed for a push-pull output

	/* Apply the new configuration to the LED pin */
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
