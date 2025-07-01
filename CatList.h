#ifndef CATLINKEDLIST_H
#define CATLINKEDLIST_H
#include <algorithm>
#include <iostream>
#include <vector>
#include <iomanip>
#include "LinkedList.h"

//Used when comparing two string using std::string.compare(), if there are the same value the result is 0
#define SAME_VALUE 0
//The value that IDs must be greater than.
#define MIN_ID_BOUND 0
//The value that IDs must be less than.
#define MAX_ID_BOUND 10000
//The char that should be at the beginning of every ID string.
#define ID_LETTER 'I'
//The length that the number section of the ID string should be.
#define ID_SIZE 4
//Max int value of ID nums.
#define MAX_ID_NUM 9999
//Index of first number in ID string.
#define FIRST_NUM_INDEX 1

#define EMPTY_STRING ""
//The char that should be in every price string.
#define DECIMAL_CHAR '.'
//The char representing a 0, being one of 2 values the second cents index should be.
#define ZERO_CHAR '0'
//The char representing a 0, being one of 2 values the second cents index should be.
#define FIVE_CHAR '5'
#define COMMA_CHAR ','
#define PIPE_CHAR '|'

//The size the vector with the stock details should be.
#define LIST_SIZE 5
//0 nodes in the linkedlist.
#define NO_NODES 0

//the size the vector with the coin details should be.
#define COIN_SIZE 8

//Max size of dollar and cents substrings in price string.
#define DOLLAR_MAX_SIZE 2
#define CENTS_MAX_SIZE 2

//Correct number of params for a stock line in data file.
#define STOCK_PARAMS 5
//Correct number of params for a coin line in data file.
#define COIN_PARAMS 2 

//Index of stock file in arguements when running the program.
#define STOCK_FILE_INDEX 1
//Index of coin file in arguements when running the program.
#define COIN_FILE_INDEX 2

//Index of denomination inside coin vector.
#define DENOM_INDEX 0
//Indexx of count inside coin vector.
#define COUNT_INDEX 1

//Correct number of arguements needed to run the program. i.e ./ppd stock.dat coins.dat
#define CORRECT_ARG_COUNT 3

//string used to seperate category and name in 2d stock file.
#define CAT_NAME_SEPERATOR "\\&"


//Node used to store categories. Used as the nodes of the category linkedlist. 
class CatNode
{
public:
    CatNode();
    ~CatNode();

    std::string category = "";
    //linkedlist containing the original nodes, which take stock data.
    LinkedList* data;
    CatNode* next = nullptr;
    

    
};



class CatLinkedList
{
public:
    CatLinkedList();
    ~CatLinkedList();

    //returns the linkedlist's count value.
    int getCount();

    CatNode* getHead();

    //Adds a node to an empty linkedlist. Sets the head value of linkedlist to node input.
    void addHead(CatNode* node);

    //traverses the linkedlist beginning with the head. Sets the next node to head and deletes the prior head.
    void deleteListNodes();

    //traverses the catlinkedlist and checks if the list contains this node and enters it in alphabetical order 
    //if not in the list.
    bool addCatNode(CatNode* node);

    //Used to print the name of category for use in display stock, after each cat name is printed the linkedlist
    //display items is called for that categories linkedlist.
    void displayCategories();

    //Tries to find a category node based off string input, checks against each nodes name data.
    //returns the node if found, if not returns a nullptr.
    CatNode* findCatNode(std::string category);
    
    //Tries to get the next new id for stock to be added. Returns "" if there is no available id. First traverses
    //the catlinkedlist and then goes through each nodes linkedlist containing the stock data to get the used
    //ids. 
    std::string getNewID();

    //For adding stock when using a 2d linkedlist, difference from original addstock is it first asks for a valid category
    //to be able to go through adding the stock data.
    bool addStock();

    //traverses the catlinkedlist and then goes through each nodes linkedlist to try and find the node with the matching
    //id to the input. returns a nullptr if the id cant be found.
    Node* getById(std::string id);

    //Traverses each cat node and then traverses each cat nodes' linkedlist and sets each stock node to the inputCount.
    void resetStockCount(int inputCount);

    //Transforms the 2d linkedlist into vector format, adds the category each stocknode was in to the beginning of the
    //name data with a seperator to be used for future application use.
    std::vector<std::vector<std::string>> getListOutput();

    //asks the user for an id to delete then traverses the 2d linkedlist trying to find that node.
    //if found, the node is deleted and the prior node has its next set to the deleted nodes next.
    void deleteNodebyID();

private:
    // the beginning of the list
    CatNode* head;
  
    // how many nodes are there in the list?
    unsigned count;
};



#endif  // LINKEDLIST_H


