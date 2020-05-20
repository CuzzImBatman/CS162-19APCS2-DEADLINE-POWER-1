#ifndef _FUNCTION_H_
#define _FUNCTION_H_
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS 1
#endif

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
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
/*
struct WeeklyStatus {
	SessionStatus* sessions = nullptr;
	WeeklyStatus* next = nullptr;
};*/
/*struct AttendanceStatus
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
    
};
*/


struct CheckinCourse
{
    int bitweek;
    string courseID;
    CheckinCourse *next;
};
struct Students
{
    string studentID;
    Accounts* account = NULL;
    Scoreboards* scoreboards = NULL;
    // AttendanceStatus* attendanceStatus = NULL;

    int Status = 1;
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
    CourseClass *next = NULL;
    OutsideStudent* Outsider=NULL;
    int DayInWeek;
    int AtNth;
};
struct Courses
{

    string courseno;
    string courseID;	//them course id
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
    string year;  //Ex: 1920 2021;
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
void accountInit(ifstream& fin, Accounts*& acc);

void courseInit(Courses*& course, char semes, string year, Classes*& Class);
void lecturerInit(Lecturers*& lec, char semes, string year);
void staffInit(Staffs*& staff, char semes, string year);
void semesterInit(Semesters*& semes, string year, Classes*& Class);
void scheduleInit(string schedule[6][4], ifstream& in);

void studentInit(Students*& st, string Class, string year);
void classInit(Classes*& Class, string year);
void InitClassToCourse(Classes*& Class,  ifstream& courseIn, Courses*& course);

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
void importAClassFromCsvFile(Classes*& aClass);
void addAStudentToAClass(Classes*& aClass);
void editAStudent(Classes*& aClass);
void removeAStudent(Classes*& aClass);
void changeClassForStudents(Classes*& classes, Courses*& course);
void viewListOfClasses(Classes* aClass);
void viewListOfStudentsInAClass(Classes* aClass);

void createLecturer(AcademicYears* year);
void updateLecturer(AcademicYears* year);
void deleteLecturer(AcademicYears* year);
void viewLecturer(AcademicYears* year);

#pragma endregion

#pragma region Course
void EditCourse(Courses*& course,Classes *&Class);
void RemovedStudentFromCourseClass(Courses*& course, Classes*& Class);
void AddStudentToCourseClass(Courses*& course,Classes * &Class );
void DeleteCourse(Courses*& course,Classes * &Class);
void AddCourse(Courses *&course,Classes* Class);
//void InitCourse(Courses *&course,Classes* Class);

///
void AddCourseToStudent(Classes*& Class,string studentID,string classID,string courseID,int DayInWeek,int AtNth);
void AddCourseToClass(Classes*& Class,string classID,string courseID,int DayInWeek,int AtNth);
void AddClassToCourse(Classes* &Class,string classID,Courses* &course,string courseID);
void RemoveCourseOfScheduleStudent(string schedule[6][4],string courseID);
void EditScheduleCourseOfClass(Courses*&course,string classID,string courseID,Classes *&Class);
void EditCourseId(Courses*& course,string NewID,string  OldID);
void EditCourseroom(Courses*& course,string courseID,string room);
void EditCourseLecture(Courses*& course,string name,string courseID);
void EditDateOfCL(Courses*& course, string classID, string courseID);
void DeleteCourseOfCheckin(CheckinCourse* &checkincourse,string courseID);
void DeleteCourseScheduleStudent(Students *&student,string courseID,OutsideStudent* &Outsider,Classes *&Class);
void DeleteCourseScheduleClass(Classes *&Class,string courseID,string classID);
void UpdateBitAttend(string classID, Courses*& course);

void viewCourseOfSemester(AcademicYears* AcaYear);
//void viewStudentsOfCourse();


#pragma endregion

#pragma region Scoreboard

#pragma endregion

#pragma region Attendance list
void View_StudentList_Course(Courses* course, Classes* Class);
void View_Attendance_List(Courses* course, Classes* Class);
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
void viewScoreCourse(Students *student);
void viewSchedule(Students* student);
void viewCheckIn(CheckinCourse *checkincourse);
void Tick( CheckinCourse*& checkincourse);
void FillCheckinCourse(Students*& student);
#pragma endregion
#endif
#pragma region tool
Classes* findClass(Classes* Class, string ClassID);
	
Students* findStudent(Students * st, string stID);

Semesters* findSemester(Semesters * semes, char no);

Courses* findCourse(Courses * course, string ID);

CourseClass* findCL(CourseClass* CL, string classID);
int CheckStatusStudent(string studentID, string classID, Classes*& Class);
#pragma endregion
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
