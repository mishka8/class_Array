#include <iostream>
#include <ctime>
#include <algorithm>



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

        if(t == 1)
        {
            for(int  i = 0; i < n; ++i)
            {
                a[i] = rand() % d + 1;
            }
        }

        else if(t == 2)
        {
            for(int i = 0; i < n; ++i)
            {
                a[i] = i;
            }
        }

        else if(t == 3)
        {
            for(int i = 0; i < n; ++i)
            {
                a[i] = n - i;
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

//   Array(int first, int step, int len)
//   {
//       if(len <= 0)
//       {
//           cout << "Error size" << endl;
//           exit(-1);
//       }
//       n = len;

//       a = new int[n];
//       a[0] = first;
//       for(size_t i = 1; i < n; ++i)
//       {
//           a[i] = a[i - 1] + step;
//       }
//   }

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

//    Array operator+(Array other)
//    {
//        size_t new_len = n + other.n;
//        int *new_arr = new int[new_len];
//        size_t i = 0, j = 0, k = 0;


//        while(i < n && j < other.n)
//        {
//            if(a[i] < other.a[j])
//            {
//                new_arr[k++] = a[i++];
//            }
//            else
//            {
//                new_arr[k++] = other.a[j++];
//            }

//        }

//        while(i < n)
//        {
//            new_arr[k++] = a[i++];
//        }

//        while(j < other.n)
//        {
//            new_arr[k++] = other.a[j++];
//        }

//    }

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
        if(n != other.n)
            return false;

        for(int i = 0; i < n; ++i)
        {
            if(a[i] != other.a[i])
                return false;

        }
        return true;
    }

    void operator-(int k)
    {
        size_t new_len = 0;
        for(int i = 0; i < n; ++i)
        {
            if(a[i] != k)
                ++new_len;

        }

        int *new_arr = new int[new_len];
        int j = 0;
        for(int i = 0; i < n; ++i)
        {
            if(a[i] != k)
            {
                new_arr[j++] = a[i];
            }
        }

        delete []a;
        a = NULL;

        n = new_len;
        a = new_arr;
    }

    void Shell_sort()
    {
         int h = 1;
        while (h < n / 3)
        {
            h = 3 * h + 1; // Вычисление шага сортировки
        }
        while (h >= 1) {
            for (int i = h; i < n; ++i)
            {
                int j = i;
                while (j >= h && a[j - h] > a[j])
                {
                    swap(a[j - h], a[j]);
                    j -= h;
                }
            }
            h /= 3;
        }
    }

    void Heap_sort()
    {

    }

    void Hoar_sort()
    {

    }

    void Bit_sort()
    {

    }

    friend istream& operator>>(istream& in, Array& arr)
    {
        for(size_t i = 0; i < arr.n; ++i)
        {
            in >> arr.a[i];
        }

        return in;
    }

    friend ostream& operator<<(ostream& out, Array& arr)
    {
        for(size_t i = 0; i < arr.n; ++i)
        {
            out << arr.a[i] << "  ";
        }
        out << endl;

        return out;
    }

};




int main()
{
    srand(time(0));

    Array a1(10, 1, 20);
    cout << a1;


    a1.Shell_sort();
    cout << a1;


    Array a2(10, 1, 10);
    cout << a2;


    a2.Heap_sort();
    cout << a2;

    Array a3(15, 1, 20);
    cout << a3;

    a3.Hoar_sort();
    cout << a3;


    Array a4(15, 1, 15);
    cout << a4;

    a4.Bit_sort();
    cout << a4;


    return 0;
}
