#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#include <iostream>
#include <fstream>
using namespace std;

struct phone {
	int id;
	char name[128];
	int stock;
	unsigned int price;
};

void LoadPhones(ifstream& fin, phone a[], int& n);
void SavePhones(ofstream& fout, phone a[], int& n);

#endif
