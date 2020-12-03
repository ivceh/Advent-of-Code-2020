#include "../my_AoC_utils.h"

void Day04(string input_file_path)
{
    // reading input
    in.open(input_file_path);
    if(in.fail())
        cerr << "Not successfully opened!\n";
    while(in >> line)
        if(!line.empty())
            ;
    in.close();
    
    cout << "Unknown\n";
}
