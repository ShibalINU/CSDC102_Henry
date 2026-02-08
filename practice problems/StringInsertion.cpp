/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <string>

using namespace std; 

int main()
{
    string arr[6] = {"henry", "vince", "james", "annabelle", "", ""};
    int size = 4;
    string newName = "Cynthia";
    int position = 2;
    
    cout << "Before insertion: ";
    for(int i = 0; i < size; i++){
        cout << arr[i] << " ";     
    }
    
    for(int i = size - 1; i >= position; i--){
        arr[i + 1] = arr[i];
    }
    
    arr[position] = newName;
    
    cout << endl;
    size++;
    
    cout << "After insertion: ";
    for(int i = 0; i < size; i++){
        cout << arr[i] << " ";     
    }
    return 0;
}
