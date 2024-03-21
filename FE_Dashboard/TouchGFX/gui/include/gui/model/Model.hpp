#ifndef MODEL_HPP
#define MODEL_HPP

#include <stdint.h>

class ModelListener;
class Model
{
public:
    Model();

    //CAN data buffer for the current, received struct
    uint8_t dataBuffer[257];

    void bind(ModelListener *listener)
    {
        modelListener = listener;
    }

    void tick();
    
    //function to return the correct buffer struct to use on the GUI side
    //merged with qasim's version
    void* getDataBuffer(TeMessageID canMessageId);

    
protected:
    ModelListener *modelListener; //iniitalizes modelListener object. therefore can apply methods from ModelListner onto this object
};

#endif // MODEL_HPP
