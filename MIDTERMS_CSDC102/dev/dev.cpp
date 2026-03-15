#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <ctime>
using namespace std;

//--------------------------------------------------------------------Main functions
// Color codes
const string RESET = "\033[0m";      // Reset to default
const string RED = "\033[31m";       // Red text
const string GREEN = "\033[32m";     // Green text
const string YELLOW = "\033[33m";    // Yellow text
const string BLUE = "\033[34m";      // Blue text
const string MAGENTA = "\033[35m";   // Magenta text
const string CYAN = "\033[36m";      // Cyan text
const string WHITE = "\033[37m";     // White text
const string BOLD = "\033[1m";       // Bold text
const string FAINT = "\033[2m";      // Faint text
const string ITALIC = "\033[3m";     // Italic text
const string UNDERLINE = "\033[4m";  // Underline text
const string SLOW_BLINK = "\033[5m"; // Slow blink text

const string RAPID_BLINK = "\033[6m";        // Rapid blink on
const string REVERSE_VIDEO = "\033[7m";      // Reverse video on
const string CONCEAL = "\033[8m";            // Conceal on
const string CROSSED_OUT = "\033[9m";        // Crossed-out on
const string BOLD_OFF = "\033[22m";          // Bold off
const string ITALIC_OFF = "\033[23m";        // Italic off
const string UNDERLINE_OFF = "\033[24m";     // Underline off
const string BLINK_OFF = "\033[25m";         // Blink off
const string REVERSE_VIDEO_OFF = "\033[27m"; // Reverse video off
const string CONCEAL_OFF = "\033[28m";       // Conceal off
const string CROSSED_OUT_OFF = "\033[29m";   // Crossed-out off

// Background color
const string BLACK_BG = "\033[40m";   // Set background color to black
const string RED_BG = "\033[41m";     // Set background color to red
const string GREEN_BG = "\033[42m";   // Set background color to green
const string YELLOW_BG = "\033[43m";  // Set background color to yellow
const string BLUE_BG = "\033[44m";    // Set background color to blue
const string MAGENTA_BG = "\033[45m"; // Set background color to magenta
const string CYAN_BG = "\033[46m";    // Set background color to cyan
const string WHITE_BG = "\033[47m";   // Set background color to white
const string DEFAULT_BG = "\033[49m"; // Reset background color to default

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
bool withdraw(vector<double> &balances, int accountIndex, double withdrawAmount);
bool withdraw(vector<double> &balances, int accountIndex, string presetAmount);
double calculateFeeRecursive(vector<double> &balances, string currentUserBank, string userAccountType, int accountIndex, int iterations);
void calculateBills(double withdrawAmount, int &bills1000, int &bills500, int &bills100);
void refillCash(int denom[], int billCount[]);
void viewAccounts(vector<string> &cardNumbers, vector<double> &balances);
void showAccountDetails(vector<string> &cardNumbers, vector<string> &userBanks, vector<string> &accountTypes, vector<double> &balances, int i);

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
            break;
        else
        {
            system("pause");
            return 0;
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
    cout << BOLD << CYAN << ITALIC << "======================================================" << endl;
    cout << "        K H G :  B A N K I N G  S Y S T E M           "
         << endl;
    cout << "======================================================" << ITALIC_OFF << endl;
    cout << "Supported Banks: BDO, BPI, Metrobank, Security Bank" << endl;
    cout << "======================================================" << RESET << endl
         << endl;
    cout << BOLD << YELLOW << "\n[1] Client   [2] Admin   [3] Shutdown" << RESET << endl;
    cout << BOLD << BLUE << "Enter your choice: " << RESET;
    cin >> roleChoice;

    if (roleChoice == 1)
    {
        return 1;
    }
    else if (roleChoice == 2)
    {

        for (int attempts = 0; attempts < 3; ++attempts)
        {

            string passcode;
            cout << BOLD << BLUE << "Enter admin passcode: " << RESET;
            cin >> passcode;

            if (passcode == adminPasscode)
            {
                cout << BOLD << GREEN << "\nAdmin access granted." << RESET;
                return 2; // admin role
            }

            cout << BOLD << RED << "Incorrect passcode (" << attempts + 1 << "/3).\n"
                 << RESET;
        }
    }
    else if (roleChoice == 3)
    {
        cout << BOLD << RED << "System shutting down..." << RESET << endl;
        return 0;
    }
    return 0;
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

    cout << BOLD << MAGENTA << "Date: " << (timeinfo->tm_mon + 1) << "/"
         << timeinfo->tm_mday << "/"
         << (timeinfo->tm_year + 1900);
    cout << BOLD << MAGENTA << " \nTime: " << timeinfo->tm_hour << ":"
         << timeinfo->tm_min << RESET << endl;
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
    cout << BOLD << BLUE << "Enter Card Number: " << RESET;
    cin >> userCard;
    int accountIndex;

    if (validateCardNumber(cardNumbers, userCard, accountIndex))
    {
        string userPIN;
        cout << BOLD << BLUE << "Enter PIN: " << RESET;
        cin >> userPIN;

        if (userPIN == encodedPINs[accountIndex])
        {
            displayDateTime();
            showAccountDetails(cardNumbers, userBanks, accountTypes, balances, accountIndex);
            cout << BOLD << ITALIC << FAINT << YELLOW << "\nTransaction fees may apply depending on your account type " << RESET << ITALIC_OFF << endl;
            int choiceUser;

            do
            {
                cout << BOLD << CYAN << "======= CLIENT MENU ========" << RESET << endl;
                cout << BOLD << ITALIC << "1. Check Balance" << endl;
                cout << "2. Withdraw Cash" << endl;
                cout << "3. Transfer Cash" << endl;
                cout << "4. View Transaction History" << endl;
                cout << "5. Change PIN" << endl;
                cout << "6. Exit" << ITALIC_OFF << endl;
                //-----
                cout << BOLD << BLUE << "\nEnter your choice: " << RESET;
                cin >> choiceUser;

                clearScreen();

                switch (choiceUser)
                {
                case 1:
                {
                    displayDateTime();
                    showAccountDetails(cardNumbers, userBanks, accountTypes, balances, accountIndex);
                    cout << BOLD << CYAN << "Current Balance: Php " << balances[accountIndex] << endl;
                    break;
                }
                case 2:
                {

                    displayDateTime();
                    showAccountDetails(cardNumbers, userBanks, accountTypes, balances, accountIndex);
                    // Withdraw cash
                    int withdrawChoice;
                    cout << BOLD << CYAN << "Select Withdrawal Option:\n"
                         << RESET;
                    cout << ITALIC << "1. Predefined Amount (500, 1000, 2000, 5000, 10000)\n";
                    cout << "2. Custom Amount\n";
                    cout << "3. Exit\n"
                         << RESET;
                    cout << BOLD << BLUE << "Enter choice: " << RESET;
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
                        {
                            presetAmount = "500";
                            cout << BOLD << YELLOW << "Preset amount selected: Php " << presetAmount << RESET << endl;
                            cout << BOLD << GREEN << "Withdrawal Successful! " << RESET << endl;
                        }

                        else if (presetChoice == 2)
                        {
                            presetAmount = "1000";
                            cout << BOLD << YELLOW << "Preset amount selected: Php " << presetAmount << RESET << endl;
                            cout << BOLD << GREEN << "Withdrawal Successful! " << RESET << endl;
                        }

                        else if (presetChoice == 3)
                        {
                            presetAmount = "2000";
                            cout << BOLD << YELLOW << "Preset amount selected: Php " << presetAmount << RESET << endl;
                            cout << BOLD << GREEN << "Withdrawal Successful! " << RESET << endl;
                        }
                        else if (presetChoice == 4)
                        {
                            presetAmount = "5000";
                            cout << BOLD << YELLOW << "Preset amount selected: Php " << presetAmount << RESET << endl;
                            cout << BOLD << GREEN << "Withdrawal Successful! " << RESET << endl;
                        }
                        else if (presetChoice == 5)
                        {
                            presetAmount = "10000";
                            cout << BOLD << YELLOW << "Preset amount selected: Php " << presetAmount << RESET << endl;
                            cout << BOLD << GREEN << "Withdrawal Successful! " << RESET << endl;
                        }
                        else
                        {
                            cout << BOLD << RED << "Invalid input.\n"
                                 << RESET;
                            return;
                        }
                        withdraw(balances, accountIndex, presetAmount);
                    }
                    else if (withdrawChoice == 2)
                    {
                        cout << BOLD << CYAN << "Enter amount to withdraw: " << RESET;
                        cin >> withdrawAmount;
                        withdraw(balances, accountIndex, withdrawAmount);
                        cout << BOLD << YELLOW << "Withdrawal amount: Php " << withdrawAmount << RESET << endl;
                        cout << BOLD << GREEN << "Withdrawal Successful! " << RESET << endl;
                    }
                    else
                    {
                        return;
                    }

                    double balanceAfterDeduction = calculateFeeRecursive(balances, userBanks[accountIndex], accountTypes[accountIndex], accountIndex, 0);
                    double deductedFee = balances[accountIndex] - balanceAfterDeduction;
                    balances[accountIndex] = balanceAfterDeduction;
                    cout << BOLD << YELLOW << "Transaction fee deducted: Php " << deductedFee << RESET << endl;
                    cout << BOLD << CYAN << "Updated Balance: Php " << balances[accountIndex] << RESET << endl;

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
                    displayDateTime();
                    showAccountDetails(cardNumbers, userBanks, accountTypes, balances, accountIndex);
                    break;
                case 4:
                {

                    displayDateTime();
                    showAccountDetails(cardNumbers, userBanks, accountTypes, balances, accountIndex);
                    ifstream file("transactions.csv");
                    string line;
                    cout << BOLD << CYAN << "\n====== Last Transactions ======\n"
                         << RESET;
                    while (getline(file, line))
                    {
                        if (line.find(cardNumbers[accountIndex]) != string::npos)
                            cout << line << endl;
                    }
                    file.close();
                    break;
                }
                case 5:
                {
                    displayDateTime();

                    showAccountDetails(cardNumbers, userBanks, accountTypes, balances, accountIndex);
                    string newpin;
                    cout << BOLD << CYAN << "Enter new PIN: " << RESET;
                    cin >> newpin;
                    encodedPINs[accountIndex] = newpin;
                    cout << BOLD << GREEN << "PIN changed successfully!\n"
                         << RESET;
                    break;
                }
                case 6:
                    cout << BOLD << CYAN << "Exiting safely...\n"
                         << RESET;
                    break;
                }
            } while (choiceUser != 6);
        }
        else
        {
            cout << BOLD << RED << "Incorrect Passcode. Please Try Again.\n"
                 << RESET;
            return;
        }
    }
    else
    {
        cout << BOLD << RED << "Card number not found. Please try again.\n"
             << RESET;
        return;
    }
}

void showAccountDetails(vector<string> &cardNumbers, vector<string> &userBanks, vector<string> &accountTypes, vector<double> &balances, int i)
{
    cout << BOLD << UNDERLINE << YELLOW << "Bank: " << userBanks[i] << endl;
    cout << "Account Type: " << accountTypes[i] << endl;
    cout << "Balance: " << balances[i] << RESET << UNDERLINE_OFF << endl;
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
}

void logTransaction(const string &cardNum, const string &type,
                    double amount, double fee)
{
    ofstream file("transactions.csv", ios::app);
    if (file.is_open())
    {
        // Get current date and time
        time_t now = time(0);
        tm *timeinfo = localtime(&now);
        // Write transaction to file
        file << (timeinfo->tm_mon + 1) << "/" << timeinfo->tm_mday
             << "/" << (timeinfo->tm_year + 1900) << ","
             << timeinfo->tm_hour << ":" << timeinfo->tm_min << ","
             << cardNum << "," << type << ","
             << amount << "," << fee << endl;
        file.close();
    }
    else
    {
        cerr << "Error: Could not open transactions.csv" << endl;
    }
}

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

double calculateFeeRecursive(vector<double> &balances, string currentUserBank, string userAccountType, int accountIndex, int iterations)
{
    // Base case: end of bank list
    if (iterations == NUM_BANKS)
    {
        return balances[accountIndex];
    }
    // If bank matches
    if (currentUserBank == bankNames[iterations])
    {
        if (userAccountType == "Local")
        {
            return balances[accountIndex] - localFees[iterations];
        }
        else
        {
            return balances[accountIndex] - intlFees[iterations];
        }
    }
    // Recursive call: to the next bank
    return calculateFeeRecursive(balances, currentUserBank, userAccountType, accountIndex, iterations + 1);
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

        cout << BOLD << CYAN << "\n=========Admin Menu:======== " << RESET << endl;
        cout << ITALIC << "1. View Current Cash" << endl;
        cout << "2. Refill Cash" << endl;
        cout << "3. Create Account" << endl;
        cout << "4. View accounts" << endl;
        cout << "5. Delete Account" << endl;
        cout << "6. Reset account passwords" << endl;
        cout << "7. Change admin Passcode" << endl;
        cout << "8. List of all admin users" << endl;
        cout << "9. Exit" << ITALIC_OFF << endl;

        cout << BOLD << BLUE << "\nEnter your choice: " << RESET;
        cin >> choiceAdmin;

        clearScreen();

        switch (choiceAdmin)
        {
        case 1:
        {
            cout << BOLD << CYAN << UNDERLINE << "Current cash in machine:\n"
                 << RESET << UNDERLINE_OFF;
            int totalCash = 0;
            for (int i = 0; i < NUM_DENOMINATIONS; i++)
            {
                totalCash += denominations[i] * billCount[i];
                cout << BOLD << YELLOW << "PHP " << denominations[i] << ": " << billCount[i] << " bills" << RESET << endl;
            }
            cout << BOLD << YELLOW << UNDERLINE << "Total cash available: PHP " << totalCash << RESET << UNDERLINE_OFF << endl;
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

            cout << BOLD << BLUE << "Card: " << RESET;
            cin >> card;

            cout << BOLD << BLUE << "PIN: " << RESET;
            cin >> pin;

            cout << BOLD << BLUE << "Initial Balance: " << RESET;
            cin >> bal;

            cout << BOLD << BLUE << "Bank (BDO, BPI, Metrobank, Security Bank): " << RESET;
            cin >> bank;

            cout << BOLD << BLUE << "Type (Local/International): " << RESET;
            cin >> type;

            cardNumbers.push_back(card);
            encodedPINs.push_back(encodeString(pin));
            balances.push_back(bal);
            userBanks.push_back(bank);
            accountTypes.push_back(type);

            cout << BOLD << GREEN << "Account created!\n"
                 << RESET;
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
            cout << BOLD << BLUE << "Enter index to delete: " << RESET;
            cin >> index;

            cardNumbers.erase(cardNumbers.begin() + index);
            encodedPINs.erase(encodedPINs.begin() + index);
            balances.erase(balances.begin() + index);
            userBanks.erase(userBanks.begin() + index);
            accountTypes.erase(accountTypes.begin() + index);

            cout << BOLD << GREEN << "Index: " << index << " Account Succesfully deleted! \n"
                 << RESET;
        }
        break;
        case 6: // veryyyyy buggyyy, it's still not updating in main, idk what's happening yet
        {
            viewAccounts(cardNumbers, balances);
            int index;
            cout << BOLD << BLUE << "Enter index to reset PIN: " << RESET;
            cin >> index;

            string newPIN;
            cout << BOLD << BLUE << "Enter new PIN: " << RESET;
            cin >> newPIN;

            encodedPINs[index] = newPIN;
            cout << BOLD << GREEN << "PIN reset successful!\n"
                 << RESET;
        }
        break;
        case 7:
        {
            string currentPasscode;
            cout << BOLD << BLUE << "Enter current passcode: " << RESET;
            cin >> currentPasscode;
            if (currentPasscode == adminPasscode)
            {
                string newPasscode;
                cout << BOLD << BLUE << "Enter new passcode: " << RESET;
                cin >> newPasscode;
                adminPasscode = newPasscode;
                cout << BOLD << GREEN << "Admin passcode updated successfully!\n"
                     << RESET;
            }
            else
            {
                cout << BOLD << RED << "Incorrect current passcode.\n"
                     << RESET;
            }
        }
        break;
        case 8:
            // List of all admin users
            break;
        case 9:
            // Exit
            cout << BOLD << YELLOW << "Exiting Admin Menu..." << RESET << endl;

            break;
        default:
            cout << BOLD << RED << "Invalid input.\n"
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
    if (localTime->tm_hour == 20 && localTime->tm_min <= 60)
    {
        // Refill bills
        int refillAmount;
        for (int i = 0; i < NUM_DENOMINATIONS; i++)
        {
            cout << BOLD << BLUE << "Enter number of PHP " << denom[i] << " bills to add: " << RESET;
            cin >> refillAmount;
            billCount[i] += refillAmount;
        }
        cout << BOLD << GREEN << "Refill successful." << RESET << endl;
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
        cout << BOLD << BLUE << i << " " << cardNumbers[i] << " Balance: " << balances[i] << RESET << endl;
    }
}
