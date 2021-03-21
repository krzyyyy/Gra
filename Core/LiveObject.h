#pragma once
#include "Object.h"
#include "..\ObjectLogic\LiveTypes.h" 
template<typename Model>
class LiveObject :
    public Object<Model>
{
public:
    LiveObject(Object<Model> object, Logic::LiveTypes logicObject);
    Logic::LiveTypes GetLiveParameters();
    void SetLiveParameters(Logic::LiveTypes newLiveParameters);
private:
    Logic::LiveTypes objectLogic;

};

template<typename Model>
LiveObject<typename Model>::LiveObject(Object<Model> object, Logic::LiveTypes logicObject):Object<Model>(object), objectLogic(logicObject)
{

}

template<typename Model>
inline Logic::LiveTypes LiveObject<Model>::GetLiveParameters()
{
    return objectLogic;
}

template<typename Model>
inline void LiveObject<Model>::SetLiveParameters(Logic::LiveTypes newLiveParameters)
{
    objectLogic = newLiveParameters;
}
