#ifndef DASHBOARDANSWERVIEW_HPP
#define DASHBOARDANSWERVIEW_HPP

#include <gui_generated/dashboardanswer_screen/DashboardAnswerViewBase.hpp>
#include <gui/dashboardanswer_screen/DashboardAnswerPresenter.hpp>

class DashboardAnswerView : public DashboardAnswerViewBase
{
public:
    DashboardAnswerView();
    virtual ~DashboardAnswerView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // DASHBOARDANSWERVIEW_HPP
