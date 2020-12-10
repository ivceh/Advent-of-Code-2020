#include "../my_AoC_utils.h"

namespace // to avoid duplicate variable definition error
{
    // put global variables here
    vector<int> V, Diff;
    vector<long long> Arrangements;
}

void Day10(string input_file_path)
{
    in.open(input_file_path);
    if(in.fail())
        cerr << "Not successfully opened!\n";
    while(in >> n)
    {
        V.push_back(n);
    }
    in.close();
    
    sort(V.begin(), V.end());
    Diff.resize(5);
    ++Diff[V[0]];
    for(i = 0; i < V.size() - 1; ++i)
        ++Diff[V[i + 1] - V[i]];
    ++Diff[3];
    cout << "Part One: " << Diff[1] * Diff[3] << endl;
    
    Arrangements.resize(V.size());
    for(i = 0; i < V.size(); ++i)
    {
        for(j = i - 1; j >= 0 && V[j] >= V[i] - 3; --j)
            Arrangements[i] += Arrangements[j];
        if(V[i] <= 3)
            ++Arrangements[i];
    }
    cout << "Part Two: " << Arrangements.back() << endl;
}
