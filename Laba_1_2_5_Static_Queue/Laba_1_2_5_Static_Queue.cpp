#include <iostream>

using namespace std;

const int ARRAY_SIZE = 5;

struct Queue
{
    int First, Last; //Указатели на начало и конец очереди
    int count; //Кол-во элементов в очереди
    int array_queue[ARRAY_SIZE]; //Массив целых чисел
};

void InitQueue(Queue* q) 
{
    q->First = 0;
    q->Last = 0;
    q->count = 0;
}

bool IsEmpty(Queue* q) 
{
    if (q->count == 0)
        return true;
    else
        return false;
}

bool IsFull(Queue* q) 
{
    if (q->count == ARRAY_SIZE)
        return true;
    else
        return false;
}

void Push(Queue* q, int value) 
{
    if (q->count != ARRAY_SIZE)
    {
        q->array_queue[q->Last] = value;
        q->Last++;
        if (q->Last == ARRAY_SIZE)
            q->Last = 0;
        q->count++;
        cout << "Элемент успешно добавлен в очередь" << endl;
    }
    else
        cout << "Очередь заполнена, добавление невозможно";
}

void Pop(Queue* q) 
{
    if (IsEmpty(q) != true)
    {
        int value = q->array_queue[q->First];
        cout << "Элемент: " << value << " удален!" << endl;
        q->First++;
        if (q->First == ARRAY_SIZE)
            q->First = 0;
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

    Queue* q = new Queue;
    InitQueue(q);
    Push(q, 55);
    ShowQueue(q);
    Push(q, 12);
    ShowQueue(q);
    Push(q, 43);
    ShowQueue(q);
    Pop(q);
    ShowQueue(q);
}

