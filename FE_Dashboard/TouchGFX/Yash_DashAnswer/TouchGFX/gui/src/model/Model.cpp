#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

Model::Model() : modelListener(0)
{
}

void Model::tick()
{
    uint8_t inverterTemp_Counter = 0;
    uint8_t Vehicle_Status = 0;
    uint8_t VCU_Errors = 0;
    uint8_t motorSpeed = 0;

    modelListener->inverterTemp(inverterTemp_Counter);
    modelListener->setmotorSpeed(motorSpeed);
    modelListener->setVCU_Errors(VCU_Errors);
    modelListener->setVehicle_Status(Vehicle_Status);
}
