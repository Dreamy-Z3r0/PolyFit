#pragma once

#include <algorithm>

class SquareMatrix {
public:
	SquareMatrix(double* matrix, int dimension);
	~SquareMatrix();

	double* inv();		// Calculate inverse of matrix

private:
	double* matrix;		// Input square matrix
	int dimension;		// Dimension of a side of the matrix

	double* inverse;		// Inverse of matrix (if any)
	bool noInverse;		// 'true' if matrix has no inverse

	void create_identity_matrix(double *identity);		// Create an identity matrix

	// Inverse operations
	void lower_triangular_matrix(double * tempMatrix, int x);
	void upper_triangular_matrix(double* tempMatrix);

	// Matrix operations
	void swap_rows(double* workingSquareMatrix, int y1, int y2);	// Swap rows y1 and y2
	void normalise_row(double* workingSquareMatrix, int y, double factor);	// Normalise row by a factor
	void add_rows(double* workingSquareMatrix, int y0, int y1, double y1_factor = 1);	// y0 = y0 + y1 * y1_factor
};

