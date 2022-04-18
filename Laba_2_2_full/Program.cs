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
                for (int j = 0; j < n - 1 - i; j++)
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

        /// <summary>
        /// Улучшение метода вставок
        /// </summary>
        /// <param name="array"></param>
        /// <param name="count_comparer"></param>
        /// <param name="count_move"></param>
        static void ShellSort(int[] array, ref int count_comparer, ref int count_move)
        {
            int t = Convert.ToInt32(Math.Log2(array.Length)); //Число шагов группировки

            int[] stepsArray = new int[t];
            for (int i = 0; t > 0; i++, t--)
            {
                stepsArray[i] = Convert.ToInt32(Math.Pow(2, t) - 1); //Высчитывание последовательности шагов
            }

            int k, temp, j;
            t = Convert.ToInt32(Math.Log2(array.Length));

            for (int m = 0; m < t; m++) //Сортировка вставками внутри каждой группы
            {
                k = stepsArray[m]; //Выбор величины шага
                for (int i = k; i < array.Length; i++)
                {
                    temp = array[i];
                    j = i - k;
                    while (j >= 0 && temp < array[j])
                    {
                        count_comparer++;
                        array[j + k] = array[j];
                        count_move++;
                        j = j - k;
                    }
                    count_comparer++;
                    array[j + k] = temp;
                }
            }
        }

        /// <summary>
        /// Улучшение метода обмена
        /// </summary>
        /// <param name="arr"></param>
        /// <param name="left"></param>
        /// <param name="right"></param>
        /// <param name="count_comparer"></param>
        /// <param name="count_move"></param>
        static void QuickSort(int[] arr, int left, int right, ref int count_comparer, ref int count_move)
        {
            int i, j, middle, temp;
            i = left; //установка начальных значений границ подмассива
            j = right;
            middle = arr[(left + right) / 2]; //определение серединного элемента
            do
            {
                while (arr[i] < middle) //поиск слева элемента, большего опорного
                {
                    i = i + 1;
                    count_comparer++;
                }
                if (arr[i] > middle) //поиск справа элемента, меньшего опорного
                    count_comparer++;
                while (arr[j] > middle)
                {
                    j = j - 1;
                    count_comparer++;
                }
                if (arr[j] < middle)
                    count_comparer++;
                if (i <= j) 
                {
                    temp = arr[i]; //обмениваем элементы и изменяем индексы
                    arr[i] = arr[j];
                    arr[j] = temp;
                    count_move++;
                    i = i + 1;
                    j = j - 1;
                }
            } while (i <= j);
            if (left < j) //обработка левой половины
                QuickSort(arr, left, j, ref count_comparer, ref count_move);
            if (i < right) //обработка правой половины
                QuickSort(arr, i, right, ref count_comparer, ref count_move);
        }

        static void Sito(int[] arr, int left, int right, ref int count_comparer, ref int count_move)
        {
            int i, j, x;
            i = left; j = 2 * left;

            x = arr[left];
            if ((j < right) && (arr[j + 1] > arr[j]))
            {
                j = j + 1;
            }
            while ((j <= right) && (arr[j] > x))
            {
                count_comparer++;
                arr[i] = arr[j];
                i = j;
                count_move++;
                j = 2 * j;
                if ((j < right) && (arr[j + 1] > arr[j]))
                {
                    j = j + 1;
                }
            }
            count_comparer++;
            arr[i] = x;
        }

        /// <summary>
        /// Улучшение сортировки выбором
        /// </summary>
        /// <param name="arr"></param>
        /// <param name="size"></param>
        /// <param name="count_comparer"></param>
        /// <param name="count_move"></param>
        static void PyramidSort(int[] arr, int size, ref int count_comparer, ref int count_move)
        {
            int temp;
            int left = Convert.ToInt32(size / 2) + 1, right = size - 1; //определение границ правой половины массива
            while (left > 0) //Цикл построения пирамиды
            {
                left = left - 1;
                Sito(arr, left, right, ref count_comparer, ref count_move);
            }
            while (right > 0) //Цикл сортировки
            {
                temp = arr[0];
                arr[0] = arr[right];
                arr[right] = temp;
                right = right - 1;
                Sito(arr, left, right, ref count_comparer, ref count_move);
            }
        }

        static void Main(string[] args)
        {
            bool result = true;
            int[] array = null;
            int[] array_sort;

            while (result)
            {
                int count_comparer = 0;
                int count_move = 0;
                Console.WriteLine("Выберите действие:");
                Console.WriteLine("1. Создать массив.");
                Console.WriteLine("2. Сортировка Шелла");
                Console.WriteLine("3. Сортировка выбором");
                Console.WriteLine("4. Сортировка вставками.");
                Console.WriteLine("5. Быстрая сортировка.");
                Console.WriteLine("6. Пирамидальная сортировка.");
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
                        ShellSort(array_sort, ref count_comparer, ref count_move);
                        Console.WriteLine("Сортировка Шелла сортирвока:");
                        Console.WriteLine($"Колличество сравнений: {count_comparer}");
                        Console.WriteLine($"Колличество перестановок {count_move}");
                        ArrayPrint(array_sort);
                        break;

                    case 3:
                        array_sort = ArrayCopy(array);
                        SelectionSort(array_sort, ref count_comparer, ref count_move);
                        Console.WriteLine("Сортировка выборкой:");
                        Console.WriteLine($"Колличество сравнений: {count_comparer}");
                        Console.WriteLine($"Колличество перестановок {count_move}");
                        ArrayPrint(array_sort);
                        break;
                    case 4:
                        array_sort = ArrayCopy(array);
                        InsertionSort(array_sort, ref count_comparer, ref count_move);
                        Console.WriteLine("Сортировка вставками:");
                        Console.WriteLine($"Колличество сравнений: {count_comparer}");
                        Console.WriteLine($"Колличество перестановок {count_move}");
                        ArrayPrint(array_sort);
                        break;
                    case 5:
                        array_sort = ArrayCopy(array);
                        QuickSort(array_sort, 0, array_sort.Length - 1, ref count_comparer, ref count_move);
                        Console.WriteLine("Быстрая сортировка:");
                        Console.WriteLine($"Колличество сравнений: {count_comparer}");
                        Console.WriteLine($"Колличество перестановок {count_move}");
                        ArrayPrint(array_sort);
                        break;
                    case 6:
                        array_sort = ArrayCopy(array);
                        PyramidSort(array_sort, array_sort.Length, ref count_comparer, ref count_move);
                        Console.WriteLine("Пирамидальная сортировка:");
                        Console.WriteLine($"Колличество сравнений: {count_comparer}");
                        Console.WriteLine($"Колличество перестановок {count_move}");
                        ArrayPrint(array_sort);
                        break;
                    case 0:
                        result = false;
                        break;
                }
            }


        }
    }
}
