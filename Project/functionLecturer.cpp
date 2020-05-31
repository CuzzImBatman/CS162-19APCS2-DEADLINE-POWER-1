#include"function.h"

void viewCourseOfASemester(AcademicYears* acaYear)
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
void ViewStudentListOfACourse(AcademicYears* year)
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

	cout << "Students List of " << courseID << endl;;
	CourseClass* CL = course->courseclass;
	cout << setw(3) << "last name" << setw(10) << "first name" << setw(10) << "student ID" << setw(10) << "class ID" << endl;
	while (CL)
	{

		StudentCourse* OS = CL->studentcourse;
		while (OS != NULL)
		{
			Classes* tempCL = findClass(Class, OS->classID);
			Students* tempST = findStudent(tempCL->students, OS->studentID);
			if (tempST->Status && tempST->Status)
				cout << setw(3) << tempST->account->lastname << setw(10) << tempST->account->firstname << setw(10) << tempST->studentID << setw(10) << OS->classID << endl;
			OS = OS->next;
		}
		CL = CL->next;
	}

}
void ViewAttendanceListOfACourse(AcademicYears* year)
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
		CL = findCL(course->courseclass, classID);
		if (!CL)cout << "Invalid class ID, please enter again." << endl;
	}
	Students* st;
	StudentCourse* OS = CL->studentcourse;
	while (OS)
	{
		Class = findClass(y->classes, OS->classID);
		st = findStudent(Class->students, OS->studentID);
		if (st->Status)
		{
			cout << setw(20) << st->account->lastname << setw(20) << st->account->firstname << setw(20) << st->studentID;
			CheckinCourse* ck = st->checkincourse;
			while (ck && ck->courseID != course->courseID)
				ck = ck->next;
			for (int i = 0; i < 11; i++) {
				int bit = ck->bitweek >> i;
				if (bit % 2)
					cout << setw(11) << "V";
				else if (!bit || ck->bitweek == 0)
					cout << setw(11) << "-";
				else if (bit)
					cout << setw(11) << "X";
			}
			cout << endl;
		}

		OS = OS->next;
	}

}
void Edit_Attend_List(AcademicYears* year, Accounts*& acc)
{
	string courseID, classID, studentID;
	Courses* course = NULL;
	Semesters* s = NULL;
	while (!s)
	{
		cout << "Please enter course ID: ";
		cin >> courseID;
		s = year->semesters;
		while (s)
		{
			course = findCourse(s->courses, courseID);
			if (!course)s = s->next;
			else
			{  
				if (course->LectureName != acc->uName)
				{
					cout << "You don't have permission to edit this course."<<endl; 
					return;
				}
				break;
			}
		}
		if (!s)cout << "Invalid course ID, please enter again." << endl;
	}

	Students* st = NULL;
	CourseClass* CL = NULL;
	while (!CL)
	{
		 CL = course->courseclass;
		cout << "Please enter student ID: ";
		cin >> studentID;
		while (CL)
		{
			StudentCourse* curST = CL->studentcourse;
			while (curST)
				if (curST->studentID == studentID)
				{
					Classes* cl = findClass(year->classes, curST->classID);
					if (cl && findStudent(cl->students, studentID))
						st = findStudent(cl->students, studentID);
					break;
				}
				else curST = curST->next;
			if (st && st->Status)break;
			CL = CL->next;
		}
		if (st) break;
		else cout << "Invalid student ID, please enter again." << endl;

	}
	CheckinCourse* ck = st->checkincourse;
	while (ck)
		if (ck->courseID == courseID)break;
		else ck = ck->next;
	cout << "week: "<<endl;
	int week;
	cin >> week;
	int n = 0;
	do
	{
		cout << "0. Back" << endl;
		cout << "1.Check in"<<endl;
		cout << "2.UnCheck in"<<endl;
		cin >> n;
		if (n == 1)
		{
			if ((ck->bitweek) >> (week - 1))
				cout << "Already Checkin" << endl;
			else
			{
				ck->bitweek += 1 << (week - 1);
				cout << "Checked in"<<endl;
			}
		}
		if (n == 2)
		{
			if ((ck->bitweek) >> (week - 1) == 0)
			cout << "Student've not checked in yet." << endl;
			else
			{
				ck->bitweek -= 1 << (week - 1);
				cout << "Un checked-in"<<endl;
			}
		}

	} while (n);

}
void ImportScoreBoard(AcademicYears* year, Accounts*& acc)
{
	Courses* course = NULL;
	AcademicYears* y = inputYear(year, course);
	if (course->LectureName != acc->uName)
	{
		cout << "You don't have permission to import this course." << endl;
		return;
	}
	CourseClass* CL = course->courseclass;
	Students* st = NULL;
	while (CL)
	{

		string name = "Yr" + year->year + "_CourseID_" + course->courseID + "_ClassID_" + CL->classID + "_ScoreBoard.csv";
		string studentID;
		ifstream in;
		in.open(name);
		if (!in.is_open()) {
			CL = CL->next;
			continue;
		}
		getline(in, name);
		getline(in, name, ',');
		while (!Is_empty(in))
		{
			getline(in, name, ',');
			getline(in, name, ',');
			getline(in, studentID, ',');
			StudentCourse* sc = CL->studentcourse;
			Classes* cl = y->classes;
			while (cl)
			{
				st = findStudent(cl->students, studentID);
				if (st)break;
				cl = cl->next;
			}
			if (!st)
			{
				string temp;
				getline(in, temp);
				continue;
			}
			Scoreboards* sb = st->scoreboards;
			while (sb)
				if (sb->courseID == course->courseID)break;
				else sb = sb->next;
			if (!sb)
			{
				string temp;
				getline(in, temp);
				continue;
			}
			getline(in, sb->midtermScore, ',');
			getline(in, sb->finalScore, ',');
			getline(in, sb->labScore, ',');
			getline(in, sb->bonusScore, '\n');

		}
		CL = CL->next;;
	}
}
void Edit_ScoreBoard_Student(AcademicYears* year, Accounts*& acc)
{
	string courseID, classID, studentID;
	Courses* course = NULL;
	Semesters* s = NULL;
	while (!s)
	{
		cout << "Please enter course ID: ";
		cin >> courseID;
		s = year->semesters;
		while (s)
		{
			course = findCourse(s->courses, courseID);
			if (!course)s = s->next;
			else
			{
				if (course->LectureName != acc->uName)
				{
					cout << "You don't have permission to edit this course." << endl;
					return;
				}
				break;
			}
		}
		if (!s)cout << "Invalid course ID, please enter again." << endl;
	}

	Students* st = NULL;
	CourseClass* CL = NULL;
	while (!CL)
	{
		CL = course->courseclass;
		cout << "Please enter student ID: ";
		cin >> studentID;
		while (CL)
		{
			StudentCourse* curST = CL->studentcourse;
			while (curST)
				if (curST->studentID == studentID)
				{
					Classes* cl = findClass(year->classes, curST->classID);
					if (cl && findStudent(cl->students, studentID))
						st = findStudent(cl->students, studentID);
					break;
				}
				else curST = curST->next;
			if (st && st->Status)break;
			CL = CL->next;
		}
		if (st) break;
		else cout << "Invalid student ID, please enter again." << endl;

	}
	Scoreboards* sb = st->scoreboards;
	while (sb)
		if (sb->courseID == courseID)break;
		else sb = sb->next;
	//if (!sb)return;
	int sc = 1;
	while (sc != 5)
	{
		cout << "1.Lab score." << endl << "2.Midterm score." << endl << "3.Final score." << endl << "4.Bonus score. " << endl << "5. Back. " << endl;
		int sc;
		string Grade;
		cin >> sc;
		if (sc == 5)break;
		cout << "Grade: ";
		///cin >> Grade;
		//sb null
		if (sc == 1)cin >> sb->labScore;// = Grade;
		if (sc == 2)cin >> sb->midtermScore;// = Grade;
		if (sc == 3)cin >> sb->finalScore;// = Grade;
		if (sc == 4)cin >> sb->bonusScore;// = Grade;
	}
}
void ViewAScoreboard(AcademicYears* year)
{
	Courses* course = NULL;
	AcademicYears* y = inputYear(year, course);
	CourseClass* CL = NULL;
	while (!CL)
	{
		string classID;
		cout << "Please enter class ID: ";
		cin >> classID;
		CL = findCL(course->courseclass, classID);
		if (!CL)cout << "Invalid class ID, please enter again." << endl;
	}
	cout << course->courseID << " " << course->courseName << endl;
	cout << setw(20) << "Last name" << setw(20) << "first name" << setw(20) << "student ID";
	cout << setw(16) << "midtermScore";
	cout << setw(16) << "finalScore";
	cout << setw(16) << "labScore";
	cout << setw(16) << "bonusScore" << endl;
	Students* st;
	int i = 0;
	StudentCourse* OS = CL->studentcourse;
	while (OS)
	{
		Classes* cl = findClass(y->classes, OS->classID);
		if (cl && findStudent(cl->students, OS->studentID))
		{
			st = findStudent(cl->students, OS->studentID);
			View_Scoreboard_Student(st, course->courseID);
		}
		OS = OS->next;
	}
}