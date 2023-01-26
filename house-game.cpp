//James Atkins
//CSC-234-0901
//M3LAB2 (Silver)
//10-20-2021


#include <iostream>
#include <vector>

using namespace std;

/*
The Room is used to organize data for an individual room.
This includes the room's name, description, and exits that lead to other rooms.
*/
class Room
{

public:
    // class fields (variables)
    int id;                         // each room has a numerical ID
    string name;                    // short name
    string description;             // full description
    int north, south, east, west, northEast, goBack, upStairs, laundryRoom, bedRoom, startPoint;   // store the ID's of the adjacent rooms

    // class methods (functions)
    Room() {
        // default constructor
    };

    Room(int id, string name, string description) {
        // alternate constructor - sets up the room
        this->id = id;
        this->name = name;
        this->description = description;
    };

    void describe () {
        // describe the room
        cout << name << endl;
        cout << description << endl;

    };
};
/*
The Game class organizes all the information, contains a vector of Rooms (room list),
as well as player location.
*/
class Game
{
public:

    vector<Room> roomList;      // stores all the Room objects
    int playerLocation;         // ID of the room the player is in

    const int NUM_ROOMS     = 8;    // determines vector size
    const int NOWHERE       = 0;    // indicates something is not right
    const int LIVING_ROOM   = 1;
    const int DINING_ROOM   = 2;
    const int KITCHEN       = 3;
    const int BATHROOM      = 4;
    const int UPSTAIRS      = 5;
    const int LAUNDRY_ROOM  = 6;
    const int BED_ROOM      = 7;

    Game() {
        // constructor
        roomList.resize(NUM_ROOMS);     // sets up the vector to be the right size
        playerLocation = LIVING_ROOM;   // starts the player on the map in the living room
    }

    setup() {
        //build the rooms and connect them
        Room livingRoom;                    //With default constructor
        livingRoom.name = "Living Room";
        livingRoom.id = LIVING_ROOM;
        livingRoom.description = "A simple living room with carpet and a couch. Stairs lead to the second floor";
        livingRoom.north = DINING_ROOM;
        livingRoom.east = BED_ROOM;
        livingRoom.upStairs = UPSTAIRS;
        roomList.at(LIVING_ROOM) = livingRoom;

        Room diningRoom = Room(DINING_ROOM, "Dining Room", "Dusty furniture fills the room.");
        diningRoom.south = LIVING_ROOM;         //alternate constructor
        diningRoom.east = KITCHEN;
        diningRoom.northEast = BATHROOM;
        roomList.at(DINING_ROOM) = diningRoom;

        Room kitchen = Room(KITCHEN, "Kitchen", "A small, dimly lit kitchen.");
        kitchen.west = DINING_ROOM;
        kitchen.north = LAUNDRY_ROOM;
        roomList.at(KITCHEN) = kitchen;

        Room bathroom = Room(BATHROOM, "Bathroom", "A small bathroom with a bathtub and broken shower-head.");
        bathroom.goBack = DINING_ROOM;
        roomList.at(BATHROOM) = bathroom;

        Room laundryRoom = Room(LAUNDRY_ROOM, "Laundry Room", "A room with a washer and dryer.");
        laundryRoom.goBack = KITCHEN;
        laundryRoom.startPoint = LIVING_ROOM;
        roomList.at(LAUNDRY_ROOM) = laundryRoom;

        Room bedRoom = Room(BED_ROOM, "Bedroom", "A bedroom with a empty bed frame and a small closet.");
        bedRoom.goBack = LIVING_ROOM;
        roomList.at(BED_ROOM) = bedRoom;


        Room nowhere = Room(NOWHERE, "Nowhere", "It is dark. You are lost.");
        roomList.at(NOWHERE) = nowhere;

    }

    void tour() {
        int newLocation;    // placeholder used to update location

        //gameplay, walking through the rooms
        cout << endl;
        Room currentRoom = roomList.at(playerLocation);     //LIVING ROOM
        currentRoom.describe();

        //moving to the first room and back
        cout << endl << "walking east..." << endl;
        newLocation = currentRoom.east;
        playerLocation = newLocation;
        currentRoom = roomList.at(playerLocation);          //BEDROOM
        currentRoom.describe();

        cout << endl << "walking back to the previous room..." << endl;
        newLocation = currentRoom.goBack;
        playerLocation = newLocation;
        currentRoom = roomList.at(playerLocation);          //LIVING ROOM
        currentRoom.describe();

        //move to a new room
        cout << endl << "walking north..." << endl;
        //to get to a new room
        newLocation = currentRoom.north;
        // update the player location ID, then get the new room
        playerLocation = newLocation;
        currentRoom = roomList.at(playerLocation);          //DINING ROOM
        //describe the room
        currentRoom.describe();

        //move to the next room and then back to the previous room
        cout << endl << "walking northeast..." << endl;
        newLocation = currentRoom.northEast;
        playerLocation = newLocation;
        currentRoom = roomList.at(playerLocation);          //BATHROOM
        currentRoom.describe();

        //previous room
        cout << endl << "going back to the previous room..." << endl;
        newLocation = currentRoom.goBack;
        playerLocation = newLocation;
        currentRoom = roomList.at(playerLocation);          //DINING ROOM
        currentRoom.describe();

        //next room
        cout << endl << "walking east..." << endl;
        newLocation = currentRoom.east;
        playerLocation = newLocation;
        currentRoom = roomList.at(playerLocation);          //KITCHEN
        currentRoom.describe();

        cout << endl << "walking north of the kitchen..." << endl;
        newLocation = currentRoom.north;
        playerLocation = newLocation;
        currentRoom = roomList.at(playerLocation);          //LAUNDRY ROOM
        currentRoom.describe();

        cout << endl << "walking back to the living room..." << endl;
        newLocation = currentRoom.startPoint;
        playerLocation = newLocation;
        currentRoom = roomList.at(playerLocation);          //LIVING ROOM
        currentRoom.describe();

        //testing nowhere room "fall back code", upStairs
        cout << endl << "walking up the stairs..." << endl;
        newLocation = currentRoom.upStairs;
        playerLocation = NOWHERE;
        currentRoom = roomList.at(playerLocation);
        currentRoom.describe();

    }

};

int main()
{
    Game game;
    cout << "Setting up the game" << endl;
    game.setup();
    cout << endl << "Starting the tour" << endl;
    game.tour();
    cout << endl << "Game tour finished" << endl;

    return 0;
}
