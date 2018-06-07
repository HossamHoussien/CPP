#include "Monster.h"

Monster::Monster()
{
    //ctor
}
/********************************************************************/
Monster::Monster(string _name, Room *starting_room,string desc)
{
    name = _name;
    current_room = starting_room;
    description = desc;
}
/********************************************************************/
bool Monster::act(string direction)
{
    int n = rand() % 4;
    string Direction;

        switch(n)
        {
            case 0: Direction = "north"; break;
            case 1: Direction = "south"; break;
            case 2: Direction = "west"; break;
            case 3: Direction = "east"; break;
        }
        if(current_room->getLinked(Direction) != NULL)
        {
            current_room = current_room->getLinked(Direction);
            return true;
        }
        else{return false;}

}
/*******************************************************************/
string Monster::getName()
 {
     return (name+": "+description);
 }
 /*****************************************************************/
 bool Monster::isMonster()
{
    return true;
}
