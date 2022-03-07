#include <iostream>

using namespace std;

int index = 1;

struct SubListItem
{
    int inf;
    SubListItem* pSupList;
};

struct MainListItem
{
    SubListItem* pSubList;
    MainListItem* pMainList;
    int value;
};

void InitList(MainListItem*& HeadMain) 
{
    HeadMain = new MainListItem;
    HeadMain->pMainList = NULL;
    HeadMain->pSubList = NULL;
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

bool MainEmptyCheck(MainListItem* HeadMain) 
{
    if (HeadMain->pMainList == NULL)
        return true;
    else
        return false;
}

bool SubEmptyCheck(SubListItem* ptr)
{
    if (ptr == NULL)
        return true;
    else
        return false;
}

void ShowList(MainListItem* HeadMain) 
{
    if (!MainEmptyCheck(HeadMain))
    {
        MainListItem* pCurrentMain = HeadMain->pMainList;
        while (pCurrentMain != NULL)
        {
            cout << "Список " << pCurrentMain->value << ": ";
            SubListItem* pCurrentSub = pCurrentMain->pSubList;
            while (pCurrentSub != NULL)
            {
                cout << pCurrentSub->inf << " ";
                pCurrentSub = pCurrentSub->pSupList;
            }
            pCurrentMain = pCurrentMain->pMainList;
            cout << endl;
        }
    }
    else
        cout << "Главный список пуст" << endl;
}

void FindElement(MainListItem* HeadMain) 
{
    if (!MainEmptyCheck(HeadMain))
    {
        int pos = 1;
        bool find = false;
        cout << "Введите значение элемента, который нужно найти: ";
        int inf = inputHandler();

        MainListItem* pCurrentMain = HeadMain->pMainList;
        while (pCurrentMain != NULL)
        {
            SubListItem* pCurrentSub = pCurrentMain->pSubList;
            while (pCurrentSub != NULL)
            {
                if (pCurrentSub->inf == inf) 
                {
                    find = true;
                    cout << "Элемент найден в списке № " << pCurrentMain->value << ". Позиция: " << pos << endl;
                    break;
                }
                pCurrentSub = pCurrentSub->pSupList;
                pos++;
            }
            if (find)
                break;

            pCurrentMain = pCurrentMain->pMainList;
            cout << endl;
        }
        if (find == false)
            cout << "Элемент не найден" << endl;

    }
    else
        cout << "Главный список пуст" << endl;
}

void MainPushBefore(MainListItem*& HeadMain) 
{
    MainListItem* pTemp = new MainListItem;
    MainListItem* prevMain = HeadMain;

    cout << "Введите номер списка, перед которым нужно вставить новый: ";
    int pos = inputHandler();
    MainListItem* pCurrentMain = HeadMain->pMainList;
    while (pCurrentMain != NULL) 
    {
        if (pCurrentMain->value == pos)
            break;
        prevMain = pCurrentMain;
        pCurrentMain = pCurrentMain->pMainList;
    }
    if (pCurrentMain == NULL)
        cout << "Список не найден.\n";
    else
    {
        pTemp->value = index;
        pTemp->pMainList = pCurrentMain;
        pTemp->pSubList = NULL;
        prevMain->pMainList = pTemp;
        index++;
    }
}

void MainPushAfter(MainListItem*& HeadMain) 
{
    MainListItem* pTemp = new MainListItem;

    if (!MainEmptyCheck(HeadMain)) 
    {
        cout << "Введите номер списка, после которого нужно вставить новый: ";
        int pos = inputHandler();
        MainListItem* pCurrentMain = HeadMain->pMainList;
        while (pCurrentMain != NULL) 
        {
            if (pCurrentMain->value == pos)
                break;
            pCurrentMain = pCurrentMain->pMainList;
        }
        if (pCurrentMain == NULL)
            cout << "Список не найден" << endl;
        else 
        {
            pTemp->value = index;
            pTemp->pSubList = NULL;
            pTemp->pMainList = pCurrentMain->pMainList;
            pCurrentMain->pMainList = pTemp;
            index++;
        }
    }
    else 
    {
        pTemp->value = index;
        pTemp->pSubList = NULL;
        pTemp->pMainList = NULL;
        HeadMain->pMainList = pTemp;
        index++;
    }
}

void SubPushBefore(MainListItem*& pCurrentMain) 
{
    SubListItem* pTemp = new SubListItem;
    SubListItem* prevSub = NULL;

    cout << "Введите значение элемента, перед которым нужно вставить новый: ";
    int pos = inputHandler();

    SubListItem* pCurrentSub = pCurrentMain->pSubList;
    while (pCurrentSub != NULL) 
    {
        if (pCurrentSub->inf == pos)
            break;
        prevSub = pCurrentSub;
        pCurrentSub = pCurrentSub->pSupList;
    }

    if (pCurrentSub == NULL)
        cout << "Элемент не найден" << endl;
    else 
    {
        cout << "Введите значение нового элемента: ";
        int inf = inputHandler();
        pTemp->inf = inf;
        pTemp->pSupList = pCurrentSub;
        if (prevSub == NULL)
            pCurrentMain->pSubList = pTemp;
        else
            prevSub->pSupList = pTemp;
    }
}

void SubPushAfter(MainListItem*& pCurrentMain) 
{
    SubListItem* pTemp = new SubListItem;

    SubListItem* pCurrentSub = pCurrentMain->pSubList;

    if (!SubEmptyCheck(pCurrentSub)) 
    {
        cout << "Введите значение элемента, после которого нужно вставить новый: ";
        int pos = inputHandler();
        while (pCurrentSub != NULL)
        {
            if (pCurrentSub->inf == pos)
                break;
            pCurrentSub = pCurrentSub->pSupList;
        }

        if (pCurrentSub == NULL)
            cout << "Элемент не найден" << endl;
        else 
        {
            cout << "Введите значение нового элемента: ";
            int inf = inputHandler();
            pTemp->inf = inf;
            pTemp->pSupList = pCurrentSub->pSupList;
            pCurrentSub->pSupList = pTemp;
        }
    }
    else 
    {
        cout << "Введите значение нового элемента: ";
        int inf = inputHandler();
        pTemp->inf = inf;
        pCurrentMain->pSubList = pTemp;
        pTemp->pSupList = NULL;
    }

}

void PopMain(MainListItem*& HeadMain) 
{
    if (MainEmptyCheck(HeadMain))
        cout << "Список пуст. Удалять нечего";
    else 
    {
        cout << endl << "Введите список, который хотите удалить: ";
        int pos = inputHandler();
        MainListItem* pCurrentMain = HeadMain->pMainList;
        MainListItem* prevMain = HeadMain;
        while (pCurrentMain != NULL) 
        {
            if (pCurrentMain->value == pos)
                break;
            prevMain = pCurrentMain;
            pCurrentMain = pCurrentMain->pMainList;
        }

        if (pCurrentMain == NULL)
            cout << "Список не найден" << endl;
        else 
        {
            MainListItem* pTempMain = pCurrentMain;
            SubListItem* pCurrentSub = pCurrentMain->pSubList;
            while (pCurrentSub != NULL)
            {
                SubListItem* pTemp = pCurrentSub;
                pCurrentSub = pCurrentSub->pSupList;
                delete pTemp;
            }
            pCurrentMain->pSubList = NULL;

            if (prevMain == HeadMain)
                HeadMain->pMainList = pCurrentMain->pMainList;
            else
                prevMain->pMainList = pCurrentMain->pMainList;
            delete pTempMain;
            cout << "Список удален" << endl;
        }       
    }
}

void PopSub(MainListItem*& HeadMain) 
{
    if (MainEmptyCheck(HeadMain))
        cout << "Главный список пуст. Удалять нечего";
    else
    {
        cout << endl << "Введите номер списка, из которого необходимо удалить элемент: ";
        int pos1 = inputHandler();
        MainListItem* pCurrentMain = HeadMain->pMainList;
        while (pCurrentMain != NULL)
        {
            if (pCurrentMain->value == pos1)
                break;
            pCurrentMain = pCurrentMain->pMainList;
        }

        if (pCurrentMain == NULL)
            cout << "Список не найден" << endl;
        else 
        {
            if (SubEmptyCheck(pCurrentMain->pSubList))
                cout << "Вспомогательный список пуст" << endl;
            else 
            {
                cout << endl << "Введите значение удаляемого элемента: ";
                int pos2 = inputHandler();
                SubListItem* pCurrentSub = pCurrentMain->pSubList;
                SubListItem* prevSub = NULL;
                while (pCurrentSub != NULL) 
                {
                    if (pCurrentSub->inf == pos2)
                        break;
                    prevSub = pCurrentSub;
                    pCurrentSub = pCurrentSub->pSupList;
                }
                if (pCurrentSub == NULL)
                    cout << "Элемент не найден" << endl;
                else 
                {
                    SubListItem* pTemp = pCurrentSub;
                    if (prevSub == NULL)
                        pCurrentMain->pSubList = pCurrentSub->pSupList;
                    else
                        prevSub->pSupList = pCurrentSub->pSupList;
                    delete pTemp;
                    cout << "Элемент удален" << endl;
                }
            }
        }
    }
}

void callMenu(MainListItem* HeadMain)
{
    bool cycle = true;
    while (cycle) {
        cout << "--------------------------------------------------------------\n";
        cout << "Выберите действие:\n";
        cout << "1. Вывести текущее состояние списка на экран.\n";
        cout << "2. Найти определенный элемент в списке.\n";
        cout << "3. Добавить новый список в главный.\n";
        cout << "4. Добавить новый элемент во вспомогательный список.\n";
        cout << "5. Удалить список из главного.\n";
        cout << "6. Удалить элемент из вспомогательного списка.\n";
        cout << "0. Завершение работы программы.\n";
        cout << ">> ";
        int choice = inputHandler();;
        switch (choice)
        {
        case 1:
            ShowList(HeadMain);
            break;
        case 2:
            FindElement(HeadMain);
            break;
        case 3:
            if (MainEmptyCheck(HeadMain))
                MainPushAfter(HeadMain);
            else
            {
                int choice;
                while (true)
                {
                    cout << "Выберите действие:\n";
                    cout << "1. Добавить новый список перед заданным.\n";
                    cout << "2. Добавить новый список после заданного.\n>> ";
                    choice = inputHandler();
                    if (choice == 1)
                    {
                        MainPushBefore(HeadMain);
                        break;
                    }
                    else if (choice == 2)
                    {
                        MainPushAfter(HeadMain);
                        break;
                    }
                    else
                        cout << "\nВы пытаетесь выбрать несуществующее действие. Попробуйте еще раз.\n";
                }
            }
            break;
        case 4:
            if (MainEmptyCheck(HeadMain))
                cout << "Главный список пуст!\n";
            else
            {
                cout << "Введите номер списка, в который необходимо добавить новый элемент: ";
                int pos = inputHandler();
                MainListItem* CurrentMain = HeadMain->pMainList;
                while (CurrentMain != NULL)
                {
                    if (CurrentMain->value == pos)
                        break;
                    CurrentMain = CurrentMain->pMainList;
                }
                if (CurrentMain == NULL)
                    cout << "Список не найден.\n";
                else
                {
                    if (SubEmptyCheck(CurrentMain->pSubList))
                        SubPushAfter(CurrentMain);
                    else
                    {
                        int choice;
                        while (true)
                        {
                            cout << "Выберите действие:\n";
                            cout << "1. Добавить новый элемент перед заданным.\n";
                            cout << "2. Добавить новый элемент после заданного.\n>> ";
                            choice = inputHandler();
                            if (choice == 1)
                            {
                                SubPushBefore(CurrentMain);
                                break;
                            }
                            else if (choice == 2)
                            {
                                SubPushAfter(CurrentMain);
                                break;
                            }
                            else
                                cout << "\nВы пытаетесь выбрать несуществующее действие. Попробуйте еще раз.\n";
                        }
                    }
                }
            }
            break;
        case 5:
            PopMain(HeadMain);
            break;
        case 6:
            PopSub(HeadMain);
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
    MainListItem* HeadMain = NULL;
    InitList(HeadMain);
    callMenu(HeadMain);
}

