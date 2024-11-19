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

    void Shell_sort()
    {
        for(int step = n / 2; step > 0; step /= 2)//начинаем с половины масива
        {
            for(int i = 1; i < n; i+=step)//елемент i  сравниваем с элементом на step левее
            {
                //cout << i << "----------";
                int tmp = a[i];//запоминаем текущий элемент

                int j;

                for(j = i; j >= step && a[j - step] > tmp; j -= step)//првоерка что мы не вышли за масив
                {
                    //cout << "i = " << i <<  " ----  j = " << j << " =====  [j - step] = " << j - step << " === === a[j - step] = " << a[j - step] << " > " << tmp << " = tmp" << endl;
                    //сравниваем элемент j - step с текущим tmp
                    a[j] = a[j - step];//сдвигаем влево
                }
                //cout << endl << endl;


                a[j] = tmp;//вставка элемента на место
//                for(int h = 0; h < n; ++h)
//                    cout << a[h] << "  ";
            }
//            cout << endl;
        }
    }

    void help_Heap(int n, int i)
    {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if(left < n && a[left] > a[largest])
            largest = left;

        if(right < n && a[right] > a[largest])
            largest = right;

        if(largest != i)
        {
            swap(a[i], a[largest]);

            help_Heap(n, largest);
        }
    }

    void Heap_sort()
    {
        for(int i = n / 2 - 1; i >= 0; i--)
            help_Heap(n, i);

        for(int i = n - 1;  i >= 0; i--)
        {
            swap(a[0], a[i]);

            help_Heap(i, 0);
        }
    }

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

    int main_bit()//поиск главного бита
    {
        int max = a[0];
        for (int i = 0; i < n; i++)
        {
            if (a[i] > max) max = a[i];
        }

        int k = 0;

        while (max)
        {
            max >>= 1;
            k++;
        }
        return k - 1;
    }

    void Bit_sort(int l = 0, int r = 0, int k = 0, bool flag = true)
    {
        if (flag)
        {
            flag = false;
            l = 0;
            r = n - 1;
            k = this->main_bit();
        }
        if (!(l >= r || k < 0))
        {
            int i = l, j = r;
            int mask = 1 << k;
            while (i <= j)
            {
                while (i <= j && !(a[i] & mask))
                    i++;

                while (i <= j && a[j] & mask)
                    j--;

                if (i < j)
                    swap(a[i++], a[j--]);
            }
            this->Bit_sort(l, j, k - 1, flag);
            this->Bit_sort(i, r, k - 1, flag);
        }
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

    Array a4(15, 1, 500);
    cout << a4;

    a4.Bit_sort();
    cout << a4;


    return 0;
}
