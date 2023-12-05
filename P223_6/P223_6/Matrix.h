#include"Node.h"
class Matrix
{
	Node* head;
	//ͷָ����ҷ����·���Ϊ��value��node ��������Լ���ֹ�����޷����ӽڵ�
	Node* dimension;
	//����n*m������Ϊͷָ����ҷ��Լ��·���Ϊ��ͷָ�� ��dimension��row=n col=m(���ܴ�СΪ(n+1)*(m+1))
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
