#include "Util.hpp"

using namespace std;

vector<string> Util::split_string(string line, char delim)
{
    stringstream ss(line);
    string token;
    vector<string> tokens;
    while (getline(ss, token, delim))
    {
        if (token.length() > 0)
        {
            tokens.push_back(token);
        }
    }
    return tokens;
}