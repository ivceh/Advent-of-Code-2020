#include "../my_AoC_utils.h"
#define UNDEFINED -1

namespace // to avoid duplicate variable definition error
{
    map<string, function<long long (long long, long long)> > Operators =
        {{"+", [](long long a, long long b){return a + b;}},
         {"*", [](long long a, long long b){return a * b;}}};
}

long long evaluate(const string& line, map<string, int> Priorities)
{
    stack<pair<long long, string> > S;
    stringstream linestream(line);
    long long result = 0;
    Priorities["("] = -1;
    while (linestream >> str_temp)
    {
        if(Operators.count(str_temp) > 0) // operator
        {
            while (!S.empty() && Priorities[S.top().second] >= Priorities[str_temp])
            {
                result = Operators[S.top().second](S.top().first, result);
                S.pop();
            }
            S.push(make_pair(result, str_temp));
        }
        else // non-operator (number and parentheses)
        {
            long left_parenth = count(str_temp.begin(), str_temp.end(), '('),
                 right_parenth = count(str_temp.begin(), str_temp.end(), ')');
            for(long i = 0; i  < left_parenth; ++i)
                S.push(make_pair(UNDEFINED, "("));
            result = stoll(str_temp.substr(left_parenth,
                            str_temp.size() - left_parenth - right_parenth));
            for(long i = 0; i < right_parenth; ++i)
            {
                while(!S.empty() && S.top().second != "(")
                {
                    result = Operators[S.top().second](S.top().first, result);
                    S.pop();
                }
                S.pop(); // remove '(' from the stack
            }
        }
    }
    while(!S.empty())
    {
        result = Operators[S.top().second](S.top().first, result);
        S.pop();
    }
    return result;
}

void Day18(string input_file_path)
{
    long long part1 = 0, part2 = 0;
    in.open(input_file_path);
    if(in.fail())
        cerr << "Not successfully opened!\n";
    while(getline(in, line))
    {
        if(!line.empty())
        {
            part1 += evaluate(line, {{"+", 0}, {"*", 0}});
            part2 += evaluate(line, {{"+", 1}, {"*", 0}});
        }
    }
    in.close();
    
    cout << "Part One: " << part1 << endl;
    cout << "Part Two: " << part2 << endl;
}
