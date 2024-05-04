#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "Player.h"

using namespace std;


    /***********************************************************************************
     * description: Constructor for player class and set default values for the object using 
     * (this) pinter
     * *********************************************************************************/
    Player::Player() {
        this -> firstName = "UNKNOWN" ;
        this -> lastName = "UNKNOWN" ;
        this -> plateAppearances = 0 ;
        this -> atBats = 0 ;
        this -> singles = 0 ;
        this -> doubles = 0 ;
        this -> triples = 0 ;
        this -> homeRuns = 0 ;
        this -> walks = 0 ;
        this -> hitByPitch = 0 ;
        this-> next = NULL;
        this-> prev = NULL;
    }
   // defining the setters and getters for the class Player
    void Player :: setNext( Player *p ){
        this->next = p; 

    }

   Player* Player :: getNext(){
        return next;
    }

    void Player:: setPrev( Player *p ){
        this->prev = p;
    }

   Player* Player :: getPrev(){
        return prev;
    }

    void Player :: setFirstName( string firstName ) {
        this->firstName = firstName;
    }
   string Player :: getFirstName() {
        return firstName;
    }

   void Player :: setLastName( string lastName ) {
        this -> lastName = lastName;
    }

   string Player :: getLastName() {
        return lastName;
    }

   void Player :: setPlateApp( int app ) {
        this -> plateAppearances = app;
    }

    int Player :: getPlateApp( ) {
        return plateAppearances;
    }

    void Player ::  setAtBats( int bats ) {
        this -> atBats = bats;
    }

   int Player :: getAtBats( ) {
        return atBats;
    }

   void Player :: setSingles( int singles ) {
        this -> singles = singles;
    }

    int Player ::  getSingles( ) {
        return singles;
    }

   void Player ::  setDoubles( int doubles ) {
        this -> doubles = doubles;
    }

    int Player :: getDoubles( ) {
        return doubles;
    }

    void Player :: setTriples( int triples ) {
        this -> triples = triples;
    }

    int Player ::  getTriples( ) {
        return triples;
    }

    void Player ::  setHomeRuns( int homeRuns ) {
        this -> homeRuns = homeRuns;
    }

    int Player ::  getHomeRuns( ) {
        return homeRuns;
    }

    void Player ::  setWalks( int walks ) {
        this -> walks = walks;
    }

    int Player ::  getWalks( ) {
        return walks;
    }

   void Player ::  setHitByPitch( int hitByPitch ) {
        this -> hitByPitch = hitByPitch;
    }

    int Player ::  getHitByPitch( ) {
        return hitByPitch;
    }

    // Calculating the Average of the player
    float Player ::  calAvg( float sum ) {
        this -> avg = sum / this -> atBats;
    }

    // Calculating the OBP of the player
    float Player ::  calObp( float sum ){
        this -> obp = ( sum +  this ->walks +  this -> hitByPitch ) / this ->plateAppearances ; 
    }

    // Calculating the slugging of the player
    float Player ::  calSlugg() {
        float data =  this->singles + 2*( this -> doubles ) + 3*( this ->triples ) +  4*( this ->homeRuns ) ;
        return data / this->atBats;
    }

    // prints data for player
    void Player ::  print( ofstream &o, float avg , float obp, float obs ) {
        string name = this -> lastName + ", " + this -> firstName;
        o << setw(25)<< name << setw(5) << " :" << setw(10) <<setprecision( 3 ) << avg << setw(10)<< fixed << setprecision( 3 )<< obp << setw(10 )<< fixed << setprecision(3)<< obs;
        o << endl;
    }
    //Printing the palyer name if found in the list
    void Player ::  print() {
        string name = this -> firstName + ", " + this -> lastName;
        cout<< name ;
    }
