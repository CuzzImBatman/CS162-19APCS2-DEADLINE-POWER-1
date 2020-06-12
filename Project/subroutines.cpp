#include "function.h"

#pragma region Tools
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
AcademicYears* findYear(AcademicYears* acaYear, string year) {
	AcademicYears* temp = acaYear;
	while (temp && temp->year != year)
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
bool smaller(int a, int b)
{
	if (a > b)return false;
	return true;
}
bool bigger(int a, int b)
{
	if (a > b)return true;
	return false;
}
bool checkDay(string& a, int x, bool(*compare)(int, int))
{
	int j = 1, sum = 0;
	for (int i = a.length() - 1; i >= 0; i--)
	{
		sum += (a[i] - 48) * j;
		j *= 10;
	}
	if (compare(sum, x) || j == 0)return  false;
	else
		while (a[0] == '0' && a.length() > 2)a.erase(0, 1);


	return true;
}
bool checkMonth(Date a)
{
	int j = 1, day = 0, month = 0;
	for (int i = a.day.length() - 1; i >= 0; i--)
	{
		day += (a.day[i] - 48) * j;
		j *= 10;
	}
	j = 1;
	for (int i = a.month.length() - 1; i >= 0; i--)
	{
		month += (a.month[i] - 48) * j;
		j *= 10;
	}
	if (day == 31)
		if (month == 2 || month == 4 || month == 6 || month == 9 || month == 11)return false;
	if (day == 30)
		if (month == 2)return false;
	return true;
}
bool checkYear(Date a)
{
	int j = 1, day = 0, month = 0, year = 0;
	for (int i = a.day.length() - 1; i >= 0; i--)
	{
		day += (a.day[i] - 48) * j;
		j *= 10;
	}
	j = 1;
	for (int i = a.month.length() - 1; i >= 0; i--)
	{
		month += (a.month[i] - 48) * j;
		j *= 10;
	}
	j = 1;
	for (int i = a.year.length() - 1; i >= 0; i--)
	{
		year += (a.year[i] - 48) * j;
		j *= 10;
	}
	if (year % 100 == 0)year /= 100;
	if (day == 29 && month == 2)
		if (year % 4)return false;




	return true;

}
int numberOfDay(Date x) {
	int j = 1, day = 0, month = 0, year = 0;
	for (int i = x.day.length() - 1; i >= 0; i--)
	{
		day += (x.day[i] - 48) * j;
		j *= 10;
	}
	j = 1;
	for (int i = x.month.length() - 1; i >= 0; i--)
	{
		month += (x.month[i] - 48) * j;
		j *= 10;
	}
	j = 1;
	for (int i = x.year.length() - 1; i >= 0; i--)
	{
		year += (x.year[i] - 48) * j;
		j *= 10;
	}
	if (month < 3) {
		year--;
		month += 12;
	}

	return 365 * year + year / 4 - year / 100 + year / 400 + (153 * month - 457) / 5 + day - 307;
}
bool input(AcademicYears* AcaYear, Semesters*& semes, string& year)
{
	cout << "\nPlease enter Academic Year: ";
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
AcademicYears* inputYear(AcademicYears* year, Courses*& course)
{

	string courseID, classID;
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
	return y;
}
int DeleteABit(int bit, int x)
{
	int newBIt = 0;
	int i = 0;
	while (bit)
	{
		if (x != i)
		{
			newBIt += ((bit) % 2) << i;
			i++;
		}
		else x = -1;
		bit = bit >> 1;
	}
	return newBIt;
}
bool Is_empty(ifstream& in)
{
	return in.peek() == ifstream::traits_type::eof();
}
#pragma endregion
#pragma region Subroutines
#pragma region importAClassFromCsvFile
Students* listStudentsFromFile(string path)
{
	Students* studentList = nullptr;
	Students* tmp = nullptr;
	ifstream in(path);
	bool firstRead = true;
	if (in.is_open())
	{
		string pwd;
		string dob;
		string gender;
		string no;
		while (true)
		{
			if (firstRead)
			{
				//  Read first line
				string tmp;
				firstRead = false;
				getline(in, tmp, '\n');
			}
			else
			{
				getline(in, no, ',');
				if (in.eof())
					break;
				if (!studentList)
				{
					studentList = new Students;
					studentList->account = new Accounts;
					studentList->account->doB = new Date;
					studentList->account->role = 1;
					getline(in, studentList->account->uName, ',');
					studentList->studentID = studentList->account->uName;
					getline(in, studentList->account->lastname, ',');
					getline(in, studentList->account->firstname, ',');
					getline(in, gender, ',');
					studentList->account->gender = gender[0];
					getline(in, dob, '\n');
					studentList->account->doB->day = dob.substr(8, 2);
					studentList->account->doB->month = dob.substr(5, 2);
					studentList->account->doB->year = dob.substr(0, 4);
					tmp = studentList;
					pwd = studentList->account->doB->day
						+ studentList->account->doB->month
						+ studentList->account->uName;
					sha256_init(&(studentList->account->pwd));
					sha256_update(&(studentList->account->pwd), pwd, pwd.length());
				}
				else
				{
					tmp->next = new Students;
					tmp = tmp->next;
					tmp->account = new Accounts;
					tmp->account->doB = new Date;
					tmp->account->role = 1;
					getline(in, tmp->account->uName, ',');
					tmp->studentID = tmp->account->uName;
					getline(in, tmp->account->lastname, ',');
					getline(in, tmp->account->firstname, ',');
					getline(in, gender, ',');
					tmp->account->gender = gender[0];
					getline(in, dob, '\n');
					tmp->account->doB->day = dob.substr(8, 2);
					tmp->account->doB->month = dob.substr(5, 2);
					tmp->account->doB->year = dob.substr(0, 4);
					pwd = tmp->account->doB->day
						+ tmp->account->doB->month
						+ tmp->account->uName;
					sha256_init(&(tmp->account->pwd));
					sha256_update(&(tmp->account->pwd), pwd, pwd.length());
				}
			}
		}
	}
	in.close();
	return studentList;
}
#pragma endregion
#pragma region removeAStudent
void DeleteScoreBoardStudent(Students*& ST)
{
	while (ST->scoreboards)
	{
		Scoreboards* SB = ST->scoreboards;
		ST->scoreboards = SB->next;
		delete SB;
		SB = NULL;
	}
}
void DeleteCheckinCourseStudent(Students*& St)
{
	while (St->checkincourse)
	{
		CheckinCourse* CK = St->checkincourse;
		St->checkincourse = CK->next;
		delete CK;
		CK = NULL;

	}
}
void DeleteStudentFromCourses(string studentID, string classID, Courses*& course)
{
	Courses* cs = course;
	CourseClass* CL;
	while (cs)
	{
		CL = cs->courseclass;
		StudentCourse* OS = CL->studentcourse;
		StudentCourse* tmp = OS;
		if (OS && OS->studentID == studentID)
		{
			OS = OS->next;
			delete tmp;
			tmp = NULL;
			break;

		}
		while (OS)
		{
			if (OS->studentID == studentID)
			{
				StudentCourse* del = OS;
				tmp->next = OS->next;
				OS = OS->next;
				delete del;
				del = NULL;
				break;
			}

			tmp = OS;
			OS = OS->next;

		}
		cs = cs->next;
	}
}
#pragma endregion
#pragma region changeClassForStudents
void FillCheckinCourse(Students*& student) {
	for (int i = 0; i <= 5; i++)
		for (int j = 0; j <= 3; j++)
			if (student->schedule[i][j] != "//") {
				CheckinCourse* newcourse = new CheckinCourse;
				newcourse->courseID = student->schedule[i][j];
				newcourse->bitweek = 0;
				//              newcourse->status=1;
				newcourse->next = student->checkincourse;
				student->checkincourse = newcourse;
			}

}
#pragma endregion
#pragma region deleteAcademicYear
void RemoveFile(string s)
{
	char* c = const_cast<char*>(s.c_str());
	remove(c);
}
void staff_deleteClasses(Classes*& Class, string year) {
	Classes* tempClass = Class;
	while (tempClass) {
		string fileName = "Year" + year + "_Class" + tempClass->classID + "_StudentDB.txt";
		RemoveFile("./DATABASE/" + fileName);
		deleteStudents(tempClass->students);
		Classes* newTemp = tempClass;
		tempClass = tempClass->next;
		delete newTemp;
	}
}
#pragma endregion
#pragma region AddCourse
Semesters* FindSemester(AcademicYears*& AY, AcademicYears*& ay)
{
	string year;
	AcademicYears* y = NULL;
	while (!y)
	{
		cout << "\nPlease enter Academic Year: ";
		cin >> year;
		y = AY;
		while (y)
			if (y->year == year)break;
			else y = y->next;
		if (!y)cout << "Invalid Academic Year, please enter again." << endl;
	}
	ay = y;
	Semesters* s = NULL;
	char sems;
	while (!s)
	{
		cout << "\nPlease enter semester: ";
		cin >> sems;
		s = y->semesters;
		while (s)
			if (sems - s->semesterNo == 0)break;
			else s = s->next;
		if (!s)cout << "Invalid semester, please enter again." << endl;
	}
	return s;

}
void AddScoreBoardCourse(Students*& st, string courseID, string courseName)
{
	Scoreboards* newcourse = new Scoreboards;
	newcourse->courseName = courseName;
	newcourse->courseID = courseID;
	newcourse->next = st->scoreboards;
	st->scoreboards = newcourse;
}
void AddCheckInCourse(Students * &st, string courseID, string room, string starTime, string endTime, Date startDate, Date endDate)
{
	CheckinCourse* newcourse = new CheckinCourse;
	newcourse->room = room;
	newcourse->courseID = courseID;
	newcourse->bitweek = 0;
	newcourse->startTime = starTime;
	newcourse->endTime = endTime;
	newcourse->startDate = startDate;
	newcourse->endDate = endDate;
	newcourse->next = st->checkincourse;
	st->checkincourse = newcourse;

}
void AddCourseToStudent(Students*& ST, Courses*& course, CourseClass*& CL, string year) {

	ST->schedule[CL->DayInWeek][CL->AtNth] = course->courseID;
	ifstream CKinit;
	string init = "Year" + year + "_StudentID" + ST->studentID + "_CheckIn.txt";
	CKinit.open("./DATABASE/" + init);
	if (!CKinit.is_open())
		AddCheckInCourse(ST, course->courseID, course->room, CL->startTime, CL->endTime, CL->startDate, CL->endDate);
	else
	{
		int n;
		CKinit >> n;
		if (!n)
			AddCheckInCourse(ST, course->courseID, course->room, CL->startTime, CL->endTime, CL->startDate, CL->endDate);
		else
		{
			CheckinCourse* test = ST->checkincourse;
			while (test)
				if (test->courseID == course->courseID)break;
				else test = test->next;
			if (test == NULL && ST->checkincourse == NULL)
			{
				for (int i = 0; i < n; i++)
				{
					CheckinCourse* newcourse = new CheckinCourse;
					CKinit >> newcourse->room;
					CKinit >> newcourse->startTime;
					CKinit >> newcourse->endTime;
					CKinit >> newcourse->startDate.day;
					CKinit >> newcourse->startDate.month;
					CKinit >> newcourse->startDate.year;
					CKinit >> newcourse->endDate.day;
					CKinit >> newcourse->endDate.month;
					CKinit >> newcourse->endDate.year;
					CKinit >> newcourse->courseID;
					CKinit >> newcourse->bitweek;
					newcourse->next = ST->checkincourse;
					ST->checkincourse = newcourse;
				}
			}
			if (test && !ST->checkincourse)
				AddCheckInCourse(ST, course->courseID, course->room, CL->startTime, CL->endTime, CL->startDate, CL->endDate);
		}
	}
	string in = "Year" + year + "_StudentID" + ST->studentID + "_ScoreBoard.csv";
	ifstream SBinit;
	SBinit.open("./DATABASE/" + in);
	if (!SBinit.is_open())//initial definitely
		AddScoreBoardCourse(ST, course->courseID, course->courseName);
	else
	{
		if (Is_empty(SBinit))
			AddScoreBoardCourse(ST, course->courseID, course->courseName);
		else
		{
			Scoreboards* test = ST->scoreboards;
			while (test)
				if (test->courseID == course->courseID)break;
				else test = test->next;
			if (test == NULL && ST->scoreboards == NULL)
			{
				while (!SBinit.eof())
				{
					Scoreboards* SB = new Scoreboards;
					getline(SBinit, SB->courseName, ',');
					getline(SBinit, SB->courseID, ',');
					getline(SBinit, SB->labScore, ',');
					getline(SBinit, SB->midtermScore, ',');
					getline(SBinit, SB->finalScore, ',');
					getline(SBinit, SB->bonusScore, '\n');

					SB->next = ST->scoreboards;
					ST->scoreboards = SB;
					if (Is_empty(SBinit))break;
				}
			}
			else if (!test && ST->scoreboards)
				AddScoreBoardCourse(ST, course->courseID, course->courseName);
		}
	}
}
void AddCourseToClass(Classes*& Class, Courses*& course, CourseClass*& CL, string year) {


	Students* curST = Class->students;
	while (curST != NULL)
	{
		AddCourseToStudent(curST, course, CL, year);
		curST = curST->next;
	}


}
void AddClassToCourse(Classes*& Class, string classID, Courses*& course, string courseID, string year) {

	Courses* curCS = findCourse(course, courseID);


	CourseClass* courseclass = new CourseClass;
	courseclass->classID = classID;

	cout << "Start Day: ";
	cin >> courseclass->startDate.day;
	cin >> courseclass->startDate.month;
	cin >> courseclass->startDate.year;
	cout << "End Day: ";
	cin >> courseclass->endDate.day;
	cin >> courseclass->endDate.month;
	cin >> courseclass->endDate.year;
	cout << "Day in week (Monday/Tuesday/...): ";
	string temp;
	cin >> temp;
	switch (temp[1]) { //Mo Tu We Th Fr Sa
	case 'o':
		courseclass->DayInWeek = 0;
		break;
	case 'u':
		courseclass->DayInWeek = 1;
		break;
	case 'e':
		courseclass->DayInWeek = 2;
		break;
	case 'h':
		courseclass->DayInWeek = 3;
		break;
	case 'r':
		courseclass->DayInWeek = 4;
		break;
	case 'a':
		courseclass->DayInWeek = 5;
		break;
	}
	cin >> courseclass->startTime;
	cin >> courseclass->endTime;
	int hour = courseclass->startTime[0] * 10 + courseclass->startTime[1] - 48 * 11;
	switch (hour) {
	case 7:
		courseclass->AtNth = 0;
		break;
	case 9:
		courseclass->AtNth = 1;
		break;
	case 13:
		courseclass->AtNth = 2;
		break;
	case 15:
		courseclass->AtNth = 3;
		break;
	}
	int DayInWeek = courseclass->DayInWeek, AtNth = courseclass->AtNth;
	//int week= 3;/// just EX

	Classes* curCL = findClass(Class, classID);

	curCL->schedule[DayInWeek][AtNth] = courseID;
	CourseDetail* CD = new CourseDetail;
	CD->courseID = course->courseID;
	CD->coursename = course->courseName;
	CD->room = course->room;
	CD->next = curCL->CD;
	curCL->CD = CD;
	Students* curST = curCL->students;
	courseclass->studentcourse = NULL;
	while (curST)
	{
		StudentCourse* st = new StudentCourse;
		st->studentID = curST->studentID;
		st->classID = classID;
		st->next = courseclass->studentcourse;
		courseclass->studentcourse = st;
		curST = curST->next;
	}


	AddCourseToClass(curCL, curCS, courseclass, year);

	courseclass->next = curCS->courseclass;
	curCS->courseclass = courseclass;

}
#pragma endregion
#pragma region EditCourse
void Edit_CourseName_Student(Students* st, string NewName, string OldName)
{

	Scoreboards* sb = st->scoreboards;
	while (sb)
	{
		if (sb->courseName == OldName)
		{
			sb->courseName = NewName;
			break;
		}
		else sb = sb->next;
	}
}
void EditCourseName(Courses*& course, string NewName, Classes*& Class) {
	CourseClass* cur = course->courseclass;
	Classes* cl;
	while (cur)
	{
		StudentCourse* OS = cur->studentcourse;
		while (OS)
		{
			cl = findClass(Class, OS->classID);
			if (cl && findStudent(cl->students, OS->studentID))
			{
				Students* st = findStudent(cl->students, OS->studentID);
				Edit_CourseName_Student(st, NewName, course->courseName);
				OS = OS->next;
			}
		}
		cur = cur->next;
	}
	course->courseName = NewName;
}

void EditDateOfCL(Courses*& course, string classID, string courseID, string year)
{
	Courses* curCS = findCourse(course, courseID);
	CourseClass* curCL = findCL(curCS->courseclass, classID);
	int YEAR = 0, j = 1;
	for (int i = year.length() - 1; i >= 0; i--)
	{
		YEAR += (year[i] - 48) * j;
		j *= 10;
	}
	cout << "Start date: " << endl;

	do
	{
		cout << "Day : ";
		cin >> curCL->startDate.day;
		if (!checkDay(curCL->startDate.day, 31, bigger))cout << "Invalid day, please enter again. " << endl;
	} while (!checkDay(curCL->startDate.day, 31, bigger));
	do
	{
		cout << "month: ";
		cin >> curCL->startDate.month;
		if (!checkDay(curCL->startDate.month, 12, bigger)) {
			cout << "Invalid month, please enter again. " << endl;
			continue;
		}
		if (!checkMonth(curCL->startDate))cout << "Invalid month, please enter again. " << endl;
	} while (!checkDay(curCL->startDate.month, 12, bigger) || !checkMonth(curCL->startDate));

	do
	{
		cout << "year: ";
		cin >> curCL->startDate.year;
		if (!checkDay(curCL->startDate.year, YEAR, smaller))
		{
			cout << "Invalid year, please enter again. " << endl;
			continue;
		}
		if (!checkYear(curCL->startDate))cout << "Invalid year, please enter again. " << endl;
	} while (!checkDay(curCL->startDate.year, YEAR, smaller) || !checkYear(curCL->startDate));
	cout << "End date: " << endl;
	do
	{
		cout << "Day : ";
		cin >> curCL->endDate.day;
		if (!checkDay(curCL->endDate.day, 31, bigger))cout << "Invalid day, please enter again. " << endl;
	} while (!checkDay(curCL->endDate.day, 31, bigger));
	do
	{
		cout << "month: ";
		cin >> curCL->endDate.month;
		if (!checkDay(curCL->endDate.month, 12, bigger)) {
			cout << "Invalid month, please enter again. " << endl;
			continue;
		}
		if (!checkMonth(curCL->endDate))cout << "Invalid month, please enter again. " << endl;
	} while (!checkDay(curCL->endDate.month, 12, bigger) || !checkMonth(curCL->endDate));

	do
	{
		cout << "year: ";
		cin >> curCL->endDate.year;
		if (numberOfDay(curCL->endDate) - numberOfDay(curCL->startDate) <= 0)
		{
			cout << "Invalid year, please enter again. " << endl;
			continue;
		}
		if (!checkYear(curCL->endDate))cout << "Invalid year, please enter again. " << endl;
	} while ((numberOfDay(curCL->endDate) - numberOfDay(curCL->startDate) <= 0) || !checkYear(curCL->endDate));

}

void EditCourseLecture(Courses*& course, string name, string courseID) {
	Courses* cur = course;
	while (cur->courseID != courseID)
		cur->next;
	cur->LectureName = name;

}

int CheckStatusStudent(string studentID, string classID, Classes*& Class) {
	Classes* curCL = Class;
	while (curCL != NULL)
		if (curCL->classID == classID) {
			Students* curST = curCL->students;
			while (curST != NULL)
				if (curST->studentID == studentID)
					return curST->Status;
		}
		else
			curCL = curCL->next;
	return -2;
}
void EditScheduleCourseOfClass(Courses*& course, string classID, string courseID, Classes*& Class) {
	Classes* curCL = findClass(Class, classID);

	Courses* curCourse = findCourse(course, courseID);

	CourseClass* courseclass = curCourse->courseclass;
	while (courseclass->classID != classID)
		courseclass = courseclass->next;

	string temp;
	cout << "Day in week";
	cin >> temp;
	switch (temp[1]) { //Mo Tu We Th Fr Sa
	case 'o':
		courseclass->DayInWeek = 0;
		break;
	case 'u':
		courseclass->DayInWeek = 1;
		break;
	case 'e':
		courseclass->DayInWeek = 2;
		break;
	case 'h':
		courseclass->DayInWeek = 3;
		break;
	case 'r':
		courseclass->DayInWeek = 4;
		break;
	case 'a':
		courseclass->DayInWeek = 5;
		break;
	}
	int hour, minute;
	cout << "Time: ";
	cin >> hour >> minute;
	switch (hour) {
	case 7:
		courseclass->AtNth = 0;
		break;
	case 9:
		courseclass->AtNth = 1;
		break;
	case 13:
		courseclass->AtNth = 2;
		break;
	case 15:
		courseclass->AtNth = 3;
		break;
	}
	int i, j;
	for (i = 0; i < 6; i++)
		for (j = 0; j < 4; j++)
			if (curCL->schedule[i][j] == courseID) {
				curCL->schedule[i][j] == "//";
				break;
			}
	curCL->schedule[courseclass->DayInWeek][courseclass->AtNth] = courseID;

	Students* curST = NULL;

	/// change schedule chechou
	StudentCourse* st = courseclass->studentcourse;

	while (st != NULL) {
		int k = CheckStatusStudent(st->studentID, st->classID, Class);

		curCL = findClass(Class, classID);

		if (curCL && findStudent(curCL->students, st->studentID))
		{
			curST = findStudent(curCL->students, st->studentID);
			curST->schedule[i][j] = "//";
			curST->schedule[courseclass->DayInWeek][courseclass->AtNth] = courseID;

		}
	}
	st = st->next;

}

void EditCourseroom(Courses*& course, string courseID, string room, Classes*& Class) {

	course->room = room;
	CourseClass* CL = course->courseclass;
	while (CL)
	{
		StudentCourse* OS = CL->studentcourse;
		Classes* cl = findClass(Class, OS->classID);
		if (cl && findStudent(cl->students, OS->studentID))
		{
			Students* st = findStudent(cl->students, OS->studentID);
			CheckinCourse* ck = st->checkincourse;
			while (ck)
				if (ck->courseID == courseID) {
					ck->room = course->room; break;
				}
				else ck = ck->next;
		}
		CL = CL->next;
	}
}

void Edit_CourseID_Student(Students* st, string NewID, string OldID)
{
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 4; j++)
			if (st->schedule[i][j] == OldID)st->schedule[i][j] = NewID;
	CheckinCourse* ck = st->checkincourse;
	while (ck)
		if (ck->courseID == OldID)
		{
			ck->courseID = NewID;
			break;
		}
		else ck = ck->next;
	Scoreboards* sb = st->scoreboards;
	while (sb)
	{
		if (sb->courseID == OldID)
		{
			sb->courseID = NewID;
			break;
		}
		else sb = sb->next;
	}

}
void Edit_CourseID_Class(Classes*& Class, string NewID, string OldID)
{

	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 4; j++)
			if (Class->schedule[i][j] == OldID)Class->schedule[i][j] = NewID;

}
void EditCourseId(Courses*& course, string NewID, Classes*& Class) {
	CourseClass* cur = course->courseclass;
	while (cur)
	{
		Classes* cl = findClass(Class, cur->classID);
		if (cl)Edit_CourseID_Class(cl, NewID, course->courseID);
		StudentCourse* OS = cur->studentcourse;
		while (OS)
		{
			cl = findClass(Class, OS->classID);
			if (cl)
			{
				Students* st = findStudent(cl->students, OS->studentID);
				if (st)Edit_CourseID_Student(st, NewID, course->courseID);
				OS = OS->next;
			}
		}
		cur = cur->next;
	}
	course->courseID = NewID;
}
#pragma endregion
#pragma region DeleteCourse
void DeleteCourseScheduleClass(Classes*& Class, string courseID, string classID) {
	Classes* curCL = Class;
	while (curCL != NULL) {
		if (curCL->classID == classID) {
			for (int i = 1; i <= 6; i++)
				for (int j = 1; j <= 4; j++)
					if (curCL->schedule[i][j] == courseID)
						curCL->schedule[i][j] = "//";

			return;
		}
		curCL = curCL->next;
	}

}

void DeleteScoreBoardOfCourse(Students*& ST, string courseName)
{
	Students* st = ST;
	while (st)
	{
		DeleteScoreBoardOfCourseStudent(st, courseName);
		st = st->next;
	}

}
void DeleteCourseOfCheckin(CheckinCourse*& checkincourse, string courseID) {
	if (checkincourse->courseID == courseID) {
		CheckinCourse* tmp = checkincourse;
		checkincourse = checkincourse->next;
		tmp = NULL;
	}
	return;
	CheckinCourse* tmp;
	CheckinCourse* cur = checkincourse;
	while (cur != NULL) {
		if (cur->courseID == courseID) {
			tmp->next = cur->next;
			CheckinCourse* del = cur;
			cur = cur->next;
			del = NULL;
		}
		tmp = cur;
		cur = cur->next;
	}
}
void RemoveCourseOfScheduleStudent(string schedule[6][4], string courseID) {
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 4; j++)
			if (schedule[i][j] == courseID)
				schedule[i][j] = "//";
}
void DeleteCourseScheduleStudent(Courses*& course, StudentCourse*& Outsider, Classes*& Class) {

	Classes* curCL = Class;
	StudentCourse* st = Outsider;
	while (st != NULL) {

		Classes* curCL = findClass(Class, st->classID);
		if (curCL && findStudent(curCL->students, st->studentID))
		{
			Students* curST = findStudent(curCL->students, st->studentID);;
			RemoveCourseOfScheduleStudent(curST->schedule, course->courseID);
			DeleteCourseOfCheckin(curST->checkincourse, course->courseID);
			DeleteScoreBoardOfCourse(curST, course->courseName);
		}
	}
}
#pragma endregion
#pragma region RemovedStudentFromCourseClass
void DeleteScoreBoardOfCourseStudent(Students*& ST, string courseName)
{
	Scoreboards* SB = ST->scoreboards, * pre = SB;
	if (SB->courseName == courseName)
	{
		Scoreboards* tmp = ST->scoreboards->next;
		ST->scoreboards = NULL;
		ST->scoreboards = tmp;
		return;
	}
	while (!SB)
	{
		if (SB->courseName == courseName)
		{
			pre->next = SB->next;
			Scoreboards* tmp = SB->next;
			SB = NULL;
			SB = tmp;

		}
		pre = SB;
		SB = SB->next;

	}

}
#pragma endregion
#pragma region View_Scoreboard
void View_Scoreboard_Student(Students* st, string courseID)
{
	Scoreboards* SB = st->scoreboards;
	while (SB)
		if (SB->courseID == courseID)break;
		else SB = SB->next;
	cout << setw(20) << st->account->lastname << setw(20) << st->account->firstname << setw(20) << st->studentID;
	cout << setw(16) << SB->midtermScore;
	cout << setw(16) << SB->finalScore;
	cout << setw(16) << SB->labScore;
	cout << setw(16) << SB->bonusScore << endl;

}
#pragma endregion
#pragma region Export_Scoreboard
void Export_Scoreboard_Student(Students* st, string courseID, ofstream& out)
{

	Scoreboards* SB = st->scoreboards;
	while (SB)
		if (SB->courseID == courseID)break;
		else SB = SB->next;
	out << st->account->lastname << "," << st->account->firstname << "," << st->studentID;
	out << "," << SB->midtermScore;
	out << "," << SB->finalScore;
	out << "," << SB->labScore;
	out << "," << SB->bonusScore << endl;


}
#pragma endregion
#pragma endregion
