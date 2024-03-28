// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <math.h>

#include "Matrix.h"
#include "PolyFit.h"

#define POLYNOMIAL_DEGREE 3

int dataSpace = 24;
double X[] = { 0,32,64,96,128,160,192,224,256,288,320,352,384,416,448,480,512,544,576,608,640,672,704,736 };
double Y[] = {
    63.66888835, 80.5688975, 99.66888835, 119.2688944, 140.6688883, 164.2688906,
    186.0688899, 208.6688912, 227.8688915, 245.9688914, 261.8688929, 276.9688914,
    289.9688914, 302.5688899, 314.6688883, 325.1688883, 334.9688914, 344.9688914,
    352.8688853, 361.1688883, 369.1688883, 376.6688883, 383.3688853, 390.6688883
};

int main() {
    double* coefficients;
    double RMS_error;

    PolyFit sample(X, Y, dataSpace);
    coefficients = sample.fit(POLYNOMIAL_DEGREE);
    RMS_error = sample.RMSE();

    std::cout << "\nCoefficients:\n";
    for (int i = POLYNOMIAL_DEGREE; i >= 0; i -= 1) {
        std::cout << 'a' << i << " = " << coefficients[i] << std::endl;
    }

    std::cout << "\nRMS error: " << RMS_error << std::endl;
}
