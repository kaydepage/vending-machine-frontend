#include "SaveData.h"


SaveData::SaveData(){}

bool SaveData::lineWrite(std::vector<std::vector<std::string>> output, std::string outputPath, char delimiter)
{
    
    std::ofstream outf(outputPath);
    char del = delimiter;
    for (unsigned i = 0; i<output.size();i++)
    {
        std::string row = "";
        for (unsigned j = 0; j<output[i].size(); j++){
            if (j == 0){
                row = row + output[i][j];
            } else {
            row = row + del + output[i][j];
            }
        }    
        outf<<row << "\n";
       
    }
    return true;
}