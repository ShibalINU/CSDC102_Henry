#include <iostream>
#include <vector>

using namespace std;
void clearScreen(){
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main()
{
    
    vector<string>menuItems = {"Burger", "Fries", "Coke", "Chicken", "Pizza"};
    vector<double>menuPrices = {99, 63, 39, 129, 600};
    
    vector<string>receiptItems;
    vector<double>receiptPrices;
    
    int choice;
    
    do{
    clearScreen();
        
        cout << "\n==SELF ORDERING MACHINE==" << endl;
        cout << "1. View Menu" << endl;
        cout << "2. Add item" << endl;
        cout << "3. Remove Item from Receipt" << endl;
        cout << "4. View Receipt" << endl;
        cout << "5. Exit" << endl;
        cin >> choice;
    clearScreen();   
        if(choice == 1){
            
            for(int i = 0; i < menuItems.size(); i++){
                cout << i + 1 << ". " << menuItems[i] << " - Php" << menuPrices[i] << endl;
            }
            
        }else if(choice == 2){
            
            int index;
            for(int i = 0; i < menuItems.size(); i++){
                cout << i + 1 << ". " << menuItems[i] << " - Php" << menuPrices[i] << endl;
            }
            
            cout << "Enter item number to add: ";
            cin >> index;
            
            if(index >= 0 & index < menuItems.size()){
                receiptItems.push_back(menuItems[index]);
                receiptPrices.push_back(menuPrices[index]);
                cout << "Item addded successfully." << endl;
            }else{
                cout << "invalid choice!";
            }
            
            cout << endl;
            cout << "press any number to continue: ";
            cin >> choice;
            
        }else if(choice == 3){
            int index;
            if(receiptItems.empty()){
                cout << "Receipt is empty. " << endl;
            }else{
                  for(int i = 0; i < menuItems.size(); i++){
                cout << i + 1 << ". " << menuItems[i] << " - Php" << menuPrices[i] << endl;
            }
            
            cout << "Enter item number to remove: ";
            cin >> index;
            
            if(index >= 0 & index < menuItems.size()){
                receiptItems.erase(receiptItems.begin() + index);
                receiptPrices.erase(receiptPrices.begin() + index);
                cout << "Item removed successfully." << endl;
            }else{
                cout << "invalid choice!";
            }
        }
        
        cout << "Press any number to continue: ";
        cin >> choice;
        }else if(choice == 4){
            if(receiptItems.empty()){
                cout << "No items ordered yet. \n";
            }else{
                double total = 0;
                
                for(int i = 0; i < receiptItems.size(); i++){
                    cout << i + 1 << ". " << receiptItems[i] << " - Php" << receiptPrices[i] << endl;
                    total += receiptPrices[i];
                }
                cout << "Total Prices:" << total;
            }
        }
    }while( choice != 5);
    return 0;
}
