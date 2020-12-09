#include "../my_AoC_utils.h"

namespace // to avoid duplicate variable definition error
{
    // put global variables here
    vector<pair<string, int> > V;
    set<int> Visited_positions;
}

enum result{Infinite_loop, Terminated};

int exec_prog(result *res)
{
    cnt = 0;
    int acc = 0;
    Visited_positions.clear();
    
    while(true)
    {
        Visited_positions.insert(cnt);
        if(V[cnt].first == "acc")
        {
            acc += V[cnt].second;
            ++cnt;
        }
        else if(V[cnt].first == "jmp")
        {
            cnt += V[cnt].second;
        }
        else if(V[cnt].first == "nop")
            ++cnt;
        else
            throw runtime_error(string("Unknown command \"" +
                V[cnt].first + "\" on index " + to_string(cnt) + "!"));
        
        if(cnt >= V.size())
        {
            *res = Terminated;
            return acc;
        }
        else if(Visited_positions.count(cnt) > 0)
        {
            *res = Infinite_loop;
            return acc;
        }
    }
}

// returns true if the swap is done, and false if the instruction was "acc"
bool swap_jmp_nop(int pos)
{
    if(V[pos].first == "jmp")
    {
        V[pos].first = "nop";
        return true;
    }
    else if(V[pos].first == "nop")
    {
        V[pos].first = "jmp";
        return true;
    }
    else
        return false;
}

void Day08(string input_file_path)
{
    in.open(input_file_path);
    if(in.fail())
        cerr << "Not successfully opened!\n";
    while(getline(in, line))
    {
        if(!line.empty())
        {
            stringstream linestream(line);
            linestream >> str_temp >> n;
            V.push_back(pair<string, int>(str_temp, n));
        }
    }
    in.close();
    
    result exec_result;
    int acc;
    cout << "Part One: " << exec_prog(&exec_result) << endl;
    
    for(i = 0; i < V.size(); ++i)
        if(swap_jmp_nop(i))
        {
            acc = exec_prog(&exec_result);
            if(exec_result == Terminated)
            {
                cout << "Part Two: " << acc << endl;
                break;
            }
            swap_jmp_nop(i);
        }
}
