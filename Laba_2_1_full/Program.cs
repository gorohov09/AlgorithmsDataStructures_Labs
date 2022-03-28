using System;
using System.Diagnostics;

namespace Laba_2_1_full
{
    public class Program
    {
        static void ArrayFill(int[] array)
        {
            Random rand = new Random();
            for (int i = 0; i < array.Length; i++)
            {
                array[i] = rand.Next(-1000, 1000);
            }
        }

        static void ArrayPrint(int[] array)
        {
            for (int i = 0; i < array.Length; i++)
            {
                Console.Write($"{array[i]} ");
            }
            Console.WriteLine();
            Console.WriteLine("---------------------------------------------------------");
        }

        static int[] ArrayCopy(int[] array)
        {
            if (array == null)
                throw new ArgumentNullException("Создайте массив");
            int[] newArr = new int[array.Length];
            for (int i = 0; array.Length > i; i++)
                newArr[i] = array[i];
            return newArr;
        }

        static void BubbleSort(int[] mas, ref int count_comparer, ref int count_move)
        {
            int temp;
            int n = mas.Length;
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n - 1- i; j++)
                {
                    count_comparer += 1;
                    if (mas[j] > mas[j + 1])
                    {
                        temp = mas[j];
                        mas[j] = mas[j + 1];
                        mas[j + 1] = temp;
                        count_move++;
                    }
                }
            }
        }

        static void SelectionSort(int[] array, ref int count_comparer, ref int count_move)
        {
            int temp;
            for (int i = 0; i < array.Length - 1; i++)
            {
                int min = i;
                for (int j = i + 1; j < array.Length; j++)
                {
                    count_comparer += 1;
                    if (array[j] < array[min])
                        min = j;
                }
                if (array[min] != array[i])
                    count_move++;
                temp = array[min];
                array[min] = array[i];
                array[i] = temp;
            }
        }

        static void InsertionSort(int[] array, ref int count_comparer, ref int count_move)
        {
            for (int i = 1; i < array.Length - 1; i++)
            {
                int x = array[i];
                int j = i;
                
                while (j > 0 && array[j - 1] > x)
                {
                    count_comparer++;
                    count_move++;
                    array[j] = array[j - 1];
                    j -= 1;
                }
                count_comparer += 1;
                array[j] = x;
            }
        }

        static void Main(string[] args)
        {
            bool result = true;
            int[] array = null;
            int[] array_sort;
            

            var watch = new Stopwatch();

            while (result)
            {
                int count_comparer = 0;
                int count_move = 0;
                Console.WriteLine("Выберите действие:");
                Console.WriteLine("1. Создать массив.");
                Console.WriteLine("2. Сортировка обменом (метод пузырька).");
                Console.WriteLine("3. Сортировка выбором");
                Console.WriteLine("4. Сортировка вставками.");
                Console.WriteLine("0. Завершение работы программы.");

                int choice = int.Parse(Console.ReadLine());


                switch (choice)
                {
                    case 1:
                        Console.WriteLine("Введите размер массива");
                        int size = int.Parse(Console.ReadLine());
                        if (size > 10_000)
                            Console.WriteLine("Введите размер, меньший 10000");
                        else
                        {
                            array = new int[size];
                            ArrayFill(array);
                            Console.WriteLine("Исходный массив");
                            ArrayPrint(array);
                        }
                        break;
                    case 2:
                        array_sort = ArrayCopy(array);
                        watch.Start();
                        BubbleSort(array_sort, ref count_comparer, ref count_move);
                        watch.Stop();
                        Console.WriteLine("Пузырьковая сортирвока:");
                        Console.WriteLine($"Колличество сравнений: {count_comparer}");
                        Console.WriteLine($"Колличество перестановок {count_move}");
                        ArrayPrint(array_sort);
                        watch.Reset();
                        break;

                    case 3:
                        array_sort = ArrayCopy(array);
                        watch.Start();
                        SelectionSort(array_sort, ref count_comparer, ref count_move);
                        watch.Stop();
                        Console.WriteLine("Сортировка выборкой:");
                        Console.WriteLine($"Колличество сравнений: {count_comparer}");
                        Console.WriteLine($"Колличество перестановок {count_move}");
                        ArrayPrint(array_sort);
                        watch.Reset();
                        break;
                    case 4:
                        array_sort = ArrayCopy(array);
                        watch.Start();
                        InsertionSort(array_sort, ref count_comparer, ref count_move);
                        watch.Stop();
                        Console.WriteLine("Сортировка вставками:");
                        Console.WriteLine($"Колличество сравнений: {count_comparer}");
                        Console.WriteLine($"Колличество перестановок {count_move}");
                        ArrayPrint(array_sort);
                        watch.Reset();
                        break;
                    case 0:
                        result = false;
                        break;
                }
            }

            
        }
    }
}
