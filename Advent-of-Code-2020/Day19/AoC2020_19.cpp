#include "../my_AoC_utils.h"

namespace // to avoid duplicate variable definition error
{
    // put global variables here
vector<string> Lines;
}

string regex_rule(int n, int part)
{
    if(part == 2 && (n == 8 || n == 11))
    {
        if(n == 8)
            return regex_rule(42, 2) + "+";
        else // n == 11
        {
            string result = "(", r42 = regex_rule(42, 2), r31 = regex_rule(31, 2);
            
            // In my case 5 was enough,
            // if it gives too low answers it should be increased to 10
            for(int i = 1; i <= 5; ++i)
            {
                if(i > 1)
                    result.push_back('|');
                result += r42 + "{" + to_string(i) + "}" +
                          r31 + "{" + to_string(i) + "}";
            }
            result.push_back(')');
            return result;
        }
    }
    if(Lines[n][0] == '"')
        return Lines[n].substr(1, Lines[n].size() - 2);
    else
    {
        stringstream linestream(Lines[n]);
        string result = "(";
        while(linestream >> str_temp)
        {
            if(str_temp == "|")
                result.push_back('|');
            else
                result += regex_rule(stoi(str_temp), part);
        }
        result.push_back(')');
        return result;
    }
}

void Day19(string input_file_path)
{
    // read input
    in.open(input_file_path);
    if(in.fail())
        cerr << "Not successfully opened!\n";
    while(getline(in, line) && !line.empty())
    {
        i = stoi(line.substr(0, line.find(":")));
        if(Lines.size() <= i)
            Lines.resize(i + 1);
        Lines[i] = line.substr(line.find(":") + 2);
    }
    regex r(regex_rule(0, 1)), r2(regex_rule(0, 2));
    smatch m;
    int part1 = 0, part2 = 0;
    while(getline(in, line) && !line.empty())
    {
        string::const_iterator search_start = line.begin(), search_end = line.end();
        if(regex_match(search_start, search_end, m, r))
            ++part1;
        if(regex_match(search_start, search_end, m, r2))
            ++part2;
    }
    in.close();
    
    cout << "Part One: " << part1 << endl;
    cout << "Part Two: " << part2 << endl;
}
