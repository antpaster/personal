#include <iostream>
#include <iomanip>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

void matrOutput(int **, int, int);
int **clockwiseMatrOneStepTurning(int **, int, int);
 
int main()
{
	cout << "Enter the number of the matrix rows: ";
	int n;
	cin >> n;
	cout << "Enter the number of the matrix columns: ";
	int m;
	cin >> m;
	
	// Initializing the dynamic matrix
	int **matr = new int *[n];
	for (int i = 0; i < n; i++)
		matr[i] = new int[m]; 
		
	srand(time(NULL));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			matr[i][j] = rand() % 100;
//			matr[i][j] = i + 10 * j;
		}
	
	cout << "Your matrix:\n\n";
	matrOutput(matr, n, m);
	 
	cout << endl << "Enter the number of the steps you wish to turn your matrix: ";
	int stepsCount;
	cin >> stepsCount;
	for (int i = 0; i < stepsCount; i++)
		matr = clockwiseMatrOneStepTurning(matr, n, m);
	
	cout << "Result matrix:\n\n";
	matrOutput(matr, n, m);
	
	getch();
	return 0;
}

void matrOutput(int **matr, int n, int m)
{
	for (int i = 0; i < n; i++)
	{
		cout << '>' << setw(10) << matr[i] << " |";
		for (int j = 0; j < m; j++)
			cout << setw (3) << matr[i][j] << ' ';
		cout << endl << endl;
	}
}

int **clockwiseMatrOneStepTurning(int **matr, int n, int m)
{
	// Initializing the dynamic array for the matrix semidiagonal and
	// saving the cooresponding values there
	int *tempBeam = new int[n / 2];
	for (int i = 0; i < n / 2; i++)
		tempBeam[i] = matr[i][i];
		
	// Left side processing
	for (int i = 0; i < n / 2; i++)
		for (int j = i; j < n - i - 1; j++)
			matr[j][i] = matr[j + 1][i];

	// Down side processing	
	for (int i = 0; i < n / 2; i++)
		for (int j = i; j < m - i - 1; j++)
			matr[n - i - 1][j] = matr[n - i - 1][j + 1];
	
	// Right side processing
	for (int i = 0; i < n / 2; i++)
		for (int j = i; j < n - i - 1; j++)
			matr[n - j - 1][m - i - 1] = matr[n - j - 2][m - i - 1];
	
	// Up side processing
	for (int i = 0; i < n / 2; i++)
		for (int j = i; j < m - i - 2; j++)
			matr[i][m - j - 1] = matr[i][m - j - 2];
	
	for (int i = 0; i < n / 2; i++)
		matr[i][i + 1] = tempBeam[i];
		
	delete [] tempBeam;
	return matr;
}
