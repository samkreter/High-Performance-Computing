#include "MatrixMultiply.hpp"


#include <iostream>
#include <exception>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <numeric>
#include <stdlib.h>

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


	float** lef = new float*[lhs.size1()];

	for(int i = 0; i < lhs.size1(); i++){
		lef[i] = new float[lhs.size2()];
	}

	for(int i = 0; i < lhs.size1(); i++){
		for(int j = 0; j < lhs.size2(); j++){
			lef[i][j] = lhs(i,j);
		}
	}

	float** right = new float*[rhs.size1()];

	for(int i = 0; i < rhs.size1(); i++){
		right[i] = new float[rhs.size2()];
	}

	for(int i = 0; i < rhs.size1(); i++){
		for(int j = 0; j < rhs.size2(); j++){
			right[i][j] = rhs(i,j);
		}
	}




	int row = lhs.size1();

	for(int i = 0; i < row; i++){
		for(int j = 0; j < rhs.size2(); j++){
			int sum = 0;
			for(int k = 0; k < lhs.size2(); k++){

				sum += lef[i][k] * right[k][j];
			}

			result(i,j) = sum;

		}
	}

	for(int i = 0; i < rhs.size1(); i++){
		delete[] right[i];
	}

	for(int i = 0; i < lhs.size1(); i++){
		delete[] lef[i];
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

