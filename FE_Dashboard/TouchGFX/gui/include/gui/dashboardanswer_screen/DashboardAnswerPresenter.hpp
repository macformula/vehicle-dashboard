#ifndef DASHBOARDANSWERPRESENTER_HPP
#define DASHBOARDANSWERPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>
#include "canal_dcu_messages.h"

using namespace touchgfx;

class DashboardAnswerView;

class DashboardAnswerPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    DashboardAnswerPresenter(DashboardAnswerView& v);

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

    virtual ~DashboardAnswerPresenter() {};

    virtual void unmarshalVehicleInfoData(void* dataBufferPtr, S_DashMessage receivingDashMessage);
    virtual void unmarshalDashboardAnswerData(void* dataBufferPtr, S_DashMessage receivingDashMessage);

private:
    DashboardAnswerPresenter();

    DashboardAnswerView& view;
};

#endif // DASHBOARDANSWERPRESENTER_HPP
