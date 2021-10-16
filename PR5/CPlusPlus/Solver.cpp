#include "../Headers/Solver.h"

//+++++++++++++++++++++++++++++++++++//                              
//               TASKS	             //
//+++++++++++++++++++++++++++++++++++//

Matrix CalculateSLAY_L(const Matrix& low, const Matrix& b)
{
    //std::vector<double> res;
    Matrix res = Matrix(b.get_rSize(), b.get_cSize());

    for (int i = 0; i < low.get_cSize(); ++i)
    {
        double sum = 0;
        for (int j = 0; j < i; ++j)
        {
            double l = low.get_elem(i, j);
            double bi = res.get_elem(j, 0);
            sum += l * bi;
        }
        sum = b.get_elem(i, 0) - sum;
        res.set_elem(i, 0, sum);
    }
    return res;
}

Matrix CalculateSLAY_U(const Matrix& up, const Matrix& y)
{
    Matrix res = Matrix(y.get_rSize(), y.get_cSize());

    for (int i = up.get_cSize() - 1; i >= 0; --i)
    {
        double sum = 0;
        for (int j = up.get_cSize() - 1; j > i; --j)
        {
            double u = up.get_elem(i, j);
            double yi = res.get_elem(j, 0);
            sum += u * yi;
        }
        sum = (y.get_elem(i, 0) - sum) / up.get_elem(i, i);
        res.set_elem(i, 0, sum);
    }
    return res;
}

Matrix TaskDecomposition::Solve(const Matrix& A, const Matrix& b)
{
    Matrix L, U;
    Decomposition dc(A);
    L = dc.get_L();
    U = dc.get_U();
    Matrix y = CalculateSLAY_L(L, b);
    Matrix x = CalculateSLAY_U(U, y);

	return x;
}

bool TaskDecomposition::ExistSolution(const Matrix& A)
{
	return A.det() != 0;
}



Matrix TaskCramer::Solve(const Matrix& A, const Matrix& b)
{
    double a_det = A.det();
    Matrix res(b.get_rSize(), b.get_cSize());

    for (int i = 0; i < A.get_cSize(); ++i)
    {
        Matrix Ab = A;
        Ab.set_column(i, b);
        res.set_elem(i, 0, Ab.det() / a_det);
    }

	return res;
}

bool TaskCramer::ExistSolution(const Matrix& A)
{
	return A.det() != 0;
}

//+++++++++++++++++++++++++++++++++++//                              
//              SOLVER	             //
//+++++++++++++++++++++++++++++++++++//

Solver::Solver(Matrix& A, Matrix& b, ITask* task) :A(A),b(b),task(task) {}
Solver::~Solver()
{
	if (result != nullptr)
		delete result;
	if (task != nullptr)
		delete task;
}

void Solver::setTask(ITask* task)
{
	if (this->task != nullptr)
		delete this->task;
	this->task = task;
}

Matrix* Solver::SolveTask()
{
	if (result != nullptr)
		delete result;

	if (task->ExistSolution(A))
		this->result = new Matrix(task->Solve(A,b));
	else
		this->result = nullptr;
	return result;
}



