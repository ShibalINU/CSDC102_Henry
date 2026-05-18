#include <iostream>
#include <string>
using namespace std;


string rem(string s){
    if (s.length() == 0) return "";
    cout <<  s[0] << endl;
    return rem(s.substr(1)) ;
}
int main()
{
    string s = "henry";
    rem(s);
    return 0;
}
