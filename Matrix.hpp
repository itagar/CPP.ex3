/**
 * @file Matrix.hpp
 * @author Itai Tagar <itagar>
 * @version 1.8
 * @date 19 Sep 2016
 *
 * @brief An implementation of the Matrix Class.
 *
 * @section LICENSE
 * This program is free to use in every operation system.
 *
 * @section DESCRIPTION
 * An implementation of the Matrix Class.
 * A Matrix class is generic Matrix which supports several methods which the
 * Matrix Class assume (e.g. Copy Constructor, '+' operator...).
 * The Matrix Class can perform several Matrix operations.
 */


#ifndef _MATRIX_HPP
#define _MATRIX_HPP


/*-----=  Includes  =-----*/


#include <thread>
#include <cassert>
#include "Matrix.h"
#include "Complex.h"


/*-----=  Definitions  =-----*/


/**
 * @def DEFAULT_VALUE 0
 * @brief A Macro that sets the default value for the elements in the Matrix.
 */
#define DEFAULT_VALUE 0

/**
 * @def EMPTY_MATRIX_SIZE 0
 * @brief A Macro that sets the size for an empty Matrix.
 */
#define EMPTY_MATRIX_SIZE 0

/**
 * @def INITIAL_MATRIX_SIZE 1
 * @brief A Macro that sets the initial size of a Matrix.
 */
#define INITIAL_MATRIX_SIZE 1

/**
 * @def CELL_SEPARATOR "\t"
 * @brief A Macro that sets the output for the separator between two cells in the Matrix.
 */
#define CELL_SEPARATOR "\t"

/**
 * @def DEFAULT_THREAD_FLAG false
 * @brief A Macro that sets the default thread flag for performing operations in multi-thread.
 */
#define DEFAULT_THREAD_FLAG false

/**
 * @def THREAD_MODE_MESSAGE_INTRO "Generic Matrix mode changed to "
 * @brief A Macro that sets the beginning of output message for changing the parallel thread mode.
 */
#define THREAD_MODE_MESSAGE_INTRO "Generic Matrix mode changed to "

/**
 * @def PARALLEL_MODE "Parallel"
 * @brief A Macro that sets the output message for changing to parallel mode operations.
 */
#define PARALLEL_MODE "Parallel"

/**
 * @def NON_PARALLEL_MODE "non-Parallel"
 * @brief A Macro that sets the output message for changing to non-parallel mode operations.
 */
#define NON_PARALLEL_MODE "non-Parallel"

/**
 * @def THREAD_MODE_MESSAGE_END " mode."
 * @brief A Macro that sets the end of the output message for changing the parallel thread mode.
 */
#define THREAD_MODE_MESSAGE_END " mode."




/*-----=  Static Variables Initialization  =-----*/


template <class T>
bool Matrix<T>::_threadFlag = DEFAULT_THREAD_FLAG;


/*-----=  Constructors & Destructors  =-----*/


/**
 * @brief The Default Constructor for a Matrix.
 *        The Constructor sets the Matrix dimensions to the INITIAL_MATRIX_SIZE,
 *        and all the elements in the Matrix are set to DEFAULT_VALUE.
 */
template <class T>
Matrix<T>::Matrix() : Matrix(INITIAL_MATRIX_SIZE, INITIAL_MATRIX_SIZE)
{

}

/**
 * @brief A Constructor for a Matrix which receives the desired dimensions and create a Matrix
 *        with these dimensions, and all the elements in the Matrix are set to DEFAULT_VALUE.
 *        If one of the dimensions is invalid (i.e. equals to zero), an Exception will be thrown.
 * @param rows The number of rows in the Matrix.
 * @param cols The number of columns in the Matrix.
 */
template <class T>
Matrix<T>::Matrix(unsigned int rows, unsigned int cols)
        : _rows(rows), _cols(cols), _cells(_rows * _cols)
{
    // The Matrix dimensions considered valid if both rows and columns are not zero or
    // if both of them are zero. (i.e. if one of them is zero and the other is not it's an error).
    if ((_rows == EMPTY_MATRIX_SIZE) ^ (_cols == EMPTY_MATRIX_SIZE))
    {
        throw MatrixDimensionsException();
    }
}

/**
 * @brief A Copy Constructor for a Matrix which receives another Matrix and create a copy of it.
 * @param other The Matrix to copy.
 */
template <class T>
Matrix<T>::Matrix(const Matrix<T>& other)
        : _rows(other._rows), _cols(other._cols), _cells(other._cells)
{

}

/**
 * @brief A Move Constructor for a Matrix.
 * @param other The Matrix to move.
 */
template <class T>
Matrix<T>::Matrix(const Matrix<T> && other)
        : _rows(other._rows), _cols(other._cols), _cells(std::move(other._cells))
{

}

/**
 * @brief A Constructor for a Matrix which receives the desired dimensions and create a Matrix
 *        with these dimensions. The Constructor also receives a vector with elements to insert
 *        to the Matrix.
 *        If one of the dimensions is invalid (i.e. equals to zero) or if the number of given
 *        elements does not match the given dimensions, an Exception will be thrown.
 * @param rows The number of rows in the Matrix.
 * @param cols The number of columns in the Matrix.
 * @param cells A Vector of elements to insert to the Matrix.
 */
template <class T>
Matrix<T>::Matrix(unsigned int rows, unsigned int cols, const std::vector<T>& cells)
        : _rows(rows), _cols(cols), _cells(cells)
{
    // The Matrix dimensions considered valid if both rows and columns are not zero or
    // if both of them are zero. (i.e. if one of them is zero and the other is not it's an error).
    if ((_rows == EMPTY_MATRIX_SIZE) ^ (_cols == EMPTY_MATRIX_SIZE))
    {
        throw MatrixDimensionsException();
    }

    // If the number of given cells does not fit the given dimensions.
    if (cells.size() != (_rows * _cols))
    {
        throw MatrixDimensionsException();
    }
}

/**
 * @brief The Destructor for the Matrix.
 */
template <class T>
Matrix<T>::~Matrix()
{

}


/*-----=  Matrix Operators  =-----*/


/**
 * @brief Swaps the data between two given Matrices.
 * @param first The first Matrix to swap.
 * @param second The second Matrix to swap.
 */
template <class T>
void Matrix<T>::_swapMatrix(Matrix<T>& first, Matrix<T>& second)
{
    using std::swap;
    swap(first._rows, second._rows);
    swap(first._cols, second._cols);
    swap(first._cells, second._cells);
}

/**
 * @brief An operator overload for the assignment operator '='.
 *        The operator assign to this Matrix the given other Matrix, and creates an independent copy
 *        of the given Matrix.
 *        This operator support both Move Assignment and Default Assignment.
 * @param other The other Matrix to assign to this Matrix.
 * @return This Matrix after copying the given Matrix to it.
 */
template <class T>
Matrix<T>& Matrix<T>::operator=(Matrix<T> other)
{
    _swapMatrix(*this, other);
    return *this;
}

/**
 * @brief An Helper Function for the Plus Operator.
 *        While working on multithread mode, this function is called from a single thread in order
 *        to perform the addition operation on a single row.
 *        Note: I had to change the name from 's_plusHelper' because of the bug in the script.
 * @param result The Matrix in which we perform the addition operation.
 * @param other The Matrix which contains the data to add.
 * @param rowNumber The current row number in the Matrices to perform the operation.
 */
template <class T>
void Matrix<T>::_plusHelper(Matrix<T>& result, const Matrix<T>& other, unsigned int rowNumber)
{
    assert(rowNumber < result._rows);
    for (unsigned int colNumber = 0; colNumber < result._cols; colNumber++)
    {
        result(rowNumber, colNumber) += other(rowNumber, colNumber);
    }
}

/**
 * @brief An operator overload for the addition operator '+'.
 *        The operator add this Matrix with the given other Matrix and return a new Matrix
 *        which represent the result of the addition operation.
 *        This operator does not change this Matrix or the given Matrix data.
 *        If the dimensions of this Matrix doesn't fit the given Matrix, an Exception will be thrown
 *        This operator supports multithread mode, where each thread perform the operation
 *        of a single row in the Matrix.
 * @param other The other Matrix to add to this Matrix.
 * @return A Matrix which represent the result of the addition operation.
 */
template <class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) const
{
    // If the two Matrices dimensions does not fit for this operation.
    if (this -> _rows != other._rows || this -> _cols != other._cols)
    {
        throw MatrixDimensionsException();
    }

    // Create the Matrix to return which hold the result of the addition operation.
    Matrix<T> result(*this);

    if (_threadFlag)
    {
        // Working in Parallel Mode.
        std::vector<std::thread> rowThreads;
        for (unsigned int currentRow = 0; currentRow < _rows; currentRow++)
        {
            rowThreads.push_back(std::thread(&Matrix<T>::_plusHelper, std::ref(result),
                                             std::ref(other), currentRow));
        }
        for (std::thread& thread : rowThreads)
        {
            thread.join();
        }
    }
    else
    {
        // Working in Non-Parallel Mode.
        for (unsigned int i = 0; i < (result._rows * result._cols); i++)
        {
            result._cells[i] += other._cells[i];
        }
    }

    return result;
}

/**
 * @brief An operator overload for the subtraction operator '-'.
 *        The operator subtract this Matrix with the given other Matrix and return a new Matrix
 *        which represent the result of the subtraction operation.
 *        This operator does not change this Matrix or the given Matrix data.
 *        If the dimensions of this Matrix doesn't fit the given Matrix, an Exception will be thrown
 * @param other The other Matrix to subtract to this Matrix.
 * @return A Matrix which represent the result of the subtraction operation.
 */
template <class T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& other) const
{
    // If the two Matrices dimensions does not fit for this operation.
    if (this -> _rows != other._rows || this -> _cols != other._cols)
    {
        throw MatrixDimensionsException();
    }

    // Create the Matrix to return which hold the result of the addition operation.
    Matrix<T> result(*this);

    for (unsigned int i = 0; i < (result._rows * result._cols); i++)
    {
        result._cells[i] -= other._cells[i];
    }

    return result;
}

/**
     * @brief An Helper Function for the Multiply Operator.
     *        This function perform the multiplication operation for a single row.
     *        While working on multithread mode, this function is called from a single
     *        thread in order to perform the multiplication operation on a single row.
     *        Note: I had to change the name from 's_multiHelper' because of the bug in the script.
     * @param result The Matrix in which we perform the multiplication operation.
     * @param first The first Matrix in the multiplication operation (on the right side).
     * @param second The second Matrix in the multiplication operation (on the left side).
     * @param rowNumber The current row number in the result Matrix to perform the operation.
     */
template <class T>
void Matrix<T>::_multiHelper(Matrix<T>& result, const Matrix<T>& first, const Matrix<T>& second,
                             unsigned int rowNumber)
{
    assert(rowNumber < result._rows);
    for (unsigned int j = 0; j < second._cols; j++)
    {
        T sum(DEFAULT_VALUE);
        for (unsigned int k = 0; k < first._cols; k++)
        {
            sum += first(rowNumber, k) * second(k, j);
        }
        result(rowNumber, j) = sum;
    }
}

/**
 * @brief An operator overload for the multiplication operator '*'.
 *        The operator multiply this Matrix with the given other Matrix and return a new Matrix
 *        which represent the result of the multiplication operation.
 *        This operator does not change this Matrix or the given Matrix data.
 *        If the dimensions of this Matrix doesn't fit the given Matrix, an Exception will be thrown
 *        This operator supports multithread mode, where each thread perform the operation
 *        of a single row in the Matrix.
 * @param other The other Matrix to multiply to this Matrix.
 * @return A Matrix which represent the result of the multiplication operation.
 */
template <class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) const
{
    // If the two Matrices dimensions does not fit for this operation.
    if (this -> _cols != other._rows)
    {
        throw MatrixDimensionsException();
    }

    // Create the Matrix to return which hold the result of the addition operation.
    Matrix<T> result(this -> _rows, other._cols);

    if (_threadFlag)
    {
        // Working in Parallel Mode.
        std::vector<std::thread> rowThreads;
        for (unsigned int currentRow = 0; currentRow < _rows; currentRow++)
        {
            rowThreads.push_back(std::thread(&Matrix<T>::_multiHelper, std::ref(result),
                                             std::ref(*this), std::ref(other), currentRow));
        }
        for (std::thread& thread : rowThreads)
        {
            thread.join();
        }
    }
    else
    {
        // Working in Non-Parallel Mode.
        for (unsigned int rowNumber = 0; rowNumber < this -> _rows; rowNumber++)
        {
            _multiHelper(result, *this, other, rowNumber);
        }
    }


    return result;
}

/**
 * @brief An operator overload for the comparison operator '=='.
 *        The operator determine if this Matrix is equal to the given other Matrix,
 *        i.e. equality in each cell of the Matrices.
 * @param other The other Matrix to check.
 * @return true if the Matrices are equal, false otherwise.
 */
template <class T>
bool Matrix<T>::operator==(const Matrix<T>& other) const
{
    // Check Dimensions first.
    if (this -> _rows != other._rows || this -> _cols != other._cols)
    {
        return false;
    }

    // Check equality in each cell.
    for (unsigned int i = 0; i < (_rows * _cols); i++)
    {
        if (_cells[i] != other._cells[i])
        {
            return false;
        }
    }
    return true;
}

/**
 * @brief An operator overload for the comparison operator '!='.
 *        The operator determine if this Matrix is not equal to the given other Matrix,
 *        i.e. at least in one cell there is non-equality.
 * @param other The other Matrix to check.
 * @return true if the Matrices are not equal, false otherwise.
 */
template <class T>
bool Matrix<T>::operator!=(const Matrix<T>& other) const
{
    return !(*this == other);
}

/**
 * @brief Perform the Transpose operation on this Matrix.
 *        This operator does not change this Matrix data.
 * @return A Matrix which represent the result of the Transpose operation.
 */
template <class T>
Matrix<T> Matrix<T>::trans() const
{
    Matrix<T> result(_cols, _rows);
    for (unsigned int row = 0; row < _rows; row++)
    {
        for (unsigned int col = 0; col < _cols; col++)
        {
            result(col, row) = (*this)(row, col);
        }
    }
    return result;

}

/**
 * @brief Perform the Conjugate Transpose operation on this Matrix.
 *        This operator does not change this Matrix data.
 * @return A Matrix which represent the result of the Conjugate Transpose operation.
 */
template <>
Matrix<Complex> Matrix<Complex>::trans() const
{
    Matrix<Complex> result(_cols, _rows);
    for (unsigned int row = 0; row < _rows; row++)
    {
        for (unsigned int col = 0; col < _cols; col++)
        {
            result(col, row) = ((*this)(row, col)).conj();
        }
    }
    return result;

}

/**
 * @brief An operator overload for the output stream operator '<<'.
 *        The operator creates an output format for a Matrix and sets the given output stream
 *        with it.
 *        The format of a Matrix output is:
 *          Each row of the Matrix is in it's own row, and all the cells in the row are separated
 *          by a single tab.
 * @param out The output stream to set with the Matrix representation.
 * @param matrix The Matrix to print to the output stream.
 * @return An output stream with the Matrix representation.
 */
template <class T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& matrix)
{
    for (unsigned int i = 0; i < matrix._rows; i++)
    {
        for (unsigned int j = 0; j < matrix._cols; j++)
        {
            out << matrix(i, j) << CELL_SEPARATOR;
        }
        out << std::endl;
    }
    return out;
}

/**
 * @brief An operator overload for the access operation '()'.
 *        The operator gives access to the element in the Matrix in the given row and column
 *        by calling the Matrix with the operator as - matrixName(row, col).
 *        This function returns a const reference to the element in the requested cell, and
 *        the user can only read the data and cannot change it.
 *        If one of the given indices to access are invalid, an Exception will be thrown.
 * @param rowNumber The row number in the Matrix to access.
 * @param colNumber The column number in the Matrix to access.
 * @return A read-only access to the element in the given indices in the Matrix.
 */
template <class T>
const T& Matrix<T>::operator()(unsigned int rowNumber, unsigned int colNumber) const
{
    // Check that the given indices are in the Matrix boundaries.
    if (rowNumber >= _rows || colNumber >= _cols)
    {
        throw MatrixIndexException();
    }

    return _cells[(rowNumber * _cols) + colNumber];
}

/**
 * @brief An operator overload for the access operation '()'.
 *        The operator gives access to the element in the Matrix in the given row and column
 *        by calling the Matrix with the operator as - matrixName(row, col).
 *        This function returns a reference to the element in the requested cell, and
 *        the user can read the data and also can change it.
 *        If one of the given indices to access are invalid, an Exception will be thrown.
 * @param rowNumber The row number in the Matrix to access.
 * @param colNumber The column number in the Matrix to access.
 * @return Access to the element in the given indices in the Matrix.
 */
template <class T>
T& Matrix<T>::operator()(unsigned int rowNumber, unsigned int colNumber)
{
    // Check that the given indices are in the Matrix boundaries.
    if (rowNumber >= _rows || colNumber >= _cols)
    {
        throw MatrixIndexException();
    }

    return _cells[(rowNumber * _cols) + colNumber];
}


/*-----=  Static Methods  =-----*/


/**
 * @brief Sets the Thread Flag to be on or off by the given parameter.
 *        The given parameter is a boolean value which determine the state of the Thread Flag.
 *        If the function changed the flag mode, an informative message about the flag state is
 *        printed.
 *        Note: I had to change the name from 's_setParallel' because of the bug in the script.
 * @param threadFlag The requested state of the Thread Flag (true = parallel, false = non-parallel).
 */
template <class T>
void Matrix<T>::setParallel(const bool threadFlag)
{
    if (threadFlag != _threadFlag)
    {
        _threadFlag = threadFlag;
        std::cout << THREAD_MODE_MESSAGE_INTRO
                  << (_threadFlag ? PARALLEL_MODE : NON_PARALLEL_MODE)
                  << THREAD_MODE_MESSAGE_END << std::endl;
    }
}

#endif
