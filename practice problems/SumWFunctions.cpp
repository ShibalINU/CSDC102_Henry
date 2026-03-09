#include <iostream>

int add(int arr[], int n);

int main()
{
	int n;
	std::cout << "Enter number of elements: ";
	std::cin >> n;

	int arr [n];
	std::cout << "Enter elements: ";
	for (int i = 0; i < n; i++) {
		std::cin >> arr[i];
	}

    int sum = add(arr, n);
    std::cout << "sum: " << sum;
	

	return 0;
}

int add(int arr[], int n){
    int sum = 0;
    for (int i = 0; i < n; i++){
        sum += arr[i];
    }
    return sum;
}


