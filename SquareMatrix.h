#ifndef SQUAREMATRIX_H 
#define SQUAREMATRIXL_H 

#include <stdlib.h> //for size_t
#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class SquareMatrix
{
public:
	SquareMatrix();//default constructor  
	~SquareMatrix();//destructor
	SquareMatrix(int size);//perimeter constructor 
	SquareMatrix(const SquareMatrix & sqr);//copy constructor
	SquareMatrix(SquareMatrix && sqr);//move constructor
	SquareMatrix& operator=(const SquareMatrix & s);//copy assignment
	SquareMatrix& operator=(SquareMatrix && s);//move assignment
	bool operator==(const SquareMatrix & s);//equity operator
	SquareMatrix<T> operator+(const SquareMatrix & s);//addition Operator
	void resize(size_t new_size);//allocates new memory after it destroys all previous content of the matrix and releases all memory
	int size() const;//returns the current size of the matrix
	void print_matrix();//to print the element in the matrix
	T** allocate(size_t size);//allocate space which is needed for the square matrix object
	void deallocate();//to release memory. Deallocates all the space used by a matrix object.
	T& at(int row, int column);// returns a reference to the element in the given row and column
	void fill(size_t element);//fills the matrix with elements


private:
	T** matrix;//pointer to an array of pointers. It will store an array of pointers of type t.
	size_t size_value;//it stores the size of the matrix. Square matrix of 3x3 will return 3

};
#endif

//default constructor that will build a two dimensional array with 0,0 dimension
//Called when no arguments are passed

//sets all the private variable side length to 0 and the pointer matrix to the nullptr
template<typename T>
SquareMatrix<T>::SquareMatrix() :matrix(nullptr), size_value(0)
{

	
	//allocate(10);
	//print_matrix();
	//cout<<"Default constructor"<<endl;
}


//perimeter constructor that will build a two dimensional array with equal row & coloumn dimension
//it is called when arguments are passed
//here private variable size_value is intialzied to the size that is passed into the argument
template<typename T>
SquareMatrix<T>::SquareMatrix(int size) :size_value(size)
{
	//here allocate function is called so that it can make space for the matrix of a particular size which is passed as an argument
	allocate(size);

	//iterates through the square matrix and initializes its elements to 0
	for (int row = 0; row < size_value; row++)
	{
		for (int col = 0; col < size_value; col++)
		{
			matrix[row][col] = 0;
		}
	}
}


//destructor is responsible for releasing all the memory occupied by the object
//called when the object gets destroyed or goes out of scope
template<typename T>
SquareMatrix<T>::~SquareMatrix()
{
	//here we just call the deallocate function which releases all the memory that was occupied by the object
	deallocate();
	//cout<<"Destructor"<<endl;
}

//This function make space for the matrix of a particular size which is passed as an argument
template<typename T>
T** SquareMatrix<T>::allocate(size_t size)
{
	//T** matrix is a pointer to a pointer. It will store an array of pointer of type t.
	// rows and columns are created for the matrix. The rows is an array of pointers.
	//The row will contain pointers which will point towards their own arrays (columns).
	//T **matrix = 0;
	
	//private variable is set to the size of the object that is being passed
	//new matrix is being created with the size of the object that has been passed
	size_value = size;
	matrix = new T*[size];

	//using the for loop, the columns are created for each row
	for (int row = 0; row < size; row++)
	{
		//for each pointer, a new array of T type columns are created       
		matrix[row] = new T[size];
	}

    
	//iterates and sets all the elements to 0 in the matrix
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			matrix[i][j] = 0;
		}
	}
    

	//will return the allocated matrix
	return matrix;
}

//This function simply destroys previous content of a matrix and releases them
//Deallocates all the space used by a matrix object.
template<typename T>
void SquareMatrix<T>::deallocate()
{
	//to delete the elements that are stored in the matrix
	//iterate throgh the array of pointers (row) which are pointing towards their own respective array (for columns) and delete it

	//so only if the matrix is not equal to the nullptr then delete
	if (this->matrix != nullptr)
	{
		for (int row = 0; row < size_value; row++)
		{
			delete[] matrix[row];
		}

		//delete the original pointer at the matrix
		delete[] matrix;
        
		//set the matrix to nullptr
		matrix=nullptr;
	}


}

//This function prints all the elments in a matrix
template<typename T>
void SquareMatrix<T>::print_matrix()
{
	//iterate through the matrix and print out the elments in the matrix
	for (int row = 0; row < size_value; row++)
	{
		for (int col = 0; col < size_value; col++)
		{
			cout << matrix[row][col] << " ";
		}

		cout << endl;
	}
}



//Copy constructor is required to construct a new object
//It is invoked if the existing object is lvalue
//It is intialized to the same state as another object of the same type
//It is implemented by applying copy constructor to each data member
template<typename T>
SquareMatrix<T>::SquareMatrix(const SquareMatrix<T> & sqr) :matrix(sqr.matrix), size_value(sqr.size_value)
{
	//in the initializers list all the object's (the one that is being passed) attribute is copied
	
	//if the object in the parameter is empty then return because there is nothing to be copied
	if (sqr.matrix == nullptr)
	{
		return;
	}

	//create a new square matrix
	matrix = new T*[sqr.size_value];
	for (int row = 0; row < size_value; row++)
	{
		matrix[row] = new T[size_value];
	}

	//iterate through the matrix 
	//copy data from the object passed in the parameter to the matrix
	for (int row = 0; row < size_value; row++)
	{
		for (int col = 0; col < size_value; col++)
		{
			matrix[row][col] = sqr.matrix[row][col];
		}
	}
}


//Move constructor are required to construct a new object
//It is invoked if the existing object is rvalue
//It is intialized to the same state as another object of the same type

//Moving our matrix pointer and making it point towards the sqr object (the same block of memory) that is passed as the parameter
template<typename T>
SquareMatrix<T>::SquareMatrix(SquareMatrix<T> && sqr) :matrix(sqr.matrix), size_value(sqr.size_value)
{
	//after the matrix pointer has been moved and pointing towards the sqr object
	//sqr object is of no use
	//then sqr attributes are set to nullptr and 0 
	sqr.matrix = nullptr;
	sqr.size_value = 0;

}

//copy assignment
//The assignment operator is called when = is applied to two objects that have both been previously constructed.
//lhs=rhs is intended to copy the state of rhs into lhs.
// If rhs is an lvalue, this is done by using the copy assignment operator 
template<typename T>
SquareMatrix<T>& SquareMatrix<T>::operator=(const SquareMatrix<T> & s)
{
	//if the matrix is identical to the matrix that has been passeed
	//it is returned because there is no need for anything to be copied
	if(this==&s)
	{
		return *this;
	}
	
    //if the matrix is not equal to nullptr
	//we need to release those memory by calling the deallocate function 
	if (matrix != nullptr)
	{
		deallocate();
		//cout << "1" << endl;
	}
    
	//assigning the private variable size_value to the object's size_value
	size_value = s.size_value;
    
	//creating a matrix of a specific size
	matrix = new T*[size_value];
	for (int row = 0; row < size_value; row++)
	{
		//cout << "2" << endl;
		matrix[row] = new T[size_value];
	}


    //using a for loop we go through all the rows and columns of the s matrix and copy the elements/value from s.matrix to the matrix's row and col
	for (int row = 0; row < size_value; row++)
	{
		//cout << "3" << endl;
		for (int col = 0; col < size_value; col++)
		{
			matrix[row][col] = s.matrix[row][col];
		}
	}

    //it returns the square matrix object
	return *this;

}

//move assignment
//The assignment operator is called when = is applied to two objects that have both been previously constructed.
//lhs=rhs is intended to copy the state of rhs into lhs.
// If rhs is an rvalue, this is done by using the move assignment operator
template<typename T>
SquareMatrix<T>& SquareMatrix<T>::operator=(SquareMatrix<T> && s)
{
	//if the matrix is identical to the matrix that has been passeed
	//then it is returned
	if (this == &s)
	{
		return *this;
	}

	//if the matrix is not equal to nullptr
	//we need to release those memory by calling the deallocate function 
	if (matrix != nullptr)
	{
		deallocate();
	}
    
	//assiging the private varibles to the attributes of the s object that is passed
	size_value = s.size_value;
	matrix=s.matrix;
    
	//after the move, we set the attributes of the s object to nullptr and 0
	s.matrix = nullptr;
	s.size_value = 0;

	//it returns the square matrix object
	return *this;
}


//This function destroys all previous content of the matrix and releases all memory.
//Then it allocates new memory. New elements are not specified (can have any value)
template<typename T>
void SquareMatrix<T>::resize(size_t new_size)
{
	//if matrix still has memory, those should be released
	if (matrix != nullptr)
	{
		//to delete the elements that are stored in the matrix
		//iterate throgh the array of pointers (row) which are pointing towards their own respective array (for coloumn) and delete it
		for (int row = 0; row < size_value; row++)
		{
			delete[] matrix[row];
		}

		//delete the original pointer at the matrix
		delete[] matrix;

		//set it to nullptr
		matrix = nullptr;

	}

	//we have to allocate new memory now 
	
	//T** matrix is a pointer to a pointer. It will store an array of pointer of type t.
	//creating rows for the matrix. The rows contain pointer which will point towards other arrays.
	
	//assigning the private variables size value to the size that has been passed
	size_value = new_size;
	matrix = new T*[new_size];

	//using the for loop, the coloumns are created for each row
	for (int row = 0; row < new_size; row++)
	{
		//for each pointer, a new array of T type coloumns are created       
		matrix[row] = new T[new_size];
	}
    
	//iterates through matrix and set its elements to 0
	for (int i = 0; i < new_size; i++)
	{
		for (int j = 0; j < new_size; j++)
		{
			matrix[i][j] = 0;
		}
	}

}

//This functions fills the matrix with a specfic elements in all its row and columns
template<typename T>
void SquareMatrix<T>::fill(size_t element)
{
	//iterate through the row and columns of the matrix and set its element to the element that is being passed
	for (int row = 0; row < size_value; row++)
	{
		for (int col = 0; col < size_value; col++)
		{
			matrix[row][col] = element;
		}
	}
}

//returns the current size of the matrix.
template<typename T>
int SquareMatrix<T>::size() const
{
	//returns the private variable
	return size_value;
}


//The equity operator compare and checks if object that is passed is equal (interms of size and elements inside it) to another object
template<typename T>
bool SquareMatrix<T>::operator== (const SquareMatrix & s)
{
	//if the size of the matrice is not equal, then return false
	if (size_value != s.size_value)
	{
		return false;
	}

	//iterate through two matrices and check whether all the elements in both matrices are equal
	//if the elements of the two matrices are not equal, then return false
	for (int row = 0; row < size_value; row++)
	{
		for (int col = 0; col < size_value; col++)
		{
			if (matrix[row][col] != s.matrix[row][col])
			{
				return false;
			}

		}
	}
    
	//returns true if the size and elements of the two square matrix object are equal
	return true;
}

//The Addition operator adds two square matrix object and returns a resulting square matrix object
template<typename T>
SquareMatrix<T> SquareMatrix<T>::operator+(const SquareMatrix & s)
{

	//creating a square matrix object
	SquareMatrix<T> objTemp;

	//assiging the obj size value to size_value
	objTemp.size_value = size_value;
	
	//creating a new matrix
	objTemp.matrix = new T*[s.size_value];

	//using the for loop, the coloumns are created for each row
	for (int row = 0; row < size_value; row++)
	{
		//for each pointer, a new array of T type coloumns are created       
		objTemp.matrix[row] = new T[size_value];
	}

	//assigns the added elemnts of the two square matrix to the new matrix obj
	for (int row = 0; row < size_value; row++)
	{
		for (int col = 0; col < size_value; col++)
		{
			objTemp.matrix[row][col] = matrix[row][col] + s.matrix[row][col];
		}
	}

    //returns the result of the addition of two square matrix object
	return objTemp;

}

//This function returns a reference to the element in the given row and column that is passed
//This function can also be used to modify matrix content

template<typename T>
T& SquareMatrix<T>::at(int row, int column)
{
	//if row and column is less than size_value and row and coloumn are greater than and equal to 0
	//then return the reference to the elemnt
	if (row < size_value && column < size_value && row >= 0 && column >= 0)
	{
		return matrix[row][column];
	}
	else
	{
		//or else throw the std::out of range exception
		throw std::out_of_range("Out of Bound");
	}
}