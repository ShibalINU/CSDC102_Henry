#include <iostream>
using namespace std;


int cdown(int n){
    if (n == 0) return 0;
    cout << n << endl;
    return cdown(n - 1);
}
int main()
{
    cout << cdown(5);
    return 0;
}
