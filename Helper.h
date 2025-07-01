#ifndef HELPER_H
#define HELPER_H

#include "Coin.h"
#include "Coins.h"

#include <charconv>
#include <cctype>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

/**
 * Helper function class
*/
class Helper
{
private:
    // Constructor
    Helper();

public:
    // Checks for integer values
    static bool validateTotal(std::string input);

    // 
    //static std::vector<std::string> getOutputVector(std::string toSave);
    
    // Parses Coin objects into strings for file writing
    static std::vector<std::vector<std::string>> getCoinOutput(Coins* coins);

    //Checks if a string contains only blank space and returns true if the condiiton is met. else returns false.
    static bool containsOnlyBlankSpaces(std::string input);
};
#endif