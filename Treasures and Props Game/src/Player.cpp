#include "Player.h"

Player::Player()
{
    //ctor
}
/*****************************************************************/
Player::Player(string _name, Room *starting_room)
{
    name = _name;
    current_room = starting_room;
}
/*****************************************************************/
bool Player::act(string direction)
{

     if(current_room->getLinked(direction) != NULL )
    {
        current_room = current_room->getLinked(direction);
        return true;
    }
    else if (current_room->toLower(direction) == "exit" ||current_room->toLower(direction) == "quit" ||current_room->toLower(direction) == "terminate" )
    {
        //Indicator to exit the game
        return false;
    }
    else
    {
        //handled in the main.cpp
        return true;
    }

}
/***********************************************************************/
bool Player::isMonster()
{
    return false;
}
/***********************************************************************/

