#Indexer Design Spec
##CS50 Lab 5
###Grace Dorgan Feb 2018

####User Interface
The crawler’s only interface with the user is on the command-line.  It always 
takes two parameters in the following style: 
>./indexer pageDirectory indexFilename
####Inputs and Outputs
Input: The input is the command line inputs, one of which is the page directory
containing unique files of previously pulled html pages.

Output:
The Index type object gets written to indexFilename file, which is either 
created or overwritten.  It gets printed with one word parsed from the html per
line, with the counts of occurrances per file printed like so:   
word docID count [docID count...]

####Functional Decomposition into Modules
There should be an *index*, which will hold the actual data structure of the 
index and all data in it.  One will be able to build and print this index.  
A *pagedir* module may also be necessary to carry over from the *crawler* lab.
This should be able to convert html back into a *webpage_t* to parse for words.

####Pseudo Code for Indexer
1. Process and validate command line parameters
  1. Make sure pageDirectory is one made by a crawler
  2. Check if indexFilename exists and if it doesn't, create it
2. Initialize data structure *index*
3. index_build(pageDirectory, index)
  1. for each document in the directory:
    1. create a new webpage from the document
    2. pass the webpage to webpage.c
    3. for each word
      1.enter it into the index or increment its counter if it already exists
4. index_save(indexFilename, index)
  1. either create or overwrite a file indexFilename
  2. for each entry in the index:
    1. print the word
    2. print the docId's and the count of occurances in each document
5. clean up
  1. delete the *hashtable_t* and each *counters_t* in it

####Dataflow through modules
1. *main* makes sure there are three parameters, then calls methods from *index*
2. *index* uses a hashtable of *counters* to make an inverted index mapping from words to documents

####Major Data Structures
We will directly use two of our data structure modules:
1. *hashtable* of counters
2. *counters* to represent the unique docIDs and number of times a word occurs in the page
