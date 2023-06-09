#ifndef CONSOLEPRESENTER_HPP
#define CONSOLEPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class ConsoleView;

class ConsolePresenter : public touchgfx::Presenter, public ModelListener
{
public:
    ConsolePresenter(ConsoleView &v);

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

    virtual ~ConsolePresenter(){};

    virtual void dataRxed();

private:
    ConsolePresenter();

    ConsoleView &view;
};

#endif // CONSOLEPRESENTER_HPP
