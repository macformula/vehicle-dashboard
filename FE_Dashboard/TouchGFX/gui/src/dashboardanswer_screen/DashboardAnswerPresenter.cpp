#include <gui/dashboardanswer_screen/DashboardAnswerView.hpp>
#include <gui/dashboardanswer_screen/DashboardAnswerPresenter.hpp>

DashboardAnswerPresenter::DashboardAnswerPresenter(DashboardAnswerView& v)
    : view(v)
{

}

void DashboardAnswerPresenter::activate()
{

}

void DashboardAnswerPresenter::deactivate()
{

}

//Void: Unmarshals the VehicleInfo data, but does not call the view. since the current screen 
    //(pointed to by the current value of modelListener = the current screen being displayed) is NOT VehicleInfo screen
void DashboardAnswerPresenter::unmarshalVehicleInfoData(void* dataBufferPtr, S_DashMessage receivingDashMessage) {

}

//Unmarshals the VehicleInfo: The data for this screen. Calls view after unmarshalling
void DashboardAnswerPresenter::unmarshalDashboardAnswerData(void* dataBufferPtr, S_DashMessage receivingDashMessage) {

}