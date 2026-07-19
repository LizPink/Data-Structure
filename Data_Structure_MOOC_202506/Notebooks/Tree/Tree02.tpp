/* 02:Tree */
/* BinTree.tpp */
#pragma once

template <typename T>
BinTree<T>::BinTree()
    : _size{0},
      _root{nullptr}
{}

template <typename T>
BinTree<T>::~BinTree()
{
    if (0 < _size) remove(_root);
}