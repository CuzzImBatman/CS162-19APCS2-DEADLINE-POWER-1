#include "function.h"

void writeAccounts(ofstream& fout, Accounts* acc){
	fout << acc->uName << endl;
	for (int i = 0; i < 8; i++)
		fout << hex << setw(8) << setfill('0') << acc->pwd.state[i]<<endl;
	fout << acc->firstname << endl;
	fout << acc->lastname << endl;
	fout << acc->gender << endl;
	fout << acc->doB->day << endl;
	fout << acc->doB->month << endl;
	fout << acc->doB->year << endl<<endl;
}

void writeCourses(Courses* course, char semes, string year) {
	ofstream out;
	string Cout = "Yr" + year + "_Sem" + semes + "_CourseDB_TEST.txt";
	out.open(Cout);

	int i = 0;
	Courses* cs = course;
	while (cs)
	{
		i++;
		cs = cs->next;
	}
	out << i << endl;
	while (course)
	{
		out << course->courseID << endl;
		out << course->courseName << endl;
		out << course->LectureName << endl;
		CourseClass* CL = course->courseclass;
		i = 0;
		while (CL)
		{
			i++;
			CL = CL->next;
		}
		out << i << endl;
		CL = course->courseclass;
		while (CL)
		{
			out << CL->startDate.day << " " << CL->startDate.month << " " << CL->startDate.year << endl;
			out << CL->endDate.day << " " << CL->endDate.month << " " << CL->endDate.year << endl;
			if (CL->DayInWeek == 0)out << "Mon";
			else if (CL->DayInWeek == 1)out << "Tue";
			else if (CL->DayInWeek == 2)out << "Wed";
			else if (CL->DayInWeek == 3)out << "Thu";
			else if (CL->DayInWeek == 4)out << "Fri";
			else if (CL->DayInWeek == 5)out << "Sat";
			out << endl;
			out << CL->startTime <<" "<<CL->endTime<< endl;
			

			out << CL->classID<<endl;
			StudentCourse* OS = CL->studentcourse;
			i = 0;
			while (OS)
			{
				i++;
				OS = OS->next;
			}
			out << i << endl;
			OS = CL->studentcourse;
			while (OS)
			{
				out << OS->studentID<<" ";
				out << OS->classID<<endl;
				OS = OS->next;
			}
			CL = CL->next;

		}
		out << course->room << endl << endl;;
		course = course->next;
	}
}

void writeLecturers(Lecturers* lect, char semes, string year) {
	Lecturers* tempLect = lect;
	ofstream lectOut;
	string fileOut = "Yr" + year + "_Sem" + semes + "_LecturerDB_TEST.txt";
	lectOut.open(fileOut);
	if (lectOut.is_open()) {
		int n = 0;
		while (tempLect) {
			n++;
			tempLect = tempLect->next;
		}
		lectOut << n << endl;
		tempLect = lect;
		while (tempLect) {
			writeAccounts(lectOut, tempLect->account);
			tempLect = tempLect->next;
		}
	}
	lectOut.close();
}
void writeStaffs(Staffs* staff, char semes, string year) {
	Staffs* tempStaff = staff;
	ofstream staffOut;
	string fileOut = "Yr" + year + "_Sem" + semes + "_StaffDB_TEST.txt";
	staffOut.open(fileOut);
	if (staffOut.is_open()) {
		int n = 0;
		while (tempStaff) {
			n++;
			tempStaff = tempStaff->next;
		}
		staffOut << n << endl;
		tempStaff = staff;
		while (tempStaff) {
			writeAccounts(staffOut, tempStaff->account);
			tempStaff = tempStaff->next;
		}
	}
	staffOut.close();
}
void writeSemesters(Semesters* semes, string year) {
	Semesters* tempSemes = semes;
	for (char n = 49; n < 52; n++) {
		writeStaffs(tempSemes->staffs, n, year);
		writeLecturers(tempSemes->lecturers, n, year);
		writeCourses(tempSemes->courses, n, year);
		tempSemes = tempSemes->next;
	}
}

void writeScoreBoard(Students* st, string year)
{
	Scoreboards* SB = st->scoreboards;
	int i = 0;


	SB = st->scoreboards;
	ofstream out;
	string output = "Yr" + year + "_StudentID" + st->studentID + "_ScoreBoard.csv";
	out.open(output);

	while (SB)
	{
		out << SB->courseName << ",";
		out << SB->courseID << "," << SB->labScore << "," << SB->midtermScore << "," << SB->finalScore << "," << SB->bonusScore << endl;
		SB = SB->next;
	}
//	out.close();

}
void writeCheckIn(Students* st, string year)
{
	CheckinCourse* CK = st->checkincourse;
	int i = 0;

	while (CK)
	{
		i++;
		CK = CK->next;
	}
	CK = st->checkincourse;
	ofstream out;
	string output = "Yr" + year + "_StudentID" + st->studentID + "_CheckIn.txt";
	out.open(output);
	out << i << endl;
	while (CK)
	{
		out << CK->room << endl;
		out << CK->courseID << " " <<CK->bitweek<< endl;
		CK = CK->next;
	}
	//	out.close();
}
void writeStudents(Students* st, string Class, string year) {

	Students* tempSt = st;
	ofstream stOut;
	string fileOut = "Yr" + year + "_Cl" + Class + "_StudentDB_TEST.txt";
	stOut.open(fileOut);
	if (stOut.is_open()) {
		int n = 0;
		while (tempSt) {
			n++;
			tempSt = tempSt->next;
		}
		stOut << n << endl;
		tempSt = st;
		while (tempSt) {
			writeAccounts(stOut, tempSt->account);
			writeScoreBoard(tempSt, year);
			writeCheckIn(tempSt, year);
			tempSt = tempSt->next;
		}
	}
	stOut.close();
}
void writeClasses(Classes* Class, string year) {
	Classes* tempClass = Class;
	ofstream classOut;
	string fileOut = "Yr" + year + "_ClassDB_TEST.txt";
	classOut.open(fileOut);
	if (classOut.is_open()) {
		int n = 0;
		while (tempClass) {
			n++;
			tempClass = tempClass->next;
		}
		classOut << n << endl;
		tempClass = Class;
		while (tempClass) {
			classOut << tempClass->classID << endl;
			writeStudents(tempClass->students, tempClass->classID, year);
			tempClass = tempClass->next;
		}
	}
	classOut.close();
}

void writeAcademicYears(AcademicYears* year) {
	AcademicYears* tempYear = year;
	ofstream yearOut;
	yearOut.open("AcademicYearDB_TEST.txt");
	if (yearOut.is_open()) {
		int n = 0;
		while (tempYear) {
			n++;
			tempYear = tempYear->next;
		}
		yearOut << n << endl;
		tempYear = year;
		while (tempYear) {
			yearOut << tempYear->year << endl;
			writeClasses(tempYear->classes, tempYear->year);
			writeSemesters(tempYear->semesters, tempYear->year);
			tempYear = tempYear->next;
		}
	}
	yearOut.close();
}