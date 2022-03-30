/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/settings_screen/SettingsViewBase.hpp>
#include <touchgfx/Color.hpp>
#include "BitmapDatabase.hpp"

SettingsViewBase::SettingsViewBase() :
    buttonCallback(this, &SettingsViewBase::buttonCallbackHandler),
    updateItemCallback(this, &SettingsViewBase::updateItemCallbackHandler)
{

    __background.setPosition(0, 0, 480, 272);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));

    box1.setPosition(0, 0, 480, 272);
    box1.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));

    buttonWithIcon1.setXY(0, 0);
    buttonWithIcon1.setBitmaps(touchgfx::Bitmap(BITMAP_BLUE_BUTTONS_ROUND_EDGE_ICON_BUTTON_ID), touchgfx::Bitmap(BITMAP_BLUE_BUTTONS_ROUND_EDGE_ICON_BUTTON_PRESSED_ID), touchgfx::Bitmap(BITMAP_BLUE_ICONS_BACK_ARROW_32_ID), touchgfx::Bitmap(BITMAP_BLUE_ICONS_BACK_ARROW_32_ID));
    buttonWithIcon1.setIconXY(22, 15);
    buttonWithIcon1.setAction(buttonCallback);

    scrollList1.setPosition(68, 0, 403, 272);
    scrollList1.setHorizontal(false);
    scrollList1.setCircular(false);
    scrollList1.setEasingEquation(touchgfx::EasingEquations::backEaseOut);
    scrollList1.setSwipeAcceleration(10);
    scrollList1.setDragAcceleration(10);
    scrollList1.setNumberOfItems(7);
    scrollList1.setPadding(0, 0);
    scrollList1.setSnapping(false);
    scrollList1.setDrawableSize(59, 0);
    scrollList1.setDrawables(scrollList1ListItems, updateItemCallback);

    add(__background);
    add(box1);
    add(buttonWithIcon1);
    add(scrollList1);
}

void SettingsViewBase::setupScreen()
{
    scrollList1.initialize();
    for (int i = 0; i < scrollList1ListItems.getNumberOfDrawables(); i++)
    {
        scrollList1ListItems[i].initialize();
    }
}

void SettingsViewBase::buttonCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &buttonWithIcon1)
    {
        //Interaction1
        //When buttonWithIcon1 clicked change screen to Dashboard
        //Go to Dashboard with screen transition towards South
        application().gotoDashboardScreenSlideTransitionSouth();
    }
}

void SettingsViewBase::updateItemCallbackHandler(touchgfx::DrawableListItemsInterface* items, int16_t containerIndex, int16_t itemIndex)
{
    if (items == &scrollList1ListItems)
    {
        touchgfx::Drawable* d = items->getDrawable(containerIndex);
        Settings_Toggle* cc = (Settings_Toggle*)d;
        scrollList1UpdateItem(*cc, itemIndex);
    }
}
