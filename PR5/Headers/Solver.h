#pragma once

#include "Matrix.h"
#include "Decomposition.h"
#include <exception>

class ITask
{
public:
	virtual Matrix Solve(const Matrix& A, const Matrix& b) = 0;
	virtual bool ExistSolution(const Matrix& A) = 0;
};

class TaskDecomposition : public ITask
{
	Matrix Solve(const Matrix& A, const Matrix& b);
	bool ExistSolution(const Matrix& A);
};

class TaskCramer : public ITask
{
	Matrix Solve(const Matrix& A, const Matrix& b);
	bool ExistSolution(const Matrix& A);
};

class Solver
{
private:
	// 0) Values:
	// Матрица системы (матрица А [см. конспект])   || Эти два параметра можно определить в классе Task 
	// Правая часть (вектор b [см. конспект])		|| И Асоциировать класс Task c классом Solver.
	//
	// Такой подход позволит избавить нас от необходимости хранить декомпозицию или систему в солвере.
	// Можно также добавить флаг, хранящий способ задания матрицы системы или возможность инициализации объектом разложения.
	// А можно просто использовать объект разложения только в случае вызова солвера LU разложением.
	ITask* task;
	Matrix& A;
	Matrix& b;

	Solver(const Solver& other);
	void operator=(const Solver& other);

public:
	//Constructors
	Solver(Matrix& A, Matrix& b, ITask* = nullptr);
	~Solver();

	//get and set
	void setTask(ITask* task);

	//Methods
	Matrix SolveTask();
};

