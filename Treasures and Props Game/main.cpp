/*********************************
*   20140098 Hossam Houssien
*   20140083 Anwar Abd El-mksoud
**********************************/
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
         else if (toLower(where_to_go) == "where am i" || toLower(where_to_go) == "where am i?" || toLower(where_to_go) == "where am i ?")
         {
             int index = getIndex(playerNames,currentPlayer);
             if (toLower((playerPosition.at(index)->getCurrentRoom())->getName()) == "a narrow road")
             {
                 car->setName("This is where you found the car!");
                 cout<<car->getName()<<endl;
             }
             else
                {

                    cout<<playerPosition.at(index)->getCurrentRoomName()<<endl;
                }

         }
         /*******************************************************************************/
         else if (toLower(where_to_go) == "reset" || toLower(where_to_go) == "play again")
         {
             system("cls");

             goto PLAY_AGAIN;
         }
         /*******************************************************************************/
         else if (toLower(where_to_go) == "who is here" || toLower(where_to_go) == "who is here?" ||
                  toLower(where_to_go) == "who is here ?" ||toLower(where_to_go) == "show players"||
                  toLower(where_to_go) == "print occupants"||toLower(where_to_go) == "show occupants")
         {
             int index = getIndex(playerNames,currentPlayer);
             (playerPosition.at(index)->getCurrentRoom())->printOccupants();

         }
         /*******************************************************************************/
         else
         {
             unsigned seed = time (0);
             srand(seed);
             int n = 1+ rand ()% 4;
             switch (n)
             {
            case 1:
                cout<<"Sorry! I can't understand what you want."<<endl;
                break;
            case 2:
                cout<<"Obviously, we don't speak the same language."<<endl;
                break;
            case 3:
                cout<<"Don't type a poem! Instead try something like \"Look around-Help-Quit\""<<endl;
                break;
            case 4:
                cout<<"Try again with better commands."<<endl;
                break;

             }
         }


}
    return 0;
    system("PAUSE");
}

/****************************************
*                                       *
*        FUNCTIONS DEFINITIONS          *
*                                       *
****************************************/
/** METHOD THAT TAKES A STRING AND CONVERT IT TO LOWER CASE **/
string toLower (string temp)
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
/*******************************************************************************************/
void walk ()
{
    cout<<"\nYou're now walking on your path."<<endl;
    Sleep(1000);
    cout<<"you have walked 100 M till now"<<endl;
    Sleep(1000);
    cout<<"you have walked 200 M till now"<<endl;
    Sleep(1000);
    cout<<"you have walked 300 M till now\n"<<endl;
    Sleep(500);


}
/*******************************************************************************************/
void LookAround (Room* current)
{
    //GENERATE A RANDOM NUMBER BETWEEN 1-5
    unsigned seed = time (0);
    srand(seed);
    int num = 1 + rand()% 5;
    switch (num)
    {
    case 1:
        cout<<"This road is so foggy, I can't see anything.\n"<<endl;
        break;
    case 2:
        cout<<"I don't know how to tell you that, but you're surrounded by wolves. RUN! \n"<<endl;
        break;
    case 3:
        cout<<"This is really a nice road, you can even call your friends to come over. Sorry I forgot that you can't call anyone.\n"<<endl;
        break;
    case 4:
        cout<<"This road is normal, nothing here but trees and SNAKES!\n"<<endl;
        break;
    case 5:
        cout<<"You're lucky enough to be here, I found you a well with sweet water. Drink well, you may not have the chance again!\n"<<endl;
        break;

    }
    vector <Object*> v;
    v = current->getObjects();
    for (unsigned i=0; i<v.size();i++)
    {
        cout<<(v.at(i))->getName()<<": "<<(v.at(i))->getDescription()<<endl;
    }
}
/*******************************************************************************************/
void help()
{
    cout<<"\n\n"<<endl;
    cout<<"These commands helps you out to play the game:\n"<<endl;
    cout<<"1) Where to go:        Guide you through the roads, it tells you about your possible moves. "<<endl;
    cout<<"2) Look around:        Displays the road objects. Try to use it whenever you enter a new road."<<endl;
    cout<<"3) Show my items:      List all the objects you currently have."<<endl;
    cout<<"4) Who is here:        List all players and/or monsters that exist in this road."<<endl;
    cout<<"5) Where am I:         Tells your current location."<<endl;
    cout<<"6) Walk:               Just make the player walk in this road. [Unless you wanna win, you can use it.]"<<endl;
    cout<<"7) Pick:               Use this command to pick up objects. [HINT: Hit \"Pick item name\"]"<<endl;
    cout<<"8) Drop:               Use this command to drop an item from your list.[HINT: Not preferred]"<<endl;
    cout<<"9) Help:               Use this command to display this list of commands again."<<endl;
    cout<<"10) Reset/Play again:  Restart the game."<<endl;
    cout<<"11) Exit:              Use it to terminate the game."<<endl;
    cout<<"\n\n"<<endl;
}
/*******************************************************************************************/
void quit()
{
    cout<<"I knew it, you can't even handle a maze like that.\nBe careful! I'm watching you.\n"<<endl;
    Sleep(1500);
    exit (EXIT_SUCCESS);
}
/*******************************************************************************************/
void whereToGo()
{
    if (toLower((*myPosition).getName()) == "a narrow road")
    {
        cout<<"\nYou already obtained the car you can either type \"quit-terminate-exit\" to end the game\n or typing \"reset-play again\" to play again."<<endl;
    }
    else{
        (*myPosition).printLinked();
    }
}
/*******************************************************************************************/
void Play ()
{
    PlaySound (TEXT("sound.wav"),NULL,SND_LOOP|SND_ASYNC);
}
/*******************************************************************************************/
void changePlayer(vector<string> names,unsigned& counter)
{
    if (counter == playerNames.size()-1)
         {
             //RESET THE COUNTER GO GO BACK TO FIRST PLAYER
             counter = 0;
         }
         else
        {
            counter++;
        }
}
/*******************************************************************************************/
int getIndex(vector<string> names, string current)
{
    int index=-1;
    for (unsigned i=0; i<names.size();i++)
    {
        if (toLower(names.at(i)) == toLower(current))
        {
            index = i;
            break;
        }

    }
    return index;
}
/*********************************************************************************************/



