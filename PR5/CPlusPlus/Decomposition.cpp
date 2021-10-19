#include "../Headers/Decomposition.h"
#include <cassert>


// 1) Constructors:
Decomposition::Decomposition(const Matrix& any)
{
    // 0. Checking of sizes. If matrix isn't square then error out!
    assert((any.get_cSize() == any.get_rSize()) && "ERROR_MATRIX_IS_NOT_SQUARE");
    assert((any.get_cSize() != 0) && "ERROR_MATRIX_IS_EMPTY");

    // 1. The data is set there:
    this->low = Matrix(any.get_cSize(), any.get_cSize());
    this->up = Matrix(any.get_cSize(), any.get_cSize());

    for (int i = 0; i < any.get_cSize(); ++i)
        this->up.set_elem(0, i, any.get_elem(0, i));

    for (int i = 0; i < any.get_cSize(); ++i)
        this->low.set_elem(i, 0, any.get_elem(i, 0) / any.get_elem(0, 0));


    for (int i = 1; i < any.get_cSize(); ++i)
        for (int j = i; j < any.get_cSize(); ++j)
        {
            double sumUp = 0;
            double sumLow = 0;
            for (int k = 0; k < i; ++k)
            {
                sumUp += this->low.get_elem(i, k) * this->up.get_elem(k, j);
                sumLow += this->low.get_elem(j, k) * this->up.get_elem(k, i);
            }
            this->up.set_elem(i, j, any.get_elem(i, j) - sumUp);
            this->low.set_elem(j, i, (any.get_elem(j, i) - sumLow) / this->up.get_elem(i, i));
        }
    //this->values = { 10.0, -0.1, 1.0, 10.1 };   //  <- Заменить на LU разложение
    // По умолчанию: (L\U) = { 10.0, -0.1, 1.0, 10.1 } - LU разложение для матрицы А = {10.0, -1.0, 1.0, 10.0}
}


// 2) Destructor:
Decomposition::~Decomposition() {}


void Get_LU_Matrix(const Matrix&, Matrix&, Matrix&);
// 3) Geters and seters:
const double Decomposition::get_elemL(unsigned int row, unsigned int col) const
{
    // 0. Checking of the indexes!
    assert(((row < this->low.get_rSize()) && (col < this->low.get_cSize())) && "ERROR_MATRIX_INDEX_IS_OUT_SIZE");

    return low.get_elem(row, col);
}


const double Decomposition::get_elemU(unsigned int row, unsigned int col) const
{
    // 0. Checking of the indexes!
    assert(((row < this->up.get_rSize()) && (col < this->up.get_cSize())) && "ERROR_MATRIX_INDEX_IS_OUT_SIZE");

    return up.get_elem(row, col);
}

const double Decomposition::get_size() const
{
    return this->low.get_cSize();
}

const Matrix Decomposition::get_L() const
{    
    return low;
}

const Matrix Decomposition::get_U() const
{
    return up;
}