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
} *sp, *sp_second;

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

StackElement* Push(int value, StackElement* sp)
{
    StackElement* pTemp = new StackElement;

    pTemp->Value = value;

    pTemp->Next = sp;

    sp = pTemp;

    return sp;
}

int main()
{
    initStack(sp, sp_second);

    sp = Push(5, sp);
    sp = Push(10, sp);
    sp = Push(12, sp);
    PrintInformationStack(sp);
}

