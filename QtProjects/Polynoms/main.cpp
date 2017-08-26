#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>

#include "polynomial.cpp"

using namespace std;

int main()
{
    srand(time(NULL));

    vector<int> coeffVect1, coeffVect2;

    for (int i = 0; i < 5; i++)
        coeffVect1.push_back(rand() % 10);

    for (int i = 0; i < 7; i++)
        coeffVect2.push_back(rand() % 10);

    Polynomial<int> poly1(coeffVect1), poly2(coeffVect2);

    cout << poly1 << endl << poly2 << endl;

    return 0;
}

