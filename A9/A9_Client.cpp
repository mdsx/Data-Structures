// FHflowGraph client
// CS 2C Foothill College
#include <iostream>
#include <string>
using namespace std;
#include "FHflowGraph.h"

// --------------- main ---------------
int main()
{
   int finalFlow;

   // build graph
   FHflowGraph<string, int> myG;

   // first test
   myG.addEdge("s", "a", 3);    myG.addEdge("s", "b", 2);
   myG.addEdge("a", "b", 1);    myG.addEdge("a", "c", 3); 
   myG.addEdge("a", "d", 4);
   myG.addEdge("b", "d", 2);
   myG.addEdge("c", "t", 2);
   myG.addEdge("d", "t", 3);

   // show the original flow graph
   myG.showResAdjTable();
   myG.showFlowAdjTable();

   myG.setStartVert("s");
   myG.setEndVert("t");
   finalFlow = myG.findMaxFlow();

   cout << "Final flow: " << finalFlow << endl;

   myG.showResAdjTable();
   myG.showFlowAdjTable();

   // second test
   myG.clear();
   myG.addEdge("s", "a", 3); myG.addEdge("s", "b", 2);
   myG.addEdge("a", "b", 1); myG.addEdge("a", "c", 3);
   myG.addEdge("a", "d", 4);
   myG.addEdge("b", "d", 2);
   myG.addEdge("c", "t", 2);
   myG.addEdge("d", "t", 3);

   // show the original flow graph
   myG.showResAdjTable();
   myG.showFlowAdjTable();

   myG.setStartVert("s");
   myG.setEndVert("t");
   finalFlow = myG.findMaxFlow();

   cout << "Final flow: " << finalFlow << endl;

   myG.showResAdjTable();
   myG.showFlowAdjTable();

   // third test
   myG.clear();
   myG.addEdge("s", "a", 4); myG.addEdge("s", "b", 2);
   myG.addEdge("a", "b", 1); myG.addEdge("a", "c", 2);
   myG.addEdge("a", "d", 4);
   myG.addEdge("b", "d", 2);
   myG.addEdge("c", "t", 3);
   myG.addEdge("d", "t", 3);

   // show the original flow graph
   myG.showResAdjTable();
   myG.showFlowAdjTable();

   myG.setStartVert("s");
   myG.setEndVert("t");
   finalFlow = myG.findMaxFlow();

   cout << "Final flow: " << finalFlow << endl;

   myG.showResAdjTable();
   myG.showFlowAdjTable();

   // fourth test
   myG.clear();
   myG.addEdge("s", "A", 1); myG.addEdge("s", "D", 4);
   myG.addEdge("s", "G", 6);
   myG.addEdge("A", "B", 2); myG.addEdge("A", "E", 2);
   myG.addEdge("B", "C", 2);
   myG.addEdge("C", "t", 4);
   myG.addEdge("D", "E", 3); myG.addEdge("D", "A", 3);
   myG.addEdge("E", "C", 2); myG.addEdge("E", "F", 3);
   myG.addEdge("E", "I", 3);
   myG.addEdge("F", "C", 1); myG.addEdge("F", "t", 3);
   myG.addEdge("G", "D", 2); myG.addEdge("G", "E", 1);
   myG.addEdge("G", "H", 6);
   myG.addEdge("H", "E", 2); myG.addEdge("H", "I", 6);
   myG.addEdge("I", "F", 1); myG.addEdge("I", "t", 4);

   // show the original flow graph
   myG.showResAdjTable();
   myG.showFlowAdjTable();

   myG.setStartVert("s");
   myG.setEndVert("t");
   finalFlow = myG.findMaxFlow();

   cout << "Final flow: " << finalFlow << endl;

   myG.showResAdjTable();
   myG.showFlowAdjTable();

   // fifth test
   myG.clear();

   myG.addEdge("s", "h", 5);
   myG.addEdge("h", "i", 5);
   myG.addEdge("i", "b", 5);
   myG.addEdge("a", "b", 5);
   myG.addEdge("s", "a", 5);
   myG.addEdge("s", "c", 5);
   myG.addEdge("s", "d", 5);
   myG.addEdge("a", "e", 5);
   myG.addEdge("e", "j", 5);
   myG.addEdge("j", "t", 5);
   myG.addEdge("d", "g", 5);
   myG.addEdge("g", "t", 5);
   myG.addEdge("b", "t", 5);
   myG.addEdge("c", "t", 5);
   myG.addEdge("d", "c", 5);

   // show the original flow graph
   myG.showResAdjTable();
   myG.showFlowAdjTable();

   myG.setStartVert("s");
   myG.setEndVert("t");
   finalFlow = myG.findMaxFlow();

   cout << "Final flow: " << finalFlow << endl;

   myG.showResAdjTable();
   myG.showFlowAdjTable();


   // first test, redux
   myG.clear();
   myG.addEdge("s", "a", 3);    myG.addEdge("s", "b", 2);
   myG.addEdge("a", "b", 1);    myG.addEdge("a", "c", 3);
   myG.addEdge("a", "d", 4);
   myG.addEdge("b", "d", 2);
   myG.addEdge("c", "t", 2);
   myG.addEdge("d", "t", 3);

   // show the original flow graph
   myG.showResAdjTable();
   myG.showFlowAdjTable();

   myG.setStartVert("s");
   myG.setEndVert("t");
   finalFlow = myG.findMaxFlow();

   cout << "Final flow: " << finalFlow << endl;

   myG.showResAdjTable();
   myG.showFlowAdjTable();

   // final exam graph analysis
   myG.clear();
   myG.addEdge("s", "a", 1);    myG.addEdge("s", "b", 2);
   myG.addEdge("s", "t", 4);
   myG.addEdge("a", "c", 1);
   myG.addEdge("b", "d", 2);
   myG.addEdge("c", "t", 1);
   myG.addEdge("d", "t", 2);

   // show the original flow graph
   myG.showResAdjTable();
   myG.showFlowAdjTable();

   myG.setStartVert("s");
   myG.setEndVert("t");
   finalFlow = myG.findMaxFlow();

   cout << "Final flow: " << finalFlow << endl;

   myG.showResAdjTable();
   myG.showFlowAdjTable();

   return 0;
}

/*----------------------------------------------------------------------------*/

/* Assignment 9 Program Output:
First test is the one from the modules; works as expected.  Next 4 tests are
the ones Paul posted in the discussion.  Strangely, even though the "show res.
adj table" and "show flow adj table" have the same results as the expected
output Paul provided, the total costs of the maximum flow graphs do not match.
I spent a good while trying to find out why this is the case but I can't
figure it out.  I even ran the first test once more at the end to show that
that is still working to prove that subsequent runs are not somehow affecting
each other.  Maybe you'll have better luck than I in determining what's the
problem.


------------------Single Run------------------
------------------------
Residual Adj List for s: a(3) b(2)
Residual Adj List for a: s(0) b(1) c(3) d(4)
Residual Adj List for b: s(0) a(0) d(2)
Residual Adj List for c: a(0) t(2)
Residual Adj List for d: a(0) b(0) t(3)
Residual Adj List for t: c(0) d(0)

------------------------
Flow Adj List for s: a(0) b(0)
Flow Adj List for a: b(0) c(0) d(0)
Flow Adj List for b: d(0)
Flow Adj List for c: t(0)
Flow Adj List for d: t(0)
Flow Adj List for t:

Final flow: 15
------------------------
Residual Adj List for s: a(0) b(0)
Residual Adj List for a: s(3) b(1) c(1) d(3)
Residual Adj List for b: s(2) a(0) d(0)
Residual Adj List for c: a(2) t(0)
Residual Adj List for d: a(1) b(2) t(0)
Residual Adj List for t: c(2) d(3)

------------------------
Flow Adj List for s: a(3) b(2)
Flow Adj List for a: b(0) c(2) d(1)
Flow Adj List for b: d(2)
Flow Adj List for c: t(2)
Flow Adj List for d: t(3)
Flow Adj List for t:

------------------------
Residual Adj List for d: t(3) a(0) b(0)
Residual Adj List for t: d(0) c(0)
Residual Adj List for s: a(3) b(2)
Residual Adj List for a: d(4) s(0) b(1) c(3)
Residual Adj List for b: d(2) s(0) a(0)
Residual Adj List for c: t(2) a(0)

------------------------
Flow Adj List for d: t(0)
Flow Adj List for t:
Flow Adj List for s: a(0) b(0)
Flow Adj List for a: d(0) b(0) c(0)
Flow Adj List for b: d(0)
Flow Adj List for c: t(0)

Final flow: 15
------------------------
Residual Adj List for d: t(0) a(1) b(2)
Residual Adj List for t: d(3) c(2)
Residual Adj List for s: a(0) b(0)
Residual Adj List for a: d(3) s(3) b(1) c(1)
Residual Adj List for b: d(0) s(2) a(0)
Residual Adj List for c: t(0) a(2)

------------------------
Flow Adj List for d: t(3)
Flow Adj List for t:
Flow Adj List for s: a(3) b(2)
Flow Adj List for a: d(1) b(0) c(2)
Flow Adj List for b: d(2)
Flow Adj List for c: t(2)

------------------------
Residual Adj List for d: t(3) a(0) b(0)
Residual Adj List for t: d(0) c(0)
Residual Adj List for s: a(4) b(2)
Residual Adj List for a: d(4) s(0) b(1) c(2)
Residual Adj List for b: d(2) s(0) a(0)
Residual Adj List for c: t(3) a(0)

------------------------
Flow Adj List for d: t(0)
Flow Adj List for t:
Flow Adj List for s: a(0) b(0)
Flow Adj List for a: d(0) b(0) c(0)
Flow Adj List for b: d(0)
Flow Adj List for c: t(0)

Final flow: 15
------------------------
Residual Adj List for d: t(0) a(1) b(2)
Residual Adj List for t: d(3) c(2)
Residual Adj List for s: a(1) b(0)
Residual Adj List for a: d(3) s(3) b(1) c(0)
Residual Adj List for b: d(0) s(2) a(0)
Residual Adj List for c: t(1) a(2)

------------------------
Flow Adj List for d: t(3)
Flow Adj List for t:
Flow Adj List for s: a(3) b(2)
Flow Adj List for a: d(1) b(0) c(2)
Flow Adj List for b: d(2)
Flow Adj List for c: t(2)

------------------------
Residual Adj List for B: C(2) A(0)
Residual Adj List for E: C(2) F(3) A(0) D(0) G(0) I(3) H(0)
Residual Adj List for C: B(0) E(0) t(4) F(0)
Residual Adj List for t: C(0) F(0) I(0)
Residual Adj List for F: E(0) C(1) t(3) I(0)
Residual Adj List for s: A(1) D(4) G(6)
Residual Adj List for A: B(2) E(2) s(0) D(0)
Residual Adj List for D: E(3) s(0) A(3) G(0)
Residual Adj List for G: E(1) s(0) D(2) H(6)
Residual Adj List for I: E(0) t(4) F(1) H(0)
Residual Adj List for H: E(2) G(0) I(6)

------------------------
Flow Adj List for B: C(0)
Flow Adj List for E: C(0) F(0) I(0)
Flow Adj List for C: t(0)
Flow Adj List for t:
Flow Adj List for F: C(0) t(0)
Flow Adj List for s: A(0) D(0) G(0)
Flow Adj List for A: B(0) E(0)
Flow Adj List for D: E(0) A(0)
Flow Adj List for G: E(0) D(0) H(0)
Flow Adj List for I: t(0) F(0)
Flow Adj List for H: E(0) I(0)

Final flow: 47
------------------------
Residual Adj List for B: C(0) A(2)
Residual Adj List for E: C(1) F(0) A(2) D(3) G(1) I(0) H(1)
Residual Adj List for C: B(2) E(1) t(0) F(1)
Residual Adj List for t: C(4) F(2) I(4)
Residual Adj List for F: E(3) C(0) t(1) I(0)
Residual Adj List for s: A(0) D(0) G(1)
Residual Adj List for A: B(0) E(0) s(1) D(3)
Residual Adj List for D: E(0) s(4) A(0) G(2)
Residual Adj List for G: E(0) s(5) D(0) H(4)
Residual Adj List for I: E(3) t(0) F(1) H(1)
Residual Adj List for H: E(1) G(2) I(5)

------------------------
Flow Adj List for B: C(2)
Flow Adj List for E: C(2) F(3) I(3)
Flow Adj List for C: E(-1) t(4)
Flow Adj List for t:
Flow Adj List for F: C(1) t(2)
Flow Adj List for s: A(1) D(4) G(5)
Flow Adj List for A: B(2) E(2)
Flow Adj List for D: E(3) A(3)
Flow Adj List for G: E(1) D(2) H(2)
Flow Adj List for I: t(4) F(0)
Flow Adj List for H: E(1) I(1)

------------------------
Residual Adj List for j: t(5) e(0)
Residual Adj List for t: j(0) c(0) g(0) b(0)
Residual Adj List for s: c(5) d(5) h(5) a(5)
Residual Adj List for i: h(0) b(5)
Residual Adj List for c: t(5) s(0) d(0)
Residual Adj List for e: j(5) a(0)
Residual Adj List for d: s(0) c(5) g(5)
Residual Adj List for g: t(5) d(0)
Residual Adj List for h: s(0) i(5)
Residual Adj List for b: t(5) i(0) a(0)
Residual Adj List for a: s(0) e(5) b(5)

------------------------
Flow Adj List for j: t(0)
Flow Adj List for t:
Flow Adj List for s: c(0) d(0) h(0) a(0)
Flow Adj List for i: b(0)
Flow Adj List for c: t(0)
Flow Adj List for e: j(0)
Flow Adj List for d: c(0) g(0)
Flow Adj List for g: t(0)
Flow Adj List for h: i(0)
Flow Adj List for b: t(0)
Flow Adj List for a: e(0) b(0)

Final flow: 40
------------------------
Residual Adj List for j: t(5) e(0)
Residual Adj List for t: j(0) c(5) g(5) b(5)
Residual Adj List for s: c(0) d(0) h(5) a(0)
Residual Adj List for i: h(0) b(5)
Residual Adj List for c: t(0) s(5) d(0)
Residual Adj List for e: j(5) a(0)
Residual Adj List for d: s(5) c(5) g(0)
Residual Adj List for g: t(0) d(5)
Residual Adj List for h: s(0) i(5)
Residual Adj List for b: t(0) i(0) a(5)
Residual Adj List for a: s(5) e(5) b(0)

------------------------
Flow Adj List for j: t(0)
Flow Adj List for t:
Flow Adj List for s: c(5) d(5) h(0) a(5)
Flow Adj List for i: b(0)
Flow Adj List for c: t(5)
Flow Adj List for e: j(0)
Flow Adj List for d: c(0) g(5)
Flow Adj List for g: t(5)
Flow Adj List for h: i(0)
Flow Adj List for b: t(5)
Flow Adj List for a: e(0) b(5)

------------------------
Residual Adj List for s: a(3) b(2)
Residual Adj List for t: c(0) d(0)
Residual Adj List for a: s(0) b(1) c(3) d(4)
Residual Adj List for b: s(0) a(0) d(2)
Residual Adj List for c: t(2) a(0)
Residual Adj List for d: t(3) a(0) b(0)

------------------------
Flow Adj List for s: a(0) b(0)
Flow Adj List for t:
Flow Adj List for a: b(0) c(0) d(0)
Flow Adj List for b: d(0)
Flow Adj List for c: t(0)
Flow Adj List for d: t(0)

Final flow: 15
------------------------
Residual Adj List for s: a(0) b(0)
Residual Adj List for t: c(2) d(3)
Residual Adj List for a: s(3) b(1) c(1) d(3)
Residual Adj List for b: s(2) a(0) d(0)
Residual Adj List for c: t(0) a(2)
Residual Adj List for d: t(0) a(1) b(2)

------------------------
Flow Adj List for s: a(3) b(2)
Flow Adj List for t:
Flow Adj List for a: b(0) c(2) d(1)
Flow Adj List for b: d(2)
Flow Adj List for c: t(2)
Flow Adj List for d: t(3)

Press any key to continue . . .

*/


/* ANSWER KEY:

// CS 2C Assignment #9. Instructor Solution CLIENT
// client file --------------------------------------------------
// FHflowGraph client
// CS 2C Foothill College
#include <iostream>
#include <string>
using namespace std;
#include "FHflowGraph.h"
// --------------- main ---------------
int main()
{
int finalFlow;

// build graph
FHflowGraph<string, int> myG;

myG.addEdge("s","h", 5);
myG.addEdge("h","i", 5);
myG.addEdge("i","b", 5);
myG.addEdge("a","b", 5);
myG.addEdge("s","a", 5);
myG.addEdge("s","c", 5);
myG.addEdge("s","d", 5);
myG.addEdge("a","e", 5);
myG.addEdge("e","j", 5);
myG.addEdge("j","t", 5);
myG.addEdge("d","g", 5);
myG.addEdge("g","t", 5);
myG.addEdge("b","t", 5);
myG.addEdge("c","t", 5);
myG.addEdge("d","c", 5);

// show the original flow graph
myG.showResAdjTable();
myG.showFlowAdjTable();

myG.setStartVert("s");
myG.setEndVert("t");
finalFlow = myG.findMaxFlow();

cout << "Final flow: " << finalFlow << endl;

myG.showResAdjTable();
myG.showFlowAdjTable();

return 0;
}

// CS 2C Assignment #9. Instructor Solution GRAPH TEMPLATE
// include file --------------------------------------------------
// File FHflowGraph.h
// Template definitions for FHflowGraph.
#ifndef FHFLOWGRAPH_H
#define FHFLOWGRAPH_H
#include <limits.h>
#include <utility>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <stack>
#include <functional>
using namespace std;

// CostType is some numeric type that expresses cost of edges
// Object is the non-graph data for a vertex
template <class Object, typename CostType>
class FHflowVertex
{
// internal typedefs to simplify syntax
typedef FHflowVertex<Object, CostType>* VertPtr;
typedef map<VertPtr, CostType> EdgePairList;

public:
static int sortKey;
static stack<int> keyStack;
static enum { SORT_BY_DATA, SORT_BY_DIST } sortType;
static bool setSortType( int whichType );
static void pushSortKey() { keyStack.push(sortKey); }
static void popSortKey() { sortKey = keyStack.top(); keyStack.pop(); };

static int const INFINITY_FH = INT_MAX;  // defined in limits.h
EdgePairList flowAdjList;
EdgePairList resAdjList;
Object data;
CostType dist;
VertPtr nextInPath;

FHflowVertex( const Object & x = Object() );

void addToFlowAdjList(VertPtr neighbor, CostType cost);
void addToResAdjList(VertPtr neighbor, CostType cost);
bool operator<( const FHflowVertex<Object, CostType> & rhs) const;
const FHflowVertex<Object, CostType> & operator=
( const FHflowVertex<Object, CostType> & rhs);
void showFlowAdjList();
void showResAdjList();
};

// static const initializations for Vertex --------------
template <class Object, typename CostType>
int FHflowVertex<Object, CostType>::sortKey
= FHflowVertex<Object, CostType>::SORT_BY_DATA;

template <class Object, typename CostType>
stack<int> FHflowVertex<Object, CostType>::keyStack;
// ------------------------------------------------------

template <class Object, typename CostType>
bool FHflowVertex<Object, CostType>::setSortType( int whichType )
{
switch (whichType)
{
case SORT_BY_DATA:
case SORT_BY_DIST:
sortKey = whichType;
return true;
default:
return false;
}
}

template <class Object, typename CostType>
FHflowVertex<Object, CostType>::FHflowVertex( const Object & x)
: data(x), dist((CostType)0),
nextInPath(NULL)
{
// nothing to do
}

template <class Object, typename CostType>
void FHflowVertex<Object, CostType>::addToFlowAdjList
(FHflowVertex<Object, CostType> *neighbor, CostType cost)
{
flowAdjList[neighbor] = cost;
}

template <class Object, typename CostType>
void FHflowVertex<Object, CostType>::addToResAdjList
(FHflowVertex<Object, CostType> *neighbor, CostType cost)
{
resAdjList[neighbor] = cost;
}


template <class Object, typename CostType>
bool FHflowVertex<Object, CostType>::operator<(
const FHflowVertex<Object, CostType> & rhs) const
{
switch (sortKey)
{
case SORT_BY_DIST:
return (dist < rhs.dist);
case SORT_BY_DATA:
return (data < rhs.data);
default:
return false;
}
}

template <class Object, typename CostType>
const FHflowVertex<Object, CostType> & FHflowVertex<Object, CostType>::operator=(
const FHflowVertex<Object, CostType> & rhs)
{
flowAdjList = rhs.flowAdjList;
resAdjList = rhs.resAdjList;
data = rhs.data;
dist = rhs.dist;
this->nextInResPath = rhs.nextInResPath;
return *this;
}

template <class Object, typename CostType>
void FHflowVertex<Object, CostType>::showFlowAdjList()
{
typename EdgePairList::iterator iter;

cout << "Adj Flow List for " << data << ": ";
for (iter = flowAdjList.begin(); iter != flowAdjList.end(); ++iter)
cout << iter->first->data << "(" << iter->second << ") ";
cout << endl;
}

template <class Object, typename CostType>
void FHflowVertex<Object, CostType>::showResAdjList()
{
typename EdgePairList::iterator iter;

cout << "Adj Res List for " << data << ": ";
for (iter = resAdjList.begin(); iter != resAdjList.end(); ++iter)
cout << iter->first->data << "(" << iter->second << ") ";
cout << endl;
}

template <class Object, typename CostType>
class FHflowGraph
{
// internal typedefs to simplify syntax
typedef FHflowVertex<Object, CostType> Vertex;
typedef FHflowVertex<Object, CostType>* VertPtr;
typedef map<VertPtr, CostType> EdgePairList;
typedef set<VertPtr> VertPtrSet;
typedef set<Vertex> VertexSet;

private:
VertexSet vertexSet;
VertPtrSet vertPtrSet;
VertPtr startVertPtr, endVertPtr;

public:
FHflowGraph ();
void addEdge(const Object &source, const Object &dest, CostType cost);
bool setStartVert(const Object &x);
bool setEndVert(const Object &x);
VertPtr addToVertexSet(const Object & object);
void showFlowAdjTable();
void showResAdjTable();
void clear();

// algorithms
CostType findMaxFlow();

private:
bool establishNextFlowPath();
CostType getLimitingFlowOnResPath();
CostType getCostOfResEdge(VertPtr src, VertPtr dst);
bool addCostToResEdge(VertPtr src, VertPtr dst, CostType cost);
bool addCostToFlowEdge(VertPtr src, VertPtr dst, CostType cost);
bool adjustPathByCost(CostType cost);
VertPtr getVertexWithThisData(const Object & s);

void showRecentResPath();  // for debugging
};

template <class Object, typename CostType>
FHflowGraph<Object, CostType>::FHflowGraph()
: startVertPtr(NULL), endVertPtr(NULL)
{
// nothing else to do
}

template <class Object, typename CostType>
FHflowVertex<Object, CostType>* FHflowGraph<Object, CostType>::addToVertexSet(
const Object & object)
{
pair<typename VertexSet::iterator, bool> retVal;
VertPtr vPtr;

// save sort key for client
Vertex::pushSortKey();
Vertex::setSortType(Vertex::SORT_BY_DATA);

// build and insert vertex int master list
retVal = vertexSet.insert( Vertex(object) );

// get pointer to this vertex and put into vert pointer list
vPtr = (VertPtr)&*retVal.first;
vertPtrSet.insert(vPtr);

Vertex::popSortKey();  // restore client sort key
return vPtr;
}

template <class Object, typename CostType>
void FHflowGraph<Object, CostType>::clear()
{
vertexSet.clear();
vertPtrSet.clear();
startVertPtr = endVertPtr = NULL;
}

template <class Object, typename CostType>
void FHflowGraph<Object, CostType>::addEdge(
const Object &source, const Object &dest, CostType cost )
{
VertPtr src, dst;

// put both source and dest into vertex list(s) if not already there
src = addToVertexSet(source);
dst = addToVertexSet(dest);

// Start flow off at all 0:
src->addToFlowAdjList(dst, (CostType)0);

// res starts off = input graph, plus we add edges in
// reverse direction to back-up if we pick a bad choice
src->addToResAdjList(dst, cost);
dst->addToResAdjList(src, (CostType)0);
}

template <class Object, typename CostType>
bool FHflowGraph<Object, CostType>::setStartVert(const Object &x)
{
startVertPtr = getVertexWithThisData(x);
if (startVertPtr == NULL)
return false;
return true;
}

template <class Object, typename CostType>
bool FHflowGraph<Object, CostType>::setEndVert(const Object &x)
{
endVertPtr = getVertexWithThisData(x);
if (endVertPtr == NULL)
return false;
return true;
}

template <class Object, typename CostType>
void FHflowGraph<Object, CostType>::showResAdjTable()
{
typename VertPtrSet::iterator iter;

cout << "---------- Residual Adjacency Table ---------- \n";
for (iter = vertPtrSet.begin(); iter != vertPtrSet.end(); ++iter)
(*iter)->showResAdjList();
cout << endl;
}

template <class Object, typename CostType>
void FHflowGraph<Object, CostType>::showFlowAdjTable()
{
typename VertPtrSet::iterator iter;

cout << "---------- Flow Adjacency Table ---------- \n";
for (iter = vertPtrSet.begin(); iter != vertPtrSet.end(); ++iter)
(*iter)->showFlowAdjList();
cout << endl;
}

template <class Object, typename CostType>
bool FHflowGraph<Object, CostType>::establishNextFlowPath()
{
typename VertPtrSet::iterator vIter;
typename EdgePairList::iterator edgePrIter;
VertPtr wPtr, vPtr;
CostType costVW;
queue<VertPtr> partiallyProcessedVerts;

if (startVertPtr == NULL || endVertPtr == NULL)
return false;

// initialize the vertex list and place the starting vert in PPV queue
for (vIter = vertPtrSet.begin(); vIter != vertPtrSet.end(); ++vIter)
{
(*vIter)->dist = (CostType)FHflowVertex<Object, CostType>::INFINITY_FH;
(*vIter)->nextInPath = NULL;
}

startVertPtr->dist = (CostType)0;
partiallyProcessedVerts.push( startVertPtr );

// outer dijkstra loop
while( !partiallyProcessedVerts.empty() )
{
vPtr = partiallyProcessedVerts.front();
partiallyProcessedVerts.pop();

// inner loop: for each RES vert adj to v, DECREASE its
// dist to s if you can
for (edgePrIter = vPtr->resAdjList.begin();
edgePrIter != vPtr->resAdjList.end();
edgePrIter++)
{
wPtr = edgePrIter->first;
costVW = edgePrIter->second;

// this is like the edge not being there - we cannot use it
if ( costVW == 0)
continue;
if ( vPtr->dist + costVW < wPtr->dist )
{
wPtr->dist = vPtr->dist + costVW;
wPtr->nextInPath = vPtr;

// if we reached end, we can stop
if (wPtr == endVertPtr)
return true;

// *wPtr now has improved distance, so add wPtr to PPV queue
partiallyProcessedVerts.push(wPtr);
}
}
}
return false;
}

template <class Object, typename CostType>
CostType FHflowGraph<Object, CostType>::findMaxFlow()
{
CostType cost, finalFlow;
typename EdgePairList::iterator iter;

if (startVertPtr == NULL || endVertPtr == NULL)
return (CostType)0;

// outer loop which increases flow using new path each iteration

while ( establishNextFlowPath() )
{
cost = getLimitingFlowOnResPath();

// for debugging
// cout << "Before ---" << endl;
// showResAdjTable();
// showRecentResPath();

if ( !adjustPathByCost(cost) )
break;

// for debugging
// cout << "After ---" << endl;
// showResAdjTable();
}

// get final flow by summing all edges in flow from startVertPtr
finalFlow = 0;
for (iter = startVertPtr->flowAdjList.begin();
iter != startVertPtr->flowAdjList.end(); ++iter)
{
finalFlow += iter->second;
}

return finalFlow;
}

template <class Object, typename CostType>
FHflowVertex<Object, CostType>* FHflowGraph<Object, CostType>::getVertexWithThisData(
const Object & x)
{
typename VertexSet::iterator findResult;
Vertex vert(x);

Vertex::pushSortKey();  // save client sort key
Vertex::setSortType(Vertex::SORT_BY_DATA);
findResult = vertexSet.find(vert);
Vertex::popSortKey();  // restore client value

if ( findResult == vertexSet.end() )
return NULL;
return  (VertPtr)&*findResult;   // address of vertex in set of origs
}

template <class Object, typename CostType>
CostType FHflowGraph<Object, CostType>::getLimitingFlowOnResPath()
{
VertPtr vp;
CostType cost, limitingFlow = (CostType)Vertex::INFINITY_FH;

if (startVertPtr == NULL || endVertPtr == NULL)
return (CostType)0;

for (vp = endVertPtr; vp != startVertPtr; vp = vp->nextInPath)
{
if ( vp->nextInPath == NULL )
return (CostType)0;
cost = getCostOfResEdge(vp->nextInPath, vp);
if (cost < limitingFlow)
limitingFlow = cost;
}

return limitingFlow;
}



-------------------------------------------------------------------------
// -------------------------          -------FOR DEBUGGING --------------
template <class Object, typename CostType>
void FHflowGraph<Object, CostType>::showRecentResPath()
{
VertPtr vp;
stack<VertPtr> pathStack;
CostType cost, limitingFlow = (CostType)Vertex::INFINITY_FH;

if (startVertPtr == NULL || endVertPtr == NULL)
{
cout << "Starting or ending vertices not defined." << endl;
return;
}

for (vp = endVertPtr; vp != startVertPtr; vp = vp->nextInPath)
{
if ( vp->nextInPath == NULL )
{
cout << "No path found to from " << startVertPtr->data
<< " to " << endVertPtr->data  << endl;
return;
}
pathStack.push(vp);
cost = getCostOfResEdge(vp->nextInPath, vp);
if (cost < limitingFlow)
limitingFlow = cost;
}
pathStack.push(vp);

cout << "Limiting cost from " << startVertPtr->data
<< " to " << endVertPtr->data  << ": "
<< limitingFlow << endl;
while (true)
{
vp = pathStack.top();
pathStack.pop();
if ( pathStack.empty() )
{
cout << vp->data << endl;
break;
}
cout << vp->data << " --> ";
}
}
// -----------------------------------------------------------

template <class Object, typename CostType>
CostType FHflowGraph<Object, CostType>::getCostOfResEdge(
   VertPtr src, VertPtr dst)
{
   typename EdgePairList::iterator iter;

   if (src == NULL || dst == NULL)
      return (CostType)0;

   iter = src->resAdjList.find(dst);
   if (iter->first != dst)
      return (CostType)0;
   return iter->second;
}

template <class Object, typename CostType>
bool FHflowGraph<Object, CostType>::addCostToResEdge(
   VertPtr src, VertPtr dst, CostType cost)
{
   typename EdgePairList::iterator iter;

   if (src == NULL || dst == NULL)
      return false;

   iter = src->resAdjList.find(dst);
   if (iter->first != dst)
      return false;
   iter->second += cost;
   return true;
}

template <class Object, typename CostType>
bool FHflowGraph<Object, CostType>::addCostToFlowEdge(
   VertPtr src, VertPtr dst, CostType cost)
{
   typename EdgePairList::iterator iter;

   if (src == NULL || dst == NULL)
      return false;

   iter = src->flowAdjList.find(dst);
   if (iter != src->flowAdjList.end())
   {
      iter->second += abs(cost);
      return true;
   }


   // if we did not find dst in src's adj list, we are reversing
   // flow along this edge  -- subtract it from the edge
   iter = dst->flowAdjList.find(src);
   if (iter != dst->flowAdjList.end())
   {
      iter->second -= cost;
      return true;
   }

   // this happens if there's a big error
   return false;
}

template <class Object, typename CostType>
bool FHflowGraph<Object, CostType>::adjustPathByCost(CostType cost)
{
   VertPtr vp;

   if (startVertPtr == NULL || endVertPtr == NULL || cost <= 0)
      return false;

   for (vp = endVertPtr; vp != startVertPtr; vp = vp->nextInPath)
   {
      if (vp->nextInPath == NULL)
         return false;

      // adjust res paths - remember we are going backwards from end to start
      if (!addCostToResEdge(vp->nextInPath, vp, -cost)) // dec. res path by cost
         return false;
      if (!addCostToResEdge(vp, vp->nextInPath, cost)) // inc. undo path by cost
         return false;
      if (!addCostToFlowEdge(vp->nextInPath, vp, cost)) // add to flow graph
         return false;
   }

   return true;
}

#endif



--------- output -----------
---------- Residual Adjacency Table ----------
Adj Res List for s: h(5) a(5) c(5) d(5)
Adj Res List for h: s(0) i(5)
Adj Res List for i: h(0) b(5)
Adj Res List for b: i(0) a(0) t(5)
Adj Res List for a: s(0) b(5) e(5)
Adj Res List for c: s(0) d(0) t(5)
Adj Res List for d: s(0) c(5) g(5)
Adj Res List for e: a(0) j(5)
Adj Res List for j: e(0) t(5)
Adj Res List for t: b(0) c(0) j(0) g(0)
Adj Res List for g: d(0) t(5)

---------- Flow Adjacency Table ----------
Adj Flow List for s: h(0) a(0) c(0) d(0)
Adj Flow List for h: i(0)
Adj Flow List for i: b(0)
Adj Flow List for b: t(0)
Adj Flow List for a: b(0) e(0)
Adj Flow List for c: t(0)
Adj Flow List for d: c(0) g(0)
Adj Flow List for e: j(0)
Adj Flow List for j: t(0)
Adj Flow List for t:
Adj Flow List for g: t(0)

Final flow: 20
---------- Residual Adjacency Table ----------
Adj Res List for s: h(0) a(0) c(0) d(0)
Adj Res List for h: s(5) i(0)
Adj Res List for i: h(5) b(0)
Adj Res List for b: i(5) a(0) t(0)
Adj Res List for a: s(5) b(5) e(0)
Adj Res List for c: s(5) d(0) t(0)
Adj Res List for d: s(5) c(5) g(0)
Adj Res List for e: a(5) j(0)
Adj Res List for j: e(5) t(0)
Adj Res List for t: b(5) c(5) j(5) g(5)
Adj Res List for g: d(5) t(0)

---------- Flow Adjacency Table ----------
Adj Flow List for s: h(5) a(5) c(5) d(5)
Adj Flow List for h: i(5)
Adj Flow List for i: b(5)
Adj Flow List for b: t(5)
Adj Flow List for a: b(0) e(5)
Adj Flow List for c: t(5)
Adj Flow List for d: c(0) g(5)
Adj Flow List for e: j(5)
Adj Flow List for j: t(5)
Adj Flow List for t:
Adj Flow List for g: t(5)

Press any key to continue . . .
-----------------------------

*/
