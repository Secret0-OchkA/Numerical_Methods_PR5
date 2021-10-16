#include "../Headers/Decomposition.h"
#include <cassert>


// 1) Constructors:
Decomposition::Decomposition(const Matrix& any)
{
    // 0. Checking of sizes. If matrix isn't square then error out!
    assert((any.get_cSize() == any.get_rSize()) && "ERROR_MATRIX_IS_NOT_SQUARE");
    assert((any.get_cSize() == 0) && "ERROR_MATRIX_IS_EMPTY");

    // 1. The data is set there:
    
    this->values = any;
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
    assert(((row < this->values.get_rSize()) && (col < this->values.get_cSize())) && "ERROR_MATRIX_INDEX_IS_OUT_SIZE");
    
    Matrix up, low;
    Get_LU_Matrix(this->values, low, up);

    return low.get_elem(row, col);
}


const double Decomposition::get_elemU(unsigned int row, unsigned int col) const
{
    // 0. Checking of the indexes!
    assert(((row < this->values.get_rSize()) && (col < this->values.get_cSize())) && "ERROR_MATRIX_INDEX_IS_OUT_SIZE");

    Matrix up, low;
    Get_LU_Matrix(this->values, low, up);

    return up.get_elem(row, col);
}

const double Decomposition::get_size() const
{
    return this->values.get_cSize();
}

const Matrix Decomposition::get_L() const
{
    Matrix up, low;
    Get_LU_Matrix(this->values, low, up);
    
    return low;
}

const Matrix Decomposition::get_U() const
{
    Matrix up, low;
    Get_LU_Matrix(this->values, low, up);

    return up;
}

void Get_LU_Matrix(const Matrix& in_A, Matrix& out_low, Matrix& out_up)
{

    out_low = Matrix(in_A.get_cSize(), in_A.get_cSize());
    out_up = Matrix(in_A.get_cSize(), in_A.get_cSize());

    for (int i = 0; i < in_A.get_cSize(); ++i)
        out_up.set_elem(0, i, in_A.get_elem(0, i));

    for (int i = 0; i < in_A.get_cSize(); ++i)
        out_low.set_elem(i, 0, in_A.get_elem(i, 0) / in_A.get_elem(0, 0));


    for (int i = 1; i < in_A.get_cSize(); ++i)
        for (int j = i; j < in_A.get_cSize(); ++j)
        {
            double sumout_up = 0;
            double sumout_low = 0;
            for (int k = 0; k < i; ++k)
            {
                sumout_up += out_low.get_elem(i, k) * out_up.get_elem(k, j);
                sumout_low += out_low.get_elem(j, k) * out_up.get_elem(k, i);
            }
            out_up.set_elem(i, j, in_A.get_elem(i, j) - sumout_up);
            out_low.set_elem(j, i, (in_A.get_elem(j, i) - sumout_low) / out_up.get_elem(i, i));
        }
}