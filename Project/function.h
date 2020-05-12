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
	Accounts* next=NULL;
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

struct AttendanceStatus
{
    string courseName;
   // SessionStatus* sessions = NULL;
    AttendanceStatus* next = NULL;
    //WeeklyStatus week[11];
    //short int present, absent;	
};

struct ViewCheckin
{
    int week;
    string viewWeek[6][4];
    ViewCheckin *next;
};

struct CheckinCourse
{
    int bitweek;
    string courseID;
    int status;
    CheckinCourse *next;
};

struct Students
{
    string studentID;
    Accounts* account = nullptr;
    Scoreboards* scoreboards = NULL;
    AttendanceStatus* attendanceStatus = NULL;

    int Status;
    ///1  in class
    ///0  not avaialble
    ///-1 removed to another class
    ///-2 kicked
    ViewCheckin *checkinList;
    string schedule[6][4];
    CheckinCourse *checkincourse;
    Students* next = NULL;
};

struct OutsideStudent
{
    string studentID;
    string classID;
    OutsideStudent* next;
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
	CourseClass* next;
};

struct Courses
{
    string courseno;
	string courseID;
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
};
#pragma endregion

#pragma region Initialization
void accountInit(ifstream& fin, Accounts*& acc);

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
void showClassOptions();
void showCourseOptions();
void showScoreboardOptions();
void showAttendanceListOptions();
void showMenu(short int role);
void changePwd(Accounts*& acc);
void viewProfile(Accounts* acc);
void logout(Accounts*& acc);
#pragma endregion

#pragma region Academic Staff

#pragma region Class
void importAClassFromCsvFile(Staffs* staff, Classes*& aClass, ifstream fin);
void addAStudentToAClass(Staffs* staff, Students*& aStudent, Classes*& aClass);
void editAStudent(Staffs* staff, Classes*& aClass);
void removeAStudent(Staffs* staff, Classes*& aClass);
void changeClassForStudents(Staffs* staff, Classes*& oldClass, Classes*& newClass);
void viewListOfClasses(Staffs* staff, Classes* classes);
void viewListOfStudentsInAClass(Staffs* staff, Classes* aClass);
#pragma endregion

#pragma region Course

#pragma endregion

#pragma region Scoreboard

#pragma endregion

#pragma region Attendance list

#pragma endregion

#pragma endregion

#pragma region Lecturer

#pragma endregion

#pragma region Student

#pragma endregion
#endif