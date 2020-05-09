#ifndef _FUNCTION_H_
#define _FUNCTION_H_
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS 1
#endif
          
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <fstream>
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
			   +--[CourseClass]<--------------------------------+			  		                  
			   |						  		 
			   |                            	          +-->[AttendanceStatus]
			   |			      	                      |
			   +-->[Classes]+------------------>[Students]+-->[Scoreboard]

*/
struct Date {
	int day, month, year;
};

struct Accounts {
	char* pwd = nullptr;  //(sha256 if possible)
	char* uName = nullptr; // = ID 
	short int role = (int)uName[0] - 48;
	string lastname, firstname;
	char gender[3]; //Female Male, Prefer not to say -> F,M,O
	Date* doB = nullptr;
};

struct Scoreboards {
	string courseName; //the course that this list belongs to
	int midtermScore, finalScore, labScore, bonusScore; 
	Scoreboards* next = nullptr;
};

struct Staffs {
	Accounts* account = nullptr;
	Staffs* next = nullptr;
};

struct Lecturers {
	Accounts* account = nullptr;
	Lecturers* next = nullptr;
};

struct SessionStatus {
	short int sessionNo; //11 12 21 22 31 32  week_session
	bool status;
	SessionStatus* next = nullptr;
};
/*
struct WeeklyStatus {
	SessionStatus* sessions = nullptr;
	WeeklyStatus* next = nullptr;
};*/
struct AttendanceStatus {
	string courseName;
	SessionStatus* sessions = nullptr; //the amount of sessions will be academicYear->semester->course->dateOfWeek(1) * 11
	AttendanceStatus* next = nullptr;
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

struct Students {
	int studentNo;
	Accounts* account = nullptr;
	Scoreboards* scoreboards = nullptr;
	AttendanceStatus* attendanceStatus = nullptr;
	//Courses* courses = nullptr;//List of courses a student enrolled
	Students* next = nullptr;
};

struct Courses {
	short int courseNo;
	string courseName;	//them course id
	Date startDate, endDate;
	short int dateOfWeek[6]; //Ex: CS162: {0000;1000;0000;0000;0000;0001} -> first shift of Tue and last shift of Sat   
	string room;
	Lecturers* lecturers = nullptr;
	Students* students = nullptr;
	Courses* next = nullptr;
};

struct Classes {
	short int classNo;
	string className; 
	Students* students = nullptr;
	Classes* next = nullptr;
};

struct CourseClass {
	short int no, classNo, courseNo, studentNo;
};

struct Semesters {
	char semesterNo;
	Courses* courses = nullptr;
	Lecturers* lecturers = nullptr;
	Staffs* staffs = nullptr;
	Semesters* next = nullptr;
};

struct AcademicYears {
	short int year;  //Ex: 1920 2021;
	Semesters* semesters = nullptr;
	Classes* classes = nullptr;
	AcademicYears* next = nullptr;
};

struct Account {
	char* pwd;  //(sha256 if possible)
	char* uName; // = ID 
	short int role = (int)uName[0] - 48;
	char* lastname, * firstname;
	int gender;
	Date* doB;
};

struct AcademicStaff {
	Account* account;
	int no;
};

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

#pragma region Class
void importAClassFromCsvFile(AcademicStaff* staff, Classes*& aClass, ifstream fin);
void addAStudentToAClass(AcademicStaff* staff, Students*& aStudent, Classes*& aClass);
void editAStudent(AcademicStaff* staff, Classes*& aClass);
void removeAStudent(AcademicStaff* staff, Classes*& aClass);
void changeClassForStudents(AcademicStaff* staff, Classes*& oldClass, Classes*& newClass);
void viewListOfClasses(AcademicStaff* staff, Classes* classes);
void viewListOfStudentsInAClass(AcademicStaff* staff, Classes* aClass);
#pragma endregion

#pragma region Course

#pragma endregion

#pragma region Scoreboard

#pragma endregion

#pragma region Attendance list

#pragma endregion

#pragma endregion
void importAClassFromCsvFile(AcademicStaff* staff, Classes*& aClass, ifstream fin);
void addAStudentToAClass(AcademicStaff* staff, Students*& aStudent, Classes*& aClass);
void editAStudent(AcademicStaff* staff, Classes*& aClass);
void removeAStudent(AcademicStaff* staff, Classes*& aClass);
void changeClassForStudents(AcademicStaff* staff, Classes*& oldClass, Classes*& newClass);
void viewListOfClasses(AcademicStaff* staff, Classes* classes);
void viewListOfStudentsInAClass(AcademicStaff* staff, Classes* aClass);
#pragma region Lecturer

#pragma endregion

#pragma region Student

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