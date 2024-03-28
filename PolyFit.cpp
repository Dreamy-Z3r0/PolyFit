#include "PolyFit.h"

PolyFit::PolyFit(double* X, double* Y, int dataSpace) {
	this->X = X;
	this->Y = Y;

	this->dataSpace = dataSpace;
}

double* PolyFit::fit(int polynomialDegree) {
	this->polynomialDegree = polynomialDegree;

	// A and B matrices where A * coefficients = B
	double *A = new double[(polynomialDegree + 1) * (polynomialDegree + 1)]; 
	double *B = new double[polynomialDegree + 1];
	initiate_components(A, B);

	// Initiate inverse of A
	double* A_inv = new double[(polynomialDegree + 1) * (polynomialDegree + 1)];

	// Construct inverse of A
	SquareMatrix matrixInstance(A, polynomialDegree + 1);
	A_inv = matrixInstance.inv();

	matrixInstance.~SquareMatrix();
	delete[] A;

	// Calculate the coefficients
	coefficients = dot_product(A_inv, B, polynomialDegree + 1);

	delete[] A_inv;
	delete[] B;
	
	return coefficients;
}

double PolyFit::RMSE() {
	double RMS_error = 0;
	for (int i = 0; i < dataSpace; i += 1) {
		double Y_fit = 0;

		for (int j = polynomialDegree; j >= 0; j -= 1) {
			Y_fit += pow(X[i], j) * coefficients[j];
		}

		RMS_error += pow(Y_fit - Y[i], 2);
	}

	RMS_error /= dataSpace;
	RMS_error = sqrt(RMS_error);

	return RMS_error;
}

// Construct necessary matrices following the least square method
void PolyFit::initiate_components(double* A, double* B) {
	/* Construct matrix A */

	// Entries of A
	int N = polynomialDegree * 2 + 1;
	double *A_list = new double[N];
	for (int i = 0; i < N; i += 1) {
		if (0 == i) A_list[i] = (double)dataSpace;
		else {
			A_list[i] = 0;
			for (int x_index = 0; x_index < dataSpace; x_index += 1) {
				A_list[i] += pow(X[x_index], i);
			}
		}
	}

	// Populate A from A_list
	N = polynomialDegree + 1;
	for (int y = 0; y < N; y += 1) {
		for (int x = 0; x < N; x += 1) {
			A[y * N + x] = A_list[x + y];
		}
	}

	// Delete A_list[] (no longer of use)
	delete[] A_list;

	/* Construct matrix B */
	for (int y = 0; y <= polynomialDegree; y += 1) {
		B[y] = 0;
		for (int i = 0; i < dataSpace; i += 1) {
			B[y] += (pow(X[i], y) * Y[i]);
		}
	}
}

// Calculate the dot product matrixA * matrixB
// Assumptions: matrixA is a square matrix of N*N, and matrixB is a dimensional matrix of N*1
// N = polynomialDegree + 1
double* PolyFit::dot_product(double* matrixA, double* matrixB, int N) {
	double* output = new double[N];

	for (int y = 0; y < N; y += 1) {
		output[y] = 0;
		for (int x = 0; x < N; x += 1) {
			output[y] += matrixA[y * N + x] * matrixB[x];
		}
	}

	return output;
}
