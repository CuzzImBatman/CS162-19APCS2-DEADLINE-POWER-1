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
//string 
/* Naming rule:
struct: StructName
variable, function: variableName, functionName
const: CONST
*/
/*
struct DBHead {
	int role;
	StudentDB* studentDBHead;
	AcademicStaffDB* academicStaffDBHead;
	LecturerDB* lecturerDBHead;
}
										  +------------+       +------------+
									   +--| account[0] |   +-->| account[1] |  +-->...
									  /	  +------------+  /	   +------------+ /
					+---------------+/   +--------------+/   +--------------+/
			   +--->| studentDBHead	|--->| studentDB[1] |--->| studentDB[2] |--->...
			   |    +---------------+    +--------------+    +--------------+
			   |								   +------------+			 +------------+
			   |							 +---->| account[0] |      +---->| account[1] |      +---->...
			   |                            /      +------------+     /      +------------+     /
+--------+     |    +---------------------+/   +--------------------+/   +--------------------+/
| dbHead |-----+--->| academicStaffDBHead |--->| academicStaffDB[1] |--->| academicStaffDB[2] |--->...
+--------+     |    +---------------------+    +--------------------+    +--------------------+
			   |						   +------------+		+------------+
			   |					    +->| account[0] |    +->| account[1] |    +->...
			   |					   /   +------------+   /   +------------+   /
			   |    +----------------+/   +---------------+/   +---------------+/
			   +--->| lecturerDBHead |--->| lecturerDB[1] |--->| lecturerDB[2] |--->...
					+----------------+    +---------------+    +---------------+
*/ 
struct AttendanceList {

};
struct Scoreboard {
	Course* courseID;
	Class* classID;
};

struct Course {
	int no;
	string id;
	string classID;
	Student* studentList;
	Lecturer* lecturerList;
	Date startDate, endDate;
	int dateOfWeek[6];//bit   
	string room;
};

struct Class {
	string id;
	Student* studentList;
};
struct Date {
	string day, month, year;
};

struct Account {
	char* pwd;  //(sha256 if possible)
	char* uName; // = ID 
	short int role = (int)uName[0] -48;
	char* lastname, * firstname, gender[2];
	Date* doB;
};
struct Student {
	Account* account;
	int no;
	char studentClass[20], studentID[20];//id = uName;
	//*classes, *courses
	//*pointer to student in list
	//*pointer to student in same class
	Student* nextStudent = nullptr;
};  //1xxxxxxx

struct AcademicStaff {
	Account* account;
	int no;
}; //3xxxxxx    *hoi gv*
struct Lecturer {
	Account* account;
	int no;
	//courses -> linked list
	//faculty 

};  //2xxxxxxx


#pragma region Initialization

#pragma endregion

#pragma region All roles
int login(char* user, char* pwd, Account* accountList); //1 2 3 -1          -> 2. 3. 4. 5.    tao curAcc
void showMenu(int role);
void viewProfile(Account* curAcc);
bool changePwd(char* newPwd, Account* accountList);
bool logout(Account* curAcc);
#pragma endregion

#pragma region Academic Staff

#pragma region Class

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