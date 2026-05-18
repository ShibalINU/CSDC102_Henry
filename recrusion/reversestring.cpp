#include <iostream>
#include <string>
using namespace std;


string rem(string s){
    if(s.length() <= 1) return s;
    return s.back() + rem(s.substr(0, s.length() - 1));
}
int main()
{
    string s = "henry";
    cout << rem(s);
    return 0;
}
