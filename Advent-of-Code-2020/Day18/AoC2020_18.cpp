#include "../my_AoC_utils.h"

namespace // to avoid duplicate variable definition error
{
    // put global variables here
}

void Day18(string input_file_path)
{
    // read input
    in.open(input_file_path);
    if(in.fail())
        cerr << "Not successfully opened!\n";
    while(getline(in, line))
    {
        if(!line.empty())
        {
            stringstream linestream(line);
            // find in all files: Shift + Cmd + F
        }
    }
    in.close();
    
    cout << "Unknown\n";
}
