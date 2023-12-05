#include"Matrix.h"  
Matrix::Matrix(int* Dimension)
{
	head = new Node(0, 0, -1);
	head->rightLink(head);
	head->downLink(head);

	dimension = new Node(Dimension[0], Dimension[1], -1);
	dimension->rightLink(dimension);
	dimension->downLink(dimension);

	Node* current1=head;
	Node* current2=head;

	//�趨ά���Լ������� �����е�ͷָ��ֱ������·�/�ҷ������Լ�
	for (int i = 1; i <= Dimension[1]; )
	{
		current1 = new Node(0, i++, -1);
		current1->downLink(current1);
		current2->rightLink(current1);
		if (i > Dimension[1]) { current1->rightLink(head); }
		else
		{
			current2 = new Node(0, i++, -1);
			current2->downLink(current2);
			current1->rightLink(current2);
		}
	}

	current1 = head;
	current2 = head;

	for (int i = 1; i <= Dimension[0]; )
	{
		current1 = new Node( i++,0, -1);
		current1->rightLink(current1);
		current2->downLink(current1);
		if (i > Dimension[0]) { current1->downLink(head); }
		else
		{
			current2 = new Node( i++,0, -1);
			current2->rightLink(current2);
			current1->downLink(current2);
		}
	}
}
void Matrix::addNode(Node* nextNode)    //�߼�������                                
{
	Node* upNode = this->head;
	Node* leftNode = this->head;

	//�����Ϸ��ڵ����¼���Ľڵ�
	
		while (upNode->getCol()!= nextNode->getCol())
		{
			upNode = upNode->getRight();
		}
		while (upNode->getDown()->getRow() < nextNode->getRow()&&upNode->getDown()->getRow()!=0)
		{
			upNode = upNode->getDown();
		}
		nextNode->downLink(upNode->getDown());
		upNode->downLink(nextNode);
	

	//�����󷽽ڵ���¼���Ľڵ�

		while (leftNode->getRow() != nextNode->getRow())
		{
			leftNode = leftNode->getDown();
		}
		while (leftNode->getRight()->getCol() < nextNode->getCol()&&leftNode->getRight()->getCol() != 0)
		{
			leftNode = leftNode->getRight();
		}
		nextNode->rightLink(leftNode->getRight());
		leftNode->rightLink(nextNode);
	
}
void Matrix::deleteNode(Node* goalNode)
{
	Node* upNode = this->head;
	Node* leftNode = this->head;

	//�����Ϸ��ڵ����¼���Ľڵ�
	while (upNode->getCol() != goalNode->getCol())
	{
		upNode = upNode->getRight();
	}
	while (upNode->getRowlink() < goalNode->getRow())
	{
		upNode = upNode->getDown();
	}
	upNode->downLink(goalNode->getDown());

	//�����󷽽ڵ���¼���Ľڵ�
	while (leftNode->getRow() != goalNode->getRow())
	{
		leftNode = leftNode->getDown();
	}
	while (leftNode->getCollink() < goalNode->getCol())
	{
		leftNode = leftNode->getRight();
	}
	leftNode->rightLink(goalNode->getRight());

	delete goalNode;
}
Matrix Matrix::operator+(Matrix& b)
{
	int goalDimension[2]{ this->getRowsize(),this->getColsize()};
	Matrix afterAdd(goalDimension);

	Node* thisCurrent = this->head;
	Node* bCurrent = b.getHead();
	Node* newCurrent=NULL;

	int time1 = 0;
	int time2 = 0;
	while (bCurrent->getRight()->getCol() != 0&&thisCurrent->getRight()->getCol()!=0)//����ͷָ�뿪ʼ �������±�����ÿ�λص�ͷָ��ʱ�����ƶ�һλ
	{
		time1++;

		thisCurrent = thisCurrent->getRight();
		bCurrent = bCurrent->getRight();

		while (bCurrent->getDown()->getRow() != 0||thisCurrent->getDown()->getRow()!=0)
		{
			time2++;
			if (bCurrent->getDown()->getRow() != 0&&thisCurrent->getDown()->getRow()!=0)
			{
				if (bCurrent->getDown()->getRow() == thisCurrent->getDown()->getRow())
				{
					bCurrent = bCurrent->getDown();
					thisCurrent = thisCurrent->getDown();
					if ((bCurrent->getValue() + thisCurrent->getValue())!=0)
					{
						newCurrent = new Node(bCurrent->getRow(), bCurrent->getCol(), bCurrent->getValue() + thisCurrent->getValue());
						cout << "����1��" << "Row: " << bCurrent->getRow() << " Col: " << bCurrent->getCol() << " Value: " << newCurrent->getValue()<<endl;
						cout << "detail:" << endl << "thisCurrent:(" << thisCurrent->getRow() << "," << thisCurrent->getCol() << "), Value: " << thisCurrent->getValue() << endl;
						cout<< "bCurrent:(" << bCurrent->getRow() << "," << bCurrent->getCol() << "), Value: " << bCurrent->getValue() << endl;
						cout << "�жϣ�" << (thisCurrent == bCurrent) << endl;
						afterAdd.addNode(newCurrent);
					}
				}
				else if (bCurrent->getDown()->getRow() > thisCurrent->getDown()->getRow())
				{
					thisCurrent = thisCurrent->getDown();
					newCurrent = new Node(thisCurrent->getRow(), thisCurrent->getCol(), thisCurrent->getValue());
					cout << "����2��" << "Row: " << thisCurrent->getRow() << " Col: " << thisCurrent->getCol() << " Value: " << newCurrent->getValue()<<endl;
					afterAdd.addNode(newCurrent);
				}
				else if (bCurrent->getDown()->getRow() < thisCurrent->getDown()->getRow())
				{
					bCurrent = bCurrent->getDown();
					newCurrent = new Node(bCurrent->getRow(), bCurrent->getCol(), bCurrent->getValue());
					cout << "����3��" << "Row: " << bCurrent->getRow() << " Col: " << bCurrent->getCol() << " Value: " << newCurrent->getValue()<<endl;
					afterAdd.addNode(newCurrent);
				}
			}
			else if (bCurrent->getDown()->getRow() == 0 && thisCurrent->getDown()->getRow() != 0)
			{
				thisCurrent = thisCurrent->getDown();
				newCurrent = new Node(thisCurrent->getRow(), thisCurrent->getCol(), thisCurrent->getValue());
				cout << "����4��" << "Row: " << thisCurrent->getRow() << " Col: " << thisCurrent->getCol() << " Value: " << newCurrent->getValue() << endl;
				afterAdd.addNode(newCurrent);
			}
			else if (bCurrent->getDown()->getRow() != 0 && thisCurrent->getDown()->getRow() == 0)
			{
				bCurrent = bCurrent->getDown();
				newCurrent = new Node(bCurrent->getRow(), bCurrent->getCol(), bCurrent->getValue());
				cout << "����5��" << "Row: " << bCurrent->getRow() << " Col: " << bCurrent->getCol() << " Value: " << newCurrent->getValue() << endl;
				afterAdd.addNode(newCurrent);
			}
			
		}

		//ʹ���ػ���ͷָ�루���ף�
		while (bCurrent->getRow() != 0)
		{
			bCurrent = bCurrent->getDown();
		}
		while (thisCurrent->getRow() != 0)
		{
			thisCurrent = thisCurrent->getDown();
		}

	}
	cout << "time1:" << time1 << endl;
	cout << "time2:" << time2<<endl;
	return afterAdd;
}
Matrix Matrix::operator*(Matrix& b)
{
	int newDimension[2]{ getRowsize(),b.getColsize() };
	Matrix afterMulti(newDimension);
	
	Node* thisCurrent = head;
	Node* bCurrent = b.getHead();
	Node* newCurrent;

	while (thisCurrent->getDown() != head && bCurrent->getRight() != b.getHead())
	{
		thisCurrent = thisCurrent->getDown();
		bCurrent = bCurrent->getRight();
		
		
		int newValue = 0;

		while (bCurrent->getDown()->getRow() != 0 && thisCurrent->getRight()->getCol() != 0)
		{
			if (bCurrent->getDown()->getRow() == thisCurrent->getRight()->getCol())
			{
				bCurrent = bCurrent->getDown();
				thisCurrent = thisCurrent->getRight();
				newValue += (bCurrent->getValue() + thisCurrent->getValue());
			}
			else if (bCurrent->getDown()->getRow() > thisCurrent->getRight()->getCol()) { thisCurrent = thisCurrent->getRight(); }
			else if (bCurrent->getDown()->getRow() < thisCurrent->getRight()->getCol()) { bCurrent = bCurrent->getDown(); }
		}

		//ʹ���ڵ��ػ���ͷ�ڵ�λ��
		while (bCurrent->getRow() != 0)
		{
			bCurrent = bCurrent->getDown();
		}
		while (thisCurrent->getCol() != 0)
		{
			thisCurrent = thisCurrent->getRight();
		}

		if (newValue != 0)
		{
			newCurrent = new Node(thisCurrent->getRow(), bCurrent->getCol(), newValue);
			afterMulti.addNode(newCurrent);
		}
	}
	return afterMulti;
}
Matrix Matrix::operator=(Matrix& b)
{
	int Dimension[2]{ b.getRowsize(),b.getColsize() };
	head = new Node(0, 0, -1);
	head->rightLink(head);
	head->downLink(head);

	dimension = new Node(Dimension[0], Dimension[1], -1);
	dimension->rightLink(dimension);
	dimension->downLink(dimension);

	Node* current1 = head;
	Node* current2 = head;

	//�趨ά���Լ������� �����е�ͷָ��ֱ������·�/�ҷ������Լ�
	for (int i = 1; i <= Dimension[1]; )
	{
		current1 = new Node(0, i++, -1);
		current1->downLink(current1);
		current2->rightLink(current1);
		if (i > Dimension[1]) { current1->rightLink(head); }
		else
		{
			current2 = new Node(0, i++, -1);
			current2->downLink(current2);
			current1->rightLink(current2);
		}
	}

	current1 = head;
	current2 = head;

	for (int i = 1; i <= Dimension[0]; )
	{
		current1 = new Node(i++, 0, -1);
		current1->rightLink(current1);
		current2->downLink(current1);
		if (i > Dimension[0]) { current1->downLink(head); }
		else
		{
			current2 = new Node(i++, 0, -1);
			current2->rightLink(current2);
			current1->downLink(current2);
		}
	}

	Node* midCurrent;
	Node* bCurrent = b.getHead();
	for (; bCurrent->getRight()->getCol() != 0;)
	{
		bCurrent = bCurrent->getRight();
		for (; bCurrent->getDown()->getRow() != 0;)
		{
			bCurrent = bCurrent->getDown();
			midCurrent = new Node(bCurrent->getRow(), bCurrent->getCol(), bCurrent->getValue());
			this->addNode(midCurrent);
		}
	}
	return *this;
}
std::ostream& operator<<(std::ostream& os, Matrix& b)
{
	int row = b.getRowsize();
	int col = b.getColsize();

	int** matrix = new int* [row];
	for (int i = 0; i < row; i++)
	{
		matrix[i] = new int[col] {0};	
	}

	Node* current = b.getHead();
	for (; current->getRight()->getCol() != 0;)
	{
		current = current->getRight();
		for (; current->getDown()->getRow() != 0;)
		{
			current = current->getDown();
			matrix[current->getRow()-1][current->getCol()-1] = current->getValue();
		}
		while(current->getRow()!=0)current = current->getDown();
	}
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cout << matrix[i][j] << "  ";
		}
		cout << endl;
	}
	return os;
}