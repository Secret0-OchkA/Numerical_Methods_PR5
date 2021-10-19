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
	// ������� ������� (������� � [��. ��������])   || ��� ��� ��������� ����� ���������� � ������ Task 
	// ������ ����� (������ b [��. ��������])		|| � ������������ ����� Task c ������� Solver.
	//
	// ����� ������ �������� �������� ��� �� ������������� ������� ������������ ��� ������� � �������.
	// ����� ����� �������� ����, �������� ������ ������� ������� ������� ��� ����������� ������������� �������� ����������.
	// � ����� ������ ������������ ������ ���������� ������ � ������ ������ ������� LU �����������.
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

