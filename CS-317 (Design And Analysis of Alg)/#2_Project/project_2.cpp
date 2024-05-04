/***********************************************************************************
@@@@@@@@@copyright@@@@@@@@
Project 2
Name - Vasu Agarwal
Date - 11/10/2022
Class - CS 317- 01
A-number - A25312905
Description : This programs reads the "input.txt" file containing entries of size (n)
            numbers. Store them in an array and then generate the dynamic programming 
            table representing the Cost and Root. From this table generating and output
            the optimal binary search tree int the outfile file.

Credits or Refrences: https://www.javatpoint.com/optimal-binary-search-tree
                    https://www.youtube.com/watch?v=vLS-zRCHo-Y&ab_channel=AbdulBari
**************************************************************************************/

#include <iostream>
#include <fstream>
#include <iomanip>

#define INPUT_FILENAME "input.txt"
#define OUTPUT_FILENAME "vra0004.txt"
#define SPACE_COUNT 5
#define MAX_ROOT_LEN  2

using namespace std;

struct cell {
    int cost;
    int root;
};
class Node {
    int val;
    Node *right;
    Node *left;
    Node *parent;
    public:
    // Constructor for the class Node
    Node() {
        val = -1;
        right = NULL;
        left = NULL;
        parent = NULL;
    }
    Node( int v, Node *r, Node *l, Node *p ) {
        val = v;
        right = r;
        left = l;
        parent = p;
    }
    // here are the setters and getters
    int getVal() {
        return val;
    }
    void setVal( int val ) {
        val = val;
    }
    Node *getRight() {
        return right;
    }   
    void setRight( Node *right ) {
        this->right = right;
    } 
    Node *getLeft() {
        return left;
    }   
    void setLeft( Node *left ) {
        this->left = left;
    } 
    Node *getParent() {
        return parent;
    }
    void setParent( Node *parent ) {
        this->parent = parent;
    }

};
/*****************************************************************************************
 * Description: Define class Tree.
 * Member Function: root
 *****************************************************************************************/
class Tree {
    Node *root;
    public:
    Tree() {
        root = NULL;   
    }
    Node *getRoot() {
        return root;
    }   
    void setRoot( Node *root ) {
        this->root = root;
    }
    /***********************************************************************************
     * Description: This generateSubTree function is creating the subtree from the dynamic 
     *             programming table. Also checking if the start and end are same or not. 
     *             If they are not equal then calling itself to create the right and left 
     *             subtree.
     **********************************************************************************/
    void generateSubTree( cell **table, int start, int end, Node *parent, bool isLeft ) {
        if( start == end )
            return;
        
        Node *n = new Node( table[start][end].root , NULL, NULL, parent );
        n->setParent( parent );
        if( isLeft )
            parent->setLeft( n );
        else
            parent->setRight( n );
            
        generateSubTree( table, start, n->getVal() -1, n, true );
        generateSubTree( table, n->getVal(), end, n, false );
    }
    /*********************************************************************************
     * Description: Here genarateTreeFromTable is creating the tree from the dynamic 
     *              programming table by calling the generateSubTree function.
    **********************************************************************************/
    void generateTreeFromTable( cell **table, int start, int end, Node *parent ) {
        generateSubTree( table, start, parent->getVal() -1, parent, true );
        generateSubTree( table, parent->getVal(), end, parent, false );
        
    }
    void generateTreeFromTable( cell **table, int n ) {
        generateTreeFromTable( table, 0, n, root );
    }
    /***********************************************************************************
     * Description: Here printPreOrder function is to print the tree in Pre-Order method
     *         in the output file.     
     ***********************************************************************************/
    void printPreOrder( ofstream &o, Node *r , int space ) {
        if( r == NULL ) {
            o << "-" << endl;
            return;
        }
        o << r->getVal() << endl;
        space++;
        for( int i = 0; i < space; i++ ) {
            o << "    ";
        }
        printPreOrder( o, r->getLeft(), space );
        for( int i = 0; i < space; i++ ) {
            o << "    ";
        }
        printPreOrder( o, r->getRight(), space );
    }
    void printPreOrder( ofstream &o ) {
        printPreOrder( o, root, 0 );
    }
};
/**********************************************************************************
* Description: This function is converting the integer into the string.
***********************************************************************************/
string convertIntoString( int n ) {
    stringstream s;
    string str;
    s << n;
    s >> str;
    return str;
}
/**********************************************************************************
* Description: This function is appending the integer with the zero.
***********************************************************************************/
string appendZero( int n ) {
    string s = "";
    int i = 0;
    for( i = 0; i < n; i++ ) {
        s += '0';
    }
    return s;
}
/**********************************************************************************
* Description: This function is printing the array.
***********************************************************************************/
void printArray( int arr[], int size ) {
    for( int i = 0; i < size; i++ ) {
        cout << arr[ i ] << endl;
    }
}
/*****************************************************************************************
 * Description: printCost Function is printing the cost in the output file genarated for 
 *              the dynamic programming table. Also. print the Cost in the string appended 
 *              with zero. To do so calling the converIntoString and appendZero 
 *              function.
 *****************************************************************************************/
void printCost( ofstream &o, int n, cell **table ) {
    int val = table[0][n].cost;
    int len = convertIntoString( val ).length();
    for( int i = 0; i <= n; i++ ) {
        for( int j = 0; j <= n; j++ ) {
            val = table[i][j].cost;
            string str = convertIntoString( val );
            int diff = len-str.length();
            string s = appendZero( diff );
            s.append( str );
            o << s << "    ";
        }
        o << endl;
    }

}
/*****************************************************************************************
 * Description: printRoott Function is printing the root in the output file genarated for 
 *              the dynamic programming table. Also. print the root in the string appended 
 *              with zero. To do so calling the converIntoString and appendZero 
 *              function.
 ****************************************************************************************/
void printRoot( ofstream &o, int n, cell **table ) {
    for( int i = 0; i <= n; i++ ) {
        for( int j = 0; j <= n; j++ ) {
            int val = table[i][j].root;
            string str = convertIntoString( val );
            int diff = MAX_ROOT_LEN-str.length();
            string s = appendZero( diff );
            s.append( str );
            o << s << "    ";
        }
        o << endl;
    }
}
/*****************************************************************************************
 * Description: createPossibleRoots is returns the possible roots.
 *****************************************************************************************/
int *createPossibleRoots( int i, int j ) {
    int diff = j-i;
    int *roots = new int[diff];
    for( int k = 0; k < diff; k++ ) {
        roots[k] = i+1+k;
    }
    return roots;
}
/*****************************************************************************************
 * Description: Here findMinValIndex is finding the minimum value and then returning the 
 *              postion of it.
 *****************************************************************************************/
int findMinValIndex( int *arr, int size ) {
    int minPos = 0;
    for( int i = 1; i < size; i++ ) {
        if( arr[i] < arr[minPos] )
            minPos = i;
    }
    return minPos;
}
/*****************************************************************************************
 * Description: calWeight function is calculating the total weight.
 *****************************************************************************************/
int calWeight( int begin, int end, int freq[] ) {
    int sum = 0;
    for( int i = begin; i < end; i++ ) {
        sum += freq[i];
    }
    return sum;
}
/*****************************************************************************************
 * Description: Here calMinCost function is finding the minimum cost.
 *****************************************************************************************/
void calMinCost( cell **table, int freq[], int i, int j ) {
    int *roots = createPossibleRoots( i, j );
    int *temp = new int[j-i];
    for( int k = 0; k < (j-i); k++ ) {
        temp[k] = table[i][roots[k]-1].cost + table[roots[k]][j].cost;
    }
    int minPos = findMinValIndex( temp, j-i );
    int weight = calWeight( i, j, freq ); 
    table[i][j].cost = weight + temp[minPos];
    table[i][j].root = roots[minPos];
    delete[] roots;
    delete[] temp;

}
void calMinCost( cell **table, int n, int freq[], int diff ) {
    int begin = 0, end = n-diff;
    switch( diff ) {
        case 0: for( int i = begin; i <= end; i++ ) {
                    table[i][i].cost = 0;
                }
                break;
        case 1: for( int i = begin; i <= end; i++ ) {
                    table[i][i+1].cost = freq[i];
                    table[i][i+1].root = i+1;
                }
                break;
        default: for( int i = begin; i <= end; i++ ) {
                    calMinCost( table, freq, i, i+diff );
                }

    }
}
/*****************************************************************************************
 * Description: populateTable function is population the table with the Costs and Roots 
 *              values to create a dynamic programming table.
 *****************************************************************************************/
void populateTable( cell **table, int n, int freq[] ) {
   // for all possible diffrences
   for( int i = 0; i <= n; i++ ) {
        calMinCost( table, n, freq, i );
   }
}
/*****************************************************************************************
 * Description: Here  createTable function is creating the dynamic table.
 *****************************************************************************************/
cell **createTable( int n ) {
    cell **table = new cell *[ n+1 ];
    for( int i = 0; i < n+1; i++) {
        table[i] = new cell[ n+1];
        for( int j =0; j < n+1; j++ ) {
            table[i][j].cost = 0;
            table[i][j].root = 0;       
        }

    }
    return table;
}
int main() {
    int i = 0, n;
    ifstream ifile;
    ofstream ofile;
    // Input and Output file is opened
    ifile.open( INPUT_FILENAME ); 
    ofile.open( OUTPUT_FILENAME );
    if( !ifile ) {
        cout << "file is not opened" << endl;
        return -1;
    }
    ifile >> n;
    int freq[ n ];
    while( ifile >> freq[ i ] ) {
        i++;
    }
    if( !ofile ) {
        cout << " file is not opened " << endl;
        return -1;
    }
    cell **table = createTable( n );
    populateTable( table, n, freq );
    ofile << "Dynamic Programming Table representing cost(C[i][j]): " << endl;
    printCost( ofile, n, table );
    ofile  << endl << endl;
    ofile << endl << "Dynamic Programming Table representing roots(R[i][j]): " << endl;
    printRoot( ofile, n, table );
    // creating new nodes for classes Node and Tree 
    Node *root = new Node( table[0][n].root, NULL, NULL, NULL);
    Tree *t = new Tree();
    // calling the setRoot and generateTreeFromTable functions
    t->setRoot( root );
    t->generateTreeFromTable( table, n );
    ofile << endl << "Optimal Binary Search Tree: " << endl;
    // calling the printPreOrder function
    t->printPreOrder( ofile );
    // Input and Output file is closed
    ifile.close();
    ofile.close();
    return 0;
}