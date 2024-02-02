#include<iostream>
#include<fstream>
using namespace std;

void outputArray(int* array, const int& size)
{
	int* endPtr = array + size;

	for (int* iPtr = array; iPtr < endPtr; iPtr++)
	{
		cout << *iPtr << " ";
	}
}

int* readmefile(ifstream& finput, int* array, int& size)
{
	
		finput >> size;

		if (size <= 0)
		{
			return NULL;
		}

		array = new int[size];

		int* endPtr = array + size;

		//loop for taking input from file into array

		for (int* iPtr = array; iPtr < endPtr; iPtr++)
		{
			finput >> *iPtr;
		}

		return array;

}

void Sorting(int* array, const int& size)
{
	//selection sort

	int* endPtr = array + size;

	for (int* iPtr = array; iPtr < endPtr - 1; iPtr++)
	{
		for (int* jPtr = iPtr + 1; jPtr < endPtr; jPtr++)
		{
			if (*iPtr > *jPtr)
			{
				int temp = *iPtr;
				*iPtr = *jPtr;
				*jPtr = temp;
			}
		}
	}
		
}

int* DistinctElements(int* arr1, int& size, int* arr2)
{
	
		for (int* iPtr = arr1; iPtr < arr1+size; iPtr++)
		{
			if (*iPtr == *(iPtr+1))
			{
				
				while (*iPtr == *(iPtr + 1))
				{
					for (int* jPtr = iPtr+1; jPtr < arr1+size; jPtr++)
					{
						*jPtr = *(jPtr + 1);

					}
					
					size--;
				}
				
			}
		}
	
		arr2 = new int[size];

		int* endPtr = arr2 + size;

		int* temp = arr1;

		for (int* kPtr = arr2; kPtr < endPtr; kPtr++)
		{
			*kPtr = *temp;
			temp++;
		}
	
		return arr2;
}

int* UnionArray(int* arr1, const int& size1, int* arr2, const int& size2, int* arr3, int& size3)
{
	int* endPtr1 = arr1 + size1;
	int* endPtr2 = arr2 + size2;

	int count = size2;   //to find the new size of array 2

	for (int* iPtr = arr1; iPtr < endPtr1; iPtr++)
	{
		for (int* jPtr = arr2; jPtr < endPtr2; jPtr++)
		{
			if (*iPtr == *jPtr)
			{
				*jPtr = 0;
				count--;
			}
		}
	}

	//cpoying elements from both arrays to a new array with exception of zeros

	size3 = size1 + count;

	arr3 = new int[size3];

	int* endPtr3 = arr3 + size3;

	int* temp = arr3;

	for (int* iPtr = arr1; iPtr < endPtr1; iPtr++)
	{
		*temp = *iPtr;
		temp++;
	}

	for (int* iPtr = arr2; iPtr < endPtr2; iPtr++)
	{
		if (*iPtr != 0)
		{
			*temp = *iPtr;
			temp++;
		}
	}

	//sorting the array

	Sorting(arr3, size3);

	return arr3;
}

int main()
{

	ifstream finput("Data1.txt");

	if (!finput.is_open())
	{
		cout << "ERROR! File cannot open!" << endl;
		return 0;
	}

	int size1=0, size2=0, finalSize=0;

	int* myarray1=0;
	int* myarray2=0;

	myarray1 = readmefile(finput, myarray1, size1);

	if (myarray1 == NULL)
	{
		cout << "\n\nERROR! Invalid input size!" << endl;
		return 0;
	}

	cout << "\nSize of array 1 is:\t" << size1 << endl;
	cout << "Data:" << endl;

	outputArray(myarray1, size1);

	myarray2 = readmefile(finput, myarray2, size2);

	if (myarray2 == NULL)
	{
		cout << "\n\nERROR! Invalid input size!" << endl;
		return 0;
	}

	cout << "\n\nSize of array 2 is:\t" << size2 << endl;
	cout << "Data:" << endl;

	outputArray(myarray2, size2);

	finput.close();

	cout << "\n\nSorted array 1 is:" << endl;
	Sorting(myarray1, size1);
	outputArray(myarray1, size1);

	cout << "\n\nSorted array 2 is:" << endl;
	Sorting(myarray2, size2);
	outputArray(myarray2, size2);

	int* distinctArr1 = 0;
	int* distinctArr2 = 0;

	cout << "\n\nDistinct elements of array 1 are:" << endl;
	distinctArr1 = DistinctElements(myarray1, size1, distinctArr1);
	outputArray(myarray1, size1);

	cout << "\n\nDistinct elements of array 2 are:" << endl;
	distinctArr2 = DistinctElements(myarray2, size2, distinctArr2);
	outputArray(myarray2, size2);

	delete[] myarray1;
	delete[] myarray2;

	int* unionArr = 0;

	cout << "\n\nUnion of arrays is:" << endl;
	unionArr=UnionArray(distinctArr1, size1, distinctArr2, size2, unionArr, finalSize);
	outputArray(unionArr, finalSize);

	delete[] distinctArr1;
	delete[] distinctArr2;
	delete[] unionArr;

	cout <<"\n\n";

    
	return 0;
}