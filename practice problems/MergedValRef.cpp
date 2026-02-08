#include <iostream>
using namespace std;

void addOneValue(int x) {
	x = x * 2;
    cout << "Inside val function: " << x << endl;
}
void addOneReference(int &x) {
	x = x * 2;
	cout << "Inside ref function: " << x << endl;
}
int main() {

	int num = 10;
	
	cout << "Before Pass by Value: " << num << endl;
	addOneValue(num);
	cout << "Pass by Value: " << num << endl;

	int ref;
	cout << "Before Pass by Reference: " << num << endl;
	addOneReference(num);
	cout << "Pass by Reference: " << num << endl;
	return 0;
}
