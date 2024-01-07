#include <gui/vehicleinfo_screen/VehicleInfoView.hpp>
#include <gui/vehicleinfo_screen/VehicleInfoPresenter.hpp>

VehicleInfoPresenter::VehicleInfoPresenter(VehicleInfoView& v)
    : view(v)
{

}

void VehicleInfoPresenter::activate()
{

}

void VehicleInfoPresenter::deactivate()
{

}

// //Unmarshals the VehicleInfo 
// void VehicleInfoPresenter::unmarshalVehicleInfoData()
// {



// }

//Unmarshals the VehicleInfo: The data for this screen. Calls view after unmarshalling
void VehicleInfoPresenter::unmarshalVehicleInfoData(void* dataBufferPtr, S_DashMessage receivingDashMessage) {

    //Iteration 1: Unmarshalling SocPercentage by placing into uint8_t buffer
    uint8_t SocPercentageBuffer = receivingDashMessage.VehicleInfo.SocPercentage;
    view.displaySocPercentage(SocPercentageBuffer);


}

//Void: Unmarshals the DashboardAnswer data, but does not call the view. since the current screen 
    //(pointed to by the current value of modelListener = the current screen being displayed) is NOT DashAnswer screen
void VehicleInfoPresenter::unmarshalDashboardAnswerData(void* dataBufferPtr, S_DashMessage receivingDashMessage) {

}


