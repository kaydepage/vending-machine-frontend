#ifndef LOADDATA_H
#define LOADDATA_H

#include <charconv>
#include <cctype>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <set>
#include <limits>
#include <memory>
#include <utility>
#include <algorithm>

#include "CatList.h"
#include "Helper.h"



class LoadData
{
    private:
        LoadData();


    public:
        //scrapes the data file and turns each line into a vector where each index is a parameter of stock. i.e id, name, desc
        //Then adds this array to an array that will contain all the scraped lines with the delimeter removed. 
        //Checks if the maount of parameters of each line is correct.
        static bool lineReturn(std::vector<std::vector<std::string>> *vector, std::string inputPath, 
        char delimeter, unsigned paremeters);

        //Checks if string input contains the I character at the beginning and that the remaining 
        //string is an int between 0 and 10000. Returns true if these conditions are met.
        //Updates the string pointer with the validated string when true.
        static bool validateID(std::string input, std::string* id);

        //Checks if a string is empty or not, returning true on non empty input.
        //Updates the string pointer with the validated input when returning true.
        static bool validateString(std::string input, std::string* stringPtr);

        //Checks if string contains a decimal point, and that left and right of the decimal point are valid ints.
        //Updates the empty price pointer values dollars and cents when true;
        static bool validatePrice(std::string input, Price* price);

        //Checks if string is a valid int that is > 0.
        //Updates unsigned int pointer with validated input when true.
        static bool validateAmount(std::string input, unsigned* amount);

        //Checks if input is one of 8 valid cents values. 
        //Updates string pointer with validated input when true.
        static bool validateValue(std::string input, std::string* value);

        //Checks if string received from lineReturn() can be created into a valid node by caliing
        //validate ID, String, Price, and Amount. If these are all true, a node is dynamically created
        //and stored in the linkedlist parameter.
        static bool validateVector(std::vector<std::string> inputVector, LinkedList* linkedList);

        //Checks if each row of the vector parameter can be considered a valid coin object.
        //Checks for the amount of coin types and duplicate coin type values. i.e. 5, 5, 20, 50, 100, 200, 500, 1000.
        static bool validateCoins(std::vector<std::vector<std::string>>);

        //Checks a string if it contains the 2d Linkedlist Category Name splitter string: \&, if found
        //that category is checked to see if it is not only whitespace. If it is all whitespace the cat is
        //set as Uncategorised. If not the category is set to the string. If no category is found in the 
        //string, it is set to Uncategorised.
        static std::string extractCategory(std::string& input);

        //For use in 2d linkedlist creation. Removes category part of string from name string so data
        //format is correct for use while running application.
        //Searches for the delimeter, and if found edits the input pointer to only include the name
        //part of the string.
        static void removeCategoryString(std::vector<std::string>* input, std::string delimeter);

        
};
#endif // LOADDATA_H