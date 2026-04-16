//formatting not final

#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Student
{
    string name;
    float midterm;
    float final_exam;
    float average;
};

int main()
{
    Student Students[2];
    for (int i = 0; i < 2; i++)
    {
        cout << "Enter name of student " << i + 1 << ": " << endl;
        getline(cin, Students[i].name);
        cout << "Enter midterm grade for " << Students[i].name << ": " << endl;
        cin >> Students[i].midterm;

        cout << "Enter final exam grade for " << Students[i].name << ": " << endl;
        cin >> Students[i].final_exam;

        cin.ignore();

        Students[i].average = (Students[i].midterm + Students[i].final_exam) / 2;
    }
    cout << "Name                   Midterm      Final     Average       Remark" << endl;
    cout << "-----                  --------     ------    -------       ------" << endl;
    for (int i = 0; i < 2; i++)
    {
        cout << Students[i].name << "       " << Students[i].midterm << "           " << Students[i].final_exam << "           " << Students[i].average;
        if (Students[i].average >= 75)
        {
            cout << "       Passed" << endl;
        }
        else
        {
            cout << "           Failed" << endl;
        }
    }

    return 0;
}
