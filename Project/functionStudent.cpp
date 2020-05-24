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
	cout << "the ID of course you want to checkin this week";
	cin >> courseID;
	while (cur != NULL)
		if (cur->courseID == courseID )
			if ((cur->bitweek >> (week - 1)) % 2 == 0) {
				cout << "Cannot check  in Course";
				return ;
			}
			else {
				cur->bitweek += 1 << (week - 1);
				return;
			}

	cout << "Cannot check  in Course";
	return ;

}
void viewCheckIn(CheckinCourse* checkincourse) {
	cout << "The week you want to wiew: ";
		int week;
		cin >> week;
	cout << "Week: " << week << endl;
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
			else if (bit % 2 == 0 && !check)
				cout << setw(10) << "-";
			else if (bit % 2 == 0 && check)
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
	cout << setw(10);

	for (int i = 1; i <= 6; i++)
		for (int j = 1; j <= 4; j++)

			cout << setw(10) << student->schedule[i][j];

}
void viewScoreCourse(Students* student) {
	cout << " ID of course you want to view: ";
	string courseID;
	Scoreboards* scoreboard = student->scoreboards;
	while (scoreboard != NULL)
		if (scoreboard->courseName == courseID) {
			cout << courseID << endl;
			cout << setw(10) << "midtermScore";
			cout << setw(10) << "finalScore";
			cout << setw(10) << "labScore";
			cout << setw(10) << "bonusScore";

			cout << setw(10) << scoreboard->midtermScore;
			cout << setw(10) << scoreboard->finalScore;
			cout << setw(10) << scoreboard->labScore;
			cout << setw(10) << scoreboard->bonusScore;

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