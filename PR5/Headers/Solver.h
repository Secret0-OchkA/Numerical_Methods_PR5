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
	// Матрица системы (матрица А [см. конспект])   || Эти два параметра можно определить в классе Task 
	// Правая часть (вектор b [см. конспект])		|| И Асоциировать класс Task c классом Solver.
	//
	// Такой подход позволит избавить нас от необходимости хранить декомпозицию или систему в солвере.
	// Можно также добавить флаг, хранящий способ задания матрицы системы или возможность инициализации объектом разложения.
	// А можно просто использовать объект разложения только в случае вызова солвера LU разложением.

public:
	
};

