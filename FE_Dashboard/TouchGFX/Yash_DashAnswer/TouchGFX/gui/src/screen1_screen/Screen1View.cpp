#include <gui/screen1_screen/Screen1View.hpp>

Screen1View::Screen1View()
{
}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

void Screen1View::setVCU_Errors(uint8_t val)
{
    Unicode::snprintf(VCU_ErrorBuffer, VCU_ERROR_SIZE, "%d", val);
    VCU_Error.invalidate();
}

void Screen1View::setVehicle_Status(uint8_t val)
{
    Unicode::snprintf(VEH_statusBuffer, VEH_STATUS_SIZE, "%d", val);
    VEH_status.invalidate();
}

void Screen1View::inverterTemp(uint8_t val)
{
    Unicode::snprintf(Inv_TempBuffer, INV_TEMP_SIZE, "%d", val);
    Inv_Temp.invalidate();
}

void Screen1View::setmotorSpeed(uint8_t val)
{
    Mspeedg.setValue(val);
    Mspeedg.invalidate();
    Unicode::snprintf(MspeedBuffer, MSPEED_SIZE, "%d", val);
    Mspeed.invalidate();
}