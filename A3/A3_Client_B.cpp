#include <iostream>
#include <cstdlib>
#include <ctime>
#include "SparseMatWMult.h"
using namespace std;

#define MAT_SIZE 800
typedef SparseMatWMult<double> SpMat;

void setRandVals(SpMat & mat, int smallPer);

int main()
{
   int r, c, smallPercent;
   clock_t startTime, stopTime;
   double randFrac;

   // initialize sparse matricies, result is 10x10 on purpose to test if the
   // matMult() method correctly clear()'s and resize()'s correctly
      SpMat x(MAT_SIZE, MAT_SIZE), y(MAT_SIZE, MAT_SIZE), result(10, 10);
      SpMat n(5, 5), m(5, 5);
   
   // set values for testing matMult() method
   n.set(0, 0, 1);
   n.set(0, 1, 2);
   n.set(0, 2, 3);
   n.set(0, 3, 4);
   n.set(0, 4, 5);
   n.set(1, 0, -1);
   n.set(1, 1, -2);
   n.set(1, 2, -3);
   n.set(1, 3, -4);
   n.set(1, 4, -5);
   n.set(2, 0, 1);
   n.set(2, 1, 3);
   n.set(2, 2, 1);
   n.set(2, 3, 3);
   n.set(2, 4, 1);
   n.set(3, 0, 0);
   n.set(3, 1, 1);
   n.set(3, 2, 0);
   n.set(3, 3, 1);
   n.set(3, 4, 0);
   n.set(4, 0, -1);
   n.set(4, 1, -1);
   n.set(4, 2, -1);
   n.set(4, 3, -1);
   n.set(4, 4, -1);

   m.set(0, 0, 2);
   m.set(0, 1, 1);
   m.set(0, 2, 5);
   m.set(0, 3, 0);
   m.set(0, 4, 2);
   m.set(1, 0, 1);
   m.set(1, 1, 4);
   m.set(1, 2, 3);
   m.set(1, 3, 2);
   m.set(1, 4, 7);
   m.set(2, 0, 4);
   m.set(2, 1, 4);
   m.set(2, 2, 4);
   m.set(2, 3, 4);
   m.set(2, 4, 4);
   m.set(3, 0, 7);
   m.set(3, 1, 1);
   m.set(3, 2, -1);
   m.set(3, 3, -1);
   m.set(3, 4, -1);
   m.set(4, 0, 0);
   m.set(4, 1, 0);
   m.set(4, 2, 8);
   m.set(4, 3, -1);
   m.set(4, 4, -6);

   // multiplying matricies n x m as described in the spec
   cout << "Resultant matrix from multiplying n x m; where n and m are the"
      " matricies given in the A3 spec:" << endl;
   result.matMult(n, m);
   result.showSubSquare(0, 5);

   // generate small% non-default values between .1 and 1
   smallPercent = MAT_SIZE / 100. * MAT_SIZE; // div by 100. means 1%, of course
   srand(time(NULL));
   setRandVals(x, smallPercent);
   setRandVals(y, smallPercent);

   // 10x10 submatrix in lower right
   cout << "The following are the lower 10x10 corners of the two matricies that"
      << " were 1% randomly populated:" << endl;
   x.showSubSquare(MAT_SIZE - 10, 10);
   y.showSubSquare(MAT_SIZE - 10, 10);

   startTime = clock();  // ------------------ start
   result.matMult(x, y);
   stopTime = clock();  // ---------------------- stop

   cout << "Now the resultant matrix after multiplying:" << endl;
   result.showSubSquare(MAT_SIZE - 10, 10);
   cout << "\nSize = " << MAT_SIZE << " Sparse Mat Mult Elapsed Time: "
      << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
      << " seconds." << endl << endl;
}

void setRandVals(SpMat & mat, int smallPer)
{
   int i, j;
   for (int r = 0; r < smallPer; r++)
   {
      i = rand() % MAT_SIZE;
      j = rand() % MAT_SIZE;

      while (mat.get(i, j) != 0)
      {
         i = rand() % MAT_SIZE;
         j = rand() % MAT_SIZE;
      }
      mat.set(i, j) = float((rand() % 10) + 1) / 10;
   }
}

/* Assignment 3 Part B Questions & Program Output:

Runs 1 - 4 were done with the matrix at 1% populated.

------------------Run 1------------------
Resultant matrix from multiplying n x m; where n and m are the matricies given i
n the A3 spec:
44  25  59   7  -6
-44 -25 -59  -7   6
30  20  23   6  18
8   5   2   1   6
-14 -10 -19  -4  -6


The following are the lower 10x10 corners of the two matricies that were 1% rand
omly populated:
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0 0.4   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0


0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0


Now the resultant matrix after multiplying:
0   0 0.02   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0 0.3   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0 0.9   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0



Size = 400 Sparse Mat Mult Elapsed Time: 0.019 seconds.

Press any key to continue . . .


------------------Run 2------------------
Resultant matrix from multiplying n x m; where n and m are the matricies given i
n the A3 spec:
44  25  59   7  -6
-44 -25 -59  -7   6
30  20  23   6  18
8   5   2   1   6
-14 -10 -19  -4  -6


The following are the lower 10x10 corners of the two matricies that were 1% rand
omly populated:
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0 0.2   0   0   0   0   0   0   0


0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0 0.9   0   0
0   0   0   0   0   0   0   0   0   0


Now the resultant matrix after multiplying:
0   0   0   0   0   0   0   0 0.02   0
0   0   0 0.7 0.2   0   0 0.12   0 0.04
0.1   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0 0.18   0 0.06
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0



Size = 800 Sparse Mat Mult Elapsed Time: 0.29 seconds.

Press any key to continue . . .


------------------Run 3------------------
Resultant matrix from multiplying n x m; where n and m are the matricies given i
n the A3 spec:
44  25  59   7  -6
-44 -25 -59  -7   6
30  20  23   6  18
8   5   2   1   6
-14 -10 -19  -4  -6


The following are the lower 10x10 corners of the two matricies that were 1% rand
omly populated:
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0


0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0


Now the resultant matrix after multiplying:
0   0   0   0 0.21   0   0   0   0   0
0   0   0   0   0 0.12   0   0   0 0.2
0 0.7   0   0   0   0   0   0   0 0.35
0   0   0   0   0   0   0   0   0   0
0   0   0 0.04   0   0   0 0.03   0 0.03
0   0   0   0   0   0   0 0.6   0   0
0   0   0   0   0   0   0   0   0   0
0 0.3   0 0.18 0.34 0.24   0   0   0 0.3
0   0   0   0   0   0   0   0   0   0
0   0 0.15 0.42   0   0   0   0   0   0



Size = 1600 Sparse Mat Mult Elapsed Time: 7.5 seconds.

Press any key to continue . . .


------------------Run 4------------------
Resultant matrix from multiplying n x m; where n and m are the matricies given i
n the A3 spec:
44  25  59   7  -6
-44 -25 -59  -7   6
30  20  23   6  18
8   5   2   1   6
-14 -10 -19  -4  -6


The following are the lower 10x10 corners of the two matricies that were 1% rand
omly populated:
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0 0.3   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0


0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0


Now the resultant matrix after multiplying:
0 0.08 0.15   0 0.02   0   0 0.1   0   0
0.63   0   0   0   0 0.4   0   0   0   0
0   0 0.45   0   0   0   0   0   0   0
0   0   0   0 0.28 0.63 0.09   0 0.16 0.28
0 0.06   0   0   0   0 0.24 0.36   0   0
0   0   0   0   0   0   0   0   0   0
0   0 0.4 0.75   0 0.62   0 0.06   0   0
0   0   0   0   0   0 0.45 1.5   0   0
0   0 0.27   0   0   0   0   0   0   0
0   0   0   0   0 0.9 0.35   0   0   0



Size = 3200 Sparse Mat Mult Elapsed Time: 1.8e+002 seconds.

Press any key to continue . . .


------------------Answers to Questions------------------
   Time Complexity:
   The clear() method would have time complextiy N for a standard mat size of N,
   but since it's not the highest order we will disregard it.  The resize() call
   also has linear time complexity.
   The innermost for loop has a call to get() (which has a call to valid();
   valid() has constant time complextiy) and get() has a maximum time complextiy
   of a fraction of N based on the sparsity of the matrix - say 0.01N given 1%
   sparsity.  The innermost for loop itself has the same 0.01N time complexity.
   The middle for loop has a call to set() which again has 0.01N time
   complexity, and the loop itself has N time complexity.  The first loop has
   linear time complexity N.
   So now we have N*N*0.01N*0.01N*0.01N = 0.0000001(N^5).
   However, in practice the results show otherwise.  When considering very
   sparse matricies, I think this algorithm exhibits O(N^3) time complexity.
   Assuming a constant sparsity, Omega would be the same since the same # of
   operations occur.  So in the end we again have Theta(N^3) time complexity.

1. Are the times longer or shorter than for dynamic matrices?
   Comparing runs that were done with matricies 5% populated, the sparse matrix
   algorithm always took longer.  0.024s vs 0.01s for size 200x200, 2s vs 0.23s
   for size 500x500, and 37s vs 10s for size 1000x1000; sparse vs dynamic
   timings respectively.
   However, for size 3200x3200 vs 3000x3000 for sparse vs dynamic, the sparse
   matrix actually runs at a brisk 3 min as opposed to 7.83 min.  This leads
   me to suspect that for larger and larger values for matrix sizes, the sparse
   matrix multiplication runs quicker (as we would expect since less data and
   therefore less computation overall for the sparse mult, whereas the dynamic
   stays rigid in its ever increasing times)

2. Are the growth rates larger or smaller?  By how much?
   N = 200, 400:
      N = 200 took 0.002 sec, so we would expect N = 400 to take
      8*0.002 = 0.016 sec.  Instead we get 0.018 sec which is close.
   N = 400, 800:
      N = 400 took 0.018 sec, so we would expect N = 800 to take
      8*0.018 = 0.144 sec.  Instead we get 0.27 sec = 1.88 * 0.144 sec.
   N = 800, 1600:
      N = 800 took 0.27 sec, so we would expect N = 1600 to take
      8*0.27 = 2.16 sec.  Instead we get 7.8 sec = 3.61 * 2.16 sec.
   N = 1600, 3200:
      N = 1600 took 7.8 sec, so we would expect N = 3200 to take
      8*7.8 = 62.4 sec.  Instead we get 180 sec = 2.88 * 62.4 sec.

   These growth rates are larger than those of the dynamic mat mult method by
   a factor of about 2, but the growth rates seem to be declining as the mat
   size grows larger.  Also these results seem in line with Theta(N^3) estimates.

3. Create a table and answer the same questions as before.
   M Value  |  Time (seconds)
   --------------------------
   100      |     0
   200      |     0.002
   400      |     0.018
   800      |     0.27
   1600     |     7.8
   3200     |     180 (3 min)

   All runs were done with the matrix at 1% populated.

4. What was the largest M you could use here, and was the reason the same or
   different than for dynamic arrays?
   At M = 10000000 the program crashes due to memory overload; at 5000000 the
   program doesn't give in but it takes way too long to actually let it run
   through its paces.  This was tested at 5% populated.
   This maximum number is much much larger than the corresponding max for
   dynamic matrix multiplication, and it makes sense because we only have 1
   MasterCol vector and each value is added as neccessary as an individual
   node to the list (this is the point of sparse matricies).

5. If you have time, modify 1% to be .5% or .1% or even less and see if the
   growth rates change.

   The following runs were done with a matrix size of 400x400; with two more
   runs at 800x800 and 1600x1600 for 0.1%.

   Sparsity |  Time (seconds)
   --------------------------
   0.1%     |     0.002      -> M = 800::0.012s, M = 1600::0.077s
   0.5%     |     0.007
   1%       |     0.019
   5%       |     0.72
   10%      |     3.1

   For sparsity 0.1%, the growth rate was actually less than cubic.

*/