#include <iostream>
#include <cassert> // for assert() in constructor
#include "FHlist.h"
#include "FHvector.h"
using namespace std;

template <class Object>
class MatNode
{
protected:
   int col;

public:
   Object data;
   // we need a default constructor for lists
   MatNode(int cl = 0, Object dt = Object()) : col(cl), data(dt) {}
   int getCol() const { return col; }

   // not optimized yet for set() = defaultVal;  refer to forums
   const Object & operator=(const Object &x) { return (data = x); }
};

// SparseMat class declarations -------------------
template <class Object>
class SparseMat
{
protected:
   typedef FHlist< MatNode<Object> > MatRow;
   typedef FHvector<MatRow> MasterCol;

   MasterCol rows;
   Object defaultValue;
   int rowSize, colSize;
public:
   SparseMat(int r, int c, const Object & defaultVal);
   const Object & get(int r, int c) const;
   bool set(int r, int c, const Object &x);
   void clear();
   void showSubSquare(int start, int size);
};

#define MAT_SIZE 100000
typedef SparseMat<float> SpMat;

// Client program to test SparseMat -------------------
int  main()
{
   SpMat mat(MAT_SIZE, MAT_SIZE, 0); // 100000 x 100000 filled with 0

   cout << "Testing set() with various combinations..." << endl;
   mat.set(2, 5, 10);
   mat.set(2, 5, 35);   // should overwrite the 10
   mat.set(3, 9, 21);
   mat.set(MAT_SIZE, 1, 5);  // should fail silently
   mat.set(9, 9, mat.get(3, 9));  // should copy the 21 here
   mat.set(4, 4, -9);
   mat.set(4, 4, 0);   // should remove the -9 node entirely
   mat.set(MAT_SIZE - 1, MAT_SIZE - 1, 99);

   // test accessors and exceptions
   cout << "\nTesting get() - try block should work for the first "
      << "three, then throw an excep- tion for the last one:" << endl;
   try
   {
      cout << mat.get(7, 8) << endl;
      cout << mat.get(2, 5) << endl;
      cout << mat.get(9, 9) << endl;
      cout << mat.get(-4, 7) << endl;  // should throw an exception
   }
   catch (...)
   {
      cout << "oops" << endl;
   }

   // show top left 15x15
   cout << "\nTop left 15x15 sub-square:" << endl;
   mat.showSubSquare(0, 15);

   // show middle 15x15
   cout << "\nRandom middle null 15x15 sub-square:" << endl;
   mat.showSubSquare(50000, 15);

   // show bottom right 15x15
   cout << "\nBottom left 15x15 sub-square:" << endl;
   mat.showSubSquare(MAT_SIZE - 15, 15);

   // test clear()
   cout << "\nPreviously non-0 values after clearing matrix:" << endl;
   mat.clear();
   cout << mat.get(2, 5) << endl;
   cout << mat.get(3, 9) << endl;
   cout << mat.get(9, 9) << endl;

   return 0;
}

// SparseMat method definitions -------------------
template <class Object>
SparseMat<Object>::SparseMat(int r, int c, const Object & defaultVal)
{
   // No requirement for exception in the spec, so I used assert() instead.
   assert(r >= 1 && c >= 1);
   rowSize = r;
   colSize = c;
   defaultValue = defaultVal;
   for (int i = 0; i < colSize; i++)
      rows.push_back(MatRow());
}

template <class Object>
const Object & SparseMat<Object>::get(int r, int c) const
{
   if (r < 0 || c < 0 || r >(colSize - 1) || c >(rowSize - 1))
      throw MasterCol::OutOfBoundsException();

   MatRow::const_iterator iter;
   MatRow::const_iterator end = rows[r].end();
   for (iter = rows[r].begin(); iter != end; iter++)
      if (c == (*iter).getCol())
         return (*iter).data;

   return defaultValue;
}

template <class Object>
bool SparseMat<Object>::set(int r, int c, const Object &x)
{
   if (r < 0 || c < 0 || r >(colSize - 1) || c >(rowSize - 1))
      return false;

   MatRow::iterator iter;
   MatRow::iterator end = rows[r].end();
   for (iter = rows[r].begin(); iter != end; iter++)
   {
      if (c == (*iter).getCol())
      {
         if (x == defaultValue)
            rows[r].erase(iter);
         else
            (*iter).data = x;

         return true;
         // The way I've written this, I don't think break; is needed
         // since as soon as a matching column is found, the method 
         // immediately returns true after the if/else.
      }
   }

   MatNode<Object> newNode(c, x);
   rows[r].push_back(newNode);
   return true;
}

template <class Object>
void SparseMat<Object>::clear()
{
   for (int i = 0; i < rowSize; i++)
      rows[i].clear();
}

template <class Object>
void SparseMat<Object>::showSubSquare(int start, int size)
{
   for (int i = start; i < (start + size); i++)
   {
      for (int j = start; j < (start +size); j++)
      {
         cout.width(2);
         cout << get(i, j) << " ";
      }
      cout << endl;
   }
}

/*Program Output:
------------------Single Run------------------
Testing set() with various combinations...

Testing get() - try block should work for the first three, then throw an excep-
tion for the last one:
0
35
21
oops

Top left 15x15 sub-square:
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0 35  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0 21  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0 21  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0

Random middle null 15x15 sub-square:
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0

Bottom left 15x15 sub-square:
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0 99

Previously non-0 values after clearing matrix:
0
0
0
Press any key to continue . . .
*/