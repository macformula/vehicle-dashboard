/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */
const uint16_t COUNTER_PERIOD = 20000 - 1; //Global Maximum number that the stm32 will count to before resetting
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
static void MX_TIM2_Init(uint32_t prescalar, _Bool Channel_1, _Bool Channel_2, _Bool Channel_3, _Bool Channel_4);
static void MX_TIM1_Init(uint32_t prescalar, _Bool Channel_1, _Bool Channel_2, _Bool Channel_3, _Bool Channel_4);
static void Timer_Init(uint8_t num, uint16_t period, _Bool Channel_1, _Bool Channel_2, _Bool Channel_3, _Bool Channel_4);
uint32_t Calculate_Prescalar(uint16_t period);
static void PWM_Init(uint8_t timer, uint8_t channel, uint8_t duty_cycle);
uint16_t Calculate_DutyCycle(uint8_t duty_cycle);
static void PWM_Stop(uint8_t timer,uint8_t channel);
static void Timer_Stop(uint8_t timer);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int _write(int file, char *ptr, int len) //printf to SWV ITM .Wiggam55
{
	int i = 0;
	for(i = 0 ; i<len ; i++)
	{
		ITM_SendChar((*ptr++));
	}
	return len;
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();

  /* USER CODE BEGIN 2 */

  Timer_Init(2,10, 1, 1, 1, 1);
  PWM_Init(2,1,10);
  PWM_Init(2,2,40);
  PWM_Init(2,3,70);
  PWM_Init(2,4,98);


  Timer_Init(1,10, 1, 1, 1, 1);
  PWM_Init(1,1,10);
  PWM_Init(1,2,40);
  PWM_Init(1,3,70);
  PWM_Init(1,4,98);

  HAL_Delay(1000);

  PWM_Stop(1, 1);

  HAL_Delay(1000);

  PWM_Stop(1, 2);

  HAL_Delay(1000);

  PWM_Stop(1, 3);

  HAL_Delay(1000);

  PWM_Stop(1, 4);

  HAL_Delay(2000);

  Timer_Init(1,1000, 1, 1, 1, 1);

  Timer_Stop(2);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(uint32_t prescalar, _Bool Channel_1, _Bool Channel_2, _Bool Channel_3, _Bool Channel_4)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */
  htim1.Init.Prescaler = prescalar;
  htim1.Init.Period = COUNTER_PERIOD;
  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  //htim1.Init.Prescaler = prescalar;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  //htim1.Init.Period = 19999;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  //htim1.Init.RepetitionCounter = 65535;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  /*if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }*/
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.BreakFilter = 0;
  sBreakDeadTimeConfig.Break2State = TIM_BREAK2_DISABLE;
  sBreakDeadTimeConfig.Break2Polarity = TIM_BREAK2POLARITY_HIGH;
  sBreakDeadTimeConfig.Break2Filter = 0;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */


  if (Channel_1)
  {
	  HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1);
  }
  if (Channel_2)
  {
  	  HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2);
  }
  if (Channel_3)
  {
  	  HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_3);
  }
  if (Channel_4)
  {
  	  HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_4);
  }

  /* USER CODE END TIM1_Init 2 */
  HAL_TIM_MspPostInit(&htim1);

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(uint32_t prescalar, _Bool Channel_1, _Bool Channel_2, _Bool Channel_3, _Bool Channel_4)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */
  htim2.Init.Prescaler = prescalar;
  htim2.Init.Period = COUNTER_PERIOD;
  /* USER CODE END TIM2_Init 1 */

  htim2.Instance = TIM2;
  //htim2.Init.Prescaler = prescalar;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  //htim2.Init.Period = 19999;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  /*if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }*/
  /* USER CODE BEGIN TIM2_Init 2 */

  if (Channel_1)
  {
	  HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1);
  }
  if (Channel_2)
  {
	  HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2);
  }
  if (Channel_3)
  {
	  HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_3);
  }
  if (Channel_4)
  {
	  HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_4);
  }
  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */
/**
  * @brief Initialize timer 1 or 2
  * @param Timer number, period (milliseconds)
  * @retval None
  */
static void Timer_Init(uint8_t num, uint16_t period, _Bool Channel_1, _Bool Channel_2, _Bool Channel_3, _Bool Channel_4)
{
	uint32_t prescalar = Calculate_Prescalar(period); //max period value is 2^16-1

	switch (num)
	{
		case (1):
			MX_TIM1_Init(prescalar,Channel_1,Channel_2,Channel_3,Channel_4);
			break;
		case (2):
			MX_TIM2_Init(prescalar,Channel_1,Channel_2,Channel_3,Channel_4);
			break;
		default:
			printf("Invalid Timer argument. Should be either '1' or '2'.");
			break;
	}
}

/**
  * @brief Calculate the prescalar necessary to operate desired PWM
  * @param period
  * @retval prescalar
  */
uint32_t Calculate_Prescalar(uint16_t period)
{
	uint32_t prescalar = ((HAL_RCC_GetSysClockFreq()*(float)period)/(COUNTER_PERIOD+1))-1;
	prescalar /= 1000;
	return prescalar;
}

/**
  * @brief Take initialized timer, channel and desired duty cycle and initialize PWM
  * @param Timer, channel, duty cycle
  * @retval None
  */
static void PWM_Init(uint8_t timer, uint8_t channel, uint8_t duty_cycle)
{

	TIM_HandleTypeDef* desired_timer;
	uint32_t desired_channel;

	uint16_t ticks_percycle = Calculate_DutyCycle(duty_cycle);

	//Initiate the PWM and desired duty cycle
	switch(timer)
	{
		case(1):
			desired_timer = &htim1;
			break;
		case(2):
			desired_timer = &htim2;
			break;
		default:
			printf("Invalid Timer argument. Should be either '1' or '2'.");
	}

	switch(channel)
	{
		case(1):
			desired_channel = TIM_CHANNEL_1;
			break;
		case(2):
			desired_channel = TIM_CHANNEL_2;
			break;
		case(3):
			desired_channel = TIM_CHANNEL_3;
			break;
		case(4):
			desired_channel = TIM_CHANNEL_4;
			break;
		default:
			printf("Invalid Channel argument. Should be an integer within range [1,4].");
	}


    HAL_TIM_PWM_Start(desired_timer, desired_channel);
    __HAL_TIM_SET_COMPARE(desired_timer, desired_channel, ticks_percycle);
}

uint16_t Calculate_DutyCycle(uint8_t duty_cycle)
{
	uint16_t ticks_percycle;
	//CHECK TO MAKE SURE DUTY CYCLE IS WITHING [0,100]
	if (duty_cycle>=0 && duty_cycle <=100)
	{
		ticks_percycle = (duty_cycle*COUNTER_PERIOD)/100;
	}

	else
	{
		ticks_percycle = 0; //Default value
		printf("Invalid Duty Cycle argument. Should be within range [0,100].");
	}
	return ticks_percycle;
}

static void PWM_Stop(uint8_t timer, uint8_t channel)
{
	TIM_HandleTypeDef* desired_timer;
	uint32_t desired_channel;
	switch(timer)
	{
		case(1):
			desired_timer = &htim1;
			break;
		case(2):
			desired_timer = &htim2;
			break;
		default:
			printf("Invalid Timer argument. Should be either '1' or '2'.");
	}

	switch(channel)
	{
		case(1):
			desired_channel = TIM_CHANNEL_1;
			break;
		case(2):
			desired_channel = TIM_CHANNEL_2;
			break;
		case(3):
			desired_channel = TIM_CHANNEL_3;
			break;
		case(4):
			desired_channel = TIM_CHANNEL_4;
			break;
		default:
			printf("Invalid Channel argument. Should be an integer within range [1,4].");
	}
	HAL_TIM_PWM_Stop(desired_timer, desired_channel);
}
static void Timer_Stop(uint8_t timer)
{
	TIM_HandleTypeDef* desired_timer;

	switch(timer)
	{
		case(1):
			desired_timer = &htim1;
			break;
		case(2):
			desired_timer = &htim2;
			break;
		default:
			printf("Invalid Timer argument. Should be either '1' or '2'.");
	}

	HAL_TIM_Base_Stop(desired_timer);
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}


#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
