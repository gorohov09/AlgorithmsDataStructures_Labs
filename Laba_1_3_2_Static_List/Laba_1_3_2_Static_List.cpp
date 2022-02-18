#include <iostream>

using namespace std;

const int ARRAY_SIZE = 10; //размер массива

struct List
{
    int count;
    int List[ARRAY_SIZE];
};

void InitList(List* my_list) 
{
    my_list->count = 0;
}

bool EmptyCheck(List* my_list)
{
    if (my_list->count == 0)
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

void Show(List* my_list)
{
    if (!EmptyCheck(my_list))
    {
        for (int i = 0; i < my_list->count; i++)
            cout << my_list->List[i] << " ";
        cout << endl;
    }
    else
        cout << "\nСписок пуст.\n";
}

void FindElement(List* my_list)
{
    if (EmptyCheck(my_list))
        cout << "Список пуст! Нечего искать.\n";
    else
    {
        cout << "Введите элемент: ";
        bool isFound = false;
        int element = inputHandler();
        for (int i = 0; i < my_list->count; i++)
        {
            if (my_list->List[i] == element)
            {
                cout << "Позиция элемента \"" << my_list->List[i] << "\" в списке равна " << i + 1 << endl;
                isFound = true;
                break;
            }
        }
        if (!(isFound))
            cout << endl << "Элемент не найден." << endl;
    }
}

void Push(List* my_list)
{
    if (FilledCheck(my_list))
        cout << "Cписок заполнен! Добавление невозможно.\n";
    else
    {
        int temp;
        cout << "Введите значение нового элемента:" << endl;
        int elem = inputHandler();
        if (my_list->count == 0)
            my_list->List[0] = elem;
        else
        {
            temp = my_list->count;
            for (int i = 0; i < my_list->count; i++)
            {
                if (my_list->List[i] >= elem)
                {
                    temp = i;
                    break;
                }
            }
            for (int i = my_list->count; i > temp; i--)
            {
                my_list->List[i] = my_list->List[i - 1];
            }
            my_list->List[temp] = elem;
        }
        my_list->count++;
    }
}
// удаление элемента
void Pop(List* my_list)
{
    if (EmptyCheck(my_list))
        cout << "Список пуст! Удалять нечего...\n";
    else
    {
        bool isFound = false;
        cout << endl << "Введите значение удаляемого элемента: ";
        int element = inputHandler();
        int current;
        for (int i = 0; i < my_list->count; i++)
        {
            if (my_list->List[i] == element)
            {
                isFound = true;
                current = i;
                break;
            }
        }
        if (isFound)
        {
            for (int i = current; i < my_list->count - 1; i++)
            {
                my_list->List[i] = my_list->List[i + 1];
            }
            my_list->count--;
        }
        else
            cout << endl << "Элемент не найден." << endl;
    }
}



void CallMenu(List* l)
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
        int choice = inputHandler();;
        switch (choice)
        {
        case 1:
            Show(l);
            break;
        case 2:
            FindElement(l);
            break;
        case 3:
            Push(l);
            break;
        case 4:
            Pop(l);
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
    List* list = new List;
    InitList(list);
    CallMenu(list);
    return 0;
}


