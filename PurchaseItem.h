
#ifndef PURCHASE_ITEM_H
#define PURCHASE_ITEM_H

#include "CoinUtils.h"

#include <fstream>
#include <regex>

/**
 * Class providing functions for purchasing Stock using Coins
*/
class PurchaseItem {

public:
    // Find item by ID
    static void selectItem( LinkedList linkedList, Coins* coins, bool colour = false);
    
    //find items by ID for a 2d Linkedlist. first finds a category, and then calls selectItem().
    static void selectItem2D( CatLinkedList linkedList, Coins* coins, bool colour = false);

    // Pay for item with Coins
    static void purchaseItem(Node* itemNode, Coins* coins, bool colour = false);

    // End purchasing of item
    static std::string cancelPurchase(Coins* coins, int change);

    // Return change of full purchase
    static void returnChange(Coins* coins, int change, Node* itemNode);
};

#endif // PURCHASE_ITEM_H