#include "../my_AoC_utils.h"
#define fcode first
#define fvalue second
#define field pair<string, string>

vector<vector<field>> passports;

bool int_in_range(int n, int low, int high)
{
    return n >= low && n <= high;
}

bool are_digits(const string& S)
{
    return all_of(S.begin(), S.end(), [](char c){return isdigit(c);});
}

vector<string> fvalues{"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};
bool check_value(const string& key, const string& value)
{
    if(key == "byr")
        return value.size() == 4 && are_digits(value) &&
            int_in_range(stoi(value), 1920, 2002);
    else if(key == "iyr")
        return value.size() == 4 && are_digits(value) &&
            int_in_range(stoi(value), 2010, 2020);
    else if(key == "eyr")
        return value.size() == 4 && are_digits(value) &&
            int_in_range(stoi(value), 2020, 2030);
    else if(key == "hgt")
    {
        if (value.size() == 5)
            return value.substr(3, 2) == "cm" && int_in_range(stoi(value.substr(0,3)), 150, 193);
        else if (value.size() == 4)
            return value.substr(2, 2) == "in" && int_in_range(stoi(value.substr(0,2)), 59, 76);
        else
            return false;
    }
    else if(key == "hcl")
        return value.size() == 7 && value[0] == '#' &&
            all_of(next(value.begin()), value.end(),
                [](char c){return isdigit(c) || (c >= 'a' && c <= 'f');});
    else if(key == "ecl")
        return value == "amb" || value == "blu" || value == "brn" ||
            value == "gry" || value == "grn" || value == "hzl" ||
            value == "oth";
    else if(key == "pid")
        return value.size() == 9 && are_digits(value);
    else
        return false;
}

void Day04(string input_file_path)
{
    // reading input
    vector<field> passport;
    string str_field;
    in.open(input_file_path);
    if(in.fail())
        cerr << "Not successfully opened!\n";
    while(getline(in, line))
    {
        if(line.empty())
        {
            passports.push_back(move(passport));
            passport.clear();
        }
        else
        {
            stringstream linestream(line);
            while(linestream >> str_field)
                passport.push_back(field(str_field.substr(0, 3), str_field.substr(4, str_field.size() - 4)));
        }
    }
    if(!passport.empty())
        passports.push_back(move(passport));
    in.close();
    
    // solving Part One
    long part1 = count_if(passports.begin(), passports.end(),
        [](vector<field> passport)
        {
            return all_of(fvalues.begin(), fvalues.end(),
                [&passport](string key)
                {
                    return any_of(passport.begin(), passport.end(),
                        [&key](field f)
                        {
                            return key == f.fcode;
                        });
                });
        });
    cout << "Part One: " << part1 << endl;
    
    // solving Part Two
    long part2 = count_if(passports.begin(), passports.end(),
        [](vector<field> passport)
        {
            return all_of(fvalues.begin(), fvalues.end(),
                [&passport](string key)
                {
                    return any_of(passport.begin(), passport.end(),
                        [&key](field f)
                        {
                            return key == f.fcode &&
                                check_value(f.fcode, f.fvalue);
                        });
                });
        });
    cout << "Part Two: " << part2 << endl;
}
