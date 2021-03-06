#include <iostream>
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DBG_NEW new( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define newDBG_NEW

using namespace std;

const int ARRAY_SIZE = 5;

//First - первая занятая ячейка в массиве
//Last - первая свобожная ячейка в массиве
struct Queue
{
    int First, Last; //Указатели на начало и конец очереди
    int count; //Кол-во элементов в очереди
    int array_queue[ARRAY_SIZE]; //Массив целых чисел
};

void InitQueue(Queue* q) 
{
    q->First = 0; //Определяем пустую очередь
    q->Last = 0;
    q->count = 0;
}

bool IsEmpty(Queue* q) //Проверка пустоты
{
    if (q->count == 0)
        return true;
    else
        return false;
}

bool IsFull(Queue* q) //Проверка заполненности
{
    if (q->count == ARRAY_SIZE)
        return true;
    else
        return false;
}

void Push(Queue* q, int value) 
{
    if (q->count != ARRAY_SIZE) //Проверка возможности добавления
    {
        q->array_queue[q->Last] = value; //Добавляем элемент в массив по индексу Last
        q->Last++; //Изменяем указатель
        if (q->Last == ARRAY_SIZE) //Если Last выходит за пределы массива
            q->Last = 0; //Изменить Last на 0
        q->count++;
        cout << "Элемент успешно добавлен в очередь" << endl;
    }
    else
        cout << "Очередь заполнена, добавление невозможно";
}

void Pop(Queue* q) 
{
    if (IsEmpty(q) != true) //Проверить на возможность удаления
    {
        int value = q->array_queue[q->First]; //Извлекаем элемент по индексу First
        cout << "Элемент: " << value << " удален!" << endl;
        q->First++; //Увеличиваем указатель First
        if (q->First == ARRAY_SIZE) //Если First выходит за пределы массива
            q->First = 0; //Устанавливаем в 0
        q->count--;
    }
    else
        cout << "Очередь пустая. Удаление невозможно";
}

void ShowQueue(Queue* q) 
{
    if (IsEmpty(q) != true) 
    {
        int current = q->First;
        do
        {
            cout << q->array_queue[current] << endl;
            current++;
            if (current == ARRAY_SIZE)
                current = 0;
        } while (current != q->Last);
    }
    else
        cout << "Очередь пуста" << endl;
}

void CleanMemory(Queue* q) 
{
    delete q;
}

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

void Menu(Queue* q)
{
    bool expression = true;
    while (expression)
    {
        cout << "--------------------------------------------------------------\n";
        cout << "Выберите действие:\n";
        cout << "1. Проверить, пуста ли очередь.\n";
        cout << "2. Проверить заполненность.\n";
        cout << "3. Добавить элемент в очередь.\n";
        cout << "4. Удалить элемент из очереди.\n";
        cout << "5. Вывести состояние очереди.\n";
        cout << "0. Завершение работы программы.\n";
        cout << ">> ";
        int choice = inputHandler();;
        switch (choice)
        {
        case 1:
            if (IsEmpty(q))
                cout << "Очередь пуста" << endl;
            else
                cout << "Очередь не пуста!" << endl;
            break;
        case 2:
            if (IsFull(q))
                cout << "Очередь заполнена" << endl;
            else
                cout << "Очередь не заполнена!" << endl;
            break;
        case 3:
            int value;
            cout << "Введите значение, которое хотите добавить: ";
            cin >> value;
            Push(q, value);
            break;
        case 4:
            Pop(q);
            break;
        case 5:
            ShowQueue(q);
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

    Queue* q = new Queue;

    setlocale(LC_ALL, "RUSSIAN");
    srand(static_cast<unsigned int>(time(0)));

    InitQueue(q);

    Menu(q);

    CleanMemory(q);
    _CrtDumpMemoryLeaks();
}

