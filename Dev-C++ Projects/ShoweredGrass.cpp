/* The program of the definiton of the number of the points of the grass, which were both trimmered
and showered. the trimmered area is a rectangle with the coordinates (x1, y1) (left down corner and
(x2, y2) (right up corner). The showered area is a circle with cnter coordinates (x3, y3) and radius r.
The output is the number of the points which belong to the joint area.

Author: Pasternak Anton

Date: 04.11.2013 2:33 PM
*/

#include <iostream>
#include <conio.h>
#include <math.h>

using namespace std;

// The function of checking if the point is in the circle
bool isInCircle(int xc, int yc, int r, int x, int y);

int main()
{
	// Input
	cout << "Enter the left down rectangle coordinates (x1, y1):\n";
	int x1, y1;
	cin >> x1 >> y1;
	cout << "Enter the right up rectangle coordinates (x2, y2):\n";
	int x2, y2;
	cin >> x2 >> y2;
	cout << "Enter the circle center coordinates (x3, y3):\n";
	int x3, y3;
	cin >> x3 >> y3;
	cout << "Enter the circle radius: ";
	int r;
	cin >> r;
	
	// Echoprint
	cout << endl << "The input data:\nRectangle: (" << x1 << ", " << y1 << ") (" << x2 << ", " << y2 << ')';
	cout << "\nCircle: (" << x3 << ", " << y3 << ") " << r << endl;
	
	int trimmeredNshoweredPointsCount = 0;
	for (int i = x1; i <= x2; i++)
		for (int j = y1; j < y2; j++)
			if (isInCircle(x3, y3, r, i, j))
				trimmeredNshoweredPointsCount++;
				
	// Output
	cout << "\nThe number of the trimmered and showered points of the grass is: " << trimmeredNshoweredPointsCount;
	getch();
	return 0;
}

bool isInCircle(int xc, int yc, int r, int x, int y)
{
	if (x >= xc - r && x <= xc + r)
	{
		if (y >= yc - (int)trunc(sqrt(r * r - x * x)) && y >= yc + (int)trunc(sqrt(r * r - x * x))) 
			return true;
		else
			return false;
	}
	else
		return false;
}
