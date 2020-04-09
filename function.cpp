#include "function.h"

void LoadPhones(ifstream& fin, phone a[], int &n) {
	fin >> n;
	for (int i = 0; i < n; ++i) {
		fin >> a[i].id;
		fin.ignore();
		int j = 0;
	 	while ((a[i].name[j++] = fin.get()) != '\n');
		a[i].name[--j] = '\0';
		fin.get(a[i].name[0]);
		fin >> a[i].stock;
		fin >> a[i].price;
	}
}

void SavePhones(ofstream& fout, phone a[], int& n) {
	unsigned long long int totalMoney = 0;
	for (int i = 0; i < n; ++i) {
		totalMoney += a[i].stock * a[i].price;
	}
	fout << totalMoney;
}