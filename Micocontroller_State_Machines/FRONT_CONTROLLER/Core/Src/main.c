/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "can_msg.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
struct StartupStateMachine {
	enum startup_seq {STANDBY,
					  START_MOTORS,	//Motor startup seq
					  WAIT_BMS,
					  WAIT_START_BTN_PRESS,
					  CONTACTOR_SEQ, //Contactor seq
					  PEDAL,
					  STARTUP_ERROR} startup_state;

	enum contactors_seq {RESET_CONT, CLMPO3, CLMPO4, CLMPO2, OPMPO4, CONTACTOR_COMPLETE} mpo_state;

	enum amk_start_seq {BEGIN_MOTOR_INIT,
						RX_SYS_READY,
						TX_DC_ON,
						RX_QUIT_DC_ON,
						TX_ZERO_TORQUE,
						TX_B_ENABLE,
						TX_B_INVERTER_ON,
						RX_BQ_INTVERTER_ON,
						SET_INITIAL_TORQUE,
						MOTOR_INITIALIZED} amk_start_state;

} startup;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;
ADC_HandleTypeDef hadc2;
ADC_HandleTypeDef hadc3;

CAN_HandleTypeDef hcan1;
CAN_HandleTypeDef hcan3;

SPI_HandleTypeDef hspi4;

TIM_HandleTypeDef htim10;
TIM_HandleTypeDef htim13;
TIM_HandleTypeDef htim14;

/* USER CODE BEGIN PV */
bool state = true;
uint8_t start_pressed = 0;

//-------- CAN BMS --------
uint8_t bms_rx_data[8];
uint8_t mpo2_data[8] = {0};
uint8_t mpo3_data[8] = {0};
uint8_t mpo4_data[8] = {0};

CAN_TxHeaderTypeDef mpo2_tx_header, mpo3_tx_header, mpo4_tx_header;
CAN_RxHeaderTypeDef bms_rx_header;

uint8_t contactor_delay_cnt = 0;
//Boolean checks to see if BMS message received
uint8_t active_rx1 = 0;
uint8_t active_rx2 = 0;


//-------- CAN AMK --------
uint32_t amk_tx_mailbox;
struct can_amk_inverter_amk0_actual_values1_t *amk0_av1;
struct can_amk_inverter_amk0_actual_values2_t *amk0_av2;
struct can_amk_inverter_amk0_set_points1_t *amk0_sp;

struct can_amk_inverter_amk1_actual_values1_t *amk1_av1;
struct can_amk_inverter_amk1_actual_values2_t *amk1_av2;
struct can_amk_inverter_amk1_set_points1_t *amk1_sp;

CAN_RxHeaderTypeDef   powertrain_rx_header;
uint8_t               powertrain_rx_data[8];
uint8_t               amk0_av1_tx_data[8], amk0_av2_tx_data[8], amk0_sp_tx_data[8];

CAN_TxHeaderTypeDef   amk0_av1_tx_header, amk0_av2_tx_header, amk0_sp_tx_header;


//-------- SPI ACCELEROMETER --------
uint8_t data_rec[6];
int16_t x, y, z;
float xg, yg, zg;

CAN_TxHeaderTypeDef   TxHeader, TxHeader2, TxHeader3, TxHeader4;
CAN_RxHeaderTypeDef   RxHeader;
uint8_t               TxData[8] = {0};
uint8_t TxData2[8] = {0};
uint8_t TxData3[8] = {0};
uint8_t TxData4[8] = {0};

uint8_t               RxData[8];
uint32_t              TxMailbox;
int num_receives = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
static void MX_ADC2_Init(void);
static void MX_ADC3_Init(void);
static void MX_CAN3_Init(void);
static void MX_CAN1_Init(void);
static void MX_TIM14_Init(void);
static void MX_TIM13_Init(void);
static void MX_SPI4_Init(void);
static void MX_TIM10_Init(void);
/* USER CODE BEGIN PFP */
static void configure_hardware(void);
static void can_config(void);
static void change_contactor_phase(struct StartupStateMachine *startup);
static void adxl_init (void);
static void adxl_read(uint8_t address);
static void adxl_write(uint8_t address, uint8_t value);

static void perform_motor_step(void);
static void process_amk0_av1(void);
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
  MX_ADC1_Init();
  MX_ADC2_Init();
  MX_ADC3_Init();
  MX_CAN3_Init();
  MX_CAN1_Init();
  MX_TIM14_Init();
  MX_TIM13_Init();
  MX_SPI4_Init();
  MX_TIM10_Init();
  /* USER CODE BEGIN 2 */

  //INITIALIZE CAN, ADC's, GPIO, BRAKE LIGHT, GPS, IMU
  configure_hardware();

  //Initial state machine configuration
  startup.startup_state = WAIT_BMS;
  startup.amk_start_state = BEGIN_MOTOR_INIT;
  startup.mpo_state = RESET_CONT;

  //HAL_Delay(2000);

  adxl_init();

        //startup_state = CONTACTOR_SEQ;
        //mpo_state = SUSPENDED;
        //mpo_state = RESET_CONT;

        //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
  int pin_state, last_pin_state;
  last_pin_state = 1;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  adxl_read(0x32);
	  x = ((data_rec[1]<<8)|data_rec[0]);
	  y = ((data_rec[3]<<8)|data_rec[2]);
	  z = ((data_rec[5]<<8)|data_rec[4]);
	  //convert into g
	  xg = x * .0078;
	  yg = y * .0078;
	  zg = z * .0078;

//	  TxData[0] = (uint8_t)xg;
//	  TxData[1] = (uint8_t)yg;
//	  TxData[2] = (uint8_t)zg;
//
//
//	  HAL_CAN_AddTxMessage(&hcan3, &TxHeader, TxData, &TxMailbox);
//	  HAL_Delay(500);


	  //pin_state = HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_6);
	  if (startup.startup_state == WAIT_START_BTN_PRESS && start_pressed)
	  {
		  //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
		  startup.startup_state = CONTACTOR_SEQ;
		  startup.mpo_state = CLMPO3;
	  }
	  //last_pin_state = pin_state;

	  if (startup.startup_state == START_MOTORS)
		  perform_motor_step();

  }

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 432;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */
  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_10;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief ADC2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC2_Init(void)
{

  /* USER CODE BEGIN ADC2_Init 0 */

  /* USER CODE END ADC2_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC2_Init 1 */

  /* USER CODE END ADC2_Init 1 */
  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc2.Instance = ADC2;
  hadc2.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc2.Init.Resolution = ADC_RESOLUTION_12B;
  hadc2.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc2.Init.ContinuousConvMode = DISABLE;
  hadc2.Init.DiscontinuousConvMode = DISABLE;
  hadc2.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc2.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc2.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc2.Init.NbrOfConversion = 1;
  hadc2.Init.DMAContinuousRequests = DISABLE;
  hadc2.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc2) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_11;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC2_Init 2 */

  /* USER CODE END ADC2_Init 2 */

}

/**
  * @brief ADC3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC3_Init(void)
{

  /* USER CODE BEGIN ADC3_Init 0 */

  /* USER CODE END ADC3_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC3_Init 1 */

  /* USER CODE END ADC3_Init 1 */
  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc3.Instance = ADC3;
  hadc3.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc3.Init.Resolution = ADC_RESOLUTION_12B;
  hadc3.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc3.Init.ContinuousConvMode = DISABLE;
  hadc3.Init.DiscontinuousConvMode = DISABLE;
  hadc3.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc3.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc3.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc3.Init.NbrOfConversion = 1;
  hadc3.Init.DMAContinuousRequests = DISABLE;
  hadc3.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc3) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_12;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC3_Init 2 */

  /* USER CODE END ADC3_Init 2 */

}

/**
  * @brief CAN1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_CAN1_Init(void)
{

  /* USER CODE BEGIN CAN1_Init 0 */

  /* USER CODE END CAN1_Init 0 */

  /* USER CODE BEGIN CAN1_Init 1 */

  /* USER CODE END CAN1_Init 1 */
  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 6;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_9TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_8TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = DISABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = DISABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN1_Init 2 */

  /* USER CODE END CAN1_Init 2 */

}

/**
  * @brief CAN3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_CAN3_Init(void)
{

  /* USER CODE BEGIN CAN3_Init 0 */

  /* USER CODE END CAN3_Init 0 */

  /* USER CODE BEGIN CAN3_Init 1 */

  /* USER CODE END CAN3_Init 1 */
  hcan3.Instance = CAN3;
  hcan3.Init.Prescaler = 6;
  hcan3.Init.Mode = CAN_MODE_NORMAL;
  hcan3.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan3.Init.TimeSeg1 = CAN_BS1_9TQ;
  hcan3.Init.TimeSeg2 = CAN_BS2_8TQ;
  hcan3.Init.TimeTriggeredMode = DISABLE;
  hcan3.Init.AutoBusOff = DISABLE;
  hcan3.Init.AutoWakeUp = DISABLE;
  hcan3.Init.AutoRetransmission = DISABLE;
  hcan3.Init.ReceiveFifoLocked = DISABLE;
  hcan3.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN3_Init 2 */

  /* USER CODE END CAN3_Init 2 */

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
  hspi4.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi4.Init.CLKPhase = SPI_PHASE_2EDGE;
  hspi4.Init.NSS = SPI_NSS_SOFT;
  hspi4.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
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
  * @brief TIM10 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM10_Init(void)
{

  /* USER CODE BEGIN TIM10_Init 0 */

  /* USER CODE END TIM10_Init 0 */

  /* USER CODE BEGIN TIM10_Init 1 */

  /* USER CODE END TIM10_Init 1 */
  htim10.Instance = TIM10;
  htim10.Init.Prescaler = 216-1;
  htim10.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim10.Init.Period = 50000-1;
  htim10.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim10.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim10) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM10_Init 2 */

  /* USER CODE END TIM10_Init 2 */

}

/**
  * @brief TIM13 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM13_Init(void)
{

  /* USER CODE BEGIN TIM13_Init 0 */

  /* USER CODE END TIM13_Init 0 */

  /* USER CODE BEGIN TIM13_Init 1 */

  /* USER CODE END TIM13_Init 1 */
  htim13.Instance = TIM13;
  htim13.Init.Prescaler = 2160-1;
  htim13.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim13.Init.Period = 50000-1;
  htim13.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim13.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim13) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM13_Init 2 */

  /* USER CODE END TIM13_Init 2 */

}

/**
  * @brief TIM14 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM14_Init(void)
{

  /* USER CODE BEGIN TIM14_Init 0 */

  /* USER CODE END TIM14_Init 0 */

  /* USER CODE BEGIN TIM14_Init 1 */

  /* USER CODE END TIM14_Init 1 */
  htim14.Instance = TIM14;
  htim14.Init.Prescaler = 216-1;
  htim14.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim14.Init.Period = 50000-1;
  htim14.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim14.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim14) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM14_Init 2 */

  /* USER CODE END TIM14_Init 2 */

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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3|GPIO_PIN_5, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, GPIO_PIN_0|GPIO_PIN_3, GPIO_PIN_RESET);

  /*Configure GPIO pin : PE4 */
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : PA3 */
  GPIO_InitStruct.Pin = GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PA5 */
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PG0 PG3 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pin : PG6 */
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : PD5 PD6 */
  GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

}

/* USER CODE BEGIN 4 */
static void configure_hardware(void)
{
	can_config();

	HAL_TIM_Base_Start_IT(&htim13);
	//HAL_TIM_Base_Start_IT(&htim10);
	HAL_TIM_Base_Start_IT(&htim14);
}


static void can_config(void)
{
	//Configure Vehicle CAN
	CAN_FilterTypeDef  sFilterConfig;
	sFilterConfig.FilterBank = 0;
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	sFilterConfig.FilterIdHigh = 0x0000;
	sFilterConfig.FilterIdLow = 0x0000;
	sFilterConfig.FilterMaskIdHigh = 0x0000;
	sFilterConfig.FilterMaskIdLow = 0x0000;
	sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
	sFilterConfig.FilterActivation = ENABLE;
	sFilterConfig.SlaveStartFilterBank = 14;

	if (HAL_CAN_ConfigFilter(&hcan3, &sFilterConfig) != HAL_OK)
	  {
	    /* Filter configuration Error */
	    Error_Handler();
	  }

	if (HAL_CAN_Start(&hcan3) != HAL_OK)
	{
	    /* Start Error */
	    Error_Handler();
	}


	//Configure Powertrain CAN
	CAN_FilterTypeDef  sFilterConfig2;
	sFilterConfig2.FilterBank = 0;
	sFilterConfig2.FilterMode = CAN_FILTERMODE_IDMASK;
	sFilterConfig2.FilterScale = CAN_FILTERSCALE_32BIT;
	sFilterConfig2.FilterIdHigh = 0x0000;
	sFilterConfig2.FilterIdLow = 0x0000;
	sFilterConfig2.FilterMaskIdHigh = 0x0000;
	sFilterConfig2.FilterMaskIdLow = 0x0000;
	sFilterConfig2.FilterFIFOAssignment = CAN_RX_FIFO1;
	sFilterConfig2.FilterActivation = ENABLE;
	sFilterConfig2.SlaveStartFilterBank = 14;
	if (HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig2) != HAL_OK)
    {
	   /* Filter configuration Error */
	   Error_Handler();
	}

	if (HAL_CAN_Start(&hcan1) != HAL_OK)
	{
	    /* Start Error */
	    Error_Handler();
	}

	if (HAL_CAN_ActivateNotification(&hcan3, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
	{
		/* Notification Error */
	    Error_Handler();
	}

	if (HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO1_MSG_PENDING) != HAL_OK)
	{
		/* Notification Error */
	    Error_Handler();
	}


	//Configure TX Headers for BMS CAN
	mpo2_tx_header.StdId = 0x400;
	mpo2_tx_header.ExtId = 0;
	mpo2_tx_header.RTR = CAN_RTR_DATA;
	mpo2_tx_header.IDE = CAN_ID_STD;
	mpo2_tx_header.DLC = 8;
	mpo2_tx_header.TransmitGlobalTime = DISABLE;

	mpo3_tx_header.StdId = 0x401;
	mpo3_tx_header.ExtId = 0;
	mpo3_tx_header.RTR = CAN_RTR_DATA;
	mpo3_tx_header.IDE = CAN_ID_STD;
	mpo3_tx_header.DLC = 8;
	mpo3_tx_header.TransmitGlobalTime = DISABLE;

	mpo4_tx_header.StdId = 0x402;
	mpo4_tx_header.ExtId = 0;
	mpo4_tx_header.RTR = CAN_RTR_DATA;
	mpo4_tx_header.IDE = CAN_ID_STD;
	mpo4_tx_header.DLC = 8;
	mpo4_tx_header.TransmitGlobalTime = DISABLE;


	//Configure TX Headers for AMK CAN
	amk0_av1_tx_header.StdId = 0x284;
	amk0_av1_tx_header.ExtId = 0;
	amk0_av1_tx_header.RTR = CAN_RTR_DATA;
	amk0_av1_tx_header.IDE = CAN_ID_STD;
	amk0_av1_tx_header.DLC = 8;
	amk0_av1_tx_header.TransmitGlobalTime = DISABLE;

	amk0_av2_tx_header.StdId = 0x286;
	amk0_av2_tx_header.ExtId = 0;
	amk0_av2_tx_header.RTR = CAN_RTR_DATA;
	amk0_av2_tx_header.IDE = CAN_ID_STD;
	amk0_av2_tx_header.DLC = 8;
	amk0_av2_tx_header.TransmitGlobalTime = DISABLE;

	amk0_sp_tx_header.StdId = 389;
	amk0_sp_tx_header.ExtId = 0;
	amk0_sp_tx_header.RTR = CAN_RTR_DATA;
	amk0_sp_tx_header.IDE = CAN_ID_STD;
	amk0_sp_tx_header.DLC = 8;
	amk0_sp_tx_header.TransmitGlobalTime = DISABLE;


	TxHeader.StdId = 0x111;
	TxHeader.ExtId = 0;
	TxHeader.RTR = CAN_RTR_DATA;
	TxHeader.IDE = CAN_ID_STD;
	TxHeader.DLC = 8;
	TxHeader.TransmitGlobalTime = DISABLE;

}

void change_contactor_phase(struct StartupStateMachine *startup)
{
	if (startup->mpo_state == RESET_CONT)
	{
		mpo2_data[0] = 1;
		mpo3_data[0] = 1;
		mpo4_data[0] = 1;
		//HAL_CAN_AddTxMessage(&hcan3, &mpo2_tx_header, mpo2_data, &TxMailbox);
		//HAL_CAN_AddTxMessage(&hcan3, &mpo3_tx_header, mpo3_data, &TxMailbox);
		//HAL_CAN_AddTxMessage(&hcan3, &mpo4_tx_header, mpo4_data, &TxMailbox);
	}
	else if (startup->mpo_state == CLMPO3)
	{
		mpo2_data[0] = 1;
		mpo3_data[0] = 0;
		mpo4_data[0] = 1;
		//HAL_CAN_AddTxMessage(&hcan3, &mpo2_tx_header, mpo2_data, &TxMailbox);
		//HAL_CAN_AddTxMessage(&hcan3, &mpo3_tx_header, mpo3_data, &TxMailbox);
		//HAL_CAN_AddTxMessage(&hcan3, &mpo4_tx_header, mpo4_data, &TxMailbox);
		startup->mpo_state = CLMPO4;
	}
	else if (startup->mpo_state == CLMPO4)
		{
		mpo2_data[0] = 1;
		mpo3_data[0] = 0;
		mpo4_data[0] = 0;
		//HAL_CAN_AddTxMessage(&hcan3, &mpo2_tx_header, mpo2_data, &TxMailbox);
		//HAL_CAN_AddTxMessage(&hcan3, &mpo3_tx_header, mpo3_data, &TxMailbox);
		//HAL_CAN_AddTxMessage(&hcan3, &mpo4_tx_header, mpo4_data, &TxMailbox);
		}
	else if (startup->mpo_state == CLMPO2)
		{
		mpo2_data[0] = 0;
		mpo3_data[0] = 0;
		mpo4_data[0] = 0;
			//HAL_CAN_AddTxMessage(&hcan3, &mpo2_tx_header, mpo2_data, &TxMailbox);
			//HAL_CAN_AddTxMessage(&hcan3, &mpo3_tx_header, mpo3_data, &TxMailbox);
			//HAL_CAN_AddTxMessage(&hcan3, &mpo4_tx_header, mpo4_data, &TxMailbox);
				startup->mpo_state = OPMPO4;
		}
	else if (startup->mpo_state == OPMPO4)
			{
		mpo2_data[0] = 0;
				mpo3_data[0] = 0;
				mpo4_data[0] = 1;
				//HAL_CAN_AddTxMessage(&hcan3, &mpo2_tx_header, mpo2_data, &TxMailbox);
				//HAL_CAN_AddTxMessage(&hcan3, &mpo3_tx_header, mpo3_data, &TxMailbox);
				//HAL_CAN_AddTxMessage(&hcan3, &mpo4_tx_header, mpo4_data, &TxMailbox);
				startup->mpo_state = CONTACTOR_COMPLETE;
			}
	else
	{
		mpo2_data[0] = 1;
				mpo3_data[0] = 1;
				mpo4_data[0] = 1;
				startup->startup_state = PEDAL;
				//HAL_CAN_AddTxMessage(&hcan3, &mpo2_tx_header, mpo2_data, &TxMailbox);
								//HAL_CAN_AddTxMessage(&hcan3, &mpo3_tx_header, mpo3_data, &TxMailbox);
								//HAL_CAN_AddTxMessage(&hcan3, &mpo4_tx_header, mpo4_data, &TxMailbox);
	}


//	switch (startup.mpo_state)
//	{
//	case RESET_CONT:
//		mpo2_data[0] = 1;
//		mpo3_data[0] = 1;
//		mpo4_data[0] = 1;
//		//HAL_CAN_AddTxMessage(&hcan3, &mpo2_tx_header, mpo2_data, &TxMailbox);
//		//HAL_CAN_AddTxMessage(&hcan3, &mpo3_tx_header, mpo3_data, &TxMailbox);
//		//HAL_CAN_AddTxMessage(&hcan3, &mpo4_tx_header, mpo4_data, &TxMailbox);
//		break;
//
//	case CLMPO3:
//		mpo2_data[0] = 1;
//		mpo3_data[0] = 0;
//		mpo4_data[0] = 1;
////		HAL_CAN_AddTxMessage(&hcan3, &mpo2_tx_header, mpo2_data, &TxMailbox);
////		HAL_CAN_AddTxMessage(&hcan3, &mpo3_tx_header, mpo3_data, &TxMailbox);
////		HAL_CAN_AddTxMessage(&hcan3, &mpo4_tx_header, mpo4_data, &TxMailbox);
//		startup.mpo_state = CLMPO4;
//		break;
//	case CLMPO4: //, CLMPO2, OPMPO4, CONTACTOR_COMPLETE
//		mpo2_data[0] = 1;
//		mpo3_data[0] = 0;
//		mpo4_data[0] = 0;
////		HAL_CAN_AddTxMessage(&hcan3, &mpo2_tx_header, mpo2_data, &TxMailbox);
////		HAL_CAN_AddTxMessage(&hcan3, &mpo3_tx_header, mpo3_data, &TxMailbox);
////		HAL_CAN_AddTxMessage(&hcan3, &mpo4_tx_header, mpo4_data, &TxMailbox);
//		//startup.mpo_state = CLMPO2;
//		break;
//
//	case CLMPO2:
//		mpo2_data[0] = 0;
//		mpo3_data[0] = 0;
//		mpo4_data[0] = 0;
////		HAL_CAN_AddTxMessage(&hcan3, &mpo2_tx_header, mpo2_data, &TxMailbox);
////		HAL_CAN_AddTxMessage(&hcan3, &mpo3_tx_header, mpo3_data, &TxMailbox);
////		HAL_CAN_AddTxMessage(&hcan3, &mpo4_tx_header, mpo4_data, &TxMailbox);
//		startup.mpo_state = OPMPO4;
//		break;
//
//	case OPMPO4:
//		mpo2_data[0] = 0;
//		mpo3_data[0] = 0;
//		mpo4_data[0] = 1;
////		HAL_CAN_AddTxMessage(&hcan3, &mpo2_tx_header, mpo2_data, &TxMailbox);
////		HAL_CAN_AddTxMessage(&hcan3, &mpo3_tx_header, mpo3_data, &TxMailbox);
////		HAL_CAN_AddTxMessage(&hcan3, &mpo4_tx_header, mpo4_data, &TxMailbox);
//		startup.mpo_state = CONTACTOR_COMPLETE;
//		//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
//		break;
//
//	default:
//		mpo2_data[0] = 1;
//		mpo3_data[0] = 1;
//		mpo4_data[0] = 1;
//		startup.startup_state = PEDAL;
////		HAL_CAN_AddTxMessage(&hcan3, &mpo2_tx_header, mpo2_data, &TxMailbox);
////		HAL_CAN_AddTxMessage(&hcan3, &mpo3_tx_header, mpo3_data, &TxMailbox);
////		HAL_CAN_AddTxMessage(&hcan3, &mpo4_tx_header, mpo4_data, &TxMailbox);
//		break;
//	}
}

void adxl_write (uint8_t address, uint8_t value)
{
	uint8_t data[2];
	data[0] = address|0x40;  // multibyte write
	data[1] = value;
	HAL_GPIO_WritePin (GPIOE, GPIO_PIN_4, GPIO_PIN_RESET);  // pull the cs pin low
	HAL_SPI_Transmit (&hspi4, data, 2, 100);  // write data to register
	HAL_GPIO_WritePin (GPIOE, GPIO_PIN_4, GPIO_PIN_SET);  // pull the cs pin high
}

void adxl_read (uint8_t address)
{
	address |= 0x80;  // read operation
	address |= 0x40;  // multibyte read
	uint8_t rec;
	HAL_GPIO_WritePin (GPIOE, GPIO_PIN_4, GPIO_PIN_RESET);  // pull the pin low
	HAL_SPI_Transmit (&hspi4, &address, 1, 100);  // send address
	HAL_SPI_Receive (&hspi4, data_rec, 6, 100);  // receive 6 bytes data
	HAL_GPIO_WritePin (GPIOE, GPIO_PIN_4, GPIO_PIN_SET);  // pull the pin high
}

void adxl_init (void)
{
//	adxl_write (0x31, 0x01);  // data_format range= +- 4g
//	adxl_write (0x2d, 0x00);  // reset all bits
//	adxl_write (0x2d, 0x08);  // power_cntl measure and wake up 8hz

	adxl_write (0x2d, 0x00);  // reset all bits

	adxl_write (0x2d, 0x08);  // measure and wake up 8hz

	adxl_write (0x31, 0x01);  // data_format range= +- 4g
}

void process_amk0_av1(void)
{
	can_amk_inverter_amk0_actual_values1_unpack(amk0_av1, powertrain_rx_data, sizeof(powertrain_rx_data));

	if(startup.amk_start_state == BEGIN_MOTOR_INIT && amk0_av1->amk_b_system_ready == 1)
		startup.amk_start_state = TX_DC_ON;
	else if(startup.amk_start_state == RX_QUIT_DC_ON && amk0_av1->amk_b_quit_dc_on == 1)
		startup.amk_start_state = TX_ZERO_TORQUE;
	else if(startup.amk_start_state == RX_BQ_INTVERTER_ON && amk0_av1->amk_b_quit_inverter_on == 1)
		startup.amk_start_state = SET_INITIAL_TORQUE;
}

void perform_motor_step(void)
{
	switch(startup.amk_start_state)
	{
	case TX_DC_ON:
		amk0_av1->amk_b_dc_on = 1;
		can_amk_inverter_amk0_actual_values1_pack(amk0_av1_tx_data, amk0_av1, sizeof(amk0_av1_tx_data));
		HAL_CAN_AddTxMessage(&hcan1, &amk0_av1_tx_header, amk0_av1_tx_data, &amk_tx_mailbox);
		startup.amk_start_state = RX_QUIT_DC_ON;
		break;

	case TX_ZERO_TORQUE:
		amk0_sp->amk_target_velocity = 0;
		amk0_sp->amk_torque_limit_negativ = 0;
		amk0_sp->amk_torque_limit_positiv = 0;
		can_amk_inverter_amk0_set_points1_pack(amk0_sp_tx_data, amk0_sp, sizeof(amk0_sp_tx_data));
		HAL_CAN_AddTxMessage(&hcan1, &amk0_sp_tx_header, amk0_sp_tx_data, &amk_tx_mailbox);
		startup.amk_start_state = TX_B_ENABLE;
		break;

	case TX_B_ENABLE:
		amk0_sp->amk_b_enable = 1;
		can_amk_inverter_amk0_set_points1_pack(amk0_sp_tx_data, amk0_sp, sizeof(amk0_sp_tx_data));
		HAL_CAN_AddTxMessage(&hcan1, &amk0_sp_tx_header, amk0_sp_tx_data, &amk_tx_mailbox);
		startup.amk_start_state = TX_B_INVERTER_ON;
		break;

	case TX_B_INVERTER_ON:
		amk0_sp->amk_b_inverter_on = 1;
		can_amk_inverter_amk0_set_points1_pack(amk0_sp_tx_data, amk0_sp, sizeof(amk0_sp_tx_data));
		HAL_CAN_AddTxMessage(&hcan1, &amk0_sp_tx_header, amk0_sp_tx_data, &amk_tx_mailbox);
		startup.amk_start_state = RX_BQ_INTVERTER_ON;
		break;

	case SET_INITIAL_TORQUE:
		amk0_sp->amk_target_velocity = 0; //CHANGE
		amk0_sp->amk_torque_limit_negativ = 0;
		amk0_sp->amk_torque_limit_positiv = 0;
		can_amk_inverter_amk0_set_points1_pack(amk0_sp_tx_data, amk0_sp, sizeof(amk0_sp_tx_data));
		HAL_CAN_AddTxMessage(&hcan1, &amk0_sp_tx_header, amk0_sp_tx_data, &amk_tx_mailbox);
		startup.amk_start_state = MOTOR_INITIALIZED;
		startup.startup_state = WAIT_BMS;
		break;

	default:
		break;
	}
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

	if (startup.startup_state == WAIT_START_BTN_PRESS && htim == &htim13)
	{
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
	}


	//CONTACTOR PHASE
	if (htim == &htim14)
	{
		if(startup.mpo_state != CONTACTOR_COMPLETE && startup.startup_state == CONTACTOR_SEQ)
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
		else if (startup.mpo_state == CONTACTOR_COMPLETE)
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);

//		if(startup.startup_state == PEDAL)
//		{
//			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
//		}

		if (startup.mpo_state == CLMPO4 && contactor_delay_cnt < 10)
			contactor_delay_cnt++;
		else if (startup.mpo_state == CLMPO4 && contactor_delay_cnt == 10)
		{
			startup.mpo_state = CLMPO2;
			contactor_delay_cnt = 200;
		}

		change_contactor_phase(&startup);
	}

	if (htim == &htim10)
	{
		if(HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_6) == GPIO_PIN_RESET)
		{
			state = true;
			HAL_TIM_Base_Stop_IT(&htim10);
			start_pressed = 1;
		}

	}


}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
  /* Get RX message */
  if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK)
  {
    /* Reception Error */
    Error_Handler();
  }

  //HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);

  uint32_t id = RxHeader.StdId;

  if (id == 0x4B0)
	  active_rx1 = 1;

  if (id == 0x4B1)
	  active_rx2 = 1;

  //CODE CHECK FOR APPROPRIATE BMS MESSAGE HERE
  if (active_rx1 && active_rx2)
  {
	  startup.startup_state = WAIT_START_BTN_PRESS;
	  //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
  }

}

void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO1, &powertrain_rx_header, powertrain_rx_data) != HAL_OK)
	{
	    /* Reception Error */
	    Error_Handler();
	}

	if(RxHeader.StdId == 644) //AMK0_ActualValues1
	{
		process_amk0_av1();
	}

}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == GPIO_PIN_6 && state == true){
		HAL_TIM_Base_Start_IT(&htim10);
		state = false;
	}


//	if(GPIO_Pin == GPIO_PIN_5)
//	{
//		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, PinState)
//	}

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

  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);

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

