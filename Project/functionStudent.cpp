#include "function.h"
#include <stdio.h>
using namespace std;
void takeString(string& take, string& s)
{
	take = "";
	int i = 0;
	while (s[i] == ' ')	i++;

	s.erase(0, i);
	i = 0;
	while (s[i] != ' ')
		take = take + s[i++];

	s.erase(0, i);
}
int takeTimeNumber(string time)
{
	return time[0] * 1000 + time[1] * 100 + time[3] * 10 + time[4] - 48 * 1111;
}
void Tick(Students* student) {
	auto start = std::chrono::system_clock::now();
	
	auto end = std::chrono::system_clock::now();

	std::chrono::duration<double> elapsed_seconds = end - start;
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);

	std::cout << "finished computation at " << std::ctime(&end_time)
		<< "elapsed time: " << elapsed_seconds.count() << "s\n";
	string s = ctime(&end_time);
	string take;
	string time;
	Date date;
	int dayinweek=0;
	takeString(take, s);
	if (take[1] == 'o')dayinweek = 0;
	else if (take[1] == 'u')dayinweek = 1;
	else if (take[1] == 'e')dayinweek = 2;
	else if (take[1] == 'h')dayinweek = 3;
	else if (take[1] == 'r')dayinweek = 4;
	else if (take[1] == 'a')dayinweek = 5;
	
	takeString(take, s);
	if (take == "Jan")date.month = "01";
	else if (take == "Feb")date.month = "02";
	else if (take == "Mar")date.month = "03";
	else if (take == "Apr")date.month = "04";
	else if (take == "May")date.month = "05";
	else if (take == "Jun")date.month = "06";
	else if (take == "Jul")date.month = "07";
	else if (take == "Aug")date.month = "08";
	else if (take == "Sep")date.month = "09";
	else if (take == "Oct")date.month = "10";
	else if (take == "Nov")date.month = "11";
	else if (take == "Dec")date.month = "12";
	takeString(take, s);
	date.day = take;
	takeString(take, s);
	time = take;
	takeString(take, s);
	date.year = take;
	int check = numberOfDay(date);

	CheckinCourse* CK = student->checkincourse;
	while (CK)
	{
		if (dayinweek == numberOfDay(CK->startDate) % 7)return;
		CK = CK->next;
	}
	if (!CK || check< numberOfDay(CK->startDate) || check> numberOfDay(CK->endDate) || takeTimeNumber(time)<takeTimeNumber(CK->startTime) || takeTimeNumber(time) > takeTimeNumber(CK->endTime))
	{
		cout << "No course at the current time.";
		return;
	}
	int bit = (check - numberOfDay(CK->startDate)) % 7;
	CK->bitweek += 1 >> bit;
	cout << "Checked in";
	return ;

}


void viewCheckIn(CheckinCourse* checkincourse) {
	while (checkincourse != NULL) {

		cout << setw(10) << checkincourse->courseID;
		for (int i = 0; i < 11; i++) {
			int bit = checkincourse->bitweek >> i;
			if (bit % 2)
				cout << setw(11) << "V";
			else if (!bit ||checkincourse->bitweek == 0)
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

	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 6; i++)

			cout << setw(10) << student->schedule[i][j];
		cout << endl;
	};
	Scoreboards* SB = student->scoreboards;
	CheckinCourse* CK = student->checkincourse;
	while (SB && CK)
	{
		cout << SB->courseID << ": " << SB->courseName << "(" << CK->room << ")"<< " time: " <<CK->startTime<<endl;
		cout << "Start Date: " << CK->startDate.day << " " << CK->startDate.month << " " << CK->startDate.year << endl;
		cout << "End Date: " << CK->endDate.day << " " << CK->endDate.month << " " << CK->endDate.year << endl<<endl;
		SB = SB->next;
		CK = CK->next;
	}

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