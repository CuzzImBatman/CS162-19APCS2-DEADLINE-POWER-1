#include "function.h"

int main() {
	ifstream fin;
	ofstream fout;
	phone a[50];
	fout.open("output.txt");
	fin.open("input.txt");
	if (!fin.is_open()) {
		cout << "Error opening file.";
	}
	else {
		int n;
		LoadPhones(fin, a, n);
		SavePhones(fout, a, n);
	}
	fin.close();
	fout.close();
	return 0;
}