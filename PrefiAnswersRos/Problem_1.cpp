#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

struct Student
{
    string name;
    float midterm;
    float final_exam;
    float average;
};

int main()
{
    Student Students[5];
    for (int i = 0; i < 5; i++)
    {
        cout << "Enter name of student " << i + 1 << ": " << endl;
        cin.ignore();
        getline(cin, Students[i].name);
        
        clearScreen();
        cout << "Enter midterm grade for " << Students[i].name << ": " << endl;
        cin >> Students[i].midterm;

        clearScreen();
        
        cout << "Enter final exam grade for " << Students[i].name << ": " << endl;
        cin >> Students[i].final_exam;
        
        clearScreen();

        Students[i].average = (Students[i].midterm + Students[i].final_exam) / 2;
    }
    
    cout << left << setw(20) << "Name"
         << setw(10) << "Midterm"
         << setw(10) << "Final"
         << setw(10) << "Average"
         << "Remark" << endl;
    cout << "-----               ------   ------     -------   ------     \n";
    
    for (int i = 0; i < 5; i++) {
        cout << left << setw(20) << Students[i].name
             << setw(10) << Students[i].midterm
             << setw(10) << Students[i].final_exam
             << setw(10) << Students[i].average;

        if (Students[i].average >= 75)
            cout << "Passed";
        else
            cout << "Failed";

        cout << endl;
    }


    return 0;
}
