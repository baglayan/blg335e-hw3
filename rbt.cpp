// EB
// Implementing Red-Black Tree in C++

#include <iostream>

namespace RBT
{
  struct Node : BST::Node
  {
    // int data;
    // std::string name;
    // Node *parent;
    // Node *left;
    // Node *right;
    int color; //0 for black, 1 for red
  };
}

class RedBlackTree : public BinarySearchTree
{
private:
  RBT::Node* root;
public:
  RedBlackTree()
  {
    
  }

  preorder()
  {
  }

  inorder()
  {
  }

  postorder()
  {
  }

  searchTree()
  {
  }

  successor(Node *node)
  {
    
  }

  predecessor()
  {
  }

  insert()
  {
  }

  deleteNode()
  {
  }

  getHeight()
  {
  }

  RBT::Node *getMaximum()
  {
    
  }

  RBT::Node *getMinimum(Node *node)
  {
    
  }

  getTotalNodes()
  {
  }
};