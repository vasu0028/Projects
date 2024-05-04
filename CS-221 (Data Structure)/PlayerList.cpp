#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "PlayerList.h"
#include "Player.h"

using namespace std;

// definition of the constructor
        PlayerList::PlayerList(){
            this->head = NULL;
            int size = 0;
            this-> tail = NULL;

        }
        // This function purpose is to find the player data in the list
        Player* PlayerList:: find( string firstName, string lastName ){
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
         * This Function purpose is to sort the doubly linked based on the 
         * lastName and FirstName entered by the user and then compare it 
         * with the Player data presented in the list. 
         ******************************************************************/

        Player* PlayerList :: nodeSort( string firstName, string lastName ){
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
    /**********************************************************
    * This function purpose is to check If the Entered Player 
    * data exist in the list or not. If it exist 
    * then deleting the entered player from 
    * the list. 
 
     *********************************************************/
     void PlayerList :: del( Player *p){
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

        Player* PlayerList::insert( Player *p )
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
        
        void PlayerList:: print () {
            Player *cur = head;
            cout << "hello" << endl;
            while( cur != NULL ) {
                cur->print();
                cout << endl;
                cur = cur->getNext();
            }
        }
        /****************************************************************************
        This Function is printing the linked in the output file and also printing
        the linked in its reverse order.
        *********************************************************************************/
        void PlayerList :: print( ofstream &o, Player *p ){
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

        float PlayerList :: overallAvg(){
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

        bool PlayerList :: isEmpty(){
            return head == NULL;
        }


        int PlayerList :: getSize(){
            return size;
        }

        Player* PlayerList :: getHead() {
            return head;
        }

        
        Player* PlayerList :: getTail() {
            return tail;
        }

        /*************************************************************************       
         * This function taking two parameters of type Player p and q where q is 
         * the node inserted before the node p.
        * ***********************************************************************/
        void PlayerList :: insertBefore( Player *p, Player *q ){
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
         *  This function is used to insert the node q after the node p. And taking 
         *  the two pararmeters of type Player p and q.
         * ***********************************************************************/
       void PlayerList :: insertAfter( Player *p, Player *q ){

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