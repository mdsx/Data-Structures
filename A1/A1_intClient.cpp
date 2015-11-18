#include <iostream>
#include <vector>
using namespace std;

// Sublist class declarations -------------------
class Sublist
{
public:
   Sublist(vector<int> *orig = NULL)
      : sum(0), originalObjects(orig) { }
   Sublist addItem(int indexOfItemToAdd);
   void showSublist() const;
   int getSum() const { return sum; }

private:
   int sum;
   vector<int> *originalObjects;
   vector<int> indices;
};

// Client for int data sets -------------------
int main()
{
   int TARGET = 180;
   vector<int> dataSet;
   vector<Sublist> choices;
   int numSets, indexOfMax, maxSum, lastIn;

   dataSet.push_back(20); dataSet.push_back(12); dataSet.push_back(22);
   dataSet.push_back(15); dataSet.push_back(25);
   dataSet.push_back(19); dataSet.push_back(29);
   dataSet.push_back(18);
   dataSet.push_back(11); dataSet.push_back(13); dataSet.push_back(17);

   choices.clear();
   cout << "Target time: " << TARGET << endl;

   // code provided by student
   // initialize variables
   Sublist empty(&dataSet);
   choices.push_back(empty);
   numSets = 1;
   indexOfMax = 0;
   maxSum = 0;

   // find maximum sum from data set
   for (int m = 0; m < dataSet.size(); m++)
      maxSum += dataSet[m];

   // display all data if TARGET exceeds max sum
   if (TARGET > maxSum)
   {
      cout << "TARGET exceeds maximum sum; "
         << "the following is the entire data set: " << endl;
      cout << "Data Set -----------------------------" << endl;
      cout << "sum: " << maxSum << endl;

      for (int n = 0; n < dataSet.size() - 1; n++)
         cout << "array[" << n << "] = " << dataSet[n] << ",   ";
      
      lastIn = dataSet.size() - 1;
      cout << "array[" << lastIn << "] = ";
      cout << dataSet[dataSet.size() - 1] << endl;
   }
   else
   {
      // for loop implements given subset-sum algorithm
      for (int i = 0; i < dataSet.size(); i++)
      {
         for (int j = 0; j < numSets; j++)
         {
            if (choices[j].getSum() + dataSet[i] <= TARGET)
               choices.push_back(choices[j].addItem(i));

            if (choices[j].getSum() + dataSet[i] == TARGET)
            {
               indexOfMax = choices.size() - 1;
               break;
            }
         }
         numSets = choices.size();
      }

      // find sublist with the largest sum
      if (indexOfMax == 0)
      {
         for (int k = 0; k < choices.size(); k++)
         {
            if (choices[k].getSum() > choices[indexOfMax].getSum())
               indexOfMax = k;
         }
      }

      choices[indexOfMax].showSublist();
   }
   
   return 0;
}

// Sublist method definitions -------------------
Sublist Sublist::addItem(int indexOfItemToAdd)
{
   Sublist newSublist(originalObjects);
   for (int i = 0; i < indices.size(); i++)
      newSublist.indices.push_back(indices[i]);

   newSublist.indices.push_back(indexOfItemToAdd);
   newSublist.sum = sum + (*originalObjects)[indexOfItemToAdd];
   return newSublist;
}

void Sublist::showSublist() const
{
   int lastIndex;
   if (indices.size() == 0)
   {
      cout << "Empty Sublist" << endl;
   }
   else
   {
      lastIndex = indices.size() - 1;
      cout << "Sublist -----------------------------" << endl;
      cout << "sum: " << sum << endl;

      for (int i = 0; i < indices.size() - 1; i++)
      {
         cout << "array[" << indices[i] << "] = "
            << (*originalObjects)[indices[i]] << ",   ";
      }
      cout << "array[" << indices[lastIndex] << "] = "
         << (*originalObjects)[indices[lastIndex]] << endl;
   }
}

/* Program Output:
------------------Run 1------------------
Target time: 180
Sublist -----------------------------
sum: 179
array[0] = 20,   array[1] = 12,   array[3] = 15,   array[4] = 25,   array[5] = 1
9,   array[6] = 29,   array[7] = 18,   array[8] = 11,   array[9] = 13,   array[1
0] = 17
Press any key to continue . . .

------------------Run 2------------------
Target time: 150
Sublist -----------------------------
sum: 150
array[0] = 20,   array[2] = 22,   array[4] = 25,   array[5] = 19,   array[6] = 2
9,   array[7] = 18,   array[10] = 17
Press any key to continue . . .

------------------Run 3------------------
Target time: 200
Sublist -----------------------------
sum: 190
array[0] = 20,   array[1] = 12,   array[2] = 22,   array[3] = 15,   array[4] = 2
5,   array[5] = 19,   array[6] = 29,   array[7] = 18,   array[9] = 13,   array[1
0] = 17
Press any key to continue . . .

------------------Run 4------------------
Target time: 500
TARGET exceeds maximum sum; the following is the entire data set:
Data Set -----------------------------
sum: 201
array[0] = 20,   array[1] = 12,   array[2] = 22,   array[3] = 15,   array[4] = 2
5,   array[5] = 19,   array[6] = 29,   array[7] = 18,   array[8] = 11,   array[9
] = 13,   array[10] = 17
Press any key to continue . . .
*/