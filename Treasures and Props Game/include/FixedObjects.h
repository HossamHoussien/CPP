#ifndef FIXEDOBJECTS_H
#define FIXEDOBJECTS_H
#include <Object.h>

class FixedObjects: public Object
{
    public:
        FixedObjects();
        FixedObjects(string, string);
        virtual bool act();


};

#endif // FIXEDOBJECTS_H
