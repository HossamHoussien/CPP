#include "Props.h"


Props::Props()
{
    //ctor
}
/**********************************************/
Props::Props(string name, string desc)
{
    this->ObjName = name;
    this->ObjDescription = desc;
}
/*********************************************/
bool Props::act ()
{
    return 1;

}
