#include <iostream>
#include <time.h>

using namespace std;

struct TNode
{
    int Inf;
    TNode* Left;
    TNode* Right;
} *Parent;

int verticesCount = 0;

void InitTree(TNode*& pRoot)
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


bool SymmetricSearchVertex(TNode* pCurrent, int inf)
{
    bool search = false;
    if (pCurrent != NULL) 
    {
        if (pCurrent->Inf == inf) 
        {
            search = true;
            Parent = pCurrent;
            return search;
        }
        else 
        {
            SymmetricSearchVertex(pCurrent->Left, inf);
            SymmetricSearchVertex(pCurrent->Right, inf);
        }
    }
}

void AddVertex(TNode*& pCurrent) 
{
    if (EmptyCheck(pCurrent)) 
    {
        TNode* temp = new TNode;
        cout << "Введите значение корня дерева: ";
        temp->Inf = inputHandler();
        temp->Left = NULL;
        temp->Right = NULL;
        pCurrent = temp;
        verticesCount++;
    }
    else
    {
        cout << "Введите значение родительской вершины: ";
        int parentInf = inputHandler();

        bool result_searching = SymmetricSearchVertex(pCurrent, parentInf);

        if (result_searching == true) 
        {
            if ((Parent->Left != NULL) && (Parent->Right != NULL)) 
            {
                cout << "Добавление невозможно, так как родительская вершина имеет двух потомков" << endl;
            }
            else if ((Parent->Left == NULL) && (Parent->Right != NULL)) 
            {
                cout << "Родительская вершина имеет потомка справа. Добавление будет слева" << endl;
                cout << "Введите значение вершины: ";
                int leftInf = inputHandler();
                TNode* temp = new TNode;
                temp->Inf = leftInf;
                temp->Left = NULL;
                temp->Right = NULL;
                Parent->Left = temp;
                verticesCount++;
            }
            else if ((Parent->Left != NULL) && (Parent->Right == NULL)) 
            {
                cout << "Родительская вершина имеет потомка слева. Добавление будет справа" << endl;
                cout << "Введите значение вершины: ";
                int rightInf = inputHandler();
                TNode* temp = new TNode;
                temp->Inf = rightInf;
                temp->Left = NULL;
                temp->Right = NULL;
                Parent->Right = temp;
                verticesCount++;
            }
            else 
            {
                cout << "Родительская вершина не имеет потомков" << endl;
                cout << "Введите значение вершины: ";
                int Inf = inputHandler();
                cout << "Введите куда добавить(1 - слева; 2 - справа): ";
                int select = inputHandler();
                while (true)
                {
                    if (select == 1)
                    {
                        TNode* temp = new TNode;
                        temp->Inf = Inf;
                        temp->Left = NULL;
                        temp->Right = NULL;
                        Parent->Left = temp;
                        break;
                    }
                    else if (select == 2)
                    {
                        TNode* temp = new TNode;
                        temp->Inf = Inf;
                        temp->Left = NULL;
                        temp->Right = NULL;
                        Parent->Right = temp;
                        break;
                    }
                    else
                        cout << "Такого выбора нет" << endl;
                }
                verticesCount++;
            }
        }
        else 
        {
            cout << "Такой вершины нет!" << endl;
        }
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

void DeleteTree(TNode*& pCurrent) 
{
    if (pCurrent != NULL) 
    {
        DeleteTree(pCurrent->Left);
        DeleteTree(pCurrent->Right);
        delete pCurrent;
        verticesCount--;
    }
}


void callMenu(TNode*& TRoot)
{
    bool cycle = true;
    while (cycle) {
        cout << "--------------------------------------------------------------\n";
        cout << "Выберите действие:\n";
        cout << "1. Поиск вершины с заданным значением информационной части.\n";
        cout << "2. Добавление левого или правого потомка для заданной вершины.\n";
        cout << "3. Вывод дерева в обратно-симметричном порядке.\n";
        cout << "4. Уничтожение всего дерева.\n";
        cout << "0. Завершение работы программы.\n";
        cout << ">> ";
        int choice = inputHandler();;
        switch (choice)
        {
        case 1:
            if (EmptyCheck(TRoot))
                cout << "Двоичное дерево пусто, искать нечего.\n";
            else
            {
                cout << "Введите значение вершины, которую нужно найти: ";
                int vertex_inf = inputHandler();
                Parent = NULL;
                SymmetricSearchVertex(TRoot, vertex_inf);
                if (Parent != NULL)
                    cout << "Элемент " << vertex_inf << " присутствует в дереве.\n";
                else
                    cout << "Элемента " << vertex_inf << " в дереве нет.\n";
            }
            break;
        case 2:
            AddVertex(TRoot);
            break;
        case 3:
            Back(TRoot, 0);
            break;
        case 4:
            if (EmptyCheck(TRoot))
                cout << "Двоичное дерево пусто, нечего удалять.\n";
            else
            {
                DeleteTree(TRoot);
                cout << "Двоичное дерево удалено.\n";
            }
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
    InitTree(TRoot);
    callMenu(TRoot);
}