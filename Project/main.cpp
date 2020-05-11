#include "function.h"

int main() {
	AcademicYears* academicYear = nullptr;
	academicYearInit(academicYear);
	
	cout << "Login? [Y/N] ";
	while (cin.get() == 'Y') {
		bool loggedin = 0;
		Accounts* acc = new Accounts;
		while (true) {
			cout << "Username: ";
			cin >> acc->uName;
			cout << "Password: ";
			cin >> acc->pwd;
			if (login(academicYear, acc)) {
				loggedin = 1;
				break;
			}
			else {
				cout << "Login failed." << endl;
				break;
			}
		}
		int choice; 
		while (loggedin) {
			cout << endl << "What do you want to do?" << endl << "[1] to show menu." << endl << "[2] to view profile."
				<< endl << "[3] to change password." << endl << "[4] to logout.";
			cin >> choice;
			switch (choice) {
			case 1: {
				showMenu(acc->role);
				break;
			}
			case 2: {
				viewProfile(acc);
				break;
			}
			case 3: {
				changePwd(acc);
				break;
			}
			case 4: {
				logout(acc);
				loggedin = 0;
				break;
			}
			}
		}
		if (!loggedin) cout << "Login? [Y/N] ";
	}
	return 0;
}