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
/*
//Unmarshals the VehicleInfo: The data for this screen. Calls view after unmarshalling
void VehicleInfoPresenter::unmarshalVehicleInfoData(void* dataBufferPtr, S_DashMessage receivingDashMessage) {

    //Iteration 1: Unmarshalling SocPercentage by placing into uint8_t buffer
    uint8_t SocPercentageBuffer = receivingDashMessage.VehicleInfo.SocPercentage;
    view.displaySocPercentage(SocPercentageBuffer);


}

//Void: Unmarshals the DashboardAnswer data, but does not call the view. since the current screen 
    //(pointed to by the current value of modelListener = the current screen being displayed) is NOT DashAnswer screen
void VehicleInfoPresenter::unmarshalDashboardAnswerData(void* dataBufferPtr, S_DashMessage receivingDashMessage) {

}*/









void VehicleInfoPresenter::socPercentage(uint8_t val)
{
	if (val == 100){
		val =0;
	} else{
		val+=1;
	}
    view.socPercentage(val);
}

void VehicleInfoPresenter::powerPercentage(uint8_t val)
{
	if (val == 100){
		val =0;
	} else{
		val+=1;
	}
    view.powerPercentage(val);
}

void VehicleInfoPresenter::setVehicleSpeed(uint8_t val)
{
	if (val == 100){
		val =0;
	} else{
		val+=1;
	}
    view.setVehicleSpeed(val);
}

void VehicleInfoPresenter::setVCU_Errors(uint8_t val)
{
	if (val == 0){
		val = rand()%10;
	}
    view.setVCU_Errors(val);
}

void VehicleInfoPresenter::setVehicle_Status(uint8_t val)
{
	if (val == 0){
		val = rand()%10;
	}
    view.setVehicle_Status(val);
}

