#ifndef BINARYTREENODE_H
#define BINARYTREENODE_H

template <class Data> class BinaryTreeNode
{
public:
	BinaryTreeNode(Data nodeValue, Data *left, Data *right);
	~BinaryTreeNode();
	
	bool isLeaf();
	
	void setNodeValue(Data val);
	Data getNodeValue();
	
	void setLeftPointer(Data *left);
	Data *getLeftPointer();
	
	void setRightPointer(Data *right);
	Data *getRightPointer();
	
	BinaryTreeNode<Data> searchNode(Data val);
	
//	void appendNode(BinaryTreeNode<Data> btn, Data *parentNodePointer);
	
private:
	Data _nodeValue;
	Data *m_pLeft;
	Data *m_pRight;
		
};

#endif // BINARYTREENODE_H
