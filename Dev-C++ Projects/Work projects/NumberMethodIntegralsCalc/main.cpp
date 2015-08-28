/**
	This program is for number method double integrals calculation using one dimensional
	square formulas. 

	Author: Pasternak A.E., antpaster@gmail.com
	
	Date: 28.08.15
	
	File: main.cpp
*/

#include <iostream>
#include <math.h>
#include <string.h>

#include "NMIC.cpp"

using namespace std;

int main()
{
	f2i.funcId = 1;
	f2i.funcName = "Sphere with radius value r";
	f2i.strFunc = "sqrt(r ^ 2 - x ^ 2 - y ^ 2)";
	
	int ht, menu, m, n;
	double r, a, b, c, d;
	
	cout << "Greetings)\n\nYou've launched the program of the number method " << 
	"multiple integrals calculation.\nFirst of all You should enter the values " <<
	"which are required for integration.";
	cout << "\n\nPlease enter the radius of the sphere (double): ";
	cin >> r;
	cout << "Please enter the Ox integration interval low border (double): ";
	cin >> a;
	cout << "Please enter the Ox integration interval high border (double): ";
	cin >> b;
	cout << "Please enter the number of parts to divide Ox interval (int): ";
	cin >> m;
	cout << "Please enter the Oy integration interval low border (double): ";
	cin >> c;
	cout << "Please enter the Oy integration interval high border (double): ";
	cin >> d;
	cout << "Please enter the number of parts to divide Oy interval (int): ";
	cin >> n;
	
	cout << "\nThe sphere radius is " << r;
	cout << "\nThe entered Ox integration interval is [" << a << "; " << b << "].";
	cout << "\nNumber of Ox interval division parts is " << m; 
	cout << "\n\nThe entered Oy integration interval is [" << c << "; " << d << "].";
	cout << "\nNumber of Oy interval division parts is " << n;	
	
	do
	{
		cout << "\n--------------------------------------------------------------------------------";
		cout << "\nWhat do You want to do?";
		cout << "\n\n1. Calculate the double integral for the surface limited by " <<
		"a sphere with\nradius r";
		cout << "\n2. Show the exact integral value";
		cout << "\n3. Calculate the precision of the number calculation method " <<
		"and compare it with the exact integral value";
		cout << "\n4. Reenter the number of parts for Ox and Oy axises division";
		cout << "\n5. Exit\n";
		
		cin >> menu;
		switch (menu)
		{
			case 1:
			{
				cout << "\n\nThe integral value is: " << oneDimSquareFormulaCalc(r, a, b, m, c, d, n);
				cout << "\n--------------------------------------------------------------------------------";
			}	
			break;
			
			case 2:
			{
				cout << "\n\nThe exact integral value is: " << exactIntVal(r, a, b, c, d) << endl;
				cout << "-------------------------------------------------------------------------------";
			}
			break;
			
			case 3:
			{
				cout << "\n\nThe per cent calculation error estimation is: " <<
				calcErrorEstim(r, 0, 0.5, 10, 0, 0.5, 10) << "%\n";
				cout << "-------------------------------------------------------------------------------";	
			}
			break;
			
			case 4:
			{
				cout << "Please enter the number of parts to divide Ox interval (int): ";
				cin >> m;
				cout << "Please enter the number of parts to divide Oy interval (int): ";
				cin >> n;
				
				cout << "\nNumber of Ox interval division parts is " << m; 
				cout << "\nNumber of Oy interval division parts is " << n;
			}
			break;
			
			case 5: 
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
