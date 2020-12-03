#include "my_AoC_utils.h"
int i, j, k, n, cnt, cnt2;
ifstream in;
string line;

void Day01(string), Day02(string), Day03(string), Day04(string), Day05(string);

vector<function<void (string)> > day_func{Day01, Day02, Day03, Day04};

string day_name(int n)
{
    return "Day" + to_string(n / 10) + to_string(n % 10);
}

string input_file_name(int n)
{
    string main_path = __FILE__, main_name = "main.cpp";
    main_path.replace(main_path.size() - main_name.size(),
                      main_name.size(),
                      day_name(n) + "/input.txt");
    return main_path;
};

void exec_day(int n)
{
    day_func[n - 1](input_file_name(n));
}

void exec_all()
{
    for(int i = 0; i < day_func.size(); ++i)
    {
        cout << day_name(i + 1) << endl;
        exec_day(i + 1);
        cout << endl;
    }
}

int main(int argc, const char * argv[])
{
    exec_day(3);
    return 0;
}
