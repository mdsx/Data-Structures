//#pragma once
// operator tests
/*
iTunesEntry test = tunes_input[0];
cout << "+ op.: " << 1 + test << endl;
cout << "<< op.: " << test << endl;
*/
#ifndef SUBLIST_H
#define SUBLIST_H

#include <vector>
using namespace std;

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

#endif // SUBLIST_H