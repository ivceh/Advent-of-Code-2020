#include "../my_AoC_utils.h"
#define UNDEFINED -1

namespace // to avoid duplicate variable definition error
{
    // put global variables here
    vector<int> Numbers;
    int current, previous;
}

int n_th_number(int n)
{
    // vector<int> was much faster than map<int, int> and unordered_map<int, int>
    // although only about 12% of it was used
    vector<int> Last_appearance = vector<int>(n, UNDEFINED);
    for(i = 0; i < Numbers.size() - 1; ++i)
        Last_appearance[Numbers[i]] = i;
    current = Numbers.back();
    for(i = (int)Numbers.size(); i < n; ++i)
    {
        previous = current;
        if(Last_appearance[previous] == UNDEFINED)
            current = 0;
        else
            current = i - 1 - Last_appearance[previous];
        Last_appearance[previous] = i - 1;
    }
    return current;
}

void Day15(string input_file_path)
{
    // read input
    in.open(input_file_path);
    if(in.fail())
        cerr << "Not successfully opened!\n";
    while(getline(in, line, ','))
        Numbers.push_back(stoi(line));
    in.close();
    
    cout << "Part One: " << n_th_number(2020) << endl;
    cout << "Part Two: " << n_th_number(30000000) << endl;
}
