#include<vector>
#include<stdio.h>
#include<iostream>
#include <stdexcept>
#include <initializer_list>
template <typename T> class Matrix
{
public:
Matrix(size_t rows,size_t col);
Matrix(const Matrix &source);
Matrix<T> operator = (const Matrix &source);
Matrix(std::initializer_list< std::initializer_list< T>> matrixList);
~Matrix();
T  operator ()(size_t row, size_t column);
void  operator()(size_t row, size_t col, T value);
Matrix<T> operator * ( Matrix rHsMatrix);
void printMatrix();
private:
size_t _rows, _cols;
T** _matrix;
};

// constructor with rows and colums
template<typename T> Matrix<T>::Matrix(const size_t rows,const size_t cols)
{
_rows= rows;
_cols = cols;
_matrix = new T*[_rows];
std::cout << "Creating " << _cols << " X " << _rows<<" Matrix"<<  std::endl;
for (size_t t= 0; t <_rows; t++)
{
	std::cout<<"Heap memory allocated for row number:"<<t << " at memory address: " << &_matrix[t]<<std::endl;
         
}   
for (size_t t= 0; t <_rows; t++)
{
	_matrix[t] = new T[_cols];
}	

}
template<typename T> Matrix<T>::Matrix(std::initializer_list< std::initializer_list< T>> matrixList )
{
try{
_rows= matrixList.begin()->size();
_cols	= matrixList.size();
_matrix = new T*[_rows];
std::cout << "Creating " << _cols << " X " << _rows <<" Matrix"<<  std::endl;
for (size_t t= 0; t <_rows; t++)
{
       std::cout<<"Heap memory allocated for row number:"<<t << " at memory address: " << &_matrix[t]<<std::endl;

}
for (size_t t= 0; t <_rows; t++)
{        _matrix[t] = new T[_cols];
}

int cIt = 0;
for (std::initializer_list<T> row : matrixList)
{
int rIt = 0;

if( row.size()!= _rows) throw std::invalid_argument( "matrix not correctly populated \n" );
for (T col: row)
{
std::cout<< "rIt: " << rIt<< " cIt " << cIt << std::endl;
_matrix[rIt][cIt]= col;
std::cout<<"__"<< std::endl;
rIt= rIt +1 ;
}
cIt = cIt +1;
}

}
catch(const std::exception& e) {
    std::cout  << e.what();
}
}
// destructor
template<typename T> Matrix<T>::~Matrix()
{
	if(_rows > 0)
	{
	for (size_t t; t < _rows; t++)
	{
		delete [] _matrix[t];	
	}
	}
	if (_cols > 0)
	{
	delete [] _matrix;
	}
	std::cout<<"Heap memory deallocated"<<std::endl;

}
//copy constructor
template <typename T>  Matrix<T>::Matrix(const Matrix &source)
{
	_cols = source._cols;
	_rows = source._rows;
	_matrix = new T*[_rows];
	for (size_t t = 0; t < _rows; t++)
	{
		_matrix[t] = new T[_cols];
	}	
	for ( size_t i =0 ; i < _rows; i++)
	{
	for (size_t j = 0; j < _cols; j++)
		{
			_matrix[i][j] = source._matrix[i][j];
			std::cout<< "copying elements ...." << std::endl;
		}
	}
}
//copy assignment operator
template<typename T> Matrix<T> Matrix<T>::operator = (const Matrix &source)
{
std::cout << "copy assingment operator invoked" << std::endl;
//free memory from previously allocated obejct his
for(int i = 0; i< _rows; i++)
{
	delete [] _matrix[i];
}
delete[] _matrix;

if (this  == &source){ return *this;}
_rows = source._rows;
_cols = source._cols;
_matrix = new T*[_rows];
for (int t =0; t< _rows; t++)
{
_matrix[t] = new T[_cols];
}
for (size_t t= 0; t <_rows; t++)
{
        std::cout<<"Heap memory allocated for row number:"<<t << " at memory address: " << &_matrix[t]<<std::endl;
}

for (int i = 0; i< _rows; i++)
{
	for (int j = 0; j < _cols; j++)
	{
	_matrix[i][j] = source._matrix[i][j];
	std::cout<< "copy elements in copy assingment operator" << std::endl;
	}
}
return *this;
}

template <typename T> T  Matrix<T>::operator()(size_t row, size_t col)
{
try
{	
if (row > _rows && col > _cols){
	throw std::out_of_range("Bad Matrix Access");
}
}
catch(const std::exception& e)
{
      std::cout  << e.what();
}
return _matrix[row][col];
}
template <typename T> void  Matrix<T>::operator()( size_t row,size_t  col, T value)
{
try{	
if(row > _rows || col > _cols){
	throw std::out_of_range("Bad Matrix Access");
}	
_matrix[row][col] = value;
}
catch(...){std::cout<<"ERROR"<< std::endl; }
}
template <typename T> void Matrix<T>::printMatrix()
{
std::cout<< std::endl;
for (int i= 0; i<_cols; i++)
{   
        for (int j=0; j<_rows; j++)
        {
	      std:: cout << _matrix[j][i];
	      std::cout << "  " ;
        }
	std::cout<< std::endl;
}
std::cout<< std::endl;
}
template <typename T> Matrix<T> Matrix<T>::operator * ( Matrix	rHsMatrix)
{
try
{
std::cout<<"Multiplying "<< this->_cols << " X " << this->_rows << " with " << rHsMatrix._cols << " X " << rHsMatrix._rows<< std::endl;
if (this->_rows != rHsMatrix._cols)
      	throw std::out_of_range("Matrix product invalid");
// allocating memory for M x N * N x P = M x P matrix product
T **productMatrix = new T*[rHsMatrix._rows];

for (int t = 0; t < rHsMatrix._rows; t++)
{
	productMatrix[t] = new T[this->_cols];
}
for (int i= 0; i<rHsMatrix._rows; i++)
{	
	for (int k = 0; k < this->_cols ; k++)
	{
	T temp = 0;
        for (int j=0; j<this->_rows; j++)
        {     
              std::cout << "accessing: " << "outer row: " << i << "  col: " << k<< "inner row "<< j << std::endl;
	      
              temp += this->_matrix[j][k] *  rHsMatrix._matrix[i][j];
        }
	std::cout << "accessing: " << "row: " << i << "  col: " << k << std::endl;
	productMatrix[i][k] = temp;
        }
}
//delete old memory of rhsMatrix
for(int i = 0; i<rHsMatrix._rows; i++)
{
        delete [] rHsMatrix._matrix[i];
}
delete[] rHsMatrix._matrix;
//create new memory for rhsMatrix with new dimensions from matrix product
rHsMatrix._cols =  this->_cols;
rHsMatrix._matrix = new T*[rHsMatrix._rows];

for (int t = 0; t < rHsMatrix._rows; t++)
{
        rHsMatrix._matrix[t] = new T[rHsMatrix._cols];
}
//inserting data from multiplication into rhsMatrix
for (int i = 0; i< rHsMatrix._rows; i++)
{
        for (int j = 0; j < rHsMatrix._cols; j++)
        {
        rHsMatrix._matrix[i][j] = productMatrix[i][j];
        std::cout<< "copy elements from multiplication" << std::endl;
        }
}
//deallocating memory from productMatrix
for(int i = 0; i<rHsMatrix._rows; i++)
{
        delete [] productMatrix[i];
}
delete[] productMatrix;

return rHsMatrix;

}
catch(const std::exception& e)
 {
       std::cout  << e.what();
       return *this;
 }
}

