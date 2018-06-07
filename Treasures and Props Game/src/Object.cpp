#include "Object.h"

Object::Object()
{
    //ctor
}

bool Object::act()
{
    return true;
}
string Object::getName()
{
    return this->ObjName;
}
string Object::getDescription()
{
    return this->ObjDescription;
}
