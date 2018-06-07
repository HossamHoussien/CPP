#ifndef PROPS_H
#define PROPS_H
#include "Object.h"
#include "Room.h"
#include <vector>
class Props:public Object
{

    public:
        Props();
        Props(string , string );
        virtual bool act();




};

#endif // PROPS_H
