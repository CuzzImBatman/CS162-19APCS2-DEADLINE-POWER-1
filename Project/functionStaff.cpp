#include "function.h"
Classes* findClass(Classes* Class, string ClassID) {
	Classes* temp = Class;
	while (temp && temp->classID != ClassID)
		temp = temp->next;
	return temp;
}
Students* findStudent(Students* st, string stID) {
	Students* temp = st;
	while (temp && temp->studentID != stID)
		temp = temp->next;
	return temp;
}
Semesters* findSemester(Semesters* semes, char no) {
	Semesters* temp = semes;
	while (temp && temp->semesterNo != no)
		temp = temp->next;
	return temp;
}

#pragma region Class
void importAClassFromCsvFile(Classes*& aClass) {
	cout << "Haven't written this yet." << endl;
}
void addAStudentToAClass(Classes*& aClass) {
	string Class;
	cout << "Specify which class to add the student to: ";
	cin >> Class;
	Classes* tmpClass = nullptr;
	while (true) {
		tmpClass = findClass(aClass, Class);
		if (tmpClass)
			break;
		else cout << "Class does not exist." << endl;
		cout << "Specify which class to add the student to: ";
		cin >> Class;
	}
	Students* aStudent = new Students;
	aStudent->account = new Accounts;
	aStudent->account->role = 1;
	cout << "Enter student ID: ";
	cin >> aStudent->studentID;
	aStudent->account->uName = aStudent->studentID;
	aStudent->account->pwd = "password";
	cout << "Enter the student's first name: ";
	getline(cin, aStudent->account->firstname);
	cout << "Enter the student's last name: ";
	cin >> aStudent->account->lastname;
	cout << "Enter the student's gender: ";
	cin >> aStudent->account->gender;
	aStudent->account->doB = new Date;
	cout << "Enter the student's DoB: " << endl;
	cout << "- Day: ";
	cin >> aStudent->account->doB->day;
	cout << "- Month: ";
	cin >> aStudent->account->doB->month;
	cout << "- Year: ";
	cin >> aStudent->account->doB->year;
	Students* tmp = tmpClass->students;
	while (tmp->next != nullptr)
		tmp = tmp->next;
	tmp->next = aStudent;
}
void editAStudent(Classes*& aClass) {
	string Class;
	cout << "Enter the class of the student: ";
	cin >> Class;
	Classes* tmpClass = nullptr;
	while (true) {
		tmpClass = findClass(aClass, Class);
		if (tmpClass)
			break;
		else cout << "Class does not exist." << endl;
		cout << "Enter the class of the student: ";
		cin >> Class;
	}

	string st;
	cout << "Enter the studetn's ID: ";
	cin >> st;
	Students* tmpSt = nullptr;
	while (true) {
		tmpSt = findStudent(tmpClass->students, st);
		if (tmpSt)
			break;
		else cout << "Student does not exist." << endl;
		cout << "Enter the studetn's ID: ";
		cin >> st;
	}
	int choice;

	cout << "What do you want to edit? " << endl;
	cout << "[1] Username." << endl;
	cout << "[2] Password." << endl;
	cout << "[3] Name." << endl;
	cout << "[4] Gender." << endl;
	cout << "[5] Date of Birth." << endl;
	cout << "[6] Back." << endl;
	cout << "Your choice: ";
	cin >> choice;
	while (choice != 6) {
		switch (choice) {
		case 1:
			cout << "Current username: " << tmpSt->account->uName << endl;
			cout << "New username: ";
			cin >> tmpSt->account->uName;
			break;
		case 2:
			cout << "Current password: " << tmpSt->account->pwd << endl;
			cout << "New password: ";
			cin >> tmpSt->account->pwd;
			break;
		case 3:
			cout << "Current full name: " << tmpSt->account->firstname << ' ' << tmpSt->account->lastname << endl;
			cout << "New full name: " << endl;
			cout << "- First name: ";
			cin.ignore(10, '\n');
			getline(cin, tmpSt->account->firstname);
			cout << "- Last name: ";
			cin >> tmpSt->account->lastname;
			break;
		case 4:
			cout << "Current gender: " << tmpSt->account->gender << endl;
			cout << "New gender: " << endl;
			cin >> tmpSt->account->lastname;
			break;
		case 5:
			cout << "Current DoB: " << tmpSt->account->doB << endl;
			cout << "New DoB: " << endl;
			cout << "- Day: ";
			cin >> tmpSt->account->doB->day;
			cout << "- Month: ";
			cin >> tmpSt->account->doB->month;
			cout << "- Year: ";
			cin >> tmpSt->account->doB->year;
			break;
		default:
			break;
		}
		cout << endl << "What do you want to edit? " << endl;
		cout << "[1] Username." << endl;
		cout << "[2] Password." << endl;
		cout << "[3] Name." << endl;
		cout << "[4] Gender." << endl;
		cout << "[5] Date of Birth." << endl;
		cout << "[6] Back." << endl;
		cout << "Your choice: ";
		cout << "Your choice: ";
		cin >> choice;
	}
}
void removeAStudent(Classes*& aClass) {
	cout << "Enter the class from which you want to renmove a student: ";
	string Class;
	cin >> Class;
	Classes* tmpClass = nullptr;
	while (true) {
		tmpClass = findClass(aClass, Class);
		if (tmpClass)
			break;
		cout << "Class does not exist." << endl;
		cout << "Enter the class from which you want to remove a students: ";
		cin >> Class;
	}
	
	cout << "Enter the student's ID: ";
	string studentToRemove;
	cin >> studentToRemove;
	Students* tmpSt = nullptr;
	while (true) {
		tmpSt = findStudent(tmpClass->students, studentToRemove);
		if (tmpSt)
			break;
		cout << "Student does not exist." << endl;
		cout << "Enter the student's ID: ";
		cin >> studentToRemove;
	}

	Students* tmp = tmpClass->students;
	if (tmp->studentID == studentToRemove) {
		Students* toRemove = tmp;
		tmp = tmp->next;
		delete tmp;
		cout << "The student is successfully removed.";
		return;
	}
	while (tmp->next->studentID != studentToRemove) //The student definitely exist, checked above.
		tmp = tmp->next;
	Students* toRemove = tmp->next;
	tmp->next = toRemove->next;
	delete toRemove;
}
void changeClassForStudents(Classes*& classes) {
	cout << "Enter the class from which you want to change the students: ";
	string classA;
	cin >> classA;
	Classes* tmpClassA = nullptr;
	while (true) {
		tmpClassA = findClass(classes, classA);
		if (tmpClassA)
			break;
		cout << "Class does not exist." << endl;
		cout << "Enter the class from which you want to change the students: ";
		cin >> classA;
	}
	cout << "Enter the class to which you want to change the students: ";
	string classB;
	cin >> classB;
	Classes* tmpClassB = nullptr;
	while (true) {
		tmpClassB = findClass(classes, classB);
		if (tmpClassB)
			break;
		cout << "Class does not exist." << endl;
		cout << "Enter the class to which you want to change the students: ";
		cin >> classB;
	}
	Students* st = tmpClassB->students;
	while (st->next)
		st = st->next;
	st->next = tmpClassA->students;
	tmpClassA->students = nullptr;
	cout << endl << "All students from class " << classA << " are moved to class " << classB << endl;
}
void viewListOfClasses(Classes* aClass) {
	cout << "Here is the list of classes: ";
	Classes* tmpClass = aClass;
	while (tmpClass) {
		cout << tmpClass->classID << endl;
		tmpClass = tmpClass->next;
	}
}
void viewListOfStudentsInAClass(Classes* aClass) {
	cout << "Enter the class from which you want to view student list: ";
	string Class;
	cin >> Class;
	Classes* tmpClass = nullptr;
	while (true) {
		tmpClass = findClass(aClass, Class);
		if (tmpClass)
			break;
		cout << "Class does not exist." << endl;
		cout << "Enter the class from which you want to view student list: ";
		cin >> Class;
	}
	Students* st = tmpClass->students;
	while (st) {
		cout << st->studentID << "     " << st->account->firstname << ' ' << st->account->lastname << endl;
		st = st->next;
	}
}
#pragma endregion

#pragma region Course

#pragma endregion

#pragma region Scoreboard

#pragma endregion

#pragma region Attendance List

#pragma endregion