#include "../Headers/Matrix.h"
#include <cassert>



//prototipe for column_reset
void add(Matrix&, unsigned int, unsigned int, const double);

//+++++++++++++++++++++++++++++++++++//                              
//           OTHER FUNCITONS         //
//+++++++++++++++++++++++++++++++++++//
unsigned int get_row2swap(const unsigned int index_diag, const Matrix& Any)
// ??????? ???????????? ????? ?????? ?????? ?? ??????? ?????????? ???????? ???????????????,
// ? ??????? ???????????? ????????? (????? ?????????? ???????? ? ??????? ? ??????? index_diag).
// 
// ???? ??????????? ???????? ?? ??????? index2swap ????????? ?????????? ???? ? ??????? =>
// => ???????????? ??????? ????!
{
	unsigned int index2swap = index_diag;
	while ((index2swap < Any.get_rSize()) && (Any.get_elem(index2swap, index_diag) == 0.0))
	{			
		index2swap = index2swap + 1;
	}

	return index2swap;
};

bool swap_rows(const unsigned int index_diag, Matrix& Any)
// ??????? ?????????? ???? bool:
//		true, ???? ???? ????????? ???????????? ?????
//		false, ???? ???????????? ????? ?? ????
{
	bool swap_flag = false;

	const unsigned int index2swap = get_row2swap(index_diag, Any);

	if (index2swap != Any.get_rSize())
	{
		// ???????????? ?????:
		swap_flag = true;

		// ???????????? ?????:
		double buffer_value;
		for (size_t col = index_diag; col < Any.get_cSize(); col++)
		{
			buffer_value = Any.get_elem(index_diag, col);
			Any.set_elem(index_diag, col, Any.get_elem(index2swap, col));
			Any.set_elem(index2swap, col, buffer_value);
		}
	}

	return swap_flag;
}

void column_reset(const unsigned int index_diag, Matrix& Any) 
{
	double swaped_value;
	for (size_t row = index_diag + 1; row < Any.get_rSize(); row++)
	{
		swaped_value = Any.get_elem(row, index_diag);
		Any.set_elem(row, index_diag, 0.0);

		for (size_t col = row; col < Any.get_cSize(); col++)
		{
			add(Any, row, col, -swaped_value * Any.get_elem(index_diag, col));
		}
	}
}




//+++++++++++++++++++++++++++++++++++//                              
//           CLASS METHODS           //
//+++++++++++++++++++++++++++++++++++//
void add(Matrix& Any, unsigned int row, unsigned int col, const double added_value)
{
	Any.set_elem(row, col, Any.get_elem(row, col) + added_value);
}

// -1) The private geter gets a linear index:
unsigned int Matrix::get_index(unsigned int row, unsigned int col) const
{
	// n = i - 1 + (j - 1) * rown    ? ??????, ???? i in [1, rown], ? j in [1, coln]  =>
	// => return row - 1 + (col - 1) * this->rown;
	// n = i + j * rown		? ??????, ???? i in [0, rown-1], ? j in [0, coln-1] =>
	// => return row + col * this->rown;
	// ?????? ????????? ???????? ? exel ????? ???????.
	
	assert((col < this->coln) && "ERROR_MATRIX_INDEX_IS_OUT_SIZE"); // assert(bool = true)
	assert((row < this->rown) && "ERROR_MATRIX_INDEX_IS_OUT_SIZE");

	return row + col * this->rown;
}

// 1) ?onstructors:
Matrix::Matrix() : rown(0), coln(0) {}

Matrix::Matrix(unsigned int rown, unsigned int coln) : coln(coln), rown(rown), values(coln * rown) {}

// 2) Destructior:
Matrix::~Matrix()
{
	values.clear();
	values.shrink_to_fit();
}

// 3) Geters and seters:
const unsigned int Matrix::get_rSize() const
{
	return this->rown;
}

const unsigned int Matrix::get_cSize() const
{
	return this->coln;
}

const double Matrix::get_elem(unsigned int row, unsigned int col) const
{
	// 0. Checking of the indexes: 
	assert(((row < this->rown) && (col < this->coln)) && "ERROR_MATRIX_INDEX_IS_OUT_SIZE");

	return this->values.at(get_index(row, col));
}

void Matrix::set_elem(unsigned int row, unsigned int col, const double value)
{
	// 0. Checking of the indexes:
	assert(((row < this->rown) && (col < this->coln)) && "ERROR_MATRIX_INDEX_IS_OUT_SIZE");

	//this->values.erase(this->values.begin() + this->get_index(row, col));
	//this->values.insert(this->values.begin() + this->get_index(row, col), value);
	this->values.at(get_index(row, col)) = value;
}

void Matrix::set_column(unsigned int col, const Matrix& column)
{
	// 0. Checking of the indexes:
	assert((col < this->coln) && "ERROR_MATRIX_INDEX_IS_OUT_SIZE");
	assert((column.rown == this->rown) && "ERROR_MATRIXES_SIZES_SHOULD_BE_EQUAL");
	assert((column.coln == 1) && "ERROR_MATRIX_SHOULD_BE_A_COLUMN");

	// 1. The column is inserted there:
	this->values.erase(this->values.begin() + col * this->rown, this->values.begin() + (col + 1) * this->rown);
	this->values.insert(this->values.begin() + col * this->rown, column.values.begin(), column.values.end());
}

// ??????? ???????? ???????????? ??????? ?????????? ??????.
// ???? ???????? - ??????? ??????? ??? ?????? ??????????? (??????????)
// ??? ?????? LU ?????????? ? ??????.
// ???? ????? ? ?????????? ?????, ?? ?????????? ?????????, ?????? ?? ???????.
const double Matrix::det() const
{
	// 0. Checking of the sizes:
	assert((this->coln == this->rown) && "ERROR_MATRIX_IS_NOT_SQUARE");
	assert((this->coln != 0) && "ERROR_MATRIXES_SIZES_SHOULD_BE_NO_ZERO");

	// 1. If matrix is number:
	if ((this->coln == 1) && (this->rown == 1))
	{
		return this->get_elem(0, 0);
	}

	// 2. If matrix is suqare:
	Matrix Copy = *this;

	double det_value = 1.0;

	unsigned int index_diag = 0;
	double value_diag;

	while (index_diag < Copy.get_rSize())
	{
		// ???????? ?? ??????? ???????????? ???????:
		if (Copy.get_elem(index_diag, index_diag) == 0.0)
		{
			// ????? ?????????? ?????? ? ???????, ???????? ????
//**********// call swap_rows(...)


			// ???????? ???????????, ???? ??? ???????? - ??????? => det = 0
			// swap_rows(...) -> false => return det_value = 0.0;
			// swap_rows(...) -> true => det_value = det_value * (-1.0);
			if (swap_rows(index_diag, Copy))
			{
				return det_value = 0.0;
			}	
		}

		// ??????? ?????????? (????? ???????, ?????? ????) det != 0
		value_diag = Copy.get_elem(index_diag, index_diag);

		det_value = det_value * value_diag;

		// ??????? ?????? ?? ???????????? ???????:
		for (size_t col = index_diag; col < Copy.get_cSize(); col++)
		{
			Copy.set_elem(index_diag, col, Copy.get_elem(index_diag, col) / value_diag);
		}

		// ?????????? ????????? ??????? ???? ????????????:
//******// call column_reset(...)
		column_reset(index_diag, Copy);

		index_diag = index_diag + 1;
	}

	return det_value;
}


const double Matrix::norm() const
{
	std::vector<double> valuesSort = this->values;
	std::sort(valuesSort.begin(), valuesSort.end(), [](double a, double b)->bool { return std::abs(a) > std::abs(b); });

	return std::abs(valuesSort[0]);
}


//+++++++++++++++++++++++++++++++++++//                              
//             OPERATORS             //
//+++++++++++++++++++++++++++++++++++//
Matrix& Matrix::operator=(const Matrix& Any)
{
	// ????????????? ?????????? ????????? Matrix& Matrix::operator=(const Matrix& Any),
	// ????????????? ?????? ?? ??????, ? ?? ??????, ????????? ????????? ??????? ??????????!
	//
	// ??? ????, ????? ??????? ?????? ?? ??????, ???????????? ? ???? ??????????? return *this;

	// 0. ???????? ?? ??????????????.
	// ????? ?? ????????? ?????? ???????????.
	// ?????????? ?????? ?? ?????? ??????.
	if (this == &Any)
	{
		return *this;
	}

	// 1. The copying of the object values:
	this->coln = Any.coln;
	this->rown = Any.rown;
	this->values = Any.values;

	return *this;
}

std::ostream& operator<<(std::ostream& out, const Matrix& m)
{
	for (int i = 0; i < m.get_rSize(); ++i)
	{
		for (int j = 0; j < m.get_cSize(); ++j)
		{
			out << m.get_elem(i, j) << "\t";
		}
		out << std::endl;
	}
	out << std::endl;
	return out;
}

Matrix operator+(const Matrix& left, const Matrix& right)
{
	// 0. Checking of the sizes:
	assert((left.get_cSize() == right.get_cSize()) && "ERROR_MATRIXES_SIZES_SHOULD_BE_EQUAL");
	assert((left.get_rSize() == right.get_rSize()) && "ERROR_MATRIXES_SIZES_SHOULD_BE_EQUAL");
	assert((left.get_cSize() != 0) && "ERROR_MATRIXES_SIZES_SHOULD_BE_NO_ZERO");
	assert((left.get_rSize() != 0) && "ERROR_MATRIXES_SIZES_SHOULD_BE_NO_ZERO");

	// 1. The matrix result is created there:
	Matrix result(left.get_rSize(), left.get_cSize());

	for (size_t j = 0; j < right.get_cSize(); j++)
	{
		for (size_t i = 0; i < right.get_rSize(); i++)
		{
			result.set_elem(i, j, left.get_elem(i, j) + right.get_elem(i, j));
		}
	}

	return result;
}

Matrix operator-(const Matrix& left, const Matrix& right)
{
	// 0. Checking of the sizes:
	assert((left.get_cSize() == right.get_cSize()) && "ERROR_MATRIXES_SIZES_SHOULD_BE_EQUAL");
	assert((left.get_rSize() == right.get_rSize()) && "ERROR_MATRIXES_SIZES_SHOULD_BE_EQUAL");
	assert((left.get_cSize() != 0) && "ERROR_MATRIXES_SIZES_SHOULD_BE_NO_ZERO");
	assert((left.get_rSize() != 0) && "ERROR_MATRIXES_SIZES_SHOULD_BE_NO_ZERO");

	// 1. The matrix result is created there:
	Matrix result(left.get_rSize(), left.get_cSize());

	for (size_t j = 0; j < right.get_cSize(); j++)
	{
		for (size_t i = 0; i < right.get_rSize(); i++)
		{
			result.set_elem(i, j, left.get_elem(i, j) - right.get_elem(i, j));
		}
	}

	return result;
}

Matrix operator*(const Matrix& left, const Matrix& right)
{
	// 0. Checking of the sizes:
	assert((left.get_cSize() == right.get_rSize()) && "ERROR_MATRIX_L_CSIZE_SHOULD_BE_EQUAL_MATRIX_R_RSIZE");
	assert((left.get_cSize() != 0) && "ERROR_MATRIXES_SIZES_SHOULD_BE_NO_ZERO");
	assert((left.get_rSize() != 0) && "ERROR_MATRIXES_SIZES_SHOULD_BE_NO_ZERO");
	assert((right.get_cSize() != 0) && "ERROR_MATRIXES_SIZES_SHOULD_BE_NO_ZERO");

	Matrix result = Matrix(left.get_rSize(), right.get_cSize());

	// C(MxN) = A(MxN) * B(NxP)
	//c[i][j] = sum(n=1 -> A.col) { a[i][n] * b[n][j] }
	for (int i = 0; i < result.get_rSize(); ++i)
		for (int j = 0; j < result.get_cSize(); ++j)
		{
			double sum = 0;
			for (int n = 0; n < left.get_cSize(); ++n)
			{
				sum += left.get_elem(i, n) * right.get_elem(n, j);
			}
			result.set_elem(i, j, sum);
		}

	return result;
}


Matrix read(std::string fullway2data)
{
	std::ifstream inputfile;
	inputfile.open(fullway2data);

	Matrix Res;

	if (inputfile.is_open())
	{
		std::string buff_s;
		double buff_d;
		std::vector <std::vector<double>> buff_data;
		std::vector <double> buff_data_row;

		while (getline(inputfile, buff_s))
		{
			std::istringstream buff_ss(buff_s);

			while (buff_ss >> buff_d)
			{
				buff_data_row.push_back(buff_d);
			}

			buff_data.push_back(buff_data_row);
			buff_data_row.clear();
		}

		Res = Matrix(buff_data.size(), buff_data.at(0).size());

		for (size_t row = 0; row < Res.get_rSize(); row++)
		{
			assert((buff_data.at(row).size() == Res.get_cSize()) && "ERROR_COPIED_MATRIX_COLUMNS_SIZES_SHOULD_BE_EQUAL");

			if (buff_data.at(row).size() != Res.get_cSize())
			{
				std::cout << "ERROR: copying matrix is failed! Process was stopped!" << std::endl;

				return Res;
			}

			for (size_t col = 0; col < Res.get_cSize(); col++)
			{
				Res.set_elem(row, col, buff_data.at(row).at(col));
			}
		}
	}
	else
	{
		std::cout << "ERROR: copying matrix is failed! File isn't opened!" << std::endl;
	}

	return Res;
}

void print(const Matrix& Any, unsigned int precicion)
{
	if ((Any.get_rSize() == 0) || (Any.get_cSize() == 0))
	{
		std::cout << "WARNING: printed matrix is empty!" << std::endl;
	}

	for (size_t i = 0; i < Any.get_rSize(); i++)
	{
		for (size_t j = 0; j < Any.get_cSize(); j++)
		{
			std::cout << std::setprecision(precicion) << std::scientific << Any.get_elem(i, j) << "		";
		}
		std::cout << std::endl;
	}
}

void Save(const std::string& way, const std::string name, const Matrix& any)
{
	// The type conversion is there: 
	const char* way_c = way.c_str();

	// The object adds:
	std::ofstream outf;

	// The file opens:
	outf.open(way_c, std::ios::app);

	if (outf.is_open())
	{
		// The name output is there:
		outf << name << std::endl;

		// The values output is there:
		for (size_t i = 0; i < any.get_rSize(); ++i)
		{
			for (size_t j = 0; j < any.get_cSize(); ++j)
			{
				outf << std::setprecision(16) << std::scientific << any.get_elem(i, j) << " ";
			}
			outf << std::endl;;
		}
	}
}

void Save(const std::string& way, const std::string name, const double num)
{
	// The type conversion is there: 
	const char* way_c = way.c_str();

	// The object adds:
	std::ofstream outf;

	// The file opens:
	outf.open(way_c, std::ios::app);

	if (outf.is_open())
	{
		// The name output is there:
		outf << name << std::endl;

		// The values output is there:
		outf << std::setprecision(16) << std::scientific << num << std::endl;
	}
}