// EB
// Implementing Binary Search Tree in C++

#include <iostream>

namespace BST
{
  template <class T>
  bool nullNodeCheck(T *node)
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
  Node *root;

public:
  BinarySearchTree()
  {
  }

  // The traversal codes are skeleton.
  // They will be modified to fit requirements
  //      listed in the main function and
  //      the homework document.
  //
  // Instead of writing the result to stdout,
  //      the function should take a std::pair<std::string, int>
  //      and its size as an argument and put the
  //      element inside that pair.
  void preorder(BST::Node *node)
  {
    if (!BST::nullNodeCheck(node))
    {
      std::cout << node->data << std::endl;
      preorder(node->left);
      preorder(node->right);
    }
  }

  void inorder(BST::Node *node)
  {
    if (!BST::nullNodeCheck(node))
    {
      inorder(node->left);
      std::cout << node->data << std::endl;
      inorder(node->right);
    }
  }

  void postorder(BST::Node *node)
  {
    if (!BST::nullNodeCheck(node))
    {
      postorder(node->left);
      postorder(node->right);
      std::cout << node->data << std::endl;
    }
  }

  BST::Node *searchTree(BST::Node *node, int key)
  {
    if (BST::nullNodeCheck(node) || key == node->data)
    {
      return node;
    }
    if (key < node->data)
    {
      return searchTree(node->left, key);
    }
    else
    {
      return searchTree(node->right, key);
    }
  }

  BST::Node *successor(BST::Node *node)
  {
    if (!BST::nullNodeCheck(node->right))
    {
      return getMinimum(node->right);
    }
    else
    {
      BST::Node *y = node->parent;
      while (!BST::nullNodeCheck(y) && node == y->right)
      {
        node = y;
        y = y->parent;
      }
      return y;
    }
  }

  predecessor()
  {
  }

  leftRotate()
  {
  }

  rightRotate()
  {
  }

  void insert(BST::Node *newNode)
  {
    BST::Node *iterator = root;
    BST::Node *parentOfNew = nullptr;

    while (!BST::nullNodeCheck(iterator))
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
    if (BST::nullNodeCheck(newNode))
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
    if (BST::nullNodeCheck(u->parent))
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
    if (!BST::nullNodeCheck(v))
    {
      v->parent = u->parent;
    }
  }

  void deleteNode(BST::Node *node)
  {
    if (BST::nullNodeCheck(node->left))
    {
      transplant(node, node->right);
    }
    else if (BST::nullNodeCheck(node->right))
    {
      transplant(node, node->left);
    }
    else
    {
      BST::Node *nodeSucc = getMinimum(node->right);
      if (nodeSucc != node->right)
      {
        transplant(nodeSucc, nodeSucc->right);
        nodeSucc->right = node->right;
        nodeSucc->right->parent = nodeSucc;
      }
      transplant(node, nodeSucc);
      nodeSucc->left = node->left;
      nodeSucc->left->parent = nodeSucc;
    }
  }

  getHeight()
  {
  }

  BST::Node *getMaximum(BST::Node *node)
  {
    while (!BST::nullNodeCheck(node->right))
    {
      node = node->right;
    }
    return node;
  }

  BST::Node *getMinimum(BST::Node *node)
  {
    while (node->left != NULL)
    {
      node = node->left;
    }
    return node;
  }

  getTotalNodes()
  {
  }
};