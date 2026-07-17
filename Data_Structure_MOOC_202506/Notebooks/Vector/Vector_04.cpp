/* 04:无序向量 */
/* 元素删除 */
#include <iostream>
#include <algorithm>

using Rank = int;
constexpr int DEFAULT_CAPACITY = 3;

template <typename T>
class Vector{
    public:
    using Rank = int;
    inline static constexpr int DEFAULT_CAPACITY = 3;

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

        // 元素访问函数
        T& operator[](Rank r) const;

        // 元素增加函数
        Rank insert(Rank r, const T& e);

        // 元素删除函数
        int remove(Rank lo, Rank hi);
};


int  main()
{
    Vector<int> vec{5};
    vec.insert(0,4); vec.insert(1,5); vec.insert(2,1); vec.insert(3,3); vec.insert(4,2);

    std::cout << vec[3] << std::endl;

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
    
    T* oldElem = _elem;                 // 保存旧的数据
    _elem = new T[_capacity <<= 1];     // 申请新的空间
    for (int i=0; i<_size; i++)         // 新旧数据转移
    {
        _elem[i] = oldElem[i];
    }
    delete[] oldElem;
}

template <typename T>
T& Vector<T>::operator[](Rank r) const
{
	return _elem[r];
}

template <typename T>
Rank Vector<T>::insert(Rank r, const T& e)
{
	expand();	// 如有必要则扩容
	for (int i = _size; i>r; i--)	// 自后向前
	{
		_elem[i] = _elem[i-1];		// 后继元素依次后移一个单位
	}
	_elem[r] = e; _size += 1;		// 置入新元素，更新容量
	return r;
}

template <typename T>	// 删除区间[lo,hi)
int Vector<T>::remove(Rank lo, Rank hi)
{
	if (lo == hi) {return 0;}
	while (hi < _size) {_elem[lo++] = _elem[hi++];}
	
	_size = lo;			// 更新规模
	return hi-lo;		// 返回被删除元素的个数
}




