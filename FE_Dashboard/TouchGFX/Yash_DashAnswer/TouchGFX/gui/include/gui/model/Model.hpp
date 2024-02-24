#ifndef MODEL_HPP
#define MODEL_HPP

class ModelListener;
#include <stdint.h>
class Model
{
public:
    Model();

    uint8_t dataBuffer[257];

    void bind(ModelListener *listener)
    {
        modelListener = listener;
    }

    void tick();

protected:
    ModelListener *modelListener;
};

#endif // MODEL_HPP
