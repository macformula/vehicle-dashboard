/*
 * canal.h
 *
 *  Created on: Jan 9, 2023
 *      Author: Samuel Parent
 *
 *                    ..::^~~~!!~~~^^:..
 *                .:^!7??JJJJJJJJJJJJ??7!~:.
 *              :~7?JJJ???????????????JJJJ??!^.
 *           .^7?JJJ???JJJJJJ??????????????JJJ?~:
 *          ^7JJ???????777777???JJJJJJJ???????JJ?~.
 *        .!JJ???????????7!~^::::^~!!7??JJ???????J7:
 *       :7JJJ??????????JJJJ??7~:    ..:~7?J??????J?^
 *      .7J???????????????????JJ?!.       :7J??????J?^
 *     .~J??????????????????JJJJ?!.       .7J???????J7.
 *     :?J?????????????JJJJ??7!^.      .:~???????????J~
 *     ^???????????JJJ??7~^:..      .:~7?JJ??????????J!.
 *     ^????????JJ?7~^:.        .:~!?JJJ?????????????J!.
 *     ^????????!^.          .:~7?JJJ????????????????J!.
 *     .7J????!.            :7?JJ?????????????????????^
 *      ~JJ?J7.             ~JJJJ???????????????????J!.
 *      .!J???^.            .^!7?JJJJJJ????????????J7:
 *       .!?J??7^.              .:^~!7???JJJJJ????J7:
 *        .^?JJJJ?7~.                 ..:^~~!7????!.
 *          .!?JJJJ?:                         ..::
 *            :~??!:
 *              ..
 */

#ifndef INC_CANAL_H_
#define INC_CANAL_H_

/*********************************************************
*                       INCLUDES
*********************************************************/

#include <stdint.h>
#include <stdbool.h>
#include "main.h"
#include "canal_types.h"

// NOTE: Must add ECU specific autogen code here for each new ECU
#if defined __has_include
    #if 	__has_include("canal_vcu_messages.h")
    #include "canal_vcu_messages.h"
    #elif 	__has_include("canal_tms_messages.h")
    #include "canal_tms_messages.h"
    #elif 	__has_include("canal_lvcontroller_messages.h")
    #include "canal_lvcontroller_messages.h"
 	#elif 	__has_include("canal_fc_messages.h")
    #include "canal_fc_messages.h"
    #endif
#endif
/*********************************************************
*                       MACROS
*********************************************************/

#define FREQ_MHZ						(1000000U)
#define NUM_SUPPORTED_PCKL1_FREQ 		(2U)
#define NUM_SUPPORTED_CAN_BITRATES		(4U)
#define NUM_BITRATE_ENTRIES				(NUM_SUPPORTED_CAN_BITRATES * NUM_SUPPORTED_PCKL1_FREQ)
#define DEFAULT_SYNC_JW 				(CAN_SJW_1TQ)
#define DEFAULT_RX_FIFO					(CAN_RX_FIFO0)

#define DEFAULT_FILTER_BANK				(0)
#define DEFAULT_FILTER_MODE				(CAN_FILTERMODE_IDMASK)
#define DEFAULT_FILTER_SCALE			(CAN_FILTERSCALE_32BIT)
#define DEFAULT_FILTER_ID_HIGH			(0x0000)
#define DEFAULT_FILTER_ID_LOW 			(0x0000)
#define DEFAULT_FILTER_MASK_ID_HIGH 	(0x0000)
#define DEFAULT_FILTER_MASK_ID_LOW		(0x0000)
#define DEFAULT_FILTER_ACTIVATION 		(ENABLE)
#define DEFAULT_FILTER_SLAVE_START_BANK (14)

#define IS_CANAL_BAUDRATE(__baud__) ((__baud__ == CANAL_BAUD_100K) || \
									 (__baud__ == CANAL_BAUD_250K) || \
									 (__baud__ == CANAL_BAUD_500K) || \
									 (__baud__ == CANAL_BAUD_1M))

#define IS_CANAL_MODE(__mode__)		((__mode__ == CANAL_MODE_NORMAL)			|| \
									 (__mode__ == CANAL_MODE_LOOPBACK)			|| \
									 (__mode__ == CANAL_MODE_SILENT_LOOPBACK) 	|| \
									 (__mode__ == CANAL_MODE_SILENT))

/*********************************************************
*                       TYPES
*********************************************************/

// TeCanALMode enumerates the modes in which the Can hardware operates
typedef enum {
	CANAL_MODE_UNKNOWN = 0,
	// CAN_NORMAL is a mode that supports tx/rx but cannot transmit to itself
	CANAL_MODE_NORMAL = CAN_MODE_NORMAL,
	// CANAL_MODE_LOOPBACK is a mode that ignores the rx line and transmits
	// messages to itself. The tx line will still send messages over the bus.
	// This should ONLY be used for testing purposes.
	CANAL_MODE_LOOPBACK = CAN_MODE_LOOPBACK,
	// CANAL_MODE_SILENT_LOOPBACK is a mode that ignores the rx line and transmits
	// messages to itself. The tx line will NOT send messages over the bus.
	// This should ONLY be used for testing purposes.
	CANAL_MODE_SILENT_LOOPBACK = CAN_MODE_SILENT_LOOPBACK,
	// CAN_SILENT is a mode that will disable the TX line.
	CANAL_MODE_SILENT = CAN_MODE_SILENT,
	// NOTE: CAN_LOOPBACK is not supported as we do not want to classify a message
	// as receivable if it can only be received by the same node that send it.
	// This feature may be good for debugging needs, but not for production.
}TeCanALMode;

// TeCanALBaud enumerates the supported can bus baudrates (aka bitrates)
typedef enum {
	CANAL_UNKNOWN_BAUD,
	CANAL_BAUD_100K = 	((uint16_t)100),
	CANAL_BAUD_250K = 	((uint16_t)250),
	CANAL_BAUD_500K = 	((uint16_t)500),
	CANAL_BAUD_1M = 	((uint16_t)1000),
}TeCanALBaud;

typedef enum {
	CANAL_INST_UNKNOWN = 0,
	CANAL_INST_CAN_1,
	CANAL_INST_CAN_2,
	CANAL_INST_CAN_3,
}TeCanALInstance;

typedef struct {
	CAN_HandleTypeDef* hcan;
	TeCanALInstance canNum;
	TeCanALBaud baud;
	TeCanALMode mode;
}TsCanAL;

/*********************************************************
*               PUBLIC FUNCTION DECLARATIONS
*********************************************************/

// CanAL_Init initializes CAN hardware and must be called with successful return
// before any other CAN functions
TeCanALRet CanAL_Init(TsCanAL* can);
// CanAL_Receive is meant to be called in HAL_CAN_RxFifo0MsgPendingCallback
TeCanALRet CanAL_Receive(TsCanAL* can);
// TODO: CanAL_Transmit will send the global message struct associated with the
// messageID provided
TeCanALRet CanAL_Transmit(TsCanAL* can, TeMessageID messageID);
// TODO: CanAL_Time_Since_Updated returns the amount of time since the message
// associated with messageID provided was last updated in milliseconds
uint8_t CanAL_Time_Since_Updated(TeMessageID messageID);

#endif /* INC_CAN_H_ */
