#include <iostream>

using namespace std;
using ll = long long int;


void reverse_(string& s, int i, int j) {
    if (i > j)
        return;
    swap(s[i], s[j]);
    reverse_(s, i + 1, j - 1);
}
    
void invert(string& s, int i) {
    if (i == s.length())
        return;
    s[i] = '0' + ('1' - s[i]);
    invert(s, i + 1);
}
    
string makeNthString(int n) {
    if (n == 1)
        return "0";
    string s = makeNthString(n - 1);
    string sInv = s;
    invert(sInv, 0);
    reverse_(sInv, 0, sInv.length() - 1);
    return s + "1" + sInv;
}
    
char findKthBit(int n, int k) {
    string s = makeNthString(n);
    return s[k - 1];
}

int main() {
    int n, k;
    cin >> n >> k;
    cout << findKthBit(n, k) << endl;
}