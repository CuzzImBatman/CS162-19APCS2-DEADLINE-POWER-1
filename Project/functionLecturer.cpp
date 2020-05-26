//Lecturer's first function is the same with Staff's eighth function
//-> no declaration or definition for first function
#include"function.h"
void Edit_Attend_List(AcademicYears* year)
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
			else break;
		}
		if (!s)cout << "Invalid course ID, please enter again." << endl;
	}

	Students* st = NULL;
	Classes* cl = NULL;
	while (!cl)
	{
		Classes* cl = year->classes;
		cout << "Please enter student ID: ";
		cin >> studentID;
		while (cl)
		{
			st = findStudent(cl->students, studentID);
			if (st && st->Status)break;
			cl = cl->next;
		}
		if (st) break;
		else cout << "Invalid student ID, please enter again." << endl;

	}
	CheckinCourse* ck = st->checkincourse;
	while (ck)
		if (ck->courseID == courseID)break;
		else ck = ck->next;
	cout << "week";
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
				cout << "Checked in";
			}
		}
		if (n == 2)
		{
			if ((ck->bitweek) >> (week - 1) == 0)
			cout << "Student've not checked in yet." << endl;
			else
			{
				ck->bitweek -= 1 << (week - 1);
				cout << "Un checked-in";
			}
		}

	} while (n);

}
void Edit_ScoreBoard_Student(AcademicYears* year)
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
			else break;
		}
		if (!s)cout << "Invalid course ID, please enter again." << endl;
	}

	Students* st = NULL;
	Classes* cl = NULL;
	while (!cl)
	{
		Classes* cl = year->classes;
		cout << "Please enter student ID: ";
		cin >> studentID;
		while (cl)
		{
			st = findStudent(cl->students, studentID);
			if (st && st->Status)break;
			cl = cl->next;
		}
		if (st) break;
		else cout << "Invalid student ID, please enter again." << endl;

	}
	Scoreboards* sb = st->scoreboards;
	cout << "Lab score, Midterm score, Final score, Bonus score: ";
	string sc,Grade;
	cin >> sc;
	cout << "Grade: ";
	if (sc == "Lab score")cin >> sb->labScore;
	if (sc == "Midterm score")cin >> sb->midtermScore;
	if (sc == "Final score")cin >> sb->finalScore;
	if (sc == "Bonus score")cin >> sb->bonusScore;
	


}
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
	cout << setw(16) << SB->bonusScore;

}
void View_Scoreboard(AcademicYears* year)
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
		if(!CL)cout << "Invalid class ID, please enter again." << endl;
	}
	cout << course->courseID << " " << course->courseName << endl;
	cout << setw(20) << "Last name" << setw(20) << "first name" << setw(20) << "student ID";
	cout << setw(16) << "midtermScore";
	cout << setw(16) << "finalScore";
	cout << setw(16) << "labScore";
	cout << setw(16) << "bonusScore" << endl;
	Students* st = CL->students;
	int i = 0;
	int bit = CL->BitAttend;
	while (st)
	{
		
		if (st->Status && (bit >> i) % 2)View_Scoreboard_Student(st, course->courseID);
		i++;
		st = st->next;
	}
	OutsideStudent* OS = CL->Outsider;
	while (OS)
	{
		Classes* cl = findClass(y->classes, OS->classID);
		if (cl)st = findStudent(cl->students, OS->studentID);
		if(st)View_Scoreboard_Student(st, course->courseID);
		OS = OS->next;
	}
}
