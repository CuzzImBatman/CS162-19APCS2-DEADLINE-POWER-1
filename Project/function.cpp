#include "function.h"

void importAClassFromCsvFile(Account* acc, Classes*& aClass, ifstream fin) {
	if (acc->role != 1)
		return;
}
void addAStudentToAClass(Account* acc, Classes*& aClass) {
	if (acc->role != 1)
		return;
	Students* aStudent = new Students;
	aStudent->next = nullptr;
	// NAME
	cout << "Enter first name: ";
	cin >> aStudent->account->firstname;
	cout << "Enter last name: ";
	cin >> aStudent->account->lastname;
	// DOB
	cout << "Enter date of birth: ";
	cout << "- Day: ";
	cin >> aStudent->account->doB->day;
	cout << "- Month: ";
	cin >> aStudent->account->doB->month;
	cout << "- Year: ";
	cin >> aStudent->account->doB->year;
	// Insert into the class
	if (aClass->students == nullptr) {
		aClass->students = aStudent;
		return;
	}
	Students* tmp = aClass->students;
	while (tmp->next != nullptr)
		tmp = tmp->next;
	tmp->next = aStudent;
}
void editAStudent(Account* acc, Classes*& aClass) {
	if (acc->role != 1)
		return;
	int studentToEditNo;
	cout << "Enter student's No. in class: ";
	cin >> studentToEditNo;
	Students* subject = aClass->students;
	while (subject->studentNo != studentToEditNo)
		subject = subject->next;
	int choice;
	cout << "Edit: " << endl;
	cout << "	1. Full name" << endl;
	cout << "	2. Username" << endl;
	cout << "	3. Password (resetting only)" << endl;
	cout << "	4. Scoreboard" << endl;
	cout << "	5. Attendance" << endl;
	cout << "	0. Quit editing" << endl;
	cout << "Choice: ";
	cin >> choice;
	while (choice != 0) {
		switch (choice) {
			case 1:
				cout << "Current full name: "<< subject->account->lastname << ' ' << subject->account->firstname << endl;
				cout << "New full name: " << endl;
				cout << "- First name: ";
				getline(cin, subject->account->firstname);
				cout << "- Last name: ";
				getline(cin, subject->account->lastname);
				break;
			case 2:
				cout << "Current username: " <<  subject->account->uName << endl;
				cout << "New username: ";
				cin.getline(subject->account->uName, '\n');
				break;
			case 3:
				delete subject->account->pwd;
				subject->account->pwd = new char[9];
				subject->account->pwd[8] = '\0';
				string tmp = to_string(subject->account->doB->day);
				// Day
				if (subject->account->doB->day < 10) {
					subject->account->pwd[0] = '0';
					subject->account->pwd[1] = tmp[0];
				}
				else {
					subject->account->pwd[0] = tmp[0];
					subject->account->pwd[1] = tmp[1];
				}
				// Month
				tmp = to_string(subject->account->doB->month);
				if (subject->account->doB->day < 10) {
					subject->account->pwd[2] = '0';
					subject->account->pwd[3] = tmp[0];
				}
				else {
					subject->account->pwd[2] = tmp[0];
					subject->account->pwd[3] = tmp[1];
				}
				// Year
				tmp = to_string(subject->account->doB->year);
				for (int i = 4; i < 8; ++i)
					subject->account->pwd[i] = tmp[i-4];
				break;
			case 4:
				viewScoreboard(subject);
				break;
			case 5:
				viewAttendance(subject);
				break;
			default:
				break;
		}
		cout << "Choice: ";
		cin >> choice;
	}
}
void removeAStudent(Account* acc, Classes*& aClass) {
	if (acc->role != 1)
		return;
	int studentToRemoveNo;
	cout << "Enter student's No. in class: ";
	cin >> studentToRemoveNo;
	Students* tmp = aClass->students;
	while (tmp->next->studentNo != studentToRemoveNo)
		tmp = tmp->next;
	Students* toRemove = tmp->next;
	tmp->next = toRemove->next;
	delete toRemove;
}
void changeClassForStudents(Account* acc, Classes*& theClass) {
	if (acc->role != 1)
		return;
	int findStudent, findClass, findDestinationClass;
	// Find original class
	cout << "Please enter the class No:";
	cin >> findClass;
	Classes* scanClass = theClass;
	while (true) {
		while (scanClass != nullptr && scanClass->classNo != findClass)
			scanClass = scan->next;
		if (scanClass == nullptr)
			cout << "Cannot find the class!" << endl;
		else 
			break;
		cout << "Please re-enter the class No:";
		cin >> findClass;
		scanClass = theClass;
	}
	// Find student
	cout << "Please enter the student No:";
	cin >> findStudent;
	Students* scanStudent = scanClass->students;
	while (true) {
		while (scanStudent != nullptr && scanStudent->next->studentNo != findStudent)
			scanStudent = scanStudent->next;
		if (scanStudent == nullptr)
			cout << "Cannot find the student!" << endl;
		else 
			break;
		cout << "Please re-enter the student No:";
		cin >> findStudent;
		scanStudent = scanClass->students;
	}
	// Find destination class
	cout << "Please enter the destination class No:";
	cin >> findDestinationClass;
	if (findDestinationClass == findClass)
		return;
	/* scanClass CHANGES for REPURPOSED */
	scanClass = theClass;
	while (true) {
		while (scanClass != nullptr && scanClass->classNo != findDestinationClass)
			scanClass = scan->next;
		if (scanClass == nullptr)
			cout << "Cannot find the destination class!" << endl;
		else
			break;
		cout << "Please re-enter the destination class No:";
		cin >> findDestinationClass;
		if (findDestinationClass == findClass)
			return;
		scanClass = theClass;
	}
	// Remove the student from the original class
	Students* theStudent = scanStudent->next;
	scanStudent->next = scanStudent->next->next;
	theStudent->next = nullptr;
	// Add the student to the destination class
	/* scanStudent CHANGES for REPURPOSED */
	scanStudent = scanClass->students;
	while (scanStudent->next != nullptr)
		scanStudent = scanStudent->next;
	scanStudent->next = theStudent;
}
void viewListOfClasses(Account* acc, Classes* aClass) {
	for (Classes* scan = aClass; scan != nullptr; scan = scan->next)
		cout << scan->classNo << ". " << scan->className << endl;
}
void viewListOfStudentsInAClass(Account* acc, Classes* aClass) {
	for (Students* scan = aClass->students; scan != nullptr; scan = scan->next)
		cout << scan->studentNo << ". " << scan->account->lastname << ' ' << scan->account->firstname << endl;
}