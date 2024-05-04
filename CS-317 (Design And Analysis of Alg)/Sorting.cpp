/***********************************************************************************
@@@@@@@@@copyright@@@@@@@@
Project 1
Name - Vasu Agarwal
Date - 10/04/2022
Class - CS 317- 01
A-number - A25312905
Description : This programs reads the "input.txt" file containing entries of size (n)
            numbers. Store them in an array and then sort them using quick Sort and Merge 
            sort functions. Further, print the sorted array in the ouptput files. Also 
            printing the total number of comparisons made in each sort method. 
**************************************************************************************/

#include<iostream>
#include<fstream>

using namespace std;

int comparison_count = 0;

bool LESS( double a, double b )
{
    comparison_count ++;
    return a < b;

}

int partition( double arr[], int low, int high )
{
    double pivot = arr[ high ];
    int i = low-1;

    for( int j = low; j < high; j++ )
    {
        if( LESS( arr[ j ],pivot ) )
        {
            i++;
            // swap
            double temp = arr[ i ];
            arr[ i ] = arr[ j ];
            arr[ j ] = temp;


        }
    }
    i++;
    double temp = arr[ i ];
    arr[ i ] = pivot;
    arr[ high ] = temp;
    return i; // pivot index
}

int randomPartition( double arr[], int low, int high )
{
    int random = low + rand() % ( high - low );
    double temp = arr[ random ];
    arr[ random ] = arr[ high ];
    arr[ high ] = temp;
    return partition( arr, low, high );
}

void quickSort( double arr[], int low, int high )
{
    if( low < high )
    {
        int pidx = randomPartition( arr, low, high );
        quickSort( arr, low, pidx-1 );
        quickSort( arr, pidx+1, high );
    }
}

void merge( double arr[], int s_idx, int mid, int e_idx )
{
   double *merged = new double[ e_idx - s_idx + 1 ];
   int size = sizeof( merged ) / sizeof( merged[ 0 ] );
   int idx1 = s_idx;
   int idx2 = mid + 1;
   int x = 0;
   int i, j;
   while( idx1 <= mid && idx2 <= e_idx )
   {
    if( LESS( arr[ idx1 ], arr[ idx2 ] ) )
        merged[ x++ ] = arr[ idx1++ ];
    else    
        merged[ x++ ] = arr[ idx2++ ];
   }

   while( idx1 <= mid )
   {
    merged[ x++ ] = arr[ idx1++ ];
   }

   while( idx2 <= e_idx )
   {
    merged[ x++ ] = arr[ idx2++ ];
   }
    for( i = 0, j = s_idx; i < size; i++, j++ )
    {
        arr[ j ] = merged[ i ];
        
    }

}

void mergeSort( double arr[], int s_idx, int e_idx )
{
    if( s_idx >= e_idx )
    {
        return;
    }

    int mid = s_idx + ( e_idx - s_idx ) / 2;
    mergeSort( arr, s_idx, mid );
    mergeSort(arr, mid + 1, e_idx );
    merge(arr, s_idx, mid, e_idx );


}

void writeInFile( ofstream &o, double arr[], int size )
{
    for( int i = 0; i < size; i++)
    {
        o << arr[ i ] << endl;
    }
    o << "Total comparison_count = " << comparison_count << endl;
}

void copyArray( double a[], double b[], int size )
{
    for( int i = 0; i < size; i++ )
    {
        b[ i ] = a[ i ];
    }
}
 
int main()
{
    
    int i = 0;
    int n;
    // reading input file entries into array
    fstream ifile;
    ofstream ofile;
    ifile.open( "input.txt" );
    if( !ifile )
        cout << "Unable to open the file" << endl;
    else 
    {  
        cout << "File is opened" << endl;
        ifile >> n;
        double arr[ n ];
        double a[ n ];
        while( ifile >> arr[ i ] )
        {
            i++;
        }
        copyArray( arr, a, n );
        ifile.close();
        cout << "file is closed" << endl;    
        quickSort( arr, 0, n-1 );

        ofile.open("vra0004_quick.txt");
        writeInFile( ofile, arr, n );
        ofile.close();
        comparison_count = 0;

        mergeSort( a, 0, n-1 );
        ofile.open("vra0004_merge.txt");
        writeInFile( ofile, arr, n );
        ofile.close();
    }
    
    cout << "Sorting Done" << endl;  
    return 0;
}