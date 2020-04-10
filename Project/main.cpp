#include "function.h"

int main() {
	StudentDB* studentDBHead;
	ifstream fStudentDB;
	fStudentDB.open("studentDB.csv");
	if (!fStudentDB.is_open()) {
		cout << "Error initializing student database.";
	}
	else {
		cin.ignore(1000, '\n'); //ignore the title row
		while (!fStudentDB.eof()) {
			studentDBHead->nextStudent = new StudentDB;
			char temp[256];
			int i = 0;

			while ((temp[i++] = cin.get()) != ',');
			temp[--i] = '\0';
			studentDBHead->no = (int)temp;

			//same goes for other information.
			studentDBHead->account->role = 1; //redundant line, put here to demonstrate the link between Account and StudentDB
		}
		//might wanna change it so that a specific db only get initialized when the role is confirmed by making use of uName[0].
		//doing this will yield a better programme memory wise.
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