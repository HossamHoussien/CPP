#ifndef OBJECT_H
#define OBJECT_H
#include <string>
using namespace std;

class Object
{

    protected:
    string ObjName;
    string ObjDescription;

    public:
        Object();
        virtual bool act();
        string getName();
        string getDescription();



};

#endif // OBJECT_H
