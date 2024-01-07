#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include <cstring>
#include <touchgfx/Utils.hpp>

//method func implementations for the Model class def

#ifndef SIMULATOR //SIMULATOR indicates only will run following includes + extern if running in TouchGFX simulator

#include "canal_dcu_messages.h" //needs this import to access the required CAN message queues for the different message structs
#include "main.h" //needs main.h to import canData_t class definition - from M1 testing
#include "cmsis_os2.h" //needs this import to use os message queueing API CMSIS-RTOS2

extern "C"
{
   osMessageQueueId_t canVehicleInfoQueue;
}
#endif

//Global instances of receiving-end message structs
    //using the defined message struct types, inits the global structs of these typedefs to store messages in
volatile TsVehicleInfo          receivingVehicleInfo;
volatile TsDashboardAnswer      receivingDashboardAnswer;
volatile TsDashboardQuestion    receivingDashboardQuestion;

S_DashMessage receivingDashMessage;

Model::Model() : modelListener(0)
{
}

// ----- GETDATABUFFER Pointer table AND GETTER: For struct data buffers

//define struct for ptr table format of each element
struct dataBuffer {
    TeMessageID canMessageId;
    void* dataBufferPtr; 
};

struct dataBuffer DATA_BUFFER_PTR_TABLE[NUM_RX_MESSAGES] = {
    {VEHICLEINFO_CANAL_ID, (void*)&receivingVehicleInfo},
    {DASHBOARDANSWER_CANAL_ID, (void*)&receivingDashboardAnswer}
};

void* Model::getDataBuffer(TeMessageID canMessageId) {

    //Iterate through DATA_BUFFER_PTR Table
    for (int i = 0; i < NUM_RX_MESSAGES; i++) { //Iterate through each struct in struct table
        if ((DATA_BUFFER_PTR_TABLE[i].canMessageId == canMessageId)) {

            return DATA_BUFFER_PTR_TABLE[i].dataBufferPtr;
        }

    }
}

// ---- SCREEN UNMARSHALLER: Removed from newest update -----

// //typedef custom function pointer type ScreenUnmarshaller: 
//     //Each unmarshaller has:
//         //void* return type
//         //getDataBuffer() are parameter therefore returns void* data type as parameter: void* parameter
// typedef void (*ScreenUnmarshaller)(void* dataBufferPtr, S_DashMessage receivingDashMessage);

// //Define global instance of function pointer void* screenUnmarshaller to store the current screenUnmarshaller for incoming message
// ScreenUnmarshaller screenUnmarshaller;

// struct unmarshalStruct {
//     TeMessageID canMessageId;
//     //Func ptr to screenUnmarshallers
//     int unmarshallerId;
// };

// struct unmarshalStruct SCREEN_UNMARSHAL_TABLE[NUM_RX_MESSAGES] = {
//       //Not reading the functions?
//     {VEHICLEINFO_CANAL_ID, 0},
//     {DASHBOARDANSWER_CANAL_ID, 1}
// };

// int getScreenUnmarshaller(TeMessageID canMessageId) {

//     for (int i = 0; i < NUM_RX_MESSAGES; i++) {
//         if (canMessageId == SCREEN_UNMARSHAL_TABLE[i].canMessageId) {
//             return SCREEN_UNMARSHAL_TABLE[i].unmarshallerId;
//         }
//     }

//     return -1;

// }

void Model::tick() //MAIN: Encapsulates what will be run at each tick of display
{

#ifndef SIMULATOR //Will run this code only when flashed and running on the board, therefore not a touchGFX simulator run
    if (osMessageQueueGetCount(canVehicleInfoQueue) > 0)
    {
        if (osMessageQueueGet(canVehicleInfoQueue, &receivingDashMessage, 0, 0) == osOK)
        {

            //Extract ID of incoming message
            TeMessageID canMessageId = receivingDashMessage.canMessageId;
            switch (canMessageId) {
                case(VEHICLEINFO_CANAL_ID):
                    modelListener->unmarshalVehicleInfoData(Model::getDataBuffer(canMessageId), receivingDashMessage);
                    break;

                case(DASHBOARDANSWER_CANAL_ID):
                    modelListener->unmarshalDashboardAnswerData(Model::getDataBuffer(canMessageId), receivingDashMessage);
                    break;
            }
        }
    }
    
#endif

}
