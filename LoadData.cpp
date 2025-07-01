#include "LoadData.h"

LoadData::LoadData(){}

bool LoadData::lineReturn(std::vector<std::vector<std::string>> *vector, std::string inputPath, 
char delimeter, unsigned paramCount)
{   
    bool result{true};
    std::ifstream inf{inputPath};
    if (!inf)
    {

        std::cout << "File not found or can't be read.\n";
        result = false;
    }
    
    std::string splitInput;
    while(std::getline(inf >> std::ws, splitInput) && result == true) {
            std::vector<std::string> slist = {};
            std::back_insert_iterator<std::vector<std::string>> zlist = std::back_inserter(slist);
            std::string token;
            std::istringstream iss(splitInput);
            while (std::getline(iss, token, delimeter)) {
                *zlist++ = token;
            }

            if (slist.size() != paramCount) {
                std::cout << "Parameter count of line is invalid." << std::endl;
                result = false;
            }
        
            vector->push_back(slist);
        }

    return result;
}

bool LoadData::validateID(std::string input, std::string* id)
{   
    bool result{true};
    std::string intString = input.substr(1, input.size() - 1);
    if (Helper::validateTotal(intString) != true) {
        result = false;
    }
    else {
        int idInt = stoi(input.substr(1, input.size() - 1));
        if (idInt > MIN_ID_BOUND && idInt < MAX_ID_BOUND && input[0] == ID_LETTER && intString.size() == ID_SIZE) {
            *id = input;
            result = true;
        }
        else {
            result = false;
        }
    }

    return result;
}

bool LoadData::validateString(std::string input, std::string* stringPtr)
{
    bool result{true};

    if (input != EMPTY_STRING) {
        *stringPtr = input;
        result = true;
    }
    else {
        result = false;
    }
    return result;
}

bool LoadData::validatePrice(std::string input, Price* price)
{   
    bool result{true};
    int decimalTest = input.find(DECIMAL_CHAR);
    if (decimalTest != int(std::string::npos)) {
        std::string leftSide = input.substr(0, decimalTest);
        std::string rightSide = input.substr(decimalTest + 1, input.size() - leftSide.size() - 1);
        if (rightSide.size() == 1) {
            rightSide[1] = ZERO_CHAR;
        }
        if (rightSide[1] != ZERO_CHAR && rightSide[1] != FIVE_CHAR) {
    
            std::cout << "Error: the cents need to be a multiple of 5." << std::endl;
            result = false;
        }
        else if (Helper::validateTotal(leftSide) && Helper::validateTotal(rightSide)) {
            price->dollars = stoi(leftSide);
            price->cents = stoi(rightSide);
            result = true;
        }
        else {
            result = false;
        }
        
    }
    else {
        result = false;
    }
    return result;
}
bool LoadData::validateAmount(std::string input, unsigned* amount)
{   

    input.data();
    bool result{true};
    if (Helper::validateTotal(input) !=  true){
        result = false;
    }
    else {
        int idInt = stoi(input);
        if (idInt > 0 ) {
            *amount = idInt;
            result = true;
        }
        else {
            result = false;
        }
    }
    return result;
}

bool LoadData::validateValue(std::string input, std::string* value) 
{
    bool result{false};
    std::vector<std::string> values{"5", "10", "20", "50", "100", "200", "500", "1000"};
    for (int i{0}; i < int(values.size()); i++) {
        if (input == values[i]) {
            result = true;
        }
    }
    return result;
  
}

bool LoadData::validateVector(std::vector<std::string> input, LinkedList* linkedList)
{   
    bool result{true};

    if (input.size() != LIST_SIZE){
        std::cout << "failsize" << std::endl;
        result = false;
    }
    else {
        std::string stockID{};
        std::string stockName{};
        std::string stockDesc{};
        Price stockPrice{}; 
        unsigned stockAmount{}; 
        bool idResult = validateID(input[0], &stockID);
        bool nameResult = validateString(input[1], &stockName);
        bool descResult = validateString(input[2], &stockDesc);
        bool priceResult = validatePrice(input[3], &stockPrice);
        bool amountResult = validateAmount(input[4], &stockAmount);

        if (idResult == false){
            std::cout << "ID value is invalid." << std::endl;
            result = false;
        }
        else if (nameResult == false){
            std::cout << "Name value is invalid." << std::endl;
            result = false;
        }

        else if (descResult == false){
            std::cout << "Description value is invalid." << std::endl;
            result = false;
        }

        else if (priceResult == false){
            std::cout << "Price value is invalid." << std::endl;
            result = false;

        }
    
        else if (amountResult == false){
            std::cout << "Amount value is invalid." << std::endl;
            result = false;
        }   
            

        else {
            Node* node{ new Node };
            node->data->id = stockID;
            node->data->name = stockName;
            node->data->description = stockDesc;
            node->data->price = stockPrice;
            node->data->amount = stockAmount; 

            if (linkedList->getCount() == NO_NODES) {
                linkedList->addHead(node);
                result = true;
            }
            else {
                if (linkedList->addNode(node)) {
                    result = true;
                }
                else {
                    std::cout << "node failed to add." << std::endl;
                    delete node;
                    result = false;
                }
                
            }


            
        }        
    }
    return result;
}

bool LoadData::validateCoins(std::vector<std::vector<std::string>> vector) 
{
    bool result{true};
    std::set<std::string> coinSet{};
    

    for (unsigned i{0}; i < vector.size(); i ++) {
        coinSet.insert(vector[i][0]);
    }

    if (coinSet.size() != COIN_SIZE) {
        std::cout << "Duplicate coin type is invalid." << std::endl;
        result = false;
    }

    if (vector.size() != COIN_SIZE) {
        std::cout << "Coin type amount is invalid." << std::endl;
        result = false;
    }

    else {
        std::string coinValue;
        bool valueResult; 
        bool totalResult;
        for (int i{0}; i < COIN_SIZE; i++) {
            valueResult = LoadData::validateValue(vector[i][0], &coinValue);
            totalResult = Helper::validateTotal(vector[i][1]);
            if (result == true) {
                if (valueResult != true) {
                    std::cout << "Coin value is invalid." << std::endl;
                    result = false;
                }
                else if (totalResult != true){
                    std::cout << "Coin quantity is invalid." << std::endl;
                    result = false;
                }
                else {
                    result = true;
                }
            }
            //std::cout << "result: " << result << std::endl;
        }
    }
    return result;
}

std::string LoadData::extractCategory(std::string& input) {
    std::string result;
    std::size_t foundIndex = input.find(CAT_NAME_SEPERATOR);
    if (foundIndex != std::string::npos && foundIndex != 0) {
        result = input.substr(0, foundIndex);
        if (Helper::containsOnlyBlankSpaces(result) == true) {
            result = "Uncategorised";
        }
    } else {
        result = "Uncategorised";
    }
    return result;
}   


void LoadData::removeCategoryString(std::vector<std::string>* input, std::string delimeter) {
    size_t start_index = input->at(1).find(delimeter);

    if (start_index != std::string::npos) {
        input->at(1) = input->at(1).substr(start_index + delimeter.length());
    }
}

