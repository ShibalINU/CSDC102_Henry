#include <iostream>

int main()
{

    int MyArray[] = {1, 2, 3, 4, 15, 6, 7, 30, 9, 10}; // the array
    // print out the array
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

    // Finding the largest and smallest values first
    int largest = MyArray[0], smallest = MyArray[0];
    for (int i = 0; i < 10; i++)
    {
        if (MyArray[i] > largest)
        {
            largest = MyArray[i];
        }
        if (MyArray[i] < smallest)
        {
            smallest = MyArray[i];
        }
    }
    // basically assuming that the second largest is the smallest and vice versa
    int secondLargest = smallest;
    int secondSmallest = largest;

    for (int i = 0; i < 10; i++)
    {
        // when index [i] is less than largest but greater than second largest then update second largest as index [i]
        // see comments i initially thought that second largest was supposed to be the smallest value but that was wrong
        if (MyArray[i] < largest && MyArray[i] > secondLargest)
        {
            secondLargest = MyArray[i];
        }
        if (MyArray[i] > smallest && MyArray[i] < secondSmallest)
        {
            secondSmallest = MyArray[i];
        }
    }

    std::cout << "Second largest: " << secondLargest << std::endl;
    std::cout << "Second smallest: " << secondSmallest << std::endl;

    // MY ATTEMPT WITHOUT HELP FROM LESSONS AND REFERENCES NOT WORKING

    /*
        for (int i = 0; i < 10; i++)
        {
            if (MyArray[i] < SecondLargest)
            {
                SecondLargest = MyArray[i];
            }
            else if (SecondLargest < Largest && MyArray[i] != SecondLargest)
            {
                SecondLargest = MyArray[i];
            }
        }

        std::cout << "Second largest: " << SecondLargest << std::endl; */

    // Right rotation by k = 2

    // Reversed
    std::cout << "Reversed: ";
    for (int i = 10 - 1; i >= 0; i--)
    {
        std::cout << MyArray[i] << " ";
    }

    std::cout << std::endl;

    return 0;
}