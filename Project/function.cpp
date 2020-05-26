#include "function.h"

 using namespace std;

/*int numberOfDay(Date x, Date y) {
  if (x.month < 3) {
    x.year--;
    x.month += 12;
  }
  if (y.month < 3) {
    y.year--;
    y.month += 12;
  }
  return 365 * x.year + x.year / 4 - x.year / 100 + x.year / 400 + (153 * x.month - 457) / 5 + x.day - 307 - (365 * y.year + y.year / 4 - y.year / 100 + y.year / 400 + (153 * y.month - 457) / 5 + y.day - 307) + 1;
}*/

#pragma region Add

#pragma endregion
//void EditScheduleCourseOfStudent()
//void RemoveCourse()


#pragma region EditCourse
void EditCourseroom(Courses * & course, string courseID, string room) {
  Courses * cur = course;

  while (cur ->  courseID != courseID)
    cur ->  next;
  cur ->  room = room;
}
#pragma endregion

#pragma region Delete
int DeleteABit(int bit, int x)
{
	int newBIt = 0;
	int i = 0;
	while (bit)
	{
		if (x != i)
		{
			newBIt += ((bit) % 2) << i;
			i++;
		}
		else x = -1;
		bit = bit >> 1;
	}
	return newBIt;
}
void DeleteCheckinCourseStudent(Students*& St)
{
	while (St->checkincourse)
	{
		CheckinCourse* CK = St->checkincourse;
		St->checkincourse = CK->next;
		delete CK;
		CK = NULL;

	}
}
void DeleteStudentFromCourses(string studentID, string classID, Courses*& course)
{
	Courses* cs = course;
	CourseClass* CL = findCL(course->courseclass, classID);
	if (CL)
	{
		Students*& st = CL->students;
		int i = 0;
		while (st)
			if (st->studentID == studentID)
			{
				CL->BitAttend = DeleteABit(CL->BitAttend, i);
			}
			else
			{
				i++;
				st = st->next;
			}
	}
	while (cs)
	{
		CL = cs->courseclass;
		OutsideStudent* OS = CL->Outsider;
		OutsideStudent* tmp = OS;
		if (OS && OS->studentID == studentID)
		{
			OS = OS->next;
			delete tmp;
			tmp = NULL;
			break;

		}
		while (OS)
		{
			if (OS->studentID == studentID)
			{
				OutsideStudent* del = OS;
				tmp->next = OS->next;
				OS = OS->next;
				delete del;
				del = NULL;
				break;
			}

			tmp = OS;
			OS = OS->next;

		}
		cs = cs->next;
	}
}
void DeleteScoreBoardOfCourse(Students* &ST, string courseID)
{
	Students* st = ST;
	while (st)
	{
		DeleteScoreBoardOfCourseStudent(st, courseID);
		st = st->next;
	}

}
#pragma endregion

bool ComparePwd(SHA256_CTX a, SHA256_CTX b)
{
	for (int i = 0; i < 8; i++)
		if (a.state[i] != b.state[i])return false;
	return true;


}
void RemoveFile(string s)
{
	char* c = const_cast<char*>(s.c_str());
	remove(c);
}
Semesters* FindSemester(AcademicYears* AY)
{
	string year;
	AcademicYears* y = NULL;
	while (!y)
	{
		cout << "\nPlease enter Academic Year: ";
		cin >> year;
			y = AY;
			while (y)
				if (y->year == year)break;
				else y = y->next;
			if (!y)cout << "Invalid Academic Year, please enter again." << endl;
	}
	Semesters* s = NULL;
	char sems;
	while (!s)
	{
		cout << "\nPlease enter semester: ";
		cin >> sems;
		s = y->semesters;
		while (s)
			if (strcmp((const char*)s->semesterNo, (const char*)sems) == 0)break;
			else s = s->next;
		if(!s)cout << "Invalid semester, please enter again." << endl;		
	}
	return s;

}