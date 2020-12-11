#include "../my_AoC_utils.h"

namespace // to avoid duplicate variable definition error
{
    // put global variables here
    vector<string> Grid;
}

vector<vector<uint8_t> > occupied_neighbours_part1(const vector<string>& Grid)
{
    vector<vector<uint8_t>> V(Grid.size(), vector<uint8_t>(Grid[0].size(), 0));
    
    for(int i = 0; i < Grid.size(); ++i)
        for(int j = 0; j < Grid[i].size(); ++j)
            if(Grid[i][j] == '#')
                for(int k = -1; k <= 1; ++k)
                    if(i + k >= 0 && i + k < Grid.size())
                        for(int l = -1; l <= 1; ++l)
                            if(j + l >= 0 && j + l < Grid[i].size())
                                ++V[i + k][j + l];
    
    return V;
}

vector<vector<uint8_t> > occupied_neighbours_part2(const vector<string>& Grid)
{
    vector<vector<uint8_t>> V(Grid.size(), vector<uint8_t>(Grid[0].size(), 0));
    
    for(int i = 0; i < Grid.size(); ++i)
        for(int j = 0; j < Grid[i].size(); ++j)
            if(Grid[i][j] == '#')
                for(int k = -1; k <= 1; ++k)
                    for(int l = -1; l <= 1; ++l)
                        if(k != 0 || l != 0)
                            for(int m = 1;
                                i + m * k >= 0 && i + m * k < Grid.size() &&
                                j + m * l >= 0 && j + m * l < Grid[i].size();
                                ++m)
                                if(Grid[i + m * k][j + m * l] != '.')
                                {
                                    ++V[i + m * k][j + m * l];
                                    break;
                                }
    
    return V;
}

long count_stable_occupied(vector<string> Grid,
    function<vector<vector<uint8_t> > (vector<string>)> f)
{
    bool something_changed;
    do
    {
        something_changed = false;
        vector<vector<uint8_t>> occupied_neighbours = f(Grid);
        for(int i = 0; i < Grid.size(); ++i)
            for(int j = 0; j < Grid[i].size(); ++j)
            {
                if(Grid[i][j] == 'L' && occupied_neighbours[i][j] == 0)
                {
                    Grid[i][j] = '#';
                    something_changed = true;
                }
                else if(Grid[i][j] == '#' && occupied_neighbours[i][j] >= 5)
                {
                    Grid[i][j] = 'L';
                    something_changed = true;
                }
            }
    }
    while(something_changed);
    
    return accumulate(Grid.begin(), Grid.end(), 0, [](int s, string Row)
    {
        return s + count(Row.begin(), Row.end(), '#');
    });
}

void Day11(string input_file_path)
{
    in.open(input_file_path);
    if(in.fail())
        cerr << "Not successfully opened!\n";
    while(getline(in, line))
    {
        if(!line.empty())
        {
            Grid.push_back(line);
        }
    }
    in.close();
    
    cout << "Input ";
    measure_time();
    
    cout << "Part One: "
         << count_stable_occupied(Grid, occupied_neighbours_part1)
         << endl;
    
    measure_time();
    
    cout << "Part Two: "
         << count_stable_occupied(Grid, occupied_neighbours_part2)
         << endl;
}
