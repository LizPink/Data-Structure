/* 向量类型基础 */
#include <iostream>
#include <algorithm>

using Rank = int;
constexpr int DEFAULT_CAPACITY = 3;

template <typename T>
class Vector{
    private:
        Rank _size;         // 规模
        int _capacity;      // 容量
        T* _elem;           // 数据区
    
    public:
        // 类构造函数
        Vector(int c=DEFAULT_CAPACITY)
        {
            _elem = new T[_capacity = c];
            _size = 0;
        }
        // 类构造函数
        Vector(const T* A, Rank low, Rank high)
        {
            copyFrom(A, low, high);
        }
        // 类构造函数
        Vector(const Vector<T> &V, Rank low, Rank high)
        {
            copyFrom(V._elem, low, high);
        }

        // 拷贝构造函数
        void copyFrom(const T* A, Rank lo, Rank hi);

        // 类析构函数
        ~Vector();
};


int  main()
{

    return 0;
}

template <typename T>
void Vector<T>::copyFrom(const T* A, Rank lo, Rank hi)
{
    _capacity = 2*(hi-lo);
    _elem = new T[_capacity];
    _size = 0;
    while(lo < hi)
    {
        _elem[lo] = A[lo];
        lo += 1;
    }
}

template <typename T>
Vector<T>::~Vector()
{
    delete[] _elem;
}