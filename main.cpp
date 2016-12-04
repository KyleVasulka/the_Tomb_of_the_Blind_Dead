/*
   COPYRIGHT (C) 20YY Student Name (UANET ID) All rights reserved.
   CSI project 2 and 3 - Blind Dead
   Author.  Kyle Vasulka
   Version. 1.01 MM.DD.20YY.
   Purpose: The maze action packed blind dead skeleton video game!
*/
#include<iostream>
#include<iomanip>
#include<limits>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include<cctype>
#include<string>
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
void reset(int &currentRoom, int &zombieRoom, int &numBullets, int &numRooms, bool &haveGrail, int gameArray[], int roomArray[][7]);
//print game instructions
void instructions();
//print layout of game memory
void printMemory(int gameArray[],int roomArray[][7]);
// the menu (which calls functions printMemory and instructions)
bool menu(int &currentRoom, int &zombieRoom, int &numBullets, int &numRooms, bool &haveGrail, int gameArray[],int roomArray[][7], int Selection);

//PART 1B prototypes
//read in the input file for the map
void readMaze(int roomArray[][7], int gameArray[5],int & numRooms);
//return a random room
int getRandomRoom(int gameArray[5],int numRooms);
//place the zombie
void placeZombie(int roomArray[][7], int gameArray[5], int numRooms);
//place the grail
void placeGrail(int roomArray[][7], int gameArray[5], int numRooms);
// the setup function
void setup(int &currentRoom, int &zombieRoom, int &numBullets, int &numRooms, bool &haveGrail, int roomArray[][7], int gameArray[5]);

//PART 2 prototypes
//returns true if zombie is present
bool checkZombie (int x, int roomArray[][7]);
//returns true if grail is present
bool checkGrail (int x, int roomArray[][7]);
//return true if Zombie in connected room
bool checkNearZombie(int numRooms, int roomArray[][7]);
//returns true if Grail in connected room
bool checkNearGrail(int x, int roomArray[][7]);
//displays the winner result
void winOrLose(bool win, int gameArray[]);
//displays connected rooms number
void showConnectedRooms(int &currentRoom, int roomArray[][7]);
//returns true if room is connected to current room
bool isConnected(int targetRoom, int gameArray[], int roomArray[][7]);


//PART 3 prototypes
//handels movement of character
void moveRoom(int roomWanted, int gameArray[], int roomArray[][7]);
//shoots a room that is next to you to maybe kill a zombie
void shootRoom(int roomToShoot,int gameArray[],int roomArray[][7]);
void moveZombie(int gameArray[], int roomArray[][7]);
bool validateSelection(std::string validate);

int main()
{

	// these variables are passed throughout this program
	int roomArray[MAX_ROOMS][7],
	    gameArray[5],
	    currentRoom = 0,
       zombieRoom = 0,
       numBullets = 0,
       numRooms = 0,
       menuSelection = 0;
   bool haveGrail = false;





   reset(currentRoom, zombieRoom, numBullets, numRooms, haveGrail, gameArray, roomArray);

   menu(currentRoom, zombieRoom, numBullets, numRooms, haveGrail, gameArray, roomArray, menuSelection);


	return 0;
}
// build your functions here. Don't forget your pre and post conditions





//reset simply resets the primary game variables
void reset(int &currentRoom, int &zombieRoom, int &numBullets, int &numRooms, bool &haveGrail, int gameArray[], int roomArray[][7])
{
    currentRoom = 0;
    zombieRoom = 0;
    numBullets = 0;
    numRooms = 0;
    haveGrail = 0;

     //set room Array to zero
   for(int i = 0; i < MAX_ROOMS; i++)
   {
       for (int j = 0; j < 7; j++)
       {
           roomArray[i][j] = 0;
       }
   }

   //set game Array to zero
   for(int i = 0; i < 5; i++)
    gameArray[i] = 0;

    return;
}

// the menu (which calls functions printMemory and instructions)
bool menu(int &currentRoom, int &zombieRoom, int &numBullets, int &numRooms, bool &haveGrail, int gameArray[],int roomArray[][7], int selection)
{

    while(1)
    {
        //display menu to user
        cout << "\t Enter, if you dare..." << endl;
        cout << "*** THE TOMB OF THE BLIND DEAD ***" << endl;
        cout << "\t Main Menu" << endl;
        cout << "1. Instructions" << endl;
        cout << "2. Begin" << endl;
        cout << "3. Exit" << endl << endl;

        bool loopFlag = true;
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
    if (selection == 1)
        instructions();


    if (selection == 2)
    {
        //when user selects begin
        readMaze(roomArray, gameArray, numRooms);
        setup(currentRoom, zombieRoom, numBullets, numRooms, haveGrail, roomArray, gameArray);
        printMemory(gameArray, roomArray);
 int temp;
  while (1)
{
     showConnectedRooms(gameArray[0], roomArray);
    cin >> temp;
    moveRoom(temp, gameArray,roomArray);
   printMemory(gameArray, roomArray);
}
    }
        //if exit is called end the program
        if (selection == 3)
            return 0;

    }
}


//print game instructions
void instructions()
{
    cout << endl;
    cout << " YOUR MISSION, SHOULD YOU CHOOSE TO ACCEPT IT, IS TO SEEK THE HOLY \n GRAIL WITHIN THE RUINS OF AN ANCIENT CHURCH. "
        << "TO SUCCEED YOU MUST \n ENTER THE CHURCH, AVOID THE UNDEAD GUARDIANS, FIND THE GRAIL AND \n ESCAPE. "
        << "YOU HAVE SIX SILVER BULLETS TO PROTECT YOU. IF THE ZOMBIES \n FIND YOU OR YOU RUN OUT OF BULLETS YOU WILL LOSE!" << endl << endl;
}

//print layout of game memory
void printMemory(int gameArray[], int roomArray[][7])
{
    //display all parameters including MAX_ROOMS entries of roomArray and display their contents to the screen.

        cout << "Game Array:" << endl;

        cout << "[currentRoom][ ZombieRoom][ numBullets][   numRooms][  haveGrail]" << endl;
        for (int i = 0; i < 5; i++)
        {
            cout << "[" <<std::setw(11) << gameArray[i] << "]";
        }

        cout << endl << endl;
        cout << "[" << "Room Array:" << "]" << endl;

        cout << "        [ north][ south][  west][  east][player][zombie][ grail]" << endl;
        for (int i = 0; i < MAX_ROOMS; i++)
        {
            cout << "[R" << std::setw(2) << (i + 1) << "] ->";
            for (int j = 0; j < 7; j++)
            {
                cout << "[" << std::setw(6) << roomArray[i][j] << "]";
            }
            cout << endl;
        }


}

void setup(int &currentRoom, int &zombieRoom, int &numBullets, int &numRooms, bool &haveGrail, int roomArray[][7], int gameArray[5])
{
    srand(time(NULL));
    //current room to 1
    gameArray[0] = 1;


    //haveGrail to 0
    gameArray[4] = 0;

    //numBullets to MAX_Bullets
    gameArray[2] = MAX_BULLETS;

    readMaze( roomArray, gameArray, numRooms);
    placeZombie( roomArray, gameArray, numRooms);
    placeGrail(roomArray, gameArray, numRooms);

    roomArray[0][4] = 1;
}

void readMaze(int roomArray[][7], int gameArray[], int & numRooms)
{
    //open easyMaze.txt
    std::ifstream inputFile;
    inputFile.open("easyMaze.txt");
    if (!inputFile)
    {
        std::cout << "Failed to open" << std::endl;
    }

    //read all numbers


    inputFile >> numRooms;
    gameArray[3] = numRooms;
    for(int i = 0 ; i < numRooms; i++)
        for(int j = 0; j < 7; j ++)
            inputFile >> roomArray[i][j];



}

//this function returns a random room
int getRandomRoom(int gameArray[5], int numRooms)
{
    return (rand() % numRooms);
}

//this function places a zombie into one of the rooms
void placeZombie(int roomArray[][7], int gameArray[5], int numRooms)
{
    int randomRoom = 0;
 while ( randomRoom < (numRooms/2))
    {
        randomRoom = getRandomRoom(gameArray,numRooms);
    }
    roomArray[randomRoom][ZOMBIE_INDEX] = 1;
    gameArray[ZOMBIE_ROOM_INDEX] = randomRoom;
}

//this function places a holy grail into one of the rooms
void placeGrail(int roomArray[][7], int gameArray[5], int numRooms)
{
    int randomRoom = 0;
 while ( randomRoom < (numRooms/2))
    {
        randomRoom = getRandomRoom(gameArray,numRooms);
    }
    roomArray[randomRoom][6] = 1;
}

bool checkZombie (int roomToShoot, int roomArray[][7])
{
    if(roomArray[roomToShoot-1][ZOMBIE_INDEX] == 1)
        return true;
    else
        return false;
}

//precondition: get room number to be checked
//postcondition: return true if Grail in the room
bool checkGrail (int roomnumber, int roomArray[][7])
{
    if(roomArray[roomnumber-1][GRAIL_INDEX] == 1)
    {
        cout << "//check grail == true\n";
        return true;
    }
    else
    {
        cout << "//check grail == false\n";
        return false;
    }
}

//precondition: get room number to be checked
//postcondition: return true if Zombie in connected room
bool checkNearZombie(int numRooms, int roomArray[][7])
{
    bool  nearZombie = false;
    for(int i = 0; i < MAX_ROOMS; i++)
    for(int j = 0; j < 4; j++)
    if(roomArray[i][j] == numRooms)                  //locate connected room
        if(checkZombie((i + 1), roomArray))     //check connected room
            nearZombie = true;
            return nearZombie;
}


//precondition: get room number to be checked
//postcondition: return true if Grail in connected room
bool checkNearGrail(int x, int roomArray[][7])
{
    bool nearGrail = false;
    for(int i = 0; i < MAX_ROOMS; i++)
    for(int j = 0; j < 4; j++)
    if(roomArray[i][j] == x)                  //locate connected room
    if(checkGrail((i + 1), roomArray))      //check connected room
    nearGrail = true;
    return nearGrail;
}

//precondition: get game variables
//postcondition: show the winner result, print it out
void winOrLose(bool win, int gameArray[])
{
    if(win)
    {
        cout << "\n===========================================================\n"
        << "YOU HAVE EMERGED FROM THE TEMPLE WITH THE GRAIL!! YOU WIN!!""\n===========================================================\n";
    }
    else
    {
        cout << "\nAs you walk in the room the zombie sees you and devour you whole!\n"
                << "\nYOU LOST!\n";
    }
    gameArray[CURRENT_ROOM_INDEX] = -1;
}

//precondition: get current roomNumber
//postcondition: show connected rooms number
void showConnectedRooms(int &currentRoom, int roomArray[][7])
{
    for(int i = 0; i < MAX_ROOMS; i++)
        for(int j = 0; j < 4; j++)
            if(roomArray[i][j] == currentRoom)
                cout << "Room " << (i + 1) << " is connected to the current room(Room " << currentRoom << ")." << endl ;
                cout << endl;
}

//precondition: get a roomNumber
//postcondition: return true if the room is connected to current room
bool isConnected(int targetRoom, int gameArray[], int roomArray[][7])
{
    bool isConnected = false;
    //cout << "Please enter a room number to test if it is connected to current room: ";
    //int x = inputValidation(1, MAX_ROOMS);
    for(int j = 0; j < 4; j++)
        if(roomArray[targetRoom-1][j] == gameArray[CURRENT_ROOM_INDEX])
            isConnected = true;
            return isConnected;
}

//this function moves what room that you are in
void moveRoom(int roomWanted, int gameArray[],int roomArray[][7])
{
    //test to see if the given room is connected to the current one
    if(isConnected(roomWanted, gameArray, roomArray))
    {

        //if in here it is okay to move

        //-if so set the current room player index to 0, the given room player index to 1 and the current room to the parameter.

        roomArray[gameArray[CURRENT_ROOM_INDEX]-1][PLAYER_INDEX] = 0;

        roomArray[roomWanted - 1][PLAYER_INDEX] = 1;

        gameArray[CURRENT_ROOM_INDEX] = roomWanted;



       //if the player already had the grail move the grail from the old to the new roomWanted
       if(gameArray[HAVE_GRAIL_INDEX] == true)
       {
           for(int i = 0; i < gameArray[NUM_ROOMS_INDEX]; i++)
        {
            roomArray[i][GRAIL_INDEX] = 0;
           }

            roomArray[roomWanted - 1][GRAIL_INDEX] = 1;
       }

        //if player finds the grail in the new room, set haveGrail to true
        if (checkGrail (gameArray[CURRENT_ROOM_INDEX], roomArray))
        {

            //if in here the grail is in this room!
            gameArray[HAVE_GRAIL_INDEX] = true;
        }

        //if the player had the grail with him and is now entered room 1, winner and end game
        if((gameArray[CURRENT_ROOM_INDEX] == 1) && gameArray[HAVE_GRAIL_INDEX])
        {

            winOrLose(1, gameArray);
            exit(0);
        }
    }
    else//if not, let the user know they cannot move there
    {
            cout << "you can not move there, It is not connected to you, please enter a room that is connected to you!";
    }
    return;
}

void shootRoom(int roomToShoot,int gameArray[],int roomArray[][7])
{
    //shoots bullet into room given as the parameter

    if(gameArray[NUM_BULLETS_INDEX] <= 0)
    {
        cout << "you have no bullets left!";
        return;
    }

    //test to see if the given room is connected to the current one,
    if(isConnected(roomToShoot, gameArray, roomArray))
    {
            //if in here it connected
        //if yes decrement the bullet count
        gameArray[NUM_BULLETS_INDEX]--;
        //check to see if the zombie was in that room
        //if yes then zombie is dead, remove him from the game(room array and zombie room)
        if(checkZombie(roomToShoot, roomArray))
        {
                roomArray[roomToShoot][ZOMBIE_INDEX] = 0;
                gameArray[ZOMBIE_ROOM_INDEX] = 0;
        }
        //if no tell player he missed
        else
        {
            cout << "you missed! The zombie was not in the room. \n";
        }
    }
     else//if not, let the user know they cannot move there
    {
            cout << "you can not shoot there, It is not connected to you, please enter a room that is connected to you!";
    }
    return;
}

void moveZombie(int gameArray[], int roomArray[][7])
{
   // if the zombie is alive
   if (gameArray[ZOMBIE_ROOM_INDEX])
   {
       int direction;
       //generate random direction for zombie to go
       direction = rand() % 4;

       //check if the room is free in that direction
       if(roomArray[gameArray[ZOMBIE_ROOM_INDEX]][direction] != 0)
       {
           //move zombie
            roomArray[gameArray[ZOMBIE_ROOM_INDEX]-1][ZOMBIE_INDEX] = 0;
            roomArray[roomArray[gameArray[ZOMBIE_ROOM_INDEX]][direction]][ZOMBIE_INDEX] = 1;
            gameArray[ZOMBIE_ROOM_INDEX] = roomArray[gameArray[ZOMBIE_ROOM_INDEX]][direction];
       }
        //if not zombie stays where he is
    }
   return;
}

 //takes a string and makes sure the first character is Q D S or M,
    //returns true if it is and false if it is not
bool validateSelection(std::string validate)
{
   std::string firstLetter = validate.substr(0,1);
   if(firstLetter.compare("Q") == 0)
    return true;
    if(firstLetter.compare("D") == 0)
    return true;
    if(firstLetter.compare("S") == 0)
    return true;
    if(firstLetter.compare("M") == 0)
    return true;
    else
    return false;
}
