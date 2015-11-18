#include <iostream>
#include <ctime> // for timing algorithms
#include <climits> // for INT_MAX
#include "FHvector.h"
#include "FHsort.h" // for insertionSort(), mySwapFH(), and median3()
using namespace std;

#define ARRAY_SIZE 100000

// quickSortX public driver
template <typename Comparable>
bool quickSortX(FHvector<Comparable> & a, int recLimit)
{
   if (recLimit < 2)
      return false;

   quickSortX(a, 0, a.size() - 1, recLimit);
   return true;
}

// quickSortX internal
template <typename Comparable>
void quickSortX(FHvector<Comparable> & a, int left, int right, int recLimit)
{
   Comparable pivot;
   int i, j;

   if (left + recLimit <= right)
   {
      pivot = median3(a, left, right);
      for (i = left, j = right - 1;;)
      {
         while (a[++i] < pivot)
            ;
         while (pivot < a[--j])
            ;
         if (i < j)
            mySwapFH(a[i], a[j]);
         else
            break;
      }

      mySwapFH(a[i], a[right - 1]);  // restore pivot

      // recursive calls on smaller sub-groups
      quickSortX(a, left, i - 1, recLimit);
      quickSortX(a, i + 1, right, recLimit);
   }
   else
      // non-recursive escape valve - insertionSort
      insertionSort(a, left, right);
}

int main()
{
   int k, recursionLimit;
   int arrayOfInts[ARRAY_SIZE];
   FHvector<int> fhVectorOfInts;

   // fill an array with random values
   for (k = 0; k < ARRAY_SIZE; k++)
      arrayOfInts[k] = rand() % INT_MAX;

   

   // how to time algorithms
   clock_t startTime, stopTime;

   cout << "Quick Sorts called on a vector of size " << ARRAY_SIZE
      << "\n\nElapsed Times for Recursion Limits of Size" << endl;

   for (recursionLimit = 2; recursionLimit <= 300; recursionLimit += 2)
   {
      // clear fhVectorOfInts and fill with random values from arrayOfInts
      fhVectorOfInts.clear();
      for (k = 0; k < ARRAY_SIZE; k++)
         fhVectorOfInts.push_back(arrayOfInts[k]);

      startTime = clock();  // ------------------ start 

      quickSortX(fhVectorOfInts, recursionLimit);  // time this

      stopTime = clock();  // ---------------------- stop
      cout << "(" << recursionLimit << ") : "
         << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
         << " seconds." << endl;
   }

   cout << endl << endl;

   // proof of correctness for quickSortX()
   for (k = 0; k < ARRAY_SIZE; k += ARRAY_SIZE / 5)
   {
      cout << "randomized array #" << k << ": " << arrayOfInts[k] << ", ";
      cout << "quickSortX #" << k << ": " << fhVectorOfInts[k] << endl;
   }

   return 0;
}

/* Assignment 8 Table, Commentary, & Program Output:

------------------Tables for Various Vector Sizes------------------
ARRAY_SIZE 40K:
Rec. Limit     |  Sorting Time (seconds)
-----------------------------------------
2 - 6          |  0.005
8 - 10         |  0.004 (MIN)
12 - 94        |  ~0.0045 (0.004 - 0.005)
96 - 144       |  ~0.0055 (0.004 - 0.007)
146 - 226      |  ~0.0065 (0.006 - 0.008)
228 - 266      |  ~0.007 (0.006 - 0.008)
268 - 300      |  ~0.008 (0.007 - 0.009)

ARRAY_SIZE 60K:
Rec. Limit     |  Sorting Time (seconds)
-----------------------------------------
2 - 10         |  0.007
12             |  0.006 (MIN)
14 - 60        |  ~0.0065 (0.006 - 0.007)
62 - 78        |  0.007
80             |  0.011 (local max)
82 - 86        |  ~0.0095 (0.009 - 0.01)
88 - 122       |  ~0.008 (0.007 - 0.008)
124            |  0.01 (local max)
126 - 154      |  ~0.008 (0.008 - 0.009)
156 - 184      |  0.009
186 - 210      |  ~0.0095 (0.009 - 0.01)
212 - 234      |  ~0.01 (0.01 - 0.011)
236 - 256      |  ~0.011 (0.01 - 0.012)
258 - 262      |  ~0.017 (0.016 - 0.018)
264            |  0.019 (MAX)
266 - 272      |  ~0.015 (0.014 - 0.015)
274 - 300      |  ~0.012 (0.011 - 0.014)

ARRAY_SIZE 80K:
Rec. Limit     |  Sorting Time (seconds)
-----------------------------------------
2 - 8          |  0.009
10             |  0.008 (MIN)
12 - 88        |  ~0.009 (0.008 - 0.011)
90 - 98        |  0.015
100 - 106      |  ~0.0135 (0.012 - 0.015)
108 - 152      |  ~0.0115 (0.011 - 0.013)
154 - 188      |  ~0.012 (0.012 - 0.014)
190 - 202      |  ~0.013 (0.012 - 0.014)
204 - 208      |  ~0.0165 (0.015 - 0.018)
210 - 214      |  ~0.0225 (0.022 - 0.024)
216            |  0.05 (MAX)
218 - 222      |  ~0.024 (0.022 - 0.026)
224 - 250      |  ~0.0145 (0.014 - 0.016)
252 - 270      |  ~0.0155 (0.015 - 0.017)
272 - 300      |  ~0.016 (0.015 - 0.017)

ARRAY_SIZE 120K:
Rec. Limit     |  Sorting Time (seconds)
-----------------------------------------
2 - 12         |  ~0.019 (0.017 - 0.02)
14 - 20        |  ~0.015 (0.014 - 0.016)
22             |  0.013 (MIN)
24 - 58        |  ~0.014 (0.013 - 0.014)
60 - 106       |  ~0.015 (0.014 - 0.016)
108            |  0.04 (local max)
110 - 128      |  ~0.021 (0.019 - 0.025)
130 - 150      |  0.017
152 - 180      |  ~0.018 (0.017 - 0.019)
182 - 216      |  ~0.023 (0.022 - 0.026)
218 - 254      |  ~0.022 (0.021 - 0.023)
256 - 274      |  ~0.023 (0.022 - 0.023)
276 - 282      |  ~0.033 (0.031 - 0.035) (0.035 = MAX)
284 - 300      |  ~0.025 (0.024 - 0.026)

ARRAY_SIZE 160K:
Rec. Limit     |  Sorting Time (seconds)
-----------------------------------------
2 - 20         |  ~0.018 (0.018 - 0.019)
22             |  0.017 (MIN)
24 - 30        |  ~0.018 (0.018 - 0.019)
32             |  0.037 (local max)
34 - 40        |  ~0.023 (0.02 - 0.026)
42 - 60        |  ~0.018 (0.018 - 0.019)
62 - 90        |  ~0.019 (0.019 - 0.02)
92 - 116       |  ~0.021 (0.02 - 0.021)
118            |  0.028 (local max)
120 - 122      |  ~0.025 (0.024 - 0.026)
124 - 164      |  ~0.023 (0.022 - 0.024)
166 - 178      |  ~0.024 (0.024 - 0.025)
180 - 190      |  ~0.025 (0.025 - 0.026)
192            |  0.057 (MAX)
194 - 196      |  ~0.036 (0.034 - 0.038)
198 - 228      |  ~0.0275 (0.026 - 0.029)
230 -250       |  ~0.029 (0.028 - 0.03)
252            |  0.044 (local max)
254 - 256      |  ~0.034 (0.032 - 0.036)
258 - 290      |  ~0.031 (0.029 - 0.031)
292 - 300      |  ~0.033 (0.031 - 0.035)

ARRAY_SIZE 240K:
Rec. Limit     |  Sorting Time (seconds)
-----------------------------------------
2              |  0.044 (local max)
4 - 14         |  ~0.03 (0.028 - 0.033)
16 - 18        |  0.027 (MIN)
20 - 36        |  0.028
38 - 46        |  ~0.029 (0.028 - 0.03)
48 - 50        |  ~0.0345 (0.034 - 0.035) (local max = 0.035)
52 - 78        |  ~0.03 (0.029 - 0.031)
80 - 104       |  ~0.032 (0.031 - 0.033)
106            |  0.047 (local max)
108 - 110      |  ~0.045 (0.044 - 0.046)
112 - 134      |  ~0.034 (0.033 - 0.036)
136 - 154      |  ~0.036 (0.034 - 0.037)
156            |  0.076 (local max)
158 - 200      |  ~0.04 (0.037 - 0.043)
202            |  0.053 (local max)
204 - 242      |  ~0.043 (0.041 - 0.046)
244            |  0.077 (MAX)
246 - 248      |  ~0.0685 (0.068 - 0.069)
250 - 252      |  ~0.0545 (0.051 - 0.058)
254 - 256      |  ~0.0715 (0.071 - 0.072) (local max = 0.072)
258            |  0.058
260 - 276      |  ~0.047 (0.045 - 0.048)
278            |  0.075 (local max)
280            |  0.06
282 - 300      |  ~0.049 (0.047 - 0.05)


------------------Commentary on Quick Sort------------------
As described in the modules, the value for a recursion limit that provided the
quickest sort times for quickSort() fell between 5 and 25 for all the runs I
did on randomized vectors.  It's interesting to note that for the smaller
vectors in the tables above (40K, 60K, and 80K) the recursion limit that gave
the fastest sort times was closer to 10 whereas for the larger vectors (120K,
160K, 240K) the recursion limit that gave the fastest sort times was around 20.
However, repeated tests performed on a vector of size 240000 indicated that
the size of the vector did not have any correlation with the optimal recursion
limit; the limit that provided the best times varied between 5 and 25 without
being skewed to either side.

Another peculiar aspect to note would be the distribution of ranges of values
for recursion limits that provided similar sort times.  Take a look at the
graphs on the attached Excel sheet to get a visual picture.  For the smaller
vectors, you can see long horizontal bars which indicate large ranges of
recursion limits that result in the same sorting time.  As the size of the
vector grows, the distributions begin to smoothen out and it starts to appear
that there is in fact a linear correlation between the recursion limit and
the sorting time of quickSort().  This makes sense.  The larger the recursion
limit, the sooner standard insertion sort will be called.  Insertion sort
is most useful for sorting an array which has the majority of its elements
in the right place.  The more disordered the array passed to the insertion
sort is, the longer the total sorting time for quickSort() will be.

The charts in the Excel sheet reveal something else as well: maximas exist
for seeminly random recursion limits for all the vector sizes tested.  The
quickSort() algorithm itself doesn't provide any clues as to the cause for
these maximas, so I ran a few tests and varied the content of the vectors.
Graphs of these tests can be found below the graph for vector size 240K on
the Excel sheet.

A run on a vector of size 240000 with random values but many repeats led to a
curious graph (see Excel sheet) with essentially the same sorting times for
all recursion limits.  This run still resulted in a few maxima for sorting
times, but the corresponding recursion limits did not appear to be correlated
with those from the original run on the vector of size 240K.  The reason that
this run showed almost no growth in time vs. the recursion limit could
possibly be due to the quickSort() algorithm sorting the majority of the
vector before calling insertionSort() since there were many repeated values.
This would lead to the time added by insertionSort() to be inconsequential to
the overall sorting time, regardless of the recursion limit.

A final run on a sorted vector of size 240000 with 2400 unsorted elements led
to a graph with large variation in the sorting times (see Excel sheet).  A
linear correlation between the recursion limit and the sorting time can still
be argued, though this is harder to observe than it was for the fully
randomized arrays.  Perhaps the large variation in sorting times is due to
the state of the vector before it is passed to insertionSort().  Since the
vector is already somewhat sorted to begin with, the majority of the sorting
will be done in insertionSort().  This tells us that we should observe the
sorting time increase along with the recursion limit; and to an extent we do
see this.  On the other hand, the vector already being partially sorted means
that the oveall sorting times will be very, very quick.  Even though there
appears to be a lot of variation, if we ignore the outliers, it is evident
that all the sorts are being done between 0.01 s and 0.02 s.  This is much
faster than the two other cases for a vector size 240000 and is a fairly
tight bound.

One last chart for time complexity (using the last row for times):
40K      |     80K      |  160K
----------------------------------
0.007s   |     0.023s   |  0.031s
       ->3x           ->1.5x


50K      |     100K     |  200K
----------------------------------
0.011s   |     0.022s   |  0.041s
       ->2x           ->2x


60K      |     120K     |  240K
----------------------------------
0.012s   |     0.03s    |  0.047s
       ->2.5x         ->1.5x


------------------Sample Run------------------
Quick Sorts called on a vector of size 200000

Elapsed Times for Recursion Limits of Size
(2) : 0.025 seconds.
(4) : 0.024 seconds.
(6) : 0.024 seconds.
(8) : 0.025 seconds.
(10) : 0.023 seconds.
(12) : 0.023 seconds.
(14) : 0.022 seconds.
(16) : 0.022 seconds.
(18) : 0.023 seconds.
(20) : 0.023 seconds.
(22) : 0.022 seconds.
(24) : 0.022 seconds.
(26) : 0.023 seconds.
(28) : 0.057 seconds.
(30) : 0.03 seconds.
(32) : 0.03 seconds.
(34) : 0.028 seconds.
(36) : 0.024 seconds.
(38) : 0.024 seconds.
(40) : 0.024 seconds.
(42) : 0.023 seconds.
(44) : 0.025 seconds.
(46) : 0.024 seconds.
(48) : 0.025 seconds.
(50) : 0.023 seconds.
(52) : 0.024 seconds.
(54) : 0.026 seconds.
(56) : 0.025 seconds.
(58) : 0.024 seconds.
(60) : 0.024 seconds.
(62) : 0.024 seconds.
(64) : 0.024 seconds.
(66) : 0.024 seconds.
(68) : 0.024 seconds.
(70) : 0.025 seconds.
(72) : 0.024 seconds.
(74) : 0.025 seconds.
(76) : 0.025 seconds.
(78) : 0.024 seconds.
(80) : 0.026 seconds.
(82) : 0.026 seconds.
(84) : 0.027 seconds.
(86) : 0.026 seconds.
(88) : 0.026 seconds.
(90) : 0.026 seconds.
(92) : 0.026 seconds.
(94) : 0.026 seconds.
(96) : 0.036 seconds.
(98) : 0.035 seconds.
(100) : 0.031 seconds.
(102) : 0.027 seconds.
(104) : 0.028 seconds.
(106) : 0.028 seconds.
(108) : 0.027 seconds.
(110) : 0.028 seconds.
(112) : 0.027 seconds.
(114) : 0.028 seconds.
(116) : 0.027 seconds.
(118) : 0.028 seconds.
(120) : 0.028 seconds.
(122) : 0.028 seconds.
(124) : 0.029 seconds.
(126) : 0.028 seconds.
(128) : 0.027 seconds.
(130) : 0.028 seconds.
(132) : 0.029 seconds.
(134) : 0.029 seconds.
(136) : 0.029 seconds.
(138) : 0.028 seconds.
(140) : 0.028 seconds.
(142) : 0.029 seconds.
(144) : 0.03 seconds.
(146) : 0.029 seconds.
(148) : 0.029 seconds.
(150) : 0.029 seconds.
(152) : 0.03 seconds.
(154) : 0.034 seconds.
(156) : 0.031 seconds.
(158) : 0.03 seconds.
(160) : 0.032 seconds.
(162) : 0.031 seconds.
(164) : 0.032 seconds.
(166) : 0.032 seconds.
(168) : 0.031 seconds.
(170) : 0.032 seconds.
(172) : 0.031 seconds.
(174) : 0.044 seconds.
(176) : 0.05 seconds.
(178) : 0.051 seconds.
(180) : 0.045 seconds.
(182) : 0.033 seconds.
(184) : 0.033 seconds.
(186) : 0.033 seconds.
(188) : 0.034 seconds.
(190) : 0.033 seconds.
(192) : 0.032 seconds.
(194) : 0.034 seconds.
(196) : 0.033 seconds.
(198) : 0.033 seconds.
(200) : 0.033 seconds.
(202) : 0.033 seconds.
(204) : 0.034 seconds.
(206) : 0.033 seconds.
(208) : 0.086 seconds.
(210) : 0.046 seconds.
(212) : 0.045 seconds.
(214) : 0.037 seconds.
(216) : 0.034 seconds.
(218) : 0.035 seconds.
(220) : 0.035 seconds.
(222) : 0.036 seconds.
(224) : 0.035 seconds.
(226) : 0.035 seconds.
(228) : 0.035 seconds.
(230) : 0.036 seconds.
(232) : 0.036 seconds.
(234) : 0.036 seconds.
(236) : 0.037 seconds.
(238) : 0.036 seconds.
(240) : 0.037 seconds.
(242) : 0.036 seconds.
(244) : 0.037 seconds.
(246) : 0.038 seconds.
(248) : 0.038 seconds.
(250) : 0.038 seconds.
(252) : 0.036 seconds.
(254) : 0.068 seconds.
(256) : 0.056 seconds.
(258) : 0.051 seconds.
(260) : 0.04 seconds.
(262) : 0.039 seconds.
(264) : 0.038 seconds.
(266) : 0.04 seconds.
(268) : 0.04 seconds.
(270) : 0.039 seconds.
(272) : 0.039 seconds.
(274) : 0.041 seconds.
(276) : 0.04 seconds.
(278) : 0.039 seconds.
(280) : 0.038 seconds.
(282) : 0.041 seconds.
(284) : 0.039 seconds.
(286) : 0.04 seconds.
(288) : 0.039 seconds.
(290) : 0.04 seconds.
(292) : 0.04 seconds.
(294) : 0.041 seconds.
(296) : 0.041 seconds.
(298) : 0.045 seconds.
(300) : 0.041 seconds.


randomized array #0: 41, quickSortX #0: 0
randomized array #40000: 4167, quickSortX #40000: 6589
randomized array #80000: 14438, quickSortX #80000: 13141
randomized array #120000: 198, quickSortX #120000: 19676
randomized array #160000: 12712, quickSortX #160000: 26200
Press any key to continue . . .

*/