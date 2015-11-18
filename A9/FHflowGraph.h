/*----------------------------------------------------------------------------*/
// File FHflowGraph.h EXPERIMENT
// Template definitions for FHflowGraph
#ifndef FHFLOWGRAPH_H
#define FHFLOWGRAPH_H

#include <limits.h>
#include <utility>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <stack>
#include <iostream>
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
   static int nSortKey;
   static stack<int> keyStack;
   static enum { SORT_BY_DATA, SORT_BY_DIST } eSortType;
   static bool setNSortType(int whichType);
   static void pushSortKey() { keyStack.push(nSortKey); }
   static void popSortKey() { nSortKey = keyStack.top(); keyStack.pop(); }

   static int const INFINITY_FH = INT_MAX;  // defined in limits.h
   EdgePairList flowAdjList, resAdjList;
   Object data;
   CostType dist;
   VertPtr nextInPath;  // used for client-specific info

   FHflowVertex(const Object & x = Object());

   void addToFlowAdjList(VertPtr neighbor, CostType cost); // added
   void addToResAdjList(VertPtr neighbor, CostType cost); // added
   bool operator<(const FHflowVertex<Object, CostType> & rhs) const;
   const FHflowVertex<Object, CostType> & operator=
      (const FHflowVertex<Object, CostType> & rhs);
   void showFlowAdjList(); // added
   void showResAdjList(); // added
};

// static const initializations for Vertex --------------
template <class Object, typename CostType>
int FHflowVertex<Object, CostType>::nSortKey
= FHflowVertex<Object, CostType>::SORT_BY_DATA;

template <class Object, typename CostType>
stack<int> FHflowVertex<Object, CostType>::keyStack;
// ------------------------------------------------------

template <class Object, typename CostType>
bool FHflowVertex<Object, CostType>::setNSortType(int whichType)
{
   switch (whichType)
   {
   case SORT_BY_DATA:
   case SORT_BY_DIST:
      nSortKey = whichType;
      return true;
   default:
      return false;
   }
}

template <class Object, typename CostType>
FHflowVertex<Object, CostType>::FHflowVertex(const Object & x)
   : data(x), dist((CostType)INFINITY_FH),
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
   switch (nSortKey)
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
const FHflowVertex<Object, CostType> & FHflowVertex<Object, CostType>::operator=
   (const FHflowVertex<Object, CostType> & rhs)
{
   flowAdjList = rhs.flowAdjList;
   resAdjList = rhs.resAdjList;
   data = rhs.data;
   dist = rhs.dist;
   nextInPath = rhs.nextInPath;;
   return *this;
}

template <class Object, typename CostType>
void FHflowVertex<Object, CostType>::showFlowAdjList()
{
   typename EdgePairList::iterator iter;

   cout << "Flow Adj List for " << data << ": ";
   for (iter = flowAdjList.begin(); iter != flowAdjList.end(); ++iter)
      cout << iter->first->data << "(" << iter->second << ") ";
   cout << endl;
}

template <class Object, typename CostType>
void FHflowVertex<Object, CostType>::showResAdjList()
{
   typename EdgePairList::iterator iter;

   cout << "Residual Adj List for " << data << ": ";
   for (iter = resAdjList.begin(); iter != resAdjList.end(); ++iter)
      cout << iter->first->data << "(" << iter->second << ") ";
   cout << endl;
}

// FHedge removed

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
   VertPtrSet vertPtrSet;
   VertexSet vertexSet;
   VertPtr startVertPtr, endVertPtr; // added

public:
   FHflowGraph(); // modified
   void addEdge(const Object &source, const Object &dest, CostType cost); // mod
   VertPtr addToVertexSet(const Object & object);
   void showFlowAdjTable(); // added
   void showResAdjTable(); // added
   void clear();
   bool setStartVert(const Object &x); // added
   bool setEndVert(const Object &x); // added

   // algorithms
   CostType findMaxFlow();

private:
   VertPtr getVertexWithThisData(const Object & x);

   // private helpers
   bool establishNextFlowPath();
   CostType getLimitingFlowOnResPath();
   bool adjustPathByCost(CostType cost);
   CostType getCostOfResEdge(VertPtr src, VertPtr dst);
   bool addCostToResEdge(VertPtr src, VertPtr dst, CostType cost);
   bool addCostToFlowEdge(VertPtr src, VertPtr dst, CostType cost);
};

template <class Object, typename CostType>
FHflowGraph<Object, CostType>::FHflowGraph()
   : startVertPtr(NULL), endVertPtr(NULL)
{
}

template <class Object, typename CostType>
bool FHflowGraph<Object, CostType>::setStartVert(const Object &x)
{
   startVertPtr = getVertexWithThisData(x);
   return (startVertPtr != NULL);
}

template <class Object, typename CostType>
bool FHflowGraph<Object, CostType>::setEndVert(const Object &x)
{
   endVertPtr = getVertexWithThisData(x);
   return (endVertPtr != NULL);
}

template <class Object, typename CostType>
FHflowVertex<Object, CostType>* FHflowGraph<Object, CostType>::addToVertexSet(
   const Object & object)
{
   pair<typename VertexSet::iterator, bool> retVal;
   VertPtr vPtr;

   // save sort key for client
   Vertex::pushSortKey();
   Vertex::setNSortType(Vertex::SORT_BY_DATA);

   // build and insert vertex into master list
   retVal = vertexSet.insert(Vertex(object));

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
}

template <class Object, typename CostType>
void FHflowGraph<Object, CostType>::addEdge(
   const Object &source, const Object &dest, CostType cost)
{
   VertPtr src, dst;

   // put both source and dest into vertex list(s) if not already there
   src = addToVertexSet(source);
   dst = addToVertexSet(dest);

   // add forward edge to res. adj. list normally, add reverse edge w/ cost = 0
   // to res. adj. list, add forward edge to flow adj. list w/ cost = 0
   src->addToResAdjList(dst, cost);
   dst->addToResAdjList(src, 0);
   src->addToFlowAdjList(dst, 0);
}

template <class Object, typename CostType>
void FHflowGraph<Object, CostType>::showFlowAdjTable()
{
   typename VertPtrSet::iterator iter;

   cout << "------------------------ \n";
   for (iter = vertPtrSet.begin(); iter != vertPtrSet.end(); ++iter)
      (*iter)->showFlowAdjList();
   cout << endl;
}

template <class Object, typename CostType>
void FHflowGraph<Object, CostType>::showResAdjTable()
{
   typename VertPtrSet::iterator iter;

   cout << "------------------------ \n";
   for (iter = vertPtrSet.begin(); iter != vertPtrSet.end(); ++iter)
      (*iter)->showResAdjList();
   cout << endl;
}

template <class Object, typename CostType>
FHflowVertex<Object, CostType>* FHflowGraph<Object, CostType>::
getVertexWithThisData(const Object & x)
{
   typename VertexSet::iterator findResult;
   Vertex vert(x);

   Vertex::pushSortKey();  // save client sort key
   Vertex::setNSortType(Vertex::SORT_BY_DATA);
   findResult = vertexSet.find(vert);
   Vertex::popSortKey();  // restore client value

   if (findResult == vertexSet.end())
      return NULL;
   return (VertPtr)&*findResult; // address of vertex in the set of originals
}

template <class Object, typename CostType>
CostType FHflowGraph<Object, CostType>::findMaxFlow()
{
   bool pathExists = true;
   CostType minCost, totalCost;
   typename VertPtrSet::iterator vIter;
   typename EdgePairList::iterator edgePrIter;

   while (pathExists)
   {
      pathExists = establishNextFlowPath();
      if (!pathExists)
         break;

      minCost = getLimitingFlowOnResPath();
      adjustPathByCost(minCost);
   }

   totalCost = 0;
   for (vIter = vertPtrSet.begin(); vIter != vertPtrSet.end(); ++vIter)
   {
      for (edgePrIter = (*vIter)->flowAdjList.begin();
         edgePrIter != (*vIter)->flowAdjList.end();
         ++edgePrIter)
      {
         totalCost += edgePrIter->second;
      }
   }

   return totalCost;
}

template <class Object, typename CostType>
bool FHflowGraph<Object, CostType>::establishNextFlowPath()
{
   // new algorithm based off Dijkstra
   typename VertPtrSet::iterator vIter;
   typename EdgePairList::iterator edgePrIter;
   VertPtr wPtr, vPtr;
   CostType costVW;
   queue<VertPtr> partiallyProcessedVerts;

   endVertPtr->nextInPath = NULL;

   if (startVertPtr == NULL)
      return false;

   // initialize the vertex list and place the starting vert in p_p_v queue
   for (vIter = vertPtrSet.begin(); vIter != vertPtrSet.end(); ++vIter)
   {
      (*vIter)->dist = Vertex::INFINITY_FH;
      (*vIter)->nextInPath = NULL;
   }

   startVertPtr->dist = 0;
   partiallyProcessedVerts.push(startVertPtr); // or, FHbinHeap::insert(), e.g.

   // outer dijkstra loop
   while (!partiallyProcessedVerts.empty())
   {
      vPtr = partiallyProcessedVerts.front();
      partiallyProcessedVerts.pop();

      // inner dijkstra loop, iterating through the residual graph's adj list
      for (edgePrIter = vPtr->resAdjList.begin();
         edgePrIter != vPtr->resAdjList.end();
         edgePrIter++)
      {
         wPtr = edgePrIter->first;
         costVW = edgePrIter->second;

         if (vPtr->dist + costVW < wPtr->dist && costVW != 0)
         {
            wPtr->dist = vPtr->dist + costVW;
            wPtr->nextInPath = vPtr;

            // *wPtr now has improved distance, so add wPtr to p_p_v queue
            partiallyProcessedVerts.push(wPtr);
         }

         if (wPtr == endVertPtr)
            break;
      }
   }

   return !(endVertPtr->nextInPath == NULL); // if no path exists return false
}

template <class Object, typename CostType>
CostType FHflowGraph<Object, CostType>::getLimitingFlowOnResPath()
{
   CostType minimumCost, tempCost;
   VertPtr vp;

   minimumCost = getCostOfResEdge(endVertPtr->nextInPath, endVertPtr);
   for (vp = endVertPtr; vp != startVertPtr; vp = vp->nextInPath)
   {
      tempCost = getCostOfResEdge(vp->nextInPath, vp);
      if (tempCost < minimumCost)
         minimumCost = tempCost;
   }

   return minimumCost;
}

template <class Object, typename CostType>
bool FHflowGraph<Object, CostType>::adjustPathByCost(CostType cost)
{
   VertPtr vp;

   for (vp = endVertPtr; vp != startVertPtr; vp = vp->nextInPath)
   {
      addCostToResEdge(vp->nextInPath, vp, -cost);
      addCostToResEdge(vp, vp->nextInPath, cost);
      addCostToFlowEdge(vp->nextInPath, vp, cost);
   }
   return true;
}

template <class Object, typename CostType>
CostType FHflowGraph<Object, CostType>::getCostOfResEdge(
   VertPtr src, VertPtr dst)
{
   return src->resAdjList[dst];
}

template <class Object, typename CostType>
bool FHflowGraph<Object, CostType>::addCostToResEdge(
   VertPtr src, VertPtr dst, CostType cost)
{
   if (src == NULL || dst == NULL)
      return false;

   src->resAdjList[dst] += cost;
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
      src->flowAdjList[dst] += cost;
   else
      src->flowAdjList[dst] -= cost;

   return true;
}

#endif