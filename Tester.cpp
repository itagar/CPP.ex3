#include <iostream>
#include "Matrix.h"

int main()
{
    try
    {
        // Checking Matrix creation with a given vector.
        std::cout << "Creating a new Matrix of ints of size 3x3 with a given cells..." << std::endl;
        std::vector<int> vecInt1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        Matrix<int> matrixInt1(3, 3, vecInt1);
        std::cout << matrixInt1 << std::endl;

        matrixInt1.setParallel(true);
        matrixInt1 + matrixInt1;


        // Checking assignment operator.
        std::cout << "Assign to a Matrix of size 4x5 the newly Matrix of ints of size 3x3..." << std::endl;
        Matrix<int> matrixAssignment(4, 5);
        matrixAssignment = matrixInt1;
        std::cout << matrixAssignment << std::endl;

        std::cout << "----------------------------------------------------------------------\n" << std::endl;

        try
        {
            // Checking Matrix creation with only rows and cols (all cells should be zero).
            std::cout << "Creating a default Matrix of ints of size 5x4..." << std::endl;
            Matrix<int> matrixInt2(5, 4);
            std::cout << matrixInt2 << std::endl;
            // Checking subtraction between different dimensions (an Exception should be thrown).
            std::cout << "Attempt to perform subtraction between this 5x4 and the assigned 3x3..." << std::endl;
            std::cout << (matrixInt2 - matrixAssignment) << std::endl;
        }
        catch (MatrixException& e)
        {
            std::cout << "An Exception caught: " << e.what() << std::endl;
        }

        std::cout << "----------------------------------------------------------------------\n" << std::endl;

        // Checking the Copy Constructor.
        std::cout << "Using the copy constructor to copy the first 3x3 Matrix..." << std::endl;
        Matrix<int> matrixInt2(matrixInt1);
        std::cout << matrixInt2 << std::endl;
        // Checking the cell access operator.
        std::cout << "Changing this Matrix data in cell (1,2) to 65..." << std::endl;
        matrixInt2(1, 2) = 65;
        std::cout << "Changing this Matrix data in cell (2,0) to -11..." << std::endl;
        matrixInt2(2, 0) = -11;
        std::cout << matrixInt2 << std::endl;
        // Checking the rows getter.
        std::cout << "Get number of rows: ";
        std::cout << matrixInt2.rows() << std::endl;
        // Checking the multithread mode (a message should appear for mode changing).
        std::cout << "Switching to multithread..." << std::endl;
        matrixInt1.setParallel(true);
        // Checking the addition operation.
        std::cout << "Attempt to perform addition between these two 3x3 Matrices (original with copy)..." << std::endl;
        std::cout << (matrixInt2 + matrixInt1) << std::endl;

        std::cout << "----------------------------------------------------------------------\n" << std::endl;

        // Checking a non-square Matrix.
        std::cout << "Creating a new Matrix of ints of size 4x3 with a given cells..." << std::endl;
        std::vector<int> vecInt2 = {23, -7, 0, 0, 3, 25, -5, 94, -36, 81, 17, -42};
        Matrix<int> matrixInt3(4, 3, vecInt2);
        std::cout << matrixInt3 << std::endl;
        std::cout << "Check if square Matrix: ";
        std::cout << std::boolalpha << matrixInt3.isSquareMatrix() << std::endl;

        // Checking the Move Constructor.
        std::cout << "Using the Move constructor on these 4x3 Matrix..." << std::endl;
        Matrix<int> matrixInt4(std::move(matrixInt3));
        std::cout << matrixInt4 << std::endl;

        // Checking the non-equality operator (should be false).
        std::cout << "Check non-equality with the move and original: ";
        std::cout << std::boolalpha << (matrixInt4 != matrixInt3) << std::endl;

        try
        {
            // Checking multiplication between bad dimensions (an Exception should be thrown).
            std::cout << "Attempt to perform multiplication of this Matrix with itself (4x3 with 4x3)..." << std::endl;
            std::cout << (matrixInt3 * matrixInt3) << std::endl;
        }
        catch (MatrixException& e)
        {
            std::cout << "An Exception caught: " << e.what() << std::endl;
        }

        // Checking the transpose.
        std::cout << "Transpose this Matrix..." << std::endl;
        std::cout << matrixInt3.trans() << std::endl;

        // Checking the equality operator (should be false).
        std::cout << "Check equality with transpose and original: ";
        std::cout << std::boolalpha << (matrixInt3 == matrixInt3.trans()) << std::endl;

        // Checking the double switch the thread mode (only one message should appear).
        std::cout << "Switching to non multithread..." << std::endl;
        matrixInt1.setParallel(false);
        std::cout << "Switching again to non multithread..." << std::endl;
        matrixInt1.setParallel(false);

        // Checking multiplication.
        std::cout << "Attempt to perform multiplication between the transpose and the original (4x3 with 3x4)..." << std::endl;
        std::cout << (matrixInt3 * matrixInt3.trans()) << std::endl;

        std::cout << "------------------------------- END ----------------------------------\n" << std::endl;

    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}