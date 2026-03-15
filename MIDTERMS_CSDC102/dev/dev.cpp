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
bool validateCard(string card);
void displayBalance(vector<string> &cardNumbers, vector<double> &balances, int index);
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
    cout << "Enter your choice: ";
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

    cout << BOLD << CYAN << "Date: " << (timeinfo->tm_mon + 1) << "/"
         << timeinfo->tm_mday << "/"
         << (timeinfo->tm_year + 1900);
    cout << BOLD << CYAN << " \nTime: " << timeinfo->tm_hour << ":"
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
    string cardNum_user;
    cout << "Enter Card Number: ";
    cin >> cardNum_user;

    for (int i = 0; i < cardNumbers.size(); i++)
    {

        if (cardNum_user == cardNumbers[i])
        {
            string userPin;
            cout << "Enter PIN: ";
            cin >> userPin;

            if (userPin == encodedPINs[i])
            {
                clearScreen();

                displayDateTime();
                cout << BOLD << YELLOW << "Bank: " << userBanks[i] << endl;
                cout << "Account Type: " << accountTypes[i] << endl;
                cout << "Balance: " << balances[i] << RESET << endl;

                int accountIndex = i;
                int choiceUser;
                char userDecision;

                do
                {
                    cout << BOLD << CYAN << "======= CLIENT MENU ========" << RESET << endl;
                    cout << BOLD << "1. Check Balance" << endl;
                    cout << "2. Withdraw Cash" << endl;
                    cout << "3. Transfer Cash" << endl;
                    cout << "4. View Transaction History" << endl;
                    cout << "5. Change PIN" << endl;
                    cout << "6. Exit" << endl;
                    //-----
                    cout << BOLD << YELLOW << "\nEnter your choice: " << RESET;
                    cin >> choiceUser;

                    clearScreen();

                    switch (choiceUser)
                    {
                    case 1:
                    {
                        displayDateTime();
                        cout << "Current Balance: Php " << balances[accountIndex] << endl;
                        break;
                    }
                    case 2:
                        // Withdraw cash
                        break;
                    case 3:
                        // Transfer cash
                        break;
                    case 4:
                    {
                        displayDateTime();
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
        }
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

        cout << BOLD << CYAN << "\n///=========Admin Menu:========/// " << RESET << endl;
        cout << BLUE << "1. View Current Cash" << endl;
        cout << "2. Refill Cash" << endl;
        cout << "3. Create Account" << endl;
        cout << "4. View accounts" << endl;
        cout << "5. Delete Account" << endl;
        cout << "6. Reset account passwords" << endl;
        cout << "7. Change admin Passcode" << endl;
        cout << "8. List of all admin users" << endl;
        cout << "9. Exit" << RESET << endl;

        cout << "\nEnter your choice: ";
        cin >> choiceAdmin;

        clearScreen();

        switch (choiceAdmin)
        {
        case 1:
        {
            cout << BOLD << CYAN << "Current cash in machine:\n"
                 << RESET;
            int totalCash = 0;
            for (int i = 0; i < NUM_DENOMINATIONS; i++)
            {
                totalCash += denominations[i] * billCount[i];
                cout << BOLD << YELLOW << "PHP " << denominations[i] << ": " << billCount[i] << " bills" << RESET << endl;
            }
            cout << BOLD << YELLOW << "Total cash available: PHP " << totalCash << RESET << endl;
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
