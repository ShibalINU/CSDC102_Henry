#include <iostream>
#include <string>

using namespace std;

void bubbleSort(int* arr, int size){
    for(int i = 0; i < size - 1; i++){
        for(int j = 0; j < size; j++){
            if(arr[j] > arr[j + 1]){
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main()
{
    int size = 5;
    int arr[size];

    cout << "Enter 5 integers: " << endl;
    for(int i = 0; i < 5; i++){
        cin >> arr[i];
    }
    cout << "Before: ";
    for (int i = 0; i < size; i++){
        cout << " " << arr[i];
    }
    
    bubbleSort(arr, size);
      
    cout << "\nAfter: ";
    for (int i = 0; i < size; i++){
        cout << " " << arr[i];
    }
    return 0;
}
