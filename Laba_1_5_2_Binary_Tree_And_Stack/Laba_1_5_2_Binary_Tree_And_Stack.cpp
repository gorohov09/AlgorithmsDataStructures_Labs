#include <iostream>
#include <time.h>

using namespace std;

struct TNode
{
    int Inf;
    TNode* Left;
    TNode* Right;
};

struct StackItem 
{
    int level;
    TNode* TreeItem; //Указатель на пройденную вершину дерева
    StackItem* pNext;
};

int verticesCount = 0;

void InitTree(TNode* pRoot)
{
    pRoot = NULL;
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

bool EmptyCheck(TNode* pRoot)
{
    if (pRoot == NULL)
        return true;
    else
        return false;
}

void AddNodes(TNode*& pCurrent, int aN)
{
    int Nl, Nr;
    TNode* pTemp;

    if (aN == 0)
        pCurrent = NULL;
    else
    {
        Nl = aN / 2;
        Nr = aN - Nl - 1;
        pTemp = new TNode;
        pTemp->Inf = rand() % 99;
        AddNodes(pTemp->Left, Nl);
        AddNodes(pTemp->Right, Nr);
        pCurrent = pTemp;
    }
}

void Forward(TNode* pCurrent, int level)
{
    if (pCurrent != NULL)
    {
        for (int i = 0; i < level; i++)
        {
            cout << "   ";
        }
        cout << pCurrent->Inf << endl;
        level++;
        Forward(pCurrent->Left, level);
        Forward(pCurrent->Right, level);
    }
}

void Symmetric(TNode* pCurrent, int level)
{
    if (pCurrent != NULL)
    {
        level++;
        Symmetric(pCurrent->Left, level);
        for (int i = 0; i < level - 1; i++)
        {
            cout << "   ";
        }
        cout << pCurrent->Inf << endl;
        Symmetric(pCurrent->Right, level);
    }
}

void Back(TNode* pCurrent, int level)
{
    if (pCurrent != NULL)
    {
        level++;
        Back(pCurrent->Right, level);
        for (int i = 0; i < level - 1; i++)
        {
            cout << "   ";
        }
        cout << pCurrent->Inf << endl;
        Back(pCurrent->Left, level);
    }
}

void NoRecursiveForward(TNode* pCurrent, StackItem* sp) 
{
    TNode* Current = pCurrent;
    bool stop = true;
    int level = -1;

    while (stop) 
    {
        while (Current != NULL) //Пока не достигнута пустая вершина
        {
            StackItem* newItem = new StackItem; //Создание элемента стека

            level++; //Увеличение уровня вершины
            newItem->level = level; //Заполнение всех полей
            newItem->TreeItem = Current;
            newItem->pNext = sp; //Добавление в стек
            sp = newItem;
            Current = Current->Left; //Переход к левому потомку
        }

        if (sp == NULL) //Если стек пустой, завершаем основной цикл
            stop = false; 
        else 
        {
            Current = sp->TreeItem; //Извлекаем из стека адрес текущей вершины и ее уровень
            level = sp->level;
            for (int i = 0; i < level; i++) {
                cout << "    "; //Вывод информации
            }
            cout << Current->Inf << endl; 
            Current = Current->Right; //Переходим к правому потомку вершины
            StackItem* temp = sp;
            sp = sp->pNext; //Удаление элемента стека
            delete temp;
        }
    }
}

void callMenu(TNode*& TRoot, StackItem*& sp)
{
    bool cycle = true;
    while (cycle) {
        cout << "--------------------------------------------------------------\n";
        cout << "Выберите действие:\n";
        cout << "1. Построение идеально сбалансированного двоичного дерева с заданным числом вершин.\n";
        cout << "2. Вывод дерева в прямом порядке.\n";
        cout << "3. Вывод дерева в симметричном порядке.\n";
        cout << "4. Вывод дерева в обратно-симметричном порядке.\n";
        cout << "5. Нерекурсивный вывод дерева\n";
        cout << "0. Завершение работы программы.\n";
        cout << ">> ";
        int choice = inputHandler();;
        switch (choice)
        {
        case 1:
            cout << "Какое количество вершин должно быть в дереве? ";
            verticesCount = inputHandler();
            if (verticesCount > 0)
            {
                AddNodes(TRoot, verticesCount);
                break;
            }
            else
                cout << "Количество вершин не может быть меньше или равно нулю.\n";
        case 2:
            Forward(TRoot, 0);
            break;
        case 3:
            Symmetric(TRoot, 0);
            break;
        case 4:
            Back(TRoot, 0);
            break;
        case 5:
            NoRecursiveForward(TRoot, sp);
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
    setlocale(LC_ALL, "");
    TNode* TRoot = new TNode;
    StackItem* sp = NULL;
    InitTree(TRoot);
    callMenu(TRoot, sp);
}
