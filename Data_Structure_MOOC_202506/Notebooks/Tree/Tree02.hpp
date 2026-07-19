/* 02:数 */
/* BinTree类 */
#pragma once
#include "Tree01.hpp"

template <typename T>
class BinTree{
public:
    using BinNode = BinNode<T>;

protected:
    int _size;               // 规模
    BinNode* _root;      // 根节点
    virtual int updateHeight(BinNode* x);   // 更新节点x的高度
    void updateHeightAbove(BinNode* x);     // 更新节点x及其祖先的高度

public:
    // 构造与析构函数
    BinTree();
    ~BinTree();


    int size() const {return _size;}        // 返回二叉树的规模
    BinNode* root() const {return _root;}  // 返回根节点
    bool empty() const {return !_root;}     // 判断二叉树是否空

    // 元素删除
    int remove(BinNode* x);     // 删除以x作为根节点的子树，并返回该子树的规模

};

#include "Tree02.tpp"