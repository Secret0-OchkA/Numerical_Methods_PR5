#include "../Headers/Solver.h"

//+++++++++++++++++++++++++++++++++++//                              
//               TASKS	             //
//+++++++++++++++++++++++++++++++++++//

Matrix TaskDecomposition::Solve(const Matrix& A, const Matrix& b)
{
	return Matrix();
}

bool TaskDecomposition::ExistSolution(const Matrix& A)
{
	return true;
}


Matrix TaskCramer::Solve(const Matrix& A, const Matrix& b)
{
	return Matrix();
}

bool TaskCramer::ExistSolution(const Matrix& A)
{
	return false;
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



