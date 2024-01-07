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
    void displaySocPercentage(uint8_t SocPercentageBuffer);
protected:
};

#endif // VEHICLEINFOVIEW_HPP
