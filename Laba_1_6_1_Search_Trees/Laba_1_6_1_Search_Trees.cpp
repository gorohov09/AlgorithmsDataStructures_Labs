#include <iostream>
#include <time.h>

using namespace std;

struct TNode
{
    int Inf; //Поле, по которому упорядочем все вершины
    int count; //Счетчик дубликатов
    TNode* Left;
    TNode* Right;
};

int verticesCount = 0;

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

bool IsEmpty(TNode* TRoot) 
{
    if (TRoot == NULL) {
        return true;
    }
    else
    {
        return false;
    }
}

void Searching(TNode* TRoot, int inf)
{
    TNode* pCurrent = TRoot;
    bool stop = false;

    while (!stop && pCurrent != NULL)  //Либо нашли элемент, либо в пустом поддереве
    {
        if (pCurrent->Inf == inf) //Если нашли, то завершаем обход
        {
            stop = true;
            break;
        }
            
        if (pCurrent->Inf > inf) //Если значение ключа, меньше, текущей вершины, переходим к левому потомку
            pCurrent = pCurrent->Left;
        else
            pCurrent = pCurrent->Right; //Иначе - к правому
    }

    if (stop == true) //Если нашли
        cout << "Значение вершины: " << pCurrent->Inf << "Счетчик: " << pCurrent->count << endl;
    else //Нашли
        cout << "Вершина не найдена!" << endl;
}

void AddVertex(TNode*& pCurrent, int inf)
{
    if (pCurrent == NULL) //Если пустая ссылка
    {
        pCurrent = new TNode; //Создаем ее 
        pCurrent->Inf = inf;
        pCurrent->Left = NULL;
        pCurrent->Right = NULL;
        pCurrent->count = 1;
    }
    else 
    {
        if (pCurrent->Inf > inf) //Если значение меньше, идем в левую вершину
            AddVertex(pCurrent->Left, inf);
        else if (pCurrent->Inf < inf) //Если значение больше, идем вправую вершину
            AddVertex(pCurrent->Right, inf);
        else //Найдена вершина с заданным значением ключа, увеличиваем счетчик
            pCurrent->count++;
    }
}

void AddVertexNonRec(TNode*& pRoot, int inf)
{
    if (pRoot == NULL)
    {
        pRoot = new TNode;
        pRoot->Inf = inf;
        pRoot->Left = NULL;
        pRoot->Right = NULL;
        pRoot->count = 1;
    }
    else 
    {
        TNode* pParent = NULL; //Адрес родителя
        TNode* pCurrent = pRoot; //Адрес текущей вершины 
        while (pCurrent != NULL) 
        {
            pParent = pCurrent;
            if (pCurrent->Inf > inf)
                pCurrent = pCurrent->Left;
            else if (pCurrent->Inf < inf)
                pCurrent = pCurrent->Right;
            else 
            {
                pCurrent->count++;
                pCurrent = NULL;
            }
        }

        if (pParent->Inf > inf)
        {
            pCurrent = new TNode;
            pCurrent->count = 1;
            pCurrent->Inf = inf;
            pCurrent->Left = NULL;
            pCurrent->Right = NULL;
            pParent->Left = pCurrent;
        }
        else if (pParent->Inf < inf)
        {
            pCurrent = new TNode;
            pCurrent->count = 1;
            pCurrent->Inf = inf;
            pCurrent->Left = NULL;
            pCurrent->Right = NULL;
            pParent->Right = pCurrent;
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

void Symmetric(TNode* pCurrent)
{
    if (pCurrent != NULL)
    {
        Symmetric(pCurrent->Left);
        cout << pCurrent->Inf << "(" << pCurrent->count << ")" << " ";
        Symmetric(pCurrent->Right);
    }
}

void Changer(TNode*& p, TNode*& pTemp)
{
    if (p->Right != NULL)
        Changer(p->Right, pTemp);
    else // Правое поддерево пустое, заменитель найден, делаем обмен
    {
        pTemp->Inf = p->Inf;
        pTemp = p;
        p = p->Left;
    }
}

void DeleteNode(TNode*& pCurrent, int x) 
{
    TNode* pTemp;

    //Поиск удаляемой вершины
    if (pCurrent == NULL)
        cout << "Удаляемой вершины нет. Ничего не делаем" << endl;
    else 
    {
        if (pCurrent->Inf > x)
            DeleteNode(pCurrent->Left, x);
        else if (pCurrent->Inf < x)
            DeleteNode(pCurrent->Right, x); 
        else  //Удаляемая вершина найдена
        {
            pTemp = pCurrent;
            if (pTemp->Right == NULL)
                pCurrent = pTemp->Left;
            else if (pTemp->Left == NULL)
                pCurrent = pTemp->Right;
            else //Если потомков два, то вызывается вспомогательная функция Changer
                Changer(pCurrent->Left, pTemp); //Входи в левое поддерево, и придерживаемся правых потомков(находим ближайшую большую)

            delete pTemp;
        }
    }
}



void callMenu(TNode*& TRoot)
{
    bool cycle = true;
    while (cycle) {
        cout << "--------------------------------------------------------------\n";
        cout << "Выберите действие:\n";
        cout << "1. Создать дерево поиска с заданным числом вершин.\n";
        cout << "2. Найти необходимую вершину.\n";
        cout << "3. Вывод дерева в обратно-симметричном порядке.\n";
        cout << "4. Вывод дерева в строчку\n";
        cout << "5. Добавить вершину нерекурсивно\n";
        cout << "6 - Удалить вершину\n";
        cout << "0. Завершение работы программы.\n";
        cout << ">> ";
        int choice = inputHandler();
        int val;
        switch (choice)
        {
            case 1:
                cout << "Какое количество вершин должно быть в дереве?\n>> ";
                verticesCount = inputHandler();
                for (int i = 0; i < verticesCount; i++)
                    AddVertex(TRoot, rand() % 99 + 1);
                break;
            case 2:
                if (!IsEmpty(TRoot)) {
                    cout << "Введите значение вершины, которое хотите найти\n>> ";
                    val = inputHandler();
                    Searching(TRoot, val);
                }
                else {
                    cout << "Дерево пустое, поиск невозможен" << endl;
                }
                break;

            case 3:
                if (!IsEmpty(TRoot)) {
                    Back(TRoot, 0);
                }
                else {
                    cout << "Дерево пустое!" << endl;
                }
                break;
            case 4:
                if (!IsEmpty(TRoot)) {
                    Symmetric(TRoot);
                }
                else {
                    cout << "Дерево пустое!" << endl;
                }
                cout << endl;
                break;
            case 5:
                cout << "Введите значение вершины, которое хотите добавить\n>> ";
                val = inputHandler();
                AddVertexNonRec(TRoot, val);
                break;
            case 6:
                if (!IsEmpty(TRoot)) {
                    cout << "Введите значение вершины, которое хотите удалить\n>> ";
                    val = inputHandler();
                    DeleteNode(TRoot, val);
                }
                else {
                    cout << "Дерево пустое! Удаление невозможно!" << endl;
                }
                break;
            case 0:
                cycle = false;
                break;
            default:
                break;
        }
    }
}



int main()
{
    setlocale(LC_ALL, "");
    srand(static_cast<unsigned int>(time(0)));
    TNode* TRoot = NULL;
    callMenu(TRoot);
}

