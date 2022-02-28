#include <iostream>

using namespace std;

const int ARRAY_SIZE = 11;

struct ListItem
{
    int Inf;
    int Next;
};

struct List 
{
    ListItem ListArray[ARRAY_SIZE];
    int count;
};

void InitList(List* my_list) 
{
    my_list->count = 0;
    my_list->ListArray[0].Next = 0;
    for (int i = 1; i < ARRAY_SIZE; i++)
        my_list->ListArray[i].Next = -1;
}

int inputHandler()
{
    int a;
    while (!(cin >> a) || (cin.peek() != '\n'))
    {
        cin.clear();
        while (cin.get() != '\n');
        cout << "Введены данные неверного формата. Попробуйте снова.\n>> ";
    }
    return a;
}

bool EmptyCheck(List* my_list)
{
    if (my_list->ListArray[0].Next == 0)
        return true;
    else
        return false;
}

bool FilledCheck(List* my_list)
{
    if (my_list->count == ARRAY_SIZE)
        return true;
    else
        return false;
}

void Show(List* my_list)
{
    if (!EmptyCheck(my_list))
    {
        int Current = my_list->ListArray[0].Next;

        while (Current != 0)
        {
            if (Current == -1)
                continue;
            cout << my_list->ListArray[Current].Inf << " ";
            Current = my_list->ListArray[Current].Next;
        }
        cout << "\n";
    }
    else
        cout << "Список пустой" << endl;
}

int FindElement(List* my_list, int element) 
{
    if (!EmptyCheck(my_list))
    {
        int Current = my_list->ListArray[0].Next;
        int pos = 1;
        while (Current != 0)
        {
            if (my_list->ListArray[Current].Inf == element) 
            {
                cout << "Элемент " << element << " найден. Позиция: " << pos << endl;
                return pos;
            }
                
            Current = my_list->ListArray[Current].Next;
            pos++;
        }
        if (Current == 0)
            cout << "Ничего не найдено" << endl;
        return -1;
        cout << "\n";
    }
    else
        cout << "Список пустой. Поиск невозможен" << endl;
        return -1;
}


int memoryManager(List* my_list)
{
    int freePos;
    for (int i = 1; i < ARRAY_SIZE; i++)
    {
        if (my_list->ListArray[i].Next == -1)
        {
            freePos = i;
            break;
        }
    }
    return freePos;
}

void PushAfter(List* my_list) 
{
    if (FilledCheck(my_list))
        cout << "Cписок заполнен! Добавление невозможно.\n";
    else
    {
        if (EmptyCheck(my_list))
        {
            int temp = 1;
            cout << "Введите значение нового элемента: ";
            int elem = inputHandler();
            my_list->ListArray[temp].Inf = elem;
            my_list->ListArray[temp].Next = 0;
            my_list->ListArray[0].Next = temp;
            my_list->count++;
        }
        else
        {
            cout << "Введите значение элемента, после которого нужно вставить новый: ";
            int pos = inputHandler();
            int current = my_list->ListArray[0].Next;
            while (current != 0)
            {
                if (my_list->ListArray[current].Inf == pos)
                    break;
                current = my_list->ListArray[current].Next;
            }
            if (current == 0)
                cout << "Элемент не найден.\n";
            else
            {
                int temp = memoryManager(my_list); // свободная ячейка
                cout << "Введите значение нового элемента: ";
                int elem = inputHandler();
                my_list->ListArray[temp].Inf = elem;
                my_list->ListArray[temp].Next = my_list->ListArray[current].Next;
                my_list->ListArray[current].Next = temp;
                my_list->count++;
            }
        }
    }
    
}

void PushBefore(List* my_list) 
{
    if (!FilledCheck(my_list)) 
    {
        cout << "Введите значение элемента, перед которым нужно вставить новый: ";
        int pos = inputHandler();
        int current = my_list->ListArray[0].Next;
        int prev = 0;
        while (current != 0)
        {
            if (my_list->ListArray[current].Inf == pos)
                break;
            prev = current;
            current = my_list->ListArray[current].Next;
        }
        if (current == 0)
            cout << "Элемент не найден.\n";
        else
        {
            int temp = memoryManager(my_list);
            cout << "Введите значение нового элемента: ";
            int elem = inputHandler();
            my_list->ListArray[temp].Inf = elem;
            my_list->ListArray[temp].Next = current;
            my_list->ListArray[prev].Next = temp;
            my_list->count++;
        }
    }  
    else
    {
        cout << "Добавление невозможно" << endl;
    }
}

void Pop(List* my_list) 
{
    if (!EmptyCheck(my_list)) 
    {
        cout << endl << "Введите значение удаляемого элемента: ";
        int pos = inputHandler();
        int current = my_list->ListArray[0].Next;
        int prev = 0;
        while (current != 0)
        {
            if (my_list->ListArray[current].Inf == pos)
                break;
            prev = current;
            current = my_list->ListArray[current].Next;
        }
        if (current == 0)
            cout << "Элемент не найден.\n";
        else
        {
            my_list->ListArray[prev].Next = my_list->ListArray[current].Next;
            my_list->ListArray[current].Next = -1;
            my_list->count--;
        }
    }   
    else
    {
        cout << "Список пустой. Удаление невозможно" << endl;
    }
    
}

void CleanMemory(List* my_list) 
{
    delete my_list;
}

void Menu(List* my_list)
{
    bool cycle = true;
    while (cycle) {
        cout << "--------------------------------------------------------------\n";
        cout << "Выберите действие:\n";
        cout << "1. Вывести текущее состояние списка на экран\n";
        cout << "2. Найти определенный элемент в списке\n";
        cout << "3. Добавить новый элемент в список\n";
        cout << "4. Удалить элемент из списка\n";
        cout << "0. Завершение работы программы.\n";
        cout << ">> ";
        int choice = inputHandler();
        int element;
        switch (choice)
        {
        case 1:
            Show(my_list);
            break;
        case 2:
            cout << "Введите элемент, который нужно найти: ";
            element = inputHandler();
            FindElement(my_list, element);
            break;
        case 3:
            if (EmptyCheck(my_list))
                PushAfter(my_list);
            else
            {
                int choice;
                while (true)
                {
                    cout << "Выберите действие:\n";
                    cout << "1. Добавить новый элемент перед заданным.\n";
                    cout << "2. Добавить новый элемент после заданного.\n";
                    choice = inputHandler();
                    if (choice == 1)
                    {
                        PushBefore(my_list);
                        break;
                    }
                    else if (choice == 2)
                    {
                        PushAfter(my_list);
                        break;
                    }
                    else
                        cout << "\nВы пытаетесь выбрать несуществующее действие. Попробуйте еще раз.\n";
                }
            }
            break;
        case 4:
            Pop(my_list);
            break;
        case 0:
            cycle = false;
            break;
        default:
            cout << "Вы пытаетесь выбрать несуществующее действие. Попробуйте еще раз.\n";
            break;
        }
    }
}


int main()
{
    setlocale(LC_ALL, "Rus");
    List* my_list = new List;
    InitList(my_list);
    Menu(my_list);
    CleanMemory(my_list);
}

