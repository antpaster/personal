#include <iostream>
#include <string.h>
#include <conio.h>

using namespace std;

char *cycleSymbolReplacement(char *, int, int);
char *cycleWordReplacement(char *, int, int);

int main()
{
	char *str = new char[50];
	cout << "Enter your string: ";
	cin >> str;
	cout << "The entered string is: " << str << endl;
//	int beginPos, endPos;
//	cout << "Enter the position of the moving letter: ";
//	cin >> beginPos;
//	cout << "Enter the position of the replacing letter: ";
//	cin >> endPos;
	int i = strlen(str) - 1, j = 1;
	cout << i << endl;
	
	while (str[i] != '_')
		i--;
	cout << i << endl;
	
	str = cycleSymbolReplacement(str, i + 1, 1);
	i++;
	
	cout << str << endl;
		
	while (i != strlen(str))
	{
		str = cycleSymbolReplacement(str, i + 1, j);													/////////////////////////////////////////////////////////////////, j);
		i++;
		j++;
	}
	
	cout << str[j] << endl;
	
	cout << str << endl;
	getch();
	return 0;
}

char *cycleSymbolReplacement(char *str, int beginPos, int endPos)
{
	char tempCh;
	tempCh = str[beginPos - 1];
	if (beginPos < endPos)
	{
		for (int i = 1; i < beginPos; i++)
			str[beginPos - i] = str[beginPos - i - 1];
		str[0] = str[strlen(str) - 1];
		for (int i = strlen(str) - 1; i >= endPos; i--)
			str[i] = str[i - 1];
	}
	else
		for (int i = beginPos - 1; i >= endPos; i--)
			str[i] = str[i - 1];
	str[endPos - 1] = tempCh;
	return str;
}

char *cycleWordReplacement(char *str, int wordBeginPos, int pastePos)
{
	
}
