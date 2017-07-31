/**
 * @file Matrix.h
 * @author Itai Tagar <itagar>
 * @version 1.3
 * @date 18 Sep 2016
 *
 * @brief A Header File for the Matrix Class.
 *
 * @section LICENSE
 * This program is free to use in every operation system.
 *
 * @section DESCRIPTION
 * A Header File for the Matrix Class.
 * Declaring the Matrix Class, it's methods and fields.
 * A Matrix class is generic Matrix which supports several methods which the
 * Matrix Class assume (e.g. Copy Constructor, '+' operator...).
 * The Matrix Class can perform several Matrix operations.
 * The Header file must include the .hpp file because it is a Template Class,
 * so I used this .h file basically for the code to be more readable and to separate
 * the declaration and the implementation
 * (even though that the user who include this .h file will see the implementation as well).
 */


#ifndef _MATRIX_H
#define _MATRIX_H


/*-----=  Includes  =-----*/


#include <iostream>
#include <vector>
#include "MatrixException.h"


/*-----=  Class Definition  =-----*/


/**
 * @brief A Class representing a Generic Matrix.
 *        The Matrix can hold different elements which satisfy several methods which the Matrix
 *        Class assume (e.g. Copy Constructor, '+' operator...).
 *        The Matrix Class can perform several Matrix operations.
 */
template <class T>
class Matrix
{
public:

    /**
     * @brief The Default Constructor for a Matrix.
     *        The Constructor sets the Matrix dimensions to the INITIAL_MATRIX_SIZE,
     *        and all the elements in the Matrix are set to DEFAULT_VALUE.
     */
    Matrix();

    /**
     * @brief A Constructor for a Matrix which receives the desired dimensions and create a Matrix
     *        with these dimensions, and all the elements in the Matrix are set to DEFAULT_VALUE.
     *        If one of the dimensions is invalid (i.e. equals to zero), an Exception will be thrown
     * @param rows The number of rows in the Matrix.
     * @param cols The number of columns in the Matrix.
     */
    Matrix(unsigned int rows, unsigned int cols);

    /**
     * @brief A Copy Constructor for a Matrix which receives another Matrix and create a copy of it.
     * @param other The Matrix to copy.
     */
    Matrix(const Matrix<T>& other);

    /**
     * @brief A Move Constructor for a Matrix.
     * @param other The Matrix to move.
     */
    Matrix(const Matrix<T> && other);

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
    Matrix(unsigned int rows, unsigned int cols, const std::vector<T>& cells);

    /**
     * @brief The Destructor for the Matrix.
     */
    ~Matrix();

    /**
     * @brief An operator overload for the assignment operator '='.
     *        The operator assign to this Matrix the given other Matrix, and creates an
     *        independent copy of the given Matrix.
     *        This operator support both Move Assignment and Default Assignment.
     * @param other The other Matrix to assign to this Matrix.
     * @return This Matrix after copying the given Matrix to it.
     */
    Matrix<T>& operator=(Matrix<T> other);

    /**
     * @brief An operator overload for the addition operator '+'.
     *        The operator add this Matrix with the given other Matrix and return a new Matrix
     *        which represent the result of the addition operation.
     *        This operator does not change this Matrix or the given Matrix data.
     *        If the dimensions of this Matrix doesn't fit the given Matrix, an Exception will
     *        be thrown.
     *        This operator supports multithread mode, where each thread perform the operation
     *        of a single row in the Matrix.
     * @param other The other Matrix to add to this Matrix.
     * @return A Matrix which represent the result of the addition operation.
     */
    Matrix<T> operator+(const Matrix<T>& other) const;

    /**
     * @brief An operator overload for the subtraction operator '-'.
     *        The operator subtract this Matrix with the given other Matrix and return a new Matrix
     *        which represent the result of the subtraction operation.
     *        This operator does not change this Matrix or the given Matrix data.
     *        If the dimensions of this Matrix doesn't fit the given Matrix, an Exception will
     *        be thrown.
     * @param other The other Matrix to subtract to this Matrix.
     * @return A Matrix which represent the result of the subtraction operation.
     */
    Matrix<T> operator-(const Matrix<T>& other) const;

    /**
     * @brief An operator overload for the multiplication operator '*'.
     *        The operator multiply this Matrix with the given other Matrix and return a new Matrix
     *        which represent the result of the multiplication operation.
     *        This operator does not change this Matrix or the given Matrix data.
     *        If the dimensions of this Matrix doesn't fit the given Matrix, an Exception will
     *        be thrown.
     *        This operator supports multithread mode, where each thread perform the operation
     *        of a single row in the Matrix.
     * @param other The other Matrix to multiply to this Matrix.
     * @return A Matrix which represent the result of the multiplication operation.
     */
    Matrix<T> operator*(const Matrix<T>& other) const;

    /**
     * @brief An operator overload for the comparison operator '=='.
     *        The operator determine if this Matrix is equal to the given other Matrix,
     *        i.e. equality in each cell of the Matrices.
     * @param other The other Matrix to check.
     * @return true if the Matrices are equal, false otherwise.
     */
    bool operator==(const Matrix<T>& other) const;

    /**
     * @brief An operator overload for the comparison operator '!='.
     *        The operator determine if this Matrix is not equal to the given other Matrix,
     *        i.e. at least in one cell there is non-equality.
     * @param other The other Matrix to check.
     * @return true if the Matrices are not equal, false otherwise.
     */
    bool operator!=(const Matrix<T>& other) const;

    /**
     * @brief Perform the Transpose operation on this Matrix.
     *        This operator does not change this Matrix data.
     * @return A Matrix which represent the result of the Transpose operation.
     */
    Matrix<T> trans() const;

    /**
     * @brief An operator overload for the output stream operator '<<'.
     *        The operator creates an output format for a Matrix and sets the given output stream
     *        with it.
     *        The format of a Matrix output is:
     *          Each row of the Matrix is in it's own row, and all the cells in the row
     *          are separated by a single tab.
     * @param out The output stream to set with the Matrix representation.
     * @param matrix The Matrix to print to the output stream.
     * @return An output stream with the Matrix representation.
     */
    template <typename U>
    friend std::ostream& operator<<(std::ostream& out, const Matrix<U>& matrix);

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
    const T& operator()(unsigned int rowNumber, unsigned int colNumber) const;

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
    T& operator()(unsigned int rowNumber, unsigned int colNumber);

    /**
     * @brief Determine if this Matrix is a square Matrix.
     * @return true if the Matrix is square, false otherwise.
     */
    bool isSquareMatrix() const { return _rows == _cols; };

    /**
     * @brief Returns the number of rows in the Matrix.
     * @return The number of rows in the Matrix.
     */
    unsigned int rows() const { return _rows; };

    /**
     * @brief Returns the number of columns in the Matrix.
     * @return The number of columns in the Matrix.
     */
    unsigned int cols() const { return _cols; };

    /**
     * @brief const_iterator is a constant iterator for the type T Vector which contains
     *        the Matrix data.
     */
    typedef typename std::vector<T>::const_iterator const_iterator;

    /**
     * @brief Returns the const iterator for the beginning of the Matrix.
     * @return const iterator for the beginning of the Matrix.
     */
    const_iterator begin() const { return _cells.begin(); };

    /**
     * @brief Returns the const iterator for the end of the Matrix.
     * @return const iterator for the end of the Matrix.
     */
    const_iterator end() const { return _cells.end(); };

    /**
     * @brief Sets the Thread Flag to be on or off by the given parameter.
     *        The given parameter is a boolean value which determine the state of the Thread Flag.
     *        If the function changed the flag mode, an informative message about the flag state is
     *        printed.
     *        Note: I had to change the name from 's_setParallel' because of the bug in the script.
     * @param threadFlag The requested state of the Thread Flag
     *        (true = parallel, false = non-parallel).
     */
    static void setParallel(const bool threadFlag);

private:

    /**
     * @brief The number of rows in the Matrix.
     */
    unsigned int _rows;

    /**
     * @brief The number of columns in the Matrix.
     */
    unsigned int _cols;

    /**
     * @brief The cells in the Matrix which holds the data.
     */
    std::vector<T> _cells;

    /**
     * @brief A flag which determine if the operation that support multi-threading should
     *        operate in parallel mode or in non-parallel mode.
     */
    static bool _threadFlag;

    /**
     * @brief An Helper Function for the Plus Operator.
     *        While working on multithread mode, this function is called from a single
     *        thread in order to perform the addition operation on a single row.
     *        Note: I had to change the name from 's_plusHelper' because of the bug in the script.
     * @param result The Matrix in which we perform the addition operation.
     * @param other The Matrix which contains the data to add.
     * @param rowNumber The current row number in the Matrices to perform the operation.
     */
    static void _plusHelper(Matrix<T>& result, const Matrix<T>& other, unsigned int rowNumber);

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
    static void _multiHelper(Matrix<T>& result, const Matrix<T>& first, const Matrix<T>& second,
                             unsigned int rowNumber);

    /**
     * @brief Swaps the data between two given Matrices.
     * @param first The first Matrix to swap.
     * @param second The second Matrix to swap.
     */
    void _swapMatrix(Matrix<T>& first, Matrix<T>& second);

};


#include "Matrix.hpp"

#endif
