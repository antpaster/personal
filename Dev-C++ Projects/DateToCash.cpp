#include <iostream>
#include <string.h>

using namespace std;

int main()
{
	cout << "Enter the date: ";
	char *date = new char[5];
	cin >> date;
	cout << "The entered date is: " << date << endl;
	char *dollars = new char[2];
	char *cents = new char[2];
	dollars = strncpy(dollars, date, 2);
	dollars[2] = '\0';
	int i = strlen(date) - 1;
	while (date[i] != '.')
	{
		cents[i - 3] = date[i];
		i--;
	}
	cents[2] = '\0';
	cout << "Output: " << dollars << " dollars, " << cents << " cents.\n";
	char ch;
	cin >> ch;
	return 0;
}
