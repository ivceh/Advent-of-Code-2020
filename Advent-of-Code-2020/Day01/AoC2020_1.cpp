#include "../my_AoC_utils.h"

vector<int> entries;

void Day01(string input_file_path)
{
    // reading input
    in.open(input_file_path);
    if(in.fail())
        cerr << "Not successfully opened!\n";
    while(in >> n)
        entries.push_back(n);
    in.close();
    
    // solution A
    for(i = 0; i < entries.size(); ++i)
        for(j = i + 1; j < entries.size(); ++j)
            if(entries[i] + entries[j] == 2020)
                cout << "Part One: " << entries[i] * entries[j] << endl;
    for(i = 0; i < entries.size(); ++i)
        for(j = i + 1; j < entries.size(); ++j)
            for(k = j + 1; k < entries.size(); ++k)
                if(entries[i] + entries[j] + entries[k] == 2020)
                    cout << "Part Two: "
                         << entries[i] * entries[j] * entries[k] << endl;
}
