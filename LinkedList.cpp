#include "LinkedList.h"

LinkedList::LinkedList() {
   head = nullptr;  
   count = {0}; 
}

LinkedList::~LinkedList() {
}

int LinkedList::getCount() {
    return count;
}

Node* LinkedList::getHead() {
    return head;
}


void LinkedList::addHead(Node* node) {

    head = node;
    count += 1;
}

bool LinkedList::addNode(Node* inputNode) {
    bool result{true};
    Node* currentNode = head;
    std::string inputName{inputNode->data->name};
    std::string inputID{inputNode->data->id};
    bool looping{true};
    while (looping) {
        std::string nextName;

        std::string currentName{currentNode->data->name};
        std::string currentID{currentNode->data->id};
        
        
        if (inputID.compare(currentID) == SAME_VALUE) {
            result = false;
            looping = false;
            std::cout << "ID already in use." << std::endl;
        }
        else if (inputName.compare(currentName) == SAME_VALUE) {
            result = false;
            looping = false;
            std::cout << "Name already in use." << std::endl;
        } 
        else if (inputName.compare(currentName) < SAME_VALUE) {
            if (currentNode == head) {
                inputNode->next = currentNode;
                head = inputNode;
                count += 1;
                result = true;
                looping = false;
            }
        }
        else {
            Node* current = currentNode;

            if (current->next != nullptr) {
                nextName = current->next->data->name;
                if (inputName.compare(nextName) < SAME_VALUE) {
                    inputNode->next = current->next;
                    currentNode->next = inputNode;
                    count += 1;
                    result = true;
                    looping = false;
                }
                else {
                    currentNode = current->next;
                }
            }
            else if (current->next == nullptr) {
                currentNode->next = inputNode;
                count += 1;
                result = true;
                looping = false;
            }
            else {
                currentNode = current->next;
            }
        }
        
    }

    return result;
    
}

void LinkedList::displayStock() {

    Node* currNode = head;
    
    
    std::cout << std::setfill('-') << std::setw(10) << "-" << std::endl;

    std::cout << std::setfill(' ') << std::setw(5) << std::left << "ID" << "|" << std::setw(45) << "Name" << "|" << std::setw(12) << "Available" << "|" << std::setw(8) << "Price" << std::endl;
    
    std::cout << std::setfill('-') << std::setw(77) << "-" << std::endl;

    while (currNode != nullptr) {
        std::cout << std::setfill(' ') << std::setw(5) << currNode->data->id << "|" 
        << std::setw(45) << currNode->data->name << "|" 
        << std::setw(12) << currNode->data->amount << "|$" 
        << std::setw(3) << std::right << currNode->data->price.dollars << DECIMAL_CHAR
        << std::setw(4) << std::left << currNode->data->price.cents << std::endl;

        currNode = currNode->next;
    }
    std::cout << std::endl;
}

std::string LinkedList::getNewID() {
    Node* currNode = head;
    std::vector<int> vector;
    bool idFound{false};
    std::string result{};
    while (currNode !=  nullptr) {
        std::string currID = currNode->data->id;
        vector.push_back(stoi(currID.substr(FIRST_NUM_INDEX, ID_SIZE)));
        currNode = currNode->next;
    }
    int i{1};
    while (i < MAX_ID_NUM && idFound != true) {
        if (std::find(vector.begin(), vector.end(), i) == vector.end()) {
            std::stringstream ss;
            ss << "I" << std::setw(ID_SIZE) << std::setfill(ZERO_CHAR) << i;
            std::string newID = ss.str();
            result = newID;
            std::cout << result << std::endl;
            idFound = true;
        }
        else {
            i++;
        } 
    }    
    
    
    return result;
}

bool LinkedList::addStock(std::string newID) {
    bool result{true};
    bool looping{true};

    std::string name;
    std::string description;

    if (newID != EMPTY_STRING) {
        std::cout << "The id of the new stock will be: " << newID << std::endl;

        std::cout << "Enter the item name: ";
        std::getline(std::cin, name);
        
        if (!std::cin || name.empty()) {
            result = false;
        }
        else {
            std::cout << "Enter the item description: ";
            std::string description {};
            std::getline(std::cin, description);

            if (!std::cin || description.empty()) {
                result = false;
            }
            else {
                while (looping) {
                    std::cout << "Enter the item price: ";
                    std::string input {};
                    std::getline(std::cin, input);

                    size_t decimalTest = input.find(".");
                    std::string left = input.substr(0, decimalTest);
                    std::string right = input.substr(decimalTest + 1, input.size() - left.size() - 1);
                    if (right.size() == 1) {
                        right[FIRST_NUM_INDEX] = ZERO_CHAR;
                    }
                    
                    if (input.empty()) {
                        looping = false;
                        result = false;
                    }
                    else if (right[FIRST_NUM_INDEX] != ZERO_CHAR && right[FIRST_NUM_INDEX] != FIVE_CHAR) {
                        std::cout << "Error: the cents need to be a multiple of 5." << std::endl;
                        result = false;
                    }
                    else if (decimalTest == std::string::npos) {
                        looping = true;
                        std::cout << "Error: the price is not valid. Please try again." << std::endl;
                    }
                    else if (Helper::validateTotal(left) != true || Helper::validateTotal(right) != true) {
                        looping = true;
                        std::cout << "Error: the price is not valid. Please try again." << std::endl;
                    }
                    else if (left.size() > DOLLAR_MAX_SIZE || right.size() > CENTS_MAX_SIZE) {
                        looping  = true;
                        std::cout << "Error: line entered was too long. Please try again." << std::endl;
                    }
                    else {
                        Node* node{ new Node };
                        node->data->id = newID;
                        node->data->name = name;
                        node->data->description = description;
                        node->data->price.dollars = stoi(left);
                        node->data->price.cents = stoi(right);
                        node->data->amount = DEFAULT_STOCK_LEVEL;
                        // std::cout << "ID: " << node->data->id << "|" << std::endl;
                        // std::cout << "ID: " << node->data->name << "|" << std::endl;
                        // std::cout << "ID: " << node->data->description << "|" << std::endl;
                        // std::cout << "ID: " << node->data->price.dollars << "|" << std::endl;
                        // std::cout << "ID: " << node->data->price.cents << "|" << std::endl;
                        // std::cout << "ID: " << node->data->amount << "|" << std::endl;

                        if (addNode(node)) {
                            std::cout << "This item \"" << name << " - " << description << "\" has been added to the menu." << std::endl;
                            result = true;
                            looping = false;
                        }
                        else {
                            std::cout << "node failed to add." << std::endl;
                            delete node;
                            result = false;
                            looping = false;
                        }   
                        
                    }
                }
            }
        }
        
    }

    return result;
}

Node* LinkedList::getById(std::string id){

    Node* targetNode = nullptr;
    Node* currNode = head;

    for (unsigned i = 0; i < count; i++) {
        if (currNode->data->id == id) {
            targetNode = currNode;
            return targetNode;
        } 
        else if (currNode->next != nullptr) {
            currNode = currNode->next;
        }

    }
    return targetNode;
}

void LinkedList::resetStockCount(int inputCount) {
    Node* currNode = head;

    while (currNode != nullptr) {
        currNode->data->amount = inputCount;
        currNode = currNode->next;
    }

}

void LinkedList::deleteListNodes() {
    Node* currNode = head;

    while (currNode != nullptr) {
        head = currNode->next;
        delete currNode;
        currNode = head;
    }

}

void LinkedList::deleteNodebyID() {
    Node* currNode = head;
    Node* prevNode = nullptr;
    unsigned i{0};
    bool nodeExists{true};
    std::cout << "Enter the ID of the item you want removed: ";
    std::string id {};
    std::getline(std::cin, id);
    if (!id.empty()) {
        while (i < count && nodeExists && currNode != nullptr) {
            if (currNode->data->id == id) {
                if (currNode == head) {
                    head = currNode->next;
                }
                else {
                    prevNode->next = currNode->next;
                }
                    std::cout << "\"" << currNode->data->id << " - " << currNode->data->description << "\" has been removed from the system." << std::endl;

                    count -= 1;

                    delete(currNode);
                    nodeExists = false;
            }

        
            else {
                prevNode = currNode;
                currNode = currNode->next;
            }
            i++;
        }
        
        if (nodeExists) {
            std::cout << "\nError: Desired ID was not found." << std::endl;
        }
    }
}

std::vector<std::vector<std::string>> LinkedList::getListOutput() {
    Node* currNode = head;
    std::vector<std::vector<std::string>> columns{};
    

    while (currNode != nullptr) {
        std::vector<std::string> row{};
        unsigned dollar = currNode->data->price.dollars;
        unsigned cent = currNode->data->price.cents;
        std::string price{};
        if (cent == 0) {
            price = std::to_string(dollar) + "." "00";
        } 
        else if (cent == 5){
            price = std::to_string(dollar) + "." "05";
        }
        else {
            price = std::to_string(dollar) + "." + std::to_string(cent);
        }
        
        row.push_back(currNode->data->id);
        row.push_back(currNode->data->name);
        row.push_back(currNode->data->description);
        row.push_back(price);
        row.push_back(std::to_string(currNode->data->amount));

        columns.push_back(row);
        currNode = currNode->next;
        
    }

    return columns;
}

