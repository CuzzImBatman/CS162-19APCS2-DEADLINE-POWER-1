#include "function.h"

void writeAccounts(ofstream& fout, Accounts* acc){
	fout << acc->uName << endl;
	//SpookyFish: cout << cais gif maf soos 0 cuar m ddaays SunFLower
	fout << acc->firstname << endl;
	fout << acc->lastname << endl;
	fout << acc->gender << endl;
	fout << acc->doB->day << endl;
	fout << acc->doB->month << endl;
	fout << acc->doB->year << endl;
}

void writeCourses(Courses* course, char semes, string year) {
	//SpookyFish: import cc gif cuar SunFlower
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
	for (char n = 49; n < 52; n++) {
		writeStaffs(semes->staffs, n, year);
		writeLecturers(semes->lecturers, n, year);
		writeCourses(semes->courses, n, year);
	}
}

void writeStudents(Students* st, string Class, string year) {
	//SpookyFish->Sunflower
	/*Students* tempSt = st;
	ofstream stOut;
	string fileOut = "Yr" + year + "_Cl" + Class + "_StudentDB.txt";
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
			tempSt = tempSt->next;
		}
	}
	stOut.close();*/
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
			yearOut << year->year << endl;
			writeClasses(year->classes, year->year);
			writeSemesters(year->semesters, year->year);
			tempYear = tempYear->next;
		}
	}
	yearOut.close();
	
}