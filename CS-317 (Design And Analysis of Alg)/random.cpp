/***************************************************************************************
 * Description: Define fRand function which takes two parameter Fmin and fMax.
 *              This function generates the random number n between the range of min and 
 *              max. And then store those random numbers in the input file to be sorted 
 *              using quick and merge
 * 
 ***************************************************************************************/
#include <iostream>
#include <fstream>

using namespace std;

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

int main()
{
    ofstream o;
    o.open("input.txt");
    double min = -1000;
    double max = 1000;
    int n = 10000;
    o << n << endl;
    for(int i = 0; i < n; i++)
    {
        o << fRand(min, max) << endl;
    }
    o.close();

    return 0;
}