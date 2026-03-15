#include <iostream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

//--------------------------------------------------------------------Main functions
// Color codes
const string RESET = "\033[0m";    // Reset to default
const string RED = "\033[31m";     // Red text
const string GREEN = "\033[32m";   // Green text
const string YELLOW = "\033[33m";  // Yellow text
const string BLUE = "\033[34m";    // Blue text
const string MAGENTA = "\033[35m"; // Magenta text
const string CYAN = "\033[36m";    // Cyan text
const string WHITE = "\033[37m";   // White text
const string BOLD = "\033[1m";     // Bold text

const int NUM_BANKS = 4;
const int NUM_DENOMINATIONS = 3;

string bankNames[NUM_BANKS] = {"BDO", "BPI", "Metrobank", "Security Bank"};
double localFees[NUM_BANKS] = {25, 20, 30, 15};
double intlFees[NUM_BANKS] = {150, 125, 200, 100};
double dailyLimits[NUM_BANKS] = {50000, 75000, 100000, 60000};

int denominations[NUM_DENOMINATIONS] = {100, 500, 1000};
int billCount[NUM_DENOMINATIONS] = {500, 500, 500};

//--------------------------------------------------------------------Function declarations

int login(string &adminPasscode, vector<string> &cardNumbers, vector<string> &encodedPINs);

void clientMenu(vector<string> &cardNumbers,
                vector<string> &encodedPINs,
                vector<double> &balances,
                vector<string> &userBanks,
                vector<string> &accountTypes);

void adminMenu(vector<string> &cardNumbers,
               vector<string> &encodedPINs,
               vector<double> &balances,
               vector<string> &userBanks,
               vector<string> &accountTypes,
               string &adminPasscode);

string encodeString(string plain);
string decodeString(string encoded);
void displayDateTime();
void clearScreen();
bool validateCardNumber(vector<string> &cardNumbers, string userCard, int &accountIndex);
<<<<<<< Updated upstream
bool withdraw(vector<double> &balances, int accountIndex, double withdrawAmount);
bool withdraw(vector<double> &balances, int accountIndex, string presetAmount);
double calculateFeeRecursive(double withdrawAmount, int iterations);
void calculateBills(double withdrawAmount, int &bills1000, int &bills500, int &bills100);
=======
bool withdraw(vector<double>& balances, int accountIndex, double withdrawAmount);
bool withdraw(vector<double>& balances, int accountIndex, string presetAmount);
double calculateFeeRecursive(double withdrawAmount, string currentUserBank, string userAccountType, int iterations);
void calculateBills(double withdrawAmount, int& bills1000, int& bills500, int& bills100);
>>>>>>> Stashed changes
void refillCash(int denom[], int billCount[]);
void viewAccounts(vector<string> &cardNumbers, vector<double> &balances);

//--------------------------------------------------------------------Main

int main()
{
    // vectors
    vector<string> cardNumbers = {"12345678910", "10987654321", "11111111111"};
    vector<string> encodedPINs = {"6767", "9876", "6543"};
    vector<double> balances = {9000, 5600, 6700};
    vector<string> userBanks = {"BPI", "BDO", "Metrobank"};
    vector<string> accountTypes = {"Local", "International", "International"};

    string adminPasscode = "6767";
    while (true)
    {
        int role = login(adminPasscode, cardNumbers, encodedPINs);

        if (role == 1)
            clientMenu(cardNumbers, encodedPINs, balances, userBanks, accountTypes);
        else if (role == 2)
            adminMenu(cardNumbers, encodedPINs, balances, userBanks, accountTypes, adminPasscode);
        else if (role == 3)
            break; // shutdown
        else
        {
            cout << "Access Denied.\n";
            break;
        }
    }

    system("pause");
    return 0;
}

//--------------------------------------------------------------------Login function

int login(string &adminPasscode, vector<string> &cardNumbers, vector<string> &encodedPINs)
{
    int roleChoice;
    cout << BOLD << CYAN << "====================================================" << endl;
    cout << "        K H G :  B A N K I N G  S Y S T E M           " << endl;
    cout << "====================================================" << RESET << endl;
    cout << BOLD << BLUE << "Supported Banks: BDO, BPI, Metrobank, Security Bank" << endl;
    cout << "====================================================" << RESET << endl
         << endl;
    cout << BOLD << YELLOW << "\n[1] Client   [2] Admin   [3] Shutdown" << RESET << endl;
    cout << "Enter your choice: ";
    cin >> roleChoice;

    if (roleChoice == 1)
    {
        return 1;
    }
    else if (roleChoice == 2) // admin attempts
    {
        for (int attempts = 0; attempts < 3; ++attempts)
        {
            string passcode;
            cout << "Enter admin passcode: ";
            cin >> passcode;

            if (passcode == adminPasscode)
            {
                cout << BOLD << GREEN << "Admin access granted." << RESET << endl;
                return 2; // admin role
            }

            cout << BOLD << RED << "Incorrect passcode (" << attempts + 1 << "/3).\n"
                 << RESET;
        }
    }
    cout << BOLD << RED << "Access denied. System Locked." << RESET << endl;
    return 3;
}

//--------------------------------------------------------------------Security functions

string encodeString(string plain)
{
    string encoded = plain;
    for (char &c : encoded)
        c += 3; // Simple Caesar cipher
    return encoded;
}

string decodeString(string encoded)
{
    string decoded = encoded;
    for (char &c : decoded)
        c -= 3; // Reverse Caesar cipher
    return decoded;
}

//--------------------------------------------------------------------Utilities

void displayDateTime()
{
    time_t now = time(0);
    tm *timeinfo = localtime(&now);

    cout << "Date: " << (timeinfo->tm_mon + 1) << "/"
         << timeinfo->tm_mday << "/"
         << (timeinfo->tm_year + 1900);
    cout << " Time: " << timeinfo->tm_hour << ":"
         << timeinfo->tm_min << endl;
}

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

//--------------------------------------------------------------------Client Menu

void clientMenu(vector<string> &cardNumbers,
                vector<string> &encodedPINs,
                vector<double> &balances,
                vector<string> &userBanks,
                vector<string> &accountTypes)
{
    string userCard;
    cout << BOLD << YELLOW << "Enter Card Number: " << RESET << endl;
    cin >> userCard;
    int accountIndex;

    if (validateCardNumber(cardNumbers, userCard, accountIndex))
    {
        string userPIN;
        cout << BOLD << YELLOW << "Enter PIN: " << RESET << endl;
        cin >> userPIN;

<<<<<<< Updated upstream
        if (encodedPINs[accountIndex] == userPIN)
        {
=======
        if(encodedPINs[accountIndex] == userPIN)
        {    
            string currentUserBank = userBanks[accountIndex];
            string userAccountType = accountTypes[accountIndex];
            cout << "WELCOME!\n";
            cout << "\nYour card has been identified as:\n";
            cout << "Bank: " << currentUserBank << endl;
            cout << "Account Type: " << userAccountType << endl;
            cout << "\nTransaction fees may apply depending on your account type.\n";
            cout << "Please proceed.\n";             

>>>>>>> Stashed changes
            int choiceUser;
            do
            {
                cout << "\n=====CLIENT MENU===== " << endl;
                cout << "1. Check Balance" << endl;
                cout << "2. Withdraw Cash" << endl;
                cout << "3. Transfer Cash" << endl;
                cout << "4. View Transaction History" << endl;
                cout << "5. Change PIN" << endl;
                cout << "6. Exit" << endl;

                cout << "\nEnter your choice: ";
                cin >> choiceUser;

                switch (choiceUser)
                {
                case 1:
                {
                    displayDateTime();
                    cout << "Current Balance: Php " << balances[accountIndex] << endl;
                }
                break;

                case 2:
                {
                    // Withdraw cash
                    int withdrawChoice;
                    cout << "Select Withdrawal Option:\n";
                    cout << "1. Predefined Amount (500, 1000, 2000, 5000, 10000)\n";
                    cout << "2. Custom Amount\n";
                    cout << "Enter choice: ";
                    cin >> withdrawChoice;

                    clearScreen();
                    double withdrawAmount;
                    int bills1000 = 0;
                    int bills500 = 0;
                    int bills100 = 0;

                    if (withdrawChoice == 1)
                    {
                        int presetChoice;
                        cout << "Select Amount:\n";
                        cout << "1. Php 500\n";
                        cout << "2. Php 1000\n";
                        cout << "3. Php 2000\n";
                        cout << "4. Php 5000\n";
                        cout << "5. Php 10000\n";
                        cout << "Enter Choice: ";
                        cin >> presetChoice;

                        string presetAmount;
                        if (presetChoice == 1)
                            presetAmount = "500";
                        else if (presetChoice == 2)
                            presetAmount = "1000";
                        else if (presetChoice == 3)
                            presetAmount = "2000";
                        else if (presetChoice == 4)
                            presetAmount = "5000";
                        else if (presetChoice == 5)
                            presetAmount = "10000";
                        else
                        {
                            cout << "Invalid input.\n";
                        }
                        withdraw(balances, accountIndex, presetAmount);
                    }

                    else if (withdrawChoice == 2)
                    {
                        cout << "Enter amount to withdraw: ";
                        cin >> withdrawAmount;
                        withdraw(balances, accountIndex, withdrawAmount);
                    }
<<<<<<< Updated upstream

                    // Deduct appropriate fee
                    if (accountTypes[accountIndex] == "Local")
                    {
                        for (int i = 0; i < NUM_BANKS; i++)
                        {
                            if (userBanks[accountIndex] == bankNames[i])
                            {
                                balances[accountIndex] -= localFees[i];
                            }
                        }
                    }
                    else
                    {
                        for (int i = 0; i < NUM_BANKS; i++)
                        {
                            if (userBanks[accountIndex] == bankNames[i])
                            {
                                balances[accountIndex] -= intlFees[i];
                            }
                        }
                    }

=======
                    
                    double deductedFee = calculateFeeRecursive(withdrawAmount, currentUserBank, userAccountType, 0); // Deduct appropriate fee for withdrawal
                    balances[accountIndex] = deductedFee; // update user balance
                    
>>>>>>> Stashed changes
                    // Calculate change in optimal bills
                    calculateBills(withdrawAmount, bills1000, bills500, bills100);
                    // Update Bill Count after withdrawal
                    billCount[0] -= bills100;
                    billCount[1] -= bills500;
                    billCount[2] -= bills1000;
                }
                break;

                case 3:
                    // Transfer cash
                    break;
                case 4:
                    // View Transaction History
                    break;
                case 5:
                    // Change PIN
                    break;
                case 6:
                    cout << "Exiting Client Menu..." << endl;
                    break;
                default:
                    cout << "Invalid input.\n";
                }

            } while (choiceUser != 6);
        }
        else
        {
            cout << "Incorrect passcode. Please try again.\n";
            cout << endl;
            return;
        }
    }
    else
    {
        cout << "Card not found. Please try again.\n";
        cout << endl;
        return;
    }
}

bool validateCardNumber(vector<string> &cardNumbers,
                        string userCard,
                        int &accountIndex)
{
    for (int i = 0; i < cardNumbers.size(); i++)
    {
        if (cardNumbers[i] == userCard)
        {
            accountIndex = i;
            return true;
        }
    }
    return false;
}

// Version 1: Custom amount
bool withdraw(vector<double> &balances, int accountIndex, double withdrawAmount)
{
    // Process withdrawal
    if (balances[accountIndex] >= withdrawAmount) // Check if balance is sufficient for the withdrawal amount
    {
        balances[accountIndex] -= withdrawAmount;
        return true;
    }
    return false;
}

// Version 2: Preset amount
bool withdraw(vector<double> &balances, int accountIndex, string presetAmount)
{
    double withdrawAmount = stod(presetAmount);              // Convert string to double
    return withdraw(balances, accountIndex, withdrawAmount); // Call Version 1
}

double calculateFeeRecursive(double withdrawAmount, string currentUserBank, string userAccountType, int iterations)
{
<<<<<<< Updated upstream
    // MAN IDK

    // Implementation for calculating fee recursively
    return 0.0;
=======
    // Base case: end of bank list
    if(iterations == NUM_BANKS)
    {
        return withdrawAmount;
    }
    // If bank matches
    if(currentUserBank == bankNames[iterations])
    {
        if(userAccountType == "Local")
        {
            return withdrawAmount - localFees[iterations];
        }
        else
        {
            return withdrawAmount - intlFees[iterations];
        }
    }
    // Recursive call: to the next bank 
    return calculateFeeRecursive(withdrawAmount, currentUserBank, userAccountType, iterations + 1);
>>>>>>> Stashed changes
};

// Recursive function to calculate number of bills for a given amount
void calculateBills(double withdrawAmount, int &bills1000, int &bills500, int &bills100)
{
    if (withdrawAmount >= 1000)
    {
        bills1000++;
        calculateBills(withdrawAmount - 1000, bills1000, bills500, bills100);
    }
    else if (withdrawAmount >= 500)
    {
        bills500++;
        calculateBills(withdrawAmount - 500, bills1000, bills500, bills100);
    }
    else if (withdrawAmount >= 100)
    {
        bills100++;
        calculateBills(withdrawAmount - 100, bills1000, bills500, bills100);
    }
    // Base case: amount < 100, recursion stops automatically
}

void logTransaction(const string &cardNum,
                    const string &type,
                    double amount) {

};

//--------------------------------------------------------------------Admin Menu

void adminMenu(vector<string> &cardNumbers,
               vector<string> &encodedPINs,
               vector<double> &balances,
               vector<string> &userBanks,
               vector<string> &accountTypes,
               string &adminPasscode)
{
    int choiceAdmin;

    do
    {
        cout << "\nAdmin Menu: " << endl;
        cout << "1. View Current Cash" << endl;
        cout << "2. Refill Cash" << endl;
        cout << "3. Create Account" << endl;
        cout << "4. View accounts" << endl;
        cout << "5. Delete Account" << endl;
        cout << "6. Reset account passwords" << endl;
        cout << "7. Change admin Passcode" << endl;
        cout << "8. List of all admin users" << endl;
        cout << "9. Exit" << endl;

        cout << "\nEnter your choice: ";
        cin >> choiceAdmin;

        switch (choiceAdmin)
        {
        case 1:
        {
            cout << "Current cash in machine:\n";
            int totalCash = 0;
            for (int i = 0; i < NUM_DENOMINATIONS; i++)
            {
                totalCash += denominations[i] * billCount[i];
                cout << BOLD << CYAN << "PHP " << denominations[i] << ": " << billCount[i] << " bills" << RESET << endl;
            }
            cout << BOLD << CYAN << "Total cash available: PHP " << totalCash << RESET << endl;
            break;
        }
        break;
        case 2:
        {
            refillCash(denominations, billCount);
            break;
        }

        break;
        case 3:
        {
            string card, pin, bank, type;
            double bal;

            cout << BOLD << CYAN << "Card: " << RESET;
            cin >> card;

            cout << BOLD << CYAN << "PIN: " << RESET;
            cin >> pin;

            cout << BOLD << CYAN << "Initial Balance: " << RESET;
            cin >> bal;

            cout << BOLD << CYAN << "Bank (BDO, BPI, Metrobank, Security Bank): " << RESET;
            cin >> bank;

            cout << BOLD << CYAN << "Type (Local/International): " << RESET;
            cin >> type;

            cardNumbers.push_back(card);
            encodedPINs.push_back(encodeString(pin));
            balances.push_back(bal);
            userBanks.push_back(bank);
            accountTypes.push_back(type);

            cout << "Account created!\n";
        }
        break;
        case 4:
        {
            viewAccounts(cardNumbers, balances);
        }
        break;
        case 5:
        {
            viewAccounts(cardNumbers, balances);
            int index;
            cout << BOLD << YELLOW << "Enter index to delete: " << RESET;
            cin >> index;

            cardNumbers.erase(cardNumbers.begin() + index);
            encodedPINs.erase(encodedPINs.begin() + index);
            balances.erase(balances.begin() + index);
            userBanks.erase(userBanks.begin() + index);
            accountTypes.erase(accountTypes.begin() + index);

            cout << BOLD << RED << "Index: " << index << " Account deleted! \n"
                 << RESET;
        }
        break;
        case 6: // veryyyyy buggyyy, it's still not updating in main, idk what's happening yet
        {
            viewAccounts(cardNumbers, balances);
            int index;
            cout << BOLD << YELLOW << "Enter index to reset PIN: " << RESET;
            cin >> index;

            string newPIN;
            cout << BOLD << CYAN << "Enter new PIN: " << RESET;
            cin >> newPIN;

            encodedPINs[index] = newPIN;
            cout << BOLD << CYAN << "PIN reset successful!\n"
                 << RESET;
        }
        break;
        case 7:
        {
            string currentPasscode;
            cout << BOLD << CYAN << "Enter current passcode: " << RESET;
            cin >> currentPasscode;
            if (currentPasscode == adminPasscode)
            {
                string newPasscode;
                cout << BOLD << CYAN << "Enter new passcode: " << RESET;
                cin >> newPasscode;
                adminPasscode = newPasscode;
                cout << BOLD << GREEN << "Admin passcode updated successfully!\n"
                     << RESET;
            }
        }
        break;
        case 8:
            // List of all admin users
            break;
        case 9:
            // Exit
            cout << BOLD << CYAN << "Exiting Admin Menu..." << RESET << endl;

            break;
        default:
            cout << BOLD << CYAN << "Invalid input.\n"
                 << RESET;
        }

    } while (choiceAdmin != 9);
}
// Henry === I can just add refill cash func inside the case statement. This is just tp make it cleaner idk
void refillCash(int denom[], int billCount[])
{
    time_t now = time(0);
    tm *localTime = localtime(&now);

    // Check if current time is between 8:00 and 8:15
    if (localTime->tm_hour == 8 && localTime->tm_min <= 15)
    {
        // Refill bills
        int refillAmount;
        for (int i = 0; i < NUM_DENOMINATIONS; i++)
        {
            cout << BOLD << CYAN << "Enter number of PHP " << denom[i] << " bills to add: " << RESET;
            cin >> refillAmount;
            billCount[i] += refillAmount;
        }
        cout << BOLD << CYAN << "Refill successful." << RESET << endl;
    }
    else
    {
        cout << BOLD << RED << "Refill allowed only from 8:00 AM to 8:15 AM." << RESET << endl;
    }
}

void viewAccounts(vector<string> &cardNumbers, vector<double> &balances)
{
    for (int i = 0; i < cardNumbers.size(); i++)
    {
        cout << BOLD << CYAN << i << " " << cardNumbers[i] << " Balance: " << balances[i] << RESET << endl;
    }
}
