#include <iostream>

int main()
{

    int MyArray[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // the array

    std::cout << "Array: [ ";
    for (int i = 0; i < 10; i++)
    {
        std::cout << MyArray[i] << " ";
    }
    std::cout << "]";

    // space
    std::cout << std::endl;
    std::cout << std::endl;

    // Sum
    float sum = 0;
    for (int i = 0; i < 10; i++)
    {
        sum = sum + MyArray[i];
    }
    std::cout << "Sum: " << sum << std::endl;

    // Average
    float avg = sum / 10;
    std::cout << "Average: " << avg << std::endl;

    // SecondLargest
    int SecondLargest, Largest;
    for (int i = 0; i < 10; i++)
    {
        Largest = MyArray[0];
        if (Largest > MyArray[i + 1])
        {
            Largest = MyArray[i];
        }
    }

    std::cout << Largest << std::endl;

    for (int i = 0; i < 10; i++)
    {
        SecondLargest = MyArray[0];
        if (SecondLargest < MyArray[i + 1])
        {
            SecondLargest = MyArray[i];
        }
    }

    std::cout << "Second largest: " << SecondLargest << std::endl;

    // Reversed
    for (int i = 10 - 1; i >= 0; i--)
    {
        std::cout << MyArray[i] << " ";
    }

    return 0;
}