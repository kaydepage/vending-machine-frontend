
#ifndef COIN_UTILS_H
#define COIN_UTILS_H
#include "CatList.h"
#include "LinkedList.h"

#include <fstream>
#include <regex>

class Coins;

/** 
 * Coin utilities class
*/
class CoinUtils {

public:
    // Print all Coins in collection to output
    void printCoins(Coins* coins);

    // Overloaded print coin
    void printCoins(std::ostream& out, Coins* coins);

    // Print a specific Coin to output
    void printCoin(Coin* coin);

    // Overloaded printCoin
    void printCoin(std::ostream& output, Coin* coin);

    // Print the denomination's integer value
    int printDenomAsInt(int denom);

    //print the denominations value as a string
    static std::string printDenomAsString(Denomination denom);

    // Checks for valid denomination in int value
    static bool validCoinInput(int value);

    // Adds to the collection count for a specific Coin
    static void addCountToCoins(Coins* coins, int payment);

    // Converts string value to Coin Denomination for reading in Coins from input files
    static Denomination toDenom(std::string input);

    //Display function for coins per spec
    static void displayCoins(Coins* coins);

    // Free memory from Coins object
    static void cleanCoins(Coins* coins);

};

#endif // COIN_UTILS_H