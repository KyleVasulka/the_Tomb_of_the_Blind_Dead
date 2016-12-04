/*
   COPYRIGHT (C) 20YY Student Name (UANET ID) All rights reserved.
   CSI project 2 and 3 - Blind Dead
   Author.  Kyle Vasulka
   Version. 1.01 MM.DD.20YY.
   Purpose: The maze action packed blind dead skeleton video game!
*/
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include<cctype>
using std::cout;
using std::cin;
using std::endl;
using std::fstream;

//gameArray indicies
//gameArray[0] = players current room
const int CURRENT_ROOM_INDEX = 0;
//gameArray[1] = current room of zombie
const int ZOMBIE_ROOM_INDEX = 1;
//gameArray[2]
const int NUM_BULLETS_INDEX = 2;
//gameArray[3]
const int NUM_ROOMS_INDEX = 3;
//boolean whether player has grail or not
const int HAVE_GRAIL_INDEX = 4;

//roomArray indices
//roomArray[gameArray[CURRENT_ROOM_INDEX]][4] = 1 or 0 if the player is
//	or is not in the current room
const int PLAYER_INDEX = 4;
//roomArray[gameArray[ZOMBIE_ROOM_INDEX]][5] = 1, tracks where the zombie is
const int ZOMBIE_INDEX = 5;
//roomArray[room][6] = the room that the grail is in should be marked 1, all others 0
const int GRAIL_INDEX = 6;
// the number of rooms and number of bullets to fend off the zombies
const int MAX_ROOMS = 11;
const int MAX_BULLETS = 6;

//PART 1A prototypes
//reset simply resets the primary game variables
void reset(int &currentRoom, int &zombieRoom, int &numBullets, int &numRooms, bool &haveGrail);
//print game instructions
void instructions();
//print layout of game memory
void printMemory(int roomArray[][7]);
// the menu (which calls functions printMemory and instructions)
bool menu(int &selection);

//PART 1B prototypes
//read in the input file for the map
void readMaze(int roomArray[][7], int gameArray[5]);
//return a random room
int getRandomRoom(int gameArray[5]);
//place the zombie
void placeZombie(int roomArray[][7], int gameArray[5]);
//place the grail
void placeGrail(int roomArray[][7], int gameArray[5]);
// the setup function
void setup(int &currentRoom, int &numBullets, bool &haveGrail);

//PART 2 prototypes

//PART 3 prototypes

int main()
{
	// these variables are passed throughout this program
	int roomArray[MAX_ROOMS][7],
	    gameArray[5],
	    currentRoom = 0,
       zombieRoom = 0,
       numBullets = 0,
       numRooms = 0;
       menuSelection = 0;
   bool haveGrail = false;

   reset();
   menu();


	return 0;
}
// build your functions here. Don't forget your pre and post conditions





//reset simply resets the primary game variables
void reset(int &currentRoom, int &zombieRoom, int &numBullets, int &numRooms, bool &haveGrail)
{
    currentRoom = 0;
    zombieRoom = 0;
    numBullets = 0;
    numRooms = 0;
    haveGrail = 0;
    return;
}

// the menu (which calls functions printMemory and instructions)
bool menu(int &selection)
{

      //display menu to user
    cout << "\t Enter, if you dare..." << endl;
    cout << "*** THE TOMB OF THE BLIND DEAD ***" << endl;
    cout << "\t Main Menu" << endl;
    cout << "1. Instructions" << endl;
    cout << "2. Begin" << endl;
    cout << "3. Exit" << endl << endl;

    do
    {

        //input
        cout << "Enter Menu Selection: ";
        cin >> selection;

        //input validation
        if(cin.fail() || selection > 3 || selection < 1)
        {
            cout << "You MUST choose an option between 1 and 3." << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else
        {
            loopFlag = false;
        }
    } while(loopFlag);



   //when user selects instructions from the main menu
   //display text enclosed in the blue box in the sample image
    instructions();

    //when user selects begin
    printMemory();


    //if exit is called end the program


}


//print game instructions
void instructions()
{

}

//print layout of game memory
void printMemory(int roomArray[][7])
{
    //display all parameters including MAX_ROOMS entries of roomArray and display their contents to the screen.


}

