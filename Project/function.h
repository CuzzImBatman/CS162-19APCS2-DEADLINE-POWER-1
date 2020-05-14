#ifndef FUNCTION_H
#define FUNCTION_H
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS 1
#endif

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

#pragma region Rules and Plans
/* Naming rule:
	struct: StructName
	variable, function: variableName, functionName
	const: CONST
	plural to indicate a list, single to indicate an attribute of a subject, structs are plural;
*/
/*  Database Structure

							  +-->[Staffs]
							  |
							  +-->[Lecturers]
							  |
[AcademicYears]+-->[Semesters]+-->[Courses]+-->[CourseClass]----+
			   |					   	   		                |
			   +<-----------------------------------------------+
			   |
			   |                            	          +-->[AttendanceStatus]
			   |			      	                      |
			   +-->[Classes]+------------------>[Students]+-->[Scoreboard]
Outsider
*/
#pragma endregion

#pragma region Structs
struct Date {
	int day, month, year;
};
struct Accounts
{
    string pwd;  //(sha256 if possible)
    string uName;
	short int role;
    string lastname, firstname;
    char gender; //Female Male, Prefer not to say -> F,M,O
    Date* doB = NULL;
};

struct Scoreboards
{
    string courseName; //the course that this list belongs to
    int midtermScore, finalScore, labScore, bonusScore;
    Scoreboards* next = NULL;
};

struct Staffs
{
    Accounts* account = NULL;
    Staffs* next = NULL;
};
struct Lecturers
{
    Accounts* account = NULL;
    Lecturers* next = NULL;
};
/*struct SessionStatus
{
    short int sessionNo; //11 12 21 22 31 32  week_session
    bool status;
    SessionStatus* next = NULL;
};
struct WeeklyStatus {
	SessionStatus* sessions = nullptr;
	WeeklyStatus* next = nullptr;
};*/

/*struct AttendanceStatus
{
    string courseName;
   // SessionStatus* sessions = NULL;
    AttendanceStatus* next = NULL;
    //WeeklyStatus week[11];
<<<<<<< HEAD
    //short int present, absent;



    //Khi input: academicYear->semester->course->courseclass      student->AttendanceStatus->sessions->status = true;
    /*Khi truy xuat:
        temp = academicYear->semester->course->       student
        while (temp->next != nullptr){
    		temp2 = temp->AttendanceStatus->sessions;
    		while (temp2->next != nullptr){
    			cout << temp2->sessionNo << ': ' << temp2->sessionStatus << endl;
    			temp2=temp2->next;
    		}
    		temp= temp->next;
    	}
    */
=======
    //short int present, absent;	
};*/

struct ViewCheckin
{
    int week;
    string viewWeek[6][4];
    ViewCheckin *next;
>>>>>>> master
};

struct CheckinCourse
{
    int bitweek;
    string courseID;
<<<<<<< HEAD
    //int status;
    CheckinCourse *next;
=======
    int status;
    CheckinCourse *next = NULL;
>>>>>>> master
};

struct Students
{
    string studentID;
<<<<<<< HEAD
    Accounts* account = NULL;
=======
    Accounts* account = nullptr;
>>>>>>> master
    Scoreboards* scoreboards = NULL;
//    AttendanceStatus* attendanceStatus = NULL;

    int Status;
    ///1  in class
    ///0  not available
    ///-1 removed to another class
    ///-2 kicked
<<<<<<< HEAD

    string schedule[6][4];
   CheckinCourse *checkincourse=NULL;
=======
    ViewCheckin *checkinList = NULL;
    string schedule[6][4];
    CheckinCourse *checkincourse = NULL;
>>>>>>> master
    Students* next = NULL;
};

struct OutsideStudent
{
    string studentID;
    string classID;
<<<<<<< HEAD
    OutsideStudent* next=NULL;

=======
    OutsideStudent* next = NULL;
>>>>>>> master
};

int numberOfDay(Date x, Date y);

struct CourseClass
{
    string classID;
    Students* students = NULL;
    long int BitAttend=0;
    Date startDate, endDate;
    OutsideStudent* Outsider=NULL;
    int DayInWeek;
    int AtNth;
	CourseClass* next = NULL;
};

struct Courses
{
    string courseno;
	string courseID;
	string courseName;
    CourseClass *courseclass;
    string room;
    string LectureName;
    Courses* next = NULL;
    /*Date startDate, endDate;
    int days= numberOfDay(startDate,endDate);
    int weeks=days/7;
    short int dateOfWeek[11][6]; //Ex: CS162: {0000;1000;0000;0000;0000;0001} -> first shift of Tue and last shift of Sat
    short int checkinList[11][6]; //Ex: CS162: {0000;1000;0000;0000;0000;0001} -> first shift of Tue and last shift of Sat
    memset(checkin,11,6);
    string room;
    Lecturers* lecturers = nullptr;
    Students* students = nullptr;
    ;*/
};

struct Classes
{
    short int classno;
    string classID;
    Students* students = NULL;
    string schedule[6][4]; //init
	Classes* next = NULL;
};
struct Semesters
{
    char semesterNo;
    Courses* courses = NULL;
    Lecturers* lecturers = NULL;
    Staffs* staffs = NULL;
    Semesters* next = NULL;
};
struct AcademicYears
{
    string year;
    Semesters* semesters = NULL;
    Classes* classes = NULL;
    AcademicYears* next = NULL;
<<<<<<< HEAD

};
/*
struct Account {
	char* pwd;  //(sha256 if possible)
	char* uName; // = ID
	short int role = (int)uName[0] - 48;
	char* lastname, * firstname;
	int gender;
	Date* doB;

};*/



=======
};
#pragma endregion

#pragma region Initialization
void accountInit(ifstream& fin, Accounts*& acc);
>>>>>>> master

void courseInit(Courses*& course, char semes, string year);
void lecturerInit(Lecturers*& lec, char semes, string year);
void staffInit(Staffs*& staff, char semes, string year);
void semesterInit(Semesters*& semes, string year);

void studentInit(Students*& st, string Class, string year);
void classInit(Classes*& Class, string year);

void academicYearInit(AcademicYears*& year);
#pragma endregion

#pragma region All roles
int login(AcademicYears* year, Accounts*& acc);
void showClassOptions(AcademicYears*& year);
void showCourseOptions(AcademicYears*& year);
void showScoreboardOptions(AcademicYears*& year);
void showAttendanceListOptions(AcademicYears*& year);
void showMenu(short int role, AcademicYears*& year);
void changePwd(Accounts*& acc);
void viewProfile(Accounts* acc);
void logout(Accounts*& acc);

#pragma endregion

#pragma region Academic Staff
int CheckStatusStudent(string studentID,string classID, Classes* &Class);



#pragma region Class
<<<<<<< HEAD
/*void importAClassFromCsvFile(AcademicStaff* staff, Classes*& aClass, ifstream fin);
void addAStudentToAClass(AcademicStaff* staff, Students*& aStudent, Classes*& aClass);
void editAStudent(AcademicStaff* staff, Classes*& aClass);
void removeAStudent(AcademicStaff* staff, Classes*& aClass);
void changeClassForStudents(AcademicStaff* staff, Classes*& oldClass, Classes*& newClass);
void viewListOfClasses(AcademicStaff* staff, Classes* classes);
void viewListOfStudentsInAClass(AcademicStaff* staff, Classes* aClass);*/
void RemoveStudentFromClass(Classes* &Class,string classID, string studentID);
void UpdateBitAttend(string classID,Courses *&course);
void ChangeStudentFromClassAtoB(Classes* &Class,string classAID, string classBID,string studentID,Courses *&course);

#pragma endregion

#pragma region Course
void EditCourse(Courses*& course,Classes *&Class);
void RemovedStudentFromCourseClass(Courses*& course,string courseID,string classID,string studentID );
bool AddStudentToCourseClass(Courses*& course,Classes * &Class,string courseID,string classID, string classIDOut,string studentID );
bool DeleteCourse(Courses*& course,string courseID,Classes * &Class);
void AddCourse(Courses *&course,Classes* Class);
void InitCourse(Courses *&course,Classes* Class);

///
void AddCourseToStudent(Classes*& Class,string studentID,string classID,string courseID,int DayInWeek,int AtNth);
void AddCourseToClass(Classes*& Class,string classID,string courseID,int DayInWeek,int AtNth);
void AddClassToCourse(Classes* &Class,string classID,Courses* &course,string courseID);
void RemoveCourseOfScheduleStudent(string schedule[6][4],string courseID);
void EditScheduleCourseOfClass(Courses*&course,string classID,string courseID,Classes *&Class);
void EditCourseId(Courses*& course,string NewID,string  OldID);
void EditCourseroom(Courses*& course,string courseID,string room);
void EditCourseLecture(Courses*& course,string name,string courseID);
void DeleteCourseOfCheckin(CheckinCourse* &checkincourse,string courseID);
void DeleteCourseScheduleStudent(Students *&student,string courseID,OutsideStudent* &Outsider,Classes *&Class);
void DeleteCourseScheduleClass(Classes *&Class,string courseID,string classID);




=======
void importAClassFromCsvFile(Classes*& aClass);
void addAStudentToAClass(Classes*& aClass);
void editAStudent(Classes*& aClass);
void removeAStudent(Classes*& aClass);
void changeClassForStudents(Classes*& classes);
void viewListOfClasses(Classes* aClass);
void viewListOfStudentsInAClass(Classes* aClass);

void createLecturer(AcademicYears* year);
void updateLecturer(AcademicYears* year);
void deleteLecturer(AcademicYears* year);
void viewLecturer(AcademicYears* year);
#pragma endregion

#pragma region Course
void viewCourseOfSemester(AcademicYears* AcaYear);
void viewStudentsOfCourse();
>>>>>>> master
#pragma endregion

#pragma region Scoreboard

#pragma endregion

#pragma region Attendance list

#pragma endregion

#pragma endregion
<<<<<<< HEAD
/*void importAClassFromCsvFile(AcademicStaff* staff, Classes*& aClass, ifstream fin);
void addAStudentToAClass(AcademicStaff* staff, Students*& aStudent, Classes*& aClass);
void editAStudent(AcademicStaff* staff, Classes*& aClass);
void removeAStudent(AcademicStaff* staff, Classes*& aClass);
void changeClassForStudents(AcademicStaff* staff, Classes*& oldClass, Classes*& newClass);
void viewListOfClasses(AcademicStaff* staff, Classes* classes);
void viewListOfStudentsInAClass(AcademicStaff* staff, Classes* aClass);*/
=======

>>>>>>> master
#pragma region Lecturer

#pragma endregion

#pragma region Student
void viewScoreCourse(Students *student,string courseID,string studentID);
void viewSchedule(Students* student);
void viewCheckIn(CheckinCourse *checkincourse, int week);
bool Tick(int week, string courseID,CheckinCourse* &checkincourse )
#pragma endregion
#endif