#include "../my_AoC_utils.h"

namespace // to avoid duplicate variable definition error
{
    // put global variables here
    vector<int> V;
}

void Day09(string input_file_path)
{
    in.open(input_file_path);
    if(in.fail())
        cerr << "Not successfully opened!\n";
    while(in >> n)
    {
        V.push_back(n);
    }
    in.close();
    
    for(i = 25; i < V.size(); ++i)
    {
        for(j = i-25; j < i; ++j)
            for(k = i-25; k<i; ++k)
            {
                if(V[j] + V[k] == V[i])
                    goto found;
            }
            cout << "Part One: " << V[i] << endl;
        goto endloop;
        found: ;
    }
    endloop:
    
    n = V[i];
    for(i = 0; i < V.size(); ++i){
        cnt = V[i];
        for(j = i + 1; j < V.size(); ++j)
        {
            cnt += V[j];
            if(cnt == n)
            {
                int part2 = *min_element(next(V.begin(), i),
                                         next(V.begin(), j + 1)) +
                    *max_element(next(V.begin(), i),
                                 next(V.begin(), j + 1));
                cout << "Part Two: " << part2 << endl;
            }
        }
    }
}
