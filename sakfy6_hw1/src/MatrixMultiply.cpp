#include "MatrixMultiply.hpp"


#include <iostream>
#include <exception>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <numeric>
#include <stdlib.h>

# define ROWMATRIXPOS(rowSize , row, col) (rowSize * row) + col
# define COLMATRIXPOS(colSize , row, col) (colSize * col) + row


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
	float sum = 0;


	const float* lef = &lhs(0,0);


	float* right = new float[rhsSize1*rhsSize2];
	const float * rightHolder = &rhs(0,0);

	for(int i = 0; i < rhsSize1; i++){
		for(int j = 0; j < rhsSize2; j++){
			right[COLMATRIXPOS(rhsSize1,i,j)] = rightHolder[ROWMATRIXPOS(rhsSize2,i,j)];
		}
	}


	for(int i = 0; i < lhsSize1; i++){
		for(int j = 0; j < rhsSize2; j++){
			sum = 0;
			for(int k = 0; k < lhsSize2; k++){

				sum += lef[ROWMATRIXPOS(lhsSize2,i,k)] * right[COLMATRIXPOS(rhsSize1,k,j)];
			}

			result(i,j) = sum;

		}
	}


	delete[] right;

	return result;
}

scottgs::FloatMatrix scottgs::MatrixMultiply::multiply(const scottgs::FloatMatrix& lhs, const scottgs::FloatMatrix& rhs) const
{
	// Verify acceptable dimensions
	if (lhs.size2() != rhs.size1())
		throw std::logic_error("matrix incompatible lhs.size2() != rhs.size1()");

	return boost::numeric::ublas::prod(lhs,rhs);
}

