#include "../my_AoC_utils.h"

namespace // because there is already variable V in Day03
{
    // contains numbers of seats
    vector<int> V;
}

void Day05(string input_file_path)
{
    // reading input
    string str_field;
    in.open(input_file_path);
    if(in.fail())
        cerr << "Not successfully opened!\n";
    string S;
    char *endpointer;
    while(in >> S)
    {
        // convert seat code to binary number
        replace(S.begin(), S.end(), 'F', '0');
        replace(S.begin(), S.end(), 'B', '1');
        replace(S.begin(), S.end(), 'L', '0');
        replace(S.begin(), S.end(), 'R', '1');
        // C function to read numbers in any base (2 in this case)
        V.push_back((int)strtol(S.c_str(), &endpointer, 2));
    }
    in.close();
    
    sort(V.begin(), V.end());
    cout << "Part One: " << V.back() << endl;
    for(i = 0; i < V.size() - 1; ++i)
        if(V[i + 1] > V[i] + 1)
            cout << "Part Two: " << V[i] + 1 << endl;
}
