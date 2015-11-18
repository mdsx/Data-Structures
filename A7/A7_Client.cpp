#include <iostream>
#include <ctime> // for timing algorithms
#include <cmath> // for pow() and ceil() used to calculate gaps
#include <cstdlib> // for rand()
#include "FHvector.h"
using namespace std;

#define ARRAY_SIZE 255000

// shellsort1 array version -- for sorting the Sedgewick gap array
template <typename Comparable>
void shellSort1(Comparable array[], int arraySize)
{
   int k, pos, gap;
   Comparable tmp;

   for (gap = arraySize / 2; gap > 0; gap /= 2)
      for (pos = gap; pos < arraySize; pos++)
      {
         tmp = array[pos];
         for (k = pos; k >= gap && tmp < array[k - gap]; k -= gap)
            array[k] = array[k - gap];
         array[k] = tmp;
      }
}

// shellSort1 -- using shell's outer loop
template <typename Comparable>
void shellSort1(FHvector<Comparable> & a)
{
   int k, pos, arraySize, gap;
   Comparable tmp;

   arraySize = a.size();
   for (gap = arraySize / 2; gap > 0; gap /= 2)  // outer gap loop
      for (pos = gap; pos < arraySize; pos++)   // middle loop
      {
         tmp = a[pos];
         for (k = pos; k >= gap && tmp < a[k - gap]; k -= gap) // inner loop
            a[k] = a[k - gap];
         a[k] = tmp;
      }
}

// shellSortX -- takes an explicit gap sequence
template <typename Comparable>
void shellSortX(FHvector<Comparable> & a, Comparable gapSequence[],
   int gapSeqSize)
{
   int i, k, pos, arraySize, gap;
   Comparable tmp;

   arraySize = a.size();
   for (i = 0; gapSequence[i] <= arraySize / 2; i++)
      gap = gapSequence[i];

   for (gap; gap > 0; gap = gapSequence[--i])  // outer gap loop
      for (pos = gap; pos < arraySize; pos++)   // middle loop
      {
         tmp = a[pos];
         for (k = pos; k >= gap && tmp < a[k - gap]; k -= gap) // inner loop
            a[k] = a[k - gap];
         a[k] = tmp;
      }
}

int main()
{
   int k, gapArraySize;
   int arrayOfInts[ARRAY_SIZE];
   FHvector<int> fhVectorOfInts1;
   FHvector<int> fhVectorOfInts2;
   FHvector<int> fhVectorOfInts3;
   FHvector<int> fhVectorOfInts4;

   int gapArray[] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024,
      2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288,
      1048576 };
   
   // computing Sedgewick's gap
   int sedgewickArray[28]; // higher values produce neg. #s due to overflow
   for (k = 0; k < 14; k++)
      sedgewickArray[k] = 9 * (pow(4, k) - pow(2, k)) + 1;
   for (k = 2; k < 16; k++)
      sedgewickArray[k + 12] = pow(4, k) - 3 * (pow(2, k)) + 1;

   // computing Tokuda's gap
   int tokudaArray[26]; // higher values produce neg. #s due to overflow
   for (k = 1; k < 27; k++)
      tokudaArray[k - 1] =
      ceil((pow(9, k) - pow(4, k)) / (5 * pow(4, k -1)));
   
   cout << "Sedgewick's Gap Sequence:" << endl;
   gapArraySize = sizeof(sedgewickArray) / sizeof(*sedgewickArray);
   shellSort1(sedgewickArray, gapArraySize);
   for (k = 0; k < 28; k++)
      cout << sedgewickArray[k] << endl;
   cout << endl;

   cout << "Tokuda's Gap Sequence:" << endl;
   for (k = 0; k < 26; k++)
      cout << tokudaArray[k] << endl;
   cout << endl;

   // fill 4 vectors with identical random values so we can compare gaps
   for (k = 0; k < ARRAY_SIZE; k++)
   {
      arrayOfInts[k] = rand() % ARRAY_SIZE;
      fhVectorOfInts1.push_back(arrayOfInts[k]);
      fhVectorOfInts2.push_back(arrayOfInts[k]);
      fhVectorOfInts3.push_back(arrayOfInts[k]);
      fhVectorOfInts4.push_back(arrayOfInts[k]);
   }

   cout << "\nShell Sorts called on vectors of size " << ARRAY_SIZE << endl;

   // how to time algorithms
   clock_t startTime, stopTime;

   // implicit Shell gap sequence
   startTime = clock();  // ------------------ start 

   shellSort1(fhVectorOfInts1);  // time this

   stopTime = clock();  // ---------------------- stop
   cout << "\nImplicit Shell Gap Elapsed Time: "
      << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
      << " seconds." << endl << endl;

   // explicit Shell gap sequence
   gapArraySize = sizeof(gapArray) / sizeof(*gapArray);
   cout << "gap size: " << gapArraySize << endl;
   startTime = clock();  // ------------------ start 

   shellSortX(fhVectorOfInts2, gapArray, gapArraySize);  // time this

   stopTime = clock();  // ---------------------- stop
   cout << "Explicit Shell Gap Elapsed Time: "
      << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
      << " seconds." << endl << endl;

   // Sedgewick's gap sequence
   gapArraySize = sizeof(sedgewickArray) / sizeof(*sedgewickArray);
   cout << "gap size: " << gapArraySize << endl;
   startTime = clock();  // ------------------ start 

   shellSortX(fhVectorOfInts3, sedgewickArray, gapArraySize);  // time this

   stopTime = clock();  // ---------------------- stop
   cout << "Sedgewick Gap Elapsed Time: "
      << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
      << " seconds." << endl << endl;

   // Tokuda's gap sequence
   gapArraySize = sizeof(tokudaArray) / sizeof(*tokudaArray);
   cout << "gap size: " << gapArraySize << endl;
   startTime = clock();  // ------------------ start 

   shellSortX(fhVectorOfInts4, tokudaArray, gapArraySize);  // time this

   stopTime = clock();  // ---------------------- stop
   cout << "Tokuda Gap Elapsed Time: "
      << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
      << " seconds." << endl << endl;

   // confirming that we got the correct results on all the arrays
   for (k = 0; k < ARRAY_SIZE; k += ARRAY_SIZE / 10)
   {
      cout << "implicit shell gap #" << k << ": "
         << fhVectorOfInts1[k] << ", ";
      cout << "explicit shell gap #" << k << ": "
         << fhVectorOfInts2[k] << ",\n";
      cout << "Sedgewick gap #" << k << ": " << fhVectorOfInts3[k] << ", ";
      cout << "Tokuda gap #" << k << ": " << fhVectorOfInts4[k] << endl;
   }

   return 0;
}

/* Assignment 7 Table, Questions, & Program Output:

ARRAY_SIZE  |  Shell (Implicit)  |  Shell(Explicit)  |  Sedgewick  |  Tokuda
----------------------------------------------------------------------------
10000       |     0.001 s        |     0.003 s       |   0.002 s   |  0.002 s
31250       |     0.007 s        |     0.014 s       |   0.006 s   |  0.007 s
75125       |     0.019 s        |     0.048 s       |   0.016 s   |  0.019 s
100000      |     0.028 s        |     0.065 s       |   0.022 s   |  0.027 s
135750      |     0.035 s        |     0.097 s       |   0.031 s   |  0.036 s
166500      |     0.044 s        |     0.123 s       |   0.038 s   |  0.045 s
200000      |     0.057 s        |     0.149 s       |   0.046 s   |  0.055 s
255000      |     0.086 s        |     0.210 s       |   0.061 s   |  0.078 s


1. Why does Shell's gap sequence implied by shellSort1() give a different
   timing result than the explicit array described above and passed to
   shellSortX()?  Which is faster and why?

   Shell's implicit sequence is flawed because in the case where the array size
   is some power of 2, the sort doesn't compare odd and even index values until
   the final loop, which is just the basic insertion sort.  In the case where
   the array size is not a power of 2, odd gap sizes ensure than odd and even
   indices are comparaed before we get all the way to the final insertion sort
   of gap size 1.  Since the vectors that were tested were filled with random
   values and the size of the vectors were not powers of 2, Shell's implicit
   gap sequence did not produce disasterous results.

   The explicit Shell gap sequence takes the worst case scenario of Shell's
   implied gap sequence and makes it standard procedure.  In a test scenario
   for array size 255000 in which I set even indices to hold the value 1 and
   odd indices to hold the value 5 (not shown in client or the table above),
   the implicit gap sequence as well as Sedgewick's and Tokuda's gap sequences
   all resulted in sort times less than 0.1 s.  Meanwhile, the explicit gap
   sequence took approximately 20 s.  This occurs because now the same, already
   sorted, indices are being redundantly compared to each other until the very
   last insertion sort with a gap size of 1 in which everything is finally
   sorted correctly.

   Sedgewick's gap sequence was computed using the two formulas from the
   text and then combined into a single sequence.  This gap sequence
   produced the best results of the four methods tested.  The 4th sequence I
   chose was created by Naoyuki Tokuda in 1992 but it didn't beat Sedgewick's
   sequence.  Another I found was by Marcin Ciura, but this one was not derived
   from a formula but rather from empirical evidence Ciura found when testing
   gap sequences.  Still in his paper Ciura claimed that his was "optimal", but
   because the max value in his sequence was only 701, I could not really test
   it effectively on large vectors (array sizes under 10000 took about 0 s when
   calculated with our standard method for timing.  Interestingly, while the
   Sedgewick sequence outperformed the other methods as expected, the Tokuda
   sequence essentially tied with Shell's implicit sequence.
   
   Another thing to note is that the time complexity appears to hover just
   over N for all the sequences except the explicit Shell sequence.  This
   verifies the big O estimate of N^(4/3) for Sedgewick given in the book.
   The others seem to be growing more towards the end but unfortunately I
   could not run tests on array sizes larger than 255000.  Larger
   discrepancies in the results for the various gap sequences might be better
   seen by running this program on a Linux computer.  Finally I should note
   that all the runs I did were done in the optimized release mode for Visual
   Studio 2013.


------------------Sample Run------------------
Sedgewick's Gap Sequence:
1
5
19
41
109
209
505
929
2161
3905
8929
16001
36289
64769
146305
260609
587521
1045505
2354689
4188161
9427969
16764929
37730305
67084289
150958081
268386305
603906049
1073643521

Tokuda's Gap Sequence:
1
4
9
20
46
103
233
525
1182
2660
5985
13467
30301
68178
153401
345152
776591
1747331
3931496
8845866
19903198
44782196
100759940
226709866
510097200
1147718700


Shell Sorts called on vectors of size 31250

Implicit Shell Gap Elapsed Time: 0.009 seconds.

gap size: 21
Explicit Shell Gap Elapsed Time: 0.014 seconds.

gap size: 28
Sedgewick Gap Elapsed Time: 0.006 seconds.

gap size: 26
Tokuda Gap Elapsed Time: 0.007 seconds.

implicit shell gap #0: 0, explicit shell gap #0: 0,
Sedgewick gap #0: 0, Tokuda gap #0: 0
implicit shell gap #3125: 1706, explicit shell gap #3125: 1706,
Sedgewick gap #3125: 1706, Tokuda gap #3125: 1706
implicit shell gap #6250: 5053, explicit shell gap #6250: 5053,
Sedgewick gap #6250: 5053, Tokuda gap #6250: 5053
implicit shell gap #9375: 8337, explicit shell gap #9375: 8337,
Sedgewick gap #9375: 8337, Tokuda gap #9375: 8337
implicit shell gap #12500: 11701, explicit shell gap #12500: 11701,
Sedgewick gap #12500: 11701, Tokuda gap #12500: 11701
implicit shell gap #15625: 14972, explicit shell gap #15625: 14972,
Sedgewick gap #15625: 14972, Tokuda gap #15625: 14972
implicit shell gap #18750: 18283, explicit shell gap #18750: 18283,
Sedgewick gap #18750: 18283, Tokuda gap #18750: 18283
implicit shell gap #21875: 21459, explicit shell gap #21875: 21459,
Sedgewick gap #21875: 21459, Tokuda gap #21875: 21459
implicit shell gap #25000: 24715, explicit shell gap #25000: 24715,
Sedgewick gap #25000: 24715, Tokuda gap #25000: 24715
implicit shell gap #28125: 28037, explicit shell gap #28125: 28037,
Sedgewick gap #28125: 28037, Tokuda gap #28125: 28037
Press any key to continue . . .

*/