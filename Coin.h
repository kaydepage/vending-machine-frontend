#ifndef COIN_H
#define COIN_H

// Coin.h defines the coin structure for managing currency in the system. 
#define DELIM ","  // delimiter 

// enumeration representing the various types of currency available in the system. 
enum Denomination
{
    FIVE_CENTS, TEN_CENTS, TWENTY_CENTS, FIFTY_CENTS, ONE_DOLLAR, 
    TWO_DOLLARS, FIVE_DOLLARS, TEN_DOLLARS
};


// represents a coin type stored in the cash register perhaps. Each demonination
// will have exactly one of these in the cash register.
class Coin
{
public:
    // Constructor
    Coin(Denomination denom, unsigned count);

    // Shallow Copy Constructor
    Coin(Coin& other);

    // Destructor
    ~Coin();

    // Return the enum Denomination value
    Denomination getDenom();

    // Set the Coin enum Denomination value
    void setDenom(int _denom);

    // Return the number of a speicific Coin in the system
    unsigned getCount();

    // Set the number of a specific Coin in the system
    void setCount(unsigned count);
    bool positiveCount();

private:

    // The denomination type
    enum Denomination denom;
    
    // The count of how many of these are in the cash register
    unsigned count;
};

#endif // COIN_H
