#include "../my_AoC_utils.h"

namespace // to avoid duplicate variable definition error
{
    vector<tuple<string, int, int, int, int> > Rules;
    vector<int> MyNumbers;
    vector<vector<int> > NearbyNumbers;
    set<pair<int, int> > InvalidValues;

    // Unfortunately bitset's size must be known at compile-time.
    // rows: positions
    // columns: possible fields
    // true if possible, false if impossible
    vector<vector<bool> > PossibleFields;
}

void Day16(string input_file_path)
{
    // read input
    regex r(R"(([a-z\s]+): (\d+)-(\d+) or (\d+)-(\d+))");
    smatch m;
    in.open(input_file_path);
    if(in.fail())
        cerr << "Not successfully opened!\n";
    
    // read rules
    while(getline(in, line))
    {
        string::const_iterator search_start = line.begin(), search_end = line.end();
        if(regex_search(search_start, search_end, m, r))
        {
            Rules.push_back(make_tuple(m.str(1), stoi(m.str(2)), stoi(m.str(3)),                                stoi(m.str(4)), stoi(m.str(5))));
        }
        else
            break;
    }
    
    // find and read my ticket
    while(getline(in, line) && line != "your ticket:");
    getline(in, line);
    stringstream linestream(line);
    while(getline(linestream, str_temp, ','))
        MyNumbers.push_back(stoi(str_temp));
    
    // find and read nearby tickets
    while(getline(in, line) && line != "nearby tickets:");
    while(getline(in, line))
        if(!line.empty())
        {
            NearbyNumbers.push_back(vector<int>());
            stringstream linestream(line);
            while(getline(linestream, str_temp, ','))
                NearbyNumbers.back().push_back(stoi(str_temp));
        }
    
    in.close();
    
    // solve Part One and find possible fields for each position
    int part1 = 0;
    
    // set all possibilities to true
    PossibleFields.resize(MyNumbers.size(), vector<bool>(Rules.size(), true));
    for(i = 0; i < NearbyNumbers.size(); ++i)
        for(j = 0; j < NearbyNumbers[i].size(); ++j)
        {
            vector<bool> Candidates(Rules.size(), false);
            n = NearbyNumbers[i][j];
            for(k = 0; k < Rules.size(); ++k)
                if((n >= get<1>(Rules[k]) && n <= get<2>(Rules[k])) ||
                    (n >= get<3>(Rules[k]) && n <= get<4>(Rules[k])))
                   Candidates[k] = true;
            if(count(Candidates.begin(), Candidates.end(), true) == 0)
                part1 += n;
            else
                for(k = 0; k < Rules.size(); ++k)
                    if(!Candidates[k])
                        PossibleFields[j][k] = false;
        }
    cout << "Part One: " << part1 << endl;
    
    // if some position has only one possible field, eliminate it from other positions
    bool something_undetermined;
    do
    {
        something_undetermined = false;
        for(i = 0; i < PossibleFields.size(); ++i)
        {
            if(count(PossibleFields[i].begin(), PossibleFields[i].end(), true) == 1)
            {
                j = (int)(find(PossibleFields[i].begin(), PossibleFields[i].end(), true) - PossibleFields[i].begin());
                for(k = 0; k < PossibleFields.size(); ++k)
                    if(i != k)
                        PossibleFields[k][j] = false;
            }
            else
                something_undetermined = true;
        }
    }
    while(something_undetermined);
    
    // solve Part Two
    long long part2 = 1;
    for(i = 0; i < PossibleFields.size(); ++i)
        for(j = 0; j < PossibleFields[i].size(); ++j)
            if(PossibleFields[i][j] && get<0>(Rules[j]).substr(0, 9) == "departure")
                part2 *= MyNumbers[i];
    cout << "Part Two: " << part2 << endl;
}
