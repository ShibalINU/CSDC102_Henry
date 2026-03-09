#include <iostream>
#include <string>
#include <vector>
using namespace std;

//--------------------------------------------------------------------Main functions

int login(string &adminPasscode);

// Display helper (const reference - read-only)
void displayMenu(const vector<string> &bankNames,
                 const vector<double> &localFees)
{
    cout << "Menu:" << endl;
    for (size_t i = 0; i < bankNames.size(); i++)
    {
        cout << i << ". " << bankNames[i] << " - ₱" << localFees[i] << endl;
    }
};

void clientMenu(vector<string> &cardNumbers,
                vector<string> &pins,
                vector<double> &balances
                /*, ... other vectors if needed */) {

};

void adminMenu(vector<string> &cardNumbers,
               vector<double> &balances,
               string &adminPasscode
               /*, ... other vectors if needed */);

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

    return 0;
}