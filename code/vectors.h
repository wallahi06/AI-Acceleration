#include <iostream>
#include <vector>

class Vector {
public:
    // Constructor and destructor definition
    Vector(unsigned int itsRow, unsigned int itsCol);
    ~Vector() {};

    std::vector<int> input_vector;

    void show();
    void dim();


    std::vector<int> zeros();
    std::vector<int> ones();
    std::vector<int> random(unsigned int size);

    Vector sum(Vector term_vector);
    Vector diff(Vector term_vector);
    Vector product(Vector term_vector);

private:
    unsigned int Row_size;
    unsigned int Col_size;
    unsigned int input_size;
};







