#include "function.h"

Students* findStudent(Students* st, string stID);
Classes* findClass(Classes* Class, string ClassID);

#pragma region Class
void importAClassFromCsvFile(Classes*& aClass) {
	cout << "Haven't written this yet." << endl;
}
void addAStudentToAClass(Classes*& aClass) {
	string Class;
	cout << endl << "Enter the class to add the student to: ";
	cin >> Class;
	Classes* tmpClass = nullptr;
	while (true) {
		tmpClass = findClass(aClass, Class);
		if (tmpClass)
			break;
		else cout << "Class does not exist." << endl;
		cout << "Enter the class to add the student to: ";
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
	cin.ignore(10, '\n');
	getline(cin, aStudent->account->firstname);
	cout << "Enter the student's last name: ";
	getline(cin, aStudent->account->lastname);
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
	cout << endl << "Enter the class of the student: ";
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
	cout << "Enter the student's ID: ";
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

	cout << endl << "What do you want to edit? " << endl;
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
			cout << endl << "Current username: " << tmpSt->account->uName << endl;
			cout << "New username: ";
			cin >> tmpSt->account->uName;
			break;
		case 2:
			cout << endl << "Current password: " << tmpSt->account->pwd << endl;
			cout << "New password: ";
			cin >> tmpSt->account->pwd;
			break;
		case 3:
			cout << endl << "Current full name: " << tmpSt->account->lastname << ' ' << tmpSt->account->firstname << endl;
			cout << "New full name: " << endl;
			cout << "- First name: ";
			cin.ignore(10, '\n');
			getline(cin, tmpSt->account->firstname);
			cout << "- Last name: ";
			getline(cin, tmpSt->account->lastname);
			break;
		case 4:
			cout << endl << "Current gender: " << tmpSt->account->gender << endl;
			cout << "New gender: ";
			cin >> tmpSt->account->gender;
			break;
		case 5:
			cout << endl << "Current DoB: " << tmpSt->account->doB->day << '-' << tmpSt->account->doB->month << '-' << tmpSt->account->doB->year << endl;
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
	cout << endl << "Enter the class from which you want to remove a student: ";
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

	/*cout << "Enter the student's ID: ";
	string studentToRemove;
	cin >> studentToRemove;*/
	Students* tmp = tmpClass->students;
	if (tmp->studentID == studentToRemove) {
		Students* toRemove = tmp;
		tmpClass->students = tmpClass->students->next;
		
		delete toRemove;
		cout << "The student is successfully removed." << endl;
		return;
	}
	while (tmp->next->studentID != studentToRemove) //The student definitely exist, checked above.
		tmp = tmp->next;
	Students* toRemove = tmp->next;
	tmp->next = toRemove->next;
	delete toRemove;
	cout << "The student is successfully removed." << endl;
}
void changeClassForStudents(Classes*& classes) {
	cout << endl << "Enter the class from which you want to change the students: ";
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
	if (!tmpClassB->students)
		tmpClassB->students = tmpClassA->students;
	else {
		while (st->next)
			st = st->next;
		st->next = tmpClassA->students;
	}
	tmpClassA->students = nullptr;
	cout << endl << "All students from class " << classA << " are moved to class " << classB << endl;
}
void viewListOfClasses(Classes* aClass) {
	cout << endl << "Here is the list of classes: ";
	Classes* tmpClass = aClass;
	cout << endl;
	while (tmpClass) {
		cout << tmpClass->classID << endl;
		tmpClass = tmpClass->next;
	}
}
void viewListOfStudentsInAClass(Classes* aClass) {
	cout << endl << "Enter the class whose student list you want to view: ";
	string Class;
	cin >> Class;
	Classes* tmpClass = nullptr;
	while (true) {
		tmpClass = findClass(aClass, Class);
		if (tmpClass)
			break;
		cout << "Class does not exist." << endl;
		cout << "Enter the class whose student list you want to view: ";
		cin >> Class;
	}
	Students* st = tmpClass->students;
	if (!st)
		cout << "There is no student in this class." << endl;
	while (st) {
		cout << st->studentID << "     " << st->account->lastname << ' ' << st->account->firstname << endl;
		st = st->next;
	}
}
#pragma endregion

#pragma region Course
bool input(AcademicYears* AcaYear, Semesters*& semes, string& year)
{
	cout << "\nPlease enter Academic Year (1920/2021): ";
	cin >> year;
	while (AcaYear != nullptr && AcaYear->year != year)
		AcaYear = AcaYear->next;
	if (AcaYear == nullptr)
	{
		cout << "Academic year not found!" << endl;
		return false;
	}
	else
	{
		semes = AcaYear->semesters;
		char semester;
		cout << "Please enter Semester: ";
		cin >> semester;
		while (semes != nullptr && semes->semesterNo != semester)
			semes = semes->next;
		if (semes == nullptr)
		{
			cout << "Semester not found!" << endl;
			return false;
		}
		else return true;
	}
}

void viewCourseOfSemester(AcademicYears* acaYear)
{
	string year;
	Semesters* semes;
	if (input(acaYear, semes, year))
	{
		Courses* courseList = semes->courses;
		cout << "List of courses in year " << year << ", semester " << semes->semesterNo << " are: " << endl;
		while (courseList != nullptr)
		{
			cout << courseList->courseID << " - " << courseList->courseName << endl;
			courseList = courseList->next;
		}
	}
}

void createLecturer(AcademicYears* acaYear)
{
	string year;
	Semesters* semes;
	if (input(acaYear, semes, year))
	{
		Lecturers* lecturerList = semes->lecturers;
		while (lecturerList->next != nullptr)
			lecturerList = lecturerList->next;
		Lecturers* newLecturer = new Lecturers;
		newLecturer->account = new Accounts;
		lecturerList->next = newLecturer;
		newLecturer->next = nullptr;

		cout << "Enter new lecturer's first name: ";
		cin.ignore(10, '\n');
		getline(cin, newLecturer->account->firstname);
		cout << "Enter new lecturer's last name: ";
		getline(cin, newLecturer->account->lastname);
		newLecturer->account->pwd = "password";
		newLecturer->account->role = 3;
		newLecturer->account->uName = "";

		string lastname = newLecturer->account->lastname;
		string firstname = newLecturer->account->firstname;
		string& uName = newLecturer->account->uName = "";
		for (int i = 0; lastname[i] != '\0'; i++)
		{
			if (i == 0) uName += lastname[i] + 32;
			else if (lastname[i] == ' ') uName += lastname[i + 1] + 32;
		}
		for (int i = 0; firstname[i] != '\0'; i++)
		{
			if (i == 0) uName += firstname[i] + 32;
			else uName += firstname[i];
		}
		cout << "Enter new lecturer's gender: ";
		cin >> newLecturer->account->gender;
		cout << "Enter new lecturer's DOB (dd mm yyyy): ";
		newLecturer->account->doB = new Date;
		cin >> newLecturer->account->doB->day >> newLecturer->account->doB->month
			>> newLecturer->account->doB->year;
		cout << "\nNew lecturer's default username: " << newLecturer->account->uName;
		cout << "\nNew lecturer's default password: " << newLecturer->account->pwd << endl;
	}
}

void updateLecturer(AcademicYears* acaYear)
{
	string year;
	Semesters* semes;
	if (input(acaYear, semes, year))
	{
		Lecturers* lecturerList = semes->lecturers;
		string uName;
		cout << "\nPlease enter lecturer's username: ";
		cin >> uName;
		while (lecturerList != nullptr && lecturerList->account->uName != uName)
			lecturerList = lecturerList->next;
		if (lecturerList == nullptr)
		{
			cout << "Lecturer not found! \n";
			return;
		}
		cout << "\nWhat do you want to edit? " << endl;
		cout << "[1] Username." << endl;
		cout << "[2] Password." << endl;
		cout << "[3] Name." << endl;
		cout << "[4] Gender." << endl;
		cout << "[5] Date of Birth." << endl;
		cout << "[6] Back." << endl;
		cout << "Your choice: ";
		int choice;
		cin >> choice;
		string tmp;
		while (choice != 6)
		{
			switch (choice)
			{
			case 1: {
				cout << "Current username: " << lecturerList->account->uName << "\nNew username: ";
				cin >> lecturerList->account->uName;
			}
				  break;
			case 2: {
				cout << "Current password: " << lecturerList->account->pwd << "\nNew password: ";
				cin >> lecturerList->account->pwd;
			}
				  break;
			case 3: {
				cout << "Current full name: " << lecturerList->account->firstname << ' '
					<< lecturerList->account->lastname << endl;
				cout << "New full name: " << endl;
				cout << "- First name: ";
				cin.ignore(10, '\n');
				getline(cin, lecturerList->account->firstname);
				cout << "- Last name: ";
				getline(cin, lecturerList->account->lastname);
			}
				  break;
			case 4: {
				cout << "Current gender: " << lecturerList->account->gender << endl;
				cout << "New gender: " << endl;
				cin >> lecturerList->account->lastname;
			}
				  break;
			case 5: {
				cout << "Current DoB: " << lecturerList->account->doB << endl;
				cout << "New DoB (dd mm yyyy): ";
				cin >> lecturerList->account->doB->day
					>> lecturerList->account->doB->month
					>> lecturerList->account->doB->year;
			}
				  break;
			default:
				break;
			}
			cout << "\nWhat do you want to edit? " << endl;
			cout << "[1] Username." << endl;
			cout << "[2] Password." << endl;
			cout << "[3] Name." << endl;
			cout << "[4] Gender." << endl;
			cout << "[5] Date of Birth." << endl;
			cout << "[6] Back." << endl;
			cout << "Your choice: ";
			cin >> choice;
		}
	}
}

void deleteLecturer(AcademicYears* acaYear)
{
	string year;
	Semesters* semes;
	if (input(acaYear, semes, year))
	{
		Lecturers* lecturerList = semes->lecturers;
		Lecturers* prev = nullptr;
		string uName;
		cout << "\nPlease enter lecturer's username: ";
		cin >> uName;
		while (lecturerList != nullptr && lecturerList->account->uName != uName)
		{
			prev = lecturerList;
			lecturerList = lecturerList->next;
		}
		if (lecturerList == nullptr)
		{
			cout << "Lecturer not found! \n";
			return;
		}
		if (lecturerList == semes->lecturers)
		{
			Lecturers* tmp = lecturerList;
			semes->lecturers = semes->lecturers->next;
			delete tmp->account->doB;
			delete tmp->account;
			delete tmp;
		}
		else
		{
			Lecturers* tmp = lecturerList;
			prev->next = lecturerList->next;
			delete tmp->account->doB;
			delete tmp->account;
			delete tmp;
		}
	}
}

void viewLecturer(AcademicYears* acaYear)
{
	string year;
	Semesters* semes;
	if (input(acaYear, semes, year))
	{
		Lecturers* lecturerList = semes->lecturers;
		cout << "List of lecturers in year " << year << ", semester " << semes->semesterNo << " are: " << endl;
		while (lecturerList != nullptr)
		{
			cout << lecturerList->account->lastname << " " << lecturerList->account->firstname << endl;
			lecturerList = lecturerList->next;
		}
	}
}

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

Courses* findCourse(Courses* course, string ID) {
	Courses* temp = course;
	while (temp && temp->courseID != ID)
		temp = temp->next;
	return temp;
}
#pragma endregion

#pragma region Scoreboard
void viewScoreboardOfACourse(Courses* course) {
	cout << "What course whose scoreboard you want to view? ";
	string courseID;
	cin >> courseID;

	Courses* tmpCourse = nullptr;
	while (true) {
		tmpCourse = findCourse(course, courseID);
		if (tmpCourse)
			break;
		else cout << "Course does not exist." << endl;
		cout << "What course whose scoreboard you want to view? ";
		cin >> courseID;
	}
	//not finished
}
#pragma endregion

#pragma region Attendance List

#pragma endregion
