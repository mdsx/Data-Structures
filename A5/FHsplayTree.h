// File FHsplayTree.h
// Template definitions for FHsplayTrees.  
#ifndef FHSPLAYTREE_H
#define FHSPLAYTREE_H
#include "FHsearch_tree.h"

// ---------------------- FHsplayTree Prototype --------------------------------
template <class Comparable>
class FHsplayTree : public FHsearch_tree < Comparable >
{
public:
   // override base class insert/remove
   bool insert(const Comparable &x);
   bool remove(const Comparable &x);

   // overloaded methods lose const modifier due to splay() calls
   bool contains(const Comparable &x);
   const Comparable & find(const Comparable &x);

   // for debugging purposes; proof of splaying
   const Comparable &showRoot();
protected:
   // protected splay and rotation methods to be used in public methods
   void splay(FHs_treeNode<Comparable> * & root, const Comparable & x);
   void rotateWithLeftChild(FHs_treeNode<Comparable> * & k2);
   void rotateWithRightChild(FHs_treeNode<Comparable> * & k2);
};

// FHsplayTree method definitions -------------------
// public methods
template <class Comparable>
bool FHsplayTree<Comparable>::insert(const Comparable &x)
{
   if (this->mRoot == NULL)
   {
      this->mRoot = new FHs_treeNode<Comparable>(x, NULL, NULL);
      this->mSize++;
      return true;
   }

   splay(this->mRoot, x);
   if (x < this->mRoot->data)
   {
      FHs_treeNode<Comparable> *newNode;
      newNode = new FHs_treeNode<Comparable>(x, this->mRoot->lftChild,
         this->mRoot);
      this->mRoot->lftChild = NULL;
      this->mRoot = newNode;
      this->mSize++;
      return true;
   }
   else if (this->mRoot->data < x)
   {
      FHs_treeNode<Comparable> *newNode;
      newNode = new FHs_treeNode<Comparable>(x, this->mRoot,
         this->mRoot->rtChild);
      this->mRoot->rtChild = NULL;
      this->mRoot = newNode;
      this->mSize++;
      return true;
   }

   return false; // node with value x already exists
}

template <class Comparable>
bool FHsplayTree<Comparable>::remove(const Comparable &x)
{
   if (this->mRoot == NULL)
      return false;

   splay(this->mRoot, x);
   FHs_treeNode<Comparable> *newRoot;
   if (x < this->mRoot->data || this->mRoot->data < x)
      return false;
   if (this->mRoot->lftChild == NULL)
      newRoot = this->mRoot->rtChild;
   else
   {
      newRoot = this->mRoot->lftChild;
      splay(newRoot, x);
      newRoot->rtChild = this->mRoot->rtChild;
   }
   delete this->mRoot;
   this->mRoot = newRoot;
   this->mSize--;
   return true;
}

template <class Comparable>
bool FHsplayTree<Comparable>::contains(const Comparable &x)
{
   try
   {
      find(x);
   }
   catch (...)
   {
      return false;
   }
   return true;
}

template <class Comparable>
const Comparable &FHsplayTree<Comparable>::find(const Comparable &x)
{
   if (this->mRoot == NULL)
      throw typename FHsearch_tree<Comparable>::EmptyTreeException();
   splay(this->mRoot, x);
   if (x < this->mRoot->data || this->mRoot->data < x)
      throw typename FHsearch_tree<Comparable>::NotFoundException();
   return this->mRoot->data;
}

template <class Comparable>
const Comparable &FHsplayTree<Comparable>::showRoot()
{
   FHs_treeNode<Comparable> *root;
   root = this->mRoot;
   return (root == NULL) ? Comparable() : root->data;
}

// protected methods
template <class Comparable>
void FHsplayTree<Comparable>::splay(FHs_treeNode<Comparable> * & root,
   const Comparable & x)
{
   FHs_treeNode<Comparable> *rightTree, *leftTree, *rightTreeMin, *leftTreeMax;
   rightTree = NULL; leftTree = NULL; rightTreeMin = NULL; leftTreeMax = NULL;

   // top-down splay
   while (root != NULL)
   {
      if (x < root->data)
      {
         if (root->lftChild == NULL)
            break;
         if (x < root->lftChild->data)
         {
            rotateWithLeftChild(root);
            if (root->lftChild == NULL)
               break;
         }
         if (rightTree == NULL)
         {
            rightTree = root;
            rightTreeMin = root;
         }
         else
         {
            rightTreeMin->lftChild = root;
            rightTreeMin = root;
         }
         root = root->lftChild;
      }
      else if (root->data < x)
      {
         if (root->rtChild == NULL)
            break;
         if (root->rtChild->data < x)
         {
            rotateWithRightChild(root);
            if (root->rtChild == NULL)
               break;
         }
         if (leftTree == NULL)
         {
            leftTree = root;
            leftTreeMax = root;
         }
         else
         {
            leftTreeMax->rtChild = root;
            leftTreeMax = root;
         }
         root = root->rtChild;
      }
      else
         break;
   }

   //reassemble
   if (leftTree != NULL)
   {
      leftTreeMax->rtChild = root->lftChild;
      root->lftChild = leftTree;
   }
   if (rightTree != NULL)
   {
      rightTreeMin->lftChild = root->rtChild;
      root->rtChild = rightTree;
   }
}

template <class Comparable>
void FHsplayTree<Comparable>::rotateWithLeftChild
   (FHs_treeNode<Comparable> * & k2)
{
   FHs_treeNode<Comparable> *k1 = k2->lftChild;
   k2->lftChild = k1->rtChild;
   k1->rtChild = k2;
   k2 = k1;
}

template <class Comparable>
void FHsplayTree<Comparable>::rotateWithRightChild
   (FHs_treeNode<Comparable> * & k2)
{
   FHs_treeNode<Comparable> *k1 = k2->rtChild;
   k2->rtChild = k1->lftChild;
   k1->lftChild = k2;
   k2 = k1;
}

#endif