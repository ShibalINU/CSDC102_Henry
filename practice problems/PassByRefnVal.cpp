#include <iostream>
using namespace std;

void doubleVal(int &x){
    x = x * 2;
    cout << "inside function: " << x << endl;
}
int main(){
    
    int x = 5;
    cout << "Before function call: " << x << endl;
    
    doubleVal(x);
    
    cout << "after function call: " << x << endl;

    return 0;
}
