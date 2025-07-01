#include "Helper.h"

Helper::Helper(){}

bool Helper::validateTotal(std::string input)
{
    bool result{true};
    for (int i{0}; i < int(input.size()); i++) {
        if (isdigit(input[i]) != true) {
            result = false;
        }
    }
    return result;

}

std::vector<std::vector<std::string>> Helper::getCoinOutput(Coins* coins) {
    std::vector<std::vector<std::string>> columns{};
    for (int i{0}; i < 8; i++) {
        std::string denom{};
        std::vector<std::string> row{};
        Coin* coin = coins->get(i); 
         
        if(coin->getDenom() == TEN_DOLLARS) {
            denom = "1000";
        } else if (coin->getDenom() == FIVE_DOLLARS) {
            denom = "500";
        } else if (coin->getDenom() == TWO_DOLLARS) {
            denom = "200";
        } else if (coin->getDenom() == ONE_DOLLAR) {
            denom = "100";
        } else if (coin->getDenom() == FIFTY_CENTS) {
            denom = "50";
        } else if (coin->getDenom() == TWENTY_CENTS) {
            denom = "20";
        } else if (coin->getDenom() == TEN_CENTS) {
            denom = "10";
        } else if (coin->getDenom() == FIVE_CENTS) {
            denom = "5";
        }
        row.push_back(denom);
        row.push_back(std::to_string(coin->getCount()));
        columns.push_back(row);
    }

    return columns;
}

bool Helper::containsOnlyBlankSpaces( std::string input) {
    for (char c : input) {
        if (!std::isspace(c)) {
            return false;  
        }
    }
    return true;  
}