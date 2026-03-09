#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int>v1 = {32, 43, 23, 54, 56, 43, 54};
    vector<int>v2 = {43, 54, 32};
    
    vector<string>names = {"Henry", "Max", "Lewis"};
    
    //egg will show 10 times
    vector<string>v4(10, "egg");
    
    vector<int>v;
    v1.insert(v1.begin() + 3, 75);
    v.front();
    
    for(int i = 0; i < v4.size(); i++){
        cout << v4[i] << " ";
    }
    
    cout << endl;
    
    for(int i = 0; i < v1.size(); i++){
        cout << v1[i] << "    ";
    }
    
    cout << endl;
    
    for(int i = 0; i < names.size(); i++){
        cout << names[i] << " ";
    }
    return 0;
}
