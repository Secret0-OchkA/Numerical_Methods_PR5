// Practical_work_5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

// #define NDEBUG    // инструкция дл препроцессора отключающая макрос assert

#include <iostream>
#include <vector>
#include "Headers/Matrix.h"
#include "Headers/Solver.h"
#include <string>

Matrix GetX(const size_t);
std::string getTime(const char* = "%4i_%#02i_%#02i_time_%#02i_%#02i_%#02i");

int main()
{
    // В релизной версии программы необходимо отключить все макросы проверки (assert).
    // Все провеки, связанные с загрузкой матрицы из файла и корректности размеров,
    // должны быть явно реализованы в main. Релизная версия программы всегда должна завершаться
    // с кодом 0. Другой код, свидетельствующий об ошибке,в отлаженной программе возникать не должен.
    // 
    // Отключить все макросы необходимо добавив дерективу дял препроцессора в этом файле.
    // Добавление директивы пропусти добавление всех строк содержащих assert.
    
    std::string fileWay = "D:\\CodeProjects\\PR5\\PR5\\1.txt";

    Matrix A = read(fileWay);

    Matrix x_exist = GetX(A.get_rSize());
    Matrix b = A * x_exist;
    Matrix x_LU;
    Matrix x_Cramer;

    try
    {
        Solver sl(A, b, new TaskDecomposition());
        x_LU = sl.SolveTask();

        sl.setTask(new TaskCramer());
        x_Cramer = sl.SolveTask();
    }
    catch (std::exception& ex)
    {
        std::cerr << ex.what();
    }

    double delta_norm = x_LU.norm() - x_Cramer.norm();

    //++++++++++++++++++//
    //   output data    //
    //++++++++++++++++++//
    std::cout << "A:\n";
    print(A, 16);

    std::cout << "decomposition:\n";
    print(x_LU, 16);

    std::cout << "cramer:\n";
    print(x_Cramer, 16);

    //1) || x_exist - x_Cramer ||
    std::cout << "|| x_exist - x_Cramer || = " << (x_exist - x_Cramer).norm() << std::endl;

    //2) || x_exist - x_LU ||
    std::cout << "|| x_exist - x_LU || " << (x_exist - x_LU).norm() << std::endl;

    //3) || x_Cramer - x_LU ||
    std::cout << "|| x_Cramer - x_LU ||" << (x_Cramer - x_LU).norm() << std::endl;

    const std::string saveWay = "D:\\CodeProjects\\PR5\\Reports\\";
    const std::string filename = "data_" + getTime();
    const std::string fullwayname = saveWay + filename + ".txt";

    Save(fullwayname, "A", A);
    Save(fullwayname, "b", b);
    Save(fullwayname, "x_Exist", x_exist);

    Save(fullwayname, "x_LU", x_LU);
    Save(fullwayname, "x_Cramer", x_Cramer);

    Save(fullwayname, "|| x_exist - x_Cramer ||", (x_exist - x_Cramer).norm());
    Save(fullwayname, "|| x_exist - x_LU || ", (x_exist - x_LU).norm());
    Save(fullwayname, "|| x_Cramer - x_LU ||", (x_Cramer - x_LU).norm());

    return 0;
}

Matrix GetX(const size_t row)
{
    Matrix res(row, 1);

    for (int i = 0; i < row; ++i)
    {
        res.set_elem(i,0,i);
    }

    return res;
}

std::string getTime(const char* format)
{
    time_t now = time(0);
    struct tm newtime;
    localtime_s(&newtime, &now);

    const int year = 1900 + newtime.tm_year;
    const int month = 1 + newtime.tm_mon;
    const int day = newtime.tm_mday;
    const int hour = newtime.tm_hour;
    const int minute = newtime.tm_min;
    const int second = newtime.tm_sec;

    char date[256];

    sprintf_s(date, format, year, month, day, hour, minute, second);

    return std::string(date);
};