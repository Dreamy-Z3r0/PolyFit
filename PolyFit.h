#pragma once

#include <math.h>
#include "Matrix.h"

class PolyFit {
public:
	PolyFit(double* X, double* Y, int dataSpace);

	double* fit(int polynomialDegree);
	double RMSE();

private:
	double* X;
	double* Y;

	int dataSpace;
	double* coefficients;
	int polynomialDegree;

	void initiate_components(double* A, double* B);	// Construct necessary matrices
	double* dot_product(double* matrixA, double* matrixB, int N);		// Calculate the dot product matrixA * matrixB
};

