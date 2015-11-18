// File FHlazySearchTree.h
// Template definitions for FHlazySearchTrees, which are general trees
#ifndef FHLAZYSEARCHTREE_H
#define FHLAZYSEARCHTREE_H

// ---------------------- FHlazySearchTreeNode Prototype ----------------------
template <class Comparable>
class FHlazySearchTreeNode
{
public:
   FHlazySearchTreeNode( const Comparable & d = Comparable(), 
      FHlazySearchTreeNode *lt = NULL, 
      FHlazySearchTreeNode *rt = NULL,
      bool isDel = false)
      : lftChild(lt), rtChild(rt), data(d), deleted(isDel)
   { }

   FHlazySearchTreeNode *lftChild, *rtChild;
   Comparable data;
   bool deleted;

   // for use only with AVL Trees
   virtual int getHeight() const { return 0; }
   virtual bool setHeight(int height) { return true; }
}; 

// ---------------------- FHlazySearchTree Prototype --------------------------
template <class Comparable>
class FHlazySearchTree
{
protected:
   int mSize;
   int mSizeHard;
   FHlazySearchTreeNode<Comparable> *mRoot;

public:
   FHlazySearchTree() { mSize = 0; mRoot = NULL; }
   FHlazySearchTree(const FHlazySearchTree &rhs) 
      { mRoot = NULL; mSize = 0; *this = rhs; }
   ~FHlazySearchTree() { clear(); }

   const Comparable &findMin() const; // revised
   const Comparable &findMax() const; // revised
   const Comparable &find(const Comparable &x) const; // revised

   bool empty() const { return (mSize == 0); }
   int size() const { return mSize; }
   int sizeHard() const { return mSizeHard; }
   void clear() { makeEmpty(mRoot); }
   void collectGarbage();
   const FHlazySearchTree & operator=(const FHlazySearchTree &rhs); // revised

   bool insert(const Comparable &x); // revised
   bool remove(const Comparable &x); // revised
   bool contains(const Comparable &x) const { return find(mRoot, x) != NULL; }

   template <class Processor>
   void traverse(Processor func) const { traverse(mRoot, func); } // revised
   int showHeight() const { return findHeight(mRoot); }

protected:
   FHlazySearchTreeNode<Comparable> *clone( 
      FHlazySearchTreeNode<Comparable> *root) const; // revised
   FHlazySearchTreeNode<Comparable> *findMin(
      FHlazySearchTreeNode<Comparable> *root) const; // revised
   FHlazySearchTreeNode<Comparable> *findMax(
      FHlazySearchTreeNode<Comparable> *root) const; // revised
   FHlazySearchTreeNode<Comparable> *find(
      FHlazySearchTreeNode<Comparable> *root,
      const Comparable &x) const; // revised
   FHlazySearchTreeNode<Comparable> *findMinHard(
      FHlazySearchTreeNode<Comparable> *root) const;
   bool insert(FHlazySearchTreeNode<Comparable> * &root,
      const Comparable &x); // revised
   bool remove(FHlazySearchTreeNode<Comparable> * &root, const Comparable &x);
      // revised
   bool removeHard(FHlazySearchTreeNode<Comparable> * &root,
      const Comparable &x); // revised
   void collectGarbage(FHlazySearchTreeNode<Comparable> * &root);
   void makeEmpty(FHlazySearchTreeNode<Comparable> * &subtreeToDelete);
      // revised
   template <class Processor>
   void traverse(FHlazySearchTreeNode<Comparable> *treeNode, 
      Processor func, int level = -1) const; // revised
   int findHeight(FHlazySearchTreeNode<Comparable> *treeNode,
      int height = -1) const;
   
public:
   // for exception throwing
   class EmptyTreeException {};
   class NotFoundException {};
};

// FHlazySearchTree public method definitions -----------------------------
template <class Comparable>
const Comparable & FHlazySearchTree<Comparable>::findMin() const
{
   FHlazySearchTreeNode<Comparable> *temp;
   if (mRoot == NULL)
      throw EmptyTreeException();
   
   temp = findMin(mRoot);
   if (temp == NULL)
      throw EmptyTreeException();
   else
      return temp->data;
}

template <class Comparable>
const Comparable & FHlazySearchTree<Comparable>::findMax() const
{
   FHlazySearchTreeNode<Comparable> *temp;
   if (mRoot == NULL)
      throw EmptyTreeException();

   temp = findMax(mRoot);
   if (temp == NULL)
      throw EmptyTreeException();
   else
      return temp->data;
}

template <class Comparable>
const Comparable &FHlazySearchTree<Comparable>::find(
   const Comparable &x) const
{ 
   FHlazySearchTreeNode<Comparable> *resultNode;
   
   resultNode = find(mRoot, x);
   if (resultNode == NULL)
      throw NotFoundException();
   return resultNode->data;
}

template <class Comparable>
void FHlazySearchTree<Comparable>::collectGarbage()
{
   collectGarbage(mRoot);
   mSizeHard = mSize;
}

template <class Comparable>
const FHlazySearchTree<Comparable> &FHlazySearchTree<Comparable>::operator=
   (const FHlazySearchTree &rhs)
{
   if (&rhs != this) 
   {
      clear();
      mRoot = clone(rhs.mRoot);
      mSize = rhs.size();
      mSizeHard = rhs.sizeHard();
   }
   return *this;
}

template <class Comparable>
bool FHlazySearchTree<Comparable>::insert(const Comparable &x)
{
   if (insert(mRoot, x))
   {
      mSize++;
      return true;
   }
   return false;
}

template <class Comparable>
bool FHlazySearchTree<Comparable>::remove(const Comparable &x)
{
   if (remove(mRoot, x))
   {
      mSize--;
      return true;
   }
   return false;
}

template <class Comparable>
template <class Processor>
void FHlazySearchTree<Comparable>::traverse(
   FHlazySearchTreeNode<Comparable> *treeNode,
   Processor func, int level) const
{
   if (treeNode == NULL)
      return;
   // we're not doing anything with level but its there in case we want it
   traverse(treeNode->lftChild, func, level + 1);
   if (!(treeNode->deleted))
      func(treeNode->data);
   traverse(treeNode->rtChild, func, level + 1);
}


// FHlazySearchTree private method definitions -----------------------------
template <class Comparable>
FHlazySearchTreeNode<Comparable> *FHlazySearchTree<Comparable>::clone(
   FHlazySearchTreeNode<Comparable> *root) const
{
   FHlazySearchTreeNode<Comparable> *newNode;
   if (root == NULL)
      return NULL;

   newNode =  new FHlazySearchTreeNode<Comparable>(root->data,
      clone(root->lftChild), clone(root->rtChild), root->deleted);
   return newNode;
}

template <class Comparable>
FHlazySearchTreeNode<Comparable> *FHlazySearchTree<Comparable>::findMin(
   FHlazySearchTreeNode<Comparable> *root) const
{
   FHlazySearchTreeNode<Comparable> *temp;
   if (root == NULL)
      return NULL;
   else if (root->lftChild == NULL)
   {
      if (root->deleted)
         return findMin(root->rtChild);
      else
         return root;
   }
   else
   {
      temp = findMin(root->lftChild);
      if (temp != NULL)
         return temp;
      else if (root->deleted)
         return findMin(root->rtChild);
      else
         return root;
   }
}

template <class Comparable>
FHlazySearchTreeNode<Comparable> *FHlazySearchTree<Comparable>::findMax(
   FHlazySearchTreeNode<Comparable> *root) const
{
   FHlazySearchTreeNode<Comparable> *temp;
   if (root == NULL)
      return NULL;
   else if (root->rtChild == NULL)
   {
      if (root->deleted)
         return findMax(root->lftChild);
      else
         return root;
   }
   else
   {
      temp = findMax(root->rtChild);
      if (temp != NULL)
         return temp;
      else if (root->deleted)
         return findMax(root->lftChild);
      else
         return root;
   }
}

template <class Comparable>
FHlazySearchTreeNode<Comparable>* FHlazySearchTree<Comparable>::find(
   FHlazySearchTreeNode<Comparable> *root, const Comparable &x) const
{
   if (root == NULL)
      return NULL;

   if (x < root->data)
      return find(root->lftChild, x);
   if (root->data < x)
      return find(root->rtChild, x);

   if (root->deleted)
      return NULL;
   else
      return root;
}

template <class Comparable>
FHlazySearchTreeNode<Comparable> *FHlazySearchTree<Comparable>::findMinHard(
   FHlazySearchTreeNode<Comparable> *root) const
{
   if (root == NULL)
      return NULL;
   if (root->lftChild == NULL)
      return root;
   return findMinHard(root->lftChild);
}

template <class Comparable>
bool FHlazySearchTree<Comparable>::insert(
   FHlazySearchTreeNode<Comparable> * &root, const Comparable &x)
{
   if (root == NULL)
   {
      root = new FHlazySearchTreeNode<Comparable>(x, NULL, NULL, false);
      mSizeHard++;
      return true;
   }
   else if (x < root->data)
      return insert(root->lftChild, x);
   else if (root->data < x)
      return insert(root->rtChild, x);
   else if (root->deleted)
   {
      root->deleted = false;
      return true;
   }

   return false; // true duplicate
}

template <class Comparable>
bool FHlazySearchTree<Comparable>::remove(
   FHlazySearchTreeNode<Comparable> * &root, const Comparable &x)
{
   if (root == NULL)
      return false;

   if (x < root->data)
      return remove(root->lftChild, x);
   if (root->data < x)
      return remove(root->rtChild, x);

   // found the node
   if (root->deleted)
      return false;
   else
   {
      root->deleted = true;
      return true;
   }
}

template <class Comparable>
bool FHlazySearchTree<Comparable>::removeHard(
   FHlazySearchTreeNode<Comparable> * &root, const Comparable &x)
{
   if (root == NULL)
      return false;

   if (x < root->data)
      return removeHard(root->lftChild, x);
   if (root->data < x)
      return removeHard(root->rtChild, x);

   // found the node
   if (root->lftChild != NULL && root->rtChild != NULL)
   {
      FHlazySearchTreeNode<Comparable> *minNode = findMinHard(root->rtChild);
      root->data = minNode->data;
      root->deleted = minNode->deleted;
      removeHard(root->rtChild, minNode->data);
   }
   else
   {
      FHlazySearchTreeNode<Comparable> *nodeToRemove = root;
      root = (root->lftChild != NULL)? root->lftChild : root->rtChild;
      delete nodeToRemove;
   }
   return true;
}

template <class Comparable>
void FHlazySearchTree<Comparable>::collectGarbage(
   FHlazySearchTreeNode<Comparable> * &root)
{
   bool cleanSubtree;
   if (root == NULL)
      return;

   collectGarbage(root->lftChild);
   cleanSubtree = root->deleted;
   while (cleanSubtree)
   {
      removeHard(root, root->data);
      if (root == NULL)
         cleanSubtree = false;
      else
         cleanSubtree = root->deleted;
   }
   if (root == NULL)
      return;
   else
      collectGarbage(root->rtChild);
}

template <class Comparable>
void FHlazySearchTree<Comparable>::makeEmpty(
   FHlazySearchTreeNode<Comparable> * &subtreeToDelete)
{
   if (subtreeToDelete == NULL)
      return;

   // remove children
   makeEmpty(subtreeToDelete->lftChild);
   makeEmpty(subtreeToDelete->rtChild);

   // clear client's pointer
   if (!(subtreeToDelete->deleted))
      --mSize;
   delete subtreeToDelete;
   subtreeToDelete = NULL;
   --mSizeHard;
}

template <class Comparable>
int FHlazySearchTree<Comparable>::findHeight(
   FHlazySearchTreeNode<Comparable> *treeNode,
   int height ) const
{
   int leftHeight, rightHeight;

   if (treeNode == NULL)
      return height;
   height++;
   leftHeight = findHeight(treeNode->lftChild, height);
   rightHeight = findHeight(treeNode->rtChild, height);
   return (leftHeight > rightHeight)? leftHeight : rightHeight;
}
#endif