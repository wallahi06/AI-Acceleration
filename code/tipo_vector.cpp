#include <iostream> 
#include <vector> 
#include <cstdlib>
#include <time.h>


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

    Vector sum(Vector term_vector);
    Vector diff(Vector term_vector);
    Vector product(Vector term_vector);

private:
    int Row_size;
    int Col_size;
    int input_size;
};


// constructor of the Vector class
Vector::Vector(int itsRow, int itsCol) {

    Row_size = itsRow;
    Col_size = itsCol;

    input_size = itsRow * itsCol;
    input_vector.resize(input_size);

}


// member of the Vector class that prints the structure of the vector
void Vector::show() {
    for (int i = 0; i < input_size; i++) {
        if (i % Col_size == 0 && i != 0) {
            std::cout << std::endl << std::endl;
        }
        std::cout << input_vector[i] << "  ";
    }
    std::cout << std::endl << std::endl << std::endl;
}


// prints the dimension and size of the given vector
void Vector::dim() {
    std::cout << Row_size << "x" << Col_size << std::endl;
}


// member of the Vector class that returns a vector of zeros
std::vector<int> Vector::zeros() {
    for (int i = 0; i < input_size; i++) {
        input_vector[i] = 0;
    }

    return input_vector;
}


// member of the Vector class that returns a vector of ones
std::vector<int> Vector::ones() {
    for (int i = 0; i < input_size; i++) {
        input_vector[i] = 1;
    }

    return input_vector;
}


//member of the Vector class that returns a vector of random values
std::vector<int> Vector::random(int size) {

    for (int i = 0; i < input_size; i++) {
        input_vector[i] = rand() % size;
    }

    return input_vector;
}


// member of the Vector class that adds vector1 with vector2
Vector Vector::sum(Vector term_vector) {

    Vector output_vector(Row_size, Col_size);
    output_vector.zeros();


    if (Col_size == term_vector.Col_size && Row_size == term_vector.Row_size) {

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

    Vector output_vector(Row_size, Col_size);
    output_vector.zeros();

    if (Col_size == term_vector.Col_size && Row_size == term_vector.Row_size) {

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

    Vector output_vector(Row_size, term_vector.Col_size);
    output_vector.zeros();

    // check if the columns of vector 1 is the same as the rows of vector 2
    if (Col_size == term_vector.Row_size) {

        for (int i = 0; i < Row_size; i++) {
            for (int j = 0; j < term_vector.Col_size; j++) {
                for (int k = 0; k < term_vector.Row_size; k++) {

                    // we cast the 4 byte values into an 8 byte value to avoid overflow
                    long long int casted_i = static_cast<int>(i);
                    long long int casted_k = static_cast<int>(k);

                    //we iterate over all the values of both vectors and multiplies them with each other
                    output_vector.input_vector[casted_i * term_vector.Col_size + j] += input_vector[casted_i * Col_size + k] * term_vector.input_vector[casted_k * term_vector.Col_size + j];
                }
            }
        }
    }
    else {
        throw std::invalid_argument("invalid size, cant combine different dimensions");
    }


    return output_vector;

}
