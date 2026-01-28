#include <iostream>

int main()
{
    int arr[] = {34, 67, 23, 89, 2, 45, 78, 12, 90, 11};
    int n = sizeof(arr) / sizeof(arr[0]); // this is just the size of the array so that it's dynamic hehehehe

    int largest = arr[0],
        smallest = arr[0],
        sum = 0;

    for (int i = 0; i < n; i++)
    {
        if (arr[i] > largest)
        {
            largest = arr[i];
        }
        if (arr[i] < smallest)
        {
            smallest = arr[i];
        }
        sum = sum + arr[i];
    }

    double avg = sum / (double)n; // I Added (double) to ensure the decimals will show without changng the data type of the variable i declared earlier
    std::cout << std::endl;
    std::cout << "Largest: " << largest << std::endl;
    std::cout << "Smallest: " << smallest << std::endl;
    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Average: " << avg << std::endl;
    std::cout << std::endl;

    for (int i = 0; i < n; i++)
    {
        if (arr[i] > avg)
        {
            std::cout << arr[i] << " - Above average." << std::endl;
        }
        else
        {
            std::cout << arr[i] << " - Below or Equal average." << std::endl;
        }
    }

    // optional activity Reverse array
    for (int i = 0; i < n / 2; i++)
    {
        int temp = arr[i];
        arr[i] = arr[n - i - 1];
        arr[n - i - 1] = temp;
    }

    // not final version just a simple one for reversing an array (output only)
    std::cout << "Reversed Array: ";
    for (int i = 0; i < n; i++)
    {
        std::cout << arr[i] << " ";
    }

    return 0;
}
