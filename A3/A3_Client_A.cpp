#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

#define MAT_SIZE 500
typedef float* DynMat[MAT_SIZE];

void matMultDyn(const DynMat & matA, const DynMat & matB,
   DynMat & matC, int size);

void matShowDyn(const DynMat & matA, int start, int size);

int main()
{
   int r, c;
   clock_t startTime, stopTime;
   int randRow, randCol, smallPercent;

   // non-sparse dynamic matrix
   DynMat matDyn, matDynAns;

   // allocate rows and initialize to 0
   for (r = 0; r < MAT_SIZE; r++)
   {
      matDyn[r] = new float[MAT_SIZE];
      matDynAns[r] = new float[MAT_SIZE];
      for (c = 0; c < MAT_SIZE; c++)
      {
         matDyn[r][c] = 0;
         matDynAns[r][c] = 0;
      }
   }

   // generate small% non-default values between .1 and 1
   smallPercent = MAT_SIZE/20. * MAT_SIZE;  // div by 20. means 5%, of course
   for (r = 0; r < smallPercent; r++)
   {
      srand(time(NULL));
      randRow = rand() % MAT_SIZE;
      randCol = rand() % MAT_SIZE;

      while (matDyn[randRow][randCol] != 0)
      {
         randRow = rand() % MAT_SIZE;
         randCol = rand() % MAT_SIZE;
      }
      matDyn[randRow][randCol] = float((rand() % 10) + 1) / 10;
   }

   // 10x10 submatrix in lower right
   matShowDyn(matDyn, MAT_SIZE - 10, 10);

   startTime = clock();  // ------------------ start
   matMultDyn(matDyn, matDyn, matDynAns, MAT_SIZE);
   stopTime = clock();  // ---------------------- stop

   matShowDyn(matDynAns, MAT_SIZE - 10, 10);
   cout << "\nSize = " << MAT_SIZE << " Dyn Array Mult Elapsed Time: "
      << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
      << " seconds." << endl << endl;

   // clean up
   for (r = 0; r < MAT_SIZE; r++)
   {
      delete[] matDyn[r];
      delete[] matDynAns[r];
   }

   cout << endl;

   return 0;
}

void matMultDyn(const DynMat & matA, const DynMat & matB,
   DynMat & matC, int size)
{
   float newVal;
   int i, j, k;
   for (i = 0; i < size; i++)
   {
      for (j = 0; j < size; j++)
      {
         newVal = 0;
         for (k = 0; k < size; k++)
            newVal += matA[i][k] * matB[k][j];
         matC[i][j] = newVal;
      }
   }
}

void matShowDyn(const DynMat & matA, int start, int size)
{
   if (start < 0 || size < 0 || start + size > MAT_SIZE)
      return;
   
   for (int i = start; i < (start + size); i++)
   {
      for (int j = start; j < (start + size); j++)
      {
         cout.width(4);
         cout.precision(2);
         cout << matA[i][j] << " ";
      }
      cout << endl;
   }
   cout << endl << endl;
}

/* Assignment 3 Part A Questions & Program Output:

   Runs 1 - 4 were done with the matrix at 5% populated.

   Given the same MAT_SIZE, runs with varying sparsities had the same run time
   since the same # of calculations occur regardless of how many values are
   non-0 (run 5 demonstrates this).

------------------Run 1------------------
0    0    0    0    0    0    0    0    0    0
0    0    0    0    0    0    0    0    0    0
0    0    0    0  0.1    0    0    0    0    0
0    0    0  0.2    0  0.2    0    0    0    0
0    0    0    0    0    0    0    0    0    0
0    0    0    0    0  0.4    0    0    0    0
0    0    0    0    0    0    0    0    0    0
0    0    0    0    0    0    0    0    0    0
0    0    0    0    0    0    0    0    0    0
0    0    0    0    0    0    0    0    0    0


0    0    0    0    0 0.45    0    0    0    0
0  0.7    0    0    0    0    0    0    0    0
0    0    0    0    0    0    0 0.15    0    0
0.18    0    0 0.04    0 0.12    0    0 0.16    0
0    0    0    0    0    0    0    0 0.28    0
0    0    0    0    0 0.16    0    0    0    0
0    0    0    0    0    0    0    0    0    0
0    0    0    0  0.3    0    0    0    0    0
0    0    0    0    0    0    0    0    0    0
0    0    0    0    0    0    0    0    0    0



Size = 50 Dyn Array Mult Elapsed Time: 0 seconds.


Press any key to continue . . .


------------------Run 2------------------
0    0    0    0    0    0    0    0    0    0
0    0    0    0    0    0    0    0  0.7    0
0    0    0    0    0    0    0    0  0.4    0
0    0  0.6    0    0    0    0    0    0    0
0    0    0    0    0    0    0    0    0    0
0    0    0    0    0    0    0    0    0    0
0    0    0    0    0    0    0    0    0    0
0    0    0    0    0    0    0    0    0    0
0    0    0    0    0    0    0    0    0    0
0    0    0    0  0.6    0    0    0    0  0.2


0    0    0    0    0    0    0    0    0 0.42
0    0    0    0    0    0 0.28    0    0    0
0    0    0    0    0    0    0    0    0    0
0  0.4    0    0    0    0 0.14    0 0.42    0
0    0    0    0    0    0    0    0    0  0.6
0    0 0.18    0    0    0    0    0    0    0
0    0    0    0    0    0    0    0    0    0
0  0.1    0    0    0    0 0.72 0.25    0    0
1.1    0    0 0.18    0    0    0    0    0    0
0.04    0    0  0.4 0.12    0    0 0.32    0 0.04



Size = 100 Dyn Array Mult Elapsed Time: 0.001 seconds.


Press any key to continue . . .


------------------Run 3------------------
0    0    0    0  0.4    0    0  0.7    0    0
0    0    0    0    0    0    0    0    0    0
0    0    0    0    0    0    0    0    0    0
0    0    0    0    0    0    0    0    0    0
0    0    0    0    0    0    0    0    0    1
0    0  0.6    0    0    0    0    0  0.3    0
0    0    0    0    0  0.9    0    0    0    0
0    0    0    0    0    0    0    0    0    0
0    0  0.3    0    0    0    0    0    0    0
0    0    0    0    0    0    0    0    0    0


0 0.07  0.5    0    0    0    0    0 0.24 0.72
0    0    0    0    0 0.42    0    0 0.54 0.03
0 0.98    0 0.72    0    0    0    0    0  0.7
0 0.24  0.4    0 0.27    0    0    0    0    0
1    0    0    0    0    0    0 0.49    0  0.8
0    0 0.13    0 0.36    0    0    0 0.05 0.74
0 0.08 0.54    0    0    0    0    0 0.27    0
0 0.48  0.5    0 0.54    0 0.74 0.42    0    0
0    0    0    0    0    0    0    0    0    0
0    0    0    0    0    0    0    0    0    0



Size = 200 Dyn Array Mult Elapsed Time: 0.01 seconds.


Press any key to continue . . .


------------------Run 4------------------
0    0  0.8    0    0    0    0    0    0    0
0    0    0    0    0    0    0    0    0    0
0    0    0    0    0    0    0    0    0    0
0    0    0    0    0    0    0    0    0    0
0    0    0    0    0  0.1    0    0    0    0
0    0    0    0    0    0    0    0    0  0.8
0    0    0    0    0    0    0  0.2    0    0
0    0    0    0    0    0    0    0    0    0
0    0    0    0    0    0    0    0    0    0
0    0    0  0.9    0    0    0    0    0    0


0 0.09    0    0 0.52 0.07 0.49    0 0.09 0.16
0.14 0.58    0 0.04  1.8 0.96    0 0.39    0 0.42
0.12  0.3 0.38  1.1  0.5  0.8    0  0.2 0.18 0.45
0 0.45    0  0.3 0.63 0.79 0.15 0.57  0.2  1.2
0.28  0.4 0.56 0.06 0.25 0.51 0.44 0.04 0.45  0.1
0.72 0.46  0.6 0.95 0.04  1.5    0    1 0.16 0.46
0.06 0.54 0.15 0.66    1  0.2    0 0.24 0.26    0
0  0.3  0.1 0.08 0.14 0.39    0    0    0  0.3
0 0.24 0.17    0 0.42 0.05 0.12 0.24    0  0.1
0.66 0.98 0.35 0.44 0.81  1.4 0.72    0  0.4 0.94



Size = 500 Dyn Array Mult Elapsed Time: 0.22 seconds.


Press any key to continue . . .


   The following run was done with the matrix at 10% populated.
------------------Run 5------------------
0    0    0    1    0    0    0    0    0    0
0    0    0    0    0    0  0.9    0    0    0
0.2    0    0    0    0    0  0.2    0    0    0
0    0    0    0  0.5    0    0    0    0    0
0    0    0    0    0    0    0    0    0    0
0    0  0.9    0    0    0  0.4    0  0.9    0
0    0    0    0    0    0    0    0    0    0
0    0    0    0    0    0    0    0    0    0
0    0    0    0    0    0    0    0    0    0
0    0    0    0  0.2    0    0    0    0    0


2.3 0.98  1.6    0  2.9  2.6  1.3 0.99  1.8  1.1
0.34  1.7  0.9 0.61 0.51 0.94 0.38    1    1 0.65
2.1  1.4  1.6 0.71  1.8  1.2  1.3 0.88  1.8  1.2
2.9  3.5  1.4  2.5  2.1  2.9  2.6  3.5  1.6  2.7
2.1 0.84 0.72  0.9  1.8  1.5    2 0.45 0.24 0.83
1.1 0.27  2.4  0.3  1.2 0.27 0.81 0.53 0.55 0.98
1.3  2.6 0.32  1.2  1.8 0.42 0.96 0.33  2.6  1.6
2.8  2.2  1.5  0.8  2.7  1.3 0.64  2.2  2.6  2.4
2.2  2.5  1.4  1.8  3.3 0.49  1.4 0.99 0.49  2.2
3.2  1.3 0.39  2.1  1.7 0.38  2.1  1.8    1 0.73



Size = 500 Dyn Array Mult Elapsed Time: 0.24 seconds.


Press any key to continue . . .


------------------Answers to Questions------------------
   Time Complexity:
   The matrix multiplication algorithm is O(N^3).  It contains 3 for loops that
   loop from 0 to N - 1, where N = MAT_SIZE.  Every operation is either a
   single calculation or an assignment, so these contribute constant time and
   do not contribute to Big O.  The algorithm is also Theta(N^3) because there
   is no variation in the length of the 3 for loops; they all run N times each.
   This implies that the minimum time complexity is equivalent to the maximum
   time complexity: Big O = Omega = Theta.

1. What was the smallest M that gave you a non-zero time?
   MAT_SIZE = 75 ran in 0.001s (sometimes the run showed 0, sometimes 0.001)

2. What happened when you doubled M , tripled it, quadrupled it, etc?  Give
   several M values and their times in a table.
   M Value  |  Time (seconds)
   --------------------------
   50       |     0
   100      |     0.002
   200      |     0.01
   500      |     0.23
   1000     |     10
   1500     |     42
   2000     |     120 (2 min)
   3000     |     470 (7.83 min)
   4000     |     1200 (20 min)

   All runs were done with the matrix at 5% populated.

3. How large an M can you use before the program refuses to run (exception
   or run-time error due to memory overload) or it takes so long you can't wait
   for the run?
   At M = 16000 the program crashes due to memory overload; at 15000 the program
   runs but it takes much too long to actually let it run through its paces.

4. How did the data agree or disagree with your original time complexity
   estimate?
   N = 500, 1000:
      N = 500 took 0.23 sec, so we would expect N = 1000 to take
      8*0.23 = 1.84 sec.  Instead we get 10 sec = 5.43 * 1.84 sec.
   N = 1000, 2000:
      N = 1000 took 10 sec, so we would expect N = 2000 to take
      8*10 = 80 sec.  Instead we get 120 sec = 1.50 * 80 sec.
   N = 1500, 3000:
      N = 1500 took 42 sec, so we would expect N = 3000 to take
      8*42 = 336 sec.  Instead we get 470 sec = 1.40 * 336 sec.
   N = 2000, 4000:
      N = 2000 took 120 sec, so we would expect N = 4000 to take
      8*120 = 960 sec.  Instead we get 1200 sec = 1.25 * 960 sec.

   From these 4 sets of N values, we can see that as N grows larger the time
   increases by a factor of 2^3 times some constant.  But since that constant
   is decreasing I think it's safe to assume that the long term behavior of
   this algorithm has a time complexity of Theta(N^3).
*/