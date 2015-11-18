#ifndef SPARSE_MAT_W_MULT_H
#define SPARSE_MAT_W_MULT_H

#include "FHsparseMat.h"
using namespace std;

template <class Object>
class SparseMatWMult : public SparseMat<double>
{
public:
   SparseMatWMult(int numRows, int numCols);
   bool matMult(SparseMatWMult<Object> & a, SparseMatWMult<Object> & b);
};

SparseMatWMult<double>::SparseMatWMult(int numRows, int numCols)
: SparseMat(numRows, numCols, 0)
{
}

bool SparseMatWMult<double>::matMult(SparseMatWMult<double> & a,
   SparseMatWMult<double> & b)
{
   if (a.getRowSize() < MIN_SIZE || a.getColSize() < MIN_SIZE ||
      b.getRowSize() < MIN_SIZE || b.getColSize() < MIN_SIZE ||
      a.getColSize() != b.getRowSize())
      return false;

   double newVal;
   MatRow::iterator iter, iterStart, iterEnd;
   MatRow *thisRow;

   clear();
   rowSize = a.getRowSize();
   colSize = b.getColSize();
   rows.resize(rowSize);

   for (int i = 0; i < rowSize; i++)
   {
      thisRow = &a.rows[i];
      iterStart = thisRow->begin();
      iterEnd = thisRow->end();
      for (int j = 0; j < colSize; j++)
      {
         newVal = 0;
         for (iter = iterStart; iter != iterEnd; iter++)
            newVal += (*iter).data * b.get((*iter).getCol(), j);
         set(i, j, newVal);
      }
   }

   return true;
}

#endif