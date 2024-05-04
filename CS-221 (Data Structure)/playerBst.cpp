/***********************************************************************************
@@@@@@@@@copyright@@@@@@@@
Programing Assignment 4
Name - Vasu Agarwal
Date - 08/01/2022
Class - CS 221
A-number - A25312905
Description : This program reads the players data from a input file, and create a 
        player Binary search tree. The data is then store in an output file.
        This performs BST operations such as Insertion, Free, getSize, print the 
        BST in ascending orderand the reverse of the BST in descending order.
**************************************************************************************/


#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;
/***************************************************************************************
 * Description: Define Player class and its data members with left and right pointer for binary tree
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
    Player *left;
    Player *right; 
   // Player *prev;

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
        this-> left = NULL;
        this-> right = NULL;
    }

    void *setLeft( Player *p ){
        this-> left = p ;
    } 

    Player *getLeft(){
        return left;
    } 

    void *setRight( Player *p ){
        this-> right = p;
    } 

    Player *getRight(){
        return right;
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

    //prints data for player
    void print( ofstream &o, float avg , float obp, float obs ) {
        string name = this -> lastName + ", " + this -> firstName;
        o << setw(25)<< name << setw(5) << " :" << setw(10) <<setprecision( 3 ) << avg << setw(10)<< fixed << setprecision( 3 )<< obp << setw(10 )<< fixed << setprecision(3)<< obs;
        o << endl;
    }
   // printing the data in the reverse order on the screen
    void printReverse( float avg , float obp, float obs ) {
        string name = this -> lastName + ", " + this -> firstName;
        cout << setw(25)<< name << setw(5) << " :" << setw(10) <<setprecision( 3 ) << avg << setw(10)<< fixed << setprecision( 3 )<< obp << setw(10 )<< fixed << setprecision(3)<< obs;
        cout << endl;
    }
    // Printing the palyer name if found in the list
    void print() {
        string name = this -> firstName + ", " + this -> lastName;
        cout<< name ;
    }


};
/***************************************************************************************
 * Description: Define PlayerBst class
 * data members: root defines the first node for the binary tree of type player.
 *              Size defines the number of player nodes in the player list
 * Member Functions : Inset-- to add a player node into the binary tree also keep track on the 
 *                     size. 
 *                      getSize-- if binary tree is empty then return 0. Otherwise the size of 
 *                                  the list. 
 *                    
 * 
 ***************************************************************************************/

class PlayerBst
{
    Player *root;
    int size;
    public:
        // defining the constructor
        PlayerBst()
        {
            this-> root = NULL;
            int size = 0;

        }

        // defining the destructor and inside it calling the freetree fuunction to free binary tree.
        ~PlayerBst(){
            cout << endl << "Destructor Called" << endl;
            freeTree( getRoot() );
            cout<< endl << "Binary Tree FREED"<< endl;
        }

        Player *getRoot() {
            return root;
        }

        void setSize( int i ){
            this -> size = i;
        }
            
        /************************************************************
         * Description: This function is to insert the node and create
         *              a binary search tree in In-Order.           
         ************************************************************/
        Player *insertInOrder( Player *p, Player *q ){
            
            if( p == NULL)
                return q;
            else if(( p-> getLastName().compare( q->getLastName())) > 0 )
                p-> setLeft(insertInOrder( p-> getLeft(), q ));
            else if(( p-> getLastName().compare(q->getLastName())) < 0 )
                p-> setRight(insertInOrder( p-> getRight(), q ));
            else if(( p-> getLastName().compare(q->getLastName())) == 0 ){
                if(( p-> getFirstName().compare(q->getFirstName())) > 0 )
                    p-> setLeft(insertInOrder( p-> getLeft(), q ));
                else
                    p-> setRight(insertInOrder( p-> getRight(), q ));
                }
            return p;
        
            }
        /***************************************************************
         * Description: This function construct the binary tree and set 
         *              the first node as the root. And then calls the 
         *              insertInOrder function to insert the new node.
         * 
         ***************************************************************/ 

        Player *constructBST( Player *q ) {
            if( root == NULL ) {
                root = q;
            }
            else 
                insertInOrder( root, q );
            return root;  
        }
        /*****************************************************************
         * Description: This function is created to print the player data 
         *              inserted in the binary tree using the method of In-Order
         *              to the screen of the user. 
         *****************************************************************/

        void printToScreen( Player *p, int asc = 1 ) {
            if ( p == NULL)
                return;
            if( asc == 1 )
                printToScreen( p->getLeft(), 1);
            else 
                printToScreen( p->getRight(), 0);
            float sum =  p->getSingles() + p-> getDoubles() +  p->getTriples() + p->getHomeRuns() ; // calculating sum
            float avg = p->calAvg( sum );
            float obp = p->calObp( sum );
            float obs = p->calSlugg()+ obp;
            p-> printReverse(avg,obp,obs);
            cout << " " << endl;
            if( asc == 1 )
                printToScreen( p->getRight(), 1);
            else 
                printToScreen( p->getLeft(), 0);
        }
        /*****************************************************************
         * Description: This function is created to print the player data 
         *              inserted in the binary tree using the method of In-Order
         *              to the output file. 
         *****************************************************************/
        void printInOrder( ofstream &o, Player *p, int asc = 1 ) {
            if ( p == NULL)
                return;
            if( asc == 1 )
                printInOrder( o, p->getLeft(), 1);
            else 
                printInOrder( o, p->getRight(), 0);
            float sum =  p->getSingles() + p-> getDoubles() +  p->getTriples() + p->getHomeRuns() ; // calculating sum
            float avg = p->calAvg( sum );
            float obp = p->calObp( sum );
            float obs = p->calSlugg()+ obp;
            p-> print(o,avg,obp,obs);
            o << " " << endl;
            if( asc == 1 )
                printInOrder( o,  p->getRight(), 1);
            else 
                printInOrder( o, p->getLeft(), 0);
            //printInOrder( asc ==1 ? p->getRight(): p->getLeft());
        
        }

        bool isEmpty(){
            return root == NULL;
        }
        /**************************************************************
         * Description: This FreeTree() is created to delete the player
         *              data from the binary tree.
         **************************************************************/
        void freeTree( Player * p ){
            if( p == NULL )
                return;
            freeTree( p->getLeft() );
            freeTree( p -> getRight() );
            delete( p );
        }
        // This function is returning the size of the binary tree.
        int getSize(){
            return size;
        }

};

int main()
{
    ifstream infile;
    ofstream outfile;
    string iFileName, line;
    string oFileName;
    int i = 0;
    cout << "Welcome to the player binary search tree test program. I am going to read player from the input data file."<< endl
            <<"Then I will store all of the player data in a binary search tree using the method of In-Order" << endl
            <<", compute each player's averages and then write the resulting team report to your output file. "<< endl;
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
     
    float sum = 0.0, oAvg =0.0;
    string data;
    PlayerBst *bst = new PlayerBst(); // create a playerBst object.
    cout << endl << endl;
    cout << "Reading data from the file : " << iFileName << endl;
    cout << "Writing the sorted binary tree data in the out file: " << oFileName << endl;
    while( !infile.eof() ) // while loop to read file till the end of it.
    {
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
        bst->constructBST( playerData );
        i++;
        sum =+ playerData->getSingles() + playerData-> getDoubles() +  playerData->getTriples() + playerData->getHomeRuns() ;
        oAvg += playerData->calAvg( sum );  
        bst->setSize(i);
    }

    oAvg = oAvg/ bst->getSize(); // calculating overall average
    outfile << "***************************************************************" << endl;
    outfile << "Printing the Binary Tree in IN-ORDER " << endl;
    outfile << "***************************************************************" << endl << endl;
    outfile << "Baseball Team Report -----------"<< " " << bst->getSize() << " Players found in file" << endl;
    outfile << "Overall Batting Average: " << fixed << setprecision(3) << oAvg << endl<< endl;
    outfile << left << setw( 25 )<< "PLayer Name" <<setw(5) << ":" <<setw( 10 )<<"Average" << setw(10) << "OBP" << setw(10) << "OBS" << endl <<endl;
    outfile << "-------------------------------------------------------------------"<< endl << endl;
    bst->printInOrder(outfile, bst->getRoot());// function call to print the binary tree in the output file in In-Order
    outfile << endl;
    outfile << "***************************************************************" << endl;
    outfile << "Printing the Binary Tree in the Reverse Order" << endl;
    outfile << "***************************************************************" << endl << endl;

    bst->printInOrder( outfile, bst->getRoot(), 0 ); // function call to print the reverse of the binary tree in the output file in In-Order.
    cout << endl << "Printing the reverse Order of the binary tree" << endl << endl;
    bst->printToScreen( bst->getRoot(), 0 ); // function call to print the reverse of the binary tree to the screen.
    delete bst; // Calling the destructor and freeing the binary tree
    cout << endl << endl << "End of Program 4." << endl;
    infile.close(); // closing input file
    outfile.close();  // closing output file.
    return 0;
}