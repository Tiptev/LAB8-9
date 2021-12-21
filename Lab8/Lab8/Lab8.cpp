#include <iostream>
#include <string>
#include <sstream>
#include <locale.h>
#include <fstream>
//#include <stdlin>

int place[8][8];
int variable;
int k, l, m, n;
bool match = 0;
bool addit = 0;
using namespace std;


int output(int place[8][8]) //вывод на экран шахматной доски
{
    cout << endl;
    for (int i = 7; i >= 0; i--)
    {
        for (int j = 0; j < 8; j++)
        {
            cout << "[";
            if (place[i][j] == 0)
                cout << " ";
            if (place[i][j] == 1)
                cout << "1";
            if (place[i][j] == 2)
                cout << "2";
            if (place[i][j] == 3)
                cout << "3";
            if (place[i][j] == 5)
                cout << "5";
            if (place[i][j] == 7)
                cout << "7";
            cout << "]";
        }
        cout << endl;
    }
    return 0;
}

bool check_first_move(int place[8][8])//проверка на первый ход
{
    int choice = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (place[i][j] == 1)
                choice++;
        }
    }
    if (choice == 0)
    {
        cout << " - Да, это возможно сделать за 1 ход!" << endl;
    }
    else
    {
        cout << " - Нет, это не возможно за один ход!" << endl;
        addit = 1;
    }
    return 0;
}


int move_rook(int place[8][8], int k, int l, int m, int n)
{
    for (int i = 0; i < 8; i++)
    {
        place[l][i] = 2;
        place[i][k] = 2;
    }
    cout << "Возможно ли ЛАДЬЁЙ попасть с поля (" << k + 1 << ";" << l + 1 << ") на поле ("<< m + 1 <<";"<< n + 1 <<") ? " << endl;
    check_first_move(place);
    return 0;
}

int move_bishop(int place[8][8], int k, int l, int m, int n)
{
    /*for (int i = 0; i < 8; i++)
    {
        if (((l + i) <= 8) || ((k + i) <= 8))
            place[l + i][k + i] = 3;
        if (((l + i) <= 8) || ((k - i) > 0))
            place[l + i][k - i] = 3;
        if (((l - i) > 0) || ((k + i) <= 8))
            place[l - i][k + i] = 3;
        if (((l - i) > 0) || ((k - i) > 0))
            place[l - i][k - i] = 3;
    }*/
    int i = 0;
    while (((l + i) <= 8) || ((k + i) <= 8))
    {
        place[l + i][k + i] = 5;
        i++;
    }
    i = 0;
    while (((l + i) <= 8) || ((k - i) > 0))
    {
        place[l + i][k - i] = 5;
        i++;
    }
    i = 0;
    while (((l - i) > 0) || ((k + i) <= 8))//вправо вниз
    {
        place[l - i][k + i] = 5;
        i++;
    }
    i = 0;
    while (((l - i) > 0) || ((k - i) > 0)) // влево вниз
    {
        place[l - i][k - i] = 5;
        i++;
    }
    cout << "Возможно ли СЛОНОМ попасть с поля (" << k + 1 << ";" << l + 1 << ") на поле (" << m + 1 << ";" << n + 1 << ") ? " << endl;
    check_first_move(place);

    return 0;
}

int move_knight(int place[8][8], int k, int l , int m ,int n)
{
    place[l][k] = 0;
    place[l + 2][k + 1] = 3;
    place[l + 2][k - 1] = 3;
    place[l - 2][k + 1] = 3;
    place[l - 2][k - 1] = 3;
    place[l + 1][k + 2] = 3;
    place[l - 1][k + 2] = 3;
    place[l + 1][k - 2] = 3;
    place[l - 1][k - 2] = 3;
    cout << "Возможно ли КОНЁМ попасть с поля (" << k + 1 << ";" << l + 1 << ") на поле (" << m + 1 << ";" << n + 1 << ") ? " << endl;
    check_first_move(place);
    return 0;
}

int move_queen(int place[8][8], int k, int l, int m, int n )
{
    for (int i = 0; i < 8; i++)
    {
        place[l][i] = 7;
        place[i][k] = 7;
        if (((l + i) <= 8) || ((k + i) <= 8))
            place[l + i][k + i] = 7;
        if (((l + i) <= 8) || ((k - i) > 0))
            place[l + i][k - i] = 7;
        if (((l - i) > 0) || ((k + i) <= 8))
            place[l - i][k + i] = 7;
        if (((l - i) > 0) || ((k - i) > 0))
            place[l - i][k - i] = 7;
    }
    cout << "Возможно ли КОРОЛЕВОЙ попасть с поля (" << k + 1 << ";" << l + 1 << ") на поле (" << m + 1 << ";" << n + 1 << ") ? " << endl;
    check_first_move(place);
    return 0;
}

int color(int place[8][8], int k, int l, int m, int n)//заполнение цветом шахматную доску
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (((i == 0) || (i % 2 == 0)) && ((j == 0) || (j % 2 == 0)))
                place[i][j] = 1;
            if ((i % 2 == 1) && (j % 2 == 1))
                place[i][j] = 1;
        }
    }
    if ((place[l][k]) == (place[n][m]))
    {
        cout << endl << "Поля (" << k + 1 << ";" << l + 1 << ") на поле (" << m + 1 << ";" << n + 1 << ") - одного цвета!" << endl;
        match = 1;
    }
    else
        cout << endl << "Поля (" << k + 1 << ";" << l + 1 << ") на поле (" << m + 1 << ";" << n + 1 << ") - разных цветов!" << endl;
    return 0;
}


int clear(int place[8][8])// очистить шахматную доску
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            place[i][j] = 0;
        }
    }
    return 0;
}



/*int check1(int variable)
{
    bool choice = 0;
    for (;;)
    {
        switch(variable)
        {
            case 1:
                choice = 1;
                break;
            case 2:
                choice = 1;
                break;
            case 3:
                choice = 1;
                break;
            case 4:
                choice = 1;
                break;
            case 5:
                choice = 1;
                break;
            case 6:
                choice = 1;
                break;
            case 7:
                choice = 1;
                break;
            case 8:
                choice = 1;
                break;
            default:
                cout <<"!";
                cin >> variable;
            break;
        }
        if (choice == 1)
            break;
    }
    return variable;
}*/

int main()
{
    setlocale(LC_CTYPE, "rus");
    ofstream file;
    file.open("C:\\Users\\acer\\OneDrive\\Рабочий стол\\Lab8-9\\log.txt", ios::app);
    if (file.is_open() == true)
    {
        file << endl << "Программа запущена!" << endl;
    }
    else
    {
        cout << "Файл не открыт";
    }
    cout << "Введите координату 'k', 1-ой точки:  ";
    cin >> variable;
    k = variable - 1;
    //-------------------------
    cout << "Введите координату 'l', 1-ой точки:  ";
    cin >> variable;
    l = variable - 1;
    //-------------------------
    cout << "Введите координату 'm', 2-ой точки:  ";
    cin >> variable;
    m = variable - 1;
    //-------------------------
    cout << "Введите координату 'n', 2-ой точки:  ";
    cin >> variable;
    n = variable - 1;
    if (file.is_open() == true)
    {
        file << "Координата первой фигуры = ("<< k + 1 <<";"<< l + 1 <<");" << endl;
        file << "Координата второй  фигуры = (" << m + 1 << ";" << n + 1 << ");" << endl;
    }
    //-------------------------
    place[l][k] = 1;
    place[n][m] = 1;
    output(place);//выводит на экран первое положение шахмат
    clear(place);
    color(place, k, l, m, n);
    clear(place);
    place[l][k] = 1;
    place[n][m] = 1;
    int choice = 0;
    cout << "Какая шахматная фигура расположена на поле (" << k + 1 << ";" << l + 1 << ")? " << endl;
    cout << "ЛАДЬЯ - '2'; " << endl;
    cout << "КОНЬ -  '3'; " << endl;
    cout << "СЛОН -  '5'; " << endl;
    cout << "ФЕРЗЬ - '7'. " << endl;
    cout << "Введите число: ";
    cin >> choice;
    switch (choice)
    {
    case 2://ЛАДЬЯ
        if (file.is_open() == true)
        {
            file << "Пользователь выбрал шахматную фигуру - ЛАДЬЯ." << endl;
        }
        move_rook(place, k, l, m, n);
        if (addit = 1)
        {
            cout << "Что бы за 2-а хода, добраться до поля (" << m + 1 << ";" << n + 1 << "), в 1-ый ход нужно переместиться на поле (" << k + 1 << ";" << n + 1 << ")" << endl;
        }
        break;
    case 3://КОНЬ
        if (file.is_open() == true)
        {
            file << "Пользователь выбрал шахматную фигуру - КОНЬ." << endl;
        }
        move_knight(place, k, l, m, n);
        break;
    case 5://СЛОН
        if (file.is_open() == true)
        {
            file << "Пользователь выбрал шахматную фигуру - СЛОН." << endl;
        }
        if (match == 1)
        {
            move_bishop(place, k, l, m, n);
        }
        else
        {
            cout << "Возможно ли СЛОНОМ попасть с поля (" << k + 1 << ";" << l + 1 << ") на поле (" << m + 1 << ";" << n + 1 << ") ? " << endl;
            cout << " - Нет, это не возможно! Фигуры находятся на полях разных цветов." << endl;
        }
        break;
    case 7://ФЕРЗЬ
        if (file.is_open() == true)
        {
            file << "Пользователь выбрал шахматную фигуру - ФЕРЗЬ." << endl;
        }
        move_queen(place, k, l, m, n);
        if (addit = 1)
        {
            cout << "Что бы за 2-а хода, добраться до поля (" << m + 1 << ";" << n + 1 << "), в 1-ый ход нужно переместиться на поле (" << k + 1 << ";" << n + 1 << ")" << endl;
        }
        break;
    default:
        break;
    }
    if (file.is_open() == true)
    {
        if (addit == 0)
            file << "За 1 ход можно попасть с поля (" << k + 1 << ";" << l + 1 << ") на поле (" << m + 1 << ";" << n + 1 << ")." << endl;
        else
            file << "За 1 ход невозможно попасть с поля (" << k + 1 << ";" << l + 1 << ") на поле (" << m + 1 << ";" << n + 1 << ")." << endl;
        file << "Программа завершена!" << endl;
    }
    file.close();
    return 0;
}
