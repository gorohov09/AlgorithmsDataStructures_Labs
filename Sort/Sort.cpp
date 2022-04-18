#include <iostream>
#include <time.h>
#include <vector>
#include <algorithm>

using namespace std;

int comparsions = 0, shifts = 0;

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

void CreateNonRepeateArray(int* arr, int size)
{
    vector<int> numbers;
    for (int i = 0; i < size; i++)
    {
        numbers.push_back(i);
    }
    random_shuffle(numbers.begin(), numbers.end());
    for (int i = 0; i < size; i++)
        arr[i] = numbers[i];
}

void ShowArray(int* arr, int size)
{
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

void PocketSortWithArray(int* arr, int size) //не требует ни одного сравнения
{
    shifts = 0;
    int* addArray = new int[size];
    for (int i = 0; i < size; i++)
    {
        addArray[arr[i]] = arr[i];
        shifts++;
    }
    cout << endl << "Отсортированный массив:\n";
    cout << "Количество перестановок: " << shifts << endl;
    ShowArray(addArray, size);
    delete[] addArray;
}

void PocketSortWithoutArray(int* arr, int size)
{
    comparsions = 0; shifts = 0;
    int temp;
    for (int i = 0; i < size; i++)
    {
        while (arr[i] != i)
        {
            shifts++;
            comparsions++;
            temp = arr[i];
            arr[i] = arr[temp];
            arr[temp] = temp;
        }
        comparsions++;
    }
    cout << "Количество перестановок: " << shifts << endl;
    cout << "Количество сравнений: " << comparsions << endl;
    cout << endl << "Отсортированный массив:\n";
    ShowArray(arr, size);
}

struct ListItem
{
    int value;
    ListItem* next;
};

void AddItem(ListItem* pItem, int value)
{
    while (pItem->next != NULL)
        pItem = pItem->next;
    pItem->next = new ListItem;
    pItem->next->value = value;
    pItem->next->next = NULL;
}

void ClearList(ListItem* head)
{
    while (head != NULL)
    {
        ListItem* tmp = head;
        head = head->next;
        delete tmp;
    }
}

void ShowPocket(ListItem* mas, int n)
{
    cout << "Отсортированный массив:" << endl;
    for (int i = 0; i < n; i++)
    {
        ListItem* current = mas[i].next;
        while (current != NULL)
        {
            cout << current->value << " ";
            current = current->next;
        }
    }
    cout << endl;
}

void PocketSort(int* arr, int size)
{
    shifts = 0;
    ListItem* sortedArray = new ListItem[size];
    for (int i = 0; i < size; i++)
        sortedArray[i].next = NULL;
    for (int i = 0; i < size; i++, shifts++)
        AddItem(&sortedArray[arr[i]], arr[i]); //добавление эл-та
    ShowPocket(sortedArray, size);
    cout << endl << "Количество перестановок: " << shifts << endl;
    for (int i = 0; i < size; i++)
        ClearList(sortedArray[i].next);
    delete[] sortedArray;
}

int searchMaxElement(int* mas, int size)
{
    int max = 0;
    for (int i = 0; i < size; i++)
    {
        if (mas[i] > max)
            max = mas[i];
    }
    return max;
}

void RadixSort(int* arr, int size)
{
    ListItem* sortedArray = new ListItem[10];
    int k = searchMaxElement(arr, size);
    int i = 0;
    shifts = 0;
    while (k >= 1)
    {
        i++;
        k /= 10;
        for (int j = 0; j < 10; j++)
            sortedArray[j].next = NULL;
        for (int j = 0; j < size; j++)
        {
            int div = 1;
            for (int l = 0; l < i; l++, div *= 10);
            AddItem(&sortedArray[((arr[j] % div) * 10) / div], arr[j]);
            shifts++;
        }
        for (int j = 0, l = 0; l < size; j++)
        {
            ListItem* tmp = sortedArray[j].next;
            while (tmp != NULL)
            {
                arr[l] = tmp->value;
                tmp = tmp->next;
                l++;
            }
        }
        for (int j = 0; j < 10; j++)
            ClearList(sortedArray[j].next);
    }
    cout << "Отсортированный массив:" << endl;
    ShowArray(arr, size);
    cout << "Количество перестановок: " << shifts << endl;
    delete[] sortedArray;
}

void CallMenu()
{
    bool cycle = true;
    int arraySize = 0;
    int* mainArray = NULL;
    while (cycle) {
        cout << "--------------------------------------------------------------\n";
        cout << "Выберите действие:\n";
        cout << "1. Простейшая карманная сортировка с использованием второго массива.\n";
        cout << "2. Простейшая карманная сортировка без использованием второго массива.\n";
        cout << "3. Обобщённая карманная сортировка.\n";
        cout << "4. Поразрядная сортировка.\n";
        cout << "0. Завершение работы программы.\n";
        cout << ">> ";
        int choice = inputHandler();
        switch (choice)
        {
        case 1:
            cout << "Введите размер массива: ";
            arraySize = inputHandler();
            if (arraySize > 0 && arraySize <= 10000)
            {
                mainArray = new int[arraySize];
                CreateNonRepeateArray(mainArray, arraySize);
                cout << "Массив создан:\n";
                ShowArray(mainArray, arraySize);
                PocketSortWithArray(mainArray, arraySize);
                delete[] mainArray;
            }
            else
                cout << "Введите значение между 0 и 10000.\n";
            break;
        case 2:
            cout << "Введите размер массива: ";
            arraySize = inputHandler();
            if (arraySize > 0 && arraySize <= 10000)
            {
                mainArray = new int[arraySize];
                CreateNonRepeateArray(mainArray, arraySize);
                cout << "Массив создан:\n";
                ShowArray(mainArray, arraySize);
                PocketSortWithoutArray(mainArray, arraySize);
                delete[] mainArray;
            }
            else
                cout << "Введите значение между 0 и 10000.\n";
            break;
        case 3:
            cout << "Введите размер массива: ";
            arraySize = inputHandler();
            if (arraySize > 0 && arraySize <= 10000)
            {
                mainArray = new int[arraySize];
                for (int i = 0; i < arraySize; i++)
                    mainArray[i] = rand() % arraySize;
                cout << "Массив создан:\n";
                ShowArray(mainArray, arraySize);
                PocketSort(mainArray, arraySize);
                delete[] mainArray;
            }
            else
                cout << "Введите значение между 0 и 10000.\n";
            break;
        case 4:
            cout << "Введите размер массива: ";
            arraySize = inputHandler();
            if (arraySize > 0 && arraySize <= 10000)
            {
                mainArray = new int[arraySize];
                for (int i = 0; i < arraySize; i++)
                    mainArray[i] = rand() % arraySize;
                cout << "Массив создан:\n";
                ShowArray(mainArray, arraySize);
                RadixSort(mainArray, arraySize);
                delete[] mainArray;
            }
            else
                cout << "Введите значение между 0 и 10000.\n";
            break;
        case 0:
            exit(1);
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
    srand(static_cast<unsigned int>(time(0)));
    CallMenu();
    return 0;
}