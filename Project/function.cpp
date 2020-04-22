#include "function.h"

void importAClassFromCsvFile(Account* acc, Classes*& aClass, ifstream fin) {
	
}
void addAStudentToAClass(Account* acc, Students*& aStudent, Classes*& aClass) {
	cout << "Enter first name: ";
	cin >> aStudent->account->firstname;
	cout << "Enter last name: ";
	cin >> aStudent->account->lastname;
	cout << "Enter date of birth: ";
	cout << "- Day: ";
	cin >> aStudent->account->doB->day;
	cout << "- Month: ";
	cin >> aStudent->account->doB->month;
	cout << "- Year: ";
	cin >> aStudent->account->doB->year;

}