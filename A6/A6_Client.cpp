#include <iostream>
#include <ctime>
#include <cstdlib>
#include "FHhashQPwFind .h"
#include "EBookEntry.h"
using namespace std;

#define NUM_RAND_INDICES 25

// declarations of hashing functions for client use
int Hash(int key);
int Hash(const string & key);
int Hash(const EBookEntry & item);

// key accessors
int getKey(const EBookEntry & item);
// string getKey( const EBookEntry & item);

void displayOneEBook(EBookEntry book);

int main()
{
   int k, arraySize;
   EBookEntry book;
   
   FHhashQPwFind<EBookEntry, int> hashTable; // for ID equality
   // FHhashQPwFind<EBookEntry, string> hashTable; // for any string equality

   // read data from files
   EBookEntryReader bookInput("catalog-short4.txt");

   // test whether read was successful
   if (bookInput.readError())
   {
      cout << "couldn't open " << bookInput.getFileName() << " for input.\n";
      exit(1);
   }

   // we want two books to be identical in different ways:  ID or author
   EBookEntry::setSortType(EBookEntry::SORT_BY_ID);
   // EBookEntry::setSortType(EBookEntry::SORT_BY_CREATOR);

   cout << "Books from: " << bookInput.getFileName() << endl;
   cout << "# of books: " << bookInput.getNumBooks() << endl;

   // create array of random ebooks
   arraySize = bookInput.getNumBooks();
   srand(time(NULL));
   EBookEntry *bookArray = new EBookEntry[NUM_RAND_INDICES];
   for (k = 0; k < NUM_RAND_INDICES; k++)
      bookArray[k] = bookInput[rand() % arraySize];

   // insert all books into hash table
   for (k = 0; k < arraySize; k++)
       hashTable.insert(bookInput[k]);

   // display all 25 books (only EBook # and author)
   cout << "First, all the random books in the array:" << endl;
   for (int k = 0; k < NUM_RAND_INDICES; k++)
   {
      cout << "   # " << bookArray[k].getETextNum() << endl;
      cout << "   by " << bookArray[k].getCreator() << endl;
   }

   // attempt to find on the selected key
   cout << "\n\nNow the same random books from the hash table:" << endl;
   for (int k = 0; k < NUM_RAND_INDICES; k++)
   {
      try
      {
         book = hashTable.find(bookArray[k].getETextNum());
         // book = hashTable.find(bookArray[k].getCreator() );

         displayOneEBook(book);
      }
      catch (...)
      {
         cout << "not found.  ";
      }
      cout << endl;
   }

   cout << "Next three find() calls should throw exceptions:" << endl;
   // test known failures exceptions:
   try
   {
      book = hashTable.find(-3);
      // book = hashTable.find( "Jack Kerouac" );

      displayOneEBook(book);
   }
   catch (...)
   {
      cout << "not found.  ";
   }

   // more failures
   try
   {
      book = hashTable.find(5001);
      // book = hashTable.find( "David Foster Wallace" );

      displayOneEBook(book);
   }
   catch (...)
   {
      cout << "not found.  ";
   }

   try
   {
      book = hashTable.find(107);
      // book = hashTable.find( "Haruki Murakami" );

      displayOneEBook(book);
   }
   catch (...)
   {
      cout << "not found.  ";
   }

   cout << "\n\nAfter 25 remove() calls on the hash table,";
   for (k = 0; k < NUM_RAND_INDICES; k++)
      hashTable.remove(bookArray[k]);

   cout << "we attempt 25 find() calls once more:" << endl;
   for (int k = 0; k < NUM_RAND_INDICES; k++)
   {
      try
      {
         book = hashTable.find(bookArray[k].getETextNum());
         // book = hashTable.find(bookArray[k].getCreator() );

         displayOneEBook(book);
      }
      catch (...)
      {
         cout << "not found.  ";
      }
      cout << endl;
   }

   delete [] bookArray;
   return 0;
}

// hasing function implementations
int Hash(int key)
{
   return key;
}

int Hash(const string & key)
{
   unsigned int k, retVal = 0;

   for (k = 0; k < key.length(); k++)
      retVal = 37 * retVal + key[k];

   return retVal;
}

int Hash(const EBookEntry & item)
{
   return Hash(item.getETextNum());
   // return Hash(item.getCreator());
}


// used for ID equality
int getKey(const EBookEntry & item)
{
   return item.getETextNum();
}

/*
// used for author equality
string getKey( const EBookEntry & item )
{
return item.getCreator() ;
}
*/

void displayOneEBook(EBookEntry book)
{
   cout << "   # " << book.getETextNum() << "  ---------------" << endl;
   cout << "   \"" << book.getTitle() << "\"" << endl;
   cout << "   by " << book.getCreator() << endl;
   cout << "   re: " << book.getSubject() << endl << endl;
}

/* Assignment 6 Program Output:

------------------Run 1: Int Key------------------

Books from: catalog-short4.txt
# of books: 4863
First, all the random books in the array:
# 29229
by Dunlap, William, 1766-1839
# 6367
by Chalippe, Father Candide
# 1778
by Shakespeare, William, 1564-1616
# 29375
by Friedl, Herman
# 27150
by Maniates, Belle Kanaris
# 29339
by Brooks, C. Harry (Cyrus Harry), 1890-
# 30024
by (no data found)
# 26173
by Stephens, Bascom Asbury Cecil
# 13330
by Smith, F. G. (Frederick George), 1880-1947
# 28808
by Orczy, Emmuska Orczy, Baroness, 1865-1947
# 26342
by (no data found)
# 216
by Laozi
# 28781
by Twain, Mark, 1835-1910
# 29211
by Bonczar, Thomas P.
# 12548
by Fontenoy, Mme. la Marquise de
# 27999
by Butler, Arthur John, 1844-1910
# 30372
by Alger, Horatio, 1832-1899
# 27212
by Cobb, Irvin S. (Irvin Shrewsbury), 1876-1944
# 5463
by Ebers, Georg, 1837-1898
# 24762
by Tappan, Eva March, 1854-1930
# 29431
by Sabatini, Rafael, 1875-1950
# 2079
by Weyman, Stanley John, 1855-1928
# 26210
by Worthington, Elizabeth Strong
# 1143
by Conrad, Joseph, 1857-1924
# 26700
by Short, Richard


Now the same random books from the hash table:
# 29229  ---------------
"Andr??"
by Dunlap, William, 1766-1839
re: Tragedies


# 6367  ---------------
"The Life and Legends of Saint Francis of Assisi"
by Chalippe, Father Candide
re: (no data found)


# 1778  ---------------
"A Midsummer Night's Dream"
by Shakespeare, William, 1564-1616
re: Comedies


# 29375  ---------------
"Manufacturing Cost Data on Artificial Ice"
by Friedl, Herman
re: Refrigeration and refrigerating machinery


# 27150  ---------------
"Penny of Top Hill Trail"
by Maniates, Belle Kanaris
re: Western stories


# 29339  ---------------
"The Practice of Autosuggestion"
by Brooks, C. Harry (Cyrus Harry), 1890-
re: Mental suggestion


# 30024  ---------------
"The Fisher-Boy Urashima"
by (no data found)
re: Fairy tales


# 26173  ---------------
"The Stephens FamilyA Genealogy of the Descendants of Joshua Stevens"
by Stephens, Bascom Asbury Cecil
re: Genealogy -- Records


# 13330  ---------------
"The Last Reformation"
by Smith, F. G. (Frederick George), 1880-1947
re: (no data found)


# 28808  ---------------
"The Scarlet Pimpernel"
by Orczy, Emmuska Orczy, Baroness, 1865-1947
re: Historical fiction


# 26342  ---------------
"Chronicles of Strathearn"
by (no data found)
re: Strathearn (Scotland) -- History


# 216  ---------------
"The Tao Teh King, or the Tao and its Characteristics"
by Laozi
re: Taoism


# 28781  ---------------
"Extracts from Adam's Diary"
by Twain, Mark, 1835-1910
re: Humorous stories


# 29211  ---------------
"Prevalence of Imprisonment in the U.S. Population, 1974-2001"
by Bonczar, Thomas P.
re: Imprisonment -- United States -- Statistics


# 12548  ---------------
"The Secret Memoirs of the Courts of Europe: William II, Germany; Francis Jos
eph, Austria-Hungary, Volume I. (of 2)"
by Fontenoy, Mme. la Marquise de
re: (no data found)


# 27999  ---------------
"Dante: His Times and His Work"
by Butler, Arthur John, 1844-1910
re: Dante Alighieri, 1265-1321


# 30372  ---------------
"Robert Coverdale's StruggleOr, On The Wave Of Success"
by Alger, Horatio, 1832-1899
re: New England -- History -- 19th century -- Fiction


# 27212  ---------------
"The Life of the Party"
by Cobb, Irvin S. (Irvin Shrewsbury), 1876-1944
re: PS


# 5463  ---------------
"The Sisters ?Çö Volume 3"
by Ebers, Georg, 1837-1898
re: Egypt -- History -- 332-30 B.C. -- Fiction


# 24762  ---------------
"Diggers in the Earth"
by Tappan, Eva March, 1854-1930
re: Readers


# 29431  ---------------
"The Project Gutenberg Works Of Rafael SabatiniAn Index"
by Sabatini, Rafael, 1875-1950
re: Indexes


# 2079  ---------------
"From the Memoirs of a Minister of France"
by Weyman, Stanley John, 1855-1928
re: Henry IV, King of France, 1553-1610 -- Fiction


# 26210  ---------------
"How to Cook Husbands"
by Worthington, Elizabeth Strong
re: Marriage


# 1143  ---------------
"Notes on Life and Letters"
by Conrad, Joseph, 1857-1924
re: Conrad, Joseph, 1857-1924


# 26700  ---------------
"SaroniaA Romance of Ancient Ephesus"
by Short, Richard
re: Ephesus (Extinct city) -- Fiction


Next three find() calls should throw exceptions:
not found.  not found.  not found.

After 25 remove() calls on the hash table,we attempt 25 find() calls once more:
not found.
not found.
not found.
not found.
not found.
not found.
not found.
not found.
not found.
not found.
not found.
not found.
not found.
not found.
not found.
not found.
not found.
not found.
not found.
not found.
not found.
not found.
not found.
not found.
not found.
Press any key to continue . . .



------------------Run 2: String Key------------------

Books from: catalog-short4.txt
# of books: 4863
First, all the random books in the array:
# 27947
by (no data found)
# 26533
by Lawrence, Josephine, 1897?-1978
# 28226
by Raleigh, Walter Alexander, Sir, 1861-1922
# 27463
by Ghosh, Sarath Kumar, 1883-
# 28847
by Busch, Wilhelm, 1832-1908
# 24858
by Bassett, Sara Ware, 1872-1968
# 26294
by Apuleius, Lucius, 125?-180
# 29533
by Birmingham, George A., 1865-1950
# 27168
by Eggleston, Edward, 1837-1902
# 2079
by Weyman, Stanley John, 1855-1928
# 27401
by Swinburne, Algernon Charles, 1837-1909
# 28660
by Anonymous
# 25005
by Crownfield, Gertrude, 1867-1945
# 28676
by Trollope, Anthony, 1815-1882
# 29714
by Kelsey, Carl, 1870-1953
# 25965
by Arnold, Edwin, Sir, 1832-1904
# 29207
by Zangwill, Louis, 1869-1938
# 28596
by Various
# 26274
by Wyss, Johann David, 1743-1818
# 25340
by Byron, George Gordon Byron, Baron, 1788-1824
# 28308
by (no data found)
# 28540
by Dibdin, Thomas Frognall, 1776-1847
# 25389
by Agee, Alva, 1858-1943
# 25316
by Standish, Burt L., 1866-1945
# 25467
by Manwell, M. B.


Now the same random books from the hash table:
# 28351  ---------------
"Dick and His Cat and Other Tales"
by (no data found)
re: Animals -- Juvenile fiction


# 26533  ---------------
"Rainbow Hill"
by Lawrence, Josephine, 1897?-1978
re: Family -- Juvenile fiction


# 28226  ---------------
"The War in the Air; Vol. 1The Part played in the Great War by the Royal Air
Force"
by Raleigh, Walter Alexander, Sir, 1861-1922
re: Great Britain. Royal Air Force


# 27463  ---------------
"The Wonders of the Jungle, Book Two"
by Ghosh, Sarath Kumar, 1883-
re: Zoology -- Juvenile literature


# 28847  ---------------
"Max and Mauricea juvenile history in seven tricks"
by Busch, Wilhelm, 1832-1908
re: Wit and humor


# 27834  ---------------
"Paul and the Printing Press"
by Bassett, Sara Ware, 1872-1968
re: Printing -- Juvenile literature


# 26294  ---------------
"The Apologia and Florida of Apuleius of Madaura"
by Apuleius, Lucius, 125?-180
re: Apuleius -- Translations into English


# 24073  ---------------
"General John Regan"
by Birmingham, George A., 1865-1950
re: Ireland -- Fiction


# 27168  ---------------
"The Faith DoctorA Story of New York"
by Eggleston, Edward, 1837-1902
re: New York (N.Y.) -- Fiction


# 29100  ---------------
"The Wild Geese"
by Weyman, Stanley John, 1855-1928
re: PR


# 18210  ---------------
"The Heptalogia"
by Swinburne, Algernon Charles, 1837-1909
re: (no data found)


# 29382  ---------------
"The Ladies' Work-Table BookContaining Clear and Practical Instructions in Pl
ain andFancy Needlework, Embroidery, Knitting, Netting and Crochet"
by Anonymous
re: Crocheting


# 25005  ---------------
"The Shadow Witch"
by Crownfield, Gertrude, 1867-1945
re: Fairy tales


# 29000  ---------------
"The Macdermots of Ballycloran"
by Trollope, Anthony, 1815-1882
re: Domestic fiction


# 29714  ---------------
"The Negro Farmer"
by Kelsey, Carl, 1870-1953
re: African American farmers -- Southern States


# 25965  ---------------
"Indian PoetryContaining &quot;The Indian Song of Songs,&quot; from the Sansk
rit of the G?«ta Govinda of Jayadeva, Two books from &quot;The Iliad Of India&qu
ot; (Mah?íbh?írata), &quot;Proverbial Wisdom&quot; from the Shlokas of the Hitop
adesa, and other Oriental Poems."
by Arnold, Edwin, Sir, 1832-1904
re: Sanskrit poetry -- Translations into English


# 29207  ---------------
"Cleo The MagnificentOr, the Muse of the Real"
by Zangwill, Louis, 1869-1938
re: PR


# 28712  ---------------
"The American Missionary ?Çö Volume 54, No. 3, October, 1900"
by Various
re: Congregational churches -- Missions -- Periodicals


# 26274  ---------------
"The Swiss Family Robinson"
by Wyss, Johann David, 1743-1818
re: Survival after airplane accidents, shipwrecks, etc. -- Fiction


# 21182  ---------------
"When We Two Parted"
by Byron, George Gordon Byron, Baron, 1788-1824
re: Poetry


# 28351  ---------------
"Dick and His Cat and Other Tales"
by (no data found)
re: Animals -- Juvenile fiction


# 28540  ---------------
"Bibliomania; or Book-MadnessA Bibliographical Romance"
by Dibdin, Thomas Frognall, 1776-1847
re: Book collecting


# 25389  ---------------
"Right Use of Lime in Soil Improvement"
by Agee, Alva, 1858-1943
re: Lime


# 22265  ---------------
"Frank Merriwell's Cruise"
by Standish, Burt L., 1866-1945
re: (no data found)


# 26714  ---------------
"The Captain's BunkA Story for Boys"
by Manwell, M. B.
re: Didactic fiction


Next three find() calls should throw exceptions:
not found.  not found.  not found.

After 25 remove() calls on the hash table,we attempt 25 find() calls once more:
not found.
not found.
not found.
not found.
not found.
not found.
not found.
not found.
not found.
not found.
not found.
not found.
not found.
not found.
not found.
not found.
not found.
not found.
not found.
not found.
not found.
not found.
not found.
not found.
not found.
Press any key to continue . . .

*/