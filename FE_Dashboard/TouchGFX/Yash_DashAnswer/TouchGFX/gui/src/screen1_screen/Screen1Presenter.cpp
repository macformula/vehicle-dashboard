#include <gui/screen1_screen/Screen1View.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>

Screen1Presenter::Screen1Presenter(Screen1View &v)
    : view(v)
{
}

void Screen1Presenter::activate()
{
}

void Screen1Presenter::deactivate()
{
}

void Screen1Presenter::setmotorSpeed(uint8_t val)
{
    if (val == 100)
    {
        val = 0;
    }
    else
    {
        val += 1;
    }
    view.setmotorSpeed(val);
}

void Screen1Presenter::inverterTemp(uint8_t val)
{
    if (val == 100)
    {
        val = 0;
    }
    else
    {
        val += 1;
    }
    view.inverterTemp(val);
}

void Screen1Presenter::setVCU_Errors(uint8_t val)
{
    if (val == 0)
    {
        val = rand() % 10;
    }
    view.setVCU_Errors(val);
}

void Screen1Presenter::setVehicle_Status(uint8_t val)
{
    if (val == 0)
    {
        val = rand() % 10;
    }
    view.setVehicle_Status(val);
}