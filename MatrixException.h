/**
 * @file MatrixException.h
 * @author Itai Tagar <itagar>
 * @version 1.0
 * @date 18 Sep 2016
 *
 * @brief A File which contains several Exception Classes for the Matrix Class.
 *
 * @section LICENSE
 * This program is free to use in every operation system.
 *
 * @section DESCRIPTION
 * A File which contains several Exception Classes for the Matrix Class.
 * Defines several Exceptions for Matrix operations errors which may occur.
 * All Exceptions inherits from the Matrix Exception Class which is defined as an Abstract Class,
 * and the Matrix Exception inherit from the Standard Exception Class, and an A
 */


#ifndef _MATRIXEXCEPTION_H
#define _MATRIXEXCEPTION_H


/*-----=  Includes  =-----*/


#include <exception>


/*-----=  Definitions  =-----*/


/**
 * @def PURE_VIRTUAL_FLAG 0
 * @brief A Macro that sets a flag to determine a Virtual method as Pure Virtual.
 */
#define PURE_VIRTUAL_FLAG 0

/**
 * @def DIMENSIONS_EXCEPTION_MESSAGE "Invalid matrix dimensions."
 * @brief A Macro that sets the Exception Message for an invalid Matrix dimensions.
 */
#define DIMENSIONS_EXCEPTION_MESSAGE "Invalid matrix dimensions."

/**
 * @def INDEX_EXCEPTION_MESSAGE "Attempt to reach an invalid index in the Matrix."
 * @brief A Macro that sets the Exception Message for an invalid index in the Matrix.
 */
#define INDEX_EXCEPTION_MESSAGE "Attempt to reach an invalid index in the Matrix."


/*-----=  Class Definition  =-----*/


/**
 * @brief An Abstract Exception Class for Matrix Exceptions.
 */
class MatrixException : public std::exception
{
public:

    /**
     * @brief Describe the error that occured when this Exception was thrown.
     * @return An informative message about the Exception.
     */
    virtual const char * what() const throw() override = PURE_VIRTUAL_FLAG;
};


/**
 * @brief A Matrix Exception Class for an error with the Matrix dimnesions.
 *
 */
class MatrixDimensionsException : public MatrixException
{
public:

    /**
     * @brief Describe the error that occured when this Exception was thrown.
     * @return An informative message about the Exception.
     */
    virtual const char * what() const throw() override { return DIMENSIONS_EXCEPTION_MESSAGE; };
};


/**
 * @brief A Matrix Exception Class for an error with the Matrix out of bounds index access.
 */
class MatrixIndexException : public MatrixException
{
public:

    /**
     * @brief Describe the error that occured when this Exception was thrown.
     * @return An informative message about the Exception.
     */
    virtual const char * what() const throw() override { return INDEX_EXCEPTION_MESSAGE; };
};


#endif
