using namespace std;
#include<iostream>
class Node
{
	int row;
	int col;
	int value;
	
	int rowLink;
	int colLink;
	
	Node* down;
	Node* right;
public:
	Node();
	Node(Node* next, bool rOd);
	Node(int givenRow, int givenCol,int givenValue);

	int getRow() { return row; }
	int getCol() { return col; }
	int getRowlink() { return rowLink; }
	int getCollink() { return colLink; }
	int getValue() { return value; }


	Node* getDown() { return down; }
	Node* getRight() { return right; }

	void downLink(Node* downNode)
	{ 
		down = downNode;
		rowLink = downNode->getRow();
	}
	void rightLink(Node* rightNode) 
	{ 
		right = rightNode;
		colLink = rightNode->getCol();
	}

	void addValue(int add) { value += add; }


};
