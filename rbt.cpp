/**
 * rbt.cpp
 *
 * BLG 335E Analysis of Algorithms Project 3
 * Implementing red-black tree in C++
 *
 * Name : Meriç Bağlayan
 * Email: baglayan19@itu.edu.tr
 * Id   : 150190056
 * Date : 2023-12-26
 */

#include <iostream>

namespace RBT
{
  template <class T>
  bool rbtNullNodeCheck(T *node)
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

  enum Color
  {
    BLACK = 0,
    RED = 1,
    UNDEFINED = 2
  };

  struct Node
  {
    int data;
    std::string name;
    Node *parent;
    Node *left;
    Node *right;
    int color; // 0 for black, 1 for red
  };
}

class RedBlackTree
{
private:
  RBT::Node *root;

  unsigned long long _getHeight(RBT::Node *node)
  {
    if (RBT::rbtNullNodeCheck(node))
    {
      return 0;
    }
    unsigned long long leftHeight = _getHeight(node->left);
    unsigned long long rightHeight = _getHeight(node->right);
    return 1 + maximum(leftHeight, rightHeight);
  }

  RBT::Node *_getMinimum(RBT::Node *node)
  {
    while (RBT::rbtNullNodeCheck(node->left))
    {
      node = node->left;
    }
    return node;
  }

  RBT::Node *_getMaximum(RBT::Node *node)
  {
    while (!RBT::rbtNullNodeCheck(node->right))
    {
      node = node->right;
    }
    return node;
  }

  void _preorder(RBT::Node *node, std::pair<std::string, int> *array, unsigned long long &index, unsigned long long size)
  {
    if (!RBT::rbtNullNodeCheck(node) && index < size)
    {
      std::pair<std::string, int> iterator = {node->name, node->data};
      array[index] = iterator;
      index++;
      _preorder(node->left, array, index, size);
      _preorder(node->right, array, index, size);
    }
  }

  void _inorder(RBT::Node *node, std::pair<std::string, int> *array, unsigned long long &index, unsigned long long size)
  {
    if (!RBT::rbtNullNodeCheck(node) && index < size)
    {
      _inorder(node->left, array, index, size);
      std::pair<std::string, int> iterator = {node->name, node->data};
      array[index] = iterator;
      index++;
      _inorder(node->right, array, index, size);
    }
  }

  void _postorder(RBT::Node *node, std::pair<std::string, int> *array, unsigned long long &index, unsigned long long size)
  {
    if (!RBT::rbtNullNodeCheck(node) && index < size)
    {
      _postorder(node->left, array, index, size);
      _postorder(node->right, array, index, size);
      std::pair<std::string, int> iterator = {node->name, node->data};
      array[index] = iterator;
      index++;
    }
  }

  RBT::Node *_searchTree(RBT::Node *node, int key)
  {
    if (RBT::rbtNullNodeCheck(node) || key == node->data)
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

public:
  RedBlackTree()
  {
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

  RBT::Node *searchTree(int key)
  {
    return _searchTree(root, key);
  }

  RBT::Node *successor(RBT::Node *node)
  {
    if (!RBT::rbtNullNodeCheck(node->right))
    {
      return _getMinimum(node->right);
    }
    else
    {
      RBT::Node *y = node->parent;
      while (!RBT::rbtNullNodeCheck(y) && node == y->right)
      {
        node = y;
        y = y->parent;
      }
      return y;
    }
  }

  RBT::Node *predecessor(RBT::Node *node)
  {
    if (!RBT::rbtNullNodeCheck(node->left))
    {
      return _getMaximum(node->left);
    }
    else
    {
      RBT::Node *y = node->parent;
      while (!RBT::rbtNullNodeCheck(y) && node == y->left)
      {
        node = y;
        y = y->parent;
      }
      return y;
    }
  }

  void leftRotate(RBT::Node *node)
  {
    RBT::Node *next = node->right;
    node->right = next->left;
    if (!RBT::rbtNullNodeCheck(next->left)) // not entirely sure
    {
      next->left->parent = node;
    }
    next->parent = node->parent;
    if (RBT::rbtNullNodeCheck(node->parent))
    {
      root = next;
    }
    else if (node == node->parent->left)
    {
      node->parent->left = next;
    }
    else
    {
      node->parent->right = next;
    }
    next->left = node;
    node->parent = next;
  }

  void rightRotate(RBT::Node *node)
  {
    RBT::Node *prev = node->left;
    node->left = prev->right;
    if (!RBT::rbtNullNodeCheck(prev->right))
    {
      prev->right->parent = node;
    }
    prev->parent = node->parent;
    if (RBT::rbtNullNodeCheck(node->parent))
    {
      root = prev;
    }
    else if (node == node->parent->right)
    {
      node->parent->right = prev;
    }
    else
    {
      node->parent->left = prev;
    }
    prev->right = node;
    node->parent = prev;
  }

  void insert(std::string name, int data)
  {
    RBT::Node newNode = {data, name, nullptr, nullptr, nullptr, RBT::UNDEFINED};
    RBT::Node *newNodePtr = &newNode;
    RBT::Node *iterator = root;
    RBT::Node *parentOfNew = nullptr;

    while (!RBT::rbtNullNodeCheck(iterator))
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
    if (RBT::rbtNullNodeCheck(parentOfNew))
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
    newNodePtr->left = nullptr;
    newNodePtr->right = nullptr;
    newNodePtr->color = RBT::RED;
    insertFixup(newNodePtr);
  }

  void insertFixup(RBT::Node *node)
  {
    while (!RBT::rbtNullNodeCheck(node->parent) && node->parent->color == RBT::RED)
    {
      if (node->parent == node->parent->parent->left)
      {
        RBT::Node *uncle = node->parent->parent->right;
        if (uncle->color == RBT::RED)
        {
          node->parent->color = RBT::BLACK;
          uncle->color = RBT::BLACK;
          node->parent->parent->color = RBT::RED;
          node = node->parent->parent;
        }
        else
        {
          if (node == node->parent->right)
          {
            node = node->parent;
            leftRotate(node);
          }
          node->parent->color = RBT::BLACK;
          node->parent->parent->color = RBT::RED;
          rightRotate(node->parent->parent);
        }
      }
      else
      {
        RBT::Node *uncle = node->parent->parent->left;
        if (uncle->color == RBT::RED)
        {
          node->parent->color = RBT::BLACK;
          uncle->color = RBT::BLACK;
          node->parent->parent->color = RBT::RED;
          node = node->parent->parent;
        }
        else
        {
          if (node == node->parent->left)
          {
            node = node->parent;
            rightRotate(node);
          }
          node->parent->color = RBT::BLACK;
          node->parent->parent->color = RBT::RED;
          leftRotate(node->parent->parent);
        }
      }
    }
    root->color = RBT::BLACK;
  }

  void transplant(RBT::Node *u, RBT::Node *v)
  {
    if (RBT::rbtNullNodeCheck(u->parent))
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
    v->parent = u->parent;
  }

  void deleteNode(int key)
  {
    _deleteNode(searchTree(key));
  }

  void _deleteNode(RBT::Node *node)
  {
    RBT::Node *succ = node;
    RBT::Color succOriginalColor = (RBT::Color)succ->color;
    RBT::Node *next;
    if (RBT::rbtNullNodeCheck(node->left))
    {
      next = node->right;
      transplant(node, node->left);
    }
    else if (RBT::rbtNullNodeCheck(node->right))
    {
      next = node->left;
      transplant(node, node->left);
    }
    else
    {
      succ = _getMinimum(node->right);
      succOriginalColor = (RBT::Color)succ->color;
      next = succ->right;
      if (succ != node->right)
      {
        transplant(succ, succ->right);
        succ->right = node->right;
        succ->right->parent = succ;
      }
      else
      {
        next->parent = succ;
      }
      transplant(node, succ);
      succ->left = node->left;
      succ->left->parent = succ;
      succ->color = node->color;
    }
    if (succOriginalColor == RBT::BLACK)
    {
      deleteFixup(next);
    }
  }

  void deleteFixup(RBT::Node *node)
  {
    RBT::Node *sibling;
    while (node != root && node->color == RBT::BLACK)
    {
      if (node == node->parent->left)
      {
        sibling = node->parent->right;
        if (sibling->color == RBT::RED)
        {
          sibling->color = RBT::BLACK;
          node->parent->color = RBT::RED;
          leftRotate(node->parent);
          sibling = node->parent->right;
        }
        if (sibling->left->color == RBT::BLACK && sibling->right->color == RBT::BLACK)
        {
          sibling->color = RBT::RED;
          node = node->parent;
        }
        else
        {
          if (sibling->right->color == RBT::BLACK)
          {
            sibling->left->color = RBT::BLACK;
            sibling->color = RBT::RED;
            rightRotate(sibling);
            sibling = node->parent->right;
          }
          sibling->color = node->parent->color;
          node->parent->color = RBT::BLACK;
          sibling->right->color = RBT::BLACK;
          leftRotate(node->parent);
          node = root;
        }
      }
      else
      {
        sibling = node->parent->left;
        if (sibling->color == RBT::RED)
        {
          sibling->color = RBT::BLACK;
          node->parent->color = RBT::RED;
          rightRotate(node->parent);
          sibling = node->parent->left;
        }
        if (sibling->right->color == RBT::BLACK && sibling->left->color == RBT::BLACK)
        {
          sibling->color = RBT::RED;
          node = node->parent;
        }
        else
        {
          if (sibling->left->color == RBT::BLACK)
          {
            sibling->right->color = RBT::BLACK;
            sibling->color = RBT::RED;
            leftRotate(sibling);
            sibling = node->parent->left;
          }
          sibling->color = node->parent->color;
          node->parent->color = RBT::BLACK;
          sibling->left->color = RBT::BLACK;
          rightRotate(node->parent);
          node = root;
        }
      }
    }
    node->color = RBT::BLACK;
  }

  unsigned long long getHeight()
  {
    return _getHeight(root);
  }

  RBT::Node *getMaximum()
  {
    return _getMaximum(root);
  }

  RBT::Node *getMinimum()
  {
    return _getMinimum(root);
  }

  unsigned long long getTotalNodes()
  {
    unsigned long long count = 0;
    countNodes(root, count);
    return count;
  }

  void countNodes(RBT::Node *node, unsigned long long &count)
  {
    if (RBT::rbtNullNodeCheck(node))
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