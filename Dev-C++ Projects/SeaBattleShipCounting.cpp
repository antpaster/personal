#include <iostream>
#include <conio.h>

using namespace std;

int main()
{
	int field[10][10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
						 0, 1, 1, 1, 1, 0, 0, 0, 0, 0,
						 0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
						 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						 1, 0, 0, 1, 1, 1, 0, 0, 0, 0,
						 1, 0, 0, 0, 0, 0, 0, 0, 1, 1,
						 0, 0, 1, 0, 0, 0, 1, 0, 0, 0,
						 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
						 0, 0, 0, 0, 0, 0, 0, 0, 1, 1};
	int valuedFieldsCount = 0;
	// Printing the field
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			cout << field[i][j] << ' ';
			if (field[i][j] == 1)
				valuedFieldsCount++;
		}
		cout << endl;
	}
	
	int *valuedCoordsValues = new int[valuedFieldsCount], k = 0;
	// Saving the coordinates' values into the dynamic array
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			if (field[i][j] == 1)
			{
				valuedCoordsValues[k] = 10 * i + j;
				k++;
			}

	int shipCount = valuedFieldsCount;
	// Core code
	for (int i = 0; i < valuedFieldsCount; i++)
		for (int j = i + 1; j < valuedFieldsCount; j++)
		{
			if (valuedCoordsValues[i] / 10 == valuedCoordsValues[j] / 10)
				if (valuedCoordsValues[i] == valuedCoordsValues[j] - 1)
				{
					shipCount--;
					continue;
				}
			if (valuedCoordsValues[i] % 10 == valuedCoordsValues[j] % 10)
				if (valuedCoordsValues[i] / 10 == valuedCoordsValues[j] / 10 - 1)
				{
					shipCount--;
					continue;
				}
		}
	// Output
	cout << endl << "The number of the ships is: " << shipCount << endl;
	getch();
	return 0;
}
