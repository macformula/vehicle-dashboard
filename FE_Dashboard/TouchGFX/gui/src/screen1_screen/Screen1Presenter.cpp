#include <gui/screen1_screen/Screen1View.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>
#include <touchgfx/Utils.hpp>

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

void Screen1Presenter::can_Data(char* data)
{
    view.canTest_Data(data);
    
    
    //
    touchgfx_printf("Calling view \n");
}
