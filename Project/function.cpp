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
#pragma endregion
//void EditScheduleCourseOfStudent()
//void RemoveCourse()


#pragma region EditCourse
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
#pragma endregion

#pragma region Delete
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
/*void InitCourse(Courses * & course, Classes * Class) {

  string a, b;
  while (cin >> a) {
    Courses * newcourse = new Courses;
    newcourse ->  courseID = a;

    cin >> newcourse ->  room;
    cin >> newcourse ->  LectureName;
    newcourse ->  next = course;
    course = newcourse;
    course ->  courseclass = NULL;

    while (cin >> b && b != "------")
      AddClassToCourse(Class, a, course, newcourse ->  courseID);

  }
  
}*/
/*void AddCourse(Courses * & course, Classes * Class) {
  Courses * newcourse = new Courses;
  cout << "courseID: ";
  cin >> newcourse ->  courseID;

  cout << "Room: ";
  cin >> newcourse ->  room;
  cout << "Lecture's name: ";
  cin >> newcourse ->  LectureName;
  newcourse ->  next = course;
  course = newcourse;
  course ->  courseclass = NULL;

  int n;

  do {
    string classID;
    cout << "1.Add Class.";
    cout << "2.Stop.";
    cin >> n;
    if (n == 1)
    {
		cout << "classID :";
		if (!findClass(Class, classID))
		{
			cout << "invalid Class ID.";
			continue;
		}
      cin >> classID;
      AddClassToCourse(Class, classID, course, course ->  courseID);
      break;
    }
  }
  while (n != 2);*/

/*void RemoveStudentFromClass(Classes * & Class, string classID, string studentID) {
  Classes * curCL = Class;
  while (curCL != NULL)
    if (curCL ->  classID == classID) {
      Students * curST = curCL ->  students;;
      while (curST != NULL)
        if (curST ->  studentID == studentID) {
          curST ->  Status = -2;
          break;
        }
      else
        curST = curST ->  next;
      break;
    }
  else
    curCL = curCL ->  next;

}


bool ChangeStudentFromClassAtoB(Classes * & Class, string classAID, string classBID, string studentID, Courses * & course) {
  Classes * curCL = Class;
  Students * curST = NULL;
  while (curCL != NULL)
    if (curCL ->  classID == classAID) {
      curST = curCL ->  students;;
      while (curST != NULL)
        if (curST ->  studentID == studentID) {
          curST ->  Status = -1;
          break;
        }
      else
        curST = curST ->  next;
      break;
    }
  else
    curCL = curCL ->  next;
  if (curST == NULL)return false;
  curCL = Class;
  while (curCL != NULL)
    if (curCL ->  classID == classBID) {
      Students * newST = new Students;
      newST ->  studentID = studentID;
      newST ->  Status = 1;
      newST ->  account = curST ->  account;
      for (int i = 1; i <= 6; i++)
        for (int j = 1; j <= 4; j++)
          newST ->  schedule[i][j] = curCL ->  schedule[i][j];
      newST ->  scoreboards = curST ->  scoreboards;
      FillCheckinCourse(newST);
    }
  UpdateBitAttend(classBID, course);
  return true;

}*/