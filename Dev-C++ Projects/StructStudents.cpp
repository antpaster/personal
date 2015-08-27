#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
	
using namespace std;

struct Student
{
	char fio[25];
	int groupNumber;
	int marks[5];	
};

double avgMark(Student);

int main()
{
	Student stud[5];
	cout << "Enter the students:\n";
	srand(time(NULL));
	for (int i = 0; i < 5; i++)
	{
		cout << "Enter the student name: ";
		cin >> stud[i].fio;
		stud[i].groupNumber = 590 + rand() % 5;
		for (int j = 0; j < 5; j++)
			stud[i].marks[j] = 3 + rand() % 3;
	}
	
	// Ascending sort of the students by group number
	int tempEl;
	for (int i = 0; i < 5; i++)
		for (int j = i; j < 5; j++)
			if (stud[i].groupNumber > stud[j].groupNumber)
			{
				tempEl = stud[i].groupNumber;
				stud[i].groupNumber = stud[j].groupNumber;
				stud[j].groupNumber = tempEl;
			}
			
	// Echoprint
	cout << "\nThe entered students are:\n";
	for (int i = 0; i < 5; i++)
	{
		cout << i + 1 << ". " << stud[i].fio << ", group " << stud[i].groupNumber << ", marks ";
		for (int j = 0; j < 5; j++)
			cout << stud[i].marks[j] << ' ';
		cout << endl;
	}
	
	// Printint the list of the students with average mark higher than 4
	cout << "\nStudents that have an average mark higher than 4 are:\n";
	int j = 1;
	for (int i = 0; i < 5; i++)
		if (avgMark(stud[i]) > 4.0)
		{
			cout << j << ". " << stud[i].fio << ", group " << stud[i].groupNumber << endl;
			j++;
		}
	if (j == 1)
		cout << "Unfortunately there are no students with such average mark:(";
		
	getch();
	return 0;
}

double avgMark(Student st)
{
	double result = 0;
	for (int i = 0; i < 5; i++)
		result += st.marks[i];
	return result /= 5;
}
