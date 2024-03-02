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

//Global instances of receiving-end message structs: 'data buffer' structs
    //using the defined message struct types, inits the global structs of these typedefs to store messages in
    //volatile: filled at runtime, changing
volatile TsVehicleInfo          receivingVehicleInfo;
volatile TsDashboardAnswer      receivingDashboardAnswer;
volatile TsDashboardQuestion    receivingDashboardQuestion;

S_DashMessage receivingDashMessage; //canQueue from .c copies incoming message into receiving-side struct
//holds its own local instances of each type of data buffer struct


// ----------------- getDataBuffer(): return ptr to correct 'data buffer' struct to copy incoming data into
struct dataBuffer {
    TeMessageId canMessageId;
    void* dataBufferStructPtr; //void ptr to point to struct of some type
}

struct dataBuffer DATA_BUFFER_PTR_TABLE[NUM_RX_MESSAGES] = {
    {VEHICLEINFO_CANAL_ID, (void*)&receivingVehicleInfo}, 
    {DASHBOARDANSWER_CANAL_ID, (void*)&receivingDashboardAnswer}
}

//getter: given the canID stored in incoming DashMessage packet, returns pointer to global data buffer struct to copy data into
void* Model::getDataBuffer(TeMessageID canMessageId) {

    for (int i = 0; i < NUM_RX_MESSAGES; i++) { //Iterate through each struct in struct table
        if ((DATA_BUFFER_PTR_TABLE[i].canMessageId == canMessageId)) {

             return DATA_BUFFER_PTR_TABLE[i].dataBufferStructPtr;

        }
    }
}

Model::Model() : modelListener(0)
{
}

void Model::tick() //MAIN: Encapsulates what will be run at each tick of display
{

#ifndef SIMULATOR //Will run this code only when flashed and running on the board, therefore not a touchGFX simulator run
    if (osMessageQueueGetCount(canVehicleInfoQueue) > 0)
    {
        if (osMessageQueueGet(canVehicleInfoQueue, &receivingDashMessage, 0, 0) == osOK)
        {

            //Extract ID of incoming message
            TeMessageID canMessageId = receivingDashMessage.canMessageId;

            //given the ID, identify the required unmarshal function to call on modelListener: 
            switch (canMessageId) {
                case(VEHICLEINFO_CANAL_ID):
                    //will pass in the void* ptr for the data struct buffer and will be cast to the correct type within the corresponding unmarshal function
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
