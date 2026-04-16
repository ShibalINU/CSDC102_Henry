//Formatting & Most expensive item not final

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Products {
    string name;
    int quantity;
    float price;
    float totalVal;
    
};

int main() {
    int n;
    
    cout << "How many products to enter? ";
    cin >> n;
    
    Products products[n];
    
    for (int i = 0; i < n; i++){
        cout << "Enter Product name: ";
        cin >> products[i].name;
        
        cout << "Enter quantity: ";
        cin >> products[i].quantity;
        
        cout << "Enter price: ";
        cin >> products[i].price;
        cin.ignore();
    }
    
    cout << "Name               Quantity        Price       Total Value(per item)"  << endl;
    cout << "-----              --------       ------      ---------------------" << endl;
    for (int i = 0; i < n; i++){
        products[i].totalVal = (float)products[i].quantity * products[i].price;
        cout << products[i].name << "               " << products[i].quantity << "              " << products[i].price << "             " << products[i].totalVal << endl;
    }
    

    
    return 0;
}
