#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>

class ModelListener
{
public:
    ModelListener() : model(0) {} //iniitalizes the Model pointer model (under the protected)
        //data members) as equal to 0 or NULL when the modelListener object is first constructed

    virtual ~ModelListener() {}

    void bind(Model *m)
    {
        model = m;
    }

    //virtual void can_Data(char *data) {}; // also defined insScreenPresenter.hpp
    //virtual void can_Data(char* data) {}; // also defined insScreenPresenter.hpp
    virtual void can_Data(char* data) {}; //void function inherited by each screen's class
    //virtual therefore redefined within the subclasses

    //any method functions to use on our screens is defined in modelListener class because the Presenter class is derived from the model listener
    // vs. Model, that just controls ./....?

    virtual void unmarshalVehicleInfoData(void* dataBufferPtr, S_DashMessage receivingDashMessage) {};
    virtual void unmarshalDashboardAnswerData(void* dataBufferPtr, S_DashMessage receivingDashMessage) {};

protected:
    Model *model; //iniitalises model object
};

#endif // MODELLISTENER_HPP
