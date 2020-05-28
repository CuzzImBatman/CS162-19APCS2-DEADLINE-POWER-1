#ifndef _FUNCTION_H_
#define _FUNCTION_H_
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS 1
#endif

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "sha256.h"
#include <stdio.h>

using namespace std;
#pragma region Naming rule
/*
struct: StructName
variables, functions: variableName, functionName
const: CONST
plural form to indicate a list, singular fomr to indicate an attribute of a subject, structs are plural;
*/
#pragma endregion
#pragma region Database Structure
/*
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
	string day, month, year;
};
struct Accounts
{

	SHA256_CTX pwd;
    string uName;
    short int role;
    string lastname, firstname;
    char gender; //Female Male, Prefer not to say -> F,M,O
    Date* doB = NULL;
};

struct Scoreboards
{
    string courseName; //the course that this list belongs to
	string courseID;
	string midtermScore = "//", finalScore = "//", labScore = "//", bonusScore = "//";
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

struct CheckinCourse
{
    int bitweek=0;
    string courseID;
    CheckinCourse *next=NULL;
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

};

struct Classes
{
    short int classno;
    string classID;
    Students* students = NULL;
    Classes* next = NULL;
    string schedule[6][4];
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
#pragma endregion

#pragma region Function Prototypes
#pragma region Initialization
void accountInit(ifstream& fin, Accounts*& acc);

void courseInit(Courses*& course, char semes, string year, Classes*& Class);
void lecturerInit(Lecturers*& lec, char semes, string year);
void staffInit(Staffs*& staff, char semes, string year);
void semesterInit(Semesters*& semes, string year, Classes*& Class);
void scheduleInit(string schedule[6][4], ifstream& in);

void studentInit(Students*& st, string Class, string year);
void classInit(Classes*& Class, string year);
void InitClassToCourse(Classes*& Class,  ifstream& courseIn, Courses*& course ,string year);

void academicYearInit(AcademicYears*& year);
#pragma endregion
#pragma region tool
Classes* findClass(Classes* Class, string ClassID);
Students* findStudent(Students* st, string stID);
Semesters* findSemester(Semesters* semes, char no);
Semesters* FindSemester(AcademicYears*& AY, AcademicYears*& ay);
Courses* findCourse(Courses* course, string ID);
CourseClass* findCL(CourseClass* CL, string classID);
AcademicYears* inputYear(AcademicYears* year, Courses*& course);
int CheckStatusStudent(string studentID, string classID, Classes*& Class);
void AddCheckInCourse(Students*& st, string courseID);
void AddScoreBoardCourse(Students*& st, string courseID);
bool ComparePwd(SHA256_CTX a, SHA256_CTX b);
void DeleteScoreBoardStudent(Students*& ST);
void DeleteCheckinCourseStudent(Students*& St);
void DeleteStudentFromCourses(string studentID, string classID, Courses*& course);
int DeleteABit(int bit, int x);
void RemoveFile(string s);
#pragma endregion

#pragma region All roles
int login(AcademicYears* year, Accounts*& acc, string pwd);
void showClassOptions(AcademicYears*& year);
void showCourseOptions(AcademicYears*& year);
void showScoreboardOptions(AcademicYears*& year);
void showAttendanceListOptions(AcademicYears*& year);
void showMenu(Accounts*& acc, AcademicYears*& year);
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
void removeAStudent(Classes*& aClass,Courses*& course,char semes,string year);
void changeClassForStudents(Classes*& classes, Courses*& course, char semes, string year);
void viewListOfClasses(AcademicYears* aYear);
void viewListOfStudentsInAClass(AcademicYears* aYear);

void createLecturer(AcademicYears* year);
void updateLecturer(AcademicYears* year);
void deleteLecturer(AcademicYears* year);
void viewLecturer(AcademicYears* year);

#pragma endregion

#pragma region Course
void createAcademicYear(AcademicYears*& year);
void updateAcademicYear(AcademicYears* year);
void staff_deleteAcademicYear(AcademicYears*& year);
void viewAcademicYear(AcademicYears* year);

void EditCourse(AcademicYears* year);
void RemovedStudentFromCourseClass(AcademicYears* year);
void AddStudentToCourseClass(AcademicYears* year);
void DeleteCourse(AcademicYears* year);
void AddCourse(AcademicYears*& year);
//void InitCourse(Courses *&course,Classes* Class);

///
void AddCourseToStudent(Students* &ST, Courses*& course,int DayInWeek,int AtNth , string year);
void AddCourseToClass(Classes*& Class, Courses*& course,int DayInWeek,int AtNth, string year);
void AddClassToCourse(Classes* &Class,string classID,Courses* &course,string courseID,string year);
void RemoveCourseOfScheduleStudent(string schedule[6][4],string courseID);
void EditScheduleCourseOfClass(Courses*&course,string classID,string courseID,Classes *&Class);
void EditCourseId(Courses*& course,string NewID, Classes*& Class);
void EditCourseName(Courses*& course, string NewName, Classes*& Class);
void EditCourseroom(Courses*& course,string courseID,string room);
void EditCourseLecture(Courses*& course,string name,string courseID);
void EditDateOfCL(Courses*& course, string classID, string courseID,string year);
void DeleteCourseOfCheckin(CheckinCourse* &checkincourse,string courseID);
void DeleteCourseScheduleStudent(Students *&student, Courses*& course,OutsideStudent* &Outsider,Classes *&Class);
void DeleteCourseScheduleClass(Classes *&Class,string courseID,string classID);
void UpdateBitAttend(string classID, Courses*& course);

void viewCourseOfSemester(AcademicYears* AcaYear);
//void viewStudentsOfCourse();


#pragma endregion

#pragma region Scoreboard
void DeleteScoreBoardOfCourse(Students* &ST, string courseID);
void DeleteScoreBoardOfCourseStudent(Students*& ST, string courseName);
#pragma endregion

#pragma region Attendance list
void View_StudentList_Course(AcademicYears* AcaYear);
void View_Attendance_List(AcademicYears* AcaYear);
#pragma endregion

#pragma endregion
#pragma region Lecturer
void Edit_Attend_List(AcademicYears* year);
void Edit_ScoreBoard_Student(AcademicYears* year);
void View_Scoreboard(AcademicYears* year);
#pragma endregion
#pragma region Student
void viewScoreCourse(Students *student);
void viewSchedule(Students* student);
void viewCheckIn(CheckinCourse *checkincourse);
void Tick(Students* student);
void FillCheckinCourse(Students*& student);
#pragma endregion

#pragma region Finalization
void writeAccounts(ofstream& fout, Accounts* acc);

void writeCourses(Courses* course, char semes, string year);
void writeLecturers(Lecturers* lect, char semes, string year);
void writeStaffs(Staffs* staff, char semes, string year);
void writeSemesters(Semesters* semes, string year);

void writeScoreBoard(Students* st, string year);
void writeCheckIn(Students* st, string year);
void writeStudents(Students* st, string Class, string year);
void writeClasses(Classes* Class, string year);

void writeAcademicYears(AcademicYears* year);
#pragma endregion
#pragma region PointersDeletion
void deleteCourses(Courses*& course);
void deleteLecturers(Lecturers*& lect);
void deleteStaffs(Staffs*& staff);
void deleteSemesters(Semesters*& semes);

void deleteStudents(Students*& st);
void deleteClasses(Classes*& Class);

void deleteAcademicYears(AcademicYears*& year);

void DeleteCheckinCourseStudent(Students*& St);
void DeleteScoreBoardStudent(Students*& ST);
void DeleteStudentFromCourses(string studentID, string classID, Courses*& course);
#pragma endregion
#pragma endregion
void RemoveFile(string s);
#endif
#pragma region Tasks
/*
All roles
			1. Login
			2. Show menu
			3. View profile info
			4. Change password
			5. Logout
Academic staff:
	Class
			6. Import students from a csv file.
			7. Manually add a new student to a class.
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
#pragma endregion
