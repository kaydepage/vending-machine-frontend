#ifndef COINS_H
#define COINS_H

#include "Coin.h"

#include <istream>
#include <string>
#include <vector>


// The default coin level to reset the coins to on request
#define DEFAULT_COIN_COUNT  20

// The number of denominations of currency available in the system 
#define NUM_DENOMINATIONS    8

/**
 * Collector class for Coin objects wrapped around an array
*/
class Coins {
public:
    // Coins constructor
    Coins();

    // Shallow copy constructor
    Coins(Coins& other);

    // Coins destructor
    ~Coins();

    // Size of the collection
    int size();

    // Return index of Coin object in collection
    Coin* get(int index);

    // Add Coin to collection
    void add(Coin* coin, int index);

    // Delete elements of collection
    void clear();

    // Reset Coin counts to default value
    void resetCoins();



private:

    Coin* coins[NUM_DENOMINATIONS];
    int denoms;

};

#endif // COINS_H