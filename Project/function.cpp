#include "function.h"

 using namespace std;

int numberOfDay(Date x) {
	int j = 1, day = 0, month = 0, year = 0;
	for (int i = x.day.length() - 1; i >= 0; i--)
	{
		day += (x.day[i] - 48) * j;
		j *= 10;
	}
	j = 1;
	for (int i = x.month.length() - 1; i >= 0; i--)
	{
		month += (x.month[i] - 48) * j;
		j *= 10;
	}
	j = 1;
	for (int i = x.year.length() - 1; i >= 0; i--)
	{
		year += (x.year[i] - 48) * j;
		j *= 10;
	}
  if (month < 3) {
    year--;
    month += 12;
  }
  
  return 365 * year + year / 4 - year / 100 + year / 400 + (153 * month - 457) / 5 + day - 307;
}

void UpdateBitAttend(string classID, Courses*& course) {
	Courses* curCS = course;
	while (curCS != NULL) {
		CourseClass* cur = curCS->courseclass;
		while (cur != NULL)
			if (cur->classID == classID) {
				cur->BitAttend =( (cur->BitAttend) >> 1) + 1;
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
void AddCourseToClass(Classes*& Class, Courses*& course, int DayInWeek, int AtNth,int check) {
	
	Students* curST = Class->students;
	while (curST != NULL)
	{
		AddCourseToStudent(curST, course, DayInWeek, AtNth,check);
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
	string temp;
	cin >> temp;
	switch (temp[1]) { //Mo Tu We Th Fr Sa
	case 'o':
		courseclass->DayInWeek = 0;
		break;
	case 'u':
		courseclass->DayInWeek = 1;
		break;
	case 'e':
		courseclass->DayInWeek = 2;
		break;
	case 'h':
		courseclass->DayInWeek = 3;
		break;
	case 'r':
		courseclass->DayInWeek = 4;
		break;
	case 'a':
		courseclass->DayInWeek = 5;
		break;
	}
	int hour, minute;
	cin >> hour >> minute;
	switch (hour) {
	case 7:
		courseclass->AtNth = 0;
		break;
	case 9:
		courseclass->AtNth = 1;
		break;
	case 13:
		courseclass->AtNth = 2;
		break;
	case 15:
		courseclass->AtNth = 3;
		break;
	}
	int DayInWeek = courseclass->DayInWeek, AtNth = courseclass->AtNth;
	//int week= 3;/// just EX

	Classes* curCL = findClass(Class, classID);

	curCL->schedule[DayInWeek][AtNth] = courseID;

	Students* curST = curCL->students;
	courseclass->students = curCL->students;

	int i = 0;
	while (curST != NULL) {

		if (curST->Status == 1)
			if (!i)courseclass->BitAttend= 1;
			else courseclass->BitAttend +=( 1 >> i);
		i++;
		curST = curST->next;
	}
	AddCourseToClass(curCL, curCS, DayInWeek, AtNth,0);

	courseclass->next = curCS->courseclass;
	curCS->courseclass = courseclass;

}



void AddCourseToStudent(Students*& ST, Courses*& course, int DayInWeek, int AtNth,int check) {

	ST->  schedule[DayInWeek][AtNth] = course->courseID;

  CheckinCourse * newcourse = new CheckinCourse;
  newcourse ->  courseID =course-> courseID;
  newcourse ->  bitweek = 0;
  newcourse ->  next = ST->checkincourse;
  ST->checkincourse = newcourse;

  Scoreboards* SB = new Scoreboards;
  if (check) {
	  SB->courseName = course->courseName;
	  return;
  }
  SB->courseID = course->courseID;
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

  for (i = 0; i < 6; i++)
    for (j = 0; j < 4; j++)
      if (curCL ->  schedule[i][j] == courseID) {
        curCL ->  schedule[i][j] == "//";
        day = i;
        nth = j;
        break;
      }
  curCL ->  schedule[day0][nth0] = courseID;

  Students * curST = Class ->  students;
  while (curST != NULL) {
	  if (i < 6 && j < 4 && i >= 0 && j >= 0)curST->schedule[i][j] = "//";
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
void Edit_CourseID_Student(Students* st, string NewID, string OldID)
{
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 4; j++)
			if (st->schedule[i][j] == OldID)st->schedule[i][j] = NewID;
	CheckinCourse* ck = st->checkincourse;
	while (ck)
		if (ck->courseID == OldID)
		{
			ck->courseID = NewID;
			break;
		}
		else ck = ck->next;
	Scoreboards* sb = st->scoreboards;
	while (sb)
	{
		if (sb->courseID == OldID)
		{
			sb-> courseID = NewID;
			break;
		}
		else sb = sb->next;
	}
}
void Edit_CourseID_Class(Classes*& Class, string NewID,string OldID)
{
	
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 4; j++)
			if (Class->schedule[i][j] == OldID)Class->schedule[i][j] = NewID;
	Students* st = Class->students;
	while (st)
	{
		Edit_CourseID_Student(st, NewID, OldID);
		st = st->next;
	}
}
void EditCourseId(Courses * & course, string NewID, Classes*& Class) {
  CourseClass * cur = course->courseclass;
  while (cur)
  {
	  Classes* cl = findClass(Class, cur->classID);
	  if (cl)Edit_CourseID_Class(cl, NewID, course->courseID);
	  OutsideStudent* OS = cur->Outsider;
	  while (OS)
	  {
		  cl = findClass(Class, OS->classID);
		  if (cl)
		  {
			  Students* st = findStudent(cl->students, OS->studentID);
			  if (st)Edit_CourseID_Student(st, NewID, course->courseID);
			  OS = OS->next;
		  }
	  }
	  cur = cur->next;
  }
  course->  courseID = NewID;
}
void Edit_CourseName_Student(Students* st, string NewName, string OldName)
{
	
	Scoreboards* sb = st->scoreboards;
	while (sb)
	{
		if (sb->courseName == OldName)
		{
			sb-> courseName = NewName;
			break;
		}
		else sb = sb->next;
	}
}
void EditCourseName(Courses*& course, string NewName, Classes*& Class) {
	CourseClass* cur = course->courseclass;
	Classes* cl;
	while (cur)
	{
		Students* st = cur->students;
		while (st)
		{
			Edit_CourseName_Student(st, NewName, course->courseName);
			st = st->next;
		}
		OutsideStudent* OS = cur->Outsider;
		while (OS)
		{
			cl = findClass(Class, OS->classID);
			if (cl)
			{
				 st = findStudent(cl->students, OS->studentID);
				if (st)Edit_CourseName_Student(st, NewName, course->courseName);
				OS = OS->next;
			}
		}
		cur = cur->next;
	}
	course->courseName = NewName;
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
bool bigger(int a, int b)
{
	if (a > b)return true;
	return false;
}
bool smaller(int a, int b)
{
	if (a > b)return false;
	return true;
}
bool checkDay(string &a, int x, bool(*compare)(int,int))
{
	int j = 1, sum = 0;
	for (int i = a.length() - 1; i >= 0; i--)
	{
		sum += (a[i] - 48) * j;
		j *= 10;
	}
	if (compare(sum, x) || j==0)return  false;
	else
		while (a[0] == '0'&& a.length()>2)a.erase(0, 1);

	
	return true;
}
bool checkMonth(Date a)
{
	int j = 1, day = 0,month=0;
	for (int i = a.day.length() - 1; i >= 0; i--)
	{
		day += (a.day[i] - 48) * j;
		j *= 10;
	}
	j = 1;
	for (int i = a.month.length() - 1; i >= 0; i--)
	{
		month += (a.month[i] - 48) * j;
		j *= 10;
	}
	if (day == 31)
		if (month == 2 || month == 4 || month == 6 || month == 9 || month == 11)return false;
	if (day == 30)
		if (month == 2)return false;
	return true;
}
bool checkYear(Date a)
{
	int j = 1, day = 0, month = 0,year=0;
	for (int i = a.day.length() - 1; i >= 0; i--)
	{
		day += (a.day[i] - 48) * j;
		j *= 10;
	}
	j = 1;
	for (int i = a.month.length() - 1; i >= 0; i--)
	{
		month += (a.month[i] - 48) * j;
		j *= 10;
	}
	j = 1;
	for (int i = a.year.length() - 1; i >= 0; i--)
	{
		year += (a.year[i] - 48) * j;
		j *= 10;
	}
	if (year % 100 == 0)year /= 100;
	if (day == 29 && month == 2)
		if (year % 4)return false;
	
	          
		
			
	return true;

}
void EditDateOfCL(Courses*& course, string classID, string courseID,  string year)
{
	Courses* curCS = findCourse(course, courseID);
	CourseClass* curCL = findCL(curCS->courseclass, classID);
	int YEAR = 0, j = 1;
	for (int i = year.length()-1; i >= 0; i--)
	{
		YEAR += (year[i] - 48) * j;
		j *= 10;
	}
	cout << "Start date: "<<endl;
	
	do
	{
		cout << "Day : " ; 
		cin >> curCL->startDate.day;
		if (!checkDay(curCL->startDate.day, 31,bigger))cout << "Invalid day, please enter again. " << endl;
	} while (!checkDay(curCL->startDate.day, 31, bigger));
	do
	{
		cout << "month: ";
		cin >> curCL->startDate.month;
		if (!checkDay(curCL->startDate.month, 12, bigger)) {
			cout << "Invalid month, please enter again. " << endl; 
			continue;
		}
		if(!checkMonth(curCL->startDate))cout << "Invalid month, please enter again. " << endl;
	} while (!checkDay(curCL->startDate.month, 12, bigger) || !checkMonth(curCL->startDate));
	
	do
	{
		cout << "year: ";
		cin >> curCL->startDate.year;
		if (!checkDay(curCL->startDate.year, YEAR, smaller))
		{
			cout << "Invalid year, please enter again. " << endl;
			continue;
		}
		if(!checkYear(curCL->startDate))cout << "Invalid year, please enter again. " << endl;
	} while (!checkDay(curCL->startDate.year, YEAR, smaller) || !checkYear(curCL->startDate));
	cout << "End date: "<<endl;
	do
	{
		cout << "Day : ";
		cin >> curCL->endDate.day;
		if (!checkDay(curCL->endDate.day, 31, bigger))cout << "Invalid day, please enter again. " << endl;
	} while (!checkDay(curCL->endDate.day, 31, bigger));
	do
	{
		cout << "month: ";
		cin >> curCL->endDate.month;
		if (!checkDay(curCL->endDate.month, 12, bigger)) {
			cout << "Invalid month, please enter again. " << endl;
			continue;
		}
		if (!checkMonth(curCL->endDate))cout << "Invalid month, please enter again. " << endl;
	} while (!checkDay(curCL->endDate.month, 12, bigger) || !checkMonth(curCL->endDate));

	do
	{
		cout << "year: ";
		cin >> curCL->endDate.year;
		if (numberOfDay(curCL->endDate)- numberOfDay(curCL->startDate)<=0)
		{
			cout << "Invalid year, please enter again. " << endl;
			continue;
		}
		if (!checkYear(curCL->endDate))cout << "Invalid year, please enter again. " << endl;
	} while ((numberOfDay(curCL->endDate) - numberOfDay(curCL->startDate) <= 0) || !checkYear(curCL->endDate));

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


void DeleteScoreBoardOfCourseStudent(Students*& ST, string courseName)
{
	
	Scoreboards* SB = ST->scoreboards, * pre = SB;
	if (SB->courseName == courseName)
	{
		Scoreboards* tmp = ST->scoreboards->next;
		ST->scoreboards = NULL;
		ST->scoreboards = tmp;
		return;
	}
	while (!SB)
	{
		if (SB->courseName == courseName)
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

void DeleteScoreBoardOfCourse(Students* &ST, string courseName)
{
	Students* st = ST;
	while (st)
	{
		DeleteScoreBoardOfCourseStudent(st, courseName);
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

void DeleteCourseScheduleStudent(Students * & student, Courses*& course, OutsideStudent * & Outsider, Classes * & Class) {
  Students * curST = student;
  while (curST != NULL) {
    RemoveCourseOfScheduleStudent(curST ->  schedule,course-> courseID);
    DeleteCourseOfCheckin(curST ->  checkincourse, course->courseID);
	DeleteScoreBoardOfCourse(curST, course->courseName);
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
          RemoveCourseOfScheduleStudent(curST ->  schedule, course->courseID);
          DeleteCourseOfCheckin(curST ->  checkincourse, course->courseID);
		  DeleteScoreBoardOfCourse(curST, course->courseName);

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
Semesters* FindSemester(AcademicYears* &AY, AcademicYears* &ay)
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
	ay = y;
	Semesters* s = NULL;
	char sems;
	while (!s)
	{
		cout << "\nPlease enter semester: ";
		cin >> sems;
		s = y->semesters;
		while (s)
			if (sems - s->semesterNo == 0)break;
			else s = s->next;
		if(!s)cout << "Invalid semester, please enter again." << endl;		
	}
	return s;

}
AcademicYears *inputYear(AcademicYears* year,Courses* &course)
{

	string courseID, classID;
	string Year;
	AcademicYears* y = NULL;
	while (!y)
	{
		cout << "\nPlease enter Academic Year: ";
		cin >> Year;
		y = year;
		while (y)
			if (y->year == Year)break;
			else y = y->next;
		if (!y)cout << "Invalid Academic Year, please enter again." << endl;
	}
	
	Semesters* s = NULL;
	while (!s)
	{
		cout << "Please enter course ID: ";
		cin >> courseID;
		s = y->semesters;
		while (s)
		{
			course = findCourse(s->courses, courseID);
			if (!course)s = s->next;
			else break;
		}
		if (!s)cout << "Invalid course ID, please enter again." << endl;
	}
	return y;
}