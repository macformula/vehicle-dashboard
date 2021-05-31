/*
 *  spi_lib.h
 *
 *  Created on: May 12, 2021
 *  Author: Samuel Parent and Dorian Knight
 */

#ifndef INC_SPI_LIB_H_
#define INC_SPI_LIB_H_

//Pre-definied SPI handles, used for easy initialization
SPI_HandleTypeDef hspi1;
SPI_HandleTypeDef hspi2;
SPI_HandleTypeDef hspi3;
SPI_HandleTypeDef hspi4;
SPI_HandleTypeDef hspi5;
SPI_HandleTypeDef hspi6;

static void SPI_Init(uint8_t desired_SPI, uint8_t SPI_mode, uint8_t SPI_datasize, uint32_t KBits_per_sec, uint8_t MSBFirst);
static SPI_HandleTypeDef* SPI_Select(uint8_t desired_SPI);
static void SPI_Mode_Select(SPI_HandleTypeDef *hspi, uint8_t SPI_mode);
static void SPI_Calculate_Baudrate_Prescaler(SPI_HandleTypeDef *hspi, uint32_t KBits_per_sec);
static void SPI_Default_Configs(SPI_HandleTypeDef * hspi);
static void SPI_Datasize_Select(SPI_HandleTypeDef *hspi, uint8_t SPI_datasize);
static void SPI_Transmit(SPI_HandleTypeDef *hspi, char *Tx_buf, uint8_t buf_len, GPIO_TypeDef* SS_Port, uint16_t SS_Pin);
static void SPI_Transmit_Receive(SPI_HandleTypeDef *hspi, char *Tx_buf, char *Rx_buf, uint8_t buf_len, GPIO_TypeDef* SS_Port, uint16_t SS_Pin);
static void SPI_Accel_Init();
static void SPI_Accel_Receive(char *Rx_buf, uint8_t buf_len);
static void SPI_MSB_Select(SPI_HandleTypeDef *hspi, uint8_t MSBFirst);
static void SPI_Accel_Deinit();
static void SPI_Deinit(SPI_HandleTypeDef *hspi);
static void SPI_Receive(SPI_HandleTypeDef *hspi, char *Rx_buf, uint8_t buf_len, GPIO_TypeDef* SS_Port, uint16_t SS_Pin);

/**
  * @brief SPI Accelerometer Initialization Function
  * @param None
  * @retval None
  */
static void SPI_Accel_Init()
{
	//Initialize SPI4 on appropriate pins with a clock rate of 1MHz (baudrate prescaler of 16 to attain speeds of 1000 Kilobits per second)
	//Carries 8 bits of data and initialized on mode 3
	//Makes the first bit the most significant bit
	SPI_Init(4,3,8,1000,1);

	//Pull the Slave Select Line High
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, SET);
}

/**
  * @brief SPI Accelerometer Uninitialization Function
  * @param None
  * @retval None
  */
static void SPI_Accel_Deinit()
{
	SPI_Deinit(&hspi4);
}

/**
  * @brief SPI Accelerometer Receive Function
  * @param Receive buffer, length of buffer
  * @retval None (Directly updates receive buffer through pointer)
  */
static void SPI_Accel_Receive(char *Rx_buf, uint8_t buf_len)
{
	SPI_Receive(&hspi4, Rx_buf, buf_len, GPIOE, GPIO_PIN_4);
}

/**
  * @brief Base Layer SPI Initialization Function
  * @param Desired SPI Number, SPI Mode, Data size limit, communication speed in kilobits/sec, Placement of Most significant bit
  * @retval None
  */
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
}

/**
  * @brief Base Layer SPI Datasize Select Function
  * @param SPI Driver, Desired data size limit
  * @retval None
  */
static void SPI_Datasize_Select(SPI_HandleTypeDef *hspi, uint8_t SPI_datasize)
{
	uint32_t datasize_arr[13] = {SPI_DATASIZE_4BIT, SPI_DATASIZE_5BIT, SPI_DATASIZE_6BIT, SPI_DATASIZE_7BIT, SPI_DATASIZE_8BIT, SPI_DATASIZE_9BIT, SPI_DATASIZE_10BIT, SPI_DATASIZE_11BIT, SPI_DATASIZE_12BIT, SPI_DATASIZE_13BIT, SPI_DATASIZE_15BIT, SPI_DATASIZE_16BIT};

	//index adjustment for finding correct datasize in datasizes array
	uint8_t datasize_index = SPI_datasize - 4;

	hspi->Init.DataSize = datasize_arr[datasize_index];
}

/**
  * @brief Base Layer SPI Communication Speed Select Function
  * @param SPI Driver, Desired communication speed limit
  * @retval None
  */
static void SPI_Calculate_Baudrate_Prescaler(SPI_HandleTypeDef *hspi, uint32_t KBits_per_sec)
{
	//Takes clock speed and divides by the desired bits/second you want to send to obtain appropriate prescaler
	//Eg. Clock frequency is 16 MHz and you want to send 2000 KBits per second, your prescaler would be 16MHz/(2000*10^3) = 8
	//Max speed is attained when prescaler is = 2 therefore you can only communicate up to 8 Mega bits per second
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

/**
  * @brief Base Layer SPI Default Settings Function - Sets Default Configurations for All SPI Drivers
  * @param SPI Driver
  * @retval None
  */
static void SPI_Default_Configs(SPI_HandleTypeDef *hspi)
{
	hspi->Init.Mode = SPI_MODE_MASTER;
	hspi->Init.Direction = SPI_DIRECTION_2LINES;
	hspi->Init.NSS = SPI_NSS_SOFT;
	hspi->Init.TIMode = SPI_TIMODE_DISABLE;
	hspi->Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi->Init.CRCPolynomial = 7;
	hspi->Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
	hspi->Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
}

/**
  * @brief Base Layer SPI Select Function
  * @param Desired SPI Driver
  * @retval SPI Driver Corresponding to the Input
  */
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

/**
  * @brief Base Layer SPI Mode Select Function
  * @param SPI Driver, Desired Mode Number
  * @retval None
  */
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

/**
  * @brief Base Layer SPI Most Significant Bit First or Last Select Function
  * @param SPI Driver, Most Significant Bit First or Last (0 for last or 1 for first)
  * @retval None
  */
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

/**
  * @brief Base Layer SPI Receive Function
  * @param SPI Driver, Receive Buffer, Buffer Length, Desired Slave Select Port, Desired Slave Select Pin
  * @retval None
  */
static void SPI_Receive(SPI_HandleTypeDef *hspi, char *Rx_buf, uint8_t buf_len, GPIO_TypeDef* SS_Port, uint16_t SS_Pin)
{
	HAL_GPIO_WritePin(SS_Port, SS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Receive(hspi, (uint8_t *)Rx_buf, buf_len, 100);
	HAL_GPIO_WritePin(SS_Port, SS_Pin, GPIO_PIN_SET);
}

/**
  * @brief Base Layer SPI Transmit Function
  * @param SPI Driver, Transmit Buffer, Buffer Length, Desired Slave Select Port, Desired Slave Select Pin
  * @retval None
  */
static void SPI_Transmit(SPI_HandleTypeDef *hspi, char *Tx_buf, uint8_t buf_len, GPIO_TypeDef* SS_Port, uint16_t SS_Pin)
{
	HAL_GPIO_WritePin(SS_Port, SS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(hspi, (uint8_t *)Tx_buf, buf_len, 100);
	HAL_GPIO_WritePin(SS_Port, SS_Pin, GPIO_PIN_SET);
}

/**
  * @brief Base Layer SPI Transmit and Receive Function
  * @param SPI Driver, Transmit Buffer, Receive Buffer, Buffer Length, Desired Slave Select Port, Desired Slave Select Pin
  * @retval None
  */
static void SPI_Transmit_Receive(SPI_HandleTypeDef *hspi, char *Tx_buf, char *Rx_buf, uint8_t buf_len, GPIO_TypeDef* SS_Port, uint16_t SS_Pin)
{
	HAL_GPIO_WritePin(SS_Port, SS_Pin, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(hspi, (uint8_t *)Tx_buf, (uint8_t *)Rx_buf, buf_len, 100);
	HAL_GPIO_WritePin(SS_Port, SS_Pin, GPIO_PIN_SET);
}

/**
  * @brief Base Layer SPI Uninitialization Function
  * @param SPI Driver
  * @retval None
  */
static void SPI_Deinit(SPI_HandleTypeDef *hspi)
{
	HAL_SPI_DeInit(hspi);
}

#endif /* INC_SPI_LIB_H_ */
