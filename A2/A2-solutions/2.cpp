#include <iostream>

using namespace std;

#define OPEN_BRACKET '['
#define CLOSE_BRACKET ']'

bool isLetter(char c)
{
    return c >= 'a' && c <= 'z';
}

bool isDigit(char c)
{
    return c >= '0' && c <= '9';
}

string decodeString(const string& s) 
{
    string ans = "";
    int repeat = 0;
    for (int i = 0 ; i < s.size() ; i++)
    {
        if (isLetter(s[i]))
            ans += s[i];
        if (isDigit(s[i]))
            repeat = repeat * 10 + (s[i] - '0');
        if (s[i] == OPEN_BRACKET)
        {
            int balance = 1;
            string t = "";
            i++;
            while (i < s.size() && balance > 0)
            {
                t += s[i];
                if (s[i] == OPEN_BRACKET)
                    balance++;
                if (s[i] == CLOSE_BRACKET)
                    balance--;  
                i++;              
            }
            i--;
            string decoded = decodeString(t);
            for (int j = 0 ; j < repeat ; j++)
                ans += decoded;
            repeat = 0;
        }
    }
    return ans;
}

int main()
{
    string s;
    cin >> s;
    cout << decodeString(s) << endl;
}