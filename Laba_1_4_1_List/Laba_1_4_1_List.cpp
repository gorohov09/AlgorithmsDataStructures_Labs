#include <iostream>

using namespace std;

struct ListItem
{
    int inf; //Информационная часть
    ListItem* left; //Указатель на левый элемент(соседний)
    ListItem* right; //Указатель на правый элемент(соседний)
};

void InitList(ListItem*& pHead) 
{
    pHead = new ListItem; //Выделение памяти под заголовок
    pHead->left = pHead;
    pHead->right = pHead;
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

bool EmptyCheck(ListItem* pHead, ListItem* ptr) 
{
    if (ptr == pHead)
        return true;
    else
        return false;
}

void ShowForward(ListItem* pHead) 
{
    if (!EmptyCheck(pHead, pHead->right))
    {
        ListItem* pCurrent = pHead->right;
        while (pCurrent != pHead) //Условие получение головы списка
        {
            cout << pCurrent->inf << " ";
            pCurrent = pCurrent->right;
        }
        cout << endl;
    }
    else
        cout << "Список пустой" << endl;
}

void ShowBack(ListItem* pHead) 
{
    if (!EmptyCheck(pHead, pHead->right))
    {
        ListItem* pCurrent = pHead->left;
        while (pCurrent != pHead)
        {
            cout << pCurrent->inf << " ";
            pCurrent = pCurrent->left;
        }
        cout << endl;
    }
    else
        cout << "Список пустой" << endl;
}

void FindElementForward(ListItem* pHead) 
{
    if (EmptyCheck(pHead, pHead->right))
        cout << "Список пуст! Нечего искать.\n";
    else
    {
        int pos = 1;
        cout << "Введите значение элемента, который нужно найти: ";
        int inf = inputHandler();
        ListItem* Current = pHead->right; //Установка текущего указателя в адрес первого элемента
        while (Current != pHead)
        {
            if (Current->inf == inf)
            {
                cout << endl << "Позиция элемента \"" << Current->inf << "\" в списке равна " << pos << endl;
                break;
            }
            pos++;
            Current = Current->right;
        }
        if (Current == NULL)
            cout << "Элемент не найден.\n";
    }
}

void FindElementBack(ListItem* pHead)
{
    if (EmptyCheck(pHead, pHead->right))
        cout << "Список пуст! Нечего искать.\n";
    else
    {
        int pos = 1;
        cout << "Введите значение элемента, который нужно найти: ";
        int inf = inputHandler();
        ListItem* Current = pHead->left; //Установка текущего указателя в адрес первого элемента
        while (Current != pHead)
        {
            if (Current->inf == inf)
            {
                cout << endl << "Позиция элемента \"" << Current->inf << "\" в списке равна " << pos << endl;
                break;
            }
            pos++;
            Current = Current->left;
        }
        if (Current == NULL)
            cout << "Элемент не найден.\n";
    }
}

void PushAfter(ListItem*& pHead) 
{
    ListItem* pTemp = new ListItem;

    if (!EmptyCheck(pHead, pHead->right))
    {
        cout << "Введите значение элемента, после которого нужно вставить новый: ";
        int pos = inputHandler();
        ListItem* pCurrent = pHead->right;
        while (pCurrent != pHead)
        {
            if (pCurrent->inf == pos)
                break;
            pCurrent = pCurrent->right;
        }
        if (pCurrent == pHead)
            cout << "Элемент не найден" << endl;
        else 
        {
            cout << "Введите значение нового элемента: ";
            int elem = inputHandler();
            pTemp->inf = elem;
            pTemp->right = pCurrent->right;
            pTemp->left = pCurrent;
            pCurrent->right->left = pTemp;
            pCurrent->right = pTemp;
        }
    }
    else
    {
        cout << "Введите значение нового элемента: ";
        int elem = inputHandler();
        pTemp->inf = elem;
        pTemp->right = pHead;
        pTemp->left = pHead;
        pHead->right = pTemp;
        pHead->left = pTemp;
    }
}

void PushBefore(ListItem*& pHead) 
{
    ListItem* pTemp = new ListItem;

    if (!EmptyCheck(pHead, pHead->right))
    {
        cout << "Введите значение элемента, после которого нужно вставить новый: ";
        int pos = inputHandler();
        ListItem* pCurrent = pHead->right;
        while (pCurrent != pHead)
        {
            if (pCurrent->inf == pos)
                break;
            pCurrent = pCurrent->right;
        }
        if (pCurrent == pHead)
            cout << "Элемент не найден" << endl;
        else
        {
            cout << "Введите значение нового элемента: ";
            int elem = inputHandler();
            pTemp->inf = elem;
            pTemp->left = pCurrent->left;
            pTemp->right = pCurrent;
            pCurrent->left->right = pTemp;
            pCurrent->left = pTemp;
        }
    }
}

void Pop(ListItem*& pHead) 
{
    if (EmptyCheck(pHead, pHead->right))
        cout << "Список пуст! Удалять нечего...\n";
    else
    {
        cout << endl << "Введите значение удаляемого элемента: ";
        int pos = inputHandler();
        ListItem* pCurrent = pHead->right;
        while (pCurrent != pHead)
        {
            if (pCurrent->inf == pos)
                break;
            pCurrent = pCurrent->right;
        }
        if (pCurrent == pHead)
            cout << "Элемент не найден.\n";
        else
        {
            pCurrent->left->right = pCurrent->right;
            pCurrent->right->left = pCurrent->left;
            delete pCurrent;
        }
    }
}

void CallMenu(ListItem* pHead)
{
    bool cycle = true;
    while (cycle) {
        cout << "--------------------------------------------------------------\n";
        cout << "Выберите действие:\n";
        cout << "1. Вывести текущее состояние списка на экран в прямом направлении.\n";
        cout << "2. Вывести текущее состояние списка на экран в обратном направлении.\n";
        cout << "3. Найти определенный элемент в списке в прямом направлении.\n";
        cout << "4. Найти определенный элемент в списке в обратном направлении.\n";
        cout << "5. Добавить новый элемент в список.\n";
        cout << "6. Удалить элемент из списка.\n";
        cout << "0. Завершение работы программы.\n";
        cout << ">> ";
        int choice = inputHandler();;
        switch (choice)
        {
        case 1:
            ShowForward(pHead);
            break;
        case 2:
            ShowBack(pHead);
            break;
        case 3:
            FindElementForward(pHead);
            break;
        case 4:
            FindElementBack(pHead);
            break;
        case 5:
            if (EmptyCheck(pHead, pHead->right))
                PushAfter(pHead);
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
                        PushBefore(pHead);
                        break;
                    }
                    else if (choice == 2)
                    {
                        PushAfter(pHead);
                        break;
                    }
                    else
                        cout << "\nВы пытаетесь выбрать несуществующее действие. Попробуйте еще раз.\n";
                }
            }
            break;
        case 6:
            Pop(pHead);
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
    InitList(pHead);
    CallMenu(pHead);
}

