#pragma once

#include "Matrix.h"
#include "Decomposition.h"


class ISolveTusk
{
public:
	virtual void InputData() = 0;
	virtual void Solve() = 0;
	virtual void OutputData() = 0;
};

class Task : public ISolveTusk
{
private:
	void (*method)();
public:
	void setMethod(void (*method)());

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

public:
	
};

