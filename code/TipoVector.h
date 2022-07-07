/* 
* TipoVector.h
* created by: Liam Nordvall togheter with TipoAI 2022-07-07
* all resources is under MIT license and free to use for everyone, 
* read more on https://github.com/wallahi06/tipoacc
*/


#pragma once

#include <iostream>
#include <string>
#include <vector>

#ifndef TIPO_VECTOR_H
#define TIPO_VECTOR_H


/*
* the Vector class conatins all necessary methods for matrix and vector calculations,
* it also provides easy to use tools for deeplearning and is mainly used to accelerate
* large matrix calculations using the Tipo library. 
*/
template<class dtype>
class Vector {
public:
    // Constructor and destructor definition
    Vector(unsigned int itsRowSize, unsigned int itsColSize);
    ~Vector() {};

    std::vector<dtype> input_vector;

    // methods for getting information about your vectors
    void show();
    void dim();

    // methods for creating and structuring vectors
    std::vector<dtype> zeros();
    std::vector<dtype> ones();
    std::vector<dtype> random(signed int interval = 100);
    std::vector<dtype> fill(std::vector<dtype> set_vector);

    // methods for calculations of the vectors
    Vector<dtype> sum(Vector<dtype> term_vector);
    Vector<dtype> diff(Vector<dtype> term_vector);
    Vector<dtype> product(Vector<dtype> term_vector);
    Vector<dtype> divide(signed int denominator);
    Vector<dtype> pow(signed int exponent);

private:
    unsigned int row_size;
    unsigned int col_size;
    unsigned int input_size;
};


// constructor of the Vector class
template<class dtype>
Vector<dtype>::Vector(unsigned int itsRowSize, unsigned int itsColSize) {

    row_size = itsRowSize;
    col_size = itsColSize;

    input_size = itsRowSize * itsColSize;
    input_vector.resize(input_size);

}


// member of the Vector class that prints the structure of the vector
template<class dtype>
void Vector<dtype>::show() {
    for (unsigned int i = 0; i < input_size; i++) {
        if (i % col_size == 0 && i != 0) {
            std::cout << std::endl << std::endl;
        }
        std::cout << input_vector[i] << "  ";
    }
    std::cout << std::endl << std::endl << std::endl;
}


// prints the dimension and size of the given vector
template<class dtype>
void Vector<dtype>::dim() {
    std::cout << row_size << "x" << col_size << std::endl;
}


// member of the Vector class that returns a vector of zeros
template<class dtype>
std::vector<dtype> Vector<dtype>::zeros() {
    if (col_size > 0 && row_size > 0) {
        for (unsigned int i = 0; i < input_size; i++) {
            input_vector[i] = 0;
        }
    }
    else {
        throw "invalid size, cant make an vector with dim(0)";
    }

    return input_vector;
}


// member of the Vector class that returns a vector of ones
template<class dtype>
std::vector<dtype> Vector<dtype>::ones() {
    if (col_size > 0 && row_size > 0) {
        for (unsigned int i = 0; i < input_size; i++) {
            input_vector[i] = 1;
        }
    }
    else {
        throw "invalid size, cant make an vector with dim(0)";
    }

    return input_vector;
}


//member of the Vector class that returns a vector of random values
template<class dtype>
std::vector<dtype> Vector<dtype>::random(signed int interval) {

    if (col_size > 0 && row_size > 0) {
        for (unsigned int i = 0; i < input_size; i++) {
            input_vector[i] = rand() % interval;
        }
    }
    else {
        throw "invalid size, cant make an vector with dim(0)";
    }

    return input_vector;
}



// member of the Vector class that return a vector of set values
template<class dtype>
std::vector<dtype> Vector<dtype>::fill(std::vector<dtype> set_vector) {
    if (input_size <= set_vector.size()) {
        for (unsigned int i = 0; i < input_size; i++) {

            // we iterate over all the values in the set_vector and import them into the input_vector
            input_vector[i] = set_vector[i];
        }
    }
    else {
        throw std::invalid_argument("invalid size, use a proper size for your vector to import all the values");
    }


    return input_vector;
}


// member of the Vector class that adds vector1 with vector2
template<class dtype>
Vector<dtype> Vector<dtype>::sum(Vector<dtype> term_vector) {

    Vector<dtype> output_vector(row_size, col_size);
    output_vector.zeros();


    if (col_size == term_vector.col_size && row_size == term_vector.row_size) {

        for (unsigned int i = 0; i < input_size; i++) {

            //we iterate over all the values of both vectors and add them each other
            output_vector.input_vector[i] = input_vector[i] + term_vector.input_vector[i];
        }

    }
    else {
        throw std::invalid_argument("invalid size, cant combine different dimensions");
    }

    return output_vector;

}


// member of the Vector class that subtracts vector1 with vector2
template<class dtype>
Vector<dtype> Vector<dtype>::diff(Vector<dtype> term_vector) {

    Vector<dtype> output_vector(row_size, col_size);
    output_vector.zeros();

    if (col_size == term_vector.col_size && row_size == term_vector.row_size) {

        for (unsigned int i = 0; i < input_size; i++) {

            //we iterate over all the values of both vectors and subtract them from each other
            output_vector.input_vector[i] = input_vector[i] - term_vector.input_vector[i];
        }
    }
    else {
        throw std::invalid_argument("invalid size, cant combine different dimensions");
    }

    return output_vector;

}


// member of the Vector class that multiplies vector1 with vector2
template<class dtype>
Vector<dtype> Vector<dtype>::product(Vector<dtype> term_vector) {

    Vector<dtype> output_vector(row_size, term_vector.col_size);
    output_vector.zeros();

    // check if the columns of vector 1 is the same as the rows of vector 2
    if (col_size == term_vector.row_size) {

        for (unsigned int i = 0; i < row_size; i++) {
            for (unsigned int j = 0; j < term_vector.col_size; j++) {
                for (unsigned int k = 0; k < term_vector.row_size; k++) {

                    // we cast the 4 byte values into an 8 byte value to avoid overflow
                    long long int casted_i = static_cast<int>(i);
                    long long int casted_k = static_cast<int>(k);

                    // iterates over all the values of both vectors and multiplies them with each other
                    output_vector.input_vector[casted_i * term_vector.col_size + j] += input_vector[casted_i * col_size + k] * term_vector.input_vector[casted_k * term_vector.col_size + j];
                }
            }
        }
    }
    else {
        throw std::invalid_argument("invalid size, cant combine different dimensions");
    }

    return output_vector;

}


// member of the Vector class that divides all values in the vector by the denominator
template<class dtype>
Vector<dtype> Vector<dtype>::divide(signed int denominator) {

    Vector<dtype> output_vector(row_size, col_size);
    output_vector.zeros();

    if (denominator != 0) {
        for (unsigned int i = 0; i < input_size; i++) {
            // iterates over all the values and divides them by the given denominator
            output_vector.input_vector[i] = input_vector[i] / denominator;
        }
    }
    else {
        throw std::invalid_argument("invalid denominator, cant devide by zero");
    }

    return output_vector;
}


// member of the Vector class that powers all the values in the vector by the exponent
template<class dtype>
Vector<dtype> Vector<dtype>::pow(signed int exponent) {

    Vector<dtype> output_vector(row_size, col_size);
    output_vector.ones();

    for (unsigned int i = 0; i < input_size; i++) {
        for (signed int j = 0; j < exponent; j++) {
            // iterates over all the values and multiply them by itself j times
            output_vector.input_vector[i] *= input_vector[i];
        }
    }

    return output_vector;
}


#endif /* TIPO_VECTOR_H */
