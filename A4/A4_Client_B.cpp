#include <iostream>
#include <string>
#include <stack>
#include "FHlazySearchTree.h"
#include "EBookEntry.h"
#include "Foothill_Sort.h"
using namespace std;

template <typename Object>
class PrintObject
{
public:
   void operator()(Object obj)
   {
      cout << "   # " << obj.getETextNum() << "  ---------------" << endl;
      cout << "   \"" << obj.getTitle() << "\"" << endl;
      cout << "   by " << obj.getCreator() << endl;
      cout << "   re: " << obj.getSubject() << endl << endl;
   }
};

void displayOneEBook(EBookEntry book);

int main()
{
   // EBOOK CLIENT FOR PART B
   int k, arraySize;
   FHlazySearchTree<EBookEntry> ebookBST;
   PrintObject<EBookEntry> ebookPrinter;

   // how we read the data from files
   EBookEntryReader bookInput("catalog-short4.txt");

   // how we test the success of the read:
   if (bookInput.readError())
   {
      cout << "couldn't open " << bookInput.getFileName() << " for input.\n";
      exit(1);
   }

   cout << bookInput.getFileName() << endl;
   cout << bookInput.getNumBooks() << endl;

   // create an array of objects for our own use:
   arraySize = bookInput.getNumBooks();
   EBookEntry *bookArray = new EBookEntry[arraySize];
   for (k = 0; k < arraySize; k++)
      bookArray[k] = bookInput[k];

   // set sort type:
   EBookEntry::setSortType(EBookEntry::SORT_BY_TITLE);

   // now what you came here for
   cout << "\n\ninitial traversal and display:" << endl;
   ebookBST.traverse(ebookPrinter);

   cout << "testing findMin/Max on hard-empty tree:" << endl;
   try
   {
      cout << "Min:\n";
      displayOneEBook(ebookBST.findMin());
      cout << "\nMax:\n";
      displayOneEBook(ebookBST.findMax());
   }
   catch (FHlazySearchTree<EBookEntry>::EmptyTreeException)
   {
      cout << "oops - empty tree" << endl;
   }

   // insert first 8 books
   cout << "\ninitial size: " << ebookBST.size() << endl;
   for (int k = 0; k < 6; k++)
      ebookBST.insert(bookArray[k]);

   cout << "After populating -- traversal and new sizes: \n";
   ebookBST.traverse(ebookPrinter);
   cout << "\ntree size: " << ebookBST.size()
      << "  Hard size: " << ebookBST.sizeHard() << endl;

   cout << "Collecting garbage on new tree - should be no garbage." << endl;
   ebookBST.collectGarbage();
   cout << "tree size: " << ebookBST.size()
      << "  Hard size: " << ebookBST.sizeHard() << endl;

   // test assignment operator
   FHlazySearchTree<EBookEntry> e2 = ebookBST;

   cout << "\n\nAttempting 1 removal: \n";
   if (ebookBST.remove(bookArray[3]))
      cout << "removed " << 20 << endl;
   cout << "tree size: " << ebookBST.size()
      << "  Hard size: " << ebookBST.sizeHard() << endl;

   cout << "Collecting Garbage - should clean 1 item. " << endl;
   ebookBST.collectGarbage();
   cout << "tree size: " << ebookBST.size()
      << "  Hard size: " << ebookBST.sizeHard() << endl;

   cout << "Collecting Garbage again - no change expected. " << endl;
   ebookBST.collectGarbage();
   cout << "tree size: " << ebookBST.size()
      << "  Hard size: " << ebookBST.sizeHard() << endl;

   // test soft insertion and deletion:

   cout << "Adding 'hard' 22 - should see new sizes. " << endl;
   ebookBST.insert(bookArray[6]);
   ebookBST.traverse(ebookPrinter);
   cout << "\ntree size: " << ebookBST.size()
      << "  Hard size: " << ebookBST.sizeHard() << endl;

   cout << "\nAfter soft removal. " << endl;
   ebookBST.remove(bookArray[6]);
   ebookBST.traverse(ebookPrinter);
   cout << "\ntree size: " << ebookBST.size()
      << "  Hard size: " << ebookBST.sizeHard() << endl;

   cout << "Repeating soft removal. Should see no change. " << endl;
   ebookBST.remove(bookArray[6]);
   ebookBST.traverse(ebookPrinter);
   cout << "\ntree size: " << ebookBST.size()
      << "  Hard size: " << ebookBST.sizeHard() << endl;

   cout << "Soft insertion. Hard size should not change. " << endl;
   ebookBST.insert(bookArray[6]);
   ebookBST.traverse(ebookPrinter);
   cout << "\ntree size: " << ebookBST.size()
      << "  Hard size: " << ebookBST.sizeHard() << endl;

   cout << "\n\nRemoving half the nodes: \n";
   for (k = 0; k < 8; k+=2)
   {
      if (ebookBST.remove(bookArray[k]))
         cout << "removed " << k << endl;
   }

   cout << "\ntree size: " << ebookBST.size()
      << "  Hard size: " << ebookBST.sizeHard() << endl;
   cout << "\ntesting findMin/Max on partially-empty tree:" << endl;
   try
   {
      cout << "Min:\n";
      displayOneEBook(ebookBST.findMin());
      cout << "\nMax:\n";
      displayOneEBook(ebookBST.findMax());
   }
   catch (FHlazySearchTree<EBookEntry>::EmptyTreeException)
   {
      cout << "oops - empty tree" << endl;
   }

   cout << "\n\nRemoving rest of the nodes: \n";
   for (k = 1; k < 9; k += 2)
   {
      if (ebookBST.remove(bookArray[k]))
         cout << "removed " << k << endl;
   }

   cout << "\ntree size: " << ebookBST.size()
      << "  Hard size: " << ebookBST.sizeHard() << endl;
   cout << "\ntesting findMin/Max on soft-empty tree:" << endl;
   try
   {
      cout << "Min:\n";
      displayOneEBook(ebookBST.findMin());
      cout << "\nMax:\n";
      displayOneEBook(ebookBST.findMax());
   }
   catch (FHlazySearchTree<EBookEntry>::EmptyTreeException)
   {
      cout << "oops - empty tree" << endl;
   }

   ebookBST.collectGarbage();
   cout << "\nebookBST after garbage collection:\n";
   ebookBST.traverse(ebookPrinter);
   cout << "\ntree size: " << ebookBST.size()
      << "  Hard size: " << ebookBST.sizeHard() << endl;

   cout << "\n\ne2 traversal:\n";
   e2.traverse(ebookPrinter);

   delete[] bookArray;

return 0;
}

void displayOneEBook(EBookEntry book)
{
   cout << "   # " << book.getETextNum() << "  ---------------" << endl;
   cout << "   \"" << book.getTitle() << "\"" << endl;
   cout << "   by " << book.getCreator() << endl;
   cout << "   re: " << book.getSubject() << endl << endl;
}

/* Assignment 4 Part B Program Output:

------------------Single Run------------------

catalog-short4.txt
4863


initial traversal and display:
testing findMin/Max on hard-empty tree:
Min:
oops - empty tree

initial size: 0
After populating -- traversal and new sizes:
# 28546  ---------------
"A History of England Principally in the Seventeenth Century, Volume I (of 6)
"
by Ranke, Leopold von, 1795-1886
re: Great Britain -- History -- Stuarts, 1603-1714

# 28805  ---------------
"Dorothy's House Party"
by Raymond, Evelyn, 1843-1910
re: Orphans -- Juvenile fiction

# 30170  ---------------
"Lonesome Hearts"
by Winterbotham, R. R. (Russell Robert), 1904-1971
re: Science fiction

# 28711  ---------------
"Operas Every Child Should KnowDescriptions of the Text and Music of Some of
the Most Famous Masterpieces"
by Bacon, Mary Schell Hoke, 1870-1934
re: Operas -- Stories, plots, etc.

# 30169  ---------------
"The Story of the White Mouse"
by Unknown
re: Conduct of life -- Juvenile fiction

# 28547  ---------------
"The Words of Jesus"
by Macduff, John R. (John Ross), 1818-1895
re: Devotional exercises


tree size: 6  Hard size: 6
Collecting garbage on new tree - should be no garbage.
tree size: 6  Hard size: 6


Attempting 1 removal:
removed 20
tree size: 5  Hard size: 6
Collecting Garbage - should clean 1 item.
tree size: 5  Hard size: 5
Collecting Garbage again - no change expected.
tree size: 5  Hard size: 5
Adding 'hard' 22 - should see new sizes.
# 28546  ---------------
"A History of England Principally in the Seventeenth Century, Volume I (of 6)
"
by Ranke, Leopold von, 1795-1886
re: Great Britain -- History -- Stuarts, 1603-1714

# 30168  ---------------
"A History of Giggleswick SchoolFrom its Foundation, 1499 to 1912"
by Bell, Edward Allen
re: Giggleswick School (Giggleswick, England) -- History

# 28805  ---------------
"Dorothy's House Party"
by Raymond, Evelyn, 1843-1910
re: Orphans -- Juvenile fiction

# 30170  ---------------
"Lonesome Hearts"
by Winterbotham, R. R. (Russell Robert), 1904-1971
re: Science fiction

# 30169  ---------------
"The Story of the White Mouse"
by Unknown
re: Conduct of life -- Juvenile fiction

# 28547  ---------------
"The Words of Jesus"
by Macduff, John R. (John Ross), 1818-1895
re: Devotional exercises


tree size: 6  Hard size: 6

After soft removal.
# 28546  ---------------
"A History of England Principally in the Seventeenth Century, Volume I (of 6)
"
by Ranke, Leopold von, 1795-1886
re: Great Britain -- History -- Stuarts, 1603-1714

# 28805  ---------------
"Dorothy's House Party"
by Raymond, Evelyn, 1843-1910
re: Orphans -- Juvenile fiction

# 30170  ---------------
"Lonesome Hearts"
by Winterbotham, R. R. (Russell Robert), 1904-1971
re: Science fiction

# 30169  ---------------
"The Story of the White Mouse"
by Unknown
re: Conduct of life -- Juvenile fiction

# 28547  ---------------
"The Words of Jesus"
by Macduff, John R. (John Ross), 1818-1895
re: Devotional exercises


tree size: 5  Hard size: 6
Repeating soft removal. Should see no change.
# 28546  ---------------
"A History of England Principally in the Seventeenth Century, Volume I (of 6)
"
by Ranke, Leopold von, 1795-1886
re: Great Britain -- History -- Stuarts, 1603-1714

# 28805  ---------------
"Dorothy's House Party"
by Raymond, Evelyn, 1843-1910
re: Orphans -- Juvenile fiction

# 30170  ---------------
"Lonesome Hearts"
by Winterbotham, R. R. (Russell Robert), 1904-1971
re: Science fiction

# 30169  ---------------
"The Story of the White Mouse"
by Unknown
re: Conduct of life -- Juvenile fiction

# 28547  ---------------
"The Words of Jesus"
by Macduff, John R. (John Ross), 1818-1895
re: Devotional exercises


tree size: 5  Hard size: 6
Soft insertion. Hard size should not change.
# 28546  ---------------
"A History of England Principally in the Seventeenth Century, Volume I (of 6)
"
by Ranke, Leopold von, 1795-1886
re: Great Britain -- History -- Stuarts, 1603-1714

# 30168  ---------------
"A History of Giggleswick SchoolFrom its Foundation, 1499 to 1912"
by Bell, Edward Allen
re: Giggleswick School (Giggleswick, England) -- History

# 28805  ---------------
"Dorothy's House Party"
by Raymond, Evelyn, 1843-1910
re: Orphans -- Juvenile fiction

# 30170  ---------------
"Lonesome Hearts"
by Winterbotham, R. R. (Russell Robert), 1904-1971
re: Science fiction

# 30169  ---------------
"The Story of the White Mouse"
by Unknown
re: Conduct of life -- Juvenile fiction

# 28547  ---------------
"The Words of Jesus"
by Macduff, John R. (John Ross), 1818-1895
re: Devotional exercises


tree size: 6  Hard size: 6


Removing half the nodes:
removed 0
removed 2
removed 4
removed 6

tree size: 2  Hard size: 6

testing findMin/Max on partially-empty tree:
Min:
# 30169  ---------------
"The Story of the White Mouse"
by Unknown
re: Conduct of life -- Juvenile fiction


Max:
# 28547  ---------------
"The Words of Jesus"
by Macduff, John R. (John Ross), 1818-1895
re: Devotional exercises



Removing rest of the nodes:
removed 1
removed 5

tree size: 0  Hard size: 6

testing findMin/Max on soft-empty tree:
Min:
oops - empty tree

ebookBST after garbage collection:

tree size: 0  Hard size: 0


e2 traversal:
# 28546  ---------------
"A History of England Principally in the Seventeenth Century, Volume I (of 6)
"
by Ranke, Leopold von, 1795-1886
re: Great Britain -- History -- Stuarts, 1603-1714

# 28805  ---------------
"Dorothy's House Party"
by Raymond, Evelyn, 1843-1910
re: Orphans -- Juvenile fiction

# 30170  ---------------
"Lonesome Hearts"
by Winterbotham, R. R. (Russell Robert), 1904-1971
re: Science fiction

# 28711  ---------------
"Operas Every Child Should KnowDescriptions of the Text and Music of Some of
the Most Famous Masterpieces"
by Bacon, Mary Schell Hoke, 1870-1934
re: Operas -- Stories, plots, etc.

# 30169  ---------------
"The Story of the White Mouse"
by Unknown
re: Conduct of life -- Juvenile fiction

# 28547  ---------------
"The Words of Jesus"
by Macduff, John R. (John Ross), 1818-1895
re: Devotional exercises

Press any key to continue . . .

*/