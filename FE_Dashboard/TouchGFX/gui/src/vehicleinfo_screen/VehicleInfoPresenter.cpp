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

//Unmarshals the VehicleInfo: The data for this screen. Calls view after unmarshalling
//Data to be unmarshalled lies in: receivingDashMessage.receivingVehicleInfo. this was copied in from the message queue
void VehicleInfoPresenter::unmarshalVehicleInfoData(void* dataBufferPtr, S_DashMessage receivingDashMessage) {
	
	//TODO: check if these are all of uint8_t type (typematch the buffers to the actual data)

    // Cast dataBufferPtr to the correct type, TsVehicleInfo*. since dataBufferPtr comes in as void*
    TsVehicleInfo* vehicleInfoPtr = static_cast<TsVehicleInfo*>(dataBufferPtr);

    // Copy the data from the receivingDashMessage packet's VehicleInfo slot into the provided buffer
    *vehicleInfoPtr = receivingDashMessage.VehicleInfo;  //deref the memory location and assign its rvalue equal to the info in receivingDashMessage.VehicleInfo

	//Unmarshal SocPercentage
	uint8_t SocPercentageBuffer = vehicleInfoPtr->SocPercentage;
	view.socPercentage(SocPercentageBuffer);

	//Unmarshal powerPercentage
    uint8_t powerPercentageBuffer = vehicleInfoPtr->MaximumPowerAvailablePercentage; //must reference correct data member from the VehicleInfo struct definition
	//TODO: buffer names + view-side display functions should match the struct data member that they are displaying i.e. powerPercentageBuffer => MaximumPowerAvailablePercentage
	view.powerPercentage(powerPercentageBuffer);

	//Unmarshal vehicleSpeed
    uint8_t vehicleSpeedBuffer = vehicleInfoPtr->VehicleSpeed; //must reference correct data member from the VehicleInfo struct definition
	view.setVehicleSpeed(vehicleSpeedBuffer);

	//Unmarshal vehicleStatus
    uint8_t vehicleStatusBuffer = vehicleInfoPtr->VehicleStatus; //must reference correct data member from the VehicleInfo struct definition
	view.setVehicle_Status(vehicleStatusBuffer);

//Previous:
    // //Iteration 1: Unmarshalling SocPercentage by placing into uint8_t buffer
    // uint8_t SocPercentageBuffer = receivingDashMessage.VehicleInfo.SocPercentage;
	// view.socPercentage(val);
    //view.displaySocPercentage(SocPercentageBuffer);
}

//Void: Unmarshals the DashboardAnswer data, but does not call the view. since the current screen 
    //(pointed to by the current value of modelListener = the current screen being displayed) is NOT DashAnswer screen
void VehicleInfoPresenter::unmarshalDashboardAnswerData(void* dataBufferPtr, S_DashMessage receivingDashMessage) {



}



