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

void UpdateBitAttend(string classID, Courses*& course) {
	Courses* curCS = course;
	while (curCS != NULL) {
		CourseClass* cur = curCS->courseclass;
		while (cur != NULL)
			if (cur->classID == classID) {
				cur->BitAttend = (cur->BitAttend) >> 1 + 1;
				break;
			}
			else
				cur = cur->next;
		curCS = curCS->next;
	}
}
void FillCheckinCourse(Students*& student) {
	for (int i = 0; i <= 5; i++)
		for (int j = 0; j <= 3; j++)
			if (student->schedule[i][j] != "//") {
				CheckinCourse* newcourse = new CheckinCourse;
				newcourse->courseID = student->schedule[i][j];
				newcourse->bitweek = 0;
				//              newcourse->status=1;
				newcourse->next = student->checkincourse;
				student->checkincourse = newcourse;
			}

}

int CheckStatusStudent(string studentID, string classID, Classes * & Class) {
  Classes * curCL = Class;
  while (curCL != NULL)
    if (curCL ->  classID == classID) {
      Students * curST = curCL ->  students;
      while (curST != NULL)
        if (curST ->  studentID == studentID)
          return curST ->  Status;
    }
  else
    curCL = curCL ->  next;
  return -2;
}




#pragma region Add

void AddCheckInCourse(Students*& st, string courseID)
{
	CheckinCourse* newcourse = new CheckinCourse;
	newcourse->courseID = courseID;
	newcourse->bitweek = 0;
	newcourse->next = st->checkincourse;
	st->checkincourse = newcourse;

}

void AddScoreBoardCourse(Students*& st, string courseID)
{
	Scoreboards* newcourse = new Scoreboards;
	newcourse->courseName = courseID;
	newcourse->next = st->scoreboards;
	st->scoreboards = newcourse;
}
void AddCourseToClass(Classes*& Class, string courseID, int DayInWeek, int AtNth,int check) {
	
	Students* curST = Class->students;
	while (curST != NULL)
	{
		AddCourseToStudent(curST, courseID, DayInWeek, AtNth,check);
		curST = curST->next;
	}

	
}

void AddClassToCourse(Classes*& Class, string classID, Courses*& course, string courseID) {

	Courses* curCS =findCourse(course,courseID);
	

	CourseClass* courseclass = new CourseClass;
	courseclass->classID = classID;

	cout << "Start Day: ";
	cin >> courseclass->startDate.day;
	cin >> courseclass->startDate.month;
	cin >> courseclass->startDate.year;
	cout << "End Day: ";
	cin >> courseclass->endDate.day;
	cin >> courseclass->endDate.month;
	cin >> courseclass->endDate.year;
	cout << "Day in Week: ";
	cin >> courseclass->DayInWeek;
	cout << "Nth class: ";
	cin >> courseclass->AtNth;
	int DayInWeek = courseclass->DayInWeek, AtNth = courseclass->AtNth;
	//int week= 3;/// just EX

	Classes* curCL = findClass(Class, classID);

	curCL->schedule[DayInWeek][AtNth] = courseID;

	Students* curST = curCL->students;
	courseclass->students = curCL->students;

	int i = 0;
	while (curST != NULL) {

		if (curST->Status == 1)
			courseclass->BitAttend += 1 >> i;
		i++;
		curST = curST->next;
	}
	AddCourseToClass(curCL, courseID, DayInWeek, AtNth,0);

	courseclass->next = curCS->courseclass;
	curCS->courseclass = courseclass;

}



void AddCourseToStudent(Students*& ST, string courseID, int DayInWeek, int AtNth,int check) {

	ST->  schedule[DayInWeek][AtNth] = courseID;

  CheckinCourse * newcourse = new CheckinCourse;
  newcourse ->  courseID = courseID;
  newcourse ->  bitweek = 0;
  newcourse ->  next = ST->checkincourse;
  ST->checkincourse = newcourse;
  if (check)return;
  Scoreboards* SB = new Scoreboards;
  SB->courseName = courseID;
  SB->next = ST->scoreboards;
  ST->scoreboards = SB;

}
#pragma endregion
//void EditScheduleCourseOfStudent()
//void RemoveCourse()


#pragma region EditCourse
void EditScheduleCourseOfClass(Courses * & course, string classID, string courseID, Classes * & Class) {
  Classes * curCL = findClass(Class,classID);
 
  Courses* curCourse = findCourse(course, courseID);

  CourseClass * courseclass = curCourse ->  courseclass;
  while (courseclass ->  classID != classID)
    courseclass = courseclass ->  next;

  int day, nth, day0, nth0, i, j;
  cout << "Day in week: ";
  cin >> day0;
  cout << "nth: ";
  cin >> nth0;
  //change schedule

  for (i = 1; i <= 6; i++)
    for (j = 1; j <= 4; j++)
      if (curCL ->  schedule[i][j] == courseID) {
        curCL ->  schedule[i][j] == "//";
        day = i;
        nth = j;
        break;
      }
  curCL ->  schedule[day0][nth0] = courseID;

  Students * curST = Class ->  students;
  while (curST != NULL) {
    curST ->  schedule[i][j] = "//";
    curST ->  schedule[day0][nth0] = courseID;
    curST = curST ->  next;
  }

  /// change schedule chechou
  OutsideStudent * Outsider = courseclass ->  Outsider;
  curCL = Class;
  while (Outsider != NULL) {
    int k = CheckStatusStudent(Outsider ->  studentID, Outsider ->  classID, Class);
    if (k < 1) {
      Outsider = Outsider ->  next;
      curCL = Class;
      continue;
    }
    while (curCL != NULL)
      if (curCL ->  classID == Outsider ->  classID) {

        curST = Class ->  students;
        while (curST != NULL && curST ->  Status) {

          if (curST ->  studentID == Outsider ->  studentID)

          {
            curST ->  schedule[i][j] = "//";
            curST ->  schedule[day0][nth0] = courseID;
            curCL = Class;
            Outsider = Outsider ->  next;
            k = 1;
            break;
          }
          curST = curST ->  next;
        }

      }
    else
      curCL = curCL ->  next;
  }

}
void EditCourseId(Courses * & course, string NewID, string OldID) {
  Courses * cur = course;
  while (cur ->  courseID != OldID)
    cur ->  next;
  cur ->  courseID = NewID;
}
void EditCourseroom(Courses * & course, string courseID, string room) {
  Courses * cur = course;

  while (cur ->  courseID != courseID)
    cur ->  next;
  cur ->  room = room;
}
void EditCourseLecture(Courses * & course, string name, string courseID) {
  Courses * cur = course;
  while (cur ->  courseID != courseID)
    cur ->  next;
  cur ->  LectureName = name;

}

void EditDateOfCL(Courses*& course, string classID, string courseID)
{
	Courses* curCS = findCourse(course, courseID);
	CourseClass* curCL = findCL(curCS->courseclass, classID);
	cout << "Start date: ";
	cin >> curCL->startDate.day;
	cin >> curCL->startDate.month;
	cin >> curCL->startDate.year;
	cout << "End date: ";
	cin >> curCL->endDate.day;
	cin >> curCL->endDate.month;
	cin >> curCL->endDate.year;

}

#pragma endregion

#pragma region Delete
void DeleteScoreBoardStudent(Students*& ST)
{
	while (ST->scoreboards)
	{
		Scoreboards* SB = ST->scoreboards;
		ST->scoreboards = SB->next;
		delete SB;
		SB = NULL;

	}

}
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
void DeleteStudentFromCourses(string studentID,string classID, Courses* &course)
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



void DeleteScoreBoardOfCourseStudent(Students*& ST, string courseID)
{
	
	Scoreboards* SB = ST->scoreboards, * pre = SB;
	if (SB->courseName == courseID)
	{
		Scoreboards* tmp = ST->scoreboards->next;
		ST->scoreboards = NULL;
		ST->scoreboards = tmp;
		return;
	}
	while (!SB)
	{
		if (SB->courseName == courseID)
		{
			pre->next = SB->next;
			Scoreboards* tmp = SB->next;
			SB = NULL;
			SB = tmp;

		}
		pre = SB;
		SB = SB->next;

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



void RemoveCourseOfScheduleStudent(string schedule[6][4], string courseID) {
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 4; j++)
			if (schedule[i][j] == courseID)
				schedule[i][j] = "//";
}

void DeleteCourseOfCheckin(CheckinCourse * & checkincourse, string courseID) {
  if (checkincourse ->  courseID == courseID) {
    CheckinCourse * tmp = checkincourse;
    checkincourse = checkincourse ->  next;
    tmp = NULL;
  }
  return;
  CheckinCourse * tmp;
  CheckinCourse * cur = checkincourse;
  while (cur != NULL) {
    if (cur ->  courseID == courseID) {
      tmp ->  next = cur ->  next;
      CheckinCourse * del = cur;
      cur = cur ->  next;
      del = NULL;
    }
    tmp = cur;
    cur = cur ->  next;
  }

}
void DeleteCourseScheduleStudent(Students * & student, string courseID, OutsideStudent * & Outsider, Classes * & Class) {
  Students * curST = student;
  while (curST != NULL) {

    RemoveCourseOfScheduleStudent(curST ->  schedule, courseID);
    DeleteCourseOfCheckin(curST ->  checkincourse, courseID);
	DeleteScoreBoardOfCourse(curST, courseID);
    /*CheckinCourse* curCk= curST->checkincourse;
    while(curCk!= NULL)
      if(curCk->courseID== courseID)curCk->status=0;*/
    curST = curST ->  next;
  }


  Classes * curCL = Class;
  while (Outsider != NULL) {
    int k = CheckStatusStudent(Outsider ->  studentID, Outsider ->  classID, Class);
    if (k < 1) {
      Outsider = Outsider ->  next;
      curCL = Class;
      continue;
    }
    while (curCL != NULL && Outsider != NULL)
      if (curCL ->  classID == Outsider ->  classID) {

        curST = Class ->  students;
        while (curST != NULL && curST ->  Status == 1)

          if (curST ->  studentID == Outsider ->  studentID)

        {
          RemoveCourseOfScheduleStudent(curST ->  schedule, courseID);
          DeleteCourseOfCheckin(curST ->  checkincourse, courseID);
		  DeleteScoreBoardOfCourse(curST, courseID);

          break;
        } else
          curST = curST ->  next;

        Outsider = Outsider ->  next;
        curCL = Class;
        break;
      }
    else
      curCL = curCL ->  next;
  }

}

void DeleteCourseScheduleClass(Classes * & Class, string courseID, string classID) {
  Classes * curCL = Class;
  while (curCL != NULL) {
    if (curCL ->  classID == classID) {
      for (int i = 1; i <= 6; i++)
        for (int j = 1; j <= 4; j++)
          if (curCL ->  schedule[i][j] == courseID)
            curCL ->  schedule[i][j] = "//";
      
      return;
    }
    curCL = curCL ->  next;
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