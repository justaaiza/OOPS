# include <iostream>
# include <fstream>

using namespace std;

int** InputMatrix(ifstream& fin, int& row, int& col)
{
	fin >> row;

	if (row <= 0)
	{
		return NULL;
	}
	
	fin >> col;

	if (col <= 0)
	{
		return NULL;
	}

	int** matrix = new int* [row];
	for (int** iptr = matrix; iptr < matrix+row; iptr++)
		*iptr = new int[col];

	for (int** iPtr = matrix; iPtr < matrix + row; iPtr++)
	{
		for (int* jPtr = *iPtr; jPtr < *iPtr + col; jPtr++)
		{
			fin >> *jPtr;
		}
	}

	return matrix;

}

void DeleteMatrix(int** matrix, const int& row)
{
	for (int i = 0; i < row; i++)
		delete[] matrix[i];
	delete[] matrix;
}

void OutputMatrix(int** matrix, const int& row, const int& col)
{
	for (int** iptr = matrix; iptr < matrix + row; iptr++)
	{
		for (int* jptr = *iptr; jptr < *iptr + col; jptr++)
		{
			cout << *jptr << "\t";
		}
		cout <<"\n\n";
	}
}

int** AddMatrix(int** matrixA, int** matrixB, const int& row, const int& col)
{
	int** matrixR = new int* [row];
	for (int** iptr = matrixR; iptr < matrixR + row; iptr++)
		*iptr = new int[col];

	int** ptrA = matrixA;
	int** ptrB = matrixB;
	
	int count;

	for (int** iptr = matrixR; iptr < matrixR + row; iptr++)
	{
		count = 0;

		for (int* jptr = *iptr; jptr < *iptr + col; jptr++)
		{
			*jptr = *(*(ptrA)+count)+ *(*(ptrB)+count);
			count++;
		}
		ptrA++;
		ptrB++;
	}

	return matrixR;
}

bool AddMatrix(int** matrixA, int** matrixB, const int& rowA, const int& colA, const int& rowB, const int& colB)
{
	if (rowA == rowB && colA == colB)
		return true;
	else
		return false;
		
}

int** TransposeMatrix(int** matrix, const int& row, const int& col)
{
	int** matrixT = new int* [col];
	for (int** iptr = matrixT; iptr < matrixT + col; iptr++)
		*iptr = new int[row];

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			(*(*(matrixT+j)+i)) = (*(*(matrix + i) + j));
		}
	}

	return matrixT;
}

bool isSymmetric(int** matrix, const int& row, const int& col)
{
	if (row == col) 
	{
		int** transpose = TransposeMatrix(matrix, row, col);

		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				if (*(*(transpose + i) + j) != *(*(matrix + i) + j))
				{
					DeleteMatrix(transpose, col);
					return false;
				}
					
			}
		}

		DeleteMatrix(transpose, col);
		return true;
	}
	else
	{
		cout << "\nThe matrix is not a square matrix! \nThus;";
		return false;
	}
}

void InterchangeRows(int*& row1, int*& row2)
{
	int* temp = row1;
	row1 = row2;
	row2 = temp;
}

void InterchangeRows(int** matrix, const int& row, const int& col)
{
	int row1 = 1, row2 = 3;

	if (row1 <= row && row2 <= row)
	{
		cout << "\nInterchanging the rows:" << endl;
		cout << "row1:1\nrow2:3" << endl;
		InterchangeRows(*(matrix + (row1-1)), *(matrix + (row2-1)));
	}
}



int main()
{
	int** matrixA = 0;
	int** matrixB = 0;
	int** matrixC = 0;

	int rowA = 0, colA=0;
	int rowB = 0, colB=0;
	int rowC = 0, colC=0;

	ifstream finput("Input.txt");

	if (!finput.is_open())
	{
		cout << "ERROR! File cannot open!" << endl;
		return 0;
	}

	matrixA = InputMatrix(finput, rowA, colA);
	if (rowA == 0 || colA == 0)
	{
		cout << "Invalid size input!" << endl;
		system("pause");
		return 0;
	}
	matrixB = InputMatrix(finput, rowB, colB);
	if (rowB == 0 || colB == 0)
	{
		cout << "Invalid size input!" << endl;
		system("pause");
		return 0;
	}
	matrixC = InputMatrix(finput, rowC, colC);
	if (rowC == 0 || colC == 0)
	{
		cout << "Invalid size input!" << endl;
		system("pause");
		return 0;
	}

	finput.close();

	cout << "\nMatrix A:" << endl;
	OutputMatrix(matrixA, rowA, colA);
	cout << "\nMatrix B:" << endl;
	OutputMatrix(matrixB, rowB, colB);
	cout << "\nMatrix C:" << endl;
	OutputMatrix(matrixC, rowC, colC);

	bool addition = false;

	addition = AddMatrix(matrixA, matrixB, rowA, colA, rowB, colB);
	
	if (addition) {
		int** matrixAB = 0;
		matrixAB = AddMatrix(matrixA, matrixB, rowA, colA);
		cout << "\nSum of matrix A and B is:" << endl;
		OutputMatrix(matrixAB, rowA, colA);
		DeleteMatrix(matrixAB, rowA);
	}
	else
		cout << "\nAddition of A and B is not possible!" << endl;
	

	addition = AddMatrix(matrixA, matrixC, rowA, colA, rowC, colC);
	
	if (addition) {
		int** matrixAC = 0;
		matrixAC = AddMatrix(matrixA, matrixC, rowA, colA);
		cout << "\nSum of matrix A and C is:" << endl;
		OutputMatrix(matrixAC, rowA, colA);
		DeleteMatrix(matrixAC, rowA);
	}
	else
		cout << "\nAddition of A and C is not possible!" << endl;
	
	int** transposeA = 0;

	transposeA = TransposeMatrix(matrixA, rowA, colA);
	cout << "\nTranspose of matrix A is:" << endl;
	OutputMatrix(transposeA, colA, rowA);
	DeleteMatrix(transposeA, colA);

	int** transposeC = 0;

	transposeC = TransposeMatrix(matrixC, rowC, colC);
	cout << "\nTranspose of matrix C is:" << endl;
	OutputMatrix(transposeC, colC, rowC);
	DeleteMatrix(transposeC, colC);

	bool matrixAcheck=false, matrixBcheck=false, matrixCcheck=false;

	matrixAcheck = isSymmetric(matrixA, rowA, colA);
	if (matrixAcheck)
		cout << "\nMatrix A is symmetric!" << endl;
	else
		cout << "\nMatrix A is NOT symmetric!" << endl;

	matrixBcheck = isSymmetric(matrixB, rowB, colB);
	if (matrixBcheck)
		cout << "\nMatrix B is symmetric!" << endl;
	else
		cout << "\nMatrix B is NOT symmetric!" << endl;

	matrixCcheck = isSymmetric(matrixC, rowC, colC);
	if (matrixCcheck)
		cout << "\nMatrix C is symmetric!" << endl;
	else
		cout << "\nMatrix C is NOT symmetric!" << endl;

	InterchangeRows(matrixA, rowA, colA);
	cout << "\nMatrix A after interchanging rows:" << endl;
	OutputMatrix(matrixA, rowA, colA);

	DeleteMatrix(matrixA, rowA);
	DeleteMatrix(matrixB, rowB);
	DeleteMatrix(matrixC, rowC);

	system("pause");
	return 0;
}