#include <iostream>
#include <string>

using namespace std;

class bankAccount{
        private:
            string accountHolder;
            double balance;
        public:
            bankAccount(string holder, double depo){
                accountHolder = holder;
                balance = depo;
            }
                
            void deposit(double amount){
                    balance += amount;
            }
            
            void Withdraw(double amount){
                if (amount > balance){
                    cout << "Insufficient balance: " << endl;
                }else{
                    cout << "Succesfully withdrawed: " << balance << endl;
                    balance -= amount;
                    
                }
            }
            
            void displayBalance(){
                cout << "Account holder name: " << accountHolder <<  endl;
                cout << "Balance avaialble: " << balance << endl;
            }
    };
    

int main()
{
    int choice;
    double amount;
    
    bankAccount bankAcc ("Henry", 0);
    
    do{
        
        cout << " \n ===== Choose Option =====" << endl;
        cout << " \n[1] Deposit,   [2] Withdraw,   [3] Check Blance,   [4]Exit" << endl;
        cin >> choice;
        
        if (choice == 1){
            cout << "enter amount deposit amount: ";
            cin >> amount;
            bankAcc.deposit(amount);
            cout << "\nSuccesfully Deposited: " << amount << endl;
        }else if (choice == 2){
            cout << "enter amount to withdraw: ";
            cin >> amount;
            bankAcc.Withdraw(amount);
        }else if (choice == 3){
            bankAcc.displayBalance();
        }
        
    }while (choice != 4);
    return 0;
}
