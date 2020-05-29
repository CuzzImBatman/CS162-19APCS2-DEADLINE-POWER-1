#include "function.h"
#include "sha256.h"
void accountInit(ifstream& fin, Accounts*& acc) {
	if (!acc)
		acc = new Accounts;
	int test;

	fin >>hex>> test;
	if(test!= 0)
	{
		acc->pwd.state[0] = test;
		for (int i = 1; i < 8; i++)
			fin >>hex>> acc->pwd.state[i];

	}
	fin >> acc->firstname;
	fin.ignore(10, '\n');
	getline(fin, acc->lastname);
	fin >> acc->gender;
	acc->doB = new Date;
	fin >> acc->doB->day;
	fin >> acc->doB->month;
	fin >> acc->doB->year;
	if (test) return;
	string pwd = acc->doB->day + acc->doB->month + acc->uName;
	sha256_init(&acc->pwd);
	sha256_update(&acc->pwd ,pwd, pwd.length());
}

void courseInit(Courses*& course, char semes, string year,Classes*& Class) {

	ifstream courseIn;
	char no = '1';
	string fileIn = "Yr" + year + "_Sem" + semes + "_CourseDB.txt";
	courseIn.open(fileIn);
	if (courseIn.is_open()) {
		int n;
		courseIn >> n;
		while (n) {
			    Courses* tempCourse = new Courses;
			 	courseIn >> tempCourse->courseID;
				courseIn.ignore(10, '\n');
				getline(courseIn, tempCourse->courseName);
				courseIn >> tempCourse->LectureName;
				tempCourse->courseclass = NULL;
				int m;
				courseIn >> m;
				for (int i = 0; i < m; ++i)
					InitClassToCourse(Class, courseIn, tempCourse,year);
				tempCourse->next = course;
				course = tempCourse;

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
void semesterInit(Semesters*& semes, string year, Classes*& Class){
	Semesters* tempSemes = semes;
	char n = '1';
	while (n < '4') {
		if (!semes) {
			semes = new Semesters;
			semes->semesterNo = n;
			staffInit(semes->staffs, semes->semesterNo, year);
			lecturerInit(semes->lecturers, semes->semesterNo, year);
			courseInit(semes->courses, semes->semesterNo, year, Class);

			tempSemes = semes;
		}
		else {
			tempSemes->next = new Semesters;
			tempSemes->next->semesterNo = n;
			staffInit(tempSemes->next->staffs, tempSemes->next->semesterNo, year);
			lecturerInit(tempSemes->next->lecturers, tempSemes->next->semesterNo, year);
			courseInit(tempSemes->next->courses, tempSemes->next->semesterNo, year, Class);
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
				for (int i = 0; i < 6; i++)
					for (int j = 0; j < 4; j++)
						st->schedule[i][j] = "//";
				tempSt = st;

			}
			else {
				tempSt->next = new Students;
				stIn >> tempSt->next->studentID;
				tempSt->next->account = new Accounts;
				tempSt->next->account->uName = tempSt->next->studentID;
				tempSt->next->account->role = 1;
				accountInit(stIn, tempSt->next->account);
				for (int i = 0; i < 6; i++)
					for (int j = 0; j < 4; j++)
						tempSt->next->schedule[i][j] = "//";

				tempSt = tempSt->next;
			}
			n--;
		}
	}
	stIn.close();
}
void scheduleInit(string schedule[6][4],ifstream& in)
{

	for (int j = 0; j < 4; j++)
		for (int i = 0; i < 6; i++)
			 schedule[i][j]="//";
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
				scheduleInit(Class->schedule,classIn);
				studentInit(Class->students, Class->classID, year);
				tempClass = Class;
			}
			else {
				tempClass->next = new Classes;
				tempClass->next->classno = no++;
				classIn >> tempClass->next->classID;
				scheduleInit(tempClass->next->schedule, classIn);
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
			semesterInit(year->semesters, year->year, year->classes);
			tempYear = year;
		}
		else {
			tempYear->next = new AcademicYears;
			yearIn >> tempYear->next->year;
			classInit(tempYear->next->classes, tempYear->next->year);
			semesterInit(tempYear->next->semesters, tempYear->next->year, tempYear->next->classes);
			tempYear = tempYear->next;
		}
		n--;
	}
	yearIn.close();
}
void InitClassToCourse(Classes*& Class, ifstream& courseIn, Courses*& course,  string year) {


	CourseClass* courseclass = new CourseClass;

	courseIn >> courseclass->startDate.day;
	courseIn >> courseclass->startDate.month;
	courseIn >> courseclass->startDate.year;
	courseIn >> courseclass->endDate.day;
	courseIn >> courseclass->endDate.month;
	courseIn >> courseclass->endDate.year;
	string temp;
	courseIn >> temp;
	switch (temp[1]) { //Mo Tu We Th Fr Sa
	case 'o':
		courseclass->DayInWeek = 0;
		break;
	case 'u':
		courseclass->DayInWeek = 1;
		break;
	case 'e':
		courseclass->DayInWeek = 2;
		break;
	case 'h':
		courseclass->DayInWeek = 3;
		break;
	case 'r':
		courseclass->DayInWeek = 4;
		break;
	case 'a':
		courseclass->DayInWeek = 5;
		break;
	}
	int hour, minute;
	courseIn >> hour >> minute;
	switch (hour) {
	case 7:
		courseclass->AtNth = 0;
		break;
	case 9:
		courseclass->AtNth = 1;
		break;
	case 13:
		courseclass->AtNth = 2;
		break;
	case 15:
		courseclass->AtNth = 3;
		break;
	}

	int no;
	courseIn >> courseclass->classID;
	courseIn >> no;
	courseclass->studentcourse = NULL;

	Classes* curCL = findClass(Class, courseclass->classID);

	if (!no)
	{
		AddCourseToClass(curCL, course, courseclass->DayInWeek, courseclass->AtNth, year);
		Students* st = curCL->students;
		while (st)
		{
			StudentCourse* OS = new StudentCourse;
			OS->studentID = st->studentID;
			OS->classID = curCL->classID;
			OS->next = courseclass->studentcourse;
			courseclass->studentcourse = OS;
			st = st->next;
		}

	}
	for (int i = 0; i < no; i++)
	{
		StudentCourse* OS = new StudentCourse;
		courseIn >> OS->studentID;
		courseIn >> OS->classID;
		OS->next = courseclass->studentcourse;
		courseclass->studentcourse = OS;
		Classes* cl = findClass(Class, OS->classID);
		Students* st = findStudent(cl->students, OS->studentID);
		AddCourseToStudent(st, course, courseclass->DayInWeek, courseclass->AtNth,year);

	}
	courseIn >> course->room;

	curCL->schedule[courseclass->DayInWeek][courseclass->AtNth] = course->courseID;
	CourseDetail* CD = new CourseDetail;
	CD->courseID = course->courseID;
	CD->coursename = course->courseName;
	CD->next = curCL->CD;
	CD->room = course->room;
	curCL->CD = CD;
	Students* curST = curCL->students;
	courseclass->students = curCL->students;

	
	courseclass->next = course->courseclass;
	course->courseclass = courseclass;

}