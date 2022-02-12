#include <iostream>
#include <ctime>

using namespace std;

/// <summary>
/// Элемент стека
/// </summary>
struct StackElement
{
    int Value; //Информационная составляющая
    StackElement* Next; //Связующая составляющая(указатель на следующий элемент стека)
};

/// <summary>
/// Инициализация стека
/// </summary>
/// <param name="Stack"></param>
void initStack(StackElement* sp, StackElement* sp_second) 
{
    sp = NULL;
    sp_second = NULL;
}

/// <summary>
/// Проверка на пустоту стека
/// </summary>
/// <param name="sp"></param>
/// <returns></returns>
bool isStackEmpty(StackElement* sp) 
{
    if (sp == NULL)
        return true;
    else
        return false;
}

/// <summary>
/// Вывод информации по стеку
/// </summary>
/// <param name="sp"></param>
void PrintInformationStack(StackElement* sp) 
{
    if (isStackEmpty(sp))
        cout << "\nСтек пуст\n";
    else
    {
        StackElement* pCurrent = sp;
        while (pCurrent != NULL)
        {
            cout << pCurrent->Value << endl;
            pCurrent = pCurrent->Next;
        }
    }
}

/// <summary>
/// Добавление элементов в стек
/// </summary>
/// <param name="value"></param>
/// <param name="sp"></param>
/// <returns></returns>
StackElement* Push(int value, StackElement* sp)
{
    StackElement* pTemp = new StackElement;

    pTemp->Value = value;

    pTemp->Next = sp;

    sp = pTemp;

    return sp;
}

/// <summary>
/// Удаление элемента из главного стека
/// </summary>
/// <param name="sp"></param>
/// <returns></returns>
int Pop(StackElement* sp) 
{
    if (!isStackEmpty(sp))
    {
        StackElement* pTemp = sp;
        sp = sp->Next;
        delete pTemp;
        return 1;
    }
    else
        return -1;
}

/// <summary>
/// Добавление определенного колличества случайных элементов
/// </summary>
/// <param name="count"></param>
/// <param name="sp"></param>
/// <returns></returns>
StackElement* PushCountRandom(int count, StackElement* sp) 
{
    for (int i = 0; i < count; i++) 
    {
        int number = rand();
        sp = Push(number, sp);
    }

    return sp;
}

/// <summary>
/// Перемещение верхнего элемента главного стека в вспомогательный
/// </summary>
/// <param name="sp"></param>
/// <param name="sp_second"></param>
void PushToSecond(StackElement* sp, StackElement* sp_second) 
{
    StackElement* current = sp;
    sp = sp->Next;
    current->Next = sp_second;
    sp_second = current;
}

/// <summary>
/// Перемещение верхнего элемента вспомогательного стека в главный
/// </summary>
/// <param name="sp"></param>
/// <param name="sp_second"></param>
void AddFromSecond(StackElement* sp, StackElement* sp_second) 
{
    StackElement* current = sp_second;
    sp_second = sp_second->Next;
    current->Next = sp;
    sp = current;
}

/// <summary>
/// Проверка введеных данных
/// </summary>
/// <returns></returns>
int inputHandler() {
    int a;
    while (!(cin >> a) || (cin.peek() != '\n'))
    {
        cin.clear();
        while (cin.get() != '\n');
        cout << "Введены данные неверного формата. Попробуйте снова.\n>> ";
    }
    return a;
}

int main()
{
    setlocale(LC_ALL, "RUSSIAN");
    srand(static_cast<unsigned int>(time(0)));

    StackElement* sp = NULL;
    StackElement* sp_second = NULL;

    initStack(sp, sp_second);

    sp = PushCountRandom(5, sp);

    PrintInformationStack(sp);
}

