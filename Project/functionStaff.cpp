#include "function.h"

void viewCourseOfSemester(AcademicYears* AcaYear)
{
	string year;
	cout << "Please enter Academic Year (1920/2021): ";
	cin >> year;
	while (AcaYear != nullptr && AcaYear->year != year)
		AcaYear = AcaYear->next;
	if (AcaYear == nullptr)
	{
		cout << "Academic year not found!" << endl;
		return;
	}
	else
	{
		Semesters* semes = AcaYear->semesters;
		char semester;
		cout << "Please enter Semester: ";
		cin >> semester;
		while (semes != nullptr && semes->semesterNo != semester)
			semes = semes->next;
		if (semes == nullptr)
		{
			cout << "Semester not found!" << endl;
			return;
		}
		else
		{
			Courses* courseList = semes->courses;
			cout << "List of courses in year " << year << ", semester " << semester << " are: " << endl;
			while (courseList != nullptr)
			{
				cout << courseList->courseID << endl;
				courseList = courseList->next;
			}
		}
	}
}