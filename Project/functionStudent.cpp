#include "function.h"

using namespace std;
/*Classes* findClass(Classes* Class, string ClassID) {
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

Courses* findCourse(Courses* course, string ID) {
	Courses* temp = course;
	while (temp && temp->courseID != ID)
		temp = temp->next;
	return temp;
}*/
void Tick(Students* student) {
	CheckinCourse* cur = student->checkincourse;
	cout << "Current week : ";
	int week; 
	cin >> week;
	string courseID;
	cout << "the ID of course you want to checkin this week"<<endl;
	cin >> courseID;
	while (cur != NULL)
	{
		if (cur->courseID == courseID)
			if ((cur->bitweek >> (week - 1)) % 2) {
				cout << "Cannot check  in Course";
				return;
			}
			else {
				cur->bitweek += 1 << (week - 1);
				return;
			}
		cur = cur->next;
	}

	cout << "Cannot check  in Course";
	return ;

}
void viewCheckIn(CheckinCourse* checkincourse) {
	
	while (checkincourse != NULL) {
		int check = 0;
		int bit = checkincourse->bitweek;
		cout << setw(10) << checkincourse->courseID;
		for (int i = 0; i < 11; i++) {
			int bit = checkincourse->bitweek >> i;
			if (bit % 2) {
				check = 1;
				cout << setw(10) << "V";
			}
			else if (check || checkincourse->bitweek == 0)
				cout << setw(10) << "-";
			else if ( !check)
				cout << setw(10) << "X";
		}
		cout << endl;
		checkincourse = checkincourse->next;
	}

}
void viewSchedule(Students* student) {

	cout << setw(10);
	cout << "Monay";
	cout << setw(10);
	cout << "Tueseday";
	cout << setw(10);
	cout << "Wednesday";
	cout << setw(10);
	cout << "Thursday";
	cout << setw(10);
	cout << "Friday";
	cout << setw(10);
	cout << "Saturday";
	cout << endl;

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 4; j++)

			cout << setw(10) << student->schedule[i][j];
		cout << endl;
	};

}
void viewScoreCourse(Students* student) {
	cout << " ID of course you want to view: ";
	string courseID;
	cin >> courseID;
	Scoreboards* scoreboard = student->scoreboards;
	while (scoreboard != NULL)
		if (scoreboard->courseName == courseID) {
			cout << courseID << endl;
			cout << setw(20) << "midtermScore";
			cout << setw(20) << "finalScore";
			cout << setw(20) << "labScore";
			cout << setw(20) << "bonusScore"<<endl;

			cout << setw(20) << scoreboard->midtermScore;
			cout << setw(20) << scoreboard->finalScore;
			cout << setw(20) << scoreboard->labScore;
			cout << setw(20) << scoreboard->bonusScore;

			break;
		}
		else
			scoreboard = scoreboard->next;
}
void AddCheckInCourse(Students*& st, string courseID)
{
	CheckinCourse* newcourse = new CheckinCourse;
	newcourse->courseID = courseID;
	newcourse->bitweek = 0;
	newcourse->next = st->checkincourse;
	st->checkincourse = newcourse;

}
void AddCourseToStudent(Students*& ST, string courseID, int DayInWeek, int AtNth) {

	ST->schedule[DayInWeek][AtNth] = courseID;

	CheckinCourse* newcourse = new CheckinCourse;
	newcourse->courseID = courseID;
	newcourse->bitweek = 0;
	//    newcourse->status=1;
	newcourse->next = ST->checkincourse;
	ST->checkincourse = newcourse;

	Scoreboards* SB = new Scoreboards;
	SB->courseName = courseID;
	SB->next = ST->scoreboards;
	ST->scoreboards = SB;

}
void EditScheduleCourseOfClass(Courses*& course, string classID, string courseID, Classes*& Class) {
	Classes* curCL = findClass(Class, classID);

	Courses* curCourse = findCourse(course, courseID);

	CourseClass* courseclass = curCourse->courseclass;
	while (courseclass->classID != classID)
		courseclass = courseclass->next;

	int day, nth, day0, nth0, i, j;
	cout << "Day in week: ";
	cin >> day0;
	cout << "nth: ";
	cin >> nth0;
	//change schedule

	for (i = 1; i <= 6; i++)
		for (j = 1; j <= 4; j++)
			if (curCL->schedule[i][j] == courseID) {
				curCL->schedule[i][j] == "//";
				day = i;
				nth = j;
				break;
			}
	curCL->schedule[day0][nth0] = courseID;

	Students* curST = Class->students;
	while (curST != NULL) {
		curST->schedule[i][j] = "//";
		curST->schedule[day0][nth0] = courseID;
		curST = curST->next;
	}

	/// change schedule chechou
	OutsideStudent* Outsider = courseclass->Outsider;
	curCL = Class;
	while (Outsider != NULL) {
		int k = CheckStatusStudent(Outsider->studentID, Outsider->classID, Class);
		if (k < 1) {
			Outsider = Outsider->next;
			curCL = Class;
			continue;
		}
		while (curCL != NULL)
			if (curCL->classID == Outsider->classID) {

				curST = Class->students;
				while (curST != NULL && curST->Status) {

					if (curST->studentID == Outsider->studentID)

					{
						curST->schedule[i][j] = "//";
						curST->schedule[day0][nth0] = courseID;
						curCL = Class;
						Outsider = Outsider->next;
						k = 1;
						break;
					}
					curST = curST->next;
				}

			}
			else
				curCL = curCL->next;
	}

}
void DeleleScoreBoardStudent(Students*& ST)
{
	while (ST->scoreboards)
	{
		Scoreboards* SB = ST->scoreboards;
		SB = ST->scoreboards->next;
		ST->scoreboards = NULL;
		ST->scoreboards = SB;

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