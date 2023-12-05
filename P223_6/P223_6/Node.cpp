#include"Node.h"
Node::Node()
{
	row = col = value = rowLink = colLink = -1;
	down = right = NULL;
}
Node::Node(Node* next, bool rOd)
{
	if (rOd) { right = next; }
	else { down = next; }

	rowLink = next->getRow();
	colLink = next->getCol();
}
Node::Node(int givenRow, int givenCol,int givenValue)
{
	row = givenRow;
	col = givenCol;
	value = givenValue;

	right = down = NULL;
	colLink = rowLink = -1;
}