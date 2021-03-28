#pragma once
#include "Object.h"
#include "..\ObjectLogic\LiveTypes.h" 
#include "..\ObjectLogic\ILiveObject.h"
template<typename Model>
class LiveObject :
    public Object<Model>, public Logic::ILiveObject
{
public:
    LiveObject(Object<Model> object, Logic::LiveTypes logicObject) ;
    Logic::LiveTypes GetLiveParameters() const override;
    void SetLiveParameters(Logic::LiveTypes newLiveParameters) override;
private:
    Logic::LiveTypes objectLogic;

};

template<typename Model>
LiveObject<typename Model>::LiveObject(Object<Model> object, Logic::LiveTypes logicObject):Object<Model>(object), objectLogic(logicObject)
{

}

template<typename Model>
inline Logic::LiveTypes LiveObject<Model>::GetLiveParameters() const
{
    return objectLogic;
}

template<typename Model>
inline void LiveObject<Model>::SetLiveParameters(Logic::LiveTypes newLiveParameters)
{
    objectLogic = newLiveParameters;
}
