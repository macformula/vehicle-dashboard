#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>

class Screen1View : public Screen1ViewBase
{
public:
    Screen1View();
    virtual ~Screen1View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void inverterTemp(uint8_t val);
    virtual void setmotorSpeed(uint8_t val);
    virtual void setVCU_Errors(uint8_t val);
    virtual void setVehicle_Status(uint8_t val);

protected:
};

#endif // SCREEN1VIEW_HPP
