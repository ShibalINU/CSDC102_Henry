#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

struct Product {
    string name;
    int quantity;
    float price;
    float totalVal;
};

int main() {
    int n;

    cout << "How many products to enter (maxi is 5)? ";
    cin >> n;

    if (n > 5) n = 5;

    Product products[5];

    cin.ignore();

    for (int i = 0; i < n; i++) {
        cout << "\nEnter Product name: ";
        getline(cin, products[i].name);

        cout << "Enter quantity: ";
        cin >> products[i].quantity;

        cout << "Enter price: ";
        cin >> products[i].price;

        cin.ignore(); 

        products[i].totalVal = products[i].quantity * products[i].price;
    }

    cout << "\nName            Quantity      Price      Total Value\n";
    cout << "----            --------      -----      ------------\n";

    int maxIndex = 0;

    for (int i = 0; i < n; i++) {
        cout << left << setw(15) << products[i].name
             << setw(14) << products[i].quantity
             << setw(11) << products[i].price
             << products[i].totalVal << endl;

        if (products[i].price > products[maxIndex].price) {
            maxIndex = i;
        }
    }

    cout << "\nMost Expensive Product:\n";
    cout << "Name: " << products[maxIndex].name << endl;
    cout << "Price: " << products[maxIndex].price << endl;

    return 0;
}
