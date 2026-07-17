#pragma once
#include "Tree01.hpp"

template <typename T>
BinNode<T>::BinNode()
    : parent(nullptr),
      lchild(nullptr),
      rchild(nullptr),
      height(0)
{}

template <typename T>
BinNode<T>::BinNode(T e, BinNodePosition p, BinNodePosition lc, BinNodePosition rc, int h)
    : data(e),
      parent(p),
      lchild(lc),
      rchild(rc),
      height(h)
{}