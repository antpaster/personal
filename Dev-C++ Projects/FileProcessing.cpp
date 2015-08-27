#include <iostream>
#include <conio.h>

using namespace std;

int main()
{
	ifstream file("City_auto.xml", ios::in | ios::binary);
	char buf[81];
	while (!file.eof())
	{
		file.getline(buf, 81);
		cout << buf << endl;
	}
	getch();
	return 0;
}
