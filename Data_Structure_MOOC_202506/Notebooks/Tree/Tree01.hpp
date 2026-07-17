/* 01:树类型 */
/* 二叉节点类的定义 */
#pragma once


template <typename T>
class BinNode{
public:
    using BinNodePosition = BinNode<T>*;

private:
    BinNodePosition parent, lchild, rchild;  // 父亲与孩子节点
    T data;           // 数据区域
    int height;       // 子树高度

public:
    // 构造与析构
    // 构造函数：默认构造函数
    BinNode();
    BinNode(const T& e, BinNodePosition p=nullptr, BinNodePosition lc=nullptr, BinNodePosition rc=nullptr, int h=0);
    

    // 接口实现
    int size();                                 // 统计子树规模
    BinNodePosition insertAsLC(const T&);
    BinNodePosition insertAsRC(const T&);
    BinNodePosition successor();                // 中序遍历当前节点的直接后继
    template <typename VST>
    void travelLevel(VST&);
    template <typename VST>
    void travelPre(VST&);
    template <typename VST>
    void trevelIn(VST&);
    template <typename VST>
    void trevelPost(VST&);
};

#include "Tree01.tpp"