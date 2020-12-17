#include "../my_AoC_utils.h"

namespace // to avoid duplicate variable definition error
{
    // put global variables here
    set<vector<int> > ActivePoints;
}

// receives vector of points by reference, adds all of their neighbors to it
void add_neighbors(vector<vector<int> > *Vp, long k = 0)
{
    if(k < (*Vp)[0].size())
    {
        long n = Vp->size();
        for(int i = 0; i < n; ++i)
        {
            auto P = (*Vp)[i];
            P[k] -= 1;
            Vp->push_back(P);
            P[k] += 2;
            Vp->push_back(P);
        }
        add_neighbors(Vp, k + 1);
    }
}

long active_after(int cycles, const set<vector<int> >& InitiallyActive,
                  int dim)
{
    set<vector<int> > Active, ActiveNext;
    
    // keys: all positions with at least one active neighbor
    // values: numbers of active neighbors
    map<vector<int>, int> ActiveNeighbors;
    
    // add coordinate 0 for additional dimensions
    for(auto P : InitiallyActive)
    {
        P.resize(dim, 0);
        Active.insert(P);
    }
    
    for(int i = 0; i < cycles; ++i)
    {
        // count active neighbors for all positions
        ActiveNeighbors.clear();
        for(auto P : Active)
        {
            vector<vector<int> > Neighbors{P};
            add_neighbors(&Neighbors);
            for(auto P2 : Neighbors)
                ++ActiveNeighbors[P2];
        }
        
        // find all positions that will be active in the next step
        ActiveNext.clear();
        for(auto P : ActiveNeighbors)
            if(P.second == 3 || (P.second == 4 && Active.count(P.first) > 0))
                ActiveNext.insert(P.first);
        Active = move(ActiveNext);
    }
    return Active.size();
}

void Day17(string input_file_path)
{
    // read input
    in.open(input_file_path);
    if(in.fail())
        cerr << "Not successfully opened!\n";
    i = 0;
    while(getline(in, line))
    {
        if(!line.empty())
        {
            for(j = 0; j < line.size(); ++j)
            if(line[j] == '#')
                ActivePoints.insert({i, j});
            ++i;
        }
    }
    in.close();
    
    cout << "Part One: " << active_after(6, ActivePoints, 3) << endl;
    cout << "Part Two: " << active_after(6, ActivePoints, 4) << endl;
}
