#include "../my_AoC_utils.h"

namespace // to avoid duplicate variable definition error
{
    // put global variables here
    vector<pair<char, double> > V;
}

double Manhattan_norm(const complex<double>& z)
{
    return abs(real(z)) + abs(imag(z));
}

void Day12(string input_file_path)
{
    // read input
    in.open(input_file_path);
    if(in.fail())
        cerr << "Not successfully opened!\n";
    while(in >> str_temp)
    {
        V.push_back(pair<char, int>(str_temp[0], stod(str_temp.substr(1))));
    }
    in.close();
    
    // solve Part One
    complex<double> position = 0, direction = 1;
    for(pair<char, double> P : V)
    {
        switch (P.first)
        {
            case 'N':
                position += 1i * P.second;
                break;
            case 'S':
                position += -1i * P.second;
                break;
            case 'E':
                position += P.second;
                break;
            case 'W':
                position -= P.second;
                break;
            case 'L':
                for(i = 0; i < P.second / 90; ++i)
                    direction *= 1i;
                break;
            case 'R':
                for(i = 0; i < P.second / 90; ++i)
                    direction *= -1i;
                break;
            case 'F':
                position += direction * P.second;
                break;
            default:
                throw runtime_error("Unknown action '" + string{P.first} + "'!");
                break;
        }
    }
    cout << "Part One: " << Manhattan_norm(position) << endl;
    
    // solve Part Two
    position = 0;
    complex<double> waypoint = 10. + 1i;
    for(pair<char, double> P : V)
    {
        switch (P.first)
        {
            case 'N':
                waypoint += 1i * P.second;
                break;
            case 'S':
                waypoint += -1i * P.second;
                break;
            case 'E':
                waypoint += P.second;
                break;
            case 'W':
                waypoint -= P.second;
                break;
            case 'L':
                for(i = 0; i < P.second / 90; ++i)
                    waypoint *= 1i;
                break;
            case 'R':
                for(i = 0; i < P.second / 90; ++i)
                    waypoint *= -1i;
                break;
            case 'F':
                position += waypoint * P.second;
                break;
            default:
                throw runtime_error("Unknown action '" + string{P.first} + "'!");
                break;
        }
    }
    cout << "Part Two: " << Manhattan_norm(position) << endl;
}
