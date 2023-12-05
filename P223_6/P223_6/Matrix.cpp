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

	//设定维度以及第零行 第零列的头指针分别令其连接下一列 下一行
	current1 = new Node(0, 1, -1);
	current2->rightLink(current1);
	for (int i = 2; i <= Dimension[1]; )
	{
		current2 = new Node(0, i++, -1);
		current1->downLink(current2);
		current1->rightLink(current2);
		if (i > Dimension[1])
		{ 
			current2->rightLink(head);
			current2->downLink(head);
		}
		else
		{
			current1 = new Node(0, i++, -1);
			current2->downLink(current1);
			current2->rightLink(current1);
		}
		if (i > Dimension[1])
		{
			current1->rightLink(head);
			current1->downLink(head);
		}
	}

	current1 = head;
	current2 = head;

	current1 = new Node(1, 0, -1);
	current2->downLink(current1);
	for (int i = 2; i <= Dimension[0]; )
	{
		current2 = new Node( i++,0, -1);
		current1->rightLink(current2);
		current1->downLink(current2);
		if (i > Dimension[0]) 
		{ 
			current2->downLink(head); 
			current2->rightLink(head);
		}
		else
		{
			current1 = new Node( i++,0, -1);
			current2->rightLink(current1);
			current2->downLink(current1);
		}
		if (i > Dimension[0])
		{
			current1->rightLink(head);
			current1->downLink(head);
		}
	}
}
void Matrix::addNode(Node* nextNode)                     
{
	Node* upNode = this->head;
	Node* leftNode = this->head;

	//连接上方节点与新加入的节点
	
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
	

	//连接左方节点和新加入的节点

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

	//连接上方节点与新加入的节点
	while (upNode->getCol() != goalNode->getCol())
	{
		upNode = upNode->getRight();
	}
	while (upNode->getRowlink() < goalNode->getRow())
	{
		upNode = upNode->getDown();
	}
	upNode->downLink(goalNode->getDown());

	//连接左方节点和新加入的节点
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

	thisCurrent = thisCurrent->getRight();
	bCurrent = bCurrent->getRight();
	while (thisCurrent != this->getHead() || bCurrent != b.getHead())
	{
		//注意保证每次b和this都在同一列
		if (thisCurrent->getDown()->getCol() == thisCurrent->getCol() && bCurrent->getDown()->getCol() == bCurrent->getCol())
		{
			if (thisCurrent->getDown()->getRow() == bCurrent->getDown()->getRow())
			{
				thisCurrent = thisCurrent->getDown();
				bCurrent = bCurrent->getDown();

				if ((thisCurrent->getValue() + bCurrent->getValue()) != 0)
				{
					newCurrent = new Node(thisCurrent->getRow(), thisCurrent->getCol(), thisCurrent->getValue() + bCurrent->getValue());
					afterAdd.addNode(newCurrent);
				}
			}
			else if (thisCurrent->getDown()->getRow() < bCurrent->getDown()->getRow())
			{
				thisCurrent = thisCurrent->getDown();
				newCurrent = new Node(thisCurrent->getRow(), thisCurrent->getCol() , thisCurrent->getValue());
				afterAdd.addNode(newCurrent);
			}
			else if (thisCurrent->getDown()->getRow() > bCurrent->getDown()->getRow())
			{
				bCurrent = bCurrent->getDown();
				newCurrent = new Node(bCurrent->getRow(), bCurrent->getCol(), bCurrent->getValue());
				afterAdd.addNode(newCurrent);
			}
		}
		else if (thisCurrent->getDown()->getCol() != thisCurrent->getCol() && bCurrent->getDown()->getCol() == bCurrent->getCol())
		{
			while (bCurrent->getDown()->getCol() != thisCurrent->getDown()->getCol())
			{
				bCurrent = bCurrent->getDown();
				newCurrent = new Node(bCurrent->getRow(), bCurrent->getCol(), bCurrent->getValue());
				afterAdd.addNode(newCurrent);
			}
		}
		else if (thisCurrent->getDown()->getCol() == thisCurrent->getCol() && bCurrent->getDown()->getCol() != bCurrent->getCol())
		{
			while (bCurrent->getDown()->getCol() != thisCurrent->getDown()->getCol())
			{
				thisCurrent = thisCurrent->getDown();
				newCurrent = new Node(thisCurrent->getRow(), thisCurrent->getCol(), thisCurrent->getValue());
				afterAdd.addNode(newCurrent);
			}
		}
		else if (thisCurrent->getDown()->getCol() != thisCurrent->getCol() && bCurrent->getDown()->getCol() != bCurrent->getCol())
		{
			thisCurrent = thisCurrent->getDown();
			bCurrent = bCurrent->getDown();
		}
	}

	return afterAdd;
/*
	while (bCurrent->getRight()->getCol() != 0&&thisCurrent->getRight()->getCol()!=0)//从行头指针开始 依次向下遍历，每次回到头指针时向右移动一位
	{
		

		thisCurrent = thisCurrent->getRight();
		bCurrent = bCurrent->getRight();

		while (bCurrent->getDown()->getRow() != 0||thisCurrent->getDown()->getRow()!=0)
		{
			if (bCurrent->getDown()->getRow() != 0&&thisCurrent->getDown()->getRow()!=0)
			{
				if (bCurrent->getDown()->getRow() == thisCurrent->getDown()->getRow())
				{
					bCurrent = bCurrent->getDown();
					thisCurrent = thisCurrent->getDown();
					if ((bCurrent->getValue() + thisCurrent->getValue())!=0)
					{
						newCurrent = new Node(bCurrent->getRow(), bCurrent->getCol(), bCurrent->getValue() + thisCurrent->getValue());
						afterAdd.addNode(newCurrent);
					}
				}
				else if (bCurrent->getDown()->getRow() > thisCurrent->getDown()->getRow())
				{
					thisCurrent = thisCurrent->getDown();
					newCurrent = new Node(thisCurrent->getRow(), thisCurrent->getCol(), thisCurrent->getValue());
					afterAdd.addNode(newCurrent);
				}
				else if (bCurrent->getDown()->getRow() < thisCurrent->getDown()->getRow())
				{
					bCurrent = bCurrent->getDown();
					newCurrent = new Node(bCurrent->getRow(), bCurrent->getCol(), bCurrent->getValue());
					afterAdd.addNode(newCurrent);
				}
			}
			else if (bCurrent->getDown()->getRow() == 0 && thisCurrent->getDown()->getRow() != 0)
			{
				thisCurrent = thisCurrent->getDown();
				newCurrent = new Node(thisCurrent->getRow(), thisCurrent->getCol(), thisCurrent->getValue());
				afterAdd.addNode(newCurrent);
			}
			else if (bCurrent->getDown()->getRow() != 0 && thisCurrent->getDown()->getRow() == 0)
			{
				bCurrent = bCurrent->getDown();
				newCurrent = new Node(bCurrent->getRow(), bCurrent->getCol(), bCurrent->getValue());
				afterAdd.addNode(newCurrent);
			}
			
		}

		//使其重回类头指针（列首）
		while (bCurrent->getRow() != 0)
		{
			bCurrent = bCurrent->getDown();
		}
		while (thisCurrent->getRow() != 0)
		{
			thisCurrent = thisCurrent->getDown();
		}

	}
*/
}
Matrix Matrix::operator*(Matrix& b)
{
	int newDimension[2]{ getRowsize(),b.getColsize() };
	Matrix afterMulti(newDimension);
	
	Node* thisCurrent = head;
	Node* bCurrent = b.getHead();
	Node* newCurrent;

	thisCurrent = thisCurrent->getDown();
	bCurrent = bCurrent->getRight();
	for (; thisCurrent != this->getHead() && bCurrent != b.getHead();)
	{
		int value = 0;
		if (thisCurrent->getRow() == bCurrent->getCol())
		{
			while(true)
			{
				if (thisCurrent->getRight()->getRow() == thisCurrent->getRow() && bCurrent->getDown()->getCol() == bCurrent->getCol())
				{
					if (thisCurrent->getRight()->getCol() == bCurrent->getDown()->getRow())
					{
						thisCurrent = thisCurrent->getRight();
						bCurrent = bCurrent->getDown();
						value += (thisCurrent->getValue() * bCurrent->getValue());
					}
					else if (thisCurrent->getRight()->getCol() > bCurrent->getDown()->getRow())bCurrent = bCurrent->getDown();
					else if (thisCurrent->getRight()->getCol() < bCurrent->getDown()->getRow())thisCurrent = thisCurrent->getRight();
				}
				else if (thisCurrent->getRight()->getRow() != thisCurrent->getRow() && bCurrent->getDown()->getCol() == bCurrent->getCol())
				{
					if (value != 0)
					{
						newCurrent = new Node(thisCurrent->getRow(), bCurrent->getCol(), value);
						afterMulti.addNode(newCurrent);
					}
					thisCurrent = thisCurrent->getRight();
					bCurrent = b.getHead();
					for (; bCurrent->getCol() != thisCurrent->getRow(); bCurrent = bCurrent->getRight());
					break;
				}
				else if (thisCurrent->getRight()->getRow() == thisCurrent->getRow() && bCurrent->getDown()->getCol() != bCurrent->getCol())
				{
					if (value != 0)
					{
						newCurrent = new Node(thisCurrent->getRow(), bCurrent->getCol(), value);
						afterMulti.addNode(newCurrent);
					}
					bCurrent = bCurrent->getDown();
					thisCurrent = this->getHead();
					for (; bCurrent->getCol() != thisCurrent->getRow(); thisCurrent = thisCurrent->getDown());
					break;
				}
				else if (thisCurrent->getRight()->getRow() != thisCurrent->getRow() && bCurrent->getDown()->getCol() != bCurrent->getCol())
				{
					if (value != 0)
					{
						newCurrent = new Node(thisCurrent->getRow(), bCurrent->getCol(), value);
						afterMulti.addNode(newCurrent);
					}
					bCurrent = bCurrent->getDown();
					thisCurrent = thisCurrent->getRight();
					break;
				}
			} 

		}
	}
	/*
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

		//使各节点重回类头节点位置
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
	*/
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

	//设定维度以及第零行 第零列的头指针分别令其下方/右方连接自己
	current1 = new Node(0, 1, -1);
	current2->rightLink(current1);
	for (int i = 2; i <= Dimension[1]; )
	{
		current2 = new Node(0, i++, -1);
		current1->downLink(current2);
		current1->rightLink(current2);
		if (i > Dimension[1]) { current2->rightLink(head); }
		else
		{
			current1 = new Node(0, i++, -1);
			current2->downLink(current1);
			current2->rightLink(current1);
		}
	}

	current1 = head;
	current2 = head;

	current1 = new Node(1, 0, -1);
	current2->downLink(current1);
	for (int i = 2; i <= Dimension[0]; )
	{
		current2 = new Node(i++, 0, -1);
		current1->rightLink(current2);
		current1->downLink(current2);
		if (i > Dimension[0]) { current2->downLink(head); }
		else
		{
			current1 = new Node(i++, 0, -1);
			current2->rightLink(current1);
			current2->downLink(current1);
		}
	}

	Node* midCurrent;
	Node* bCurrent = b.getHead()->getRight();
	for (; bCurrent!=b.getHead();)
	{
		if (bCurrent->getRow() != 0)
		{
			midCurrent = new Node(bCurrent->getRow(), bCurrent->getCol(), bCurrent->getValue());
			this->addNode(midCurrent);
		}
		bCurrent->getDown();
		
		/*
		for (; bCurrent->getDown()->getRow() != 0;)
		{
			bCurrent = bCurrent->getDown();
			midCurrent = new Node(bCurrent->getRow(), bCurrent->getCol(), bCurrent->getValue());
			this->addNode(midCurrent);
		}
		*/
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
	current = current->getRight();
	for (; current != b.getHead();)
	{
		if (current->getCol() != 0 && current->getRow() != 0)
		{
			matrix[current->getRow() - 1][current->getCol() - 1] = current->getValue();
		}
		current = current->getDown();
	}
	/*
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
	*/
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