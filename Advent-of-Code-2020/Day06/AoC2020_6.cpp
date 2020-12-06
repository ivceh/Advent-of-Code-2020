#include "../my_AoC_utils.h"

namespace // to avoid duplicate variable definition error
{
    // put global variables here
vector<vector<set<char> > > V;
}

void Day06(string input_file_path)
{
    // reading input
    string str_field;
    in.open(input_file_path);
    if(in.fail())
        cerr << "Not successfully opened!\n";
    vector<set<char> > Group;
    set<char> Person;
    while(getline(in, line))
    {
        if(line.empty())
        {
            V.push_back(move(Group));
            Group.clear();
        }
        else
        {
            Person.clear();
            for (auto c : line)
                Person.insert(c);
            Group.push_back(move(Person));
        }
    }
    if(!Group.empty())
    {
        V.push_back(move(Group));
        Group.clear();
    }
    in.close();
    
    for(auto Group : V)
    {
        for(char c = 'a'; c <= 'z'; ++c)
        {
            if(any_of(Group.begin(), Group.end(), [c](set<char> Person)
                {
                    return Person.count(c) > 0;
                }))
            {
                ++cnt;
                if(all_of(Group.begin(), Group.end(), [c](set<char> Person)
                    {
                        return Person.count(c) > 0;
                    }))
                    ++cnt2;
            }
        }
    }
    cout << "Part One: " << cnt << endl;
    cout << "Part Two: " << cnt2 << endl;
}
