#ifndef PLAYER_H
#define PLAYER_H
//#include <iostream>
    // #include <string>
    // #include <fstream>
    // #include <iomanip>

using namespace std;

/***************************************************************************************
 * Description: Define Player class and its data members with next pointer for linked list
 * Member Functions : getters and setters for properties and other helpers functions
 * 
 ***************************************************************************************/


class Player {
    string firstName ;
    string lastName ;
    int plateAppearances ;
    int atBats ;
    int singles ;
    int doubles ;
    int triples ;
    int homeRuns ;
    int walks ;
    int hitByPitch ;
    float avg;
    float obp;
    Player *next;
    Player *prev;

    public: 
    /***********************************************************************************
     * description: Constructor for player class and set default values for the object using 
     * (this) pinter
     * *********************************************************************************/
    Player();
    void setNext( Player *p );
    void setPrev( Player *p );
    Player *getPrev();
    void setFirstName( string firstName );
    string getFirstName();
    Player *getNext();
    void setLastName( string lastName );
    string getLastName();
    void setPlateApp( int app );
    int getPlateApp();
    void setAtBats( int bats );
    int getAtBats();
    void setSingles( int singles );
    int getSingles();
    void setDoubles( int doubles );
    int getDoubles();
    void setTriples( int triples );
    int getTriples();
    void setHomeRuns( int homeRuns );
    int getHomeRuns();
    void setWalks( int walks );
    int getWalks(); 
    void setHitByPitch( int hitByPitch );
    int getHitByPitch();
    float calAvg( float sum );
    float calObp( float sum );
    float calSlugg();
    void print( ofstream &o, float avg , float obp, float obs );
    void print();

};