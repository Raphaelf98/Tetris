#ifndef MATRIX_H
#define MATRIX_H
#include<vector>
#include<stdio.h>
#include <stdlib.h>
#include<iostream>
#include <stdexcept>
#include <initializer_list>
template <typename T> class Matrix
{
public:
Matrix();
Matrix(size_t rows,size_t col);
Matrix(const Matrix &source);
Matrix<T> operator = (const Matrix &source);
Matrix(std::initializer_list< std::initializer_list< T>> matrixList);
Matrix(Matrix &&source);
Matrix<T> &operator = ( Matrix &&source);
~Matrix();
T  operator ()(size_t row, size_t column);
void  operator()(size_t row, size_t col, T value);
void operator()(std::initializer_list< std::initializer_list< T>> matrixList);
Matrix<T> operator * (  Matrix &rHsMatrix);
Matrix<T> operator + ( Matrix rHsMatrix);
Matrix<T> operator - ( Matrix rHsMatrix);

Matrix<T> operator * (T x);

int getRowSize();
int getColumnSize();
void eraseColumn(int col);
void printMatrix();
private:

size_t _rows, _cols;
T** _matrix;
bool memoryAllocated = true;
bool moved = false;
};
//default constructor 
template<typename T> Matrix<T>::Matrix()
{
	std::cout<<"default constrtuctor called"<<std::endl;
	_matrix = nullptr;
}

// constructor with rows and colums
template<typename T> Matrix<T>::Matrix(const size_t rows,const size_t cols)
{
	//std::cout.setstate(std::ios_base::failbit);
	std::cout<<"row column construcor called"<<std::endl;
	_rows= rows;	
	_cols = cols;
	_matrix = new T*[_rows];
//std::cout << "Creating " << _cols << " X " << _rows<<" Matrix"<<  std::endl;
	for (size_t t= 0; t <_rows; t++)
	{
	//std::cout<<"Heap memory allocated for row number:"<<t << " at memory address: " << &_matrix[t]<<std::endl;
         
	}   
	for (size_t t= 0; t <_rows; t++)
	{
		_matrix[t] = new T[_cols];
	}	

}
template<typename T> Matrix<T>::Matrix(std::initializer_list< std::initializer_list< T>> matrixList )
{
std::cout<<"initializer list constructor called"<<std::endl;
try{
	
_rows= matrixList.begin()->size();
_cols	= matrixList.size();
_matrix = new T*[_rows];
for (size_t t= 0; t <_rows; t++)
{

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
_matrix[rIt][cIt]= col;
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
	std::cout<<"destructor called"<<std::endl;
	if (_matrix != nullptr ) 
	{
		std::cout<<"Heap memory deallocated"<<std::endl;
		if(_rows > 0)
		{
			for (size_t t; t < _rows; t++)
			{
		
				delete [] _matrix[t];	
			}
		}
		if (_cols > 0)
		{std::cout<<"Heap memory deallocated"<<std::endl;
		
			delete [] _matrix;
		}
	
	}

}
//copy constructor
template <typename T>  Matrix<T>::Matrix(const Matrix &source)
{
	std::cout<<"copy constructor called"<<std::endl;
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
		}
	}
}
//copy assignment operator
template<typename T> Matrix<T> Matrix<T>::operator = (const Matrix &source)
{
	
std::cout<<"copy assignment operator called"<<std::endl;

//free memory from previously allocated obejct his
if(_matrix != nullptr){
for(int i = 0; i< _rows; i++)
{
	delete [] _matrix[i];
}
delete[] _matrix;
}
if (this  == &source){ return *this;}
_rows = source._rows;
_cols = source._cols;
_matrix = new T*[_rows];
for (int t =0; t< _rows; t++)
{
_matrix[t] = new T[_cols];
}


for (int i = 0; i< _rows; i++)
{
	for (int j = 0; j < _cols; j++)
	{
	_matrix[i][j] = source._matrix[i][j];
	}
}
return *this;
}
//move constructor 
template<typename T> Matrix<T>::Matrix( Matrix &&source)
{
	std::cout<<"move constructor called"<<std::endl;

	_matrix = source._matrix;
	_rows = source._rows;
	_cols = source._cols;
	
 	source._matrix = nullptr;
    source._rows = 0;
	source._cols = 0;
         
}
//move assignment operator
template<typename T> Matrix<T> &Matrix<T>::operator = ( Matrix &&source)
{
	std::cout<<"move assingment operator called"<<std::endl;
		
//free memory from previously allocated obejct his
	if(_matrix != nullptr )
	{
	
		delete[] _matrix;
	}
	if (this  == &source){ return *this;}
	_rows = source._rows;
	_cols = source._cols;

	_matrix = source._matrix;  
    source._rows = 0;
	source._cols = 0;
	source._matrix = nullptr;
	return *this;
}



template <typename T> T  Matrix<T>::operator()(size_t row, size_t col)
{
try
{	
if (row > _rows && col > _cols ){
	throw std::out_of_range("Bad Matrix Access");
}
if (_rows ==0 ||_cols==0){
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
if(_matrix!= nullptr )
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
/*
template <typename T> Matrix<T> Matrix<T>::operator * ( Matrix &rHsMatrix)
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
std::cout<< "product matrix deallocated" << std::endl;

return rHsMatrix;
}
catch(const std::exception& e)
 {
       std::cout  << e.what();
       return *this;
 }
}
*/
template <typename T> Matrix<T> Matrix<T>::operator * ( Matrix &rHsMatrix)
{
try
{
//std::cout<<"Multiplying "<< this->_cols << " X " << this->_rows << " with " << rHsMatrix._cols << " X " << rHsMatrix._rows<< std::endl;
if (this->_rows != rHsMatrix._cols)
      	throw std::out_of_range("Matrix product invalid");

Matrix <T> tmp (rHsMatrix._rows, this->_cols);

for (int i= 0; i<rHsMatrix._rows; i++)
{	
	for (int k = 0; k < this->_cols ; k++)
	{
	T temp = 0;
        for (int j=0; j<this->_rows; j++)
        {     
	      
              temp += this->_matrix[j][k] *  rHsMatrix._matrix[i][j];
        }
		tmp._matrix[i][k] = temp;
        }
}

return tmp;

}
catch(const std::exception& e)
 {
       std::cout  << e.what();
       return *this;
 }
}

template <typename T> void Matrix<T>::operator()(std::initializer_list< std::initializer_list< T>> matrixList)
{
try{
//If Matrix was initialized memory should be feed otherwise (default constructor) not
if(_matrix != nullptr){
	for(int i = 0; i< _rows; i++)
	{	
	delete [] _matrix[i];
	}
delete[] _matrix;
}
_rows= matrixList.begin()->size();
_cols	= matrixList.size();
_matrix = new T*[_rows];

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
_matrix[rIt][cIt]= col;
rIt= rIt +1 ;
}
cIt = cIt +1;
}

}
catch(const std::exception& e) {
    std::cout  << e.what();
}

}
template <typename T > int Matrix<T>::getRowSize()
{
	return _rows;
}
template <typename T > int Matrix<T>::getColumnSize()
{
	return _cols;
}

template <typename T> Matrix<T> Matrix<T>::operator + ( Matrix	rHsMatrix)
{
try
{
	if (this->_rows == rHsMatrix._rows && this->_cols == rHsMatrix._cols)
	{
    for (int i = 0; i< rHsMatrix._rows; i++)
	{
        for (int j = 0; j < rHsMatrix._cols; j++)
        {
        	rHsMatrix._matrix[i][j] = rHsMatrix._matrix[i][j] + this->_matrix[i][j];
        }
	}
	
	}
	else std::out_of_range("Matrix addition invalid");
return rHsMatrix;

}
catch(const std::exception& e)
 {
       std::cout  << e.what();
       return *this;
 }
}
template <typename T> Matrix<T> Matrix<T>::operator - ( Matrix	rHsMatrix)
{
try
{
	if (this->_rows == rHsMatrix._rows && this->_cols == rHsMatrix._cols)
	{
    for (int i = 0; i< rHsMatrix._rows; i++)
	{
        for (int j = 0; j < rHsMatrix._cols; j++)
        {
        	rHsMatrix._matrix[i][j] = rHsMatrix._matrix[i][j] - this->_matrix[i][j];
        }
	}
	
	}
	else std::out_of_range("Matrix subtraction invalid");
return rHsMatrix;

}
catch(const std::exception& e)
 {
       std::cout  << e.what();
       return *this;
 }
}
template<typename T> Matrix<T> Matrix<T>::operator * (T x)
{

Matrix<T> tmp(this->_rows, this->_cols);
for (int i = 0; i< this->_rows; i++)
	{
        for (int j = 0; j < this->_cols; j++)
        {
        	tmp._matrix[i][j] = x * this->_matrix[i][j]  ;
        	std::cout<< "scalar product" << std::endl;
        }
	}
	return tmp;

}
template <typename T > void Matrix<T>::eraseColumn(int col)
{
	if ((_rows -1 == 0) & (_matrix != nullptr))
	{	
		std::cout<< "   this->_rows-1 == 0   " << std::endl;
		for(int i = 0; i< _rows; i++)
		{
			delete [] this->_matrix[i];
		}
		delete[] this->_matrix;
		this->_rows = 0;
		this->_cols= 0;
	}
	else
	{
		
		if(col < _rows && col >= 0)
		{ 	
			Matrix<T> tmp(this->_rows-1, this->_cols);
			int t =0;
			for (int i = 0; i< this->_rows; i++)
			{	
				if (i != col)
				{	
					std::cout<< "t  " << t<< std::endl;
        			for (int j = 0; j < this->_cols; j++)
        			{
        				tmp._matrix[t][j] = this->_matrix[i][j];
        			
        			}
					
					t++;
				}
				else
				{
					std::cout<< "ignored  " << t<< std::endl;
				}
			}
			std::cout<< "delete old matrix  " << std::endl;
			for(int i = 0; i< _rows; i++)
			{
				delete [] _matrix[i];
			}
			delete[] _matrix;
			std::cout<< "create new " << std::endl;
			_rows=tmp._rows;
			_cols=tmp._cols;
			_matrix = new T*[tmp._rows];
			for (size_t t = 0; t < tmp._rows; t++)
			{
				_matrix[t] = new T[tmp._cols];
			}	
			std::cout<< "fill new matrix with temp data " << std::endl;
			for (int i = 0; i< tmp._rows; i++)
				{	
				
        			for (int j = 0; j < tmp._cols; j++)
        			{
        				_matrix[i][j] = tmp._matrix[i][j];
        			
        			}
					
				
				}
			std::cout<< "Column "<< col << " erased" << std::endl;
		}
	
		else {std::cout<< "Bad Matrix Access"<< std::endl;}
	}
}
#endif