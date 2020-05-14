#ifndef _FUNCTION_H_
#define _FUNCTION_H_
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS 1
#endif

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>
using namespace std;
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
struct Date {
	int day, month, year;
};

struct Accounts
{
    char* pwd = NULL;  //(sha256 if possible)
    char* uName = NULL; // = ID
    short int role = (int)uName[0] - 48;
    string lastname, firstname;
    char gender[3]; //Female Male, Prefer not to say -> F,M,O
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

struct SessionStatus
{
    short int sessionNo; //11 12 21 22 31 32  week_session
    bool status;
    SessionStatus* next = NULL;
};
/*
struct WeeklyStatus {
	SessionStatus* sessions = nullptr;
	WeeklyStatus* next = nullptr;
};*/
struct AttendanceStatus
{
    string courseName;
    SessionStatus* sessions = NULL; //the amount of sessions will be academicYear->semester->course->dateOfWeek(1) * 11
    AttendanceStatus* next = NULL;
    //WeeklyStatus week[11];
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
};

struct CheckinCourse
{
    int bitweek;
    string courseID;
    //int status;
    CheckinCourse *next;
};
struct Students
{
    string studentID;
    Accounts* account = NULL;
    Scoreboards* scoreboards = NULL;
    AttendanceStatus* attendanceStatus = NULL;

    int Status;
    ///1  in class
    ///0  not available
    ///-1 removed to another class
    ///-2 kicked

    string schedule[6][4];
   CheckinCourse *checkincourse=NULL;
    Students* next = NULL;

};
struct OutsideStudent
{
    string studentID;
    string classID;
    OutsideStudent* next=NULL;

};
int numberOfDay(Date x, Date y);

struct CourseClass
{
    string classID;
    Students* students = NULL;
    long int BitAttend=0;
    Date startDate, endDate;
    CourseClass *next;
    OutsideStudent* Outsider=NULL;
    int DayInWeek;
    int AtNth;
};
struct Courses
{

    short int courseno;
    string courseID;	//them course id
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
    Classes* next = NULL;
    string schedule[6][4];

};

struct CourseClass0 {
	short int no, classNo, courseNo, studentNo;
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
    short int year;  //Ex: 1920 2021;
    Semesters* semesters = NULL;
    Classes* classes = NULL;
    AcademicYears* next = NULL;

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





#pragma region Initialization

#pragma endregion

#pragma region All roles
int login(char* user, char* pwd, Accounts* accountList); //1 2 3 -1          -> 2. 3. 4. 5.    tao curAcc
void showMenu(int role);
void viewProfile(Accounts* curAcc);
bool changePwd(char* newPwd, Accounts* accountList);
bool logout(Accounts* curAcc);
#pragma endregion

#pragma region Academic Staff
int CheckStatusStudent(string studentID,string classID, Classes* &Class);


#pragma region Class
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




#pragma endregion

#pragma region Scoreboard

#pragma endregion

#pragma region Attendance list

#pragma endregion

#pragma endregion
/*void importAClassFromCsvFile(AcademicStaff* staff, Classes*& aClass, ifstream fin);
void addAStudentToAClass(AcademicStaff* staff, Students*& aStudent, Classes*& aClass);
void editAStudent(AcademicStaff* staff, Classes*& aClass);
void removeAStudent(AcademicStaff* staff, Classes*& aClass);
void changeClassForStudents(AcademicStaff* staff, Classes*& oldClass, Classes*& newClass);
void viewListOfClasses(AcademicStaff* staff, Classes* classes);
void viewListOfStudentsInAClass(AcademicStaff* staff, Classes* aClass);*/
#pragma region Lecturer

#pragma endregion

#pragma region Student
void viewScoreCourse(Students *student,string courseID,string studentID);
void viewSchedule(Students* student);
void viewCheckIn(CheckinCourse *checkincourse, int week);
bool Tick(int week, string courseID,CheckinCourse* &checkincourse )
#pragma endregion
#endif

/*

All roles
	1. Login
	2. Show menu
	3. View profile info
	4. Change password
	5. Logout
Academic staff:
	Class
		6. Import students from a csv file.     -> void InputStudents(ifstream& f,    close right after importing
				Remember to create student accounts based on their Student ID and their DoB.
		7. Manually add a new student to a class.
				For example, there is a new student enrolled in 18CLC6. Remember to create a student account based on his/her Student ID and their DoB.
		8. Edit an existing student.
		9. Remove a student.
		10. Change students from class A to class B
		11. View list of classes.
		12. View list of students in a class.
	Course
		13. Create / update / delete / view academic years (2018-2019), and semesters (Fall).
		14. From a semester, import courses such as CTT008, CTT010 from a csv file.
			The csv file should include columns such as No (1), Course ID (CTT008),
			Course Name (Programming Techniques), Class (18CLC6),
			LecturerAccount (nhminh), Start Date (2019-01-07), End Date
			(2019-04-13), Day of Week (Wed), Start Hour:Minute (08:00), and End Hour:Minute (11:00), Room (I33).
			By default, all students in the mentioned classes will be enrolled to imported courses.
		15. Manually add a new course.
		16. Edit an existing course.
		17. Remove a course.
		18. Remove a specific student from a course.
			For example, by default all students of 18CLC are enrolled in course
			CTT008, but because of a private reason, student Nguyen Van A is dropped from CTT008.
		19. Add a specific student to a course.
			For example, student 1753001 enrolls in CTT008 to improve his previous result.
		20. View list of courses in the current semester.
		21. View list of students of a course.
		22. View attendance list of a course.
		23. Create / update / delete / view all lecturers.
	Scoreboard:
		24. Search and view the scoreboard of a course.
		25. Export a scoreboard to a csv file.
	Attendance list:
		26. Search and view attendance list of a course.
		27. Export a attendance list to a csv file.
Lecturer:
		28. View list of courses in the current semester.
		29. View list of students of a course.
		30. View attendance list of a course.
		31. Edit an attendance.
		32. Import scoreboard of a course (midterm, final, lab, bonus) from a csv file.
		33. Edit grade of a student
		34. View a scoreboard
Student:
		35. Check-in.
		36. View check-in result.
		37. View schedules.
		38. View his/her scores of a course.
*/