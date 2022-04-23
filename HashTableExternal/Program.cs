using System;

namespace HashTableExternal
{
    public class ArrayCell
    {
        public string Key { get; set; }

        public Node Begin { get; set; }

        public Node End { get; set; }

        public int Count { get; set; }
    }

    public class Node
    {
        public string Key { set; get; }

        public Node Next { get; set; }
    }

    public class Program
    {
        private const int SIZE_HASH_TABLE = 10;

        private static int count = 0;

        private static string[] _keys = { "АВЕРИНА", "СЕЛЕДКИНА", "ФЕДОРОВА", "АНДРЕЙ", "АЛЕКСЕЙ", "МАКСИМ", "JVRF", "SSDSD", "EWFFW","FEEFEFFEFE", "ASWQ" };

        private static ArrayCell[] _hashTable = new ArrayCell[SIZE_HASH_TABLE];

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

        private static void PrintHashTable(ArrayCell[] _hashTable)
        {
            for (int i = 0; i < _hashTable.Length; i++)
            {
                if (_hashTable[i] == null)
                    Console.WriteLine($"Индекс: {i}. Значение: пусто ");
                else
                {
                    Console.Write($"Индекс: {i}. Значение: {_hashTable[i].Key} ");

                    Node current = _hashTable[i].Begin;
                    while (current != null)
                    {
                        Console.Write($"{current.Key} ");
                        current = current.Next;
                    }
                    Console.WriteLine();
                }
            }
        }

        private static void AddKey(ArrayCell[] _hashTable, string key, ref int comparer)
        {
            int index = Hashing(key);

            if (_hashTable[index] == null)
            {
                ArrayCell cell = new ArrayCell();
                cell.Key = key;
                cell.Begin = null;
                cell.End = null;
                _hashTable[index] = cell;
            }
            else
            {
                if (_hashTable[index].Key == key)
                    return;
                else
                {
                    Node node = new Node();
                    node.Key = key;
                    node.Next = null;
                    if (_hashTable[index].Begin == null)
                    {
                        _hashTable[index].Begin = node;
                        _hashTable[index].End = node;
                    }
                    else
                    {
                        _hashTable[index].End.Next = node;
                    }
                    _hashTable[index].Count++;
                }
            }
        }

        private static int SearchKey(ArrayCell[] _hashTable, string key, ref int comparer)
        {
            int index = Hashing(key);

            if (_hashTable[index] == null)
            {
                return -1;
            }
            else
            {
                if (_hashTable[index].Key == key)
                    return index;
                else
                {
                    Node current = _hashTable[index].Begin;
                    while (current != null)
                    {
                        if (current.Key == key)
                            return index;
                        current = current.Next;
                    }
                    return -1;
                }
            }
        }

        private static void DeleteKey(ArrayCell[] _hashTable, string key, ref int comparer)
        {
            int index = Hashing(key);

            if (_hashTable[index] == null)
            {
                return;
            }
            else
            {
                if (_hashTable[index].Key == key)
                {
                    if (_hashTable[index].Begin is null)
                    {
                        _hashTable[index].Key = null;
                        _hashTable[index] = null;
                    }
                        
                    else
                    {
                        _hashTable[index].Key = _hashTable[index].Begin.Key;
                        _hashTable[index].Begin = _hashTable[index].Begin.Next;
                        if (_hashTable[index].Count == 1)
                        {
                            _hashTable[index].End = null;
                        }
                        _hashTable[index].Count--;
                    }
                }
                else
                {
                    Node current = _hashTable[index].Begin;
                    while (current != null)
                    {
                        if (current.Key == key)
                        {
                            if (current == _hashTable[index].Begin)
                            {
                                _hashTable[index].Begin = _hashTable[index].Begin.Next;

                                if (_hashTable[index].Count == 1)
                                {
                                    _hashTable[index].End = null;
                                    _hashTable[index].Begin = null;
                                }
                                _hashTable[index].Count--;
                            }
                            else if (current == _hashTable[index].End)
                            {
                                if (_hashTable[index].Count == 1)
                                {
                                    _hashTable[index].Begin = null;
                                    _hashTable[index].End = null;
                                }
                                else
                                {
                                    Node Current = _hashTable[index].Begin;

                                    while (Current.Next != _hashTable[index].End)
                                        Current = Current.Next;

                                    Current.Next = null;
                                    _hashTable[index].End = Current;
                                }
                                _hashTable[index].Count--;
                            }
                            else
                            {
                                Node Current = _hashTable[index].Begin;

                                while (Current.Next != current)
                                    Current = Current.Next;

                                Current.Next = current.Next;
                            }
                        }   
                        current = current.Next;
                    }
                }
                count--;
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
                Console.WriteLine("5.Удалить ключ в хеш-таблице");
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
                    PrintHashTable(_hashTable);
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
                else if (choice == 5)
                {
                    int comparer = 0;
                    Console.Write("Введите ключ: ");
                    string key = Console.ReadLine();
                    DeleteKey(_hashTable, key, ref comparer);

                }
                else if (choice == 0)
                    break;
            }
            Console.WriteLine("Программа завершила свою работу!");
        }
    }
}
