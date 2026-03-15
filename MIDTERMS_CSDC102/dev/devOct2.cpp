#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <ctime>
using namespace std;

//--------------------------------------------------------------------Main functions
// Color codes
const string RESET = "\033[0m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string MAGENTA = "\033[35m";
const string CYAN = "\033[36m";
const string WHITE = "\033[37m";
const string BOLD = "\033[1m";
const string FAINT = "\033[2m";
const string ITALIC = "\033[3m";
const string UNDERLINE = "\033[4m";
const string SLOW_BLINK = "\033[5m";

const string RAPID_BLINK = "\033[6m";
const string REVERSE_VIDEO = "\033[7m";
const string CONCEAL = "\033[8m";
const string CROSSED_OUT = "\033[9m";
const string BOLD_OFF = "\033[22m";
const string ITALIC_OFF = "\033[23m";
const string UNDERLINE_OFF = "\033[24m";
const string BLINK_OFF = "\033[25m";
const string REVERSE_VIDEO_OFF = "\033[27m";
const string CONCEAL_OFF = "\033[28m";
const string CROSSED_OUT_OFF = "\033[29m";

// Background color
const string BLACK_BG = "\033[40m";
const string RED_BG = "\033[41m";
const string GREEN_BG = "\033[42m";
const string YELLOW_BG = "\033[43m";
const string BLUE_BG = "\033[44m";
const string MAGENTA_BG = "\033[45m";
const string CYAN_BG = "\033[46m";
const string WHITE_BG = "\033[47m";
const string DEFAULT_BG = "\033[49m";

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
double calculateFeeRecursive(double withdrawAmount, string currentUserBank, string userAccountType, int iterations);
void calculateBills(double withdrawAmount, int &bills1000, int &bills500, int &bills100);
void refillCash(int denom[], int billCount[]);
void viewAccounts(vector<string> &cardNumbers, vector<double> &balances);
void showAccountDetails(vector<string> &cardNumbers, vector<string> &userBanks, vector<string> &accountTypes, vector<double> &balances, int i);
void logTransaction(const string &cardNum, const string &type,double amount,double fee);

//--------------------------------------------------------------------Main

int main()
{
    vector<string> cardNumbers = {"12345678910", "10987654321", "11111111111"};
    vector<string> encodedPINs = {encodeString("6767"), encodeString("9876"), encodeString("6543")};
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
        else
            break;
    }

    system("pause");
    return 0;
}

//--------------------------------------------------------------------Login function

int login(string &adminPasscode, vector<string> &cardNumbers, vector<string> &encodedPINs)
{
    int roleChoice;

    cout << BOLD << CYAN << ITALIC << "======================================================" << endl;
    cout << "        K H G :  B A N K I N G  S Y S T E M           " << endl;
    cout << "======================================================" << ITALIC_OFF << endl;
    cout << "Supported Banks: BDO, BPI, Metrobank, Security Bank" << endl;
    cout << "======================================================" << RESET << endl;

    cout << BOLD << YELLOW << "\n[1] Client   [2] Admin   [3] Shutdown" << RESET << endl;
    cout << BOLD << BLUE << "Enter your choice: " << RESET;
    cin >> roleChoice;

    if (roleChoice == 1) return 1;

    if (roleChoice == 2)
    {
        for (int attempts = 0; attempts < 3; attempts++)
        {
            string passcode;
            cout << BOLD << BLUE << "Enter admin passcode: " << RESET;
            cin >> passcode;

            if (passcode == adminPasscode)
            {
                cout << BOLD << GREEN << "\nAdmin access granted." << RESET;
                return 2;
            }

            cout << BOLD << RED << "Incorrect passcode (" << attempts + 1 << "/3).\n" << RESET;
        }
    }

    cout << BOLD << RED << "System shutting down..." << RESET << endl;
    return 0;
}

//--------------------------------------------------------------------Security functions

string encodeString(string plain)
{
    string encoded = plain;
    for (char &c : encoded) c += 3;
    return encoded;
}

string decodeString(string encoded)
{
    string decoded = encoded;
    for (char &c : decoded) c -= 3;
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

    cout << " \nTime: " << timeinfo->tm_hour << ":"
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

//--------------------------------------------------------------------Card validation

bool validateCardNumber(vector<string> &cardNumbers, string userCard, int &accountIndex)
{
    for(int i=0;i<cardNumbers.size();i++)
    {
        if(cardNumbers[i]==userCard)
        {
            accountIndex=i;
            return true;
        }
    }
    return false;
}

//--------------------------------------------------------------------Fee recursion

double calculateFeeRecursive(double withdrawAmount,string currentUserBank,string userAccountType,int iterations)
{
    if(iterations==NUM_BANKS) return 0;

    if(currentUserBank==bankNames[iterations])
    {
        if(userAccountType=="Local")
            return localFees[iterations];
        else
            return intlFees[iterations];
    }

    return calculateFeeRecursive(withdrawAmount,currentUserBank,userAccountType,iterations+1);
}

//--------------------------------------------------------------------Bills recursion

void calculateBills(double withdrawAmount,int &bills1000,int &bills500,int &bills100)
{
    if(withdrawAmount>=1000)
    {
        bills1000++;
        calculateBills(withdrawAmount-1000,bills1000,bills500,bills100);
    }
    else if(withdrawAmount>=500)
    {
        bills500++;
        calculateBills(withdrawAmount-500,bills1000,bills500,bills100);
    }
    else if(withdrawAmount>=100)
    {
        bills100++;
        calculateBills(withdrawAmount-100,bills1000,bills500,bills100);
    }
}

//--------------------------------------------------------------------Withdraw

bool withdraw(vector<double> &balances,int accountIndex,double withdrawAmount)
{
    if(balances[accountIndex] >= withdrawAmount)
    {
        balances[accountIndex]-=withdrawAmount;
        return true;
    }
    return false;
}

bool withdraw(vector<double> &balances,int accountIndex,string presetAmount)
{
    double withdrawAmount = stod(presetAmount);
    return withdraw(balances,accountIndex,withdrawAmount);
}

//--------------------------------------------------------------------Transaction logger

void logTransaction(const string &cardNum,const string &type,double amount,double fee)
{
    ofstream file("transactions.csv",ios::app);

    if(file.is_open())
    {
        time_t now=time(0);
        tm *timeinfo=localtime(&now);

        file<<(timeinfo->tm_mon+1)<<"/"<<timeinfo->tm_mday<<"/"<<(timeinfo->tm_year+1900)<<","
            <<timeinfo->tm_hour<<":"<<timeinfo->tm_min<<","
            <<cardNum<<","<<type<<","<<amount<<","<<fee<<endl;

        file.close();
    }
}

//--------------------------------------------------------------------Client Menu (transfer implemented)

void clientMenu(vector<string> &cardNumbers,
                vector<string> &encodedPINs,
                vector<double> &balances,
                vector<string> &userBanks,
                vector<string> &accountTypes)
{
    string cardNum_user;

    cout<<BOLD<<BLUE<<"Enter Card Number: "<<RESET;
    cin>>cardNum_user;

    int accountIndex;

    if(!validateCardNumber(cardNumbers,cardNum_user,accountIndex))
    {
        cout<<RED<<"Card not found"<<RESET<<endl;
        return;
    }

    string userPin;
    cout<<BOLD<<BLUE<<"Enter PIN: "<<RESET;
    cin>>userPin;

    if(encodeString(userPin)!=encodedPINs[accountIndex])
    {
        cout<<RED<<"Incorrect PIN"<<RESET<<endl;
        return;
    }

    int choiceUser;

    do
    {
        cout<<BOLD<<CYAN<<"======= CLIENT MENU ========"<<RESET<<endl;
        cout<<"1. Check Balance"<<endl;
        cout<<"2. Withdraw Cash"<<endl;
        cout<<"3. Transfer Cash"<<endl;
        cout<<"4. View Transaction History"<<endl;
        cout<<"5. Change PIN"<<endl;
        cout<<"6. Exit"<<endl;

        cin>>choiceUser;

        if(choiceUser==1)
        {
            cout<<"Balance: "<<balances[accountIndex]<<endl;
        }

        if(choiceUser==2)
        {
            double withdrawAmount;
            cout<<"Enter amount: ";
            cin>>withdrawAmount;

            double fee=calculateFeeRecursive(withdrawAmount,userBanks[accountIndex],accountTypes[accountIndex],0);

            int bankIndex=0;
            for(int i=0;i<NUM_BANKS;i++)
                if(userBanks[accountIndex]==bankNames[i]) bankIndex=i;

            if(withdrawAmount>dailyLimits[bankIndex])
            {
                cout<<"Daily limit exceeded"<<endl;
                continue;
            }

            if(withdraw(balances,accountIndex,withdrawAmount+fee))
            {
                int b1000=0,b500=0,b100=0;

                calculateBills(withdrawAmount,b1000,b500,b100);

                billCount[0]-=b100;
                billCount[1]-=b500;
                billCount[2]-=b1000;

                cout<<"Withdraw successful"<<endl;
                logTransaction(cardNumbers[accountIndex],"Withdraw",withdrawAmount,fee);
            }
        }

        if(choiceUser==3)
        {
            string targetCard;
            double amount;

            cout<<"Enter recipient card: ";
            cin>>targetCard;

            int receiverIndex;

            if(!validateCardNumber(cardNumbers,targetCard,receiverIndex))
            {
                cout<<"Recipient not found"<<endl;
                continue;
            }

            cout<<"Enter amount: ";
            cin>>amount;

            if(balances[accountIndex]>=amount)
            {
                balances[accountIndex]-=amount;
                balances[receiverIndex]+=amount;

                logTransaction(cardNumbers[accountIndex],"TransferOut",amount,0);
                logTransaction(cardNumbers[receiverIndex],"TransferIn",amount,0);

                cout<<"Transfer successful"<<endl;
            }
            else
                cout<<"Insufficient balance"<<endl;
        }

        if(choiceUser==4)
        {
            ifstream file("transactions.csv");
            string line;

            while(getline(file,line))
            {
                if(line.find(cardNumbers[accountIndex])!=string::npos)
                    cout<<line<<endl;
            }

            file.close();
        }

        if(choiceUser==5)
        {
            string newpin;
            cin>>newpin;

            encodedPINs[accountIndex]=encodeString(newpin);
        }

    }while(choiceUser!=6);
}

//--------------------------------------------------------------------Admin Menu (index validation added)

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
        cout<<"1 View Cash\n2 Refill\n3 Create Account\n4 View Accounts\n5 Delete\n6 Reset PIN\n7 Change Pass\n9 Exit\n";

        cin>>choiceAdmin;

        if(choiceAdmin==3)
        {
            string card,pin,bank,type;
            double bal;

            cin>>card>>pin>>bal>>bank>>type;

            cardNumbers.push_back(card);
            encodedPINs.push_back(encodeString(pin));
            balances.push_back(bal);
            userBanks.push_back(bank);
            accountTypes.push_back(type);
        }

        if(choiceAdmin==4)
        {
            viewAccounts(cardNumbers,balances);
        }

        if(choiceAdmin==5)
        {
            int index;
            cin>>index;

            if(index>=0 && index<cardNumbers.size())
            {
                cardNumbers.erase(cardNumbers.begin()+index);
                encodedPINs.erase(encodedPINs.begin()+index);
                balances.erase(balances.begin()+index);
                userBanks.erase(userBanks.begin()+index);
                accountTypes.erase(accountTypes.begin()+index);
            }
        }

        if(choiceAdmin==6)
        {
            int index;
            cin>>index;

            if(index>=0 && index<encodedPINs.size())
            {
                string newPIN;
                cin>>newPIN;
                encodedPINs[index]=encodeString(newPIN);
            }
        }

    }while(choiceAdmin!=9);
}

//--------------------------------------------------------------------

void refillCash(int denom[], int billCount[])
{
    time_t now = time(0);
    tm *localTime = localtime(&now);

    if(localTime->tm_hour==8 && localTime->tm_min<=15)
    {
        int refillAmount;

        for(int i=0;i<NUM_DENOMINATIONS;i++)
        {
            cin>>refillAmount;
            billCount[i]+=refillAmount;
        }
    }
}

void viewAccounts(vector<string> &cardNumbers,vector<double> &balances)
{
    for(int i=0;i<cardNumbers.size();i++)
    {
        cout<<i<<" "<<cardNumbers[i]<<" Balance: "<<balances[i]<<endl;
    }
}

void showAccountDetails(vector<string> &cardNumbers,vector<string> &userBanks,vector<string> &accountTypes,vector<double> &balances,int i)
{
    cout<<"Bank: "<<userBanks[i]<<endl;
    cout<<"Type: "<<accountTypes[i]<<endl;
    cout<<"Balance: "<<balances[i]<<endl;
}