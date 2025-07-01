#include "CoinUtils.h"
#include <iostream>
#include "LoadData.h"
#include "CatList.h"
#include "SaveData.h"
#include "LinkedList.h"
#include <fstream>
#include "Helper.h"
#include "PurchaseItem.h"

using std::string;
/**
 * manages the running of the program, initialises data structures, loads
 * data, display the main menu, and handles the processing of options. 
 * Make sure free memory and close all files before exiting the program.
 **/
int main(int argc, char **argv)
{
    // Reading the two data files
    if(argc >= CORRECT_ARG_COUNT) {
        bool enhancement2D{false};
        bool enhancementColour{false};
        for (int i{0}; i < argc; i++) {
            if (strcmp(argv[i], "2d") == 0) {
                enhancement2D = true;

            }
            else if (strcmp(argv[i], "colour") == 0) {
                enhancementColour = true;

            }
        }

        Coins* coins = new Coins();
        bool stockImportResult{true};
        bool coinImportResult{true};
        // Create a vector from the given file with a delimeter.
        LinkedList populatedList;
        CatLinkedList catList;
        std::vector<std::vector<std::string>> svector{};
        std::vector<std::vector<std::string>> *vPointer = &svector;
        bool scrapeResult = LoadData::lineReturn(vPointer, argv[STOCK_FILE_INDEX], PIPE_CHAR, STOCK_PARAMS);
        

        if (enhancement2D) {
            if (scrapeResult) {
                for (int i{0}; i < int(svector.size()); i++) {
                    //extracts the category from the name parameter, if no cat is present, uncategorised is the category.
                    std::string newCat = LoadData::extractCategory(svector[i][1]);
                    //remove category tag from name string.
                    LoadData::removeCategoryString(&svector[i], "\\&");
                    CatNode* node{ new CatNode };
                    node->category = newCat;
                    //if a new category is added to catList, attempt to add the line data to this categorie's linkedlist.
                    if (catList.addCatNode(node) == true) {
                        //attempting to add line data to the new categorie's linkedlist. 
                        if (!LoadData::validateVector(svector[i], node->data)) {
                            std::cout << "The stock file is invalid." << std::endl;
                            stockImportResult = false;
                        }
                    }
                    //Category is already in the catList, attempt to add the line data to that category.
                    else {
                        delete node;
                        CatNode* inputNode = catList.findCatNode(newCat);
                        if (!LoadData::validateVector(svector[i], inputNode->data)) {
                            std::cout << "The stock file is invalid." << std::endl;
                            stockImportResult = false;
                        }    
                    }                   
                    
                }
            }
            else {
                std::cout << "The stock file is invalid." << std::endl;
                stockImportResult = false;

                
            }   
        }
        
        else {
            if (scrapeResult) {
                for (int i{0}; i < int(svector.size()); i++) {
                    if (!LoadData::validateVector(svector[i], &populatedList)) {
                        //delete list and exit.
                        std::cout << "The stock file is invalid." << std::endl;
                        stockImportResult = false;
                    }
                }
            }
            else {
                std::cout << "The stock file is invalid." << std::endl;
                stockImportResult = false;

                
            }   
        }

        std::vector<std::vector<std::string>> coinVector;
        std::vector<std::vector<std::string>> *coinPointer = &coinVector;
        bool coindataResult = LoadData::lineReturn(coinPointer, argv[COIN_FILE_INDEX], COMMA_CHAR, COIN_PARAMS);
        if (coindataResult) {
            if (!LoadData::validateCoins(coinVector)) {
                // delete coin vector and exit.
                std::cout << "The coin file is invalid." << std::endl;
                coinImportResult = false;
            }
            else {
                for (int i{0}; i < COIN_SIZE; i++) {
                    // add Coins to collection
                    Denomination tempDenom = CoinUtils::toDenom(coinVector[i][DENOM_INDEX]);
                    Coin* tempPtr = new Coin(tempDenom, std::stoul(coinVector[i][COUNT_INDEX]));
                    coins->add(tempPtr, i);
                }
            }
        }
        else {
            std::cout << "The coin file is invalid." << std::endl;
            coinImportResult = false;
        }
        
        
        
        if (stockImportResult == true && coinImportResult == true) {
            bool run = 1;
            while (run){

                std::cout << "Main Menu:" << std::endl;
                std::cout << "   1.Display Items" << std::endl;
                std::cout << "   2.Purchase Items" << std::endl;
                std::cout << "   3.Save and Exit" << std::endl;
                std::cout << "Administrator-Only Menu:" << std::endl;
                std::cout << "   4.Add Item" << std::endl;
                std::cout << "   5.Remove Item" << std::endl;
                std::cout << "   6.Display Coins" << std::endl;
                std::cout << "   7.Reset Stock" << std::endl;
                std::cout << "   8.Reset Coins" << std::endl;
                std::cout << "   9.Abort Program" << std::endl;
                std::cout << "Select your option(1-9): ";

                string input;
                std::getline(std::cin, input);

                if (input == "1") {
                    if (enhancement2D) {
                        catList.displayCategories();
                    }
                    else {
                        std::cout << "\nItems Menu" << std::endl;
                        populatedList.displayStock();
                    }
                    
                }
                else if (input == "2") {
                    if (enhancement2D) {
                        if (enhancementColour) {
                            PurchaseItem::selectItem2D(catList, coins, true);
                        }
                        else {
                            PurchaseItem::selectItem2D(catList, coins);
                        }
                        
                    }
                    else {
                        if (enhancementColour) {
                            PurchaseItem::selectItem(populatedList, coins, true);
                        }
                        else {
                            PurchaseItem::selectItem(populatedList, coins);
                        }
                    }
                    
                }
                else if (input == "3") {
                    std::vector<std::vector<std::string>> stockOutput;
                    if (enhancement2D) {
                        stockOutput = catList.getListOutput();
                    }
                    else {
                        stockOutput = populatedList.getListOutput();
                    }

                    bool saveFile = SaveData::lineWrite(stockOutput, argv[STOCK_FILE_INDEX], PIPE_CHAR);
                    if ((saveFile = 0)){
                        std::cout<<"Error saving stock"<<std::endl;
                    }
                    saveFile = SaveData::lineWrite(Helper::getCoinOutput(coins), argv[COIN_FILE_INDEX], COMMA_CHAR);
                    if ((saveFile = 0)){
                        std::cout<<"Error saving coins"<<std::endl;
                    }
                    else {
                        if (enhancement2D) {
                            catList.deleteListNodes();
                        }
                        else {
                            populatedList.deleteListNodes();
                        }
                        coins->clear();
                    }
                    run = 0;
                }
                else if (input == "4") {
                    if (enhancement2D) {
                        catList.addStock();
                        
                        
                    }
                    else {
                        std::string newId = populatedList.getNewID();
                        if (newId != "") {
                            populatedList.addStock(newId);
                        }
                        else {
                            std::cout << "No space available to add stock." << std::endl;
                        }
                        
                    }
                    
                }
                else if (input == "5") {
                    if (enhancement2D) {
                        catList.deleteNodebyID();
                    }
                    else {
                        populatedList.deleteNodebyID();
                    }
                    
                }
                else if (input == "6") {
                    CoinUtils::displayCoins(coins);
                }
                else if (input == "7") {
                    if (enhancement2D) {
                        catList.resetStockCount(DEFAULT_STOCK_LEVEL);
                    }
                    else {
                        populatedList.resetStockCount(DEFAULT_STOCK_LEVEL);
                    }
                    std::cout << "All stock has been reset ot the default level of " << DEFAULT_STOCK_LEVEL << std::endl;
                }
                
                else if (input == "8") {
                    coins->resetCoins();
                    std::cout << "Coins have been reset to " << DEFAULT_COIN_COUNT << std::endl;
                }
                else if (input == "9") {
                    if (enhancement2D) {
                            catList.deleteListNodes();
                        }
                    else {
                        populatedList.deleteListNodes();
                    }
                    coins->clear();
                    run = 0;
                }
                else if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    run = 0;
                }


            }
        }
        CoinUtils::cleanCoins(coins);
    }
    return EXIT_SUCCESS;
}
