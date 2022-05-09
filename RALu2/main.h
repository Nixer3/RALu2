#include<vector>
#include<string>
#include<iostream> 
using namespace std;

const string WHITESPACE = " \n\r\t\f\v";

int ipow(int g1, int left) {
    if (left == 1) return g1;
    return ipow(g1, left - 1) * g1;
}

int calculate(int g1, int g2, char op) {
    switch (op) {
    case '+': return g1 + g2;
    case '*': return g1 * g2;
    case '-': return g1 - g2;
    case '/': return g1 / g2;
    case '^': return ipow(g1, g2);
    }
}
int calculate(int g1, char op) {
    switch (op) {
    case 'i': return -g1;
    }
    throw new invalid_argument(string("no supported single operand operation '" + op) + "'");
}

vector<string> split(const string& s, char sep) {
    vector<string> ret;
    typedef string::size_type string_size;
    string_size i = 0;
    while (i != s.size()) {
        while (i != s.size() && s[i] == sep)
            ++i;
        string_size j = i;
        while (j != s.size() && s[j] != sep)
            j++;
        if (i != j) {
            ret.push_back(s.substr(i, j - i));
            i = j;
        }
    }
    return ret;
}
string ltrim(const string& s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == string::npos) ? "" : s.substr(start);
}

string rtrim(const string& s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == string::npos) ? "" : s.substr(0, end + 1);
}

string trim(const string& s) {
    return rtrim(ltrim(s));
}

int subParanth(string str, int pos) { // find ending paranthesis index (recuscive)
    if (str.size() == pos)
        return -1; //bad paranthing
    while (1) {
        pos++;
        if (str[pos] == '(') {
            pos = subParanth(str, pos + 1) + 1;
        }
        if (str[pos] == ')') {
            return pos;
        }
    }
}