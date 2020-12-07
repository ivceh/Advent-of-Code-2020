#include "../my_AoC_utils.h"

namespace // to avoid duplicate variable definition error
{
    // put global variables here

    // keys: all bags mentioned
    // values: keys: bags directly contained in key bag
    //         values: their quantities
    map<string, map<string, int> > Bags;
}

// dynamic programming used to avoid multiple checks for the same type
bool contains_x(string bag, string x)
{
    static map<string, bool> results;
    map<string, bool>::const_iterator it = results.find(bag);
    if(it != results.end())
        return it->second;
    else
    {
        for(pair<string, int> const str_temp2 : Bags[bag])
        {
            if(str_temp2.first == x || contains_x(str_temp2.first, x))
            {
                results[bag] = true;
                return true;
            }
        }
        results[bag] = false;
        return false;
    }
}

// dynamic programming used to avoid multiple checks for the same type
int total_bags(string bag)
{
    int sum = 0;
    
    static map<string, int> results;
    map<string, int>::const_iterator it = results.find(bag);
    if(it != results.end())
        return it->second;
    else
    {
        for(auto P : Bags[bag])
        {
            sum += P.second * (total_bags(P.first) + 1);
        }
        return sum;
    }
}

void Day07(string input_file_path)
{
    // reading input
    regex r1(R"((([a-z]|\s)+) bags contain)"),
        r2(R"((\d+) (([a-z]|\s)+) bags?[,.])");
    smatch m;
    in.open(input_file_path);
    if(in.fail())
        cerr << "Not successfully opened!\n";
    while(getline(in, line))
    {
        if(!line.empty() && regex_search(line, m, r1))
        {
            str_temp = m.str(1);
            map<string, int> Subbags;
            string::const_iterator search_start = line.begin(),
                search_end = line.end();
            while(regex_search(search_start, search_end, m, r2))
            {
                Subbags[m.str(2)] = stoi(m.str(1));
                search_start = m.suffix().first;
            }
            Bags[str_temp] = move(Subbags);
        }
    }
    in.close();
    
    cnt = 0;
    for(pair<string, map<string, int> > P : Bags)
        if(contains_x(P.first, "shiny gold"))
            ++cnt;
    cout << "Part One: " << cnt << endl;
    cout << "Part Two: " << total_bags("shiny gold") << endl;
}
