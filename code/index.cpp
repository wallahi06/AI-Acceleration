#include <iostream> 
#include <vector> 


void error_handler(int error_code);

class Vector {
    public:
        Vector(unsigned int itsRow, unsigned int itsCol);
        ~Vector() {};
        
        std::vector<int> input_vector;

        void show();
        
        std::vector<int> zeros();
        std::vector<int> ones();
        std::vector<int> random(unsigned int i);
        
        Vector sum(Vector term_vector);
        Vector diff(Vector term_vector);
    
        
    private:
        unsigned int Row_size;
        unsigned int Col_size;
        unsigned int input_size;
}; 


// constructor of the Vector class
Vector::Vector(unsigned int itsRow, unsigned int itsCol) {
    
    Row_size = itsRow;
    Col_size = itsCol;
    
    input_size = itsRow * itsCol;
    input_vector.resize(input_size);
    
}


void Vector::show() {
    for (unsigned int i = 0; i < input_size; i++) {
        if (i % Col_size == 0 && i != 0) {
            std::cout << std::endl << std::endl;
        }
        std::cout << input_vector[i] << "  ";
    }
    std::cout << std::endl << std::endl << std::endl;
}


// member of the Vector class that returns a vector of zeros
std::vector<int> Vector::zeros() {
    for (unsigned int i = 0; i < input_size; i++) {
        input_vector[i] = 0;
    }
    
    return input_vector;
}

// member of the Vector class that returns a vector of ones
std::vector<int> Vector::ones() {
    for (unsigned int i = 0; i < input_size; i++) {
        input_vector[i] = 1; 
    }
    
    return input_vector;
}

//member of the Vector class that returns a vector of random values
std::vector<int> Vector::random(unsigned int size = 100) {
    for (unsigned int i = 0; i < input_size; i++) {
        input_vector[i] = rand() % size;
    }
    
    return input_vector;
}



// member of the Vector class that adds vector1 with vector2
Vector Vector::sum(Vector term_vector) {
    
    Vector output_vector(Row_size, Col_size);
    output_vector.zeros();
    
    try {
        if (Col_size == term_vector.Col_size && Row_size == term_vector.Row_size) {
            for (unsigned int i = 0; i < input_size; i++) {
                output_vector.input_vector[i] = input_vector[i] + term_vector.input_vector[i];
                }
        } else {
            throw std::runtime_error("invalid size, cant combine different dimensions");
        }
    } catch (std::runtime_error &error) {
        std::cout << "Error occured: " << error.what() << std::endl;
    }
    
    return output_vector;
}


// member of the Vector class that subtracts vector1 with vector2
Vector Vector::diff(Vector term_vector) {
    
    Vector output_vector(Row_size, Col_size);
    output_vector.zeros();

    try {
        if (Col_size == term_vector.Col_size && Row_size == term_vector.Row_size) {
            for (unsigned int i = 0; i < input_size; i++) {
                output_vector.input_vector[i] = input_vector[i] - term_vector.input_vector[i];
                }
        } else {
            throw std::runtime_error("invalid size, cant combine different dimensions");
        }
    } catch (std::runtime_error &error) {
        std::cout << "Error occured: " << error.what() << std::endl;
    }
    
    return output_vector;
}


int main() {
    return 0;
}

