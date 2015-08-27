#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "Triangle.h"

using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) 
{
	Triangle tr;
	double *trSides = new double[3];
	double *trAngles = new double[3];
	
	srand(time(NULL));
	for (int i = 0; i < 3; i++)
		trSides[i] = 10 + rand() % 41;
	tr.setSides(trSides);
	for (int i = 0; i < 3; i++)
		trAngles[i] = rand() % 91;
	tr.setAngles(trAngles);
	
	tr.print();
	getch();
	return 0;
}
