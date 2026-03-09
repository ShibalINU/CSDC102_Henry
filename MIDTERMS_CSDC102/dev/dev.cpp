#include <iostream>
#include <string>
#include <vector>
using namespace std;

//--------------------------------------------------------------------Main functions

int login(string &adminPasscode) {
}

// Display helper (const reference - read-only)
void displayMenu(string bankNames[], double localFees[], double intlFees[], double dailyLimits[]) {
};

void clientMenu(vector<string> &cardNumbers,
                vector<string> &pins,
                vector<double> &balances
                /*, ... other vectors if needed */)
{
    cout << "Enter Card Number: ";
    cout << "Enter PIN: ';

    
    int choiceUser;
    cout << "Client Menu: " << endl;
    cout << "1. Check Balance" << endl;
    cout << "2. Withdraw Cash" << endl;
    cout << "3. Deposit Cash" << endl;
    cout << "4. Transfer Funds" << endl;
    cout << "5. View Transaction History" << endl;
    cout << "6. Exit" << endl;
    //-----
    cout << "\nEnter your choice: ";
    cin >> choiceUser;

    if (choiceUser == 1)
    {
        // Check balance
    }
    else if (choiceUser == 2)
    {
        // Withdraw cash
    }
    else if (choiceUser == 3)
    {
        // Deposit cash
    }
    else if (choiceUser == 4)
    {
        // Transfer funds
    }
    else if (choiceUser == 5)
    {
        // View transaction history
    }
    else
    {
        cout << "Exiting..." << endl;
    }
};

void adminMenu(vector<string> &cardNumbers,
               vector<double> &balances,
               string &adminPasscode
               /*, ... other vectors if needed */)
{
    int choiceAdmin;
    cout << "Admin Menu: " << endl;
    cout << "1. Cash Management" << endl;
    cout << "2. User Management" << endl;
    cout << "3. Admin Credentials" << endl;
    cout << "4. Exit" << endl;
    cin >> choiceAdmin;
    if (choiceAdmin == 1)
    {
        int ChoiceCashManagement;
        cout << "Cash Management: " << endl;
        cout << "1. View current cash" << endl;
        cout << "2. Replenish cash" << endl;
        cout << "3. Track total cash" << endl;
        cout << "4. Exit" << endl;
        cout << "\nEnter choice: ";
        cin >> ChoiceCashManagement;
        // Cash management
    }
    else if (choiceAdmin == 2)
    {
        int ChoiceUserManagement;
        cout << "User Management: " << endl;
        cout << "1. View all accounts and balances" << endl;
        cout << "2. Add new account" << endl;
        cout << "3. delete/ deactivate account" << endl;
        cout << "4. Reset account passwords" << endl;
        cout << "5. Exit" << endl;
        cout << "\nEnter choice: ";
        cin >> ChoiceUserManagement;
        // User management
    }
    else if (choiceAdmin == 3)
    {

        // Admin credentials
        int ChoiceAdminCredentials;
        cout << "Admin Credentials: " << endl;
        cout << "1. Change Admin passcode" << endl;
        cout << "2. View all Admin users" << endl;
        cout << "3. Exit" << endl;
        cout << "\nEnter choice: ";
        cin >> ChoiceAdminCredentials;
    }
};

//--------------------------------------------------------------------Utility Functions
string encodeString(string plain);
string decodeString(string encoded);
bool validateCardNumber(string card);
double calculateFeeRecursive(double amount, int iterations);
void logTransaction(const string &cardNum,
                    const string &type,
                    double amount);

int main()
{
    const int NUM_BANKS = 4;
    string bankNames[NUM_BANKS] = {"BDO", "BPI", "Metrobank", "Security Bank"};
    double localFees[NUM_BANKS] = {25, 20, 30, 15};
    double intlFees[NUM_BANKS] = {150, 125, 200, 100};
    double dailyLimits[NUM_BANKS] = {50000, 75000, 100000, 60000};

    const int NUM_DENOMINATIONS = 2;
    int denominations[NUM_DENOMINATIONS] = {500, 1000};
    int billCount[NUM_DENOMINATIONS] = {500, 500}; // Current count of each

    vector<string> cardNumbers;
    // Parallel vectors - keep in sync!

    vector<string> encodedPINs;
    // Encoded passwords

    vector<double> balances;
    // Account balances

    vector<string> userBanks;
    // Which bank

    vector<string> accountTypes;
    // "Local" or "International"

    // For each account's transaction history
    vector<string> transactionTypes;

    // "Withdrawal", "Deposit", "Transfer"
    vector<double> transactionAmounts;
    vector<double> transactionFees;
    vector<int> transactionQuantities;

    // for trial
    string adminPasscode = "admin123"; // Default

    adminMenu(cardNumbers, balances, adminPasscode);

    return 0;
}
