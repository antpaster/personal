#include <iostream>
#include "MyStack.h"

using namespace std;

template <class Data>
MyStack<Data>::MyStack(int size)
{
	m_pTop = new Data[size];
	_size = size;
	_topElement = -1;
}

template <class Data>
MyStack<Data>::~MyStack()
{
	delete [] m_pTop;
}

template <class Data>
int MyStack<Data>::getSize()
{
	return _size;
}

template <class Data>
Data MyStack<Data>::getTopElement()
{
	return m_pTop[0];
}

template <class Data>
bool MyStack<Data>::pushElement(Data el)
{
	if (_topElement == _size - 1)
		return false;
	_topElement++;
	m_pTop[_topElement] = el;
	return true;
}

template <class Data>
bool MyStack<Data>::pullElement()
{
	if (m_pTop == 0)
		return false;
	m_pTop[_topElement] = 0;
	_topElement--;
	return true;
}

template <class Data>
void MyStack<Data>::printStack()
{
	for (int i = _size - 1; i >= 0; i--)
		cout << m_pTop[i] << ' ';
	cout << endl; 
}
