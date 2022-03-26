#pragma once
#include <iostream>
#include <time.h>
const int size = 9;
int sudoku[size][size];
int test_array[size * size][size] = { 0 };
bool schecker[9][9];
int solsudoku[9][9];
int a;
bool checkrow(int, int);
bool checkcol(int, int);
bool checksqr(int, int);
bool test(int, int);
bool CheckRepeated(int i, int j);
void moveback(int& i, int& j);
void write(int i, int j);
void delElements(int delele);
void redefinition()
{
    //finish();
}
void print();
void selector()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            schecker[i][j] = sudoku[i][j];
        }
    }
}
void solution()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            solsudoku[i][j] = sudoku[i][j];
        }
    }
}
void finish()
{
    //isTue = false;
    srand(time(NULL));
    int delele = a;
    int i, j;
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            for (;;)
            {
                if (!test(i, j))
                    moveback(i, j);

                sudoku[i][j] = rand() % 9 + 1;

                if (CheckRepeated(i, j))
                    continue;

                write(i, j);
                if (checksqr(i, j) && checkrow(i, j) && checkcol(i, j))
                    break;
            }
        }
    }
    print();
    solution();
    delElements(delele);
    print();
//    isTrue();
    selector();
}
void delElements(int delele)
{
    int u, y;
    for (int i = 0; i < delele; )
    {
        u = rand() % 9;
        y = rand() % 9;
        if (sudoku[u][y] != 0) { sudoku[u][y] = 0; i++; }
    }
}
bool checkrow(int x, int y)
{
    for (int i = 0; i < y; i++)
        if (sudoku[x][i] == sudoku[x][y])
            return false;

    return true;
}

bool checkcol(int x, int y)
{
    for (int i = 0; i < x; i++)
        if (sudoku[i][y] == sudoku[x][y])
            return false;

    return true;
}

bool checksqr(int x, int y)
{
    int i_start = x / 3;      i_start *= 3;
    int j_start = y / 3;      j_start *= 3;

    for (int i = i_start; i < i_start + 3; i++)
        for (int j = j_start; j < j_start + 3; j++)
        {
            if (i == x && j == y)
                return true;

            if (sudoku[i][j] == sudoku[x][y])
                return false;
        }
    return true;
}

bool test(int i, int j)
{
    int current = i * 9 + j + 1;

    for (int x = 1; x < 9; x++)
        if (test_array[current][x] == 0)
            return true;

    return false;
}

bool CheckRepeated(int i, int j)
{
    int value = sudoku[i][j];
    int current = i * 9 + j + 1;

    if (test_array[current][value] == 1)
        return true;
    else
        return false;
}

void moveback(int& i, int& j)
{
    int current = i * 9 + j + 1;

    for (int x = 1; x <= 9; x++)
        test_array[current][x] = 0;

    if (j < 1)
    {
        i--;    j = 8;
    }
    else
        j--;
}

void write(int i, int j)
{
    int current = i * 9 + j + 1;
    int value = sudoku[i][j];
    test_array[current][value] = 1;
}

void print()
{
    int i, j;

    for (i = 0; i < 9; i++)
    {
        if (i % 3 == 0)
            std::cout << "=========================\n";

        std::cout << "| ";

        for (j = 0; j < 9; j++)
        {
            if (sudoku[i][j] == 0) std::cout << "  ";
            else std::cout << sudoku[i][j] << " ";

            if ((j + 1) % 3 == 0)
                std::cout << "| ";
        }

        std::cout << "\n";
    }
    std::cout << "=========================\n";
}