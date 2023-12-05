#include"Node.h"
class Matrix
{
	Node* head;
	//头指针的右方和下方均为无value的node 方便遍历以及防止空行无法增加节点
	Node* dimension;
	//例如n*m矩阵，因为头指针的右方以及下方均为类头指针 则dimension的row=n col=m(即总大小为(n+1)*(m+1))
public:
	void addNode(Node* nextNode);
	void deleteNode(Node* goalNode);
	int getRowsize() { return dimension->getRow(); }
	int getColsize() { return dimension->getRow(); }
	Node* getHead() { return head; }

	Matrix(int* Dimension);
	Matrix() { dimension = NULL; head = NULL; }

	Matrix operator+(Matrix& b);
	Matrix operator*( Matrix& b);
	Matrix operator=(Matrix& b);
	friend std::ostream& operator<<(std::ostream& os, Matrix& obj);
};
