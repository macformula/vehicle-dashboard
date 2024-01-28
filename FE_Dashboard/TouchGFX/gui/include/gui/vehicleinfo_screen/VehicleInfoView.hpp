#ifndef VEHICLEINFOVIEW_HPP
#define VEHICLEINFOVIEW_HPP

#include <gui_generated/vehicleinfo_screen/VehicleInfoViewBase.hpp>
#include <gui/vehicleinfo_screen/VehicleInfoPresenter.hpp>

class VehicleInfoView : public VehicleInfoViewBase
{
public:
    VehicleInfoView();
    virtual ~VehicleInfoView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    //display functions
    //void displaySocPercentage(uint8_t SocPercentageBuffer);

    //Vehicleinfoview
	virtual void powerPercentage(uint8_t val);
	virtual void socPercentage(uint8_t val);
	virtual void setVehicleSpeed(uint8_t val);
	virtual void setVCU_Errors(uint8_t val);
	virtual void setVehicle_Status(uint8_t val);
protected:
};

#endif // VEHICLEINFOVIEW_HPP
