#ifndef MODEL_HPP
#define MODEL_HPP

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
    void* getDataBuffer(TeMessageID canMessageId);
    void* getScreenUnmarshaller(TeMessageID canMessageId);
    
protected:
    ModelListener *modelListener; //iniitalizes modelListener object
};

#endif // MODEL_HPP
