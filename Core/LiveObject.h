#pragma once
#include "Object.h"
#include "..\ObjectLogic\LiveTypes.h" 
#include "..\ObjectLogic\ILiveObject.h"
template<typename Object>
class LiveObject :
    public Object, public Logic::ILiveObject
{
public:
    LiveObject(Object object, Logic::LiveTypes logicObject) ;
    Logic::LiveTypes GetLiveParameters() const override;
    void SetLiveParameters(Logic::LiveTypes newLiveParameters) override;
    //void BounceReaction(glm::vec3 collisionPoint) override;
private:
    Logic::LiveTypes objectLogic;

};

template<typename Object>
LiveObject<typename Object>::LiveObject(Object object, Logic::LiveTypes logicObject):Object(object), objectLogic(logicObject)
{

}

template<typename Object>
inline Logic::LiveTypes LiveObject<Object>::GetLiveParameters() const
{
    return objectLogic;
}

template<typename Object>
inline void LiveObject<Object>::SetLiveParameters(Logic::LiveTypes newLiveParameters)
{
    objectLogic = newLiveParameters;
}

//template<typename Object>
//inline void LiveObject<Object>::BounceReaction(glm::vec3 collisionPoint)
//{
//
//}
