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
void viewAccounts(vector<string> &cardNumbers, vector<double> &balances);

//--------------------------------------------------------------------Main

int main()
{
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
    cout << BOLD << GREEN << "\n[1] Client   [2] Admin   [3] Shutdown" << RESET << endl;
    cout << "Enter your choice: ";
    cin >> roleChoice;

    if (roleChoice == 1)
    {
        return 1;
    }
    else if (roleChoice == 2)
    {
        string passcode;
        cout << "Enter admin passcode: ";
        cin >> passcode;

        if (passcode != adminPasscode)
        {
            cout << "Incorrect passcode. Access denied." << endl;
            return 0; // Invalid role
        }
        else
        {
            cout << "Admin access granted." << endl;
            return 2; // Admin role
        }
    }
    else if (roleChoice == 3)
    {
        return 3;
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
    int choiceUser;

    do
    {
        cout << "\nClient Menu: " << endl;
        cout << "1. Check Balance" << endl;
        cout << "2. Withdraw Cash" << endl;
        cout << "3. Deposit Cash" << endl;
        cout << "4. Transfer Funds" << endl;
        cout << "5. View Transaction History" << endl;
        cout << "6. Exit" << endl;

        cout << "\nEnter your choice: ";
        cin >> choiceUser;

        switch (choiceUser)
        {
        case 1:
            displayDateTime();
            break;
        case 2:
            // Withdraw cash
            break;
        case 3:
            // Deposit cash
            break;
        case 4:
            // Transfer funds
            break;
        case 5:
            // View transaction history
            break;
        case 6:
            cout << "Exiting Client Menu..." << endl;
            break;
        default:
            cout << "Invalid input.\n";
        }

    } while (choiceUser != 6);
}

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
        cout << "6. Change admin Passcode" << endl;
        cout << "7. List of all admin users" << endl;
        cout << "8. Exit" << endl;

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
                cout << "PHP " << denominations[i] << ": " << billCount[i] << " bills8" << endl;
            }
            cout << "Total cash available: PHP " << totalCash << endl;
            break;
        }
        break;
        case 2:
            // Refill cash
            break;
        case 3:
        {
            string card;
            string pin;
            double bal;
            string bank;
            string type;

            cout << "Card: ";
            cin >> card;

            cout << "PIN: ";
            cin >> pin;

            cout << "Initial Balance: ";
            cin >> bal;

            cout << "Bank(BDO, BPI, Metrobank, Security Bank): ";
            cin >> bank;

            cout << "Type(Local/International): ";
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
            for (int i = 0; i < cardNumbers.size(); i++)
            {
                cout << i << " " << cardNumbers[i] << " Balance: " << balances[i] << endl;
            }
        }
        break;
        case 5:
        {
            int index;
            cout << "Enter index to delete: ";
            cin >> index;

            cardNumbers.erase(cardNumbers.begin() + index);
            encodedPINs.erase(encodedPINs.begin() + index);
            balances.erase(balances.begin() + index);
            userBanks.erase(userBanks.begin() + index);
            accountTypes.erase(accountTypes.begin() + index);
        }
            cout << "Account deleted! \n";
            break;
        case 6:
            // Change admin Passcode
            break;
        case 7:
            // List of all admin users
            break;
        case 8:
            // Exit
            cout << "Exiting Admin Menu..." << endl;
            break;
        default:
            cout << "Invalid input.\n";
        }

    } while (choiceAdmin != 8);
}