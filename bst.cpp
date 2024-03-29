/**
 * bst.cpp
 *
 * BLG 335E Analysis of Algorithms Project 3
 * Implementing binary search tree in C++
 *
 * Name : Meriç Bağlayan
 * Email: baglayan19@itu.edu.tr
 * Id   : 150190056
 * Date : 2023-12-27
 */

#include <iostream>

namespace BST
{
  struct Node
  {
    int data;
    std::string name;
    Node *parent;
    Node *left;
    Node *right;
  };
}

class BinarySearchTree
{
private:
  BST::Node *root;

  void clear(BST::Node *node)
  {
    if (node != nullptr)
    {
      clear(node->left);
      clear(node->right);
      delete node;
    }
  }

  unsigned long long _getHeight(BST::Node *node)
  {
    if (node == nullptr)
    {
      return 0;
    }
    unsigned long long leftHeight = _getHeight(node->left);
    unsigned long long rightHeight = _getHeight(node->right);
    return 1 + maximum(leftHeight, rightHeight);
  }

  BST::Node *_getMinimum(BST::Node *node)
  {
    if (node->left == nullptr)
    {
      return node;
    }
    else
    {
      return _getMinimum(node->left);
    }
  }

  BST::Node *_getMaximum(BST::Node *node)
  {
    if (node->right == nullptr)
    {
      return node;
    }
    else
    {
      return _getMaximum(node->right);
    }
  }

  void _preorder(BST::Node *node, std::pair<std::string, int> *array, unsigned long long &index, unsigned long long &size)
  {
    if (node != nullptr && index < size)
    {
      std::pair<std::string, int> iterator = {node->name, node->data};
      array[index] = iterator;
      index++;
      size++;
      _preorder(node->left, array, index, size);
      _preorder(node->right, array, index, size);
    }
  }

  void _inorder(BST::Node *node, std::pair<std::string, int> *array, unsigned long long &index, unsigned long long &size)
  {
    if (node != nullptr && index <= size)
    {
      _inorder(node->left, array, index, size);
      std::pair<std::string, int> iterator = {node->name, node->data};
      array[index] = iterator;
      index++;
      size++;
      _inorder(node->right, array, index, size);
    }
  }

  void _postorder(BST::Node *node, std::pair<std::string, int> *array, unsigned long long &index, unsigned long long &size)
  {
    if (node != nullptr && index <= size)
    {
      _postorder(node->left, array, index, size);
      _postorder(node->right, array, index, size);
      std::pair<std::string, int> iterator = {node->name, node->data};
      array[index] = iterator;
      index++;
      size++;
    }
  }

  BST::Node *_searchTree(BST::Node *node, int key)
  {
    if (node == nullptr || key == node->data)
    {
      return node;
    }
    if (key < node->data)
    {
      return _searchTree(node->left, key);
    }
    else
    {
      return _searchTree(node->right, key);
    }
  }

  void _deleteNode(BST::Node *node)
  {
    if (node->left == nullptr)
    {
      transplant(node, node->right);
    }
    else if (node->right == nullptr)
    {
      transplant(node, node->left);
    }
    else
    {
      BST::Node *succ = _getMinimum(node->right);
      if (succ != node->right)
      {
        transplant(succ, succ->right);
        succ->right = node->right;
        succ->right->parent = succ;
      }
      transplant(node, succ);
      succ->left = node->left;
      succ->left->parent = succ;
    }
  }

public:
  BinarySearchTree()
  {
    root = nullptr;
  }

  ~BinarySearchTree()
  {
    clear(root);
  }

  void preorder(std::pair<std::string, int> *array, unsigned long long size)
  {
    unsigned long long index = 0;
    _preorder(root, array, index, size);
  }

  void inorder(std::pair<std::string, int> *array, unsigned long long size)
  {
    unsigned long long index = 0;
    _inorder(root, array, index, size);
  }

  void postorder(std::pair<std::string, int> *array, unsigned long long size)
  {
    unsigned long long index = 0;
    _postorder(root, array, index, size);
  }

  BST::Node *searchTree(int key)
  {
    return _searchTree(root, key);
  }

  BST::Node *successor(BST::Node *node)
  {
    if (node->right != nullptr)
    {
      return _getMinimum(node->right);
    }
    else
    {
      BST::Node *y = node->parent;
      while (y != nullptr && node == y->right)
      {
        node = y;
        y = y->parent;
      }
      return y;
    }
  }

  BST::Node *predecessor(BST::Node *node)
  {
    if (node->left != nullptr)
    {
      return _getMaximum(node->left);
    }
    else
    {
      BST::Node *y = node->parent;
      while (y != nullptr && node == y->left)
      {
        node = y;
        y = y->parent;
      }
      return y;
    }
  }

  void insert(std::string name, int data)
  {
    BST::Node *newNode = new BST::Node{data, name, nullptr, nullptr, nullptr};
    BST::Node *iterator = root;
    BST::Node *parentOfNew = nullptr;

    while (iterator != nullptr)
    {
      parentOfNew = iterator;
      if (newNode->data < iterator->data)
      {
        iterator = iterator->left;
      }
      else
      {
        iterator = iterator->right;
      }
    }
    newNode->parent = parentOfNew;
    if (parentOfNew == nullptr)
    {
      root = newNode;
    }
    else if (newNode->data < parentOfNew->data)
    {
      parentOfNew->left = newNode;
    }
    else
    {
      parentOfNew->right = newNode;
    }
  }

  void transplant(BST::Node *u, BST::Node *v)
  {
    if (u->parent == nullptr)
    {
      root = v;
    }
    else if (u == u->parent->left)
    {
      u->parent->left = v;
    }
    else
    {
      u->parent->right = v;
    }
    if (v != nullptr)
    {
      v->parent = u->parent;
    }
  }

  void deleteNode(int key)
  {
    _deleteNode(searchTree(key));
  }

  unsigned long long getHeight()
  {
    return _getHeight(root) - 1;
  }

  BST::Node *getMaximum()
  {
    return _getMaximum(root);
  }

  BST::Node *getMinimum()
  {
    return _getMinimum(root);
  }

  unsigned long long getTotalNodes()
  {
    unsigned long long count = 0;
    countNodes(root, count);
    return count;
  }

  unsigned long long countNodes(BST::Node *node, unsigned long long &count)
  {
    if (node == nullptr)
    {
      return 0;
    }
    count++;
    unsigned long long leftSize = countNodes(node->left, count);
    unsigned long long rightSize = countNodes(node->right, count);
    return leftSize + rightSize;
  }

  unsigned long long maximum(unsigned long long a, unsigned long long b)
  {
    if (a < b)
    {
      return b;
    }
    return a;
  }
};