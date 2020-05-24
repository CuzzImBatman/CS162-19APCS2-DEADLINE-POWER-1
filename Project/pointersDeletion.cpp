#include "function.h"

void deleteAccounts(Accounts*& acc) {
	Accounts* tempAcc = acc;
		acc->doB = nullptr;
}

void deleteCourses(Courses*& course) {
	//SpookyFish->SunFLower
}
void deleteLecturers(Lecturers*& lect) {
	Lecturers* tempLect = lect;
	while (tempLect) {
		delete tempLect->account->doB;
		delete tempLect->account;
		Lecturers* newTemp = tempLect;
		tempLect = tempLect->next;
		delete newTemp;
	}
}
void deleteStaffs(Staffs*& staff) {
	Staffs* tempStaff = staff;
	while (tempStaff) {
		delete tempStaff->account->doB;
		delete tempStaff->account;
		Staffs* newTemp = tempStaff;
		tempStaff = tempStaff->next;
		delete newTemp;
	}
}
void deleteSemesters(Semesters*& semes) {
	Semesters* tempSemes = semes;
	while (tempSemes) {
		deleteStaffs(semes->staffs);
		deleteLecturers(semes->lecturers);
		deleteCourses(semes->courses);
		Semesters* newTemp = tempSemes;
		tempSemes = tempSemes->next;
		delete newTemp;
	}
}

void deleteStudents(Students*& st) {
	Students* tempSt = st;
	while (tempSt) {
		delete tempSt->account->doB;
		delete tempSt->account;
		Students* newTemp = tempSt;
		tempSt = tempSt->next;
		delete newTemp;
	}
}
void deleteClasses(Classes*& Class) {
	Classes* tempClass = Class;
	while (tempClass) {
		deleteStudents(Class->students);
		Classes* newTemp = tempClass;
		tempClass = tempClass->next;
		delete newTemp;
	}
}

void deleteAcademicYears(AcademicYears*& year) {
	AcademicYears* tempYear = year;
	while (tempYear) {
		deleteClasses(tempYear->classes);
		deleteSemesters(tempYear->semesters);
		AcademicYears* newTemp = tempYear;
		tempYear = tempYear->next;
		delete newTemp;
	}
}