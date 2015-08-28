/**
	This program is for number method multiple integrals calculation. 

	Author: Pasternak A.E., antpaster@gmail.com
	
	Date: 26.08.15
*/

#include <iostream>
#include <math.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

struct function2Integrate
{
	int funcId;
	char *funcName;
	char *strFunc;
} f2i;

/// Initial function for integration is sphere with radius 1
double func(double x, double y)
{
	return sqrt(1 - x * x - y * y);
}

/// Double integrals calculation using one dimensional square formulas
double oneDimSquareFormulaCalc(double a, double b, int m, double c, double d, int n)
{
	double hx = (b - a) / m;
	double hy = (d - c) / n;
	double xi, yj, xstep = a, ystep = b;
	double intValue = 0;			
				
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			xi = xstep + hx / 2;
			yj = ystep + hy / 2;
			intValue += func(xi, yj);
			ystep += hy;
		}
		xstep += hx;
	}
	
	return intValue;					
}

/// Per cent calculation error estimation
double calcErrorEstim(double a, double b, int m, double c, double d, int n)
{
	double exactIntVal = 4 * M_PI / 3;
	return fabs(exactIntVal - oneDimSquareFormulaCalc(a, b, m, c, d, n)) / exactIntVal * 100;
}
 
char calcLoop();

int main()
{
	f2i.funcId = 1;
	f2i.funcName = "Sphere with radius value 1";
	f2i.strFunc = "sqrt(1 - x ^ 2 - y ^ 2)";
	
	int ht, menu;
	
	do
	{
		cout << "Greetings)\n\nYou've launched the program of the number method " << 
		"multiple integrals calculation.\n\nWhat do You want to do?";
		cout << "\n\n1. Calculate the double integral for the surface limited by " <<
		"a sphere with\nradius 1";
		cout << "\n2. Calculate the precision of the number calculation method " <<
		"and compare it with the exact integral value";
		cout << "\n3. Exit\n";
		
		cin >> menu;
		switch (menu)
		{
			case 1:
			{
//				cout << "\nPlease enter the height of the AES[km]: ";
//				cin >> ht;
//				cout << "\nThe entered by You height value is: " << ht << " km";
//				cout << "\n\nThe velocity value is: " << calcLOVC(ht) << " km/s\n";
//				cout << "-------------------------------------------------------------------------------";
			}	
			break;
			
			case 2:
			{
//				srand(time(NULL));
//				ht = rand() % 100000;
//				cout << "\nThe random generated height value is: " << ht << " km";	
//				cout << "\n\nThe velocity value is: " << calcLOVC(ht) << " km/s\n";
//				cout << "-------------------------------------------------------------------------------";
			}
			break;
			
			case 3: 
			{
				cout << "\nFarewell)";
				return 0;	
			}
			
			default: cout << "\nYou should enter only numbers in menu!"; break;
		}
	} while (calcLoop() != 'n');
	
	cout << "Farewell)";
	return 0;
}

/// Calculation loop
char calcLoop()
{
	char ch;
	do
	{
		cout << "\n\nCalculate once more (y/n)? ";
		ch = getch();
		cout << ch;
		if (ch != 'y' && ch != 'n')
			cout << "\n\nPlease enter only 'y' or 'n' symbols! Try again please"; 
	} while (ch != 'y' && ch != 'n');
			
	cout << endl << endl;			
	
	return ch;
}
