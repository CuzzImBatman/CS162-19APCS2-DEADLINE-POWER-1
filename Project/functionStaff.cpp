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
	aStudent->checkincourse = NULL;
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 4; j++)
		{
			aStudent->schedule[i][j] = tmpClass->schedule[i][j];
			if (tmpClass->schedule[i][j] != "//")
			{
				CheckinCourse* newcourse = new CheckinCourse;
				newcourse->courseID = tmpClass->schedule[i][j];
				newcourse->bitweek = 0;
				newcourse->next = aStudent->checkincourse;
				aStudent->checkincourse = newcourse;
			}
		}
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
	tmpSt->Status = -2;
	cout << "The student is successfully removed." << endl;
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



void changeClassForStudents(Classes*& classes, Courses*& course) {
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
	tmpSt->Status = -1;
	Students* AddSt = new Students;
	AddSt->account = tmpSt->account;
	AddSt->checkincourse = tmpSt->checkincourse;
	for (int i = 0; i < 6; i++)
	for (int j = 0; j < 4; j++)
	    AddSt->schedule[i][j] = tmpSt->schedule[i][j];
	AddSt->scoreboards = tmpSt->scoreboards;
	AddSt->studentID = tmpSt->studentID;
	AddSt->Status = 1;
	FillCheckinCourse(AddSt);
	AddSt->next = tmpClassB->students;
	tmpClassB->students = AddSt;
	UpdateBitAttend(tmpClassB->classID, course);
	cout << "Changed.";
	
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

void View_Attendance_List(Courses* course, Classes* Class)
{
	string CourseID;
	Courses* curCS = NULL;
	while (!curCS)
	{
		cout << "Course ID: ";
		cin >> CourseID;
		curCS = findCourse(course, CourseID);
		if (!curCS)cout << "invalid course ID. Please enter agian." << endl;
		else break;
	}
	curCS = findCourse(course, CourseID);
	cout << "Attendace List of " << CourseID << endl;
	CourseClass* CL = curCS->courseclass;
	while (CL)
		cout << setw(3) << CL->classID << endl;
	//not done yet;

}
void View_StudentList_Course(Courses* course, Classes* Class)
{
	string CourseID;
	Courses* curCS = NULL;
	while (!curCS)
	{
		cout << "Course ID: ";
		cin >> CourseID;
		curCS = findCourse(course, CourseID);
		if (!curCS)cout << "invalid course ID. Please enter agian." << endl;
		else break;
	}
	 curCS = findCourse(course, CourseID);
	 cout << "Students List of " << CourseID << endl;;
	CourseClass* CL = curCS->courseclass;
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

void AddCourse(Courses*& course, Classes* Class) {
	Courses* newcourse = new Courses;
	cout << "courseID: ";
	cin >> newcourse->courseID;

	cout << "Room: ";
	cin >> newcourse->room;
	cout << "Lecture's name: ";
	cin >> newcourse->LectureName;
	newcourse->next = course;
	course = newcourse;
	course->courseclass = NULL;

	int n;

	do {
		string classID;
		cout << "1.Add Class.";
		cout << "2.Stop.";
		cin >> n;
		if (n == 1)
		{
			cout << "classID :";
			if (!findClass(Class, classID))
			{
				cout << "invalid Class ID.";
				continue;
			}
			cin >> classID;
			AddClassToCourse(Class, classID, course, course->courseID);
			break;
		}
	} while (n != 2);
}

void AddStudentToCourseClass(Courses*& course, Classes*& Class) {
	string courseID, classSTID, studentID,classID;

	Courses* curCourse = NULL;
	while (!curCourse)
	{
		cout << "Course ID: ";
		cin >> courseID;
		curCourse = findCourse(course, courseID);
		if (!curCourse)cout << "invalid course ID. Please enter agian." << endl;
		else break;
	}
	Classes* curCL = NULL;
	while (!curCL)
	{
		cout << "Class ID of Student: ";
		cin >> classSTID;
		curCL = findClass(curCL, classSTID);
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
	while (!courseclass)
	{
		cout << "Class ID of course you want to add student: " << endl;
		cin >> classID;
		CourseClass* courseclass = NULL;
		courseclass = findCL(curCourse->courseclass, classID);
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
				AddCourseToStudent(curST, courseID, courseclass->DayInWeek, courseclass->AtNth);
				cout << "Added" << endl;
				break;
			}
		else
			curST = curST->next;

	///
	if (!curST) return;
	OutsideStudent* Outsider = new OutsideStudent;
	Outsider->classID = classID;
	Outsider->studentID = studentID;
	Outsider->next = courseclass->Outsider;
	courseclass->Outsider = Outsider;
	curST = findStudent(curCL->students, studentID);
	AddCourseToStudent(curST, courseID, courseclass->DayInWeek, courseclass->AtNth);
	cout << "Added" << endl;
	return ;
}

void EditCourse(Courses*& course, Classes*& Class) {
	int n = 1;
	do {

		string courseID, room, NewID, OldID, name, classID, Lname;
		cout << "Menu: " << endl;
		cout << "1.Change course ID. " << endl;;
		cout << "2.change Room." << endl;
		cout << "3.Change Schedule course of a class." << endl;
		cout << "4.Change Course Lecture." << endl;
		cout << "5.Edit start date, end date of a class course." << endl;
		cout << " Press 0 to stop.";

		cin >> n;
		switch (n) {
		case 1:
			cout << "Course ID: ";
			cin >> OldID;
			cout << "New course ID: ";
			cin >> NewID;
			EditCourseId(course, NewID, OldID);
			break;
		case 2:
			cout << "Course ID: ";
			cin >> courseID;
			cout << "New room: ";
			cin >> room;
			EditCourseroom(course, courseID, room);
			break;

		case 3:
			cout << "Class ID: ";
			cin >> classID;
			cout << "Course ID: ";
			cin >> courseID;
			EditScheduleCourseOfClass(course, classID, courseID, Class);
			break;

		case 4:
			cout << "New lecture: ";
			cin >> Lname;
			cout << "Course ID: ";
			cin >> courseID;
			EditCourseLecture(course, Lname, courseID);
			break;

		case 5:
			cout << "Course ID: ";
			cin >> courseID;
			cout << "Class ID: ";
			cin >> classID;
			EditDateOfCL(course, classID, courseID);


		}

	} while (n);

}
void RemovedStudentFromCourseClass(Courses*& course, Classes*& Class) {

	string courseID, classID, studentID;
	

	Courses* curCourse = NULL;
	while (!curCourse)
	{
		cout << "Course ID: ";
		cin >> courseID;
		curCourse = findCourse(course, courseID);
		if (!curCourse)cout << "invalid course ID. Please enter agian." << endl;
		else break;
	}

	CourseClass* courseclass = NULL;
	while (!courseclass)
	{
		cout << "Class ID of course: ";
		cin >> classID;
		courseclass = findCL(curCourse->courseclass, classID);
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
		DeleteScoreBoardOfCourseStudent(students, courseID);
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
			DeleteScoreBoardOfCourseStudent(students, courseID);
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
				DeleteScoreBoardOfCourseStudent(students, courseID);
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

void DeleteCourse(Courses*& course, Classes*& Class) {
	
	string courseID;
	
	Courses* cur = NULL;
	Courses* tmp = new Courses;
	Courses* pre = new Courses;

	while (!cur)
	{
		cout << "course ID: "; 
		cin >> courseID;
		cur = findCourse(course, courseID);
		if (!cur)cout << "invalid course ID. Please enter agian." << endl;
		else break;
	}
	cur = course;
	if (cur->courseID == courseID) {
		CourseClass* courseclass = cur->courseclass;

		while (courseclass) {
			DeleteCourseScheduleStudent(courseclass->students, courseID, courseclass->Outsider, Class);
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
				DeleteCourseScheduleStudent(courseclass->students, courseID, courseclass->Outsider, Class);
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