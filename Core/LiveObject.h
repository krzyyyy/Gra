#pragma once
#include "Object.h"
#include "..\ObjectLogic\ObjectLogic.h" 
template<typename Model>
class LiveObject :
    public Object<Model>, public Logic::ObjectLogic
{
public:
    LiveObject(Object<Model> object, Logic::ObjectLogic logicObject);

};

template<typename Model>
LiveObject<typename Model>::LiveObject(Object<Model> object, Logic::ObjectLogic logicObject):Object<Model>(object), Logic::ObjectLogic(logicObject)
{

}