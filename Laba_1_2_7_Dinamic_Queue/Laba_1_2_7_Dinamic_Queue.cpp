#include <iostream>
#include <ctime>
#include <Windows.h>
#include <conio.h>
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DBG_NEW new( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define newDBG_NEW

using namespace std;

struct QueueElement
{
    char Value;
    QueueElement* Next;
};

void InitQueue(QueueElement*& pFirst, QueueElement*& pLast) 
{
    pFirst = new QueueElement; //Выделение памяти для заголовка(фиктивного)
    pFirst->Next = NULL; //Занесение в ссылочную часть пустого указателя
    pLast = pFirst; //Установка указателя конца очереди на pFirst
}

bool IsEmpty(QueueElement* pFirst) 
{
    if (pFirst->Next == NULL) //Услоивие пустой очереди
        return true;
    else
        return false;
}

void Push(QueueElement*& pFirst, QueueElement*& pLast, char symbol) 
{
    QueueElement* pTemp = new QueueElement; //Выделяем память для нового элемента
    pTemp->Next = NULL; //Заполняем поля
    pTemp->Value = symbol;
    pLast->Next = pTemp; //изменяем связующую часть бывшего последнего элемента таким образом, чтобы она адресовала новый добавленный элемент
    pLast = pTemp; //изменяем значение указателя pLast так, чтобы он указывал новый последний элемент
}

void PushCountRandom(QueueElement*& pFirst, QueueElement*& pLast, int count)
{
    for (int i = 0; i < count; i++)
    {
        int num = rand() % (90 - 65 + 1) + 65; // рандомная генерация числа в диапазоне от 65 до 90 включительно
        Push(pFirst, pLast, (char)num); // преобразование в заглавную букву латинского алфавита
    }
}

void Pop(QueueElement*& pFirst, QueueElement*& pLast) 
{
    if (!IsEmpty(pFirst))
    {
        QueueElement* pTemp;

        pTemp = pFirst->Next; //Адресуем удаляемый элемент с помощью вспомогательной переменной
        pFirst->Next = pTemp->Next; //Изменяем связующую часть заголовка так, чтобы она указывала на второй элемент очереди

        if (IsEmpty(pFirst)) //Если после удаления в списке не остается реальных элементов
            pLast = pFirst;
        delete pTemp; //Удаляем элемент
    }
    else
        cout << "Очередь пуста \n";
}

void PopCountRandom(QueueElement*& pFirst, QueueElement*& pLast, int count) 
{
    for (int i = 0; i < count; i++)
    {
        Pop(pFirst, pLast);
    }
}

void Show(QueueElement*& pFirst) 
{
    if (!IsEmpty(pFirst))
    {
        QueueElement* pTemp; //Вводим вспомогательную ссылочную переменную
        pTemp = pFirst->Next; //Устанавливаем в нее адрес первого элемента
        cout << "<-[";
        while (pTemp != NULL)
        {
            cout << pTemp->Value << ", "; // обработка указателя (вывод в консоль)
            pTemp = pTemp->Next; //Изменяем указатель
        }
        cout << "]<-" << endl;
    }
    else
        cout << "Очередь пуста \n";
}

void CleanMemory(QueueElement*& pFirst, QueueElement*& pLast)
{
    if (!IsEmpty(pFirst))
    {
        /*QueueElement* pTemp;
        pTemp = pFirst->Next;*/
        while (pFirst->Next != NULL)
        {
            Pop(pFirst, pLast);
        }
        cout << "Очистка  памяти выполнена успешно" << endl;
    }
    else
        cout << "Очередь пуста, очистка памяти невозможна \n";
}

int inputHandler()
{
    char a;
    while (!(cin >> a) || (cin.peek() != '\n'))
    {
        cin.clear();
        while (cin.get() != '\n');
        cout << "Вы пытаетесь выбрать несуществующее действие. Попробуйте еще раз.\n>> ";
    }
    return a;
}

int RandomCount() {
    return rand() % 3 + 1;
}

void CallMenu(QueueElement*& pFirst, QueueElement*& pLast) {
    unsigned int start = clock();
    const char KEY_ESC_CODE = 27;
    int key = 0;

    int popCount, pushCount, choice;
    popCount = pushCount = 0;
    bool cycle = true;
    cout << "Выберите линию поведения программы:\n";
    cout << "1. Случайное число добавляемых и удаляемых элементов одинаково.\n";
    cout << "2. Число добавляемых элементов чуть больше числа удаляемых.\n";
    cout << "3. Число удаляемых элементов чуть больше числа добавляемых.\n>> ";
    while (cycle)
    {
        choice = inputHandler() - '0';
        switch (choice)
        {
        case 1:
            cycle = false;
            break;
        case 2:
            pushCount = 1;
            cycle = false;
            break;
        case 3:
            popCount = 1;
            cycle = false;
            break;
        default:
            cout << "Вы пытаетесь выбрать несуществующее действие. Попробуйте еще раз.\n>> ";
            break;
        }
    }
    
    while (key != 'q')
    {

        cout << "--------------------------------------------------------------\n";
        int randomizer = rand() % 100 + 1;
        if (randomizer % 2 != 0)
        {
            cout << "Операция... удаление!\n";
            if (!IsEmpty(pFirst))
            {
                int count = RandomCount() + popCount;
                PopCountRandom(pFirst, pLast, count);
                cout << "Количество удалённых элементов: " << count << endl;
            }
            else
                cout << "Очередь пуста, удаление невозможно.\n";
        }
        else
        {
            cout << "Операция... добавление!\n";
            int count = RandomCount() + pushCount;
            PushCountRandom(pFirst, pLast, count);
            cout << "Количество добавленных элементов: " << count << endl;
        }
        cout << "Текущее состояние очереди:\n";
        Show(pFirst);
        Sleep(2000);

        if (_kbhit()) {
            key = _getch();
        }
#pragma region MyRegion
        /*unsigned int end = clock();
                if (end - start > 15000)
                {
                    while (true)
                    {
                        cout << "\nНажмите на клавишу 'c', чтобы продолжить выполнение программы.\n";
                        cout << "Нажмите клавишу 'q', чтобы завершить работу программы.\n";
                        char val = inputHandler();
                        if (val == 'c')
                            break;
                        else if (val == 'q')
                            exit(0);
                        else
                            cout << "\nПроверьте корректность ввода.\n";
                    }
                    start = clock();
                }*/
#pragma endregion
    }
}

int main()
{
    setlocale(LC_ALL, "RUSSIAN");
    srand(static_cast<unsigned int>(time(0)));
    cout << "Генератор псевдослучайных чисел инициирован.\n";

    QueueElement* pFirst = NULL; //Указатель на начало очереди
    QueueElement* pLast = NULL; //Указатель на конец очереди

    InitQueue(pFirst, pLast);

    CallMenu(pFirst, pLast);

    CleanMemory(pFirst, pLast);
    _CrtDumpMemoryLeaks();

}

