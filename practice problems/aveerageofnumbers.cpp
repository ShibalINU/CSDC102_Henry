#include <iostream>

int main()
{

    int arr[5] = {85, 90, 78, 92, 88};
    int sum = 0;
    for (int i = 0; i < 5; i++){
        sum += arr[i];
    }
    float avg = ()sum / 5;
    std::cout << avg;

   return 0;
}
