#include <iostream>

int main()
{
    int n,
    largest,
    smallest,
    sum = 0;
    std::cout << "Enter size of array: ";
    std::cin >> n;
    
    int arr[n];
    
    std::cout << "Input " << n << " array elements: " << std::endl;
    for(int i = 0; i < n; i++){
        std::cin >> i;
    }
    
    largest = arr[0];
    smallest = arr[0];
    
    
    return 0;
}
