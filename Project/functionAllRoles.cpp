#include "function.h"

int login(AcademicYears* year, Accounts*& acc) {
	if (acc->uName[0] <= 57) {
		//student
		Classes* tempClass = year->classes;
		while (tempClass) {
			Students* tempSt = tempClass->students;
			while (tempSt) {
				if (tempSt->account->uName == acc->uName)
					if (tempSt->account->pwd == acc->pwd) {
						delete acc;
						acc = tempSt->account;
						return 1;
					}
					else {
						//cout << "Wrong password." << endl;
						return 0;
					}
				tempSt = tempSt->next;
			}
			tempClass = tempClass->next;
		}
		//cout << "Wrong username." << endl;
		return 0;
	}
	else {
		//staff or lecturer
		Semesters* tempSemes = year->semesters;
		while (tempSemes) {
			Staffs* tempStaff = tempSemes->staffs;
			while (tempStaff) {
				if (tempStaff->account->uName == acc->uName)
					if (tempStaff->account->pwd == acc->pwd) {
						delete acc;
						acc = tempStaff->account;
						return 2;
					}
					else {
						//cout << "Wrong password." << endl;
						return 0;
					}
				tempStaff = tempStaff->next;
			}
			Lecturers* tempLec = tempSemes->lecturers;
			while (tempLec) {
				if (tempLec->account->uName == acc->uName)
					if (tempLec->account->pwd == acc->pwd) {
						delete acc;
						acc = tempLec->account;
						return 3;
					}
					else {
						//cout << "Wrong password." << endl;
						return 0;
					}
				tempLec = tempLec->next;
			}
			tempSemes = tempSemes->next;
		}
		//cout << "Wrong username." << endl;
		return 0;
	}
}

void showClassOptions(AcademicYears*& year) {
	int choice;
	bool variableName = 1;
	while (variableName) {
		cout << endl << "Sub menu: What do you want to do? " << endl;
		cout << "[1] Import students from a csv file." << endl;
		cout << "[2] Manually add a new student to a class." << endl;
		cout << "[3] Edit an existing student." << endl;
		cout << "[4] Remove a student." << endl;
		cout << "[5] Change students from class A to class B." << endl;
		cout << "[6] View list of classes." << endl;
		cout << "[7] View list of students in a class." << endl;
		cout << "[8] Back to main menu." << endl;
		cout << "Your choice: ";
		cin >> choice;
		switch (choice) {
		case 1: {

			break;
		}
		case 2: {
			addAStudentToAClass(year->classes);
			break;
		}
		case 3: {
			editAStudent(year->classes);
			break;
		}
		case 4: {
			removeAStudent(year->classes);
			break;
		}
		case 5: {
			changeClassForStudents(year->classes);
			break;
		}
		case 6: {
			viewListOfClasses(year->classes);
			break;
		}
		case 7: {
			viewListOfStudentsInAClass(year->classes);
			break;
		}
		case 8: variableName = 0;
		default: break;
		}
	}
}

void showCourseOptions(AcademicYears*& year) {
	int choice;
	bool variableName = 1;
	while (variableName) {
		cout << endl << "Sub menu: What do you want to do? " << endl;
		cout << "[1] Create/update/delete/view academic years, and semesters." << endl;
		cout << "[2] From a semester, import courses from a csv file." << endl;
		cout << "[3] Manually add a new course." << endl;
		cout << "[4] Edit an existing course." << endl;
		cout << "[5] Remove a course." << endl;
		cout << "[6] Remove a specific student from a course." << endl;
		cout << "[7] Add a specific student to a course." << endl;
		cout << "[8] View list of courses in the current semester." << endl;
		cout << "[9] View list of students of a course." << endl;
		cout << "[10] View attendance list of a course." << endl;
		cout << "[11] Create/update/delete/view all lecturers." << endl;
		cout << "[12] Back to main menu." << endl;
		cout << "Your choice: ";
		cin >> choice;
		switch (choice) {
		case 1: {
			break;
		}
		case 2: {

			break;
		}
		case 3: {

			break;
		}
		case 4: {

			break;
		}
		case 5: {

			break;
		}
		case 6: {

			break;
		}
		case 7: {

			break;
		}
		case 8: {
			viewCourseOfSemester(year);
			break;
		}
		case 9: {

			break;
		}
		case 10: {

			break;
		}
		case 11: {
			cout << endl << "Sub menu: What do you want to do?" << endl
				<< "[1] Create a new lecturer." << endl
				<< "[2] Edit a lecturer." << endl
				<< "[3] Delete a lecturer." << endl
				<< "[4] View all lecturers." << endl
				<< "Your choice: ";
			cin >> choice;
			switch (choice)
			{
			case 1: {
				createLecturer(year);
				break;
			}
				  
			case 2: {
				updateLecturer(year);
				break;
			}
			case 3: {
				deleteLecturer(year);
				break;
			}
			case 4: {
				viewLecturer(year);
				break;
			}
			}
			break;
		}
		case 12: variableName = 0;
		default: break;
		}
	}
}

void showScoreboardOptions(AcademicYears*& year) {
	int choice;
	bool variableName = 1;
	while (variableName) {
		cout << endl << "Sub menu: What do you want to do? " << endl;
		cout << "[1] Search and view the scoreboard of a course." << endl;
		cout << "[2] Export a scoreboard to a csv file." << endl;
		cout << "[3] Back to main menu." << endl;
		cout << "Your choice: ";
		cin >> choice;
		switch (choice) {
		case 1: {

			break;
		}
		case 2: {

			break;
		}
		case 3: variableName = 0;
		default: break;
		}
	}
}

void showAttendanceListOptions(AcademicYears*& year) {
	int choice;
	bool variableName = 1;
	while (variableName) {
		cout << endl << "Sub menu: What do you want to do? " << endl;
		cout << "[1] Search and view attendance list of a course." << endl;
		cout << "[2] Export a attendance list to a csv file." << endl;
		cout << "[3] Back to main menu." << endl;
		cout << "Your choice: ";
		cin >> choice;
		switch (choice) {
		case 1: {

			break;
		}
		case 2: {

			break;
		}
		case 3: variableName = 0;
		default: break;
		}
	}
}
//Emblema: need to add param academicYear for some functions to work...

void showMenu(short int role, AcademicYears*& year) {
	switch (role) {
	case 1: {
		//call student functions
		int choice;
		bool variableName = 1;
		while (variableName) {
			cout << endl << "Sub menu: What do you want to do? " << endl;
			cout << "[1] Check-in." << endl;
			cout << "[2] View check-in result." << endl;
			cout << "[3] View schedules." << endl;
			cout << "[4] View my scores of a course." << endl;
			cout << "[5] Back to main menu." << endl;
			cout << "Your choice: ";
			cin >> choice;
			switch (choice) {
			case 1: {

				break;
			}
			case 2: {

				break;
			}
			case 3: {

				break;
			}
			case 4: {

				break;
			}
			case 5: variableName = 0;
			default: break;
			}
		}
		break;
	}
	case 3: {
		//call lecturer functions
		int choice;
		bool variableName = 1;
		while (variableName) {
			cout << endl << "Sub menu: What do you want to do? " << endl;
			cout << "[1] View list of courses in the current semester." << endl;
			cout << "[2] View list of students of a course." << endl;
			cout << "[3] View attendance list of a course." << endl;
			cout << "[4] Edit an attendance." << endl;
			cout << "[5] Import scoreboard of a course from a csv file." << endl;
			cout << "[6] Edit grade of a student." << endl;
			cout << "[7] View a scoreboard." << endl;
			cout << "[8] Back to main menu." << endl;
			cout << "Your choice: ";
			cin >> choice;
			switch (choice) {
			case 1: {
				viewCourseOfSemester(year);
				break;
			}
			case 2: {

				break;
			}
			case 3: {

				break;
			}
			case 4: {

				break;
			}
			case 5: {

				break;
			}
			case 6: {

				break;
			}
			case 7: {

				break;
			}
			case 8: variableName = 0;
			default: break;
			}
		}
		break;
	}
	case 2: {
		//call staff functions
		int choice;
		bool variableName = 1;
		while (variableName) {
			cout << endl << "Sub menu: What do you want to do? " << endl;
			cout << "[1] View class-related options." << endl;
			cout << "[2] View course-related options." << endl;
			cout << "[3] View scoreboard-related options." << endl;
			cout << "[4] View attedance-list-related options." << endl;
			cout << "[5] Back to main menu." << endl;
			cout << "Your choice: ";
			cin >> choice;
			switch (choice) {
			case 1: {
				showClassOptions(year);
				break;
			}
			case 2: {
				showCourseOptions(year);
				break;
			}
			case 3: {
				showScoreboardOptions(year);
				break;
			}
			case 4: {
				showAttendanceListOptions(year);
				break;
			}
			case 5: variableName = 0;
			default: break;
			}
		}
		break;
	}
	default: break;
	}
}

void changePwd(Accounts*& acc) {
	cout << endl << "Type in your old password." << endl;
	string oldPwd;
	cin >> oldPwd;
	cout << "Type in your new password." << endl;
	string newPwd;
	cin >> newPwd;
	cout << "Type in your new password again to confirm." << endl;
	string conPwd;
	cin >> conPwd;
	while (oldPwd != acc->pwd || newPwd != conPwd || newPwd == oldPwd) {
		if (oldPwd != acc->pwd)
			cout << endl << "The old password does not match." << endl;
		else if (newPwd != conPwd)
			cout << endl << "The new password does not match with confirm password." << endl;
		else if (newPwd == oldPwd)
			cout << endl << "New password cannot be the same as old password." << endl;
		cout << endl << "Type in your old password." << endl;
		cin >> oldPwd;
		cout << "Type in your new password." << endl;
		cin >> newPwd;
		cout << "Type in your new password again to confirm." << endl;
		cin >> conPwd;
	}
	acc->pwd = newPwd;
	cout << endl << "Password changed." << endl;
}

void viewProfile(Accounts* acc) {
	cout << endl << "Your profile: " << endl;
	cout << "Name: " << acc->firstname << ' ' << acc->lastname << endl;
	cout << "DoB (dd-mm-yyyy): " << acc->doB->day << '-' << acc->doB->month << '-' << acc->doB->year << endl;
	cout << "Gender: ";
	switch (acc->gender) {
	case 'F': cout << "Female" << endl;
		break;
	case 'M': cout << "Male" << endl; break;
	case 'O': cout << "Prefer not to say" << endl;
		break;
	}
	cout << "Username: " << acc->uName << endl;
	cout << "Password: ";
	for (int i = 0; i < acc->pwd.length(); ++i)
		cout << '*';
	cout << endl;
	int choice;
	bool variableName = 1;
	while (variableName) {
		cout << endl << "Sub menu: What do you want to do? " << endl << "[1] Show password." << endl << "[2] Change password." << endl
			<< "[3] Back to main menu" << endl << "Your choice: ";
		cin >> choice;
		switch (choice) {
		case 1: {
			cout << endl << "Please confirm your password: ";
			string confPwd;
			cin >> confPwd;
			if (confPwd == acc->pwd) 
				cout << "Password: " << acc->pwd << endl;
			else {
				cout << "Confirm password incorrect." << endl;
			}
			break;
		}
		case 2: {
			changePwd(acc);
			break;
		}
		case 3: {
			variableName = 0;
			break;
		}
		default: break;
		}
	}
	
}

void logout(Accounts*& acc) {
	acc = nullptr;
}
