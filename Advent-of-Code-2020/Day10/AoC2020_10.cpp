#include "../my_AoC_utils.h"

namespace // to avoid duplicate variable definition error
{
    // put global variables here
}

void Day10(string input_file_path)
{
    in.open(input_file_path);
    if(in.fail())
        cerr << "Not successfully opened!\n";
    while(getline(in, line))
    {
        if(!line.empty())
        {
            stringstream linestream(line);
        }
    }
    in.close();
    
    cout << "Unknown\n";
}
