#include "CatList.h"

CatLinkedList::CatLinkedList() {
   head = nullptr;  
   count = {0}; 
}

CatLinkedList::~CatLinkedList() {
}

int CatLinkedList::getCount() {
    return count;
}

CatNode* CatLinkedList::getHead() {
    return head;
}

void CatLinkedList::addHead(CatNode* node) {

    head = node;
    count += 1;
}


void CatLinkedList::deleteListNodes() {
    CatNode* currNode = head;

    while (currNode != nullptr) {
        head = currNode->next;
        currNode->data->deleteListNodes();
        delete currNode;
        currNode = head;
    }

}



bool CatLinkedList::addCatNode(CatNode* inputNode) {
    bool result{true};
    CatNode* currentNode = head;
    std::string currentName{EMPTY_STRING};
    std::string inputName{inputNode->category};
    bool looping{true};
    while (looping) {
        std::string nextName;

        if (currentNode != nullptr) {
            currentName = {currentNode->category};
        }

        //checks whether the catlist is empty, and if empty, makes the node the head.
        if (count == 0) {
            addHead(inputNode);
            result = true;
            looping = false;
        }
        
        else if (inputName.compare(currentName) == SAME_VALUE) {
            result = false;
            looping = false;
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
            CatNode* current = currentNode;

            if (current->next != nullptr) {
                nextName = current->next->category;
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

void CatLinkedList::displayCategories() {
    CatNode* currNode = head;
    while (currNode != nullptr) {
        std::cout << "\n" << currNode->category << " Menu" << std::endl;
        currNode->data->displayStock();
        currNode = currNode->next;
    }
}

CatNode* CatLinkedList::findCatNode(std::string category){

    CatNode* targetNode = nullptr;
    CatNode* currNode = head;
    CatNode* result = nullptr;

    for (unsigned i = 0; i < count; i++) {
        if (currNode->category == category) {
            targetNode = currNode;
            result = targetNode;
        } 
        else if (currNode->next != nullptr) {
            currNode = currNode->next;
        }
        else {
            result = nullptr;
        }

    }
    return result;
}

std::string CatLinkedList::getNewID() {
    CatNode* currNode = head;
    Node* stockNode = nullptr;
    std::vector<int> vector;
    bool idFound{false};
    std::string result{};
    //getting all id ints and adding them to a vector.
    while (currNode !=  nullptr) {
        stockNode = currNode->data->getHead();
        while (stockNode != nullptr) {
            std::string currID = stockNode->data->id;
            vector.push_back(stoi(currID.substr(FIRST_NUM_INDEX, ID_SIZE)));
            stockNode = stockNode->next;
        }

        currNode = currNode->next;
    }
    int i{1};
    while (i < MAX_ID_NUM && idFound != true) {
        //if i is not found in the vector, it is set as the new id int.
        if (std::find(vector.begin(), vector.end(), i) == vector.end()) {
            std::stringstream ss;
            ss << "I" << std::setw(ID_SIZE) << std::setfill(ZERO_CHAR) << i;
            std::string newID = ss.str();
            result = newID;
            idFound = true;
        }
        else {
            i++;
        } 
    }    
    
    
    return result;
}

bool CatLinkedList::addStock() {
    bool result{true};
    bool looping{true};
    while (looping) {
        std::cout << "Enter the category you are adding stock to: ";
        std::string name {};
        std::getline(std::cin, name);
        
        if (!std::cin || name.empty()) {
            looping = false;
            result = false;
        }
        else {
            CatNode* foundNode = findCatNode(name);
            if (foundNode == nullptr) {
                std::cout << "No category found with name: " << name << std::endl;
                result = false;
            }
            else {
                std::string newId = getNewID();
                if (newId == "") {
                    std::cout << "No space available to add stock." << std::endl;
                    result = false;
                    looping = false;

                }
                else {
                    if(foundNode->data->addStock(newId)) {
                        result = true;
                        looping = false;
                    }
                    else {
                        result = false;
                        looping = false;
                    }
                    
                }
            }
        }
    }
    

    return result;
}

Node* CatLinkedList::getById(std::string id) {
    Node* result = nullptr;
    CatNode* currNode = head;
    while (currNode != nullptr && result == nullptr) {
        if (currNode->data != nullptr) {
            result = currNode->data->getById(id);
        }
        currNode = currNode->next;
    }

    return result;
}

void CatLinkedList::resetStockCount(int amount) {
    CatNode* currNode = head;
    while (currNode != nullptr) {
        if (currNode->data != nullptr) {
            currNode->data->resetStockCount(amount);
        }

        currNode = currNode->next;
    }
}

std::vector<std::vector<std::string>> CatLinkedList::getListOutput() {
    CatNode* currNode = head;
    std::vector<std::vector<std::string>> columns{};
    while (currNode != nullptr) {
        
        if (currNode->data != nullptr) {
            Node* currStockNode = currNode->data->getHead();

            while (currStockNode != nullptr) {
                std::vector<std::string> row{};
                unsigned dollar = currStockNode->data->price.dollars;
                unsigned cent = currStockNode->data->price.cents;
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
                
                row.push_back(currStockNode->data->id);
                row.push_back(currNode->category + CAT_NAME_SEPERATOR + currStockNode->data->name);
                row.push_back(currStockNode->data->description);
                row.push_back(price);
                row.push_back(std::to_string(currStockNode->data->amount));

                columns.push_back(row);
                currStockNode = currStockNode->next;
                
            }
        }

        currNode = currNode->next;
        
    }
    
    return columns;
}

void CatLinkedList::deleteNodebyID() {

    
    std::cout << "Enter the ID of the item you want removed: ";
    std::string id {};
    std::getline(std::cin, id);
    if (!id.empty()) {
        CatNode* currNode = head;
        
        bool nodeExists{true};
        while (currNode != nullptr) {
            Node* currStockNode = currNode->data->getHead();
            Node* prevNode = nullptr;
            int i{0};
            //std::cout << currNode->category << std::endl;
            while (i < currNode->data->getCount() && nodeExists && currStockNode != nullptr) {

                //std::cout << currStockNode->data->id << " " << currStockNode->data->name << std::endl;
                if (currStockNode->data->id == id) {
                    if (currStockNode == currNode->data->getHead()) {
                        
                        currNode->data->addHead(currStockNode->next);
                    }
                    else {
                        prevNode->next = currStockNode->next;
                    }
                        std::cout << "\"" << currStockNode->data->id << " - " << 
                        currStockNode->data->name << " - " << currStockNode->data->description << 
                        "\" has been removed from the system." << std::endl;

                        count -= 1;

                        delete(currStockNode);
                        nodeExists = false;
                }

            
                else {
                    prevNode = currStockNode;
                    currStockNode = currStockNode->next;
                }
                i++;
            }

            currNode = currNode->next;
        }




        
        
        if (nodeExists) {
            std::cout << "\nError: Desired ID was not found." << std::endl;
        }
    }
}



CatNode::CatNode(): data{new LinkedList()} {

}
CatNode::~CatNode(){
    delete data;
}

