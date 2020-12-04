#include "../my_AoC_utils.h"

vector<int> entries;

void Day01(string input_file_path)
{
    // reading input
    in.open(input_file_path);
    measure_time(false);
    if(in.fail())
        cerr << "Not successfully opened!\n";
    while(in >> n)
        entries.push_back(n);
    in.close();
    measure_time();
    
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
    measure_time();
    
    // solution B
    sort(entries.begin(), entries.end());
    for(i = 0; 2 * entries[i] < 2020; ++i)
    {
        j = 2020 - entries[i];
        if(binary_search(entries.begin(), entries.end(), j))
            cout << "Part One: " << entries[i] * j << endl;
    }
    for(i = 0; 3 * entries[i] < 2020; ++i)
        for(j = i + 1; entries[i] + 2 * entries[j] < 2020; ++j)
        {
            k = 2020 - entries[i] - entries[j];
            if(binary_search(entries.begin(), entries.end(), k))
                cout << "Part Two: " << entries[i] * entries[j] * k << endl;
        }
    measure_time();
    
    // solution C
    // entries are already sorted in solution B
    i = 0;
    long j = entries.size() - 1;
    while(i < j)
    {
        int s = entries[i] + entries[j];
        if(s == 2020)
        {
            cout << "Part One: " << entries[i] * entries[j] << endl;
            ++i;
            --j;
        }
        else if(s < 2020)
            ++i;
        else
            --j;
    }
    for(i = 0; 3 * entries[i] < 2020; ++i)
    {
        j = i + 1;
        long k = entries.size() - 1;
        while(j < k)
        {
            int s = entries[i] + entries[j] + entries[k];
            if(s == 2020)
            {
                cout << "Part Two: " << entries[i] * entries[j] * entries[k] <<
                    endl;
                ++j;
                --k;
            }
            else if(s < 2020)
                ++j;
            else
                --k;
        }
    }
}
