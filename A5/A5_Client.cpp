// Client / Splay Tree ----------------------------------------------

#include <iostream>
#include "FHsplayTree.h"
using namespace std;

template <typename Object>
class PrintObject
{
public:
   void operator()(Object obj)
   {
      cout << obj << " ";
   }
};

int main()
{
   int k;
   FHsplayTree<int> searchTree;
   //FHsearch_tree<int> searchTree;
   PrintObject<int> intPrinter;

   searchTree.traverse(intPrinter);
   //cout << searchTree.showRoot() << endl;

   cout << "Initial size: " << searchTree.size() << endl;
   for (k = 1; k <= 32; k++)
      searchTree.insert(k);
   cout << "New size: " << searchTree.size() << endl;

   cout << "\nTraversal: \n";
   searchTree.traverse(intPrinter);
   cout << endl << endl;

   for (k = -1; k < 10; k++)
   {
      // alt to find() - different error return
      cout << (searchTree.contains(k) ? "found\n" : "not found\n");
      try
      {
         //searchTree.find(k);
      }
      catch (...)
      {
         cout << " oops ";
      }
      cout << "splay " << k << " --> root: " << searchTree.showRoot()
         << " height: " << searchTree.showHeight() << endl;
   }

   return 0;
}

/* Assignment 5 Program Output:

The heights for both runs were either correct or off by -1 from the text.

------------------Run 1------------------
find() was used in the try block; essentially the main you provided

Initial size: 0
New size: 32

Traversal:
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
31 32

oops splay -1 --> root: 1 height: 16
oops splay 0 --> root: 1 height: 16
splay 1 --> root: 1 height: 16
splay 2 --> root: 2 height: 9
splay 3 --> root: 3 height: 6
splay 4 --> root: 4 height: 6
splay 5 --> root: 5 height: 5
splay 6 --> root: 6 height: 6
splay 7 --> root: 7 height: 6
splay 8 --> root: 8 height: 7
splay 9 --> root: 9 height: 8
Press any key to continue . . .

------------------Run 2------------------
contains() was used for this run

Initial size: 0
New size: 32

Traversal:
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
31 32

not found
splay -1 --> root: 1 height: 16
not found
splay 0 --> root: 1 height: 16
found
splay 1 --> root: 1 height: 16
found
splay 2 --> root: 2 height: 9
found
splay 3 --> root: 3 height: 6
found
splay 4 --> root: 4 height: 6
found
splay 5 --> root: 5 height: 5
found
splay 6 --> root: 6 height: 6
found
splay 7 --> root: 7 height: 6
found
splay 8 --> root: 8 height: 7
found
splay 9 --> root: 9 height: 8
Press any key to continue . . .

*/