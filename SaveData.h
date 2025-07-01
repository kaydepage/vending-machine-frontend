#ifndef SAVEDATA_H
#define SAVEDATA_H

#include "LinkedList.h"

#include <fstream>
#include <iterator>
#include <ostream>
#include <vector>

/**
 * Class for writing Stock and Coin data to file
*/
class SaveData{
private:
    // Constructor
    SaveData();
public:
    // Outputs delimited string data to file
    static bool lineWrite(std::vector<std::vector<std::string>> output, std::string outputPath, char delimiter);
};

#endif