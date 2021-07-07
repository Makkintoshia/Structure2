#include <iostream> // Cout Cin
#include <Windows.h> // Для использования русского языка
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <iomanip> // setw и т.д.



//Проект //Свойства название_проекта//Свойства конфигурации//Препроцессор/Определения препроцессора//;_CRT_SECURE_NO_WARNINGS




using namespace std;

struct TIME { int ch, min; };

struct STUDENT
{
    char name[50]; // Имя студента
    int number; // Номер группы
    int srednee;
    int type[5] = {0,0,0,0,0}; // Успеваемость 
    
};

const int size_aro = sizeof(STUDENT); // Размер структуры

void FileWriter(const char* fname)
{
    FILE* fwriter = fopen(fname, "ab+"); // Открытие бинарного файла для записи в конец

    STUDENT aro;

    while (fwriter) // Файл открыт для записи пока пользователь не захочет выйти. Открыть файл для записи и чтения в режиме добавления 
    {
        cout << "[SYSTEM]: Предупреждение! Для выхода введите '*'.\n[SYSTEM]: Введите имя студента: "; 
        cin >> aro.name;
        if (aro.name[0] == '*') break;

        cout << "[SYSTEM]: Введите номер группы: ";
        cin >> aro.number;
        for (int l = 0;l < 5;l++)
        {
            cout << "[SYSTEM]: Введите оценку: ";
            cin >> aro.type[l];
        }
        aro.srednee = (aro.type[0] + aro.type[1] + aro.type[2] + aro.type[3] + aro.type[4]) / 5;
        cout << "[SYSTEM]:Средняя оценка" << aro.srednee;
        fwrite(&aro, size_aro, 1, fwriter); // Запись данных в файл

        cout << "\n----------Запись успешно добавлена----------\n";

        cout << setw(14) << "| ФИО: " << setw(27) << aro.name << setw(14) << "\n| Номер группы: " << setw(26) << aro.number << setw(14) << "\n| Оценки: " <<  aro.type[0]<< aro.type[1] << aro.type[2] << aro.type[3] << aro.type[4]
            <<"\n|Среднее Оценки: "<< aro.srednee;

        cout << "\n--------------------------------------------\n";
    }
    fclose(fwriter);
}


void FileReader(const char* fname)
{
    FILE* freader = fopen(fname, "rb"); // Открытие бинарного файла для чтения (файл должен существовать)

    STUDENT aro;

    int n = 0; // Если n < 1 - то конец файла

    int count = 0; // Количество записей в файле

    if (!freader) cout << "[SYSTEM]: Нет данных для чтения!\n";
    else // Если файл существует
    {
        while (!feof(freader))
        {
            n = fread(&aro, size_aro, 1, freader); // Буффер | Размер буффера | Количество читаемых данных | Поток

            if (n < 1) break; // Если n < 1 - то конец файла

            count++;

            cout << "\n---------------Запись №" << count << "-----------------\n";

            cout << setw(14) << "| ФИО: " << setw(27) << aro.name << setw(14) << "\n| Номер группы: " << setw(26) << aro.number << setw(14) <<"\n| Оценки: " <<  aro.type[0]<< aro.type[1] << aro.type[2] << aro.type[3] << aro.type[4]
                <<"\n|Среднее Оценки: "<< aro.srednee;

            cout << "\n-----------------------------------------\n";
        }
        fclose(freader);
    }
}


void Sort(const char* fname) // Сортировка данных по номеру ггруппы (пузырьком)
{
    FILE* freader = fopen(fname, "rb+"); // Открытие бинарного файла для записи и чтения

    STUDENT aro1, aro2;

    // Длина файла (количество записей)
    fseek(freader, 0, SEEK_END); // Указать в конец

    int fsize = ftell(freader) / size_aro; // Получаем количество записей |

    rewind(freader); // Указать в начало
    // Конец подсчета длины

    if (!freader || fsize == 0) cout << "[SYSTEM]: Нет данных для чтения!\n";
    else
    {
        cout << "[SYSTEM]: Начало сортировки данных по номерам группы\n";
        for (int i = fsize - 1; i >= 1; i--)
        {
            for (int j = 0; j <= i - 1; j++)
            {
                fseek(freader, j * size_aro, SEEK_SET); //указатель на j-ую запись

                fread(&aro1, size_aro, 1, freader); //читаем запись j в aro1

                fread(&aro2, size_aro, 1, freader); //читаем след. запись в aro2

                if (aro1.number > aro2.number)  //сравниваем номера групп
                {
                    fseek(freader, (-2) * size_aro, SEEK_CUR); //указатель на 2 позиции назад

                    //свапнуть значения
                    fwrite(&aro2, size_aro, 1, freader); //сначала записываем aro2

                    fwrite(&aro1, size_aro, 1, freader); // затем записываем aro1
                }
            }
        }
        cout << "[SYSTEM]: Сортировка успешно завершена\n";
    }
    fclose(freader);
}


void Search(const char* fname) // Ученики со средним больше 4
{
    FILE* freader = fopen(fname, "rb"); // Открытие бинарного файла для чтения (файл должен существовать)

    STUDENT aro ;

    int n = 0; // Если n < 1 - то конец файла

    int count = 0; // Количество записей в файле



    if (!freader) cout << "[SYSTEM]: Нет данных для чтения!\n";
    else // Если файл существует
    {
        

        while (!feof(freader))
        {
            n = fread(&aro, size_aro, 1, freader); // Буффер | Размер буффера | Количество читаемых данных | Поток

            if (n < 1) break; // Если n < 1 - то конец файла

            if (aro.srednee >=4)
            {
                if (count == 0) 

                count++;

                cout << "\n---------------Студет №" << count << "-------------------\n";

                cout << setw(14) << "| Номер группы: " << setw(26) << aro.number << setw(14) << "\n| Оценки: " << setw(25) << aro.type[0] << aro.type[1] << aro.type[2] << aro.type[3] << aro.type[4]
                    << "\n|Среднее Оценки: " << aro.srednee;;

                cout << "\n-----------------------------------------\n";
            }
        }
        if (count == 0) cout << "[SYSTEM]: К сожалению, мы не смогли найти ни одного рейса по вашему запросу :(\n";

        fclose(freader);
    }
}







int main()
{
    int mode = 0; // Режим работы программы (меню)

    const char* fname = "main.dat"; // Имя файла (передается в функции)

    // Параметры русского языка
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "[1] - Прочитать бинарный файл\n[2] - Записать данные в файл\n[3] - Очистить экран\n[4] - Сортировка данных по номеру группы (пузырьком)\n[5] - Ученики со средним баллом больше 4\n[666] - Выход\n";
    while (true) 
    {
        cout << "[SYSTEM MODE]: "; cin >> mode;

        switch (mode)
        {
        case 1: FileReader(fname); break; // Прочитать файл язык Си
        case 2: FileWriter(fname); break; // Записть в файл
        case 3: system("cls"); cout << "[1] - Прочитать бинарный файл\n[2] - Записать данные в файл\n[3] - Очистить экран\n[4] - Сортировка данных по номеру группы (пузырьком)\n[5] -Ученики со средним баллом больше 4\n[666] - Выход\n"; break; // Очистить консоль
        case 4: Sort(fname); break; // Сортировка данных по номеру группы (пузырьком)
        case 5: Search(fname); break; // Студенты сосредним баллом больще 4
        case 666: return 0; break;
        }
    }
}