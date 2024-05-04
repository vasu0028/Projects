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
**************************************************************************************/

 
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

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
    Player( ) {
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
    void setNext( Player *p ){
        this->next = p; 

    }

    Player *getNext(){
        return next;
    }

     void setPrev( Player *p ){
        this->prev = p;
    }

    Player *getPrev(){
        return prev;
    }

    void setFirstName( string firstName ) {
        this->firstName = firstName;
    }
    string getFirstName() {
        return firstName;
    }

    void setLastName( string lastName ) {
        this -> lastName = lastName;
    }

    string getLastName() {
        return lastName;
    }

    void setPlateApp( int app ) {
        this -> plateAppearances = app;
    }

    int getPlateApp( ) {
        return plateAppearances;
    }

    void setAtBats( int bats ) {
        this -> atBats = bats;
    }

    int getAtBats( ) {
        return atBats;
    }

    void setSingles( int singles ) {
        this -> singles = singles;
    }

    int getSingles( ) {
        return singles;
    }

    void setDoubles( int doubles ) {
        this -> doubles = doubles;
    }

    int getDoubles( ) {
        return doubles;
    }

    void setTriples( int triples ) {
        this -> triples = triples;
    }

    int getTriples( ) {
        return triples;
    }

    void setHomeRuns( int homeRuns ) {
        this -> homeRuns = homeRuns;
    }

    int getHomeRuns( ) {
        return homeRuns;
    }

    void setWalks( int walks ) {
        this -> walks = walks;
    }

    int getWalks( ) {
        return walks;
    }

    void setHitByPitch( int hitByPitch ) {
        this -> hitByPitch = hitByPitch;
    }

    int getHitByPitch( ) {
        return hitByPitch;
    }

    // Calculating the Average of the player
    float calAvg( float sum ) {
        this -> avg = sum / this -> atBats;
    }

    // Calculating the OBP of the player
    float calObp( float sum ){
        this -> obp = ( sum +  this ->walks +  this -> hitByPitch ) / this ->plateAppearances ; 
    }

    // Calculating the slugging of the player
    float calSlugg() {
        float data =  this->singles + 2*( this -> doubles ) + 3*( this ->triples ) +  4*( this ->homeRuns ) ;
        return data / this->atBats;
    }

    // prints data for player
    void print( ofstream &o, float avg , float obp, float obs ) {
        string name = this -> lastName + ", " + this -> firstName;
        o << setw(25)<< name << setw(5) << " :" << setw(10) <<setprecision( 3 ) << avg << setw(10)<< fixed << setprecision( 3 )<< obp << setw(10 )<< fixed << setprecision(3)<< obs;
        o << endl;
    }
    // Printing the palyer name if found in the list
    void print() {
        string name = this -> firstName + ", " + this -> lastName;
        cout<< name ;
    }


};
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
        PlayerList()
        {
            this->head = NULL;
            int size = 0;
            this-> tail = NULL;

        }

        Player *find( string firstName, string lastName ){
            Player *curr = head;
            while( curr != NULL ){                                
                if((curr -> getLastName().compare(lastName)) == 0 && ( curr -> getFirstName().compare(firstName)) == 0 ){
                    return curr;
                }
               curr = curr -> getNext();

            }
            return NULL;
        }
        /*******************************************************************
         * This Function is used to sort the doubly linked based on the 
         * lastName and FirstName entered by the user and then compare it 
         * with the Player data presented in the list. 
         ******************************************************************/

        Player *nodeSort( string firstName, string lastName ){
            Player *curr = head;
            while( curr != NULL ){                                
                if((curr -> getLastName().compare(lastName)) > 0 ){
                    return curr;
                } else if ( curr -> getLastName().compare(lastName) == 0) {
                    if((curr -> getFirstName().compare(firstName)) > 0 ){
                        return curr;
                    }
                }
               curr = curr -> getNext();
            }
            return NULL;
        } 
    /*************************************************************************
    * Description: This function purpose id to check If the Entered Player 
    *              data exist in the list then deleting the entered player from 
    *              the list. 
 
     **************************************************************************/
     void del( Player *p){
            if( p == head ){
                head = p->getNext();
                p-> getNext()->setPrev(NULL);
                p-> setNext(NULL);

            }
            else if( p == tail ){
                p-> getPrev()->setNext( NULL );
                tail = p-> getPrev();
                p-> setPrev( NULL );
            }
            else if( p != NULL ){
                cout<< endl;
                p -> getPrev()->setNext(p->getNext());

                p->getNext()->setPrev( p -> getPrev());

                p->setPrev(NULL);
                p->setNext(NULL);
            }
            p->print();
            cout << " removed successfully"<< endl;
            cout << endl;
            delete( p );
        }
        /************************************************************
         * Description: This function is to create a sorted double link 
         *              list.
         *             
         ************************************************************/
        Player *insert( Player *p )
        {
            if( head == NULL)
            {
                head = p;
                tail = head;
                tail ->setNext(NULL);
            }
            else{
                Player *q = nodeSort( p->getFirstName(), p->getLastName() );
                //p->print();

                if( q == NULL ) {
                    //cout << " Inserting after ";
                    //tail->print();
                    insertAfter( tail, p );
                }
                else {
                    //cout<< " Insderting before ";
                    //q->print();
                    insertBefore( q, p );
                }
                /*tail ->setNext(p);
                p->setPrev(tail);
                tail = p;
                tail -> setNext(NULL);*/
            }
            this-> size++;
            //tail->print();
            return head;
        }
        // This function is used to print the list.
        void print () {
            Player *cur = head;
            while( cur != NULL ) {
                cur->print();
                cout << endl;
                cur = cur->getNext();
            }
        }
        /*************************************************************************************
        Description: This Function is printing the linked in the output file and also printing
                    the linked in its reverse order.
                    Parameter p is either head or tail.
        **************************************************************************************/
        void print( ofstream &o, Player *p ){
            Player *temp = p;
            o << "Baseball Team Report -----------"<< " " << size << " Players found in file" << endl;
            o << "Overall Batting Average: " << fixed << setprecision(3) <<overallAvg()<< endl<< endl;
            o << left << setw( 25 )<< "PLayer Name" <<setw(5) << ":" <<setw( 10 )<<"Average" << setw(10) << "OBP" << setw(10) << "OBS" << endl <<endl;
            o << "-------------------------------------------------------------------"<< endl << endl;
           while( temp != NULL )
            {
                float sum =  temp->getSingles() + temp-> getDoubles() +  temp->getTriples() +  temp->getHomeRuns() ; // calculating sum
                float avg = temp->calAvg( sum );
                float obp = temp->calObp( sum );
                float obs = temp->calSlugg()+ obp;
                temp-> print(o,avg,obp,obs);
                if( p == head )
                    temp = temp->getNext();
                if( p == tail )
                    temp = temp->getPrev();
            }
            o << endl << endl;

        }

        float overallAvg(){
            Player *temp = head;
            float oAvg = 0.0;
            while( temp != NULL )
            {
            
                float sum =  temp->getSingles() + temp-> getDoubles() +  temp->getTriples() +  temp->getHomeRuns() ;
                oAvg += temp->calAvg( sum );  
                temp = temp->getNext();         
            }
            return (oAvg)/size;
        }

        bool isEmpty(){
            return head == NULL;
        }


        int getSize(){
            return size;
        }

        Player *getHead() {
            return head;
        }

        
        Player *getTail() {
            return tail;
        }

        /*************************************************************************       
         Description: This function taking two parameters of type Player p and q where q is 
                    the node inserted before the node p.
        * ***********************************************************************/
        void insertBefore( Player *p, Player *q ){
            if( p == head ){
                p -> setPrev(q);
                q-> setNext(p);
                head = q;
            }
            else{
                p -> getPrev() -> setNext(q);
                q -> setNext(p);
                q -> setPrev( p -> getPrev());
                p -> setPrev(q);
            }
        }
        /*************************************************************************       
         Description: This function is to insert the node q after the node p. 
                    And taking the two pararmeters of type Player p and q.
         ***********************************************************************/
       void insertAfter( Player *p, Player *q ){

            if( p == head ){
                p -> setNext(q);
                q -> setPrev(p);
                tail = q;
            }
            else if( p == tail ){
                p -> setNext(q);
                q -> setPrev(p);
                tail = q;
            }
            else if( p != NULL ){
                p -> getPrev() -> setNext(q);
                q -> setNext(p);
                q -> setPrev( p -> getPrev());
                p -> setPrev(q);
            }         
            
        }


};
/*******************************************************************
 Description: This function has the parameter of type PlayerList
            and then prompt the user to enter the Player's lastName 
            and the firstName to delete.
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
    //else 
    //cout << "output file is open"<< endl;
     
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
    outfile << "**********************************************" << endl << endl;
    list->print(outfile, list->getTail()); // printing the data in reverse order in file
    infile.close(); // closing input file
    outfile.close();  // closing output file.
    return 0;
}
