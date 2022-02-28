#include <iostream>
#include <ctime>
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DBG_NEW new( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define newDBG_NEW

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
        StackElement* pCurrent = sp; //Вспомогательная ссылочная переменная(на каждом шаге определяет адрес текущего элемента)
        while (pCurrent != NULL)
        {
            cout << pCurrent->Value << endl; //Выводим информацию
            pCurrent = pCurrent->Next; //Меняем указатель на следующий элемент
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
    try
    {
        StackElement* pTemp = new StackElement; //Выделяем память для размещения нового элемента с помощью вспомогательной ссылочной переменной

        pTemp->Value = value; //Заносим информацию

        pTemp->Next = sp; //установливаем адресную часть нового элемента таким образом, чтобы она определяла адрес бывшего вершинного элемента

        sp = pTemp; //Изменяем адрес вершины стека

        return sp; //Возвращаем новый адрес
    }
    catch (const std::exception&)
    {
        cout << "Стек заполнен" << endl;
    }
}

/// <summary>
/// Удаление элемента из главного стека
/// </summary>
/// <param name="sp"></param>
/// <returns></returns>
void Pop(StackElement*& sp)
{
    if (!isStackEmpty(sp))
    {
        StackElement* pTemp = sp; //С помощью вспомогательной переменной адресуем удаляемый элемент
        sp = sp->Next; //Изменяем значение переменной sp на адрес новой вершины стека
        delete pTemp; //Обрабатываем удаленный элемент
    }
    else
        cout << "Главный стек пуст";
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
void PushToSecond(StackElement*& sp, StackElement*& sp_second) 
{
    StackElement* current = sp; //Ссылаемся на вершину главного стека
    sp = sp->Next; //Меняем вершину главного стека
    current->Next = sp_second; //Делаем временную переменную головой второстепенного стека
    sp_second = current;
}

/// <summary>
/// Перемещение верхнего элемента вспомогательного стека в главный
/// </summary>
/// <param name="sp"></param>
/// <param name="sp_second"></param>
void AddFromSecond(StackElement*& sp, StackElement*& sp_second) 
{
    StackElement* current = sp_second;
    sp_second = sp_second->Next;
    current->Next = sp;
    sp = current;
}

void CleanMemory(StackElement*& sp) 
{
    if (isStackEmpty(sp))
        cout << "\nСтек пуст, очистка памяти невозможна\n";
    else
    {
        while (sp != NULL)
        {
            Pop(sp);
        }
        cout << "Очистка памяти выполнена успешно" << endl;
    }
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

void Menu(StackElement*& sp, StackElement*& sp_second) 
{
    bool expression = true;
    while (expression)
    {
        cout << "--------------------------------------------------------------\n";
        cout << "Выберите действие:\n";
        cout << "1. Проверить, пуст ли стек.\n";
        cout << "2. Вывести состояние главного стека.\n";
        cout << "3. Вывести состояние вспомогательного.\n";
        cout << "4. Добавить элемент в вершину главного стека.\n";
        cout << "5. Удалить элемент из вершины главного стека.\n";
        cout << "6. Добавление нескольких случайных элементов в вершину главного стека.\n";
        cout << "0. Завершение работы программы.\n";
        cout << ">> ";
        int choice = inputHandler();;
        switch (choice)
        {
        case 1:
            if (isStackEmpty(sp))
                cout << "\nГлавный стек пуст.\n";
            else
                cout << "\nГлавный стек не пуст.\n";
            break;
        case 2:
            PrintInformationStack(sp);
            break;
        case 3:
            PrintInformationStack(sp_second);
            break;
        case 4:
            int choice;
            cout << "Выберите действие:\n";
            cout << "1. Действительно создать новоый элемент.\n";
            cout << "2. Выбрать его с вершины вспомогательного стека.\n>> ";
            cin >> choice;
            if (choice == 1)
            {
                int value;
                cout << "Введите значение, которое хотите занести: ";
                cin >> value;
                sp = Push(value, sp);
                cout << "\nНовый элемент добавлен.\n";
            }
            else if (choice == 2)
            {
                if (isStackEmpty(sp_second))
                {
                    cout << "Вспомогательный список пуст.\n";
                    break;
                }
                AddFromSecond(sp, sp_second);
                cout << "\nЭлемент перемещён.\n";
            }
            else
                cout << "Вы пытаетесь выбрать несуществующее действие. Попробуйте еще раз.\n";
            break;
        case 5:
            if (isStackEmpty(sp))
            {
                cout << "Главный стек пуст, удаление невозможно.\n";
                break;
            }
            int deleteChoice;
            cout << "Выберите действие:\n";
            cout << "1. Действительно удалить элемент с освобождением памяти.\n";
            cout << "2. Включить его в вершину вспомогательного стека удаленных элементов.\n>> ";
            cin >> deleteChoice;
            if (deleteChoice == 1)
            {
                Pop(sp);
                cout << "\nЭлемент из вершины стека удалён.\n";
            }
            else if (deleteChoice == 2)
            {
                PushToSecond(sp, sp_second);
                cout << "Элемент из вершины стека включён в вершину вспомогательного стека.\n";
            }
            else
                cout << "Вы пытаетесь выбрать несуществующее действие. Попробуйте еще раз.\n";
            break;
        case 6:
            int count;
            cout << "Сколько элементов Вы хотите добавить? ";
            cin >> count;
            sp = PushCountRandom(count, sp);
            break;
        case 0:
            expression = false;
            break;
        default:
            cout << "Вы пытаетесь выбрать несуществующее действие. Попробуйте еще раз.\n";
            break;
        }
    }
}

int main()
{
    setlocale(LC_ALL, "RUSSIAN");
    srand(static_cast<unsigned int>(time(0)));

    StackElement* sp = NULL;
    StackElement* sp_second = NULL;

    initStack(sp, sp_second);

    Menu(sp, sp_second);
    CleanMemory(sp);
    CleanMemory(sp_second);
    _CrtDumpMemoryLeaks();
}

