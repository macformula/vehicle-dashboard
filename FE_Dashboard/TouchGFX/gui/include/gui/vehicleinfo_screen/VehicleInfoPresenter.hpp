#ifndef VEHICLEINFOPRESENTER_HPP
#define VEHICLEINFOPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>
//#include "canal_dcu_messages.h"

using namespace touchgfx;

class VehicleInfoView;

class VehicleInfoPresenter : public touchgfx::Presenter, public ModelListener

//The VehicleInfo inherits from the ModelListener class 
{
public:
    VehicleInfoPresenter(VehicleInfoView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~VehicleInfoPresenter() {};

    //virtual void unmarshalVehicleInfoData(void* dataBufferPtr, S_DashMessage receivingDashMessage);
    //virtual void unmarshalDashboardAnswerData(void* dataBufferPtr, S_DashMessage receivingDashMessage);

    //Vehicleinfoview
	virtual void powerPercentage(uint8_t val);
	virtual void socPercentage(uint8_t val);
	virtual void setVehicleSpeed(uint8_t val);
	virtual void setVCU_Errors(uint8_t val);
	virtual void setVehicle_Status(uint8_t val);

private:
    VehicleInfoPresenter();

    VehicleInfoView& view;
};

#endif // VEHICLEINFOPRESENTER_HPP
