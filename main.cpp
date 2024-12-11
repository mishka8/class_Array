#include <iostream>
#include <algorithm>
#include <chrono>

using namespace std;


class Array
{
    int *a;
    int n;

public:



    Array (int len = 1, int t = 1, int d = 10) /*: n(len)*/
    {
        n = len;
        a = new int[n];

        if(t > 3 || t < 1)
        {
            for(int i = 0; i < n; ++i)
                a[i] = 0;
        }
        else if(t == 1)
        {
            for(int  i = 0; i < n; ++i)
            {
                a[i] = rand() % (d + 1);
            }
        }

        else if(t == 2)
        {
            a[0] = rand() % (d + 1);
            for(int i = 1; i < n; ++i)
            {
                a[i] = a[i - 1] + rand() % (d + 1);
            }
        }

        else if(t == 3)
        {
            a[n - 1] = rand() % (d + 1);
            for(int i = n - 2; i >= 0; i--)
            {
                a[i] = a[i + 1] + rand() % (d + 1);
            }
        }
    }

    Array(int *arr , int len) : n(len)
   {
       a = new int[n];
       for(int i = 0; i < n; ++i)
       {
           a[i] = arr[i];
       }
   }

    Array(Array &other)
   {
       n = other.n;
       a = new int[n];
       for(int i = 0; i < n; ++i)
       {
           a[i] = other.a[i];
       }
   }

   ~Array()
   {
       if(a)
       {
           delete []a;
       }

       a = NULL;
   }

    Array& operator=(Array &other)
    {
        if(this == &other)
            return *this;

        delete []a;

        n = other.n;
        a = new int[n];
        for(int i = 0; i < n; ++i)
        {
            a[i] = other.a[i];
        }
        return *this;
    }

    int& operator[](int ix)
    {
        if(ix == 0 || ix > n)
        {
            cout << "Indexout of range" << endl;
        }
        else
        {
            return a[ix];
        }
    }

    bool Test()
    {
        for(int i = 0; i < n - 1; ++i)
        {
            if(a[i] > a[i + 1])
                return false;

        }
        return true;
    }

    bool operator==(Array other)
    {
        if (n != other.n)
            return false;
    int len = n;
    for (int i = 0; i < n; i++)
    {
        bool fl = false;
        for (int j = 0; j < len; j++)
        {
            if (a[i] == other.a[j])
            {

                fl = true;
                other[j] = other[len - 1];
                len--;
                break;
            }
        }
        if (fl == false)
            return false;
    }
    return true;
}

    void Shell_sort()
    {
        for(int step = n / 2; step > 0; step /= 2)//начинаем с половины масива
        {
            for(int i = 1; i < n; i+=step)//елемент i  сравниваем с элементом i + step
            {
                int tmp = a[i];//запоминаем текущий элемент
                int j;

                for(j = i; j >= step && a[j - step] > tmp; j -= step)//првоерка что мы не вышли за масив
                {
                    a[j] = a[j - step];//сдвигаем влево
                }
                a[j] = tmp;
            }
        }
    }

    void heap_help(int n, int i)
    {
        int j = 2 * i + 1;
        int x = a[i];
        bool flag = true;

        while(j < n && flag)
        {
            if(j + 1 < n  && a[j + 1] > a[j])
                j++;

            if(a[j] > x)
            {
                a[i] = a[j];
                i = j;
                j = 2 * i + 1;
            }
            else
                flag = false;

        }
        a[i] = x;
    }

    void Heap_sort()
    {
        for(int i = n / 2 - 1; i >= 0; i--)
            heap_help(n, i);

        for(int i = n - 1;  i >= 0; i--)
        {
            swap(a[0], a[i]);

            heap_help(i, 0);
        }
    }
    //Постройте max-heap из входных данных.
    //На данном этапе самый большой элемент хранится в корне кучи. Замените его на последний элемент кучи, а затем уменьшите ее размер на 1. Наконец, преобразуйте полученное дерево в max-heap с новым корнем.
    //Повторяйте вышеуказанные шаги, пока размер кучи больше 1

    int change(int *arr, int left, int right)
    {
        if(left >= right)
            return 0;

        int i = left;
        int j = right;
        int x = arr[(left + right) / 2];//опорный елемент
        while(i <= j)
        {
            while(arr[i] < x)
                //сравниеваем слева
                i++;

            while(arr[j] > x)//сравниваем справа
                j--;

            if(i <= j)
            {
                swap(arr[i], arr[j]);
                i++;
                j--;
            }

        }
        //слева меньше опроного справа больше опорного
        //с помощью рекурсии сортируем правую и левую части
        //каждый раз масив разбивается на два меньших и тем самым сортируется
        change(arr, left, j);
        change(arr, i, right);
        return 0;
    }

    void Hoar_sort()
    {
        change(a, 0, n - 1);
    }

    friend istream& operator>>(istream& in, Array& arr)
    {
        for(int i = 0; i < arr.n; ++i)
        {
            in >> arr.a[i];
        }

        return in;
    }

    friend ostream& operator<<(ostream& out, Array& arr)
    {
        for(int i = 0; i < arr.n; ++i)
        {
            out << arr.a[i] << "  ";
        }
        out << endl;

        return out;
    }

};

void test()
{
    Array a1(100, 3);
    Array a2(100, 3);
    Array a3(100, 3);

    using chrono::high_resolution_clock;//позволяет измерять время с высокой точностью
    using chrono::duration_cast;// конвертирует значение длительности в другой тип длительности, учитывая различия в их периодах
    using chrono::duration;//для интервала времени
    using chrono::milliseconds;//using milliseconds = duration<long long, milli>;

    auto time1 = high_resolution_clock::now();
    a1.Shell_sort();
    auto time2 = high_resolution_clock::now();

    duration <double, milli> timeMs = time2 - time1;
    cout << "Shell_sort - " << timeMs.count() << " ms" << endl;


    time1 = high_resolution_clock::now();
    a1.Heap_sort();
    time2 = high_resolution_clock::now();

    timeMs = time2 - time1;
    cout << "Heap_sort -  " << timeMs.count() << " ms" << endl;\


    time1 = high_resolution_clock::now();
    a1.Hoar_sort();
    time2 = high_resolution_clock::now();

    timeMs = time2 - time1;
    cout << "Hoar_sort -  " << timeMs.count() << " ms" << endl;

}

int main()
{
    srand(time(0));

    test();


    return 0;
}
