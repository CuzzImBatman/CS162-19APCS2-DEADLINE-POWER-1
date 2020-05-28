#include "function.h"
void deleteStudentCourse(StudentCourse* OS)
{
	while (OS)
	{
		StudentCourse* tmp = OS;
		OS = OS->next;
		delete tmp;
	}
}

void deleteCourses(Courses*& course) {
	while (course)
	{
		CourseClass* CL = course->courseclass;
		while (CL)
		{
			deleteStudentCourse(CL->Outsider);
			CourseClass* tmpCL = CL;
			CL = CL->next;
			delete tmpCL;
		}
		Courses* tmpCS = course;
		course = course->next;
		delete tmpCS;
	}
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
		deleteStaffs(tempSemes->staffs);
		deleteLecturers(tempSemes->lecturers);
		deleteCourses(tempSemes->courses);
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
		DeleteCheckinCourseStudent(tempSt);
		DeleteScoreBoardStudent(tempSt);

		Students* newTemp = tempSt;
		tempSt = tempSt->next;
		delete newTemp;
	}
}
void deleteClasses(Classes*& Class) {
	Classes* tempClass = Class;
	while (tempClass) {
		deleteStudents(tempClass->students);
		Classes* newTemp = tempClass;
		tempClass = tempClass->next;
		delete newTemp;
		newTemp = NULL;
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
