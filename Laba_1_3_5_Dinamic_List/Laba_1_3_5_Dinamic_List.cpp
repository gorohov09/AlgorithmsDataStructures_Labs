#include <iostream>

using namespace std;

struct ListItem
{
    int value;
    ListItem* Next; //Указатель на следующий элемент
};

void InitList(ListItem*& Head, ListItem*& Sp)
{
    Head = new ListItem(); //Выделение памяти под заголовок
    Head->Next = NULL; //Установка пустой ссылочной части заголовка
    Sp = new ListItem();
    Sp->Next = NULL;
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

bool EmptyCheck(ListItem* ptr)
{
    if (ptr->Next == NULL)
        return true;
    else
        return false;
}

void ShowList(ListItem* Head) 
{
    if (!EmptyCheck(Head))
    {
        ListItem* Current = Head->Next;
        while (Current != NULL)
        {
            cout << Current->value << " ";
            Current = Current->Next;
        }
        cout << endl;
    }
    else
        cout << "Список пустой" << endl;
}

void FindElement(ListItem* Head)
{
    if (EmptyCheck(Head))
        cout << "Список пуст! Нечего искать.\n";
    else
    {
        int pos = 1;
        cout << "Введите значение элемента, который нужно найти: ";
        int inf = inputHandler();
        ListItem* Current = Head->Next; //Установка текущего указателя в адрес первого элемента
        while (Current != NULL)
        {
            if (Current->value == inf)
            {
                cout << endl << "Позиция элемента \"" << Current->value << "\" в списке равна " << pos << endl;
                break;
            }
            pos++;
            Current = Head->Next;
        }
        if (Current == NULL)
            cout << "Элемент не найден.\n";
    }
}

void PushBefore(ListItem* Head)
{
    ListItem* Temp = new ListItem;

    cout << "Введите значение элемента, перед которым нужно вставить новый: ";
    int pos = inputHandler();
    ListItem* Current = Head->Next;
    ListItem* Prev = Head;
    while (Current != NULL)
    {
        if (Current->value == pos)
            break;
        Prev = Current;
        Current = Current->Next;
    }
    if (Current == NULL)
        cout << "Элемент не найден.\n";
    else
    {
        cout << "Введите значение нового элемента: ";
        int elem = inputHandler();
        Temp->value = elem;
        Temp->Next = Current;
        Prev->Next = Temp;
    }
}

void PushAfter(ListItem* Head)
{
    ListItem* Temp = new ListItem;

    if (EmptyCheck(Head))
    {
        cout << "Введите значение нового элемента: ";
        int elem = inputHandler();
        Temp->value = elem;
        Temp->Next = NULL;
        Head->Next = Temp;
    }
    else
    {
        cout << "Введите значение элемента, после которого нужно вставить новый: ";
        int pos = inputHandler();
        ListItem* Current = Head->Next;
        while (Current != NULL)
        {
            if (Current->value == pos)
                break;
            Current = Current->Next;
        }
        if (Current == NULL)
            cout << "Элемент не найден.\n";
        else
        {
            cout << "Введите значение нового элемента: ";
            int elem = inputHandler();
            Temp->value = elem;
            Temp->Next = Current->Next;
            Current->Next = Temp;
        }
    }
}

void Pop(ListItem* Head, ListItem* Sp)
{
    if (EmptyCheck(Head))
        cout << "Список пуст! Удалять нечего...\n";
    else
    {
        cout << endl << "Введите значение удаляемого элемента: ";
        int pos = inputHandler();
        ListItem* Current = Head->Next; //Текущий элемент
        ListItem* Prev = Head; //Адрес элемента предшественника
        while (Current != NULL)
        {
            if (Current->value == pos)
                break;
            Prev = Current;
            Current = Current->Next;
        }
        if (Current == NULL)
            cout << "Элемент не найден.\n";
        else
        {
            Prev->Next = Current->Next; //Изменение ссылочнйо части его предшественника
            Current->Next = Sp->Next; //
            Sp->Next = Current;
        }
    }
}

void СallMenu(ListItem* Head, ListItem* sp)
{
    bool cycle = true;
    while (cycle) {
        cout << "--------------------------------------------------------------\n";
        cout << "Выберите действие:\n";
        cout << "1. Вывести текущее состояние списка на экран.\n";
        cout << "2. Найти определенный элемент в списке.\n";
        cout << "3. Добавить новый элемент в список.\n";
        cout << "4. Удалить элемент из списка и добавить его во вспомогательный список (стек).\n";
        cout << "5. Вывести текущее состояние вспомогательного списка (стека) на экран.\n";
        cout << "0. Завершение работы программы.\n";
        cout << ">> ";
        int choice = inputHandler();;
        switch (choice)
        {
        case 1:
            ShowList(Head);
            break;
        case 2:
            FindElement(Head);
            break;
        case 3:
            if (EmptyCheck(Head))
                PushAfter(Head);
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
                        PushBefore(Head);
                        break;
                    }
                    else if (choice == 2)
                    {
                        PushAfter(Head);
                        break;
                    }
                    else
                        cout << "\nВы пытаетесь выбрать несуществующее действие. Попробуйте еще раз.\n";
                }
            }
            break;
        case 4:
            Pop(Head, sp);
            break;
        case 5:
            ShowList(sp);
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
    ListItem* pHead = NULL;
    ListItem* sp = NULL;
    InitList(pHead, sp);
    СallMenu(pHead, sp);
}

