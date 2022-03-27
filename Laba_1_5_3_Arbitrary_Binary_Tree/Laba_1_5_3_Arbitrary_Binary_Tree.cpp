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


bool SymmetricSearchVertex(TNode* pCurrent, int inf) //Рекурсивный поиск
{
    bool search = false;
    if (pCurrent != NULL) //Проверка текущей вершины на существование
    {
        if (pCurrent->Inf == inf)  //Сравниваю
        {
            search = true;
            Parent = pCurrent; //Устанавливаю адрес родительской вершины
            return search;
        }
        else 
        {
            SymmetricSearchVertex(pCurrent->Left, inf); //Ищу слева
            SymmetricSearchVertex(pCurrent->Right, inf); //Ищу справа
        }
    }

    return search;
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

        if (result_searching == true) //Если нашли родительскую вершину
        {
            if ((Parent->Left != NULL) && (Parent->Right != NULL)) //Имеет двух потомков
            {
                cout << "Добавление невозможно, так как родительская вершина имеет двух потомков" << endl;
            }
            else if ((Parent->Left == NULL) && (Parent->Right != NULL)) //Имеет одного потомка справа
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
            else if ((Parent->Left != NULL) && (Parent->Right == NULL)) //Имеет одного потомка слева
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
            else //Не имеет потомков
            {
                cout << "Родительская вершина не имеет потомков" << endl; 
                cout << "Введите значение вершины: ";
                int Inf = inputHandler();
                cout << "Введите куда добавить(1 - слева; 2 - справа): ";
                int select = inputHandler();
                while (true)
                {
                    if (select == 1) //Добавляем слева
                    {
                        TNode* temp = new TNode;
                        temp->Inf = Inf;
                        temp->Left = NULL;
                        temp->Right = NULL;
                        Parent->Left = temp;
                        break;
                    }
                    else if (select == 2) //Добавляем справа
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
    if (pCurrent != NULL) //Удаление 
    {
        DeleteTree(pCurrent->Left);
        DeleteTree(pCurrent->Right);
        cout << "Удаление вершины, со значением: " << pCurrent->Inf << endl;
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
            if (TRoot == NULL)
                cout << "Дерево пустое" << endl;
            else
                Back(TRoot, 0);
            break;
        case 4:
            if (EmptyCheck(TRoot))
                cout << "Двоичное дерево пусто, нечего удалять.\n";
            else
            {
                DeleteTree(TRoot);
                cout << "Двоичное дерево удалено.\n";
                TRoot = NULL;
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