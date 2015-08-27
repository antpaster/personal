#include <iostream>
#include <conio.h>
#include "MyStack.h"

using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv)
{
	MyStack<int> type1(20), type2(20), commonStock(50);
	for (int i = 0; i < 20; i++)
		type1.pushElement(i);
	type1.printStack();
	getch();
	return 0;
}
