#include <iostream>
#include <vector>
#include <cstdlib>


class Vector {
    public:
        Vector(unsigned int itsCol, unsigned int itsRow);
        ~Vector() {};
        
        unsigned int input_size;
        std::vector<int> input_matrix;
        
        void show();
        
        // Functions for cretaing different types of matrixes
        std::vector<int> zeros();
        std::vector<int> ones();
        std::vector<int> random(unsigned int size);

        // Functions for calculations
        std::vector<int> sum(std::vector<int> term_vector);
        std::vector<int> diff(std::vector<int> term_vector);
        std::vector<int> product(std::vector<int> term_vector);

    private:
        unsigned int num_col;
        unsigned int num_row;

        
};

Vector::Vector(unsigned int itsCol, unsigned int itsRow) {
    num_col = itsCol;
    num_row = itsRow;
    input_size = num_col * num_row;
    input_matrix.resize(input_size);

}

// members of the Vector class that takes care of creating and formatting the matrices
std::vector<int> Vector::zeros() {
    for (unsigned int i = 0; i < input_size; i++) {
        input_matrix[i] = 0;
    }
    return input_matrix;
}

std::vector<int> Vector::ones() {
    for (unsigned int i = 0; i < input_size; i++) {
        input_matrix[i] = 1;
    }
    return input_matrix;
}

std::vector<int> Vector::random(unsigned int size = 100) {
    for (unsigned int i = 0; i < input_size; i++) {
        input_matrix[i] = rand() % size;
    }
    
    return input_matrix;
}


// Outputs the values oriented in the correct order for visulizing the matrices
void Vector::show() {
    for (unsigned int i = 0; i < input_size; i++) {
        if (i % num_col == 0 && i != 0) {
            std::cout << std::endl;
        }
        std::cout << input_matrix[i] << "  ";
        
    }
}

// members of the Vector class that takes care of the calculations
// returns the sum of vector1 and vector2
std::vector<int> Vector::sum(std::vector<int> term_vector) {
    
    Vector output_matrix(2, 2);
    output_matrix.zeros();
    
    for (unsigned int i = 0; i < input_size; i++) {
        output_matrix.input_matrix[i] = input_matrix[i] + term_vector[i];
    }
    return output_matrix.input_matrix;
}

// returns the difference between vector1 and vector2
std::vector<int> Vector::diff(std::vector<int> term_vector) {
    
    Vector output_matrix(2, 2);
    output_matrix.zeros();
    
    for (unsigned int i = 0; i < input_size; i++) {
        output_matrix.input_matrix[i] = input_matrix[i] - term_vector[i];
    }
    return output_matrix.input_matrix;
}

// returns the product of vector1 and vector2
std::vector<int> Vector::product(std::vector<int> term_vector) {
    Vector output_matrix(2, 2);
    output_matrix.zeros();
    
    for (unsigned int i = 0; i < 2; i++) {    
        for (unsigned int j = 0; j < 2; j++) {
            for (unsigned int k = 0; k < 2; k++) {
                output_matrix.input_matrix[i * 2 + j] += input_matrix[i * 2 + k] * term_vector[k * 2 + j];
            }
        }
    }
    
    return output_matrix.input_matrix;
}



int main() {
    
    Vector vector1(2, 2);
    Vector vector2(2, 2);
    Vector vector3(2, 2);
    
    vector1.ones();
    vector2.ones();
    
    
    vector3.input_matrix = vector1.product(vector2.input_matrix);
    vector3.show();
    
    return 0;
}
