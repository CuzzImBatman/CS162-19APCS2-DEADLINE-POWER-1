#include "function.h"
void accountInit(ifstream& fin, Accounts*& acc) {
	if (!acc)
		acc = new Accounts;
	fin >> acc->pwd;
	fin >> acc->firstname;
	fin.ignore(10, '\n');
	getline(fin, acc->lastname);
	fin >> acc->gender;
	acc->doB = new Date;
	fin >> acc->doB->day;
	fin >> acc->doB->month;
	fin >> acc->doB->year;
}

void courseInit(Courses*& course, char semes, string year) {
	Courses* tempCourse = course;
	ifstream courseIn;
	char no = '1';
	string fileIn = "Yr" + year + "_Sem" + semes + "_CourseDB.txt";
	courseIn.open(fileIn); 
	if (courseIn.is_open()) {
		int n;
		courseIn >> n;
		while (n) {
			if (!course) {
				course = new Courses;
				course->courseno = no++;
				courseIn >> course->courseID;
				courseIn.ignore(10, '\n');
				getline(courseIn, course->courseName);
				course->courseclass = new CourseClass;
				int m;
				courseIn >> m;
				for (int i = 0; i < m; ++i) {
					courseIn >> course->courseclass->classID;// temporary, it's wrong btw.
				}
				courseIn >> course->LectureName;
				courseIn >> course->courseclass->startDate.day;
				courseIn >> course->courseclass->startDate.month;
				courseIn >> course->courseclass->startDate.year;
				courseIn >> course->courseclass->endDate.day;
				courseIn >> course->courseclass->endDate.month;
				courseIn >> course->courseclass->endDate.year;
				string temp;
				courseIn >> temp;
				switch (temp[1]) { //Mo Tu We Th Fr Sa
				case 'o':
					course->courseclass->DayInWeek = 1;
					break;
				case 'u':
					course->courseclass->DayInWeek = 2;
					break;
				case 'e':
					course->courseclass->DayInWeek = 3;
					break;
				case 'h':
					course->courseclass->DayInWeek = 4;
					break;
				case 'r':
					course->courseclass->DayInWeek = 5;
					break;
				case 'a':
					course->courseclass->DayInWeek = 6;
					break;
				}
				int hour, minute;
				courseIn >> hour >> minute;
				switch (hour) {
				case 7:
					course->courseclass->AtNth = 1;
					break;
				case 9:
					course->courseclass->AtNth = 2;
					break;
				case 13:
					course->courseclass->AtNth = 3;
					break;
				case 15:
					course->courseclass->AtNth = 4;
					break;
				}
				courseIn >> course->room;
				tempCourse = course;
			}
			else {
				tempCourse->next = new Courses;
				tempCourse->next->courseno = no++;
				courseIn >> tempCourse->next->courseID;
				courseIn.ignore(10, '\n');
				getline(courseIn, tempCourse->next->courseName);
				tempCourse->next->courseclass = new CourseClass;
				int m;
				courseIn >> m;
				for (int i = 0; i < m; ++i) {
					courseIn >> tempCourse->next->courseclass->classID;// temporary, it's wrong btw.
				}
				courseIn >> tempCourse->next->LectureName;
				courseIn >> tempCourse->next->courseclass->startDate.day;
				courseIn >> tempCourse->next->courseclass->startDate.month;
				courseIn >> tempCourse->next->courseclass->startDate.year;
				courseIn >> tempCourse->next->courseclass->endDate.day;
				courseIn >> tempCourse->next->courseclass->endDate.month;
				courseIn >> tempCourse->next->courseclass->endDate.year;
				string temp;
				courseIn >> temp;
				switch (temp[1]) { //Mo Tu We Th Fr Sa
				case 'o':
					tempCourse->next->courseclass->DayInWeek = 1;
					break;
				case 'u':
					tempCourse->next->courseclass->DayInWeek = 2;
					break;
				case 'e':
					tempCourse->next->courseclass->DayInWeek = 3;
					break;
				case 'h':
					tempCourse->next->courseclass->DayInWeek = 4;
					break;
				case 'r':
					tempCourse->next->courseclass->DayInWeek = 5;
					break;
				case 'a':
					tempCourse->next->courseclass->DayInWeek = 6;
					break;
				}
				int hour, minute;
				courseIn >> hour >> minute;
				switch (hour) {
				case 7:
					tempCourse->next->courseclass->AtNth = 1;
					break;
				case 9:
					tempCourse->next->courseclass->AtNth = 2;
					break;
				case 13:
					tempCourse->next->courseclass->AtNth = 3;
					break;
				case 15:
					tempCourse->next->courseclass->AtNth = 4;
					break;
				}
				courseIn >> tempCourse->next->room;
				tempCourse = tempCourse->next;
			}
			n--;
		}
	}
	courseIn.close();
}
void lecturerInit(Lecturers*& lec, char semes, string year) {
	Lecturers* tempLec = lec;
	ifstream lecIn;
	string fileIn = "Yr" + year + "_Sem" + semes + "_LecturerDB.txt";
	lecIn.open(fileIn);
	if (lecIn.is_open()) {
		int n;
		lecIn >> n;
		while (n) {
			if (!lec) {
				lec = new Lecturers;
				lec->account = new Accounts;
				lecIn >> lec->account->uName;
				accountInit(lecIn, lec->account);
				lec->account->role = 3;
				tempLec = lec;
			}
			else {
				tempLec->next = new Lecturers;
				tempLec->next->account = new Accounts;
				lecIn >> tempLec->next->account->uName;
				accountInit(lecIn, tempLec->next->account);
				tempLec->next->account->role = 3;
				tempLec = tempLec->next;
			}
			n--;
		}
	}
	lecIn.close();
}
void staffInit(Staffs*& staff, char semes, string year) {
	Staffs* tempStaff = staff;
	ifstream staffIn;
	string fileIn = "Yr" + year + "_Sem" + semes + "_StaffDB.txt";
	staffIn.open(fileIn);
	if (staffIn.is_open()) {
		int n;
		staffIn >> n;
		while (n) {
			if (!staff) {
				staff = new Staffs;
				staff->account = new Accounts;
				staffIn >> staff->account->uName;
				accountInit(staffIn, staff->account);
				staff->account->role = 2;
				tempStaff = staff;
			}
			else {
				tempStaff->next = new Staffs;
				tempStaff->next->account = new Accounts;
				staffIn >> tempStaff->next->account->uName;
				accountInit(staffIn, tempStaff->next->account);
				tempStaff->next->account->role = 2;
				tempStaff = tempStaff->next;
			}
			n--;
		}
	}
	staffIn.close();
}
void semesterInit(Semesters*& semes, string year) {
	Semesters* tempSemes = semes;
	char n = '1';
	while (n < '4') {
		if (!semes) {
			semes = new Semesters;
			semes->semesterNo = n;
			staffInit(semes->staffs, semes->semesterNo, year);
			lecturerInit(semes->lecturers, semes->semesterNo, year);
			courseInit(semes->courses, semes->semesterNo, year);
			tempSemes = semes;
		}
		else {
			tempSemes->next = new Semesters;
			tempSemes->next->semesterNo = n;
			staffInit(tempSemes->next->staffs, tempSemes->next->semesterNo, year);
			lecturerInit(tempSemes->next->lecturers, tempSemes->next->semesterNo, year);
			courseInit(tempSemes->next->courses, tempSemes->next->semesterNo, year);
			tempSemes = tempSemes->next;
		}
		n++;
	}
}

void studentInit(Students*& st, string Class, string year) {
	Students* tempSt = st;
	ifstream stIn;
	string fileIn = "Yr" + year + "_Cl" + Class + "_StudentDB.txt";
	stIn.open(fileIn);
	if (stIn.is_open()) {
		int n;
		stIn >> n;
		while (n > 0) {
			if (!st) {
				st = new Students;
				stIn >> st->studentID;
				Accounts* acc = new Accounts;
				st->account = acc;
				st->account->uName = st->studentID;
				st->account->role = 1;
				accountInit(stIn, st->account);
				tempSt = st;
			}
			else {
				tempSt->next = new Students;
				stIn >> tempSt->next->studentID;
				tempSt->next->account = new Accounts;
				tempSt->next->account->uName = tempSt->next->studentID;
				tempSt->next->account->role = 1;
				accountInit(stIn, tempSt->next->account);
				tempSt = tempSt->next;
			}
			n--;
		}
	}
	stIn.close();
}
void classInit(Classes*& Class, string year) {
	Classes* tempClass = Class;
	int no = 1;
	ifstream classIn;
	string fileIn = "Yr" + year + "_ClassDB.txt";
	classIn.open(fileIn);
	if (classIn.is_open()) {
		int n;
		classIn >> n;
		while (n) {
			if (!Class) {
				Class = new Classes;
				Class->classno = no++;
				classIn >> Class->classID;
				//scheduleInit
				studentInit(Class->students, Class->classID, year);
				tempClass = Class;
			}
			else {
				tempClass->next = new Classes;
				tempClass->next->classno = no++;
				classIn >> tempClass->next->classID;
				studentInit(tempClass->next->students, tempClass->next->classID,year);
				//scheduleInit
				tempClass = tempClass->next;
			}
			n--;
		}
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