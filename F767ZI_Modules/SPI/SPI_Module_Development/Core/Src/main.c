/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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



/* USER CODE BEGIN PV */

SPI_HandleTypeDef hspi1;
SPI_HandleTypeDef hspi2;
SPI_HandleTypeDef hspi3;
SPI_HandleTypeDef hspi4;
SPI_HandleTypeDef hspi5;
SPI_HandleTypeDef hspi6;

GPIO_TypeDef* SPI1_Port;
GPIO_TypeDef* SPI2_Port;
GPIO_TypeDef* SPI3_Port;
GPIO_TypeDef* SPI4_Port;
GPIO_TypeDef* SPI5_Port;
GPIO_TypeDef* SPI6_Port;

uint16_t SPI1_Pin;
uint16_t SPI2_Pin;
uint16_t SPI3_Pin;
uint16_t SPI4_Pin;
uint16_t SPI5_Pin;
uint16_t SPI6_Pin;


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI4_Init(void);
static void MX_SPI5_Init(void);
/* USER CODE BEGIN PFP */
//static void SPI_Select(SPI_HandleTypeDef* hspi, uint8_t desired_SPI);

static void SPI_Init(uint8_t desired_SPI, uint8_t SPI_mode, uint8_t SPI_datasize, uint32_t KBits_per_sec, uint8_t MSBFirst);
static SPI_HandleTypeDef* SPI_Select(uint8_t desired_SPI);
static void SPI_Mode_Select(SPI_HandleTypeDef *hspi, uint8_t SPI_mode);
static void SPI_Calculate_Baudrate_Prescaler(SPI_HandleTypeDef *hspi, uint32_t KBits_per_sec);
static void SPI_Default_Configs(SPI_HandleTypeDef * hspi);
static void SPI_Datasize_Select(SPI_HandleTypeDef *hspi, uint8_t SPI_datasize);
static void SPI_Transmit(SPI_HandleTypeDef *hspi, char *Tx_buf, uint8_t buf_len, GPIO_TypeDef* SS_Port, uint16_t SS_Pin);
static void SPI_Transmit_Receive(SPI_HandleTypeDef *hspi, char *Tx_buf, char *Rx_buf, uint8_t buf_len, GPIO_TypeDef* SS_Port, uint16_t SS_Pin);
static void SPI_Accel_Init();
static void SPI_Accel_Transmit_Receive(char *Tx_buf, char *Rx_buf, uint8_t buf_len);
static void SPI_MSB_Select(SPI_HandleTypeDef *hspi, uint8_t MSBFirst);
static void SPI_Accel_Deinit();
static void SPI_Deinit(SPI_HandleTypeDef *hspi);


/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  char spi_buf[20];
  char Rx_buf[20];
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
  //MX_SPI4_Init();
  //MX_SPI5_Init();
  /* USER CODE BEGIN 2 */
  //SPI_Init(4, 2, 8, 125, 1);
  //SPI_Init(5, 2, 8, 125, 1);
  SPI_Accel_Init();

  HAL_GPIO_WritePin(SPI4_SS_GPIO_Port, SPI4_SS_Pin, GPIO_PIN_SET);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  spi_buf[0] = 0x64;
		spi_buf[1] = 0x00;
		spi_buf[2] = 0x03;
		spi_buf[3] = 0x64;
		uint8_t buf_len = 4;
		//spi_buf[3] = 0x0a;
	   // spi_buf[4] = 122;
		HAL_Delay(50);

		//SPI_Transmit(&hspi4, &spi_buf, buf_len);
		//SPI_Transmit_Receive(&hspi5, &spi_buf, &Rx_buf, buf_len);

		//SPI_Transmit(&hspi4, spi_buf, buf_len, SPI4_SS_GPIO_Port, SPI4_SS_Pin);


		SPI_Accel_Transmit_Receive(&spi_buf, &Rx_buf, 4);

		/*HAL_GPIO_WritePin(SPI4_SS_GPIO_Port, SPI4_SS_Pin, GPIO_PIN_RESET);
		HAL_SPI_Transmit(&hspi4, (uint8_t *)spi_buf, 8, 100);
		HAL_GPIO_WritePin(SPI4_SS_GPIO_Port, SPI4_SS_Pin, GPIO_PIN_SET);*/

		spi_buf[0] = 0;
		spi_buf[1] = 0;
		spi_buf[2] = 0;
		//spi_buf[3] = 0;
		//spi_buf[4] = 0;

		//SPI_Deinit(&hspi4);
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI4_Init(void)
{

  /* USER CODE BEGIN SPI4_Init 0 */

  /* USER CODE END SPI4_Init 0 */

  /* USER CODE BEGIN SPI4_Init 1 */

  /* USER CODE END SPI4_Init 1 */
  /* SPI4 parameter configuration*/
  hspi4.Instance = SPI4;
  hspi4.Init.Mode = SPI_MODE_MASTER;
  hspi4.Init.Direction = SPI_DIRECTION_2LINES;
  hspi4.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi4.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi4.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi4.Init.NSS = SPI_NSS_SOFT;
  hspi4.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi4.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi4.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi4.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi4.Init.CRCPolynomial = 7;
  hspi4.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi4.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
  if (HAL_SPI_Init(&hspi4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI4_Init 2 */

  /* USER CODE END SPI4_Init 2 */

}

/**
  * @brief SPI5 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI5_Init(void)
{

  /* USER CODE BEGIN SPI5_Init 0 */

  /* USER CODE END SPI5_Init 0 */

  /* USER CODE BEGIN SPI5_Init 1 */

  /* USER CODE END SPI5_Init 1 */
  /* SPI5 parameter configuration*/
  hspi5.Instance = SPI5;
  hspi5.Init.Mode = SPI_MODE_MASTER;
  hspi5.Init.Direction = SPI_DIRECTION_2LINES;
  hspi5.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi5.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi5.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi5.Init.NSS = SPI_NSS_SOFT;
  hspi5.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi5.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi5.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi5.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi5.Init.CRCPolynomial = 7;
  hspi5.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi5.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
  if (HAL_SPI_Init(&hspi5) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI5_Init 2 */

  /* USER CODE END SPI5_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(SPI4_SS_GPIO_Port, SPI4_SS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(SPI5_SS_GPIO_Port, SPI5_SS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LD1_Pin|LD3_Pin|LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(USB_PowerSwitchOn_GPIO_Port, USB_PowerSwitchOn_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : SPI4_SS_Pin */
  GPIO_InitStruct.Pin = SPI4_SS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(SPI4_SS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : USER_Btn_Pin */
  GPIO_InitStruct.Pin = USER_Btn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USER_Btn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : SPI5_SS_Pin */
  GPIO_InitStruct.Pin = SPI5_SS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(SPI5_SS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : RMII_MDC_Pin RMII_RXD0_Pin RMII_RXD1_Pin */
  GPIO_InitStruct.Pin = RMII_MDC_Pin|RMII_RXD0_Pin|RMII_RXD1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : RMII_REF_CLK_Pin RMII_MDIO_Pin RMII_CRS_DV_Pin */
  GPIO_InitStruct.Pin = RMII_REF_CLK_Pin|RMII_MDIO_Pin|RMII_CRS_DV_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LD1_Pin LD3_Pin LD2_Pin */
  GPIO_InitStruct.Pin = LD1_Pin|LD3_Pin|LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : RMII_TXD1_Pin */
  GPIO_InitStruct.Pin = RMII_TXD1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
  HAL_GPIO_Init(RMII_TXD1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : STLK_RX_Pin STLK_TX_Pin */
  GPIO_InitStruct.Pin = STLK_RX_Pin|STLK_TX_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_PowerSwitchOn_Pin */
  GPIO_InitStruct.Pin = USB_PowerSwitchOn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(USB_PowerSwitchOn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_OverCurrent_Pin */
  GPIO_InitStruct.Pin = USB_OverCurrent_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USB_OverCurrent_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : USB_SOF_Pin USB_ID_Pin USB_DM_Pin USB_DP_Pin */
  GPIO_InitStruct.Pin = USB_SOF_Pin|USB_ID_Pin|USB_DM_Pin|USB_DP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF10_OTG_FS;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_VBUS_Pin */
  GPIO_InitStruct.Pin = USB_VBUS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USB_VBUS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : RMII_TX_EN_Pin RMII_TXD0_Pin */
  GPIO_InitStruct.Pin = RMII_TX_EN_Pin|RMII_TXD0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

static void SPI_Accel_Init()
{
	//Initialize SPI4 on appropriate pins with a clock rate of 1MHz (baudrate prescaler of 16/ 1000 Kilobits per second)
	//Carries 8 bits of data and initialized on mode 3
	//Makes the first bit the most significant bit

	SPI_Init(4,3,8,1000,1);

}

static void SPI_Accel_Deinit()
{
	SPI_Deinit(&hspi4);
}

static void SPI_Accel_Transmit_Receive(char *Tx_buf, char *Rx_buf, uint8_t buf_len)
{
	SPI_Transmit_Receive(&hspi4, Tx_buf, Rx_buf, buf_len, SPI4_SS_GPIO_Port, SPI4_SS_Pin);
}

static void SPI_Init(uint8_t desired_SPI, uint8_t SPI_mode, uint8_t SPI_datasize, uint32_t KBits_per_sec, uint8_t MSBFirst)
{
	//selects appropriate SPI line, sets the pointer hspi to the address of corresponding SPI line e.g. &hspi1
	SPI_HandleTypeDef *hspi = SPI_Select(desired_SPI);

	//Selects appropriate baud rate depending on the desired Kilobits per second
	SPI_Calculate_Baudrate_Prescaler(hspi, KBits_per_sec);

	//all non changeable (as of now) configurations
	SPI_Default_Configs(hspi);
	//Selects mode (refer to SPI mode table, differs from master/slave mode select)
	SPI_Mode_Select(hspi, SPI_mode);
	//Sets correct datasize (in number of bits)
	SPI_Datasize_Select(hspi, SPI_datasize);
	//Selects if the MSB goes first or last
	SPI_MSB_Select(hspi, MSBFirst);

	if (HAL_SPI_Init(hspi) != HAL_OK)
	    {
	    	Error_Handler();
	    }

//Before all the nice functions:

//	switch(desired_SPI) // would like to somehow put in SPI_Select Function
//			{
//				case(1):
//					hspi = &hspi1; //pointer to memory address off hspi1 (done so that multiple SPI lines can run simultaneously)
//					break;
//				case(2):
//					hspi = &hspi2;
//					break;
//				case(3):
//					hspi = &hspi3;
//					break;
//				case(4):
//					hspi = &hspi4;
//					break;
//				case(5):
//					hspi = &hspi5;
//					break;
//				case(6):
//					hspi = &hspi6;
//					break;
//				default:
//					//handle error
//					break;
//			}

//	  hspi4.Init.DataSize = SPI_DATASIZE_8BIT;
//	  hspi4.Instance = SPI4;
//	  hspi4.Init.Mode = SPI_MODE_MASTER;
//    hspi4.Init.Direction = SPI_DIRECTION_2LINES;
//    hspi4.Init.NSS = SPI_NSS_SOFT;
//    hspi4.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
//    hspi4.Init.FirstBit = SPI_FIRSTBIT_MSB;
//    hspi4.Init.TIMode = SPI_TIMODE_DISABLE;
//    hspi4.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
//    hspi4.Init.CRCPolynomial = 7;
//    hspi4.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
//    hspi4.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;

}

static void SPI_Datasize_Select(SPI_HandleTypeDef *hspi, uint8_t SPI_datasize)
{
	uint32_t datasize_arr[13] = {SPI_DATASIZE_4BIT, SPI_DATASIZE_5BIT, SPI_DATASIZE_6BIT, SPI_DATASIZE_7BIT, SPI_DATASIZE_8BIT, SPI_DATASIZE_9BIT, SPI_DATASIZE_10BIT, SPI_DATASIZE_11BIT, SPI_DATASIZE_12BIT, SPI_DATASIZE_13BIT, SPI_DATASIZE_15BIT, SPI_DATASIZE_16BIT};

	//index adjustment for finding correct datasize in datasizes array
	uint8_t datasize_index = SPI_datasize - 4;

	hspi->Init.DataSize = datasize_arr[datasize_index];
}

static void SPI_Calculate_Baudrate_Prescaler(SPI_HandleTypeDef *hspi, uint32_t KBits_per_sec)
{
	uint32_t quotient = HAL_RCC_GetSysClockFreq()/(KBits_per_sec*1000);

	if (quotient <=2)
	{
		hspi->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
	}

	else if (quotient <=4)
	{
		hspi->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
	}

	else if (quotient <=8)
	{
		hspi->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
	}

	else if (quotient <=16)
	{
		hspi->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
	}

	else if (quotient <=32)
	{
		hspi->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
	}

	else if (quotient <=64)
	{
		hspi->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
	}

	else if (quotient <=128)
	{
		hspi->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
	}

	else if (quotient > 128)
	{
		hspi->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
	}

	else
	{
		//Error handling
	}
}

static void SPI_Default_Configs(SPI_HandleTypeDef *hspi)
{
	hspi->Init.Mode = SPI_MODE_MASTER;
	hspi->Init.Direction = SPI_DIRECTION_2LINES;
	hspi->Init.NSS = SPI_NSS_SOFT;
	//hspi->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16; //Function now made to simplify the process
	hspi->Init.FirstBit = SPI_FIRSTBIT_MSB; // Find a function to change this
	hspi->Init.TIMode = SPI_TIMODE_DISABLE;
	hspi->Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi->Init.CRCPolynomial = 7;
	hspi->Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
// FLAG ALERT ERROR - not an actual error, but now that i have your attention below should be disabled, just makes it easier to view on logic analyzer
	hspi->Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
}


//below was removed as a param, kept there to remind myself
//SPI_HandleTypeDef* hspi
static SPI_HandleTypeDef* SPI_Select(uint8_t desired_SPI)
{
	SPI_HandleTypeDef *hspi;
	switch(desired_SPI)
	{
		case(1):
			hspi = &hspi1;
			hspi-> Instance = SPI1;
			break;
		case(2):
			hspi = &hspi2;
			hspi-> Instance = SPI2;
			break;
		case(3):
			hspi = &hspi3;
			hspi-> Instance = SPI3;
			break;
		case(4):
			hspi = &hspi4;
			hspi-> Instance = SPI4;
			break;
		case(5):
			hspi = &hspi5;
			hspi-> Instance = SPI5;
			break;
		case(6):
			hspi = &hspi6;
			hspi-> Instance = SPI6;
			break;
		default:
			//handle error
			break;
	}
	return hspi;
}

static void SPI_Mode_Select(SPI_HandleTypeDef *hspi, uint8_t SPI_mode)
{
	switch(SPI_mode)
	{
	case(0):
		hspi->Init.CLKPolarity = SPI_POLARITY_LOW;
		hspi->Init.CLKPhase = SPI_PHASE_1EDGE;
		break;
	case(1):
		hspi->Init.CLKPolarity = SPI_POLARITY_LOW;
		hspi->Init.CLKPhase = SPI_PHASE_2EDGE;
		break;
	case(2):
		hspi->Init.CLKPolarity = SPI_POLARITY_HIGH;
		hspi->Init.CLKPhase = SPI_PHASE_1EDGE;
		break;
	case(3):
		hspi->Init.CLKPolarity = SPI_POLARITY_HIGH;
		hspi->Init.CLKPhase = SPI_PHASE_2EDGE;
		break;
	default:
		//handle error
		break;
	}
}

static void SPI_MSB_Select(SPI_HandleTypeDef *hspi, uint8_t MSBFirst)
{
	switch(MSBFirst)
	{
	case(0):
		hspi->Init.FirstBit = SPI_FIRSTBIT_LSB;
		break;
	case(1):
		hspi->Init.FirstBit = SPI_FIRSTBIT_MSB;
		break;
	default:
		//error handling
		break;

	}
}


static void SPI_Transmit(SPI_HandleTypeDef *hspi, char *Tx_buf, uint8_t buf_len, GPIO_TypeDef* SS_Port, uint16_t SS_Pin)
{
	HAL_GPIO_WritePin(SS_Port, SS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(hspi, (uint8_t *)Tx_buf, buf_len, 100);
	HAL_GPIO_WritePin(SS_Port, SS_Pin, GPIO_PIN_SET);
}

static void SPI_Transmit_Receive(SPI_HandleTypeDef *hspi, char *Tx_buf, char *Rx_buf, uint8_t buf_len, GPIO_TypeDef* SS_Port, uint16_t SS_Pin)
{
	HAL_GPIO_WritePin(SS_Port, SS_Pin, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(hspi, (uint8_t *)Tx_buf, (uint8_t *)Rx_buf, buf_len, 100);
	HAL_GPIO_WritePin(SS_Port, SS_Pin, GPIO_PIN_SET);
}

static void SPI_Deinit(SPI_HandleTypeDef *hspi)
{
	HAL_SPI_DeInit(hspi);
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
