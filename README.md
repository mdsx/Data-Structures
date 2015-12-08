# C++ Data Structures Files

This file contains folders associated with programming assignments completed for a C++ Data Structures course taken at Foothill College.  The class was taught by Professor Michael Loceff in the Spring 2015 quarter.

Projects cover the main topics  of ADTs:
  - lists, vectors, sparse matrices
  - time complexity of algorithms
  - trees: general, binary search tree, AVL tree, splay tree
  - hashing tables, queues
  - implementations of quick sort among other sorting algorithms (and searching algorithms)
  - graphs: implemented using STL maps & sets; programs solve problems such as shortest path, minimum spanning tree, maximum flow, etc.

Write-ups & program output can be found in the comments below the main() of the client file for any given assignment.  Some projects involve analysis of ADT's & algorithms while others are mostly implementations of ADT's.  Many of the computations involved have been timed, with some algorithms anyalyzed for time-complexity.  Below you will find brief descriptions of each assignment:


A1: view A1_templateClient.cpp

A1 is an implementation of the subset-sum algorithm.  Given a target that is less than the sum of all the values in a data set (first part is for iTunesEntries objects, second part is for integers), the algorithm keeps adding values from the original data set to a set of choices as long as the total value of a choice doesn't exceed the target.  Once all subsets are considered, the choice with the largest sum is chosen.  If a choice happened to exactly meet the target while considering all the subsets, the loop would break since that would be the solution.  The algorithm is timed for both parts.


A2: view A2_Client.cpp

A2 is an implementation of a Sparse Matrix class as a list of vectors.  The class includes a constructor, destructor, accessor, mutator, & a print sub-square function.  All of these functions are tested in the client, as can be seen in the comments below the main() of the client.


A3: view A3_ClientA.cpp

A3 is mainly an implementation of dynamic matrix multiplication.  A dynamic matrix is initialized as dynamic 2-D array (ie an array of arrays of floats) and the matrix is partially populated at random indices to some non-zero value.  The matrix multiplication algorithm is then timed & tested in the client; output is found in the comments below.

A4: view A4_ClientA.cpp & FHlazySearchTree.h

A4 implements lazy deletion in a binary search tree.  The functions commented "revised" in the FHlazySearchTree function prototypes were altered from the more general FHsearch_tree.h found in the CS-2C-Template-Files repository in order to implement lazy deletion.  The client files runs tests on a FHlazySearchTree to present the values of the search tree's defining parameters at various stages.  These tests demonstrate the implementation of soft deletion, hard deletion, & garbage collection in the lazy search tree.


A5: view A5_Client.cpp & FHsplayTree.h

A5 implements a binary top-down splay tree as a decendent of the binary search tree found in FHsearch_tree.h.  The public functions of this class revolve around the protected function splay() which makes use of the helper functions rotateWithLeftChild() & rotateWithRightChild().  The goal of top-down splaying is to "splay" for some value, ie move the node with the value closest to some target to the root of the tree.  The value of nodes in the splay tree is a comparable data type, and the tree is organized by the rule which says that lesser items go on the left and greater items go on the right.  With this in mind, the splay() algorithm uses rotations to re-shuffle the tree biased towards the splay value.  insert() & remove() work by splay()'ing for the target value and then inserting / removing a node and reorganizing the tree accordingly.  Likewise, contains() & finds() work by first splay()'ing for a target value then returning the appropriate answer by evaluating the value at the new root.


A6: view A6_Client.cpp & FHhashQPwFind.h

A6 implements a quadratic-probing hash table with a find() function as a decendent of the hash table found in FHhashQP.h.  find() searches for a hash entry in a table by hashing for a key.  The Hash() function is defined by the client and has different implementations for parameters of different data types.  insert() in the original FHhashQP.h calls the version of Hash() that operates on EBookEntry objects.  Then that Hash() passes the EBookEntry key to either the Hash() which operates on integers or the Hash() which operates on strings; depending on the key's data type.  On the other hand, when find() in FHhashQPwFind.h along with its helpers findPosKey() & myHashKey() call Hash(), they pass the key as the parameter so only the Hash() implementations which take a key as input are called.  It should be noted that findPosKey() also accounts for the quadratic probing done to avoid collisions (hash entries with equivalent keys cannot occupy the same index, so they are spaced apart).


A7: view A7_Client.cpp

A7 analyzes the effects of varying gap sequences on the Shell Sort Algorithm.  shellSort() works by running insertionSort() multiple times -- each time only the elements of an array separated by some gap are sorted; the gap values continue to shrink according to some gap sequence until a pure insertionSort() is run thus completing the sort.  Further details can be found in the comments below the main() function of the client.


A8: view A8_Client.cpp

A8 is a thourough analysis of quickSort() and how its sorting time varies with attributes of an array -- size, population, etc.  quickSort() works by choosing a "pivot" element and then putting all the elements greater than it on its right and all the elements less than it on its left.  Next, quickSort() recurses for both the left & right parts of the array relative to the pivot).  Recursion continues until the entire array is sorted.  Further details can be found in the comments below the main() function of the client.


A9:


A10 (Extra Credit): view A10_Client.cpp

A10 implements a class called SNE_Analyzer which is derived from the base class StarNearEarth found in StarNearEarth.h.  StarNearEarth objects represent stars, and their positions are stored as their right ascension & declination relative to our Sun.  The SNE_Analyzer


