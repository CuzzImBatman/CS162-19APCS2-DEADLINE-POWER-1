#ifndef _FUNCTION_H_
#define _FUNCTION_H_
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS 1
#endif

#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdio.h>
#include "sha256.h"

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
							  +-->[Staffs]+-->[Accounts]
							  |
							  +-->[Lecturers]+-->[Accounts]
							  |                             +-->(ClassID)
							  |								|
               +-->[Semesters]+-->[Courses]+-->[CourseClass]+-->[Students]	   +-->(StudentID)
			   |					   	   		            |				   |	
			   |                                            +-->[StudentCourse]+-->(ClassID)
[AcademicYears]+
			   |                          +-->[ChechinCourse]+-->(CoursesID)
	           |     	                  |
			   +-->[Classes]+-->[Students]+-->[Scoreboards]+-->(CourseID)
			                |			  |
							|			  +-->[Accounts]
							|			  |
							|			  +-->(StudentID)
							|
							+-->[CourseDetail]+-->(CourseID)
							|
							+-->(Schedule)

CourseClass is a legacy struct, CourseDetail and other relations between Classes, Students and Courses
have rendered CourseClass pretty much useless.
*/
#pragma endregion


#pragma region Structs
struct Date {
	string day = "", month = "", year = "";
};
struct Accounts
{
	SHA256_CTX pwd;
    string uName;
    short int role;
    string lastname, firstname;
    char gender; //Female Male, Prefer not to say -> F,M,O
    Date* doB = nullptr;
};

struct Scoreboards
{
	string courseName; //the course that this list belongs to
	string courseID;
	string midtermScore = "", finalScore = "", labScore = "", bonusScore = "";
	Scoreboards* next = nullptr;
};
struct CheckinCourse
{
	int bitweek = 0;
	string courseID, room;
	CheckinCourse* next = nullptr;
};
struct Students
{
	string studentID;
	Accounts* account = nullptr;
	Scoreboards* scoreboards = nullptr;

	int Status = 1;
	///1  in class
	///0  not available
	///-1 removed to another class
	///-2 kicked

	string schedule[6][4];
	CheckinCourse* checkincourse = nullptr;
	Students* next = nullptr;
};
struct CourseDetail
{
	string courseID, coursename, room;
	CourseDetail* next = nullptr;
};
struct Classes
{
	string classID;
	Students* students = nullptr;
	string schedule[6][4];
	CourseDetail* CD = nullptr;
	Classes* next = nullptr;
};

struct Staffs
{
    Accounts* account = nullptr;
    Staffs* next = nullptr;
};
struct Lecturers
{
    Accounts* account = nullptr;
    Lecturers* next = nullptr;
};
struct StudentCourse
{
	string classID;
    string studentID;
	StudentCourse* next = nullptr;
};
struct CourseClass
{
    string classID;
    Students* students = nullptr;
    Date startDate, endDate;
	StudentCourse* studentcourse = nullptr;
    int DayInWeek;
    int AtNth;
	CourseClass* next = nullptr;
};
struct Courses
{
   // string courseno;
    string courseID="";
    string courseName="";
    CourseClass *courseclass;
    string room="";
    string LectureName="";
    Courses* next =  nullptr;
}; 
struct Semesters
{
	char semesterNo;
	Courses* courses = nullptr;
	Lecturers* lecturers = nullptr;
	Staffs* staffs = nullptr;
	Semesters* next = nullptr;
};

struct AcademicYears
{
    string year;  //Ex: 1920 2021;
    Semesters* semesters = nullptr;
    Classes* classes = nullptr;
    AcademicYears* next = nullptr;
};
#pragma endregion


#pragma region Function Prototypes
#pragma region Initialization
void accountInit(ifstream& fin, Accounts*& acc);

void InitClassToCourse(Classes*& Class, ifstream& courseIn, Courses*& course, string year);
void courseInit(Courses*& course, char semes, string year, Classes*& Class);
void lecturerInit(Lecturers*& lec, char semes, string year);
void staffInit(Staffs*& staff, char semes, string year);
void semesterInit(Semesters*& semes, string year, Classes*& Class);
void scheduleInit(string schedule[6][4], ifstream& in);

void studentInit(Students*& st, string Class, string year);
void classInit(Classes*& Class, string year);

void academicYearInit(AcademicYears*& year);
#pragma endregion
#pragma region Subroutines
Classes* findClass(Classes* Class, string ClassID);
Students* findStudent(Students* st, string stID);
Semesters* findSemester(Semesters* semes, char no);
AcademicYears* findYear(AcademicYears* acaYear, string year);
Courses* findCourse(Courses* course, string ID);
CourseClass* findCL(CourseClass* CL, string classID);
bool smaller(int a, int b);
bool bigger(int a, int b);
bool checkDay(string& a, int x, bool(*compare)(int, int));
bool checkMonth(Date a);
bool checkYear(Date a);
int numberOfDay(Date x);
bool input(AcademicYears* AcaYear, Semesters*& semes, string& year);
AcademicYears* inputYear(AcademicYears* year, Courses*& course);
int DeleteABit(int bit, int x);
bool Is_empty(ifstream& in);


void showClassOptions(AcademicYears*& year);
void showCourseOptions(AcademicYears*& year);
void showScoreboardOptions(AcademicYears*& year);
void showAttendanceListOptions(AcademicYears*& year);

bool ComparePwd(SHA256_CTX a, SHA256_CTX b);

Students* listStudentsFromFile(string path);

void DeleteScoreBoardStudent(Students*& ST);
void DeleteCheckinCourseStudent(Students*& St);
void DeleteStudentFromCourses(string studentID, string classID, Courses*& course);

void FillCheckinCourse(Students*& student);

void RemoveFile(string s);
void staff_deleteClasses(Classes*& Class, string year);

Semesters* FindSemester(AcademicYears*& AY, AcademicYears*& ay);
void AddScoreBoardCourse(Students*& st, string courseID, string courseName);
void AddCheckInCourse(Students*& st, string courseID, string room);
void AddCourseToStudent(Students*& ST, Courses*& course, int DayInWeek, int AtNth, string year);
void AddCourseToClass(Classes*& Class, Courses*& course, int DayInWeek, int AtNth, string year);
void AddClassToCourse(Classes*& Class, string classID, Courses*& course, string courseID, string year);

void Edit_CourseName_Student(Students* st, string NewName, string OldName);
void EditCourseName(Courses*& course, string NewName, Classes*& Class);
void EditDateOfCL(Courses*& course, string classID, string courseID, string year);
void EditCourseLecture(Courses*& course, string name, string courseID);
int CheckStatusStudent(string studentID, string classID, Classes*& Class);
void EditScheduleCourseOfClass(Courses*& course, string classID, string courseID, Classes*& Class);
void EditCourseroom(Courses*& course, string courseID, string room, Classes*& Class);
void Edit_CourseID_Student(Students* st, string NewID, string OldID);
void Edit_CourseID_Class(Classes*& Class, string NewID, string OldID);
void EditCourseId(Courses*& course, string NewID, Classes*& Class);

void DeleteCourseScheduleClass(Classes*& Class, string courseID, string classID);
void DeleteScoreBoardOfCourse(Students*& ST, string courseName);
void DeleteCourseOfCheckin(CheckinCourse*& checkincourse, string courseID);
void RemoveCourseOfScheduleStudent(string schedule[6][4], string courseID);
void DeleteCourseScheduleStudent(Courses*& course, StudentCourse*& Outsider, Classes*& Class);

void DeleteScoreBoardOfCourseStudent(Students*& ST, string courseName);

void View_Scoreboard_Student(Students* st, string courseID);

void Export_Scoreboard_Student(Students* st, string courseID, ofstream& out);
#pragma endregion


#pragma region All roles
int login(AcademicYears* year, Accounts*& acc, string pwd);
void showMenu(Accounts*& acc, AcademicYears*& year);
void changePwd(Accounts*& acc);
void viewProfile(Accounts* acc);
void logout(Accounts*& acc);
#pragma endregion

#pragma region Academic Staff
#pragma region Class
void importAClassFromCsvFile(Classes*& classList);
void addAStudentToAClass(Classes*& aClass);
void editAStudent(Classes*& aClass);
void removeAStudent(Classes*& aClass,Courses*& course,char semes,string year);
void changeClassForStudents(Classes*& classes, Courses*& course, char semes, string year);
void viewListOfClasses(AcademicYears* aYear);
void viewListOfStudentsInAClass(AcademicYears* aYear);
#pragma endregion
#pragma region Course
void createAcademicYear(AcademicYears*& year);
void updateAcademicYear(AcademicYears* year);
void deleteAcademicYear(AcademicYears*& year);
void viewAcademicYear(AcademicYears* year);

void ImportCourseFromCsv(AcademicYears* year);
void AddCourse(AcademicYears*& year);
void EditCourse(AcademicYears* year);
void DeleteCourse(AcademicYears* year);
void RemovedStudentFromCourseClass(AcademicYears* year);
void AddStudentToCourseClass(AcademicYears* year);
void viewCourseOfSemester(AcademicYears* acaYear);
void View_StudentList_Course(AcademicYears* year);
void View_Attendance_List(AcademicYears* year);

void createLecturer(AcademicYears* year);
void updateLecturer(AcademicYears* year);
void deleteLecturer(AcademicYears* year);
void viewLecturer(AcademicYears* year);
#pragma endregion
#pragma region Scoreboard
void View_Scoreboard(AcademicYears* year);
void Export_ScoreBoard(AcademicYears* year);
#pragma endregion
#pragma region Attendance list
void ViewAttendanceList(AcademicYears* year);
void exportAttendanceListOfCourse(AcademicYears* year);
#pragma endregion
#pragma endregion

#pragma region Lecturer
void viewCourseOfASemester(AcademicYears* acaYear);
void ViewStudentListOfACourse(AcademicYears* year);
void ViewAttendanceListOfACourse(AcademicYears* year);
void Edit_Attend_List(AcademicYears* year, Accounts*& acc);
void ImportScoreBoard(AcademicYears* year, Accounts*& acc);
void Edit_ScoreBoard_Student(AcademicYears* year, Accounts*& acc);
void ViewAScoreboard(AcademicYears* year);
#pragma endregion

#pragma region Student
void Tick(Students* student);
void viewCheckIn(CheckinCourse* checkincourse);
void viewSchedule(Students* student);
void viewScoreCourse(Students* student);
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
void deleteStudentCourse(StudentCourse* OS);
void deleteCourses(Courses*& course);
void deleteLecturers(Lecturers*& lect);
void deleteStaffs(Staffs*& staff);
void deleteSemesters(Semesters*& semes);

void deleteStudents(Students*& st);
void deleteClasses(Classes*& Class);

void deleteAcademicYears(AcademicYears*& year);
#pragma endregion
#pragma endregion
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
#endif