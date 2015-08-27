#include <iostream>
#include <iomanip>
#include <conio.h>
#include <vector>
#include <cstdlib>

using namespace std;

int imageMatr[13][13] = {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1,
    					 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0,
						 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0,
						 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
						 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
						 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0,
						 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
						 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1,
						 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1,
						 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0,
						 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 
						 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0,
						 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
						 
struct Point
{
	int x, y;	
};

typedef vector<Point> pVect;
typedef vector<pVect> ppVect;
							 
int maxWayLength(ppVect, int, int);
void contPathPrint(ppVect);
bool isClosed(ppVect);

int main()
{
	bool endOfScan;
	cout << "The image is:" << endl << endl;
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 13; j++)
			cout << setw(3) << imageMatr[i][j];
		cout << endl;
	}
	cout << endl;
	
	vector<ppVect> contours;
	ppVect contBorders;
	do
	{
		endOfScan = true;
		for (int i = 0; i < 13; i++)
			for (int j = 0; j < 13; j++)
				if (imageMatr[i][j] == 1)
				{
					endOfScan = false;
					contours.push_back(contBorders);
					maxWayLength(contBorders, j, i);
//					if (isClosed(contBorders))
//					{
//						cout << "Contour length: " << contBorders.size() * 2 - 1 << endl;
//						contPathPrint(contBorders);
//					}
//					else
//						cout << "The contour is not closed!" << endl;
				}
	} while (!endOfScan);
	
	cout << endl << "The image is:" << endl << endl;
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 13; j++)
			cout << setw(3) << imageMatr[i][j];
		cout << endl;
	}
	
	getch();
	return 0;
}

int maxWayLength(ppVect contBorders, int x, int y)
{
	Point tempPoint = {x, y};
	
	pVect waveFrontCurr, waveFrontNext;
	waveFrontCurr.push_back(tempPoint);
	
	contBorders.push_back(waveFrontCurr);
	
	int dx[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
	int dy[8] = {0, -1, -1, -1, 0, 1, 1, 1};

	int d = 2;
	bool stop;
	
	imageMatr[y][x] = d * -1;
	do
	{
		stop = true;
		for (vector<Point>::iterator it = contBorders[d - 2].begin(); it != contBorders[d - 2].end(); ++it)
			for (int k = 0; k < 8; k++)
				if (imageMatr[it->y + dy[k]][it->x + dx[k]] == 1)
					{
						stop = false;
						
						tempPoint.x = it->x + dx[k];
						tempPoint.y = it->y + dy[k];
						waveFrontNext.push_back(tempPoint);
						
						imageMatr[it->y + dy[k]][it->x + dx[k]] = (d + 1) * -1;
					}
		if (!waveFrontNext.empty())
			contBorders.push_back(waveFrontNext);
		waveFrontCurr = waveFrontNext;
		waveFrontNext.clear();	
		d++;
	} while (!stop);
	
	isClosed(contBorders);
	cout << endl;
	
	return contBorders.size() * 2 - 1;
}

void contPathPrint(ppVect contBorders)
{
	int i = 0;
	cout << endl;
	for (vector<pVect>::iterator it = contBorders.begin(); it != contBorders.end(); ++it)
	{
		cout << "Wave front number " << i + 1 << ": ";
		for (vector<Point>::iterator jt = it->begin(); jt != it->end(); ++jt)
			cout << " (" << jt->x << ", " << jt->y << ')';
		cout << endl;
		i++;
	}
}

bool isClosed(ppVect contBorders)
{
	int contLength = contBorders.size();
	int neighbourCount = 0;
	bool closeFlag = false;
	for (vector<pVect>::reverse_iterator rit = contBorders.rbegin(); rit != contBorders.rend(); ++rit)
	{
		for (vector<Point>::reverse_iterator rjt = rit->rbegin(); rjt != rit->rend(); ++rjt)
		{
			cout << " (" << rjt->x << ", " << rjt->y << ')';
			/*for (vector<Point>::iterator kt = (it - 1)->end(); kt != (it - 1)->begin(); --kt)
			{
				if (!abs(jt->x - kt->x) && !abs(jt->y - kt->y))
					neighbourCount++;
				if (neighbourCount >= 2)
				{
					closeFlag = true;
					break;
				}
			}
			if (closeFlag)
				break;*/
		}
		cout << endl;
//		if (closeFlag)
//			break;
//		contLength--;
	}

	//contBorders.resize(contLength);
	return true;
}
