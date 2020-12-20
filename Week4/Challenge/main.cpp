/*

Below, please implement the downHeap procedure for
a min heap data structure, which we will represent
as node-based tree for this exercise (not an array).

Suppose you are given a tree where the left and right
subtrees are min heaps, but the root node in particular
might not maintain the min heap property. Your code
should modify the tree rooted at Node* n so it is a
min heap. This means you need to satisfy the min heap
property: it is okay for a node's value to be equal to
one or both of its children, but the node's value must
not be greater than either of its children.

Tips:
Unlike the video lessons which demonstrated downHeap
implemented with an array implementation, this assignment
uses an ordinary binary tree with left and right child
pointers. This ordinary binary tree might not be complete
or balanced: any node might have only one child or the
other, or both, or neither. (You do not have to try to
balance the tree or turn it into a complete tree.)

If the root node exists, and if it has a left or right
child, and if one of the children has a smaller value
than the root node, then you should swap the root node
with the smaller child to move the large value down
into the tree. (This may need to be done recursively.)
Be careful to check whether pointers are null before
dereferencing them, as always; that includes using "->"
to access a class member through a pointer. In addition,
you must be careful not to accidentally compare "left"
and "right" pointers directly if you really intend to
compare the stored values "left->value" and "right->value".

Assume that these headers have already been included
for you:

#include <iostream>
#include <string>

You have the following class Node already defined.
You cannot change this class definition, so it is
shown here in a comment for your reference only:

class Node {
public:
  int value;
  Node *left, *right;
  Node(int val = 0) { value = val; left = right = nullptr; }
  ~Node() {
    delete left;
    left = nullptr;
    delete right;
    right = nullptr;
  }
};

This function has also previously been defined for you:

void printTreeVertical(const Node* n);

You can use it to print a verbose, vertical diagram of
a tree rooted at n. In this vertical format, a left child
is shown above a right child in the same column. If no
child exists, [null] is displayed.

*/
#include <iostream>
#include <string>
#include <stack>
#include <stdio.h>

class Node {
public:
  int value;
  Node *left, *right;
  Node(int val = 0) { value = val; left = right = nullptr; }
  ~Node() {
    delete left;
    left = nullptr;
    delete right;
    right = nullptr;
  }
};

// You can also use this compact printing function for debugging.
void printTree(Node *n);


void downHeapRecur(Node* n){
    if(!n){
        return;
    }

    if(!n->left && !n->right){
        //Do nothing
    }else if(!n->left && n->right){
        if(n->value > n->right->value){
            std::swap(n->value, n->right->value);
            downHeapRecur(n->right);
        }
    }else if(n->left && !n->right){
        if(n->value > n->left->value){
            std::swap(n->value, n->left->value);
            downHeapRecur(n->left);
        }
    }else{
        if(n->left->value > n->right->value){
            if(n->value > n->right->value){
                std::swap(n->value, n->right->value);
                downHeapRecur(n->right);
            }
        }else{
            if(n->value > n->left->value){
                std::swap(n->value, n->left->value);
                downHeapRecur(n->left);
            }
        }
    }
}

/*
Node*& downHeapIter(Node*& n){


}
*/

void downHeap(Node *n) {
    downHeapRecur(n);
  // Implement downHeap() here.

}

// You can also use this compact printing function for debugging.
void printTree(Node *n) {
  if (!n) return;
  std::cout << n->value << "(";
  printTree(n->left);
  std::cout << ")(";
  printTree(n->right);
  std::cout << ")";
}

void printTreeVertical(Node* n) {

  // Stacks maintain the next node contents to display as well as the
  // corresponding amount of indentation to show in the margin.
  std::stack<Node*> node_stack;
  std::stack<int> margin_stack;

  node_stack.push(n);
  margin_stack.push(0);

  while (!node_stack.empty()) {

    Node* n = node_stack.top();
    node_stack.pop();

    int margin_level = margin_stack.top();
    margin_stack.pop();

    for (int i=0; i < margin_level; i++) {
      std::cout << " ";
    }

    if (margin_level > 0) {
      std::cout << "|- ";
    }
    else {
      std::cout << ". ";
    }

    if (n) {

      // Only push child markers if at least one child exists.
      // This makes the leaf output clearer: if both children are nullptr,
      // they are simply not printed.
      if (n->left || n->right) {
        node_stack.push(n->right);
        margin_stack.push(margin_level+1);
        node_stack.push(n->left);
        margin_stack.push(margin_level+1);
      }

      std::cout << "[" << n->value << "] ";
    }
    else {
      // no child (nullptr)
      std::cout << "[]" << std::endl;
    }

  }

}

int main() {
  Node *n = new Node(100);
  n->left = new Node(1);
  n->right = new Node(2);
  n->right->left = new Node(3);
  n->right->right = new Node(4);
  n->right->right->right = new Node(5);

  std::cout << "Orignal, Compact printout:" << std::endl;
  printTree(n);
  std::cout <<"\n";

  downHeap(n);

  std::cout << "After downHeap, Compact printout:" << std::endl;
  printTree(n);
  std::cout <<"\n";
//  std::cout << std::endl << "Vertical printout:" << std::endl;
//  printTreeVertical(n);
//  std::cout <<"\n";

  delete n;
  n = nullptr;

  return 0;
}
