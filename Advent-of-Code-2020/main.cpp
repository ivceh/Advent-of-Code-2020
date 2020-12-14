#include "my_AoC_utils.h"
int i, j, k, n, cnt, cnt2;
ifstream in;
string line, str_temp;

void Day01(string), Day02(string), Day03(string), Day04(string), Day05(string),
    Day06(string), Day07(string), Day08(string), Day09(string), Day10(string),
    Day11(string), Day12(string), Day13(string), Day14(string);

vector<function<void (string)> > day_func{Day01, Day02, Day03, Day04, Day05,
    Day06, Day07, Day08, Day09, Day10, Day11, Day12, Day13, Day14};

void measure_time(bool output)
{
    using namespace chrono;
    static const bool time_measure = true;
    if(time_measure)
    {
        static steady_clock::time_point time = steady_clock::now();
        steady_clock::time_point time2 = steady_clock::now();
        if(output)
            cout << "Time: " << duration_cast<microseconds>(time2 - time).count() << " µs\n";
        time = time2;
    }
}

string day_name(int n)
{
    return "Day" + to_string(n / 10) + to_string(n % 10);
}

string input_file_name(int n, const string& input_name)
{
    string main_path = __FILE__, main_name = "main.cpp";
    main_path.replace(main_path.size() - main_name.size(),
                      main_name.size(),
                      day_name(n) + "/" + input_name);
    return main_path;
};

void exec_day(int n, const string& input_name)
{
    day_func[n - 1](input_file_name(n, input_name));
    measure_time();
}

void exec_all(const string& input_name)
{
    for(int i = 0; i < day_func.size(); ++i)
    {
        cout << day_name(i + 1) << endl;
        exec_day(i + 1, input_name);
        cout << endl;
    }
}

int main(int argc, const char * argv[])
{
    measure_time(false);
    exec_all("input.txt");
    return 0;
}
