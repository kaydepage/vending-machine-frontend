#include "PurchaseItem.h"

#include <iostream>


void PurchaseItem::selectItem( LinkedList linkedList, Coins* coins, bool colour){

    Node* itemNode = nullptr; 
    std::cout << "Purchase Item" << std::endl 
    << "-------------" << std::endl 
    << "Please enter the id of the item you wish to purchase:" << std::endl;
    bool validInput = false;
    while (!validInput){
        std::string input;
        std::getline(std::cin, input);
        //node search
        
        if (linkedList.getById(input) && linkedList.getById(input)->data->amount > 0) {
            validInput = true;
            itemNode = linkedList.getById(input);
            if (colour) {
                purchaseItem(itemNode, coins, true);
            }
            else {
                purchaseItem(itemNode, coins);
            }
        } else if (std::cin.eof()) {
            validInput = true;
            std::cin.clear();
            std::cin.ignore(10000,'\n');
            // return
        } else if (linkedList.getById(input) && (linkedList.getById(input)->data->amount <= 0)) {
            std::cout << "Item with id: " << input << " has no stock remaining." << std::endl
            << "Please enter again." << std::endl;   
        } else if (input.empty()) {
            validInput = true;
        } else if (!linkedList.getById(input)) {
            std::cout << "Item with id: " << input << " does not exist." << std::endl
            << "Please enter again." << std::endl;
        } else {
            validInput = true;
            // return
        }
    }
}

void PurchaseItem::selectItem2D(CatLinkedList linkedList, Coins* coins, bool colour){
    
    Node* itemNode = nullptr; 
    std::cout << "Purchase Item" << std::endl 
    << "-------------" << std::endl 
    << "Please enter the id of the item you wish to purchase:" << std::endl;
    bool validInput = false;
    while (!validInput){
        std::string input;
        std::getline(std::cin, input);
        //node search
        if (linkedList.getById(input) && linkedList.getById(input)->data->amount > 0) {
            validInput = true;
            itemNode = linkedList.getById(input);
            if (colour) {
                purchaseItem(itemNode, coins, true);
            }
            else {
                purchaseItem(itemNode, coins);
            }
            
        } else if (std::cin.eof()) {
            validInput = true;
            std::cin.clear();
            std::cin.ignore(10000,'\n');
            // return
        } else if (linkedList.getById(input) && (linkedList.getById(input)->data->amount <= 0)) {
            std::cout << "Item with id: " << input << " has no stock remaining." << std::endl
            << "Please enter again." << std::endl;   
        } else if (input.empty()) {
            validInput = true;
        } else if (!linkedList.getById(input)) {
            std::cout << "Item with id: " << input << " does not exist." << std::endl
            << "Please enter again." << std::endl;
        } else {
            validInput = true;
            // return
        }
    }
}


    void PurchaseItem::purchaseItem(Node* itemNode, Coins* coins, bool colour){
    std::cout << "You have selected \"" << itemNode->data->name << " - " 
    << itemNode->data->description << "\". This will cost you $ "
    << itemNode->data->price.dollars << "." << itemNode->data->price.cents << "." << std::endl
    << "Please hand over the money - type in the value of each note/coin in cents." << std::endl
    << "Press enter or ctrl+d on a new line to cancel this purchase:" << std::endl;

    std::vector<Denomination> individualPayments{};
    individualPayments.reserve(6);

    double total  = (itemNode->data->price.dollars*100) + itemNode->data->price.cents;
    double amountOwing = (itemNode->data->price.dollars*100) + itemNode->data->price.cents;
    int change = 0;
    int payment = 0;
    int amountPaid = 0;

    bool validInput = false;
    while (validInput == false && !std::cin.eof()){

        if (validInput == false && !std::cin.eof()){
            std::cout << "You still need to give us ";
            if (colour) {
                std::cout << "\033[1;32m";  // Set text color to green
                std::cout << "$";
                std::cout << std::fixed << std::setprecision(2) << (amountOwing/100) - (change/100);
                std::cout << "\033[0m";  // Reset text color to default
                std::cout << ": ";
            }
            else {
                std::cout << std::fixed << std::setprecision(2) << (amountOwing/100)  - (change/100);
                std::cout << ": ";
            }

            std::string input;
            std::getline(std::cin, input);
            std::regex numsOnly("^[0-9]{1,10}$");

            if(std::regex_match(input, numsOnly)) {
            payment = std::stoi(input);
            }

            if (input.empty()) {
            if (amountPaid > 0){
                std::cout << "You have cancelled your purchase. Here is your change: "
                <<  amountPaid / 100 << "." << amountPaid % 100 << ": " << cancelPurchase(coins, amountPaid) << std::endl;
                validInput = true;
            } else {
                std::cout << "You have cancelled your purchase. Returning to menu." << std::endl;
                validInput = true;
            }
            } else if (std::cin.bad()) {
            std::cout << "You have quit the application." << std::endl;
            validInput = true;
            std::cin.clear();
            std::cin.ignore(10000,'\n');
            
            } else if (!std::regex_match(input, numsOnly)){
            std::cout << "Please enter an integer value of a single valid currency amount. e.g. enter 100 for one dollar."
            << std::endl;
            //std::cin.clear();
            //std::cin.ignore(10000,'\n');
            } else if (CoinUtils::validCoinInput(payment) && payment < amountOwing) {
            CoinUtils::addCountToCoins(coins, payment);
            amountPaid = amountPaid + payment;
            amountOwing = amountOwing - payment;
            std::cout << std::endl;
            //std::cout << "amount paid: " << payment << std::endl;

            } else if (CoinUtils::validCoinInput(payment) && payment  >= amountOwing) {
            CoinUtils::addCountToCoins(coins, payment);
            //std::cout << "payment: " << payment << std::endl;
            //std::cout << "amount paid: " << payment << std::endl;
            amountPaid = amountPaid + payment;
            amountOwing = amountOwing - payment;
            change = amountPaid - total;
            std::cout << std::endl;

            if (change == 0) {
                std::cout << "Here is your " << itemNode->data->name << "." <<std::endl;
            }
            else if (change != 0){
                returnChange(coins, change, itemNode);
            }

            itemNode->data->amount--;

            validInput = true;
            } else if (!CoinUtils::validCoinInput(payment)){
            std::cout << "Error: $" << payment / 100 << "." << payment % 100 
            << " is not a valid denomination of money. Please try again." << std::endl;
            } else {
            std::cout << "Unknown input error." << std::endl;
            }

        }
        
    }   
}

    std::string PurchaseItem::cancelPurchase(Coins* coins, int change){

    std::string changeString{};

    int fiveCents = 5;
    int tenCents = 10;
    int twentyCents = 20;
    int fiftyCents = 50;
    int oneDollar = 100;
    int twoDollars = 200;
    int fiveDollars = 500;
    int tenDollars = 1000;

    do {
        if (change >= tenDollars && coins->get(0)->getCount() > 0) {
        // Ten dollar coin -1
            change = change - tenDollars;
            changeString = changeString + "$10 ";
            coins->get(0)->setCount(coins->get(0)->getCount()-1);
        } else if (change >= fiveDollars && coins->get(1)->getCount() > 0) {
        // Five dollar coin -1
            change = change - fiveDollars;
            changeString = changeString + "$5 ";
            coins->get(1)->setCount(coins->get(1)->getCount()-1);
        } else if (change >= twoDollars && coins->get(2)->getCount() > 0) {
        // Two dollar coin -1
            change = change - twoDollars;
            changeString = changeString + "$2 ";
            coins->get(2)->setCount(coins->get(2)->getCount()-1);
        } else if (change >= oneDollar && coins->get(3)->getCount() > 0) {
        // One dollar coin -1
            change = change - oneDollar;
            changeString = changeString + "$1 ";
            coins->get(3)->setCount(coins->get(3)->getCount()-1);
        } else if (change >= fiftyCents && coins->get(4)->getCount() > 0) {
        // 50 cent coin -1
            change = change - fiftyCents;
            changeString = changeString + "50c ";
            coins->get(4)->setCount(coins->get(4)->getCount()-1);
        } else if (change >= twentyCents && coins->get(5)->getCount() > 0) {
        // Twenty cent coin -1
            change = change - twentyCents;
            changeString = changeString + "20c ";
            coins->get(5)->setCount(coins->get(5)->getCount()-1);
        } else if (change >= tenCents && coins->get(6)->getCount() > 0) {
        // Ten cent coin -1
            change = change - tenCents;
            changeString = changeString + "10c ";
            coins->get(6)->setCount(coins->get(6)->getCount()-1);
        } else if (change >= fiveCents && coins->get(7)->getCount() > 0) {
        // Five cent coin -1
            change = change - fiveCents;
            changeString = changeString + "5c ";
            coins->get(7)->setCount(coins->get(7)->getCount()-1);
        } else {
        // No more change to give out
            return changeString;
        }
    }
    while (change != 0); 

    return changeString;
}

    void PurchaseItem::returnChange(Coins* coins, int change, Node* itemNode){

    std::string changeString{};
    bool isChange = true;
    int totalChange = change;

    int fiveCents = 5;
    int tenCents = 10;
    int twentyCents = 20;
    int fiftyCents = 50;
    int oneDollar = 100;
    int twoDollars = 200;
    int fiveDollars = 500;
    int tenDollars = 1000;

    do {
        if (change >= tenDollars && coins->get(0)->getCount() > 0) {
        // Ten dollar coin -1
            change = change - tenDollars;
            changeString = changeString + "$10 ";
            coins->get(0)->setCount(coins->get(0)->getCount()-1);
        } else if (change >= fiveDollars && coins->get(1)->getCount() > 0) {
        // Five dollar coin -1
            change = change - fiveDollars;
            changeString = changeString + "$5 ";
            coins->get(1)->setCount(coins->get(1)->getCount()-1);
        } else if (change >= twoDollars && coins->get(2)->getCount() > 0) {
        // Two dollar coin -1
            change = change - twoDollars;
            changeString = changeString + "$2 ";
            coins->get(2)->setCount(coins->get(2)->getCount()-1);
        } else if (change >= oneDollar && coins->get(3)->getCount() > 0) {
        // One dollar coin -1
            change = change - oneDollar;
            changeString = changeString + "$1 ";
            coins->get(3)->setCount(coins->get(3)->getCount()-1);
        } else if (change >= fiftyCents && coins->get(4)->getCount() > 0) {
        // 50 cent coin -1
            change = change - fiftyCents;
            changeString = changeString + "50c ";
            coins->get(4)->setCount(coins->get(4)->getCount()-1);
        } else if (change >= twentyCents && coins->get(5)->getCount() > 0) {
        // Twenty cent coin -1
            change = change - twentyCents;
            changeString = changeString + "20c ";
            coins->get(5)->setCount(coins->get(5)->getCount()-1);
        } else if (change >= tenCents && coins->get(6)->getCount() > 0) {
        // Ten cent coin -1
            change = change - tenCents;
            changeString = changeString + "10c ";
            coins->get(6)->setCount(coins->get(6)->getCount()-1);
        } else if (change >= fiveCents && coins->get(7)->getCount() > 0) {
        // Five cent coin -1
            change = change - fiveCents;
            changeString = changeString + "5c ";
            coins->get(7)->setCount(coins->get(7)->getCount()-1);
            std::cout << coins->get(7)->getCount() << std::endl;
        } else {
        // No coins available
            changeString = "We are unable to provide change. Please contact our customer service for compensation.";
            std::cout << changeString << std::endl;
            isChange = false;
        }
    }
    while (change != 0 && isChange == true);

    // Return change
    if (isChange == true) {
        std::cout << "Here is your " << itemNode->data->name 
        << " and your change of $" << totalChange / 100 << "."; 
        std::cout << std::setw(2) << std::setfill('0') << change % 100 << ": " << changeString << std::endl;
    }
}