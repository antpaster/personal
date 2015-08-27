#ifndef MYSTACK_H
#define MYSTACK_H

template <class Data> class MyStack
{
public:
	MyStack(int size);
	~MyStack();

	int getSize();

	Data getTopElement();
	
	bool pushElement(Data el);
	
	bool pullElement();
	
	void printStack();
	
private:
	int _size;
	Data *m_pTop;
	Data _topElement;
};

#endif // MYSTACK_H
