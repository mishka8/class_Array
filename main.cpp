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
        if(n != other.n)
            return false;

        for(int i = 0; i < n; ++i)
        {
            if(a[i] != other.a[i])
                return false;

        }
        return true;
    }



    void Shell_sort()//выбор шага, сортировка подмассивов, уменьшение шага
    {
         int h = 1;
        while (h < n / 3)
        {
            //h = 3 * h + 1; //шаг 1 4 13
            h = h * 2 + 1;//шаг 1 3 7
        }
        while (h >= 1)
        {
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
        int j = n / 2 - 1;
        for(int i = j; i >= 0; --i)
        {
            pyramid(i, n);
        }

        int k = n - 1;
        for(int i = k; i >= 0; --i)
        {
            swap(a[0], a[i]);
            pyramid(0, i);
        }

    }

    void pyramid(int i , int size)
    {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if(left < size && a[left] > a[largest])
            largest = left;

        if(right < size && a[right] > a[largest])
            largest = right;

        if(largest != i)
        {
            swap(a[i], a[largest]);
            pyramid(largest, size);
        }
    }


    void Hoar_sort()
    {

    }

    int help_Hoar(int l, int r)
    {
        int pivot = a[r];
        int i = l - 1;
        for(int j = l; j < r; j++)
        {
            if(a[j] <= pivot)
            {
                i++;
                swap(a[i] , a[j]);
            }
        }

        swap(a[i + 1], a[r]);
        return (i + 1);
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
    cout << "a1 non sorted - " << a1;


    a1.Shell_sort();
    cout << "a1 sorted " << a1 << endl;


    Array a2(10, 1, 10);
    cout << "a2 non sorted - " << a2 << endl;


    a2.Heap_sort();
    cout << "a2 sorted " << a2 << endl;

    Array a3(15, 1, 20);
    cout << "a3 non sorted - " <<  a3 << endl;

    a3.Hoar_sort();
    cout << "a3 sorted " << a3 << endl;


//    Array a4(15, 1, 15);
//    cout << a4;

//    a4.Bit_sort();
//    cout << a4;


    return 0;
}
