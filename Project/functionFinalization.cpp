#include "function.h"

void writeCourses(Courses* course, char semes, string year) {

}

void writeLecturers(Lecturers* lect, char semes, string year) {

}

void writeStaffs(Staffs* staff, char semes, string year) {

}

void writeSemesters(Semesters* semes, string year) {
	char n = 49;
	for (n; n < 52; ++n) {
		writeStaffs(semes->staffs, n, year);
		writeLecturers(semes->lecturers, n, year);
		writeCourses(semes->courses, n, year);
	}
}

void writeStudents(Students* st, string Class, string year) {
	Students* tempSt = st;
	ofstream stOut;
	string fileOut = "Yr" + year + "_Cl" + Class + "_StudentDB.txt";
	stOut.open(fileOut);
	if (stOut.is_open()) {
		int n = 0;
		while (st) {
			n++;
			//writeSchedule();
			st = st->next;
		}
	}
}

void writeClasses(Classes* Class, string year) {
	Classes* tempClass = Class;
	ofstream classOut;
	string fileOut = "Yr" + year + "_ClassDB.txt";
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
}

void writeAcademicYears(AcademicYears* year) {
	AcademicYears* tempYear = year;
	ofstream yearOut;
	yearOut.open("AcademicYearDB.txt");
	if (yearOut.is_open()) {
		int n = 0;
		while (tempYear) {
			n++;
			tempYear = tempYear->next;
		}
		yearOut << n << endl;
		tempYear = year;
		while (tempYear) {
			yearOut << year->year << endl;
			writeClasses(year->classes, year->year);
			writeSemesters(year->semesters, year->year);

			tempYear = tempYear->next;
		}
	}
	yearOut.close();
}