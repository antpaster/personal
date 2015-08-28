/**
	This program is for calculating the artificial Earth satellite (AES) orbital linear velocity (OLV).
It can calculate OLV for manually entered AES height and for  random generated height in range
[0 - 100000] km.

	Author: Pasternak A.E., antpaster@gmail.com
	
	Date: 24.08.15
*/

#include <iostream>
#include <math.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

/// Contants
const int Rearth = 6400000;
const double g = 9.8;

using namespace std;

double calcLOVC(int);
char calcLoop();

int main()
{
	int ht, menu;
	
	do
	{
		cout << "Greetings)\n\nYou've launched the program of the calculating " << 
		"\nthe artificial Earth satellite (AES) orbital linear velocity (OLV)." <<
		"\n\nWhat do You want to do?";
		cout << "\n\n1. Enter the AES height and calculate its OLV for it";
		cout << "\n2. Use the random generator to obtain the AES height for calculation in" <<
		"\n[0 - 100000] km range";
		cout << "\n3. Exit\n";
		
		cin >> menu;
		switch (menu)
		{
			case 1:
			{
				cout << "\nPlease enter the height of the AES[km]: ";
				cin >> ht;
				cout << "\nThe entered by You height value is: " << ht << " km";
				cout << "\n\nThe velocity value is: " << calcLOVC(ht) << " km/s\n";
				cout << "-------------------------------------------------------------------------------";
			}	
			break;
			
			case 2:
			{
				srand(time(NULL));
				ht = rand() % 100000;
				cout << "\nThe random generated height value is: " << ht << " km";	
				cout << "\n\nThe velocity value is: " << calcLOVC(ht) << " km/s\n";
				cout << "-------------------------------------------------------------------------------";
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

/// The OLV-height dependency formula itself
double calcLOVC(int height)
{
	return Rearth * sqrt(g / (Rearth + height * 1000)) / 1000;
}

/// Calculation loop
char calcLoop()
{
	char ch;
	do
	{
		cout << "\n\nCalculate velocity for another height (y/n)? ";
		ch = getch();
		cout << ch;
		if (ch != 'y' && ch != 'n')
			cout << "\n\nPlease enter only 'y' or 'n' symbols! Try again please"; 
	} while (ch != 'y' && ch != 'n');
			
	cout << endl << endl;			
	
	return ch;
}
