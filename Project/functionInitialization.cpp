#include "function.h"
void accountInit(ifstream& fin, Accounts*& acc) {
	if (!acc)
		acc = new Accounts;
	fin >> acc->pwd;
	fin >> acc->role;
	fin >> acc->lastname;
	fin.ignore(10, '\n');
	getline(fin, acc->firstname);
	fin >> acc->gender;
	acc->doB = new Date;
	fin >> acc->doB->day;
	fin >> acc->doB->month;
	fin >> acc->doB->year;
}

void courseInit(Courses* course, char semes) {
	Courses* tempCourse = course;
	ifstream courseIn;
	courseIn.open("CourseDB.txt");
	int n;
	courseIn >> n;
	while (n) {
		char temp;
		courseIn >> temp;
		if (temp == semes) {
			if (!course) {
				course = new Courses;

				tempCourse = course;
			}
			else {
				tempCourse->next = new Courses;

				tempCourse = tempCourse->next;
			}
		}
		else {
			courseIn.ignore(100, '\n');
			courseIn.ignore(100, '\n');
			courseIn.ignore(100, '\n');
		}
		n--;
	}
	courseIn.close();
}
void lecturerInit(Lecturers* lec, char semes) {
	Lecturers* tempLec = lec;
	ifstream lecIn;
	lecIn.open("LecturerDB.txt");
	int n;
	lecIn >> n;
	while (n) {
		char temp;
		lecIn >> temp;
		if (temp == semes) {
			if (!lec) {
				lec = new Lecturers;
				lec->account = new Accounts;
				accountInit(lecIn, lec->account);
				tempLec = lec;
			}
			else {
				tempLec->next = new Lecturers;
				tempLec->next->account = new Accounts;
				accountInit(lecIn, tempLec->next->account);
				tempLec = tempLec->next;
			}
		}
		n--;
	}
	lecIn.close();
}
void staffInit(Staffs* staff, char semes) {
	Staffs* tempStaff = staff;
	ifstream staffIn;
	staffIn.open("StaffDB.txt");
	int n;
	staffIn >> n;
	while (n) {
		char temp;
		staffIn >> temp;
		if (temp == semes) {
			if (!staff) {
				staff = new Staffs;
				staff->account = new Accounts;
				accountInit(staffIn, staff->account);
				tempStaff = staff;
			}
			else {
				tempStaff->next = new Staffs;
				tempStaff->next->account = new Accounts;
				accountInit(staffIn, tempStaff->next->account);
				tempStaff = tempStaff->next;
			}
		}
		n--;
	}
	staffIn.close();
}
void semesterInit(Semesters*& semes, int year) {
	Semesters* tempSemes = semes;
	ifstream semesIn;
	semesIn.open("SemesterDB.txt");
	int n;
	semesIn >> n;
	while (n) {
		int temp;
		semesIn >> temp;
		if (temp == year) {
			if (!semes) {
				semes = new Semesters;
				semesIn >> semes->semesterNo;
				staffInit(semes->staffs, semes->semesterNo);
				lecturerInit(semes->lecturers, semes->semesterNo);
				courseInit(semes->courses, semes->semesterNo);
				tempSemes = semes;
			}
			else {
				tempSemes->next = new Semesters;
				semesIn >> tempSemes->next->semesterNo;
				staffInit(tempSemes->next->staffs, tempSemes->next->semesterNo);
				lecturerInit(tempSemes->next->lecturers, tempSemes->next->semesterNo);
				courseInit(tempSemes->next->courses, tempSemes->next->semesterNo);
				tempSemes = tempSemes->next;
			}
		}
		else {
			//add case 
		}
		n--;
	}
	semesIn.close();
}

void studentInit(Students*& st, string Class) {
	Students* tempSt = st;
	ifstream stIn;
	stIn.open("StudentDB.txt");
	int n;
	stIn >> n;
	while (n>0) {
		string temp;
		stIn >> temp;
		if (temp == Class) {
			if (!st) {
				st = new Students;
				stIn >> st->studentID;
				st->account = new Accounts;
				accountInit(stIn, st->account);
				st->account->uName = st->studentID;
				tempSt = st;
			}
			else {
				tempSt->next = new Students;
				stIn >> tempSt->next->studentID;
				tempSt->next->account->uName = tempSt->next->studentID;
				accountInit(stIn, tempSt->next->account);
				tempSt = tempSt->next;
			}
		}
		else {
			stIn.ignore(100, '\n');
			stIn.ignore(100, '\n');
			stIn.ignore(100, '\n');
			stIn.ignore(100, '\n');
			stIn.ignore(100, '\n');
			stIn.ignore(100, '\n');
			stIn.ignore(100, '\n');
			stIn.ignore(100, '\n');
			stIn.ignore(100, '\n');
			stIn.ignore(100, '\n');
		}
		n--;
	}
	stIn.close();
}
void classInit(Classes*& Class, int year) {
	Classes* tempClass = Class;
	int no = 1;
	ifstream classIn;
	classIn.open("ClassDB.txt");
	int n;
	classIn >> n;
	while (n) {
		int temp;
		classIn >> temp;
		if (temp == year) {
			if (!Class) {
				Class = new Classes;
				Class->classno = no++;
				classIn >> Class->classID;
				//scheduleInit
				studentInit(Class->students, Class->classID);
				tempClass = Class;
			}
			else {
				tempClass->next = new Classes;
				tempClass->next->classno = no++;
				classIn >> tempClass->next->classID;
				studentInit(tempClass->next->students, tempClass->next->classID);
				//scheduleInit
				tempClass = tempClass->next;
			}
		}
		else
			classIn.ignore(100, '\n');
		n--;
	}
	classIn.close();
};

void academicYearInit(AcademicYears*& year) {
	AcademicYears* tempYear = year;
	ifstream yearIn;
	yearIn.open("AcademicYearDB.txt");
	int n;
	yearIn >> n;
	while (n) {
		if (!year) {
			year = new AcademicYears;
			yearIn >> year->year;
			classInit(year->classes, year->year);
			semesterInit(year->semesters, year->year);
			tempYear = year;
		}
		else {
			tempYear->next = new AcademicYears;
			yearIn >> tempYear->next->year;
			classInit(tempYear->next->classes, tempYear->next->year);
			semesterInit(tempYear->next->semesters, tempYear->next->year);
			tempYear = tempYear->next;
		}
		n--;
	}
	yearIn.close();
}