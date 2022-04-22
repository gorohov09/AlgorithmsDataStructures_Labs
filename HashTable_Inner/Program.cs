using System;

namespace HashTable_Inner
{
    public class Program
    {
        private const int SIZE_HASH_TABLE = 10;

        private static int count = 0;

        private static string[] _keys = { "АВЕРИНА", "СЕЛЕДКИНА", "ФЕДОРОВА", "АНДРЕЙ", "АЛЕКСЕЙ", "МАКСИМ", "JVRF" };

        private static string[]  _hashTable = new string[SIZE_HASH_TABLE];

        private static int Hashing(string key)
        {
            if (key == null || key.Length == 0)
                throw new ArgumentNullException("key");

            int index = 0;

            for (int i = 0; i < key.Length; i++)
            {
                index += char.ConvertToUtf32(key, i);
            }

            return index % 10;
        }

        private static void AddKey(string[] _hashTable, string key, ref int comparer)
        {
            int index = Hashing(key);
            comparer++;
            if (_hashTable[index] is null)
            {
                _hashTable[index] = key;
                count++;
            }
            else
            {
                if (key == _hashTable[index])
                    return;
                else
                {
                    for (int i = 0; i < SIZE_HASH_TABLE - 2; i++)
                    {
                        int j = ((index + i) % SIZE_HASH_TABLE) + 1;
                        if (j == 10)
                            j = 0;
                        comparer++;
                        if (_hashTable[j] is null)
                        {
                            _hashTable[j] = key;                         
                            count++;
                            break;
                        }
                    }
                }
            }
        }

        private static int SearchKey(string[] _hashTable, string key, ref int comparer)
        {
            int index = Hashing(key);
            comparer++;
            if (_hashTable[index] is null)
            {
                return -1;
            }
            else
            {
                if (key == _hashTable[index])
                    return index;
                else
                {
                    for (int i = 0; i < SIZE_HASH_TABLE - 2; i++)
                    {
                        int j = ((index + i) % SIZE_HASH_TABLE) + 1;
                        if (j == 10)
                            j = 0;
                        comparer++;
                        if (_hashTable[j] == key)
                        {
                            return j;
                        }

                    }
                    return -1;
                }
            }
        }

        static void Main(string[] args)
        {
            while (true)
            {
                Console.WriteLine("_ _ _ _ _ _ _ _ _ _ _МЕНЮ_ _ _ _ _ _ _ _ _ _ _");
                Console.WriteLine("Выберите действие:");
                Console.WriteLine("1. Заполнить хеш-таблицу исходными ключами");
                Console.WriteLine("2. Добавить в хеш-таблицу ключ");
                Console.WriteLine("3. Вывести хеш-таблицу на экран");
                Console.WriteLine("4. Найти ключ в хеш-таблице");
                Console.WriteLine("0. Выход из программы");

                Console.Write("Выбор: ");
                int choice = int.Parse(Console.ReadLine());

                if (choice == 1)
                {
                    for (int i = 0; i < _keys.Length; i++)
                    {
                        int comparer = 0;

                        if (count == SIZE_HASH_TABLE)
                        {
                            Console.WriteLine("Таблица заполнена. Добавление невозможно!");
                            break;
                        }
                        AddKey(_hashTable, _keys[i], ref comparer);
                    }
                    Console.WriteLine("Хеш-таблица успешно заполнена");
                }
                else if (choice == 2)
                {
                    if (count == SIZE_HASH_TABLE)
                        Console.WriteLine("Таблица заполнена, добавлять нечего!");
                    else
                    {
                        int comparer = 0;
                        Console.Write("Введите ключ: ");
                        string key = Console.ReadLine();
                        if (key != null)
                            AddKey(_hashTable, key, ref comparer);
                        Console.WriteLine($"Ключ добавлен. Кол-во сравнений: {comparer}");
                    }
                    
                }
                else if (choice == 3)
                {
                    for (int i = 0; i < _hashTable.Length; i++)
                    {
                        if (_hashTable[i] is null)
                            Console.WriteLine($"Индекс массива:{i} - Значение: пусто");
                        else
                            Console.WriteLine($"Индекс массива:{i} - Значение: {_hashTable[i]}");
                    }
                }
                else if (choice == 4)
                {
                    int comparer = 0;
                    Console.Write("Введите ключ: ");
                    string key = Console.ReadLine();
                    int index = SearchKey(_hashTable, key, ref comparer);
                    if (index == -1)
                        Console.WriteLine($"Ключ не найден");
                    else
                    {
                        Console.WriteLine($"Ключ найден. Индекс в массиве: {index}");
                        Console.WriteLine($"Кол-во сравнений: {comparer}");
                    }
                    
                }
                else if (choice == 0)
                    break;
            }
            Console.WriteLine("Программа завершила свою работу!");
        }
    }
}
