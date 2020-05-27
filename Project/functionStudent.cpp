#include "function.h"
#include <stdio.h>
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
	CheckinCourse* cur = NULL;
	string courseID;
	cout << "Current week : ";
	int week; 
	cin >> week;
	while (!cur)
	{
		
		cout << "the ID of course you want to checkin this week" << endl;
		cin >> courseID;
		cur = student->checkincourse;
		while (cur)
			if (cur->courseID == courseID)break;
			else cur = cur->next;
		if (!cur)cout << "Invalid course ID, please enter again.";
	}
		if (cur->courseID == courseID)
			if ((cur->bitweek >> (week - 1)) % 2) {
				cout << "Cannot check  in Course";
				return;
			}
			else {
				cur->bitweek += 1 << (week - 1);
				cout << "Checked";
				return;
			}


	
	return ;

}


void viewCheckIn(CheckinCourse* checkincourse) {
	while (checkincourse != NULL) {

		cout << setw(10) << checkincourse->courseID;
		for (int i = 0; i < 11; i++) {
			int bit = checkincourse->bitweek >> i;
			if (bit % 2)
				cout << setw(11) << "V";
			else if (checkincourse->bitweek == 0)
				cout << setw(11) << "-";
			else if (bit)
				cout << setw(11) << "X";
		}
		cout << endl << endl;
		checkincourse = checkincourse->next;
	}

}
void viewSchedule(Students* student) {

	cout << setw(10);
	cout << "Monday";
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
		if (scoreboard->courseID == courseID) {
			cout << courseID <<" "<< scoreboard->courseName<<endl;
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



//CheckStatusStudent