#include "function.h"
#include <stdio.h>
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
	string pwd = aStudent->account->doB->day + aStudent->account->doB->month + aStudent->account->uName;
	sha256_init(&aStudent->account->pwd);
	sha256_update(&aStudent->account->pwd, pwd, pwd.length());
	aStudent->checkincourse = NULL;
	aStudent->scoreboards = NULL;
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 4; j++)
		{
			aStudent->schedule[i][j] = tmpClass->schedule[i][j];
			if (tmpClass->schedule[i][j] != "//")
			{
				AddCheckInCourse(aStudent, tmpClass->schedule[i][j]);
				AddScoreBoardCourse(aStudent, tmpClass->schedule[i][j]);

			}
		}
	Students* tmp = tmpClass->students;
	if (tmp == nullptr)
		// Joey: Doesn't work yet
		tmp = aStudent;
	else {
		while (tmp->next != nullptr)
			tmp = tmp->next;
		tmp->next = aStudent;
	}
	aStudent->next = nullptr;
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
		cout << "Enter the student's ID: ";
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
			// Joey: DOES NOT WORK
			cout << endl << "Current username: " << tmpSt->account->uName << endl;
			cout << "New username: ";
			cin >> tmpSt->account->uName;
			break;
		case 2:

			cout << "New password: ";
			cin >> Class;
			sha256_init(&tmpSt->account->pwd);
			sha256_update(&tmpSt->account->pwd, Class, Class.length());
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
		cin >> choice;
	}
}
void removeAStudent(Classes*& aClass, Courses*& course, char semes, string year) {
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
	Students* tmpSt = nullptr, * tmp = tmpClass->students;
	while (true) {
		tmpSt = findStudent(tmpClass->students, studentToRemove);
		if (tmpSt && tmpSt->Status==1)
			break;
		cout << "Student does not exist." << endl;
		cout << "Enter the student's ID: ";
		cin >> studentToRemove;
	}
	tmpSt = tmpClass->students;
	if (tmpSt->studentID == studentToRemove)
	{
		string s = "Yr" + year  + "_StudentID" + tmpSt->studentID + "ScoreBoard.txt";
		RemoveFile(s);
		DeleteScoreBoardStudent(tmpSt);
		DeleteCheckinCourseStudent(tmpSt);
		DeleteStudentFromCourses(tmpSt->studentID, tmpClass->classID, course);
		tmpClass->students = tmpClass->students->next;
		delete tmpSt->account->doB;
		delete tmpSt->account;
		delete tmpSt;
		tmpSt = NULL;
		cout << "The student is successfully removed." << endl;
		return;

	}
	tmp = tmpClass->students;
	while (tmpSt)
	{
		if (tmpSt->studentID == studentToRemove)
		{
			DeleteScoreBoardStudent(tmpSt);
			DeleteCheckinCourseStudent(tmpSt);
			DeleteStudentFromCourses(tmpSt->studentID, tmpClass->classID, course);
			Students* del = tmpSt;
			tmp->next = tmpSt->next;
			tmpSt = tmpSt->next;
			delete del->account->doB;
			delete del->account;
			delete del;
			del = NULL;
			cout << "The student is successfully removed." << endl;
			return;
		}

		tmp = tmpSt;
		tmpSt = tmpSt->next;
	}


	/*tmpSt->Status = -2;
	cout << "The student is successfully removed." << endl;*/

	/*cout << "Enter the student's ID: ";
	string studentToRemove;
	cin >> studentToRemove;*/
	/*Students* tmp = tmpClass->students;
	if (tmp->studentID == studentToRemove) {

		tmp->Status = -2;
		cout << "The student is successfully removed." << endl;
		return;
	}
	while (tmp->next->studentID != studentToRemove) //The student definitely exist, checked above.
		tmp = tmp->next;*/

}
void changeClassForStudents(Classes*& classes, Courses*& course, char semes, string year) {
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
	cout << "Enter the student's ID: ";
	string studentToChange;
	cin >> studentToChange;
	Students* tmpSt = nullptr;
	while (true) {
		tmpSt = findStudent(tmpClassA->students, studentToChange);
		if (tmpSt)
			break;
		cout << "Student does not exist." << endl;
		cout << "Enter the student's ID: ";
		cin >> studentToChange;
	}
	string s = "Yr" + year  + "_StudentID" + tmpSt->studentID + "ScoreBoard.txt";
	RemoveFile(s);
	Students* AddSt = new Students;
	AddSt->account = tmpSt->account;
	AddSt->studentID = tmpSt->studentID;
	if (tmpSt->studentID == studentToChange)
	{
		DeleteScoreBoardStudent(tmpSt);
		DeleteCheckinCourseStudent(tmpSt);
		DeleteStudentFromCourses(tmpSt->studentID, tmpClassA->classID, course);
		tmpClassA->students = tmpClassA->students->next;
		delete tmpSt;
		tmpSt = NULL;
	}
	Students*  tmp = tmpClassA->students;
	while (tmpSt)
	{
		if (tmpSt->studentID == studentToChange)
		{
			DeleteScoreBoardStudent(tmpSt);
			DeleteCheckinCourseStudent(tmpSt);
			DeleteStudentFromCourses(tmpSt->studentID, tmpClassA->classID, course);
			Students* del = tmpSt;
			tmp->next = tmpSt->next;
			tmpSt = tmpSt->next;
			delete del;
			del = NULL;
			break;
		}

		tmp = tmpSt;
		tmpSt = tmpSt->next;
	}


	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 4; j++)
		{
			AddSt->schedule[i][j] = tmpClassB->schedule[i][j];
			if (tmpClassB->schedule[i][j] != "//")
			{
				AddCheckInCourse(AddSt, tmpClassB->schedule[i][j]);
				AddScoreBoardCourse(AddSt, tmpClassB->schedule[i][j]);
			}
		}


	AddSt->Status = 1;
	FillCheckinCourse(AddSt);
	AddSt->next = tmpClassB->students;
	tmpClassB->students = AddSt;
	UpdateBitAttend(tmpClassB->classID, course);
	cout << "Changed.";
	/// scoreborad
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
	while (st)
	{
		if (st->Status==1)
			cout << st->studentID << "     " << st->account->lastname << ' ' << st->account->firstname << endl;
		st = st->next;
	}
}
#pragma endregion

#pragma region Course
void createAcademicYear(AcademicYears*& year)
{
	ofstream out;
	AcademicYears* newYear = new AcademicYears;
	cout << "Please enter the academic year: ";
	cin >> newYear->year;
	newYear->semesters = new Semesters;
	newYear->classes = nullptr;
	newYear->semesters->courses = nullptr;
	newYear->semesters->lecturers = nullptr;
	newYear->semesters->staffs = nullptr;

	out.close();

	newYear->next = year;
	year = newYear;
}

void updateAcademicYear(AcademicYears* year)
{
	if (year == nullptr)
	{
		cout << "No year to update!\n";
		return;
	}
	string updateYear;
	cout << "Please enter year that needs updating: ";
	cin >> updateYear;
	while (year != nullptr && year->year != updateYear)
		year = year->next;
	if (year == nullptr)
	{
		cout << "Can't find year!\n";
		return;
	}
	int choice;
	cout << "What do you want to update?\n"
		"[1] Year.\n"
		"[2] Lecturers.\n"
		"[3] Students. \n"
		"Your choice: ";
	cin >> choice;
	switch (choice)
	{
	case 1:
		cout << "Please enter new year: ";
		cin >> year->year;
		break;
	case 2:
		updateLecturer(year);
		break;
	case 3:
		editAStudent(year->classes);
		break;
	}
}
void staff_deleteClasses(Classes*& Class, string year) {
	Classes* tempClass = Class;
	while (tempClass) {
		string fileName = "Yr" + year + "_Cl" + tempClass->classID + "_StudentDB_TEST.txt";
		RemoveFile(fileName);
		deleteStudents(tempClass->students);
		Classes* newTemp = tempClass;
		tempClass = tempClass->next;
		delete newTemp;
	}
}
void staff_deleteAcademicYear(AcademicYears*& year)
{
	if (year == nullptr)
	{
		cout << "No year to delete!\n";
		return;
	}
	AcademicYears* prev = nullptr;
	AcademicYears* tempYear = year;
	cout << "Please enter year to delete: ";
	string deletingYear;
	cin >> deletingYear;
	while (tempYear != nullptr && tempYear->year != deletingYear)
	{
		prev = year;
		tempYear = tempYear->next;
	}
	if (tempYear == nullptr)
	{
		cout << "Can't find academic year " << deletingYear << endl;
		return;
	}

	else if (tempYear == year) year = year->next;
	else prev->next = tempYear->next;

	staff_deleteClasses(tempYear->classes, tempYear->year);
	deleteSemesters(tempYear->semesters);
	string fileName;
	fileName = "Yr" + tempYear->year + "_ClassDB_TEST.txt";
	RemoveFile(fileName);
	for (int i = 49; i < 53; i++)
	{
		fileName = "Yr" + tempYear->year + "_Sem" + (char)i + "_LecturerDB_TEST.txt";
		RemoveFile(fileName);
		fileName = "Yr" + tempYear->year + "_Sem" + (char)i + "_StaffDB_TEST.txt";
		RemoveFile(fileName);
		fileName = "Yr" + tempYear->year + "_Sem" + (char)i + "_CourseDB_TEST.txt";
		RemoveFile(fileName);
	}
	delete tempYear;
}

void viewAcademicYear(AcademicYears* year)
{
	if (year == nullptr)
	{
		cout << "No year to view!\n";
		return;
	}
	while (year)
	{
		cout << "Academic year:\n";
		cout << year->year << endl;
		year = year->next;
	}
}

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
		Lecturers* newLecturer = new Lecturers;
		newLecturer->account = new Accounts;
		newLecturer->next = semes->lecturers;
		semes->lecturers = newLecturer;

		cout << "Enter new lecturer's first name (one word): ";
		cin.ignore(10, '\n');
		getline(cin, newLecturer->account->firstname);
		cout << "Enter new lecturer's last name (rest of your name): ";
		getline(cin, newLecturer->account->lastname);

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
		string pwd = newLecturer->account->doB->day + newLecturer->account->doB->month + newLecturer->account->uName;
		sha256_init(&newLecturer->account->pwd);
		sha256_update(&newLecturer->account->pwd, pwd, pwd.length());
		cout << "\nNew lecturer's default password: " << pwd << endl;
	}
}

void updateLecturer(AcademicYears* acaYear)
{
	string year;
	Semesters* semes;
	if (input(acaYear, semes, year))
	{
		if (semes->lecturers == nullptr)
			cout << "No lecturer to update!\n";
		else
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
					cout << "\nNew password: ";
					cin >> year;
					sha256_init(&lecturerList->account->pwd);
					sha256_update(&lecturerList->account->pwd, year, year.length());
				};
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
}

void deleteLecturer(AcademicYears* acaYear)
{
	string year;
	Semesters* semes;
	if (input(acaYear, semes, year))
	{
		if (semes->lecturers == nullptr)
			cout << "No lecturer to delete!\n";
		else
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
}

void viewLecturer(AcademicYears* acaYear)
{
	string year;
	Semesters* semes;
	if (input(acaYear, semes, year))
	{
		if (semes->lecturers == nullptr)
			cout << "No lecturer to view!";
		else
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
CourseClass* findCL(CourseClass* CL, string classID) {
	CourseClass* temp = CL;
	while (temp && temp->classID != classID)
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
//void edit

void View_Attendance_List(AcademicYears* year)
{
	string courseID,classID;
	string Year;
	AcademicYears* y = NULL;
	while (!y)
	{
		cout << "\nPlease enter Academic Year: ";
		cin >> Year;
		y = year;
		while (y)
			if (y->year == Year)break;
			else y = y->next;
		if (!y)cout << "Invalid Academic Year, please enter again." << endl;
	}
	Courses* course = NULL;
	Classes* Class = y->classes;
	Semesters* s = NULL;
	while (!s)
	{
		cout << "Please enter course ID: ";
		cin >> courseID;
		s = y->semesters;
		while (s)
		{
			course = findCourse(s->courses, courseID);
			if (!course)s = s->next;
			else break;
		}
		if (!s)cout << "Invalid course ID, please enter again." << endl;
	}

	CourseClass* CL = NULL;

	while (!CL)
	{
		cout << "Please enter class ID: ";
		cin >> classID;
		CL = findCL(course->courseclass,classID);
		if(!CL)cout << "Invalid class ID, please enter again." << endl;
	}
	Students* st = CL->students;
	int bit = CL->BitAttend;
	cout << setw(20) << "Last name" << setw(20) << "first name" << setw(20) << "student ID";
	for (int i = 0; i < 11; i++)cout << setw(10) << "Week " << i+1;
	int i = 0;
	cout << endl;
	while (st)
	{
		if ((bit >> i) % 2 == 1 && st->Status)
		{
			cout << setw(20) << st->account->lastname << setw(20) << st->account->firstname << setw(20) << st->studentID;
			CheckinCourse* ck = st->checkincourse;
			while (ck)
				if (ck->courseID == course->courseID)break;
				else ck = ck->next;
			int check = 0;
			for (int j = 0; j < 11; j++) {
				int BIT = (ck->bitweek) >> j;
				if (BIT % 2) {
					check = 1;
					cout << setw(11) << "V";
				}
				else if (check || ck->bitweek == 0)
					cout << setw(11) << "-";
				else if (!check)
					cout << setw(11) << "X";
			}
			cout << endl;
		}
		i++;
		st = st->next;
	}
	OutsideStudent* OS = CL->Outsider;
	while (OS)
	{
		Class = findClass(y->classes, OS->studentID);
		st = findStudent(Class->students, OS->studentID);
		if (st->Status)
		{
			cout << setw(20) << st->account->lastname << setw(20) << st->account->firstname << setw(1200) << st->studentID;
			CheckinCourse* ck = st->checkincourse;
			while (ck)
				if (ck->courseID == course->courseID)break;
				else ck = ck->next;
			int check = 0;
			for (int j = 0; j < 11; j++) {
				int BIT = (ck->bitweek) >> j;
				if (BIT % 2) {
					check = 1;
					cout << setw(11) << "V";
				}
				else if (check || ck->bitweek == 0)
					cout << setw(11) << "-";
				else if (!check)
					cout << setw(11) << "X";
			}
			cout << endl;
		}



		OS = OS->next;
}




}
void View_StudentList_Course(AcademicYears* year)
{
	string courseID;
	string Year;
	AcademicYears* y = NULL;
	while (!y)
	{
		cout << "\nPlease enter Academic Year: ";
		cin >> Year;
		y = year;
		while (y)
			if (y->year == Year)break;
			else y = y->next;
		if (!y)cout << "Invalid Academic Year, please enter again." << endl;
	}
	Courses* course=NULL;
	Classes* Class = y->classes;
	Semesters* s = NULL;
	while (!s)
	{
		cout << "Please enter course ID: ";
		cin >> courseID;
		s = y->semesters;
		while (s)
		{
			course = findCourse(s->courses, courseID);
			if (!course)s = s->next;
			else break;
		}
		if (!s)cout << "Invalid course ID, please enter again." << endl;
	}

	 cout << "Students List of " << courseID << endl;;
	CourseClass* CL = course->courseclass;
	cout << setw(3) << "last name" << setw(10) << "first name" << setw(10) << "student ID"<< setw(10) << "class ID"<<endl;
	while (CL )
	{
		Students* ST = CL->students;
		OutsideStudent* OS = CL->Outsider;
		int i = 0;
		while (ST != NULL)
		{
			if (ST->Status && (CL->BitAttend) % 2)
				cout << setw(3) << ST->account->lastname << setw(10) << ST->account->firstname << setw(10) << ST->studentID << setw(10) << CL->classID << endl;
			ST = ST->next;
		}
		while (OS != NULL)
		{
			Classes* tempCL = findClass(Class, OS->classID);
			Students* tempST = findStudent(tempCL->students, OS->studentID);
			if(tempST->Status && tempST->Status)
				cout << setw(3) << tempST->account->lastname << setw(10) << tempST->account->firstname << setw(10) << tempST->studentID << setw(10) << OS->classID << endl;
			OS = OS->next;
		}
		CL = CL->next;
	}

}
#pragma endregion
#pragma region course

void AddCourse(AcademicYears*& year) {
	AcademicYears* AY;
	Semesters* s = FindSemester(year,AY);
	Courses* course = s->courses;
	Classes* Class = AY->classes;
	Courses* newcourse = new Courses;
	cout << "courseID: ";
	cin >> newcourse->courseID;
	cout << "coursename: ";
	cin.ignore();
	getline(cin, newcourse->courseName);
	cout << "Room: ";
	cin >> newcourse->room;
	cout << "Lecture's name: ";
	cin.ignore();
	getline(cin, newcourse->LectureName);
	newcourse->next = course;
	course = newcourse;
	course->courseclass = NULL;

	int n;

	do {
		string classID;
		cout << "[1] Add Class.\n";
		cout << "[2] Stop.\n";
		cin >> n;
		if (n == 1)
		{
			cout << "classID :";
			cin >> classID;
			if (!findClass(Class, classID))
			{
				cout << "invalid Class ID.";
				continue;
			}
			AddClassToCourse(Class, classID, course, course->courseID);
			break;
		}
	} while (n != 2);

	newcourse->next = s->courses;
	s->courses = newcourse;
}

void AddStudentToCourseClass(AcademicYears* year) {
	string courseID, classSTID, studentID,classID;
	string Year;
	AcademicYears* y = NULL;
	while (!y)
	{
		cout << "\nPlease enter Academic Year: ";
		cin >> Year;
		y = year;
		while (y)
			if (y->year == Year)break;
			else y = y->next;
		if (!y)cout << "Invalid Academic Year, please enter again." << endl;
	}
	Courses* course = NULL;
	Classes* Class = y->classes;
	Semesters* s = NULL;
	while (!s)
	{
		cout << "Please enter course ID: ";
		cin >> courseID;
		s = y->semesters;
		while (s)
		{

			course = findCourse(s->courses, courseID);
			if (!course)s = s->next;
			else break;
		}
		if (!s)cout << "Invalid course ID, please enter again." << endl;
	}

	Classes* curCL = NULL;
	while (!curCL)
	{
		cout << "Class ID of Student: ";
		cin >> classSTID;
		curCL = findClass(Class, classSTID);
		if (!curCL)cout << "invalid class ID. Please enter agian." << endl;
		else break;
	}
	Students* curST=NULL;
	while (!curST)
	{
		cout << "student ID: ";
		cin >> studentID;
		curST = findStudent(curCL->students, studentID);
		if (!curST)cout << "invalid student ID. Please enter agian." << endl;
	}
	CourseClass* courseclass = NULL;
	while (!courseclass && course)
	{
		cout << "Class ID of course you want to add student: " << endl;
		cin >> classID;
		courseclass = findCL(course->courseclass, classID);
		if(!courseclass)cout << "invalid class ID. Please enter agian." << endl;
	}
	///
	int i = 0;
	curST = courseclass->students;
	while (curST != NULL)
		if (curST->studentID == studentID)
			if ((courseclass->BitAttend >> i) % 2)
			{
				cout << "Student's already in the course" << endl;
				return;
			}
			else {
				courseclass->BitAttend += 1 << i;
				AddCourseToStudent(curST, course, courseclass->DayInWeek, courseclass->AtNth,0);
				cout << "Added" << endl;
				break;
			}
		else
			curST = curST->next;

	///
	if (curST) return;
	OutsideStudent* Outsider = new OutsideStudent;
	Outsider->classID = classSTID;
	Outsider->studentID = studentID;
	Outsider->next = courseclass->Outsider;
	courseclass->Outsider = Outsider;
	curST = findStudent(curCL->students, studentID);
	AddCourseToStudent(curST, course, courseclass->DayInWeek, courseclass->AtNth,0);
	cout << "Added" << endl;
	return ;
}

void EditCourse(AcademicYears* year) {
	string Year;
	AcademicYears* y = NULL;
	while (!y)
	{
		cout << "\nPlease enter Academic Year: ";
		cin >> Year;
		y = year;
		while (y)
			if (y->year == Year)break;
			else y = y->next;
		if (!y)cout << "Invalid Academic Year, please enter again." << endl;
	}


	int n = 1;
	do {

		string  room, NewID, OldID, name, classID, Lname;
		cout << "Menu: " << endl;
		cout << "1.Change course ID. " << endl;
		cout << "2.change Room." << endl;
		cout << "3.Change Schedule course of a class." << endl;
		cout << "4.Change Course Lecture." << endl;
		cout << "5.Edit start date, end date of a class course." << endl;
		cout << "6.Change course name. " << endl;
		cout << " Press 0 to stop." << endl << endl;

		cin >> n;

		string courseID;
		Courses* course = NULL;
		Classes* Class = y->classes;
		Semesters* s = NULL;
		CourseClass* CL = NULL;
		if(n)while (!s)
		{
			s = y->semesters;
			cout << "Please enter course ID: ";
			cin >> courseID;
			while (s)
			{
				course = findCourse(s->courses, courseID);
				if (!course)s = s->next;
				else break;
			}
			if (!s)cout << "Invalid course ID, please enter again." << endl;
		}
		switch (n) {
		case 1:

			cout << "New course ID: ";
			cin >> NewID;
			EditCourseId(course, NewID, Class);
			break;
		case 2:

			cout << "New room: ";
			cin >> room;
			EditCourseroom(course, courseID, room);
			break;

		case 3:

			CL = NULL;
			while (!CL)
			{
				cout << "Class ID: ";
				cin >> classID;
				CL = findCL(course->courseclass, classID);
				if(!CL)cout<< "Invalid class ID, please enter again." << endl;
			}
			EditScheduleCourseOfClass(course, classID, courseID, Class);
			break;

		case 4:
			cout << "New lecture: ";
			cin >> Lname;

			EditCourseLecture(course, Lname, courseID);
			break;

		case 5:

			CL = NULL;
			while (!CL && course)
			{
				cout << "Class ID: ";
				cin >> classID;
				CL = findCL(course->courseclass, classID);
				if (!CL)cout << "Invalid class ID, please enter again." << endl;
			}
			EditDateOfCL(course, classID, courseID,y->year);
			break;

		case 6:
			cout << "New course name: ";
			cin.ignore();
			getline(cin, NewID);
			EditCourseName(course, NewID, Class);
			break;
		}

	} while (n);

}
void RemovedStudentFromCourseClass(AcademicYears* year) {
	string Year;
	Courses* course=NULL;
	string courseID, classID, studentID;
	AcademicYears* y = NULL;
	while (!y)
	{
		cout << "\nPlease enter Academic Year: ";
		cin >> Year;
		y = year;
		while (y)
			if (y->year == Year)break;
			else y = y->next;
		if (!y)cout << "Invalid Academic Year, please enter again." << endl;
	}
	Semesters* s = NULL;
	while (!s)
		{
		cout << "Please enter course ID: ";
		cin >> courseID;
			s = y->semesters;
			while (s)
			{

				course = findCourse(s->courses, courseID);
				if (!course)s = s->next;
				else break;
			}
			if (!s)cout << "Invalid course ID, please enter again." << endl;
		}

	Classes* Class = y->classes;

	CourseClass* courseclass = NULL;
	while (!courseclass && course)
	{
		cout << "Class ID of course: ";
		cin >> classID;
		courseclass = findCL(course->courseclass, classID);
		if (!courseclass)cout << "invalid class ID. Please enter agian." << endl;
		else break;
	}



	int i = 0;
	Students* students = NULL;
	OutsideStudent* OS = NULL;
	while (!students && !OS)
	{
		cout << "Student ID: ";
		cin >> studentID;
		students = findStudent(courseclass->students, studentID);
		OS = courseclass->Outsider;
		while (OS)
			if (OS->studentID == studentID)break;
			else OS->next;
		if (!students && !OS)cout << "invalid student ID. Please enter againn." << endl;
		else break;
	}
	students = courseclass->students;

	while (students)
	{
		if (students->studentID == studentID)break;
		students = students->next;
		i++;
	}
	if (students)
	{
		courseclass->BitAttend -= 1 >> i;
		DeleteCourseOfCheckin(students->checkincourse, courseID);
		RemoveCourseOfScheduleStudent(students->schedule, courseID);
		DeleteScoreBoardOfCourseStudent(students, course->courseName);
		return;
	}
	///
	OS = courseclass->Outsider;
	if (OS->classID == classID && OS->studentID == studentID)
	{
		Classes* CL = findClass(Class, OS->classID);
		if (CL)students = findStudent(CL->students, OS->studentID);
		if (students)
		{
			courseclass->BitAttend -= 1 >> i;
			DeleteCourseOfCheckin(students->checkincourse, courseID);
			RemoveCourseOfScheduleStudent(students->schedule, courseID);
			DeleteScoreBoardOfCourseStudent(students, course->courseName);
		}
		courseclass->Outsider = courseclass->Outsider->next;
		OS = NULL;

	}
	OutsideStudent* pre = OS, * tmp;

	while (OS)
	{
		if (OS->classID == classID && OS->studentID == studentID)
		{
			Classes* CL = findClass(Class, OS->classID);
			if (CL)students = findStudent(CL->students, OS->studentID);
			if (students)
			{
				courseclass->BitAttend -= 1 >> i;
				DeleteCourseOfCheckin(students->checkincourse, courseID);
				RemoveCourseOfScheduleStudent(students->schedule, courseID);
				DeleteScoreBoardOfCourseStudent(students,  course->courseName);
			}
			pre->next = OS->next;
			tmp = OS->next;
			OS = NULL;
			OS = tmp;
			continue;

		}
		pre = OS;
		OS = OS->next;
	}

	//1 inside
	//0 outsie
}

void DeleteCourse(AcademicYears* year) {

	string Year;
	AcademicYears* y = NULL;
	while (!y)
	{
		cout << "\nPlease enter Academic Year: ";
		cin >> Year;
		y = year;
		while (y)
			if (y->year == Year)break;
			else y = y->next;
		if (!y)cout << "Invalid Academic Year, please enter again." << endl;
	}

	string courseID;
	Courses* course;
	Classes* Class = y->classes;
	Semesters* s = NULL;
	while (!s)
	{
		cout << "Please enter course ID: ";
		cin >> courseID;
		s = y->semesters;
		while (s)
		{

			course = findCourse(s->courses, courseID);
			if (!course)s = s->next;
			else break;
		}
		if (!s)cout << "Invalid course ID, please enter again." << endl;
	}
	course = s->courses;
	Courses* cur = course;
	Courses* tmp = new Courses;
	Courses* pre = new Courses;

	if (cur->courseID == courseID) {
		CourseClass* courseclass = cur->courseclass;

		while (courseclass) {
			DeleteCourseScheduleStudent(courseclass->students, cur, courseclass->Outsider, Class);
			DeleteCourseScheduleClass(Class, courseID, courseclass->classID);
			courseclass = courseclass->next;
		}

		cur = cur->next;
		course = NULL;
		course = cur;
		cout << "Removed."<<endl;
		return;
	}
	while (cur != NULL) {
		if (cur->courseID == courseID) {

			CourseClass* courseclass = cur->courseclass;

			while (courseclass != NULL) {
				DeleteCourseScheduleStudent(courseclass->students, cur, courseclass->Outsider, Class);
				DeleteCourseScheduleClass(Class, courseID, courseclass->classID);
				courseclass = courseclass->next;
			}

			pre->next = cur->next;
			Courses* tmp = cur->next;
			cur = NULL;
			cur = tmp;
			cout << "Removed." << endl;
			return;
		}
		pre = cur;
		cur = cur->next;
	}
	return;

}

#pragma endregion
