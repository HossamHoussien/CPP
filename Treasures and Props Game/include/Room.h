#ifndef ROOM_H
#define ROOM_H
#include <string>
#include <iostream>
#include <cstring>
#include <vector>
#include <FixedObjects.h>
using namespace std;

class Agent;
class Monster;
class Room
{
    private:

        std::string name;
        std::string description;
        Room* south;
        Room* north;
        Room* east;
        Room* west;
        vector <Agent*> occupants;
        vector <Object*> objects;


    public:

        //CONSTRUCTOR
        Room();
        Room(std::string name, std::string desc);

        //METHODS

        void setName (std::string );
        void setWest(Room *r);
        void setEast(Room *r);
        void setSouth(Room *r);
        void setNorth(Room *r);

        std::string getName();
        std::string getDescription();

        void link(Room *r, std::string direction);
        Room *getLinked(const std::string& direction);
        void printLinked();
        std::string toLower(std::string temp);
        vector <Object*> getObjects();
        void addObject(Object*);
        vector <Agent*>getMonsters();

        void enter(Agent *a);
        void leave(Agent *a);
        void printOccupants();

        ~Room();





};

#endif // ROOM_H
