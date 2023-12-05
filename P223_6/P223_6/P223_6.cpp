#include"Matrix.h"
int main()
{
	int dimension[2]{ 3,3 };

	Node node11(1, 1, 3);
	Node node221(2, 2, 2);
	Node node33(3, 3, 1);
	
	Node node13(1, 3, 3);
	Node node222(2, 2, 2);
	Node node31(3, 1, 1);

	Matrix matrix1(dimension);
	Matrix matrix2(dimension);
	
	matrix1.addNode(&node11);
	matrix1.addNode(&node221);
	matrix1.addNode(&node33);
	cout << matrix1<<endl;

	matrix2.addNode(&node13);
	matrix2.addNode(&node222);
	matrix2.addNode(&node31);
	cout << matrix2<<endl;

	Matrix matrix3 = matrix1+matrix2;
	Matrix matrix4 = matrix1 * matrix2;
	cout << matrix3;
	cout << endl;
	cout << matrix4;

}