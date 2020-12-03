#include "../my_AoC_utils.h"

struct row
{
    int low, high;
    char letter;
    string passwd;
};

vector<row> rows;

void Day02(string input_file_path)
{
    // reading input
    regex r = regex(R"((\d+)-(\d+) ([a-z]): ([a-z]+))");
    smatch m;
    in.open(input_file_path);
    if(in.fail())
        cerr << "Not successfully opened!\n";
    while(getline(in, line))
        if(regex_search(line, m, r))
        {
            row r;
            r.low = stoi(m.str(1));
            r.high = stoi(m.str(2));
            r.letter = m.str(3)[0];
            r.passwd = m.str(4);
            rows.push_back(r);
        }
    in.close();
    
    // solving Part One
    cnt = 0;
    for(auto r : rows)
    {
        cnt2 = 0;
        for(auto c : r.passwd)
            if(c == r.letter)
                ++cnt2;
        if(cnt2 >= r.low && cnt2 <= r.high)
            ++cnt;
    }
    cout << "Part One: " << cnt << endl;
    
    // solving Part Two
    cnt = 0;
    for(auto r : rows)
        if(r.passwd[r.low - 1] == r.letter ^ r.passwd[r.high - 1] == r.letter)
            ++cnt;
    cout << "Part Two: " << cnt << endl;
}
