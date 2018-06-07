#include "Room.h"
#include "Agent.h"
#include "Room.h"


//DEFAULT CONSTRUCTOR
Room::Room()
{

}
/***************************************************/
std::string Room::toLower (std::string temp)
{
    int len = temp.length()+1;
    char arr[len];
    strncpy(arr, temp.c_str(), sizeof(arr));
    for (int i=0; i<len;i++){
        arr[i]= tolower(arr[i]);
    }
    std::string str (arr);
    return str ;

}
/*************************************************/
 Room::Room(std::string name, std::string desc)
 {
     this-> name = name;
     this-> description = desc;
 }
 /*************************************************/
std::string Room::getName()
{
    return this->name;
}
/*************************************************/
std::string Room::getDescription()
{
    return description;
}
/*************************************************/
void Room::link(Room *r, std::string direction)
{
    if (direction == "south")
    {south = r;}
    else if (direction == "west")
    {west = r;}
    else if (direction == "east")
    {east = r;}
    else if (direction == "north")
    {north = r;}
}
/*************************************************/
Room* Room::getLinked(const std::string& direction)
{
    if (toLower(direction) == "south")
        {return south;}

    else if (toLower(direction)  == "west")
        {return west;}

    else if (toLower(direction)  == "east")
        {return east;}

    else if (toLower(direction)  == "north")
        {return north;}
    else
    {return NULL;}
}
/*************************************************/
void Room::setName (std::string n)
{
    name = n;
}
/*************************************************/
void Room::printLinked(){
    if (north != NULL)
    {std::cout<<"You can go to north ("<<(*north).getName()<<")"<<std::endl;}

    if (east != NULL)
    {std::cout<<"You can go to east ("<<(*east).getName()<<")"<<std::endl;}

    if (west != NULL)
    {std::cout<<"You can go to west ("<<(*west).getName()<<")"<<std::endl;}

    if (south != NULL)
    {std::cout<<"You can go to south ("<<(*south).getName()<<")"<<std::endl;}
}

/*************************************************/
void Room::setWest (Room *r)
{
    west = r;
}
/*************************************************/
void Room::setEast (Room *r)
{
    east = r;
}
/*************************************************/
void Room::setNorth (Room *r)
{
    north = r;
}
/*************************************************/
void Room::setSouth (Room *r)
{
    south = r;
}
/*************************************************/
void Room::enter(Agent *a)
{
    occupants.push_back(a);
}
/*************************************************/
void Room::leave(Agent *a)
{
    //search for the agent pointer a and remove it but don’t forget to shift the array appropriately
    for (unsigned i=0; i<occupants.size();i++)
    {
        if (occupants.at(i) == a)
        {
            //IT DOES SHIFTING AUTOMATICALLY
            //erase(iterator var) cannot remove an element using an int index
            occupants.erase(occupants.begin() + i);
        }
    }
}
/*************************************************/
void Room::printOccupants()
{
    cout << "Players in this room: " << endl;
    for(unsigned i=0; i<occupants.size(); i++)
    {
        cout <<"\t>> "<<occupants[i]->getName() << endl;
    }

}
/*************************************************/
vector <Object*> Room::getObjects()
{
    return (this->objects);
}
/*************************************************/
void Room::addObject(Object* obj)
{
    (this->objects).push_back(obj);
}
/*************************************************/
vector <Agent*>Room::getMonsters()
{
    vector <Agent*> mons;
    for (unsigned i=0; i<occupants.size();i++)
    {
        if (occupants.at(i)->isMonster()){
            mons.push_back(occupants.at(i));
        }

    }
    return mons;
}
/*************************************************/
Room::~Room()
{
    //dtor
}
