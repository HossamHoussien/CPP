#include "Agent.h"
#include "Room.h"


Agent::Agent()
{
    //ctor
}
/*****************************************************************/
bool Agent::act(string direction)
{
    return 0;
}
/*****************************************************************/
string Agent::getName()
{
    return name;
}
/*****************************************************************/
string Agent::getCurrentRoomName()
{
    return current_room->getName();
}
/*****************************************************************/
string Agent::toLower (string temp)
{
    int len = temp.length()+1;
    char arr[len];
    strncpy(arr, temp.c_str(), sizeof(arr));
    for (int i=0; i<len;i++){
        arr[i]= tolower(arr[i]);
    }
    string str (arr);
    return str ;

}
/*****************************************************************/
Room* Agent::getCurrentRoom()
{
    return current_room;
}
/*****************************************************************/
 void Agent::setCurrentRoom (Room* r)
 {
        this->current_room = r;
 }
/*****************************************************************/
void Agent::addObject(Props* obj)
{
    (this->objects).push_back(obj);
}
/*****************************************************************/
vector<Props*> Agent::getObjects()
{
    return (this->objects);
}
/********************************************************************/
bool Agent::isMonster()
{

}
/********************************************************************/
bool Agent::hasKey()
{
    bool key =false;
    vector <Props*> temp = this->getObjects();
    for (unsigned i=0; i<temp.size();i++)
    {
        if (temp.at(i)->getName() == "Key")
            key = true;
    }
    return key;
}
