/* 02：可扩充向量 */
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
        Vector(int c=DEFAULT_CAPACITY);
        Vector(const T* A, Rank low, Rank high);
        Vector(const Vector<T> &V, Rank low, Rank high);
        void copyFrom(const T* A, Rank lo, Rank hi);

        // 类析构函数
        ~Vector();

        // 向量扩容函数
        void expand();
};


int  main()
{
    return 0;
}

template <typename T>
Vector<T>::Vector(int c)
{
    _elem = new T[_capacity = c];
    _size = 0;
}

template <typename T>
Vector<T>::Vector(const Vector<T> &V, Rank low, Rank high)
{
    copyFrom(V._elem, low, high);
}

template <typename T>
Vector<T>::Vector(const T* A, Rank low, Rank high)
{
    copyFrom(A, low, high);
}

template <typename T>
void Vector<T>::copyFrom(const T* A, Rank lo, Rank hi)
{
    _capacity = 2*(hi-lo);
    _elem = new T[_capacity];
    _size = 0;
    while(lo < hi)
    {
        _elem[_size] = A[lo];
        _size += 1;
        lo += 1;
    }
}

template <typename T>
Vector<T>::~Vector()
{
    delete[] _elem;
}

template <typename T>
void Vector<T>::expand()
{
    if (_size < _capacity) return;                      // 尚未满员时不必扩容
    _capacity = std::max(_capacity, DEFAULT_CAPACITY);  // 不低于最小容量
    
    _elem = new T[_capacity <<= 1];     // 容量加倍
    T* oldElem = _elem;                 // 复制内容
    for (int i=0; i<_size; i++)
    {
        _elem[i] = oldElem[i];
    }
    delete[] oldElem;
}










