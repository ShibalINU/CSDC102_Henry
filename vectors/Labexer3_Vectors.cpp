#include <iostream>
#include <vector>
using namespace std;

void displayMenu(const vector<string>& menuItems,
                 const vector<double>& menuPrices) {

    cout << "\n=============================\n";
    cout << "            MENU\n";
    cout << "=============================\n\n";

    for(int i = 0; i < menuItems.size(); i++) {
        cout << i << " - "
             << menuItems[i]
             << " - P"
             << menuPrices[i] << endl;
    }
}

int login(string adminPasscode) {

    int role;
    string passcode;

    cout << "\n[1] User   [2] Admin   [3] Shutdown\n";
    cout << "Enter choice: ";
    cin >> role;

    if(role == 2) {
        cout << "Enter Admin Passcode: ";
        cin >> passcode;

        if(passcode != adminPasscode)
            return 0; // access denied
    }

    return role;
}


void userMenu(vector<string>& menuItems,
              vector<double>& menuPrices) {

    vector<string> receiptItems;
    vector<double> receiptPrices;
    vector<int> receiptQuantities;

    int choice;

    do {
        cout << "\n====== USER MENU ======\n";
        cout << "1. View Menu\n";
        cout << "2. Add Item\n";
        cout << "3. View Receipt\n";
        cout << "4. Clear Receipt\n";
        cout << "5. Remove Item from Receipt\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;


        if(choice == 1) {
            displayMenu(menuItems, menuPrices);
        }

        else if(choice == 2) {

            displayMenu(menuItems, menuPrices);

            int index, quantity;
            cout << "Enter item index: ";
            cin >> index;

            if(index < 0 || index >= menuItems.size()) {
                cout << "Invalid index.\n";
                continue;
            }

            cout << "Enter quantity: ";
            cin >> quantity;

            bool found = false;

            for(int i = 0; i < receiptItems.size(); i++) {
                if(receiptItems[i] == menuItems[index]) {
                    receiptQuantities[i] += quantity;
                    found = true;
                    break;
                }
            }

            if(!found) {
                receiptItems.push_back(menuItems[index]);
                receiptPrices.push_back(menuPrices[index]);
                receiptQuantities.push_back(quantity);
            }

            cout << "Item added successfully!\n";
        }

        else if(choice == 3) {

            if(receiptItems.empty()) {
                cout << "Receipt is empty.\n";
                continue;
            }

            double total = 0;

            cout << "\n====== RECEIPT ======\n";

            for(int i = 0; i < receiptItems.size(); i++) {
                double subtotal = receiptPrices[i] * receiptQuantities[i];
                total += subtotal;

                cout << i << " - "
                     << receiptItems[i]
                     << " x" << receiptQuantities[i]
                     << " = P" << subtotal << endl;
            }

            cout << "Total: P" << total << endl;

            char checkout;
            cout << "Checkout and pay? (Y/N): ";
            cin >> checkout;

            if(checkout == 'Y' || checkout == 'y') {

                double payment;

                do {
                    cout << "Enter payment: ";
                    cin >> payment;

                    if(payment < total)
                        cout << "Insufficient amount.\n";

                } while(payment < total);

                cout << "Change: P" << payment - total << endl;

                receiptItems.clear();
                receiptPrices.clear();
                receiptQuantities.clear();

                cout << "Payment successful. Receipt cleared.\n";
            }
        }

        else if(choice == 4) {

            receiptItems.clear();
            receiptPrices.clear();
            receiptQuantities.clear();

            cout << "Receipt cleared.\n";
        }

        else if(choice == 5) {

            if(receiptItems.empty()) {
                cout << "Receipt is empty.\n";
                continue;
            }

            for(int i = 0; i < receiptItems.size(); i++) {
                cout << i << " - "
                     << receiptItems[i]
                     << " x" << receiptQuantities[i] << endl;
            }

            int index;
            cout << "Enter index to remove: ";
            cin >> index;

            if(index < 0 || index >= receiptItems.size()) {
                cout << "Invalid index.\n";
                continue;
            }

            if(receiptQuantities[index] > 1) {

                int option;
                cout << "1. Reduce by 1\n";
                cout << "2. Remove entirely\n";
                cin >> option;

                if(option == 1) {
                    receiptQuantities[index]--;
                }
                else {
                    receiptItems.erase(receiptItems.begin() + index);
                    receiptPrices.erase(receiptPrices.begin() + index);
                    receiptQuantities.erase(receiptQuantities.begin() + index);
                }
            }
            else {
                receiptItems.erase(receiptItems.begin() + index);
                receiptPrices.erase(receiptPrices.begin() + index);
                receiptQuantities.erase(receiptQuantities.begin() + index);
            }

            cout << "Item updated.\n";
        }

    } while(choice != 6);
}

void adminMenu(vector<string>& menuItems,
               vector<double>& menuPrices,
               string& adminPasscode) {

    int choice;

    do {
        cout << "\n====== ADMIN MENU ======\n";
        cout << "1. View Menu\n";
        cout << "2. Add New Menu Item\n";
        cout << "3. Edit Existing Menu Item\n";
        cout << "4. Change Admin Passcode\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if(choice == 1) {
            displayMenu(menuItems, menuPrices);
        }

        else if(choice == 2) {

            string newItem;
            double newPrice;

            cin.ignore();

            cout << "Enter item name: ";
            getline(cin, newItem);

            cout << "Enter price: ";
            cin >> newPrice;

            menuItems.push_back(newItem);
            menuPrices.push_back(newPrice);

            cout << "Item added successfully!\n";
        }


        else if(choice == 3) {

            displayMenu(menuItems, menuPrices);

            int index;
            cout << "Enter index to edit: ";
            cin >> index;

            if(index < 0 || index >= menuItems.size()) {
                cout << "Invalid index.\n";
                continue;
            }

            int editChoice;
            cout << "1. Edit Name\n";
            cout << "2. Edit Price\n";
            cout << "3. Both\n";
            cin >> editChoice;

            cin.ignore();

            if(editChoice == 1 || editChoice == 3) {
                string newName;
                cout << "Enter new name: ";
                getline(cin, newName);
                menuItems[index] = newName;
            }

            if(editChoice == 2 || editChoice == 3) {
                double newPrice;
                cout << "Enter new price: ";
                cin >> newPrice;
                menuPrices[index] = newPrice;
            }

            cout << "Item updated successfully!\n";
        }

 
        else if(choice == 4) {

            string current, newPass;

            cout << "Enter current passcode: ";
            cin >> current;

            if(current == adminPasscode) {
                cout << "Enter new passcode: ";
                cin >> newPass;
                adminPasscode = newPass;
                cout << "Passcode changed successfully!\n";
            }
            else {
                cout << "Incorrect passcode.\n";
            }
        }

    } while(choice != 5);
}


int main() {

    vector<string> menuItems = {"Burger","Fries","Coke","Chicken"};
    vector<double> menuPrices = {99, 49, 39, 129};

    string adminPasscode = "6767";

    while(true) {

        int role = login(adminPasscode);

        if(role == 1)
            userMenu(menuItems, menuPrices);

        else if(role == 2)
            adminMenu(menuItems, menuPrices, adminPasscode);

        else if(role == 3)
            break;

        else {
            cout << "Access Denied.\n";
            break;
        }
    }

    cout << "System Shutdown.\n";
    return 0;
}
