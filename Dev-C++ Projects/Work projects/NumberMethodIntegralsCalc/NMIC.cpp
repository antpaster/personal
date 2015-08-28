/**
	This program is for number method double integrals calculation using one dimensional
	square formulas. 

	Author: Pasternak A.E., antpaster@gmail.com
	
	Date: 28.08.15
	
	File: NMIC.cpp
*/

#include <iostream>
#include <conio.h>
#include <math.h>
#include <string.h>

using namespace std;

/// Struct for exact function definition
struct function2Integrate
{
	int funcId;
	string funcName;
	string strFunc;
} f2i;

/// Initial function for integration is sphere with radius r
double func(double r, double x, double y)
{
	return sqrt(r * r - x * x - y * y);
}

/// Double integrals calculation using one dimensional square formulas
double oneDimSquareFormulaCalc(double r, double a, double b, int m, double c, double d, int n)
{
	double hx = (b - a) / m;
	double hy = (d - c) / n;
	double xi, yj, xstep = a, ystep = c;
	double intValue = 0;			
				
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			xi = xstep + hx / 2;
			yj = ystep + hy / 2;
			intValue += func(r, xi, yj);
		}
		xstep += hx;
		ystep += hy;
	}
	
	return hx * hy * intValue;					
}

/// Exact integral value calculation 
double exactIntVal(double r, double a, double b, double c, double d)
{
	double integrSquareVal = (b - a) * (d - c);
	return (integrSquareVal / (M_PI * r * r)) * 4 * pow(r, 3) * M_PI / 3;
}

/// Per cent calculation error estimation
double calcErrorEstim(double r, double a, double b, int m, double c, double d, int n)
{
	return 100 - (fabs(exactIntVal(r, a, b, c, d) - oneDimSquareFormulaCalc(r, a, b, m, c, d, n)) / 
		   exactIntVal(r, a, b, c, d)) * 100;
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
