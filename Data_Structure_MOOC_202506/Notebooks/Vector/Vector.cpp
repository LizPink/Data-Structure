#include <iostream>

using Rank = int;
constexpr int DEFAULT_CAPACITY = 3;

template <typename T> class Vector{
    private:
        // 规模、容量、数据区
        Rank _size; int _capacity; T* _elem;
    
    public:
        // 【类构造函数】默认
        Vector(int c=DEFAULT_CAPACITY)
        {
            _elem = new T[_capacity = c];
            _size = 0;
        }
        // 【类构造函数】数组区间复制
        Vector(T const* A, Rank low, Rank high)
        {
            copyFrom(A, low, high);
        }
        // 【类构造函数】向量区间复制
        Vector(Vector<T> const &V, Rank low, Rank high)
        {
            copyFrom(V._elem, low, high);
        }
        
        // 【类析构函数】
        ~Vector()
        {
            delete [] _elem;
        }
};