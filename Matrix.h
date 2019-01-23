#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <cmath>

//TODO: det() - determinant
//TODO: inverse() - inverse matrix
//TODO: minor(T element) - get minor of the given element of the matrix
//TODO: adjoint() - get adjoint matrix
//TODO: algcompl() - get algebraic complement for the given element
//TODO: isIdentity() - check if current matrix is identity
//TODO: isInverse()
//TODO: isZero()
//TODO: isUpperTriangular()
//TODO: isLowerTriangular()
//TODO: isDiagonal()
//etc

#include <iostream>
#include <cstddef>
#include <cstring>

template<typename T>
class Matrix;

template<typename T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& _matrix);

template<typename T>
class Matrix
{
    public:
        Matrix(const std::size_t& rows, const std::size_t& columns);
        Matrix(const Matrix<T>& _matrix);
        Matrix(Matrix<T>&& _matrix);
        
        ~Matrix();
        
        const Matrix<T> transpose() const;
        const Matrix<T> minor(T element);
        T               det() const;
        T               trace() const;
        bool            isSquare() const;
        bool            isTraceless() const;
        void            clear();
        std::size_t     length() const;
        std::size_t     length(const std::size_t& dimension) const; 
        
        //get arr[row][column]
        inline T& operator()(const std::size_t& row, const std::size_t& column) const;
        
        const Matrix<T> operator+(const Matrix<T>& _matrix) const; 
        const Matrix<T> operator-(const Matrix<T>& _matrix) const;
        const Matrix<T> operator*(const Matrix<T>& _matrix) const;
        const Matrix<T> operator*(const T& value) const;
        
        Matrix<T>& operator=(const Matrix<T>& _matrix);
        Matrix<T>& operator=(Matrix<T>&& _matrix);
        Matrix<T>& operator+=(const Matrix<T>& _matrix);
        Matrix<T>& operator-=(const Matrix<T>& _matrix);
        Matrix<T>& operator*=(const Matrix<T>& _matrix);
        Matrix<T>& operator*=(const T& value);
        
    private:
        std::size_t rows;
        std::size_t columns;
        T **arr;
        
        template<typename T1>
        friend const Matrix<T1> operator*(const T1& value, const Matrix<T1>& _matrix);
        friend std::ostream& operator<<<>(std::ostream& out, const Matrix<T>& _matrix);
};

template<typename T>
Matrix<T>::Matrix(const std::size_t& rows, const std::size_t& columns)
    :rows(rows), columns(columns)
{
    if(!rows || !columns)
    {
        throw "Rows and columns must be greater than zero!";
    } 
    
    arr = new T*[rows];
    
    for(std::size_t i = 0; i < rows; i++)
    {
        arr[i] = new T[columns]{0};
    }
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T>& _matrix)
    :rows(_matrix.rows), columns(_matrix.columns)
{
    arr = new T*[rows];
    
    for(std::size_t i = 0; i < rows; i++)
    {
        arr[i] = new T[columns];
        for(std::size_t j = 0; j < columns; j++)
        {
            arr[i][j] = _matrix.arr[i][j];
        }
    }
}

template<typename T>
Matrix<T>::Matrix(Matrix<T>&& _matrix)
    :rows(_matrix.rows), columns(_matrix.columns)
{
    clear();
    arr         = _matrix.arr;
    _matrix.arr = nullptr;
}

template<typename T>
Matrix<T>::~Matrix()
{
    clear();
}

template<typename T>
const Matrix<T> Matrix<T>::transpose() const
{
    Matrix<T> tmp(columns, rows);
    
    for(std::size_t i = 0; i < rows; i++)
    {
        for(std::size_t j = 0; j < columns; j++)
        {
            tmp.arr[j][i] = arr[i][j];
        }
    }
    
    return tmp;
}

/*template<typename T>
const Matrix<T> Matrix<T>::minor(std::size_t& const std::size_t& i, const std::size_t& j)
{
    
    Matrix<T> tmp(rows - 1, columns - 1);
    
    
}*/

template<typename T>
T Matrix<T>::trace() const
{
    if(!isSquare())
	{
		throw "Matrix is not square!";
	}
	
    T tmp = 0;
    
    for(std::size_t i = 0; i < rows; i++)
    {
        tmp += arr[i][i];
    }
    
    return tmp;
}

template<typename T>
inline bool Matrix<T>::isSquare() const
{
	return rows == columns;
}

template<typename T>
inline bool Matrix<T>::isTraceless() const
{
	return !trace();
}

template<typename T>
void Matrix<T>::clear()
{
    if(!arr)
    {
        return;
    }
    
    for(std::size_t i = 0; i < rows; i++)
    {
        delete[] arr[i];
    }
    
    delete[] arr;
    arr = nullptr;
}

template<typename T>
inline std::size_t Matrix<T>::length() const
{
    return rows * columns;
}

template<typename T>
inline std::size_t Matrix<T>::length(const std::size_t& dimension) const
{
    if(dimension == 0)
    {
        return rows;
    }
    else if(dimension == 1)
    {
        return columns;
    }
    
    throw "Dimension doesn't exist!";
}

template<typename T>
inline T& Matrix<T>::operator()(const std::size_t& row, const std::size_t& column) const
{
    return arr[row][column];
}

template<typename T>
const Matrix<T> Matrix<T>::operator+(const Matrix<T>& _matrix) const
{
    if((rows != _matrix.rows) || (columns != _matrix.columns))
    {
        throw "The sizes of the matrices don't match";
        
    }
    
    Matrix<T> tmp(rows, columns);
        
    for(std::size_t i = 0; i < rows; i++)
    {
        for(std::size_t j = 0; j < columns; j++)
        {
            tmp.arr[i][j] = arr[i][j] + _matrix.arr[i][j];
        }
    }
    
    return tmp;
}

template<typename T>
const Matrix<T> Matrix<T>::operator-(const Matrix<T>& _matrix) const
{
    if((rows != _matrix.rows) || (columns != _matrix.columns))
    {
        throw "The sizes of the matrices don't match";
    }
    
    Matrix<T> tmp(rows, columns);
        
    for(std::size_t i = 0; i < rows; i++)
    {
        for(std::size_t j = 0; j < columns; j++)
        {
            tmp.arr[i][j] = arr[i][j] - _matrix.arr[i][j];
        }
    }
    
    return tmp;
}

template<typename T>
const Matrix<T> Matrix<T>::operator*(const Matrix<T>& _matrix) const
{
    if(columns != _matrix.rows)
    {
        throw "Wrong size for matrix multilplication"; 
    }
    
    Matrix<T> tmp(rows, _matrix.columns);
        
    for(std::size_t i = 0 ; i < rows; i++)
    {
        for(std::size_t j = 0 ; j < columns; j++)
        {
            tmp.arr[i][j] = 0;
            for(std::size_t k = 0 ; k < columns; k++)
            {
                tmp.arr[i][j] += arr[i][k] * _matrix.arr[k][j];                 
            }
        }
    }
    
    return tmp;
}

template<typename T>
const Matrix<T> Matrix<T>::operator*(const T& value) const
{   
    Matrix<T> tmp(*this);
    
    for(std::size_t i = 0; i < rows; i++)
    {
        for(std::size_t j = 0; j < columns; j++)
        {
            tmp.arr[i][j] *= value;
        }
    }
    
    return tmp;
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& _matrix)
{
    if(this == &_matrix)
    {
        return *this;
    }
    
    clear();
    
    rows    = _matrix.rows;
    columns = _matrix.columns;
    
    arr = new T*[rows];
    for(std::size_t i = 0; i < rows; i++)
    {
        arr[i] = new T[columns];
        memmove(arr[i], _matrix.arr[i], sizeof(T) * columns);
    }  
    
    return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(Matrix<T>&& _matrix)
{
    if(this == &_matrix)
    {
        return *this;
    }
    
    clear();
    
    rows    = _matrix.rows;
    columns = _matrix.columns;
    arr     = _matrix.arr;
    
    _matrix.rows    = 0;
    _matrix.columns = 0;
    _matrix.arr     = nullptr;
    
    return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& _matrix)
{
    return *this = *this + _matrix;
}

template<typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& _matrix)
{
    return *this = *this - _matrix;
}

template<typename T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& _matrix)
{
    return *this = *this * _matrix;
}

template<typename T>
Matrix<T>& Matrix<T>::operator*=(const T& value)
{
    return *this = *this * value;
}

template<typename T1>
const Matrix<T1> operator*(const T1& value, const Matrix<T1>& _matrix)
{
    return _matrix * value;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& _matrix)
{
    if(!_matrix.arr)
    {
        return out;
    }
    
    for(std::size_t i = 0; i < _matrix.rows; i++)
    {
        for(std::size_t j = 0; j < _matrix.columns; j++)
        {
            out << _matrix.arr[i][j] << " ";
        }
        
        out << std::endl;
    }
    
    return out;
}

#endif
