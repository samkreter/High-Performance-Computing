#include "MatrixMultiply.hpp"


#include <iostream>
#include <exception>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <numeric>
#include <stdlib.h>

# define MATRIXPOS(rowSize , row, col) (rowSize * row) + col

scottgs::MatrixMultiply::MatrixMultiply()
{
	;
}

scottgs::MatrixMultiply::~MatrixMultiply()
{
	;
}


scottgs::FloatMatrix scottgs::MatrixMultiply::operator()(const scottgs::FloatMatrix& lhs, const scottgs::FloatMatrix& rhs) const
{
	// Verify acceptable dimensions
	if (lhs.size2() != rhs.size1())
		throw std::logic_error("matrix incompatible lhs.size2() != rhs.size1()");

	scottgs::FloatMatrix result(lhs.size1(),rhs.size2());

	int lhsSize1 = lhs.size1();
	int lhsSize2 = lhs.size2();
	int rhsSize1 = rhs.size1();
	int rhsSize2 = rhs.size2();
	int sum = 0;


	float* lef = new float[lhsSize1*lhsSize2];

	for(int i = 0; i < lhsSize1; i++){
		for(int j = 0; j < lhsSize2; j++){
			lef[MATRIXPOS(lhsSize2,i,j)] = lhs(i,j);
		}
	}

	float** right = new float*[rhsSize1];

	for(int i = 0; i < rhsSize1; i++){
		right[i] = new float[rhsSize2];
	}

	for(int i = 0; i < rhsSize1; i++){
		for(int j = 0; j < rhsSize2; j++){
			right[i][j] = rhs(i,j);
		}
	}



	for(int i = 0; i < lhsSize1; i++){
		for(int j = 0; j < rhsSize2; j++){
			sum = 0;
			for(int k = 0; k < lhsSize2; k++){

				sum += lef[MATRIXPOS(lhsSize2,i,k)] * right[k][j];
			}

			result(i,j) = sum;

		}
	}

	for(int i = 0; i < rhsSize1; i++){
		delete[] right[i];
	}


	delete[] right;
	delete[] lef;

	return result;
}

scottgs::FloatMatrix scottgs::MatrixMultiply::multiply(const scottgs::FloatMatrix& lhs, const scottgs::FloatMatrix& rhs) const
{
	// Verify acceptable dimensions
	if (lhs.size2() != rhs.size1())
		throw std::logic_error("matrix incompatible lhs.size2() != rhs.size1()");

	return boost::numeric::ublas::prod(lhs,rhs);
}

