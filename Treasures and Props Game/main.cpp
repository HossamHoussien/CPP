#include <windows.h>
#include <MMSystem.h>
#include <iostream>
#include <cstring>
#include <random>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <map>
#include "Room.h"
#include "Agent.h"
#include "Monster.h"
#include "Player.h"


using namespace std;

/****************************************
*                                       *
*        FUNCTIONS PROTOTYPES           *
*                                       *
****************************************/
void walk ();
void LookAround (Room*);
void help();
void quit();
void whereToGo ();
void changePlayer(vector<string> , unsigned&);
int getIndex(vector<string> , string);
string toLower(string temp);
void Play();//TO PLAY BACKGROUND MUSIC
/****************************************
*                                       *
*        GLOBAL VARIABLES               *
*                                       *
****************************************/
Room* myPosition;
string currentPlayer;
Agent* curPlayer;
static unsigned counter =0;
vector <string> playerNames;
vector <Agent*> playerPosition;
/****************************************
*                                       *
*           MAIN FUNCTION               *
*                                       *
****************************************/
int main()
{
    srand(time(NULL));
    //USED TO RESET THE GAME
    PLAY_AGAIN:
    Play();
/********************************************************
*                                                       *
*                 CREATING Objects                      *
*                                                       *
*********************************************************/
    FixedObjects* obj1 = new FixedObjects("A giant Tree","This is really a BIG tree that cover both of road sides.");
    FixedObjects* obj2 = new FixedObjects("Wall","This wall blocks the road.");
    FixedObjects* obj3 = new FixedObjects("Well","This is well full of sweet water.");
    FixedObjects* obj4 = new FixedObjects("Lamppost ","A lamppost that enlighten this road");
    FixedObjects* obj5 = new FixedObjects("Car","This is a really old car, it's not working anymore.");
    FixedObjects* obj6 = new FixedObjects("The Car","This is the car you will use to get out of here!");

    Props* pro1 = new Props ("Ladder","You can use this ladder.");
    Props* pro2 = new Props ("Key","Secure this key with your life, you gonna need it to start the car!");
    Props* pro3 = new Props ("Rope","This is just a rope. I don't know if you will need it or not.");
    Props* pro4 = new Props ("Axe","This is really interesting, you may wanna keep it in your hands all the time.");
    Props* pro5 = new Props ("Flash Light","This would be really useful, especially in DARK roads.");
    Props* pro6 = new Props ("Shield","This shield save you from monsters' axes. You better pick it up entire game.");
/****************************************
*                                       *
*         INITIALIZE THE GAME           *
*                                       *
****************************************/
     Room* start   = new Room("Wide road","This is the place where you woke up and found yourself in.");
     Room* left1   = new Room("First left turn","This is the first left turn on the road.");
     Room* fork1   = new Room("First fork","This is the first fork on the road.");
     Room* right1  = new Room("First right turn","This is the first right turn on the road.");
     Room* fork2   = new Room("Second fork","This is the second fork on the road.");
     Room* left2   = new Room("Second left turn","This is the second left turn on the road.");
     Room* DeadEnd = new Room("Another road","UH! This is a dead end, nothing but wall.");
     Room* car     = new Room("A narrow road","\nFinally! Here's your Car,This is your way out, well done!");

    start->setWest(NULL);
    start->setSouth(NULL);
    start->link(fork1,"north");
    start->link(fork2,"east");

    start->addObject(obj3);
    start->addObject(obj4);
    start->addObject(pro5);
    start->addObject(pro6);
/****************************/
    fork1->setNorth(NULL);
    fork1->link(left1,"west");
    fork1->link(right1,"east");
    fork1->link(start,"south");

    fork1->addObject(obj4);
    fork1->addObject(pro4);
/****************************/
    left1->setEast(NULL);
    left1->setWest(NULL);
    left1->link(DeadEnd,"north");
    left1->link(fork1,"south");

    left1->addObject(obj4);
    left1->addObject(pro3);
/****************************/
    right1->setEast(NULL);
    right1->setWest(NULL);
    right1->link(fork2,"north");
    right1->link(fork1,"south");

    right1->addObject(obj4);
    right1->addObject(obj1);
    right1->addObject(pro4);
/****************************/
    fork2->setNorth(NULL);
    fork2->link(start,"east");
    fork2->link(left2,"west");
    fork2->link(right1,"south");

    fork2->addObject(obj4);
    fork2->addObject(obj1);
    fork2->addObject(obj5);
/****************************/
    left2->setEast(NULL);
    left2->setWest(NULL);
    left2->link(fork2,"south");
    left2->link(car,"north");

    left2->addObject(obj4);
    left2->addObject(pro3);
    left2->addObject(pro6);
/****************************/
    DeadEnd->setEast(NULL);
    DeadEnd->setWest(NULL);
    DeadEnd->setNorth(NULL);
    DeadEnd->link(left1,"south");

    DeadEnd->addObject(obj4);
    DeadEnd->addObject(obj2);
    DeadEnd->addObject(pro2);
    DeadEnd->addObject(pro1);
    DeadEnd->addObject(pro6);
/****************************/
    car->setEast(NULL);
    car->setNorth(NULL);
    car->setWest(NULL);
    car->link(left2,"south");
    car->addObject(obj6);
    car->addObject(obj4);
    car->addObject(pro6);


    myPosition = start;
/********************************************************
*                                                       *
*                 CREATING MONSTERS                     *
*                                                       *
*********************************************************/
    Monster* m1 = new Monster ("Grue",start,"A creepy monster that eat whatever it meets! Good luck.");
    Monster* m2 = new Monster ("Fard",left1,"You will wish never to meet him!");
    Monster* m3 = new Monster ("Duncan",DeadEnd,"A very smart monster that knows how to hunt its prey. Watch out!");
    Monster* m4 = new Monster ("Napoleon",car,"A French military and political leader, known for his love to blood.");
    Monster* m5 = new Monster ("Gulit",fork2,"That creature is the most nice creature you would meet.");
    Monster* m6 = new Monster ("Devil",fork2,"A very smart monster that knows how to hunt its prey. Watch out!");
    Monster* m7 = new Monster ("Spider",car,"A French military and political leader, known for his love to blood.");
    Monster* m8 = new Monster ("Batgod",right1,"That creature is the most nice creature you would meet.");

    //ALL MONSTERS HAVE AXES
    m1->addObject(pro4);
    m2->addObject(pro4);
    m3->addObject(pro4);
    m4->addObject(pro4);
    m5->addObject(pro4);

/********************************************************
*                                                       *
*                 CREATING PLAYERS                      *
*                                                       *
*********************************************************/
    int NoPlayers;
    string tempName;
    Player* tempPlayer;
    cout<<"Enter Number of Players: ";
    cin>>NoPlayers;
    cin.ignore();
    for (int i=0; i<NoPlayers;i++)
    {
        cout<<"\nEnter Player "<<i+1<<" Name: ";
        getline(cin,tempName);
        tempPlayer = new Player (tempName,start);
        start->enter(tempPlayer);
        playerNames.push_back(tempName);
        playerPosition.push_back(tempPlayer);

    }
    cout<<"\n* All Players starting at \"Start of the road\"\n"<<endl;
    Sleep(2000);

    cout <<"* Each player will make his/her move when his/her turn comes.\n"<<endl;
    Sleep(2000);

    cout <<"* Players take turns whenever they do their move!";
    Sleep(2000);

    system("cls");

/****************************************
*                                       *
*         INTERACTING WITH USER         *
*                                       *
****************************************/
    string where_to_go;

    cout <<"- You woke up and found yourself in a dark, muddy and frightening road.\n";
    Sleep(1000);
    cout<<"- There is a car out there in some place on the road. You have to find it and also find the key!\n";
    Sleep(1000);
    cout <<"- You have to choose where to go to find that car and survive.\n";
    Sleep(1000);
    cout<<"- It's all up to you now, tell me what to do: \n"<< endl;

   help();
/*********************************************************************************/
    while (true)
        {

        //MAKE MONSTERS MOVE "RANDOMLY" BETWEEN ROOMS
        m1->getCurrentRoom()->leave(m1);
        m1->act("");
        m1->getCurrentRoom()->enter(m1);

        m2->getCurrentRoom()->leave(m2);
        m2->act("");
        m2->getCurrentRoom()->enter(m2);

        m3->getCurrentRoom()->leave(m3);
        m3->act("");
        m3->getCurrentRoom()->enter(m3);

        m4->getCurrentRoom()->leave(m4);
        m4->act("");
        m4->getCurrentRoom()->enter(m4);

        m5->getCurrentRoom()->leave(m5);
        m5->act("");
        m5->getCurrentRoom()->enter(m5);

        m6->getCurrentRoom()->leave(m6);
        m6->act("");
        m6->getCurrentRoom()->enter(m6);

        m7->getCurrentRoom()->leave(m7);
        m7->act("");
        m7->getCurrentRoom()->enter(m7);

        m8->getCurrentRoom()->leave(m8);
        m8->act("");
        m8->getCurrentRoom()->enter(m8);


        /*********************************************************************************/
        currentPlayer = playerNames.at(counter);
        cout<<"\n***Current Player is: "<<currentPlayer<<"***\n"<<endl;
        getline(cin,where_to_go);

        if (toLower(where_to_go) == "look around" || toLower(where_to_go) == "lookaround"||toLower(where_to_go) == "show objects"
            ||toLower(where_to_go) == "show room objects"||toLower(where_to_go) == "show items"||toLower(where_to_go) == "show room items")
         {
             int index = getIndex(playerNames,currentPlayer);
             myPosition = playerPosition.at(index)->getCurrentRoom();
             LookAround(myPosition);
             cout<<"\nTo pick an object from the listed objects above just type the \"pick+object name\"."<<endl;

         }
         /*******************************************************************************/
        else if (toLower(where_to_go) == "help" )
         {help();}
         /*******************************************************************************/
        else if (toLower(where_to_go) == "pick a giant tree"||toLower(where_to_go) == "pick wall"||toLower(where_to_go) == "pick well"
            ||toLower(where_to_go) == "pick lamppost"||toLower(where_to_go) == "pick car")
        {
            cout<<"You can not pick this object!"<<endl;

        }
       else if (toLower(where_to_go) == "pick ladder")
       {
           int index = getIndex(playerNames,currentPlayer);
           curPlayer = (playerPosition.at(index));
           curPlayer->addObject(pro1);
       }
       else if (toLower(where_to_go) == "pick key")
       {
            int index = getIndex(playerNames,currentPlayer);
           curPlayer = (playerPosition.at(index));
           curPlayer->addObject(pro2);
           cout<<"\nThis is really important item. Keep it until you reach the car."<<endl;
       }
       else if (toLower(where_to_go)== "pick rope")
       {
            int index = getIndex(playerNames,currentPlayer);
           curPlayer = (playerPosition.at(index));
           curPlayer->addObject(pro3);
           cout<<"\nThis would be helpful in case you want to hang up yourself."<<endl;
       }
       else if (toLower(where_to_go) == "pick axe")
       {
            int index = getIndex(playerNames,currentPlayer);
           curPlayer = (playerPosition.at(index));
           curPlayer->addObject(pro4);
           cout<<"\nWill help you against monsters."<<endl;
       }
       else if (toLower(where_to_go) == "pick flash light")
       {
            int index = getIndex(playerNames,currentPlayer);
           curPlayer = (playerPosition.at(index));
           curPlayer->addObject(pro5);
           cout<<"\nIt will improve your sight of the road."<<endl;
       }
       else if (toLower(where_to_go) == "pick shield")
       {
            int index = getIndex(playerNames,currentPlayer);
           curPlayer = (playerPosition.at(index));
           curPlayer->addObject(pro6);
           cout<<"\nKeep this shield with you all the time, it protects you from monsters' axes."<<endl;
       }

         /*******************************************************************************/
        else if (toLower(where_to_go) == "where to go")
         {
                int index = getIndex(playerNames,currentPlayer);
                myPosition = playerPosition.at(index)->getCurrentRoom();
                cout<<"\n";
                myPosition->printLinked();

        }
         /*******************************************************************************/
        else if (toLower(where_to_go) == "walk")
         {walk();}
         /*******************************************************************************/
         else if (toLower(where_to_go) == "show my items" ||toLower(where_to_go) == "show my objects")
         {
             vector <Props*> vect;
            int index = getIndex(playerNames,currentPlayer);
            curPlayer = (playerPosition.at(index));
            vect = curPlayer->getObjects();
            for (unsigned i=0; i<vect.size();i++)
            {
                cout<<vect.at(i)->getName()<<": "<<vect.at(i)->getDescription()<<endl;
            }
         }

         /*******************************************************************************/
        else if (toLower(where_to_go) == "quit" ||toLower(where_to_go) =="terminate" ||toLower(where_to_go) =="end the game"||toLower(where_to_go) =="exit" )
         {quit();}
        /*******************************************************************************/
        else if (toLower(where_to_go) == "south" || toLower(where_to_go) == "down")
         {

             bool safe = false;
             int index = getIndex(playerNames,currentPlayer);
             curPlayer = (playerPosition.at(index));
             myPosition = (playerPosition.at(index)->getCurrentRoom())->getLinked("south");
             vector <Props*> vect = curPlayer->getObjects();
             if (myPosition == NULL)
             {cout<<"Nothing here! Try \"where to go\""<<endl;}
             else
             {
                 walk();

                //REMOVE THE PLAYER FROM THE THE PREVIOUS ROOM
                 (playerPosition.at(index)->getCurrentRoom())->leave(playerPosition.at(index));

                 //CHANGE PLAYER'S CURRENT ROOM
                 playerPosition.at(index)->act("south");

                //ADD PLAYER TO THE ROOM
                 (playerPosition.at(index)->getCurrentRoom())->enter(playerPosition.at(index));

                if ((curPlayer->getCurrentRoom()->getMonsters()).size() == 0)//NO MONSTERS IN THIS ROOM
                {
                    //SWITCH PLAYER
                    changePlayer(playerNames,counter);
                    cout<<"Room has no monsters. You are safe.\n"<<endl;
                }
                else //THERE IS ONE OR MORE MONSTER IN THIS ROOM
                {
                     for (unsigned i=0; i<vect.size();i++)
                    {
                        //CHECK WETHER THE PLAYER HAS THE SHIELD OR NOT
                        if (vect.at(i)->getName() == "Shield")
                        {
                            safe = true;
                            break;
                        }
                    }


                        if (safe)//THIS PLAYER HAS THE SHIELD
                        {
                            cout<<"You encountered a monster but don't worry you have a shield to protect you."<<endl;
                             //SWITCH PLAYER
                            changePlayer(playerNames,counter);

                        }
                        else //PLAYER STRAT FROM BEGGINING
                        {
                            //REMOVE THE PLAYER FROM THE THE PREVIOUS ROOM
                         (playerPosition.at(index)->getCurrentRoom())->leave(playerPosition.at(index));

                         //CHANGE PLAYER'S CURRENT ROOM
                         playerPosition.at(index)->setCurrentRoom(start);

                        //ADD PLAYER TO THE ROOM
                         (playerPosition.at(index)->getCurrentRoom())->enter(playerPosition.at(index));

                         //SWITCH PLAYER
                         changePlayer(playerNames,counter);
                         cout<<"You don't have a shield, and this road has a monster with axe. You start from beginning again."<<endl;
                        }


                }

            }
            if (curPlayer->hasKey()== true && curPlayer->getCurrentRoomName() == "A narrow road")
            {
                cout<<"Player: "<<curPlayer->getName()<<" got his car and won the game.\n"<<endl;
                cout<<"\n\n Press \"Play again: To start another game.\""<<endl;
                cout<<"Press \"Exit: To terminate the game.\""<<endl;
            }
         }
         /*******************************************************************************/
        else if (toLower(where_to_go) == "east" || toLower(where_to_go) == "right")
        {
              bool safe = false;
             int index = getIndex(playerNames,currentPlayer);
             curPlayer = (playerPosition.at(index));
             myPosition = (playerPosition.at(index)->getCurrentRoom())->getLinked("east");
             vector <Props*> vect = curPlayer->getObjects();
             if (myPosition == NULL)
             {cout<<"Nothing here! Try \"where to go\""<<endl;}
             else
             {
                 walk();

                //REMOVE THE PLAYER FROM THE THE PREVIOUS ROOM
                 (playerPosition.at(index)->getCurrentRoom())->leave(playerPosition.at(index));

                 //CHANGE PLAYER'S CURRENT ROOM
                 playerPosition.at(index)->act("east");

                //ADD PLAYER TO THE ROOM
                 (playerPosition.at(index)->getCurrentRoom())->enter(playerPosition.at(index));

                if ((curPlayer->getCurrentRoom()->getMonsters()).size() == 0)//NO MONSTERS IN THIS ROOM
                {
                    //SWITCH PLAYER
                    changePlayer(playerNames,counter);
                    cout<<"Room has no monsters. You are safe.\n"<<endl;
                }
                else //THERE IS ONE OR MORE MONSTER IN THIS ROOM
                {
                     for (unsigned i=0; i<vect.size();i++)
                    {
                        //CHECK WETHER THE PLAYER HAS THE SHIELD OR NOT
                        if (vect.at(i)->getName() == "Shield")
                        {
                            safe = true;
                            break;
                        }
                    }


                        if (safe)//THIS PLAYER HAS THE SHIELD
                        {
                            cout<<"You encountered a monster but don't worry you have a shield to protect you."<<endl;
                            //SWITCH PLAYER
                            changePlayer(playerNames,counter);

                        }
                        else //PLAYER STRAT FROM BEGGINING
                        {
                            //REMOVE THE PLAYER FROM THE THE PREVIOUS ROOM
                         (playerPosition.at(index)->getCurrentRoom())->leave(playerPosition.at(index));

                         //CHANGE PLAYER'S CURRENT ROOM
                         playerPosition.at(index)->setCurrentRoom(start);

                        //ADD PLAYER TO THE ROOM
                         (playerPosition.at(index)->getCurrentRoom())->enter(playerPosition.at(index));

                         //SWITCH PLAYER
                         changePlayer(playerNames,counter);
                         cout<<"You don't have a shield, and this road has a monster with axe. You start from beginning again."<<endl;
                        }


                }

            }
            if (curPlayer->hasKey()== true && curPlayer->getCurrentRoomName() == "A narrow road")
            {
                cout<<"Player: "<<curPlayer->getName()<<" got his car and won the game.\n"<<endl;
                cout<<"\n\n Press \"Play again: To start another game.\""<<endl;
                cout<<"Press \"Exit: To terminate the game.\""<<endl;
            }

        }
        /*******************************************************************************/
        else if (toLower(where_to_go) == "west"|| toLower(where_to_go) == "left")
         {
            bool safe = false;
             int index = getIndex(playerNames,currentPlayer);
             curPlayer = (playerPosition.at(index));
             myPosition = (playerPosition.at(index)->getCurrentRoom())->getLinked("west");
             vector <Props*> vect = curPlayer->getObjects();
             if (myPosition == NULL)
             {cout<<"Nothing here! Try \"where to go\""<<endl;}
             else
             {
                 walk();

                //REMOVE THE PLAYER FROM THE THE PREVIOUS ROOM
                 (playerPosition.at(index)->getCurrentRoom())->leave(playerPosition.at(index));

                 //CHANGE PLAYER'S CURRENT ROOM
                 playerPosition.at(index)->act("west");

                //ADD PLAYER TO THE ROOM
                 (playerPosition.at(index)->getCurrentRoom())->enter(playerPosition.at(index));

                if ((curPlayer->getCurrentRoom()->getMonsters()).size() == 0)//NO MONSTERS IN THIS ROOM
                {
                    //SWITCH PLAYER
                    changePlayer(playerNames,counter);
                    cout<<"Room has no monsters. You are safe.\n"<<endl;
                }
                else //THERE IS ONE OR MORE MONSTER IN THIS ROOM
                {
                     for (unsigned i=0; i<vect.size();i++)
                    {
                        //CHECK WETHER THE PLAYER HAS THE SHIELD OR NOT
                        if (vect.at(i)->getName() == "Shield")
                        {
                            safe = true;

                            break;
                        }
                    }

                        if (safe)//THIS PLAYER HAS THE SHIELD
                        {
                            cout<<"You encountered a monster but don't worry you have a shield to protect you."<<endl;
                            //SWITCH PLAYER
                            changePlayer(playerNames,counter);

                        }
                        else //PLAYER STRAT FROM BEGGINING
                        {
                            //REMOVE THE PLAYER FROM THE THE PREVIOUS ROOM
                         (playerPosition.at(index)->getCurrentRoom())->leave(playerPosition.at(index));

                         //CHANGE PLAYER'S CURRENT ROOM
                         playerPosition.at(index)->setCurrentRoom(start);

                        //ADD PLAYER TO THE ROOM
                         (playerPosition.at(index)->getCurrentRoom())->enter(playerPosition.at(index));

                         //SWITCH PLAYER
                         changePlayer(playerNames,counter);
                         cout<<"You don't have a shield, and this road has a monster with axe. You start from beginning again."<<endl;
                        }


                }

            }
            if (curPlayer->hasKey()== true && curPlayer->getCurrentRoomName() == "A narrow road")
            {
                cout<<"Player: "<<curPlayer->getName()<<" got his car and won the game.\n"<<endl;
                cout<<"\n\n Press \"Play again: To start another game.\""<<endl;
                cout<<"Press \"Exit: To terminate the game.\""<<endl;
            }
         }
         /*******************************************************************************/
         else if (toLower(where_to_go) == "north"|| toLower(where_to_go) == "up")
         {
            bool safe = false;
             int index = getIndex(playerNames,currentPlayer);
             curPlayer = (playerPosition.at(index));
             myPosition = (playerPosition.at(index)->getCurrentRoom())->getLinked("north");
             vector <Props*> vect = curPlayer->getObjects();
             if (myPosition == NULL)
             {cout<<"Nothing here! Try \"where to go\""<<endl;}
             else
             {
                 walk();

                //REMOVE THE PLAYER FROM THE THE PREVIOUS ROOM
                 (playerPosition.at(index)->getCurrentRoom())->leave(playerPosition.at(index));

                 //CHANGE PLAYER'S CURRENT ROOM
                 playerPosition.at(index)->act("north");

                //ADD PLAYER TO THE ROOM
                 (playerPosition.at(index)->getCurrentRoom())->enter(playerPosition.at(index));

                if ((curPlayer->getCurrentRoom()->getMonsters()).size() == 0)//NO MONSTERS IN THIS ROOM
                {
                    //SWITCH PLAYER
                    changePlayer(playerNames,counter);
                    cout<<"Room has no monsters. You are safe.\n"<<endl;
                }
                else //THERE IS ONE OR MORE MONSTER IN THIS ROOM
                {
                     for (unsigned i=0; i<vect.size();i++)
                    {
                        //CHECK WETHER THE PLAYER HAS THE SHIELD OR NOT
                        if (vect.at(i)->getName() == "Shield")
                        {
                            safe = true;

                            break;
                        }
                    }

                        if (safe)//THIS PLAYER HAS THE SHIELD
                        {
                            cout<<"You encountered a monster but don't worry you have a shield to protect you."<<endl;
                            //SWITCH PLAYER
                            changePlayer(playerNames,counter);

                        }
                        else //PLAYER STRAT FROM BEGGINING
                        {
                            //REMOVE THE PLAYER FROM THE THE PREVIOUS ROOM
                         (playerPosition.at(index)->getCurrentRoom())->leave(playerPosition.at(index));

                         //CHANGE PLAYER'S CURRENT ROOM
                         playerPosition.at(index)->setCurrentRoom(start);

                        //ADD PLAYER TO THE ROOM
                         (playerPosition.at(index)->getCurrentRoom())->enter(playerPosition.at(index));

                         //SWITCH PLAYER
                         changePlayer(playerNames,counter);
                         cout<<"You don't have a shield, and this road has a monster with axe. You start from beginning again."<<endl;
                        }


                }

            }
            if (curPlayer->hasKey()== true && curPlayer->getCurrentRoomName() == "A narrow road")
            {

                cout<<"Player: "<<curPlayer->getName()<<" got his car and won the game.\n"<<endl;
                cout<<"\n\n Press \"Play again: To start another game.\""<<endl;
                cout<<"Press \"Exit: To terminate the game.\""<<endl;

            }
         }
         /*******************************************************************************/
         else if (toLower(where_to_go) == 
