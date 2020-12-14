#include "../my_AoC_utils.h"
#define UNDEFINED -1

namespace // to avoid duplicate variable definition error
{
    // put global variables here
    int earliest_depart;
    vector<int> Buses;
}

inline int waiting_time(int earliest, int busID)
{
    return busID - earliest % busID;
}

void Day13(string input_file_path)
{
    // read input
    in.open(input_file_path);
    if(in.fail())
        cerr << "Not successfully opened!\n";
    getline(in, line);
    earliest_depart = stoi(line);
    while(getline(in, line, ','))
    {
        if(line == "x")
            Buses.push_back(UNDEFINED);
        else
            Buses.push_back(stoi(line));
    }
    in.close();
    
    // solve Part One
    int min_wait = UNDEFINED, minID = UNDEFINED;
    for(i = 1; i < Buses.size(); ++i)
        if(Buses[i] != UNDEFINED)
        {
            int wait = waiting_time(earliest_depart, Buses[i]);
            if(min_wait == UNDEFINED || wait < min_wait)
            {
                min_wait = wait;
                minID = Buses[i];
            }
        }
    cout << "Part One: " << minID * min_wait << endl;
    
    // solve Part Two
    long long step = 1, solution2 = 0;
    for(i = 0; i < Buses.size(); ++i)
        if(Buses[i] != UNDEFINED)
        {
            while((solution2 + i) % Buses[i] != 0)
                solution2 += step;
            
            step *= Buses[i]; // because IDs in my input are pairwise coprime,
            // otherwise I would write step = LCM(step, Buses[i]);
        }
    cout << "Part Two: " << solution2 << endl;
}
