/* Tree01：树 */
/* 二叉树的定义 */
#pragma once

template <typename T>
BinNode<T>::BinNode()
    : parent(nullptr),
      lchild(nullptr),
      rchild(nullptr),
      height(0)
{}

template <typename T>
BinNode<T>::BinNode(const T& e, BinNodePosition p, BinNodePosition lc, BinNodePosition rc, int h)
    : data(e),
      parent(p),
      lchild(lc),
      rchild(rc),
      height(h)
{}

// 新节点的插入
template <typename T>
BinNode<T>* BinNode<T>::insertAsLC(const T& e)
{
    lchild = new BinNode(e, this);
    return lchild;
}

template <typename T>
BinNode<T>* BinNode<T>::insertAsRC(const T& e)
{
    rchild = new BinNode(e, this);
    return rchild;
}

// 统计子树的规模
template <typename T>
int BinNode<T>::size()
{
    int s = 1;
    if(lchild)
        s += lchild->size();     // 递归的计算子树的规模
    if(rchild)
        s += rchild->size();
    return s;
}
