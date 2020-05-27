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
			out << CL->classID<<endl;
			out << CL->BitAttend<<endl;
			OutsideStudent* OS = CL->Outsider;
			i = 0;
			while (OS)
			{
				i++;
				OS = OS->next;
			}
			out << i << endl;
			OS = CL->Outsider;
			while (OS)
			{
				out << OS->studentID<<endl;
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
	ofstream out;
	out.open("Yr" + year + "_StudentID" + st->studentID + "ScoreBoard.txt");
	while (SB)
	{
		out << SB->courseID << " " << SB->labScore << " " << SB->midtermScore << " " << SB->finalScore << " " << SB->bonusScore << endl;
		SB = SB->next;
	}
	out.close();

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
