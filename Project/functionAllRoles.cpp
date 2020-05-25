#include "function.h"

int login(AcademicYears* year, Accounts*& acc, string pwd) {
	if (acc->uName[0] <= 57) {
		//student
		SHA256_CTX check;
		sha256_init(&check);
		sha256_update(&check, pwd, pwd.length());
		Classes* tempClass = year->classes;
		while (tempClass) {
			Students* tempSt = tempClass->students;
			while (tempSt) {
				if (tempSt->account->uName == acc->uName)
					if (ComparePwd( tempSt->account->pwd, check)) {
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
		SHA256_CTX check;
		sha256_init(&check);
		sha256_update(&check, pwd, pwd.length());
		Semesters* tempSemes = year->semesters;
		while (tempSemes) {
			Staffs* tempStaff = tempSemes->staffs;
			while (tempStaff) {
				if (tempStaff->account->uName == acc->uName)
					if ( ComparePwd(tempStaff->account->pwd , check) ) {
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
					if (ComparePwd(tempLec->account->pwd ,check)) {
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
		cout << "[8] Back." << endl;
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
			removeAStudent(year->classes,  year->semesters->courses,year->semesters->semesterNo,year->year);
			break;
		}
		case 5: {
			changeClassForStudents(year->classes,year->semesters->courses);
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
		cout << "[12] Back." << endl;
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
		    AddCourse(year->semesters->courses, year->classes);
			break;
		}
		case 4: {
			EditCourse(year->semesters->courses, year->classes);
			break;
		}
		case 5: {
			DeleteCourse(year->semesters->courses, year->classes);
			break;
		}
		case 6: {
			RemovedStudentFromCourseClass(year->semesters->courses, year->classes);
			break;
		}
		case 7: {
			AddStudentToCourseClass(year->semesters->courses, year->classes);
			break;
		}
		case 8: {
			viewCourseOfSemester(year);
			break;
		}
		case 9: {
			View_StudentList_Course(year->semesters->courses, year->classes);
			break;
		}
		case 10: {
			View_Attendance_List(year->semesters->courses, year->classes);// still not understand difference (Attendancelist and Stulist)
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
		cout << "[3] Back." << endl;
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
		cout << "[3] Back." << endl;
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

void showMenu(Accounts*& acc, AcademicYears*& year) {

	Classes* cl = year->classes;
	Students* st=cl->students;
	while (cl)
	{
		 st = findStudent(cl->students, acc->uName);
		if(st && st->Status)break;
		cl = cl->next;;
	}
	switch (acc->role) {
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
				Tick(st);
				break;
			}
			case 2: {
				viewCheckIn(st->checkincourse);
				break;
			}
			case 3: {
				viewSchedule(st);
				break;
			}
			case 4: {
				viewScoreCourse(st);
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
			// Joey: Infinite loop when type in letters into "choice" (cannot escape)
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
	SHA256_CTX confirm;
	string oldPwd, newPwd, conPwd;
	do
	{
		cout << endl << "Type in your old password." << endl;
		cin >> oldPwd;
		sha256_init(&confirm);
		sha256_update(&confirm, oldPwd, oldPwd.length());
		if (!ComparePwd(confirm, acc->pwd))
			cout << endl << "The old password does not match." << endl;
	} while (!ComparePwd(confirm, acc->pwd));
	
	do
	{
		cout << "Type in your new password." << endl;
		cin >> newPwd;
		if (newPwd == oldPwd)
			cout << endl << "New password cannot be the same as old password." << endl;
	} while (newPwd == oldPwd);
	do
	{
		cout << "Type in your new password again to confirm." << endl;
		cin >> conPwd;
		if(newPwd == conPwd)
		cout << endl << "The new password does not match with confirm password." << endl;
	} while (newPwd != conPwd);
	
	
	sha256_init(&acc->pwd);
	sha256_update(&acc->pwd, conPwd, conPwd.length());
	cout << endl << "Password changed." << endl;
}

void viewProfile(Accounts* acc) {
	cout << endl << "Your profile: " << endl;
	cout << "Name: " << acc->lastname << ' ' << acc->firstname << endl;
	cout << "DoB (dd-mm-yyyy): " << acc->doB->day << '-' << acc->doB->month << '-' << acc->doB->year << endl;
	cout << "Gender: ";
	switch (acc->gender) {
	case 'F': cout << "Female" << endl;
		break;
	case 'M': cout << "Male" << endl; break;
	case 'O': cout << "Other" << endl;
		break;
	}
	cout << "Username: " << acc->uName << endl;
	cout << endl;
	int choice;
	bool variableName = 1;

	
}

void logout(Accounts*& acc) {
	acc = nullptr;
}
