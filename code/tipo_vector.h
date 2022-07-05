#pragma once
#include <iostream>
#include <vector>


// The Vector class takes care of everything related to Tipo's vector/matrix operations, such as multiplicaiton 
// of vectors and easily creating them using one of our pre-made methods for filling your vector with random 
// values, zeros, ones or your own values using .fill
class Vector {
public:
    // Constructor and destructor definition
    Vector(unsigned int itsRowSize, unsigned int itsColSize);
    ~Vector() {};

    std::vector<double> input_vector;

    // methods for getting information about your vectors
    void show();
    void dim();

    // methods for creating and structuring vectors
    std::vector<double> zeros();
    std::vector<double> ones();
    std::vector<double> random(signed int interval = 100);
    std::vector<double> fill(std::vector<double> set_vector);

    // methods for calculations of the vectors
    Vector sum(Vector term_vector);
    Vector diff(Vector term_vector);
    Vector product(Vector term_vector);
    Vector divide(signed int denominator);
    Vector pow(signed int exponent);

private:
    unsigned int row_size;
    unsigned int col_size;
    unsigned int input_size;
};


