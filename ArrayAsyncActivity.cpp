#include <iostream>

int main()
{

    int MyArray[] = {1, 2, 3, 4, 15, 6, 7, 30, 9, 10}; // the array

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
    int SecondLargest = MyArray[0], Largest = MyArray[0];
    for (int i = 0; i < 10; i++)
    {
        if (MyArray[i] > Largest)
        {
            Largest = MyArray[i];
        }
    }

    std::cout << Largest << std::endl;

    for (int i = 0; i < 10; i++)
    {
        SecondLargest = Largest;
        if(MyArray[i] < SecondLargest){
            SecondLargest = MyArray[i];
        }else if (SecondLargest < Largest && MyArray[i] != SecondLargest){
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
