/***********************************************************************************
@@@@@@@@@copyright@@@@@@@@
Programing Assignment 3
Name - Vasu Agarwal
Date - 07/14/2022
Class - CS 221
A-number - A25312905
Description : This program reads the players data from a input file, and create a 
        player double linked list to calculate average, On-basepercentage, and On-Basepercentage
        slugging etc. The data is then store in an output file.
        This performs linked list operations such as Insertion, isEmpty, getSize, insertBefore
        , insertAfter, deletion, print the list and the reverse of the list.
Compiler : using g++ compiler
**************************************************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "PlayerList.cpp"
#include "Player.cpp"


using namespace std;



/*******************************************************************
 * This function has the parameter of type PlayerList
 * and then prompt the user to enter the Player's 
 * lastName and the firstName. 
 *******************************************************************/
void deletePlayer( PlayerList *l){
    string firstName, lastName;
    char ch;

    do {
        cout << endl << "Please Enter the Player FirstName and the LastName to delete from the doubly linked list : ";
        cin >> firstName >> lastName;
        Player *p = l->find(firstName,lastName);
        if( p == NULL){
            cout << "Not Found in the list" << endl;
        }
        else{
            cout  << endl << "Found Name in the List "<< endl;
            l -> del( p );
        }
        cout << endl << "Would you like to remove the player from the list (Y/N): ";
        cin >> ch;
    } while( ch == 'Y' || ch == 'y');
    cout  << endl << "Testing Complete. The new version of the list has been added to the report file." << endl;
    cout << endl << "End of the program 3.";
}

int main()
{
    // Player *p = new Player();
    // p->print();
    // PlayerList *l = new PlayerList();
    // l->print();
    ifstream infile;
    ofstream outfile;
    string iFileName, line;
    string oFileName;
    int i = 0;
    cout << "Welcome to the player statistics calculator test program. I am going to read player from the input data file. You will tell me the names " 
            << "of your input and output files. I will store all of the player data in a list, compute each player's averages and then write the resulting "<< endl
            << "team report to your output file. "<< endl;
    cout << endl << "Enter the name of the Input file: " ;
    cin >> iFileName; 
    infile.open( iFileName ); // condition for the input file
    if (!infile)
	{
		cout << "Unable to open the data file." << endl;
		return 1;
	}
    //else
        //cout << "input  file is opened. " << endl;
    cout << "Enter the output file name:  "; 

    cin >> oFileName;
    outfile.open( oFileName );
    if( !outfile )   // condition for the output file
    {
        cout << "Unable to open the output file. " << endl;
        return -1;
    }
    else 
    cout << "output file is open"<< endl;
     
    float sum = 0.0;
    string data;
    PlayerList *list = new PlayerList(); // create a player list object.
    cout << endl << endl;
    cout << "Reading data from the file : " << iFileName << endl;
    cout << "Writing the sorted linked list data in the out file: " << oFileName << endl;
    while( !infile.eof() ) // while loop to read file till the end of it.
    {
        sum = 0.0;
        Player *playerData = new Player();  // creating dynamic memory allocation for player object.

        infile >> data;
        playerData->setFirstName( data );
        infile>>data ;
        playerData->setLastName( data );
        infile >> data;
        playerData->setPlateApp(stoi(data) );
        infile >> data; 
        playerData->setAtBats( stoi( data ));
        infile >> data;
        playerData->setSingles( stoi( data ) );
        infile >> data;
        playerData->setDoubles( stoi( data ) );
        infile >> data; 
        playerData->setTriples(stoi(data ) );
        infile >> data; 
        playerData->setHomeRuns(stoi(data ) );
        infile >> data;
        playerData->setWalks( stoi( data ) );
        infile >> data ;
        playerData->setHitByPitch( stoi( data ) ) ;
        list->insert( playerData ); // insert into player list
        /*if( playerData ->getPrev() != NULL )
            playerData->getPrev()->print();
        else
            cout<< "NULL";
        
        cout << " - > ";
        playerData->print();
        cout<< endl;*/
    }

    list-> print(outfile, list->getHead()); // printing the data
    outfile << "***************************************************************" << endl;
    outfile << "Printing the refined Linked List after the Deletion of the node" << endl;
    outfile << "***************************************************************" << endl << endl;
    deletePlayer(list); // calling this function to delete the data from the list

    //list->print();
    list-> print(outfile, list->getHead()); // printing the data in file
    cout << endl << endl;
    outfile << "*********************************************" << endl; 
    outfile << "Printing the Linked List in the Reverse Order" << endl;
    outfile << "*********************************************" << endl << endl; 
    list->print(outfile, list->getTail()); // printing the data in reverse order in file
    infile.close(); // closing input file
    outfile.close();  // closing output file.
    return 0;
}