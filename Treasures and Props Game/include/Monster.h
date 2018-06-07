#ifndef MONSTER_H
#define MONSTER_H
#include "agent.h"
#include "room.h"
#include <random>
using namespace std;

class Monster: public Agent
{
    private:
        string description;
    public:
        Monster();
        Monster(string _name, Room *starting_room,string desc);
        virtual bool act(string direction);
        virtual string getName();
        virtual bool isMonster();

};

#endif // MONSTER_H
