#ifndef AGENT_H
#define AGENT_H
#include <Room.h>
#include "Props.h"
#include<string>
using namespace std;

class Agent
{
    protected:
      Room *current_room;
      string name;
      vector <Props*> objects;

   public:
      Agent();
      virtual bool act(string) ;
      virtual string getName();
      string getCurrentRoomName();
      string toLower(string temp);
      Room* getCurrentRoom();
      void addObject(Props*);
      vector<Props*> getObjects();
      virtual bool isMonster();
      void setCurrentRoom (Room*);
      bool hasKey();



};

#endif // AGENT_H
