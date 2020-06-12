#include "function.h"

int main() {
	AcademicYears* academicYear = nullptr;
	academicYearInit(academicYear);
	
	char loginchoice;
	cout << "Login? [Y/N] ";
	cin >> loginchoice;
	while (loginchoice == 'Y') {
		bool loggedin = 0;
		Accounts* acc = new Accounts;
		while (true) {
			cout << "Username: ";
			cin >> acc->uName;
			cout << "Password: ";
			string pwd;
			cin >> pwd;
			if (login(academicYear, acc,pwd)) {
				loggedin = 1;
				pwd = "";
				break;
			}
			else {
				cout << "Login failed. Wrong username or password." << endl;
				pwd = "";
				break;
			}
		}
		int choice; 
		while (loggedin) {
			cout << endl << "Main menu: What do you want to do?" << endl << "[1] to show menu." << endl << "[2] to view profile."
				<< endl << "[3] to change password." << endl << "[4] to logout." << endl << "Your choice: ";
			cin >> choice;
			switch (choice) {
			case 1: {
				showMenu(acc, academicYear);
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
		if (!loggedin) cout << endl << "Login again? [Y/N] ";
		cin >> loginchoice;
	}

	writeAcademicYears(academicYear);
	deleteAcademicYears(academicYear);
	return 0;
}