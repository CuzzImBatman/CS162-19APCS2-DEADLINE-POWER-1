#include "function.h"

void writeClasses(Classes* Class, string year) {
	Classes* tempClass = Class;
	ofstream classOut;
	string fileOut = "Yr" + year + "_ClassDB.txt";
	classOut.open(fileOut);
	if (classOut.is_open()) {
		
	}
}

void writeAcademicYears(AcademicYears* year) {
	AcademicYears* tempYear = year;
	ofstream yearOut;
	yearOut.open("AcademicYearDB.txt");
	int n = 0;
	while (tempYear) {
		n++;
		tempYear = tempYear->next;
	}
	yearOut << n << endl;
	tempYear = year;
	while (tempYear) {
		yearOut << year->year << endl;
		writeClasses(year->classes, year->year);
		tempYear = tempYear->next;
	}
	yearOut.close();

	
}