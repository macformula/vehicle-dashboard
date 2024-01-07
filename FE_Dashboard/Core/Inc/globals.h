/*
 * globals.h
 *
 *  Created on: May 21, 2023
 *      Author: Samuel Parent
 */

#ifndef INC_GLOBALS_H_
#define INC_GLOBALS_H_

/*********************************************************
*                       INCLUDES
*********************************************************/

#include "stdint.h"
#include "adc.h"
#include "canal.h"
#include "uart.h"
#include <pthread.h>

/*********************************************************
*                       DEFINES
*********************************************************/

#define DEBUG_MODE 0

// ADC:
#define APPS1_ADC_CHANNEL 					(10)
#define APPS1_BUFFER_LEN 					(10)

#define APPS2_ADC_CHANNEL 					(11)
#define APPS2_BUFFER_LEN 					(10)

#define STEERING_ANGLE_SENSOR_ADC_CHANNEL 	(12)
#define STEERING_ANGLE_SENSOR_BUFFER_LEN 	(10)

#define BPPS_BUFFERED 						(13)
#define BPPS_BUFFERED_BUFFER_LEN 			(10)

#define ADC1_NUM_CHANNELS 					(4)

// CAN:
#define PT1_CAN_INST 						(CANAL_INST_CAN_1)
#define PT1_CAN_BAUD						(CANAL_BAUD_500K)
#if DEBUG_MODE
#define PT1_CAN_MODE						(CANAL_MODE_SILENT_LOOPBACK)
#else
#define PT1_CAN_MODE						(CANAL_MODE_NORMAL)
#endif // DEBUG_MODE

#define PT2_CAN_INST						(CANAL_INST_CAN_2)
#define PT2_CAN_BAUD						(CANAL_BAUD_500K)
#define PT2_CAN_MODE						(CANAL_MODE_SILENT_LOOPBACK)

#define VEH_CAN_INST						(CANAL_INST_CAN_3)
#define VEH_CAN_BAUD						(CANAL_BAUD_500K)
#if DEBUG_MODE
#define VEH_CAN_MODE						(CANAL_MODE_SILENT_LOOPBACK)
#else
#define VEH_CAN_MODE						(CANAL_MODE_NORMAL)
#endif // DEBUG_MODE

extern TsCanAL veh_can;

/*********************************************************
*                        CAN
*********************************************************/

extern pthread_mutex_t can_lock;

CAN_HandleTypeDef hcan1;
CAN_HandleTypeDef hcan2;
CAN_HandleTypeDef hcan3;

TsCanAL veh_can = {
	.hcan = &hcan3,
	.canNum = VEH_CAN_INST,
	.baud = VEH_CAN_BAUD,
	.mode = VEH_CAN_MODE,
};

#endif /* INC_GLOBALS_H_ */
