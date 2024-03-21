#include <gui/vehicleinfo_screen/VehicleInfoView.hpp>
#include <gui_generated/vehicleinfo_screen/VehicleInfoViewBase.hpp>

VehicleInfoView::VehicleInfoView()
{

}

void VehicleInfoView::setupScreen()
{
    VehicleInfoViewBase::setupScreen();
}

void VehicleInfoView::tearDownScreen()
{
    VehicleInfoViewBase::tearDownScreen();
}
void VehicleInfoView::displaySocPercentage(uint8_t SocPercentageBuffer)
{
    char strBuffer[10];
    // Convert uint8_t to string using sprintf
    sprintf(strBuffer, "%u", SocPercentageBuffer);

    Unicode::strncpy(textArea1Buffer, strBuffer, strlen(strBuffer));
    textArea1.invalidate(); //final line for display
}

//TODO: change all display functions to be named display<Data>

void VehicleInfoView::setVehicleSpeed(uint8_t val){
    Speed_gauge.setValue(val);
    Speed_gauge.invalidate();
    Unicode::snprintf(VehicleSpeedTextBuffer, VEHICLESPEEDTEXT_SIZE, "%d", val);
    VehicleSpeedText.invalidate();
}

void VehicleInfoView::socPercentage(uint8_t val){
    Soc_progressbar.setValue(val);
    Soc_textProgress.setValue(val);

}

void VehicleInfoView::powerPercentage(uint8_t val){
    Power_progressbar.setValue(val);
}

void VehicleInfoView::setVCU_Errors(uint8_t val)
{
    Unicode::snprintf(VCU_Error_textBuffer, VCU_ERROR_TEXT_SIZE, "%d", val);
    VCU_Error_text.invalidate();
}

void VehicleInfoView::setVehicle_Status(uint8_t val)
{
    Unicode::snprintf(Vehicle_Status_textBuffer, VEHICLE_STATUS_TEXT_SIZE, "%d", val);
    Vehicle_Status_text.invalidate();
}
