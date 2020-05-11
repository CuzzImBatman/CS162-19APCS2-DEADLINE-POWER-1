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
						acc = tempSt->account;
						return 1;
					}
					else {
						cout << "Wrong password." << endl;
						return 0;
					}
				tempSt = tempSt->next;
			}
			tempClass = tempClass->next;
		}
		cout << "Wrong username." << endl;
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
						acc = tempStaff->account;
						return 2;
					}
					else {
						cout << "Wrong password." << endl;
						return 0;
					}
				tempStaff = tempStaff->next;
			}
			Lecturers* tempLec = tempSemes->lecturers;
			while (tempLec) {
				if (tempLec->account->uName == acc->uName)
					if (tempLec->account->pwd == acc->pwd) {
						acc = tempLec->account;
						return 3;
					}
					else {
						cout << "Wrong password." << endl;
						return 0;
					}
				tempLec = tempLec->next;
			}
			tempSemes = tempSemes->next;
		}
		cout << "Wrong username." << endl;
		return 0;
	}
}

void showMenu(int role) {
	switch (role) {
	case 1: {
		//call student functions
		break;
	}
	case 2: {
		//call lecturer functions
		break;
	}
	case 3: {
		//call staff functions
		break;
	}
	}
}

void viewProfile(Accounts* acc) {
	cout << "Your profile: " << endl;
	cout << "Name: " << acc->firstname << ' ' << acc->lastname << endl;
	cout << "DoB (dd-mm-yyyy): " << acc->doB->day << '-' << acc->doB->month << '-' << acc->doB->year;
	cout << "Gender: ";
	switch (acc->gender) {
	case 'F': cout << "Female" << endl;
	case 'M': cout << "Male" << endl;
	case 'O': cout << "Prefer not to say" << endl;
	}
	cout << "Username: " << acc->uName << endl;
	cout << "Password: " << acc->pwd << endl;
	//for (int i = 0; i < acc->pwd.length(); ++i)
	//	cout << '*';
}

void changePwd(Accounts*& acc) {
	cout << "Type in your new password." << endl;
	string pwd;
	cin >> pwd;
	while (pwd == acc->pwd) {
		cout << "New password cannot be the same as old password." << endl;
		cout << "Type in your new password." << endl;
		cin >> pwd;
	}
	acc->pwd = pwd;
	cout << "Password changed." << endl;
}

bool logout(Accounts*& acc) {
	acc = nullptr;
}
