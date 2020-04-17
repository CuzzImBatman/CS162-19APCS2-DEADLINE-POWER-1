#include "function.h"

int main() {
	AcademicYears* acaYr = new AcademicYears;
	acaYr->year = 1920;

	acaYr->semesters = new Semesters;
	acaYr->semesters->semesterNo = 2;

	acaYr->semesters->courses = new Courses;
	acaYr->semesters->courses->courseName = "CS162";
	acaYr->semesters->courses->dateOfWeek[1] = 1000;
	acaYr->classes = new Classes;
	acaYr->classes->className = "19CTT2";

	ifstream studentList;
	studentList.open("studentDB.csv");

	if (studentList.is_open()) {
		studentList.ignore(1000, '\n'); //ignore the title row
		while (!studentList.eof()) {
			acaYr->classes->students = new Students;
			studentList.ignore(1000, '\n');
			char temp[256];
			int i = 0;
			
	
			
		}
	}
	else {
		std::cout << "Error opening file";
	}










	char choice;
	cout << "Login? (Y/N)";
	cin >> choice;
	while (choice == 'Y') {
		//Take in temporary username and password
		Account curAcc;
		char temp[256];

		cout << "Please enter your username: ";
		cin.ignore();
		int i = 0;
		while ((temp[i++] = cin.get()) != '\n');
		temp[--i] = '\0';
		curAcc.uName = new char[strlen(temp)];
		curAcc.uName = temp;

		cout << "Please enter your password";
		cin.ignore();
		i = 0;
		while ((temp[i++] = cin.get()) != '\n');
		temp[--i] = '\0';
		curAcc.pwd = new char[strlen(temp)];
		curAcc.pwd = temp;
		
		short int loginStatus = login(curAcc.uName, curAcc.pwd, /* asvsasvwv*/);
		if (loginStatus == -1) {
			cout << "Login unsuccessful, login again? (Y/N)";
			cin >> choice;
		}
		else {
			//showMenu();
			//viewProfile();
			//changePwd();
			//logout();
		}
	}
	
}

//tao 3 file csv db 
//tao 3 array db S, AS, L ban dau de luu tu file -> khi chay -> hien login -> so sanh db
//studentInput -> 6.