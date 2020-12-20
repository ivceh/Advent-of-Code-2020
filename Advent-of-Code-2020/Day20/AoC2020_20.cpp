/* My long and disorganized backtracking solution with some debugging outputs in the comments and one Heisenbug (https://en.wikipedia.org/wiki/Heisenbug).
I hope I will refactor it in the future. */



#include "../my_AoC_utils.h"

namespace // to avoid duplicate variable definition error
{
    // put global variables here
map<int, vector<vector<string> > > M;
}

vector<string> flip(vector<string> V) // is this called horizontal of vertical?
{
    reverse(V.begin(), V.end());
    return V;
}

vector<string> rotate(vector<string> V)
{
    vector<string> V2(V[0].size());
    int i, j;
    for(auto Line : V)
    {
        for(i = 0, j = (int)V2.size() - 1; j >= 0; ++i, --j)
        V2[j].push_back(Line[i]);
    }
    return V2;
}

void add_flipped_and_rotated(vector<vector<string> > *Vp)
{
    long n = Vp->size();
    for(int i = 0; i < n; ++i)
        Vp->push_back(flip((*Vp)[i]));
    n = Vp->size();
    for(int i = 0; i < n; ++i)
    {
        auto V2 = (*Vp)[i];
        for(int j = 0; j < 3; ++j)
        {
            V2 = rotate(V2);
            Vp->push_back(V2);
        }
    }
}

bool match_left_right(vector<string> Left, vector<string> Right)
{
    if(Left.size() != Right.size())
        throw runtime_error("Dimension does not match!");
    for(int i = 0; i < Left.size(); ++i)
        if(Left[i].back() != Right[i].front())
            return false;
    return true;
}

bool match_up_down(vector<string> Up, vector<string> Down)
{
    return Up.back() == Down.front();
}

int int_sqrt(int n)
{
    for(i = 0; i * i < n; ++i);
    if(i * i == n)
        return i;
    else
        throw runtime_error("int " + to_string(n) + "is not a square");
}

void Day20(string input_file_path)
{
    // read input
    in.open(input_file_path);
    if(in.fail())
        cerr << "Not successfully opened!\n";
    vector<string> V;
    int current;
    regex r(R"(Tile (\d+):)");
    smatch m;
    if(getline(in, line) && !line.empty())
    {
        string::const_iterator search_start = line.begin(), search_end = line.end();
        if(regex_search(search_start, search_end, m, r))
            current = stoi(m.str(1));
    }
    while(getline(in, line))
    {
        if(line.empty())
        {
            M[current] = {V};
            V.clear();
            if(getline(in, line) && !line.empty())
            {
                string::const_iterator search_start = line.begin(),
                search_end = line.end();
                if(regex_search(search_start, search_end, m, r))
                    current = stoi(m.str(1));
            }
        }
        else
        {
            V.push_back(line);
        }
    }
    if(!V.empty())
        M[current] = {V};
    in.close();
    
    /*for(auto& P : M)
    {
        add_flipped_and_rotated(&(P.second));
        cout << P.first << endl;
        for(auto V : P.second)
        {
            for(auto Line : V)
                cout << Line << endl;
            cout << "----------\n";
        }
        cout << endl;
    }*/
    
    ofstream out;
    out.open(input_file_path.replace(input_file_path.size() - 9, 9, "output.txt"));
    for(auto& P : M)
    {
        add_flipped_and_rotated(&(P.second));
        
        /* This output is needed to remove Heisenbug
         (https://en.wikipedia.org/wiki/Heisenbug).
         I hope I will fix it in the future.*/
        out << P.first << ":" << P.second.size() << " ";
    }
    out.close();
    
    // I figured out using this output that full backtracking was not needed,
    // so my solution is an overkill.
    /*for(auto P : M)
    {
        for(auto Or : P.second)
        {
            cout << accumulate(M.begin(), M.end(), 0, [P, Or](long s, auto P2)
            {
                if(P2 == P)
                    return s;
                else
                    return s + count_if(P2.second.begin(), P2.second.end(), [Or](auto V)
                    {
                        return V[0] == Or[0];
                    });
            }) << " ";
        }
        cout << " ";
    }
    cout << endl;*/
    
    // backtracking starts!!!
    int dim = int_sqrt((int)M.size()),
        min_dim = (int)M.begin()->second[0].size();
    
    int i = 0, j = 0, orientation = 0;
    set<int> Used;
    vector<map<int, vector<vector<string> > >::const_iterator> Iters;
    vector<int> Orientations;
    map<int, vector<vector<string> > >::const_iterator it = M.begin();
    while(i < dim && i >= 0)
    {
        /*cout << "Current map:\n";
        for(int k = 0; k <= i; ++k)
        {
            if(k < i || j > 0)
            {
                for(int l = 0; l < min_dim; ++l)
                {
                    for(int m = 0; m < j; ++m)
                    cout << Iters[k * dim + m]->
                            second[Orientations[k * dim + m]][l] << " ";
                    cout << endl;
                }
            }
        }
        cout << "Trying:\n";
        for(auto Line : it->second[orientation])
            cout << Line << endl;*/
        
        if(Used.count(it -> first) == 0 &&
           (i == 0 ||
            match_up_down(Iters[(i - 1) * dim + j]->
                            second[Orientations[(i - 1) * dim + j]],
                          it->second[orientation])) &&
           (j == 0 ||
            match_left_right(Iters.back()->second[Orientations.back()],
                             it->second[orientation])))
        {
            //cout << "OK\n\n";
            Iters.push_back(it);
            Orientations.push_back(orientation);
            Used.insert(it->first);
            it = M.begin();
            orientation = 0;
            if(++j >= dim)
            {
                j = 0;
                ++i;
            }
        }
        else
        {
            //cout << "Not OK\n\n";
            while(true)
            {
                if(++orientation >= 8)
                {
                    orientation = 0;
                    if(++it == M.end())
                    {
                        it = Iters.back();
                        orientation = Orientations.back();
                        Iters.pop_back();
                        Orientations.pop_back();
                        Used.erase(it->first);
                        if(--j < 0)
                        {
                            j = dim - 1;
                            --i;
                        }
                    }
                    else
                        break;
                }
                else
                    break;
            }
        }
    }
    long long part1 = Iters[0]->first;
    part1 *= Iters[dim - 1]->first;
    part1 *= Iters[dim * (dim - 1)]->first;
    part1 *= Iters.back()->first;
    cout << "Part One: " << part1 << endl;
    
    vector<string> Final;
    for(i = 0; i < dim; ++i)
    {
        for(j = 1; j < min_dim - 1; ++j)
        {
            string S;
            for(k = 0; k < dim; ++k)
            S += Iters[i * dim + k]->second[Orientations[i * dim + k]][j].substr(1, min_dim - 2);
            Final.push_back(move(S));
        }
    }
    vector<vector<string> > FinalOrientations{Final};
    add_flipped_and_rotated(&FinalOrientations);
    vector<pair<int, int> > SeaMonsterPoints{{1, 0}, {2, 1}, {2, 4}, {1, 5}, {1, 6},
        {2, 7}, {2, 10}, {1, 11}, {1, 12}, {2, 13}, {2, 16}, {1, 17}, {1, 18}, {1, 19},
        {0, 18}};
    
    long min_part2 = dim * dim * min_dim * min_dim;
    for(auto Orientation : FinalOrientations)
    {
        set<pair<int, int> > S;
        for(i = 0; i < Orientation.size() - 2; ++i)
        for(j = 0; j < Orientation[i].size() - 19; ++j)
        {
            if(all_of(SeaMonsterPoints.begin(), SeaMonsterPoints.end(),
                      [i, j, Orientation](auto P)
            {
                return Orientation[i + P.first][j + P.second] == '#';
            }))
            {
                for(auto P : SeaMonsterPoints)
                    S.insert(make_pair(i + P.first, j + P.second));
            }
        }
        long roughness = accumulate(Orientation.begin(), Orientation.end(), 0,
                                    [](long s, string Line)
        {
            return s + count(Line.begin(), Line.end(), '#');
        }) - S.size();
        if(roughness < min_part2)
            min_part2 = roughness;
    }
    cout << "Part Two: " << min_part2 << endl;
}
