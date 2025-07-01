#include "CoinUtils.h"

#include <iostream>

void CoinUtils::printCoins(Coins* coins) {
    printCoins(std::cout, coins);
}

void CoinUtils::printCoins(std::ostream& out, Coins* coins) {
    for (int i = 0; i < coins->size(); ++i) {
        if (coins->get(i) != nullptr) {
            printCoin(out, coins->get(i));
        }
    }
}  

void CoinUtils::printCoin(std::ostream& output, Coin* coin) {
    CoinUtils::printDenomAsInt(coin->getDenom());
    output << ","
            << coin->getCount()
            << std::endl;
}

void CoinUtils::printCoin(Coin* coin) {
    printCoin(std::cout, coin);
}

int CoinUtils::printDenomAsInt(int denom) {

    int fiveCents = 5;
    int tenCents = 10;
    int twentyCents = 20;
    int fiftyCents = 50;
    int oneDollar = 100;
    int twoDollars = 200;
    int fiveDollars = 500;
    int tenDollars = 1000;
    int invalid = -1;
    int output = invalid;

    if (denom == FIVE_CENTS) {
        output = fiveCents;
    } else if (denom == TEN_CENTS) {
        output = tenCents;
    } else if (denom == TWENTY_CENTS) {
        output = twentyCents;
    } else if (denom == FIFTY_CENTS) {
        output = fiftyCents;
    } else if (denom == ONE_DOLLAR) {
        output = oneDollar;
    } else if (denom == TWO_DOLLARS) {
        output = twoDollars;
    } else if (denom == FIVE_DOLLARS) {
        output = fiveDollars;
    } else if (denom == TEN_DOLLARS) {
        output = tenDollars;
    } else {
        output = invalid;
    }
    return output;
}

std::string CoinUtils::printDenomAsString(Denomination denom) {
    std::string fiveCents = "5 Cents";
    std::string tenCents = "10 Cents";
    std::string twentyCents = "20 Cents";
    std::string fiftyCents = "50 Cents";
    std::string oneDollar = "1 Dollar";
    std::string twoDollars = "2 Dolars";
    std::string fiveDollars = "5 Dollars";
    std::string tenDollars = "10 Dollars";
    std::string invalid = "Invalid denomination";
    std::string output = invalid;


    if (denom == FIVE_CENTS) {
        output = fiveCents;
    } else if (denom == TEN_CENTS) {
        output = tenCents;
    } else if (denom == TWENTY_CENTS) {
        output = twentyCents;
    } else if (denom == FIFTY_CENTS) {
        output = fiftyCents;
    } else if (denom == ONE_DOLLAR) {
        output = oneDollar;
    } else if (denom == TWO_DOLLARS) {
        output = twoDollars;
    } else if (denom == FIVE_DOLLARS) {
        output = fiveDollars;
    } else if (denom == TEN_DOLLARS) {
        output = tenDollars;
    } else {
        output = invalid;
    }
    return output;
}


    bool CoinUtils::validCoinInput(int value) {

    int fiveCents = 5;
    int tenCents = 10;
    int twentyCents = 20;
    int fiftyCents = 50;
    int oneDollar = 100;
    int twoDollars = 200;
    int fiveDollars = 500;
    int tenDollars = 1000;

    if (value == fiveCents || value == tenCents || 
    value == twentyCents || value == fiftyCents || 
    value == oneDollar || value == twoDollars || 
    value == fiveDollars || value == tenDollars) {
        return true;
    } else {
        return false;
    }
}

void CoinUtils::addCountToCoins(Coins* coins, int payment) {

    int fiveCents = 5;
    int tenCents = 10;
    int twentyCents = 20;
    int fiftyCents = 50;
    int oneDollar = 100;
    int twoDollars = 200;
    int fiveDollars = 500;
    int tenDollars = 1000;

    if (payment == fiveCents) {
        coins->get(7)->setCount(coins->get(7)->getCount()+1);
    } else if (payment == tenCents) {
        coins->get(6)->setCount(coins->get(6)->getCount()+1);
    } else if (payment == twentyCents) {
        coins->get(5)->setCount(coins->get(5)->getCount()+1);
    } else if (payment == fiftyCents) {
        coins->get(4)->setCount(coins->get(4)->getCount()+1);
    } else if (payment == oneDollar) {
        coins->get(3)->setCount(coins->get(3)->getCount()+1);
    } else if (payment == twoDollars) {
        coins->get(2)->setCount(coins->get(2)->getCount()+1);
    } else if (payment == fiveDollars) {
        coins->get(1)->setCount(coins->get(1)->getCount()+1);
    } else if (payment == tenDollars) {
        coins->get(0)->setCount(coins->get(0)->getCount()+1);
    } else {
        std::cout << "Invalid coin to add." << std::endl;
    }
}

    Denomination CoinUtils::toDenom(std::string input) {

    Denomination denom;

    if(input == "1000") {
        denom = TEN_DOLLARS;
    } else if (input == "500") {
        denom = FIVE_DOLLARS;
    } else if (input == "200") {
        denom = TWO_DOLLARS;
    } else if (input == "100") {
        denom = ONE_DOLLAR;
    } else if (input == "50") {
        denom = FIFTY_CENTS;
    } else if (input == "20") {
        denom = TWENTY_CENTS;
    } else if (input == "10") {
        denom = TEN_CENTS;
    } else {
        denom = FIVE_CENTS;
    }
    return denom;
}

void CoinUtils::displayCoins(Coins* coins) {
    std::cout << "\nCoins Summary" << std::endl;
    std::cout << std::setfill('-') << std::setw(13) << "-" << std::endl;

    std::cout << std::setfill(' ') << std::setw(16) << std::left << "Denomination" << "|"
         << std::setw(10) << std::right << "Count" << std::endl;

    std::cout << std::setfill('-') << std::setw(27) << "-" << std::endl;

    for (int i = 0; i < NUM_DENOMINATIONS; i++)
    {
        std:: cout << std::setfill(' ') << std::setw(16) << std::left
            << CoinUtils::printDenomAsString(coins->get(i)->getDenom()) << '|'
            << std::setw(10) << std::right << coins->get(i)->getCount() << std::endl;
    }
    std::cout << std::endl;

}

void CoinUtils::cleanCoins(Coins* coins) {
   delete coins;
}