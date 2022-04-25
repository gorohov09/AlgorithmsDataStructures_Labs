using System;

namespace SimpleHashTable
{
    public class Program
    {
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
        static void Main(string[] args)
        {
            string[] _keys = { "WHILE", "FOR", "RETURN", "STRUct", "OUT", "Ref", "FOREACH", "PROGRAM", "ARRAY", "Class" };

            string[] _hashTable = new string[_keys.Length];

            while (true)
            {
                Console.WriteLine("_ _ _ _ _ _ _ _ _ _ _МЕНЮ_ _ _ _ _ _ _ _ _ _ _");
                Console.WriteLine("Выберите действие:");
                Console.WriteLine("2. Заполнить хеш-таблицу в соответствии со значением хеш-функции");
                Console.WriteLine("3. Вывести хеш-таблицу на экран");
                Console.WriteLine("4. Найти ключ в хеш-таблице");
                Console.WriteLine("0. Выход из программы");

                Console.Write("Выбор: ");
                int choice = int.Parse(Console.ReadLine());

                if (choice == 2)
                {
                    for (int i = 0; i < _keys.Length; i++)
                    {
                        _hashTable[Hashing(_keys[i])] = _keys[i];
                    }
                    Console.WriteLine("Хеш-таблица успешно заполнена");
                }
                else if (choice == 3)
                {
                    for (int i = 0; i < _hashTable.Length; i++)
                    {
                        Console.WriteLine($"Индекс массива:{i} - Ключ: {_hashTable[i]} - Значение: {_hashTable[i]}");
                    }
                }
                else if (choice == 4)
                {
                    Console.Write("Введите значение ключа: ");
                    string key = Console.ReadLine();
                    int index = Hashing(key);

                    if (_hashTable[index] == key)
                    {
                        Console.WriteLine("Ключ успешно найден!");
                        Console.WriteLine($"Ключ {key} находится под индексом {index}");
                    }
                    else
                        Console.WriteLine("Такого ключа нет!");
                }
                else if (choice == 0)
                    break;
            }
            Console.WriteLine("Программа завершила свою работу!");
        }
    }
}
