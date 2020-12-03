#include "../my_AoC_utils.h"

vector<string> V;

int cnt_trees(int moveX, int moveY, vector<string> const&V)
{
    cnt = 0;
    for(i = j = 0; i < V.size(); i += moveY, j += moveX)
    {
        if(V[i][j % V[i].size()] == '#')
            ++cnt;
    }
    return cnt;
}

void Day03(string input_file_path)
{
    // reading input
    in.open(input_file_path);
    if(in.fail())
        cerr << "Not successfully opened!\n";
    while(in >> line)
        if(!line.empty())
            V.push_back(line);
    in.close();
    
    cout << "Part One: " << cnt_trees(3, 1, V) << endl;
    
    long long part2 = (long long)cnt_trees(1, 1, V) * cnt_trees(3, 1, V) *
        cnt_trees(5, 1, V) * cnt_trees(7, 1, V) * cnt_trees(1, 2, V);
    cout << "Part Two: " << part2 << endl;
}
