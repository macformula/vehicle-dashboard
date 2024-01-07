#include <gui/vehicleinfo_screen/VehicleInfoView.hpp>

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
