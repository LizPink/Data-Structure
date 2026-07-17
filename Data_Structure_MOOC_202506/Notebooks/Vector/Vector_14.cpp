/* 14:向量 */
/* 冒泡排序(C) */
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

        // 元素排序函数
        void swap(int &a, int &b);
        void bubble_sort_a(Rank lo, Rank hi);
        void bubble_sort_b(Rank lo, Rank hi);
        void bubble_sort_c(Rank lo, Rank hi);

        // 元素查找函数
        Rank find(const T& e, Rank lo, Rank hi) const;
        Rank binary_search_a(const T& e, Rank lo, Rank hi) const;
        Rank binary_search_b(const T& e, Rank lo, Rank hi) const;
        Rank binary_search_c(const T& e, Rank lo, Rank hi) const;

        // 元素去重函数
        int deduplicate();
        int uniquify();

        // 顺序判断函数
        int disordered() const;
};


int  main()
{
    Vector<int> vec{5};
    vec.insert(0,9); vec.insert(1,7); vec.insert(2,2); vec.insert(3,6); vec.insert(4,3); vec.insert(5,1); vec.insert(6,5);
    std::cout <<  "The initial Vectors is:" << std::endl; 
    for (int i=0; i<7; i++)
    {std::cout << vec[i] << " ";}
    std::cout << std::endl;

    vec.bubble_sort_c(0,7);
    std::cout <<  "The sorted Vectors is:" << std::endl; 
    for (int i=0; i<7; i++)
    {std::cout << vec[i] << " ";}
    
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

// 元素排序函数-冒泡排序（A）
template <typename T>
void Vector<T>::swap(int &a, int &b){
    int tmp = a;
    a = b;
    b = tmp;
}

template <typename T>
void Vector<T>::bubble_sort_a(Rank lo, Rank hi)
{
    for (int i=1; i<(hi-lo); i++)
    {
        for (int j=lo; j<hi-1; j++)
        {
            if(_elem[j] > _elem[j+1])
            {
                swap(_elem[j], _elem[j+1]);
            }
        }

    }
}

template <typename T>
void Vector<T>::bubble_sort_b(Rank lo, Rank hi)
{
    bool sorted = false;
    while(!sorted)
    {
        {
            sorted = true;
            for (int i=lo; i<hi-1; i++)
            {
                if(_elem[i] > _elem[i+1])
                {
                    swap(_elem[i], _elem[i+1]);
                    sorted = false;
                }
            }
            hi -= 1;
        } 
    }
}

template <typename T>
void Vector<T>::bubble_sort_c(Rank lo, Rank hi)
{
    while(lo<hi)
    {
        Rank last = lo;
        for (int i=lo+1; i<hi; ++i)
        {
            if(_elem[i-1] > _elem[i])
            {
                swap(_elem[i-1], _elem[i]);
                last = i;
            }
        }
        hi = last;
    }
}


// 元素查找函数：
template <typename T>	// 0 <= lo < hi <= _size
Rank Vector<T>::find(const T& e, Rank lo, Rank hi) const	// 逆向查找：在命中多个元素时返回秩最大者
{
	while ((lo<hi--) && (e!=_elem[hi])){}				    // 逆向查找
	return hi;			// 返回最终停止的索引：hi<lo意味着查找失败，否则hi即命中元素的秩。
}
// 元素查找函数-二分查找(a)
template <typename T>
Rank Vector<T>::binary_search_a(const T& e, Rank lo, Rank hi) const
{
    while (lo < hi)
    {
        int mi = (lo+hi) >> 1;
        if (e < _elem[mi])
            hi = mi;
        else if (_elem[mi] < e)
            lo = mi+1;
        else
            return mi;
    }
    return -1;
}
// 元素查找函数-二分查找(b)
template <typename T>			// 右边界查找：返回目标元素的右侧开位置
Rank Vector<T>::binary_search_b(const T& e, Rank lo, Rank hi) const
{
	Rank begin = lo, end = hi;
	while(lo < hi)				// 终止条件：形成空列表
	{
		Rank mid = (lo+hi) >> 1;		// 计算中间位置
		
		if (e < _elem[mid])
			{hi = mid;}
		else
			{lo = mid+1;}
	}
	Rank pos = lo;				// pos = lo = hi
	return (pos>begin && _elem[pos-1]==e) ? pos-1 : -1;	// 处理左右边界条件，返回命中元素的秩或者-1
}


// 元素查找函数-二分查找(c)
template <typename T>
Rank Vector<T>::binary_search_c(const T& e, Rank lo, Rank hi) const
{
    while(hi < lo)    // 终止条件：切分到单元素子向量
    {
        // 计算向量中点
        int mi = (lo + hi) >> 1;
        // 计算新的比较子向量
        (e < _elem[mi]) ? hi = mi : lo = mi+1;
    }
    return (_elem[lo] == e) ? lo : -1;  // 返回命中元素的秩或者-1
}



// 元素去重函数
template <typename T>
int Vector<T>::deduplicate()
{
    int oldSize = _size;    // 记录原规模
    Rank i = 1;             // 从_elem[1]开始
    while(i < _size)        // 自前向后逐一考察各元素
    {
        (find(_elem[i], 0, i) < 0)  // 在前缀中寻找雷同者
        ? i++                       // 若无雷同者，则往后继续查
        : remove(i,i+1);            // 若有雷同者，则删除雷同者
    }
    return oldSize - _size;         // 返回向量被删除的个数
}

template <typename T>
int Vector<T>::uniquify()
{
    Rank i=0, j=0;
    while(++j < _size)  // 逐一扫描，直至扫描所有元素
    {
        // 跳过雷同者；发现不同元素时，前移至新元素右侧
        if (_elem[i] != _elem[j])
        {
            _elem[++i] = _elem[j];
        }
    }

    _size = ++i;
    return j-i;         // 返回被删除的元素总数
}


// 顺序判断函数
template <typename T>
int Vector<T>::disordered() const
{
    int n = 0;
    for (int i=1; i<_size; i++)
    {
        n += int(_elem[i-1] > _elem[i]);
    }
    return n;
}