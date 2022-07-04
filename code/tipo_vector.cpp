// includes all necessarry libraries
#include <iostream> 
#include <vector> 
#include <cstdlib>
#include <time.h>


// The Vector class takes care of everything related to Tipo's vector/matrix operations, such as multiplicaiton of vectors and easily creating them using one of
// our pre-made methods for filling your vector with random values, zeros, ones or your own values using .fill
class Vector {
public:
    // Constructor and destructor definition
    Vector(int itsRow, int itsCol);
    ~Vector() {};

    std::vector<int> input_vector;

    void show();
    void dim();


    std::vector<int> zeros();
    std::vector<int> ones();
    std::vector<int> random(int size = 100);
    std::vector<int> fill(std::vector<int> set_vector);

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


// constructor of the Vector class
Vector::Vector(int itsRow, int itsCol) {

    row_size = itsRow;
    col_size = itsCol;

    input_size = itsRow * itsCol;
    input_vector.resize(input_size);

}


// member of the Vector class that prints the structure of the vector
void Vector::show() {
    for (int i = 0; i < input_size; i++) {
        if (i % col_size == 0 && i != 0) {
            std::cout << std::endl << std::endl;
        }
        std::cout << input_vector[i] << "  ";
    }
    std::cout << std::endl << std::endl << std::endl;
}


// prints the dimension and size of the given vector
void Vector::dim() {
    std::cout << row_size << "x" << col_size << std::endl;
}


// member of the Vector class that returns a vector of zeros
std::vector<int> Vector::zeros() {
    if (col_size > 0 && row_size > 0) {
        for (int i = 0; i < input_size; i++) {
            input_vector[i] = 0;
        }
    }
    else {
        throw "invalid size, cant make an vector with dim(0)";
    }

    return input_vector;
}


// member of the Vector class that returns a vector of ones
std::vector<int> Vector::ones() {  
    if (col_size > 0 && row_size > 0) {
        for (int i = 0; i < input_size; i++) {
            input_vector[i] = 1;
        }
    }
    else {
        throw "invalid size, cant make an vector with dim(0)";
    }

    return input_vector;
}


//member of the Vector class that returns a vector of random values
std::vector<int> Vector::random(int size) {
    
    // sets the seed of the random function to generate different numbers every iteration
    srand(time(NULL));

    if (col_size > 0 && row_size > 0) {
        for (int i = 0; i < input_size; i++) {
            input_vector[i] = rand() % size;
        }
    }
    else {
        throw "invalid size, cant make an vector with dim(0)";
    }

    return input_vector;
}



// member of the Vector class that return a vector of set values
std::vector<int> Vector::fill(std::vector<int> set_vector) {
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
Vector Vector::sum(Vector term_vector) {

    Vector output_vector(row_size, col_size);
    output_vector.zeros();


    if (col_size == term_vector.col_size && row_size == term_vector.row_size) {

        for (int i = 0; i < input_size; i++) {

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
Vector Vector::diff(Vector term_vector) {

    Vector output_vector(row_size, col_size);
    output_vector.zeros();

    if (col_size == term_vector.col_size && row_size == term_vector.row_size) {

        for (int i = 0; i < input_size; i++) {

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
Vector Vector::product(Vector term_vector) {

    Vector output_vector(row_size, term_vector.col_size);
    output_vector.zeros();

    // check if the columns of vector 1 is the same as the rows of vector 2
    if (col_size == term_vector.row_size) {

        for (int i = 0; i < row_size; i++) {
            for (int j = 0; j < term_vector.col_size; j++) {
                for (int k = 0; k < term_vector.row_size; k++) {

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
Vector Vector::divide(signed int denominator) {

    Vector output_vector(row_size, col_size);
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
Vector Vector::pow(signed int exponent) {

    Vector output_vector(row_size, col_size);
    output_vector.ones();

    for (unsigned int i = 0; i < input_size; i++) {
        for (unsigned int j = 0; j < exponent; j++) {
            // iterates over all the values and multiply them by itself j times
            output_vector.input_vector[i] *= input_vector[i];
        }
    }

    return output_vector;
}

