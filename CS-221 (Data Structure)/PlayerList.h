#ifndef PLAYERLIST_H
#define PLAYERLIST_H
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "Player.h"

using namespace std;

/***************************************************************************************
 * Description: Define PlayerList class
 * data members: head defines the first node for the player list of type player.
 *               tail deines the last node for the player list of type player.
 *               Size defines the number of player nodes in the player list
 * Member Functions : Inset-- to add a player node into the list also keep track on the 
 *                     size. 
 *                     IsEmpty-- returns true if the list is empty otherwise false
 *                      getSize-- if list is empty then return 0. Otherwise the size of 
 *                                  the list. 
 *                    
 * 
 ***************************************************************************************/


class PlayerList
{ 
    Player *head;
    Player *tail;
    int size;
    public:
        PlayerList();
        Player *find( string firstName, string lastName );
        Player *nodeSort( string firstName, string lastName );
        void del( Player *p);
        Player *insert( Player *p );
        void print ();
        void print( ofstream &o, Player *p );
        float overallAvg();
        bool isEmpty();
        int getSize();
        Player *getHead();
        Player *getTail();
        void insertBefore( Player *p, Player *q );
        void insertAfter( Player *p, Player *q );
};
#endif