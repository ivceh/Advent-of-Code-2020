#include "../my_AoC_utils.h"

namespace // to avoid duplicate variable definition error
{
    // put global variables here
    map<long long, long long> Memory1, Memory2;
    string mask;
}

void update_memory1(long long address, long long value)
{
    string str_mask0 = mask, str_mask1 = mask;
    long long llmask0, llmask1;
    char *endpointer;
    replace(str_mask0.begin(), str_mask0.end(), 'X', '1');
    llmask0 = strtoll(str_mask0.c_str(), &endpointer, 2);
    replace(str_mask1.begin(), str_mask1.end(), 'X', '0');
    llmask1 = strtoll(str_mask1.c_str(), &endpointer, 2);
    Memory1[address] = (value & llmask0) | llmask1;
}

// char 'O' is used for bits overwritten with 0
void update_memory2(long long address, long long value, string str_mask)
{
    size_t posX = str_mask.find('X');
    if(posX == string::npos)
    {
        string str_mask1 = str_mask;
        long long llmask0, llmask1;
        char *endpointer;
        replace(str_mask.begin(), str_mask.end(), '0', '1');
        replace(str_mask.begin(), str_mask.end(), 'O', '0');
        llmask0 = strtoll(str_mask.c_str(), &endpointer, 2);
        replace(str_mask1.begin(), str_mask1.end(), 'O', '0');
        llmask1 = strtoll(str_mask1.c_str(), &endpointer, 2);
        Memory2[(address & llmask0) | llmask1] = value;
    }
    else
    {
        str_mask[posX] = 'O';
        update_memory2(address, value, str_mask);
        str_mask[posX] = '1';
        update_memory2(address, value, str_mask);
    }
}

void Day14(string input_file_path)
{
    regex r1(R"(mask = ([01X]+))"),
        r2(R"(mem\[([0-9]+)\] = ([0-9]+))");
    smatch m;
    in.open(input_file_path);
    if(in.fail())
        cerr << "Not successfully opened!\n";
    while(getline(in, line))
    {
        if(!line.empty())
        {
            string::const_iterator search_start = line.begin(),
                search_end = line.end();
            if(regex_search(search_start, search_end, m, r1))
            {
                mask = m.str(1);
            }
            else if(regex_search(search_start, search_end, m, r2))
            {
                update_memory1(stoll(m.str(1)), stoll(m.str(2)));
                update_memory2(stoll(m.str(1)), stoll(m.str(2)), mask);
            }
        }
    }
    in.close();
    
    long long part1 = 0, part2 = 0;
    for(pair<long long, long long> P : Memory1)
        part1 += P.second;
    cout << "Part One: " << part1 << endl;
    for(pair<long long, long long> P : Memory2)
        part2 += P.second;
    cout << "Part Two: " << part2 << endl;
}
