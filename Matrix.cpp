#include "Matrix.h"

SquareMatrix::SquareMatrix(double* matrix, int dimension) {
	this->matrix = matrix;
	this->dimension = dimension;

	noInverse = false;
	inverse = new double[dimension * dimension];
}

SquareMatrix::~SquareMatrix() {

}

// Calculate inverse of matrix
double* SquareMatrix::inv() {
	// Create a copy of the original matrix
	double* matrix_cp = new double[dimension * dimension];
	std::copy(matrix, matrix + dimension * dimension, matrix_cp);
	
	// Initiate inverse as an identity matrix
	create_identity_matrix(inverse);

	// Handles lower triangular matrix
	for (int x = 0; x < dimension; x += 1) {
		lower_triangular_matrix(matrix_cp, x);
	}

	// Handles upper triangular matrix
	upper_triangular_matrix(matrix_cp);

	// Delete the copy after use
	delete[] matrix_cp;

	// Return the inverse
	return inverse;
}

// Create an identity matrix
void SquareMatrix::create_identity_matrix(double* identity) {
	for (int y = 0; y < dimension; y += 1) {
		for (int x = 0; x < dimension; x += 1) {
			identity[y * dimension + x] = (y == x ? 1 : 0);
		}
	}
}


/* Inverse operations */

// Handles lower triangular matrix: all values -> 0
void SquareMatrix::lower_triangular_matrix(double* tempMatrix, int x) {
	// Make sure the first element of the submatrix x*x is 1

	// Look for the first occurance of 1 in the first column of the x*x submatrix
	bool firstRowWithOne = false;
	int yPos = x;

	int zeroCount = 0;	// Additional: If the first column of the x*x submatrix contains only 0's,
						//			   the original matrix does not have an inverse.

	for (int y = x; y < dimension; y += 1) {
		double valueInCheck = tempMatrix[y * dimension + x];

		if (1 == valueInCheck) {
			firstRowWithOne = true;
			yPos = y;
			break;
		}

		if (0 == valueInCheck) {
			zeroCount += 1;
		}
	}

	// The first column of the x*x submatrix only contains 0's
	if (dimension - x == zeroCount) {
		noInverse = true;
		return;
	}

	// First occurance of 1 on the first column of the x*x submatrix found, but not on its first row
	if (x != yPos) {		// There's a row starting with 1
		swap_rows(tempMatrix, x, yPos);
		swap_rows(inverse, x, yPos);
	}
	
	// No occurance found
	if (!firstRowWithOne) {
		// Make sure the first value of the x*x submatrix is not 0
		if (0 == tempMatrix[x * dimension + x]) {
			for (int y = x + 1; y < dimension; y += 1) {
				if (0 != tempMatrix[y * dimension + x]) {
					swap_rows(tempMatrix, x, y);
					swap_rows(inverse, x, y);
					break;
				}
			}
		}

		// Make sure the first value of the x*x submatrix is 1
		double factor = tempMatrix[x * dimension + x];
		
		normalise_row(tempMatrix, x, factor);
		normalise_row(inverse, x, factor);
	}

	// Get all other values of the first column to 0's
	for (int y = x + 1; y < dimension; y += 1) {
		double factor = -tempMatrix[y * dimension + x] / tempMatrix[x * dimension + x];
		add_rows(tempMatrix, y, x, factor);
		add_rows(inverse, y, x, factor);
	}
}

// Handles upper triangular matrix: all values -> 0
void SquareMatrix::upper_triangular_matrix(double* tempMatrix) {
	for (int y = dimension - 2; y >= 0; y -= 1) {
		for (int x = dimension - 1; x > y; x -= 1) {
			double factor = -tempMatrix[y * dimension + x];
			add_rows(tempMatrix, y, x, factor);
			add_rows(inverse, y, x, factor);
		}
	}
}


/* Matrix operations */

// Swap rows y1 and y2
void SquareMatrix::swap_rows(double* workingSquareMatrix, int y1, int y2) {
	for (int x = 0; x < dimension; x += 1) {
		double temp = workingSquareMatrix[y1 * dimension + x];
		workingSquareMatrix[y1 * dimension + x] = workingSquareMatrix[y2 * dimension + x];
		workingSquareMatrix[y2 * dimension + x] = temp;
	}
}

// Normalise row by a factor
void SquareMatrix::normalise_row(double* workingSquareMatrix, int y, double factor) {
	for (int x = 0; x < dimension; x += 1) {
		workingSquareMatrix[y * dimension + x] /= factor;
	}
}

// Add row y1 to row y0 with a factor
void SquareMatrix::add_rows(double* workingSquareMatrix, int y0, int y1, double y1_factor) {
	for (int x = 0; x < dimension; x += 1) {
		workingSquareMatrix[y0 * dimension + x] += workingSquareMatrix[y1 * dimension + x] * y1_factor;
	}
}


