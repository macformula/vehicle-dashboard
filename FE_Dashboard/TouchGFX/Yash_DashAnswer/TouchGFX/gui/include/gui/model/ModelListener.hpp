#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>
#include <stdint.h>

class ModelListener
{
public:
    ModelListener() : model(0) {}

    virtual ~ModelListener() {}

    void bind(Model *m)
    {
        model = m;
    }

    virtual void inverterTemp(uint8_t val){};
    virtual void setmotorSpeed(uint8_t val){};
    virtual void setVCU_Errors(uint8_t val){};
    virtual void setVehicle_Status(uint8_t val){};

protected:
    Model *model;
};

#endif // MODELLISTENER_HPP
