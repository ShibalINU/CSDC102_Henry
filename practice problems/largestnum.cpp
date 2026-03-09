#include <iostream>
using namespace std;

int main() {
    int numbers[5] = {12, 45, 7, 23, 89};
    int max = numbers[0];

    for (int i = 1; i < 5; i++) {
        if (numbers[i] > max) {
            max = numbers[i];
        }
    }

    cout << "Largest number: " << max;

    return 0;
}
