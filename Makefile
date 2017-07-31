CXX= g++
CXXFLAGS= -c -Wextra -Wall -Wvla -pthread -std=c++11 -DNDEBUG
CODEFILES= ex3.tar Matrix.h Matrix.hpp MatrixException.h Makefile README


# Default
default: GenericMatrixDriver
	./GenericMatrixDriver


# Executables
GenericMatrixDriver: GenericMatrixDriver.o Complex.o
	$(CXX) GenericMatrixDriver.o Complex.o -lpthread -o GenericMatrixDriver


# Object Files
Complex.o: Complex.cpp Complex.h
	$(CXX) $(CXXFLAGS) Complex.cpp -o Complex.o

GenericMatrixDriver.o: GenericMatrixDriver.cpp Matrix.h Complex.h
	$(CXX) $(CXXFLAGS) GenericMatrixDriver.cpp -o GenericMatrixDriver.o


# GCH Files
Matrix: Matrix.hpp.gch

Matrix.hpp.gch: Matrix.hpp Matrix.h MatrixException.h Complex.h
	$(CXX) $(CXXFLAGS) Matrix.hpp -o Matrix.hpp.gch


# tar
tar:
	tar -cvf $(CODEFILES)


# Other Targets
clean:
	-rm -vf *.o Matrix.hpp.gch GenericMatrixDriver



