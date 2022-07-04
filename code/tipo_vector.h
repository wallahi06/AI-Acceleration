#pragma once
#include <iostream>
#include <vector>


class Vector {
public:
    // Constructor and destructor definition
    Vector(int itsRow, int itsCol);
    ~Vector() {};

    std::vector<int> input_vector;

    // methods for getting information about your vectors
    void show();
    void dim();

    // methods for creating and structuring vectors
    std::vector<int> zeros();
    std::vector<int> ones();
    std::vector<int> random(int size = 100);
    std::vector<int> fill(std::vector<int> set_vector);

    // methods for calculations of the vectors
    Vector sum(Vector term_vector);
    Vector diff(Vector term_vector);
    Vector product(Vector term_vector);
    Vector divide(signed int denominator);
    Vector pow(signed int exponent);

private:
    int row_size;
    int col_size;
    int input_size;
};


