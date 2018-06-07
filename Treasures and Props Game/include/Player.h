#ifndef PLAYER_H
#define PLAYER_H
#include<string>

#include "Room.h"
#include "Agent.h"

using namespace std;

class Player: public Agent
{
    public:
        Player();
        Player(string _name, Room *starting_room);
        virtual bool act(string direction);
        virtual bool isMonster();


};

#endif // PLAYER_H
