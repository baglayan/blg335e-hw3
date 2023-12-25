/**
 * bst.cpp
 *
 * BLG 335E Analysis of Algorithms Project 3
 * Implementing binary search tree in C++
 *
 * Name : Meriç Bağlayan
 * Email: baglayan19@itu.edu.tr
 * Id   : 150190056
 * Date : 2023-12-26
 */

#include <iostream>

namespace BST
{
  template <class T>
  bool bstNullNodeCheck(T *node)
  {
    // this is implemented as RBT's null can be implemented as sentinel node
    // which cannot be checked by nullptr
    // definite control for a node being null is checking its parent and both children
    if (node == nullptr)
    {
      return true;
    }
    if (node->parent == nullptr && node->left == nullptr && node->right == nullptr)
    {
      return true;
    }
    return false;
  }

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

  unsigned long long _getHeight(BST::Node *node)
  {
    if (BST::bstNullNodeCheck(node))
    {
      return 0;
    }
    unsigned long long leftHeight = _getHeight(node->left);
    unsigned long long rightHeight = _getHeight(node->right);
    return 1 + maximum(leftHeight, rightHeight);
  }

  BST::Node *_getMinimum(BST::Node *node)
  {
    while (!BST::bstNullNodeCheck(node) && BST::bstNullNodeCheck(node->left))
    {
      node = node->left;
    }
    return node;
  }

  BST::Node *_getMaximum(BST::Node *node)
  {
    while (!BST::bstNullNodeCheck(node->right))
    {
      node = node->right;
    }
    return node;
  }

  void _preorder(BST::Node *node, std::pair<std::string, int> *array, unsigned long long &index, unsigned long long size)
  {
    if (!BST::bstNullNodeCheck(node) && index < size)
    {
      std::pair<std::string, int> iterator = {node->name, node->data};
      array[index] = iterator;
      index++;
      _preorder(node->left, array, index, size);
      _preorder(node->right, array, index, size);
    }
  }

  void _inorder(BST::Node *node, std::pair<std::string, int> *array, unsigned long long &index, unsigned long long size)
  {
    if (!BST::bstNullNodeCheck(node) && index < size)
    {
      _inorder(node->left, array, index, size);
      std::pair<std::string, int> iterator = {node->name, node->data};
      array[index] = iterator;
      index++;
      _inorder(node->right, array, index, size);
    }
  }

  void _postorder(BST::Node *node, std::pair<std::string, int> *array, unsigned long long &index, unsigned long long size)
  {
    if (!BST::bstNullNodeCheck(node) && index < size)
    {
      _postorder(node->left, array, index, size);
      _postorder(node->right, array, index, size);
      std::pair<std::string, int> iterator = {node->name, node->data};
      array[index] = iterator;
      index++;
    }
  }

  BST::Node *_searchTree(BST::Node *node, int key)
  {
    if (BST::bstNullNodeCheck(node) || key == node->data)
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
    if (BST::bstNullNodeCheck(node->left))
    {
      transplant(node, node->right);
    }
    else if (BST::bstNullNodeCheck(node->right))
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

  void preorder(std::pair<std::string, int> *array, unsigned long long size)
  {
    static unsigned long long index = 0;
    _preorder(root, array, index, size);
  }

  void inorder(std::pair<std::string, int> *array, unsigned long long size)
  {
    static unsigned long long index = 0;
    _inorder(root, array, index, size);
  }

  void postorder(std::pair<std::string, int> *array, unsigned long long size)
  {
    static unsigned long long index = 0;
    _postorder(root, array, index, size);
  }

  BST::Node *searchTree(int key)
  {
    return _searchTree(root, key);
  }

  BST::Node *successor(BST::Node *node)
  {
    if (!BST::bstNullNodeCheck(node->right))
    {
      return _getMinimum(node->right);
    }
    else
    {
      BST::Node *y = node->parent;
      while (!BST::bstNullNodeCheck(y) && node == y->right)
      {
        node = y;
        y = y->parent;
      }
      return y;
    }
  }

  BST::Node *predecessor(BST::Node *node)
  {
    if (!BST::bstNullNodeCheck(node->left))
    {
      return _getMaximum(node->left);
    }
    else
    {
      BST::Node *y = node->parent;
      while (!BST::bstNullNodeCheck(y) && node == y->left)
      {
        node = y;
        y = y->parent;
      }
      return y;
    }
  }

  void insert(std::string name, int data)
  {
    BST::Node *newNodePtr = new BST::Node{data, name, nullptr, nullptr, nullptr};
    BST::Node *iterator = root;
    BST::Node *parentOfNew = nullptr;

    while (!BST::bstNullNodeCheck(iterator))
    {
      parentOfNew = iterator;
      if (newNodePtr->data < iterator->data)
      {
        iterator = iterator->left;
      }
      else
      {
        iterator = iterator->right;
      }
    }
    newNodePtr->parent = parentOfNew;
    if (BST::bstNullNodeCheck(newNodePtr))
    {
      root = newNodePtr;
    }
    else if (newNodePtr->data < parentOfNew->data)
    {
      parentOfNew->left = newNodePtr;
    }
    else
    {
      parentOfNew->right = newNodePtr;
    }
  }

  void transplant(BST::Node *u, BST::Node *v)
  {
    if (BST::bstNullNodeCheck(u->parent))
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
    if (!BST::bstNullNodeCheck(v))
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
    return _getHeight(root);
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

  void countNodes(BST::Node *node, unsigned long long &count)
  {
    if (BST::bstNullNodeCheck(node))
    {
      return;
    }
    count++;
    countNodes(node->left, count);
    countNodes(node->right, count);
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