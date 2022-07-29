/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef SETTINGSVIEWBASE_HPP
#define SETTINGSVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/settings_screen/SettingsPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/ButtonWithIcon.hpp>
#include <touchgfx/containers/scrollers/ScrollList.hpp>
#include <gui/containers/Settings_Toggle.hpp>
#include <touchgfx/mixins/ClickListener.hpp>

class SettingsViewBase : public touchgfx::View<SettingsPresenter>
{
public:
    SettingsViewBase();
    virtual ~SettingsViewBase() {}
    virtual void setupScreen();

    virtual void scrollList1UpdateItem(Settings_Toggle& item, int16_t itemIndex)
    {
        // Override and implement this function in Settings
    }

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box __background;
    touchgfx::Box box1;
    touchgfx::ClickListener< touchgfx::ButtonWithIcon > buttonWithIcon1;
    touchgfx::ScrollList scrollList1;
    touchgfx::DrawableListItems<Settings_Toggle, 6> scrollList1ListItems;

private:

    /*
     * Callback Declarations
     */
    touchgfx::Callback<SettingsViewBase, const touchgfx::AbstractButton&> buttonCallback;
    touchgfx::Callback<SettingsViewBase, touchgfx::DrawableListItemsInterface*, int16_t, int16_t> updateItemCallback;

    /*
     * Callback Handler Declarations
     */
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);
    void updateItemCallbackHandler(touchgfx::DrawableListItemsInterface* items, int16_t containerIndex, int16_t itemIndex);

};

#endif // SETTINGSVIEWBASE_HPP