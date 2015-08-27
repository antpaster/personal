#include <iostream>
#include <conio.h>
#include "Rectangle.h"

using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

Rectangle createRectangle();

int main(int argc, char** argv) 
{
	int menuItem;
	Rectangle r1, r2;
	bool exitFlag = false;
	while (true)
	{
		cout << "\nWelcome to the main menu. Please choose the action from the list below:\n\n";
		cout << "1. Create a new rectangle.\n";
		cout << "2. Print an information about the rectangle.\n";
		cout << "3. Move the rectangle by the specified steps.\n";
		cout << "4. Change the size of the rectangle by specified steps.\n";
		cout << "5. Make a united rectangle which includes two ones in itself.\n";
		cout << "6. Make a common rectangle which is the common area of the two ones.\n";
		cout << "7. Exit program.\n";
		cout << "\nEnter the number of the selected item of the menu: ";
		do
		{
			cin >> menuItem;
			if (menuItem < 1 || menuItem > 7)
				cout << "The entered character is uncorrect. Please try again\n";
		} while (menuItem < 1 || menuItem > 7);
		
		switch (menuItem)
		{
			case 1: r1 = createRectangle(); break;
			case 2: break;
			case 3: break;
			case 4: break;
			case 5: break;
			case 6: break;
			case 7: exitFlag = true; break;
		}
		if (exitFlag)
			break;
	}
	return 0;
}

Rectangle createRectangle()
{
	cout << "Enter the left down corner's coordinates (x1, y1): ";
	Point ldc;
	cin >> ldc.x >> ldc.y;
	cout << "Enter the right up corner's coordinates (x2, y2): ";
	Point ruc;
	cin >> ruc.x >> ruc.y;
	Rectangle rect(ldc, ruc);
	return rect;
}
