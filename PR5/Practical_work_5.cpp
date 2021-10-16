// Practical_work_5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

// #define NDEBUG    // инструкция дл препроцессора отключающая макрос assert

#include <iostream>
#include <vector>
#include "Headers/Matrix.h"
#include "Headers/Solver.h"

int main()
{
    // В релизной версии программы необходимо отключить все макросы проверки (assert).
    // Все провеки, связанные с загрузкой матрицы из файла и корректности размеров,
    // должны быть явно реализованы в main. Релизная версия программы всегда должна завершаться
    // с кодом 0. Другой код, свидетельствующий об ошибке,в отлаженной программе возникать не должен.
    // 
    // Отключить все макросы необходимо добавив дерективу дял препроцессора в этом файле.
    // Добавление директивы пропусти добавление всех строк содержащих assert.
    

    // тест солвера
    Matrix A = Matrix();
    Matrix b = Matrix(2,1);
    b.set_elem(0, 0, 1);
    b.set_elem(1, 0, 2);

    Solver sl(A,b, new TaskDecomposition());
    Matrix* x_ptr = sl.SolveTask();
    Matrix decomposit;
    if (x_ptr != nullptr)
        decomposit = *x_ptr;

    sl.setTask(new TaskCramer());
    x_ptr = sl.SolveTask();
    Matrix cramer;
    if (x_ptr != nullptr)
        cramer = *x_ptr;

    double delta_norm = decomposit.norm() - cramer.norm();

    std::cout << "decomposition:\n" << decomposit << std::endl;
    std::cout << "cramer:\n" << cramer << std::endl;
    std::cout << "delta_norm: " << delta_norm << std::endl;

    return 0;
}

