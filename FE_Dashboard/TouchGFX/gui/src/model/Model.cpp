#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include <cstring>
#include <touchgfx/Utils.hpp>

//method func implementations for the Model class def

#ifndef SIMULATOR //SIMULATOR indicates only will run following includes + extern if running in TouchGFX simulator

#include "main.h" //needs main.h to import canData_t class definition
#include "cmsis_os2.h" //needs this import to use os message queueing

/*
extern "C"
{
    extern osMessageQueueId_t canQueueHandle;
    canData_t *canData_r; //a new struct for the receiving/gui end
}
#endif*/

Model::Model() : modelListener(0)
{
}

void Model::tick()
{
    uint8_t socPercentage_Counter = 0;
	uint8_t powerPercentage_Counter = 0;
	uint8_t vehicleSpeed = 0;
	uint8_t VCU_Errors = 0;
	uint8_t Vehicle_Status = 0;

	modelListener->powerPercentage(powerPercentage_Counter);
	modelListener->socPercentage(socPercentage_Counter);
	modelListener->setVehicleSpeed(vehicleSpeed);
	modelListener->setVCU_Errors(VCU_Errors);
	modelListener->setVehicle_Status(Vehicle_Status);
    /*
#ifndef SIMULATOR //will run this code only when flashed and running on the board, therefore not a touchGFX simulator run
    if (osMessageQueueGetCount(canQueueHandle) > 0)
    {
        if (osMessageQueueGet(canQueueHandle, &canData_r, 0, 0) == osOK)
        {
            strncpy(Model::getRData(), canData_r->Data, canData_r->size);
            modelListener->can_Data(Model::getRData()); //modellistner is a pointer to thec urrently actively presenter object
        }
    }

#endif

    //gui-side test 1: Test comms from Model() tso display on Presenter->View via function canData()
    char guiTest[] = "guiTest";
    strncpy(Model::getRData(), guiTest, strlen(guiTest));
    //call canData() now to display
    modelListener->can_Data(Model::getRData());
    //modelListener->can_Data(RData);
    //modelListener->can_Data();
    touchgfx_printf("Called model func \n");

    //strncpy(Model::getRData(), stringTest, sizeof(stringTest)); just to test whether the gui/model side functions are working
    */
}
