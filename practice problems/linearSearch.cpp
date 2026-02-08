#include <iostream>

using namespace std;
int main()
{
    int arr [] = {4, 2 , 3, 8 , 5, 34 , 64, 108};
    for(int i = 0; i < sizeof(arr) / sizeof (arr[0]); i++){
        if(arr[i] == 64){
            cout << "found at index: " << "[" << i << "]" << endl;
        }
    }

    return 0;
}
