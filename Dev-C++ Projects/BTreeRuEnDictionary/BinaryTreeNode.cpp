#include "binarytreenode.h"

template <class Data>
BinaryTreeNode<Data>::BinaryTreeNode(Data nodeValue, Data *left, Data *right)
{
	_nodeValue = nodeValue;
	m_pLeft = left;
	m_pRight = right;
}

template <class Data>
BinaryTreeNode<Data>::~BinaryTreeNode()
{
	delete m_pLeft;
	delete m_pRight;
}

template <class Date>
bool BinaryTreeNode<Data>::isLeaf()
{
	(m_pLeft == 0 && m_pRight == 0) ? return true : return false;
}

template <class Data>
void BinaryTreeNode<class Data>::setNodeValue(Data val)
{
	_nodeValue = val;
}

template <class Data>
Data BinaryTreeNode<Data>::getNodeValue()
{
	return _nodeValue;
}

template <class Data>
void BinaryTreeNode<Data>::setLeftPointer(Data *left)
{
	m_pLeft = left;
}

template <class Data>
Data *BinaryTreeNode<Data>::getLeftPointer()
{
	return m_pLeft;
}

template <class Data>
void BinaryTreeNode<Data>::setRightPointer(Data *right)
{
	m_pRight = right;
}

template <class Data>
Data *BinaryTreeNode<Data>::getRightPointer()
{
	return m_pRight;
}

template <class Data>
BinaryTreeNode<Data> BinaryTreeData<Data>::searchNode(Data val)
{
	bool foundFlag = false;
	while ()
	if (val == _nodeValue)
		foundFlag = true;
	else
}
