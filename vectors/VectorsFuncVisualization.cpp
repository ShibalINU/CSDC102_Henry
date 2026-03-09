#include <iostream>
#include <vector>
using namespace std;

int main()
{
    cout << "Before pushback: ";
    vector<int>v1 = {43, 33, 53, 76, 89, 67, 13};
    vector<int>v2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for(int i = 0; i < v2.size(); i++){
        cout << v2[i] << " ";
    }
    
    cout << endl;
    cout << "After pushbach: ";
    v1.push_back(109);
    v1.push_back(145);
    v1.pop_back(); //deletes last element
    
    for(int i = 0; i < v1.size(); i++){
        cout << v1[i] << " ";
    }
    
    cout << endl;
    
    cout << "Erase function: ";
    v1.erase(v1.begin()+3);
    for(int i = 0; i < v1.size(); i++){
        cout << v1[i] << " ";
    }
    
    cout << endl;
    cout << "Swap function: ";
    v1.swap(v2);
    for(int i = 0; i < v1.size(); i++){
        cout << v1[i] << " ";
    }
    
    cout << endl;
    cout << "Resize function: ";
    v1.resize(20); // Basically adds more values, but the default values are zero so it outputs zero
    for(int i = 0; i < v1.size(); i++){
        cout << v1[i] << " ";
    }
    
    cout << endl;
    cout << "Clear function: ";
    v1.clear();
    for(int i = 0; i < v1.size(); i++){
        cout << v1[i] << " ";
    }
    
    cout << endl;
    cout << "Empty function: ";
    v1.clear(); //1 == true 0 == false
    cout << v1.empty() << endl;
    
    
    return 0;
}
