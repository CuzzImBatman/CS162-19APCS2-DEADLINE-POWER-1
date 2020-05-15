#include "function.h"

 using namespace std;

int numberOfDay(Date x, Date y) {
  if (x.month < 3) {
    x.year--;
    x.month += 12;
  }
  if (y.month < 3) {
    y.year--;
    y.month += 12;
  }
  return 365 * x.year + x.year / 4 - x.year / 100 + x.year / 400 + (153 * x.month - 457) / 5 + x.day - 307 - (365 * y.year + y.year / 4 - y.year / 100 + y.year / 400 + (153 * y.month - 457) / 5 + y.day - 307) + 1;
}

void FillCheckinCourse(Students * & student) {
  for (int i = 1; i <= 6; i++)
    for (int j = 1; j <= 4; j++)
      if (student ->  schedule[i][j] != "//") {
        CheckinCourse * newcourse = new CheckinCourse;
        newcourse ->  courseID = student ->  schedule[i][j];
        newcourse ->  bitweek = 0;
        //              newcourse->status=1;
        newcourse ->  next = student ->  checkincourse;
        student ->  checkincourse = newcourse;
      }

}
bool Tick(int week, string courseID, CheckinCourse * & checkincourse) {
  CheckinCourse * cur = checkincourse;

  while (cur != NULL)
    if (cur ->  courseID == courseID /*&& cur->status*/ )
      if ((cur ->  bitweek >> (week - 1)) % 2 == 0) {
        cout << "Cannot check  in Course";
        return false;
      }
  else {
    cur ->  bitweek += 1 << (week - 1);
    return true;
  }

  cout << "Cannot check  in Course";
  return false;

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

void viewCheckIn(CheckinCourse * checkincourse, int week) {
  cout << "Week: " << week << endl;
  while (checkincourse != NULL) {
    int check = 0;
    int bit = checkincourse ->  bitweek;
    cout << setw(10) << checkincourse ->  courseID;
    for (int i = 0; i < 11; i++) {
      int bit = checkincourse ->  bitweek >> i;
      if (bit % 2) {
        check = 1;
        cout << setw(10) << "V";
      } else if (bit % 2 == 0 && !check)
        cout << setw(10) << "-";
      else if (bit % 2 == 0 && check)
        cout << setw(10) << "X";
    }
    cout << endl;
    checkincourse = checkincourse ->  next;
  }

}

void viewSchedule(Students * student) {

  cout << setw(10);
  cout << "Monay";
  cout << setw(10);
  cout << "Tueseday";
  cout << setw(10);
  cout << "Wednesday";
  cout << setw(10);
  cout << "Thursday";
  cout << setw(10);
  cout << "Friday";
  cout << setw(10);
  cout << "Saturday";
  cout << setw(10);

  for (int i = 1; i <= 6; i++)
    for (int j = 1; j <= 4; j++)

      cout << setw(10) << student ->  schedule[i][j];

}
void viewScoreCourse(Students * student, string courseID, string studentID) {
  while (student ->  studentID != studentID)
    student = student ->  next;
  Scoreboards * scoreboard = student ->  scoreboards;
  while (scoreboard != NULL)
    if (scoreboard ->  courseName == courseID) {
      cout << courseID << endl;
      cout << setw(10) << "midtermScore";
      cout << setw(10) << "finalScore";
      cout << setw(10) << "labScore";
      cout << setw(10) << "bonusScore";

      cout << setw(10) << scoreboard ->  midtermScore;
      cout << setw(10) << scoreboard ->  finalScore;
      cout << setw(10) << scoreboard ->  labScore;
      cout << setw(10) << scoreboard ->  bonusScore;

      break;
    }
  else
    scoreboard = scoreboard ->  next;
}

void AddCourseToStudent(Classes * & Class, string studentID, string classID, string courseID, int DayInWeek, int AtNth) {

  Classes * curCL = Class;
  while (curCL ->  classID != classID)
    curCL = curCL ->  next;
  Students * curST = curCL ->  students;
  while (curST ->  studentID != studentID)
    curST = curST ->  next;
  curST ->  schedule[DayInWeek][AtNth] = courseID;
  CheckinCourse * checkincourse = curST ->  checkincourse;
  CheckinCourse * newcourse = new CheckinCourse;
  newcourse ->  courseID = courseID;
  newcourse ->  bitweek = 0;
  //    newcourse->status=1;
  newcourse ->  next = checkincourse;
  checkincourse = newcourse;

}
void AddCourseToClass(Classes * & Class, string classID, string courseID, int DayInWeek, int AtNth) {
  Classes * curCL = Class;
  while (curCL ->  classID != classID)
    curCL = curCL ->  next;
  Students * curST = curCL ->  students;
  while (curST != NULL) {
    curST ->  schedule[DayInWeek][AtNth] = courseID;
    CheckinCourse * checkincourse = curST ->  checkincourse;
    CheckinCourse * newcourse = new CheckinCourse;
    newcourse ->  courseID = courseID;
    newcourse ->  bitweek = 0;
    //        newcourse->status=1;
    newcourse ->  next = checkincourse;
    checkincourse = newcourse;
    curST = curST ->  next;

  }
}

void AddClassToCourse(Classes * & Class, string classID, Courses * & course, string courseID) {

  Courses * curCS = course;
  while (curCS ->  courseID != courseID)
    curCS = curCS ->  next;

  CourseClass * courseclass = new CourseClass;
  courseclass ->  classID = classID;

  cout << "Start Day: ";
  cin >> courseclass ->  startDate.day;
  cin >> courseclass ->  startDate.month;
  cin >> courseclass ->  startDate.year;
  cout << "End Day: ";
  cin >> courseclass ->  endDate.day;
  cin >> courseclass ->  endDate.month;
  cin >> courseclass ->  endDate.year;
  cout << "Day in Week: ";
  cin >> courseclass ->  DayInWeek;
  cout << "Nth class: ";
  cin >> courseclass ->  AtNth;
  int DayInWeek = courseclass ->  DayInWeek, AtNth = courseclass ->  AtNth;
  //int week= 3;/// just EX

  Classes * curCL = Class;
  while (curCL ->  classID != classID)
    curCL = curCL ->  next;

  curCL ->  schedule[DayInWeek][AtNth] = courseID;

  Students * curST = curCL ->  students;
  courseclass ->  students = curCL ->  students;

  int i = 0;
  while (curST != NULL) {

    if (curST ->  Status == 1 || curST ->  Status == 0)
      courseclass ->  BitAttend += 1 >> i;
    i++;
    curST = curST ->  next;
  }
  AddCourseToClass(curCL, classID, courseID, DayInWeek, AtNth);

  courseclass ->  next = curCS ->  courseclass;
  curCS ->  courseclass = courseclass;

}
//void EditScheduleCourseOfStudent()
//void RemoveCourse()
void RemoveCourseOfScheduleStudent(string schedule[6][4], string courseID) {
  for (int i = 1; i <= 6; i++)
    for (int j = 1; j <= 4; j++)
      if (schedule[i][j] == courseID)
        schedule[i][j] = "//";
}
void EditScheduleCourseOfClass(Courses * & course, string classID, string courseID, Classes * & Class) {
  Classes * curCL = Class;
  while (curCL ->  classID != classID)
    curCL = curCL ->  next;

  Courses * curCourse = course;
  while (curCourse ->  courseID != courseID)
    curCourse = curCourse ->  next;

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

void EditCourse(Courses * & course, Classes * & Class) {
  int n = 1;
  do {

    string courseID, room, NewID, OldID, name, classID, Lname;
    cout << "Menu: " << endl;
    cout << "1.Change course ID. " << endl;;
    cout << "2.change Room." << endl;
    cout << "3.Change Schedule course of a class." << endl;
    cout << "4.Change Course Lecture." << endl;
    cout << " Press 0 to stop.";
    cin >> n;
    switch (n) {
    case 1:
      cout << "Course ID: ";
      cin >> OldID;
      cout << "New course ID: ";
      cin >> NewID;
      EditCourseId(course, NewID, OldID);
      break;
    case 2:
      cout << "Course ID: ";
      cin >> courseID;
      cout << "New room: ";
      cin >> room;
      EditCourseroom(course, courseID, room);
      break;

    case 3:
      cout << "Class ID: ";
      cin >> classID;
      cout << "Course ID: ";
      cin >> courseID;
      EditScheduleCourseOfClass(course, classID, courseID, Class);
      break;

    case 4:
      cout << "New lecture: ";
      cin >> Lname;
      cout << "Course ID: ";
      cin >> courseID;
      EditCourseLecture(course, Lname, courseID);
      break;

    }

  }
  while (n);

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
      /* Students curST=Class->students;
       while(curST!=NULL)
       {
          DeleteCourseOfCheckin(curST->checkincourse,courseID);
           curST= curST->next;
       }*/
      return;
    }
    curCL = curCL ->  next;
  }

}

bool DeleteCourse(Courses * & course, string courseID, Classes * & Class) {
  Courses * cur = course;
  Courses * tmp = new Courses;
  Courses * pre = new Courses;
  if (cur ->  courseID == courseID) {
    CourseClass * courseclass = cur ->  courseclass;

    while (courseclass != NULL) {
      DeleteCourseScheduleStudent(courseclass ->  students, courseID, courseclass ->  Outsider, Class);
      DeleteCourseScheduleClass(Class, courseID, courseclass ->  classID);
      courseclass = courseclass ->  next;
    }

    cur = cur ->  next;
    course = NULL;
    course = cur;
    return true;
  }
  while (cur != NULL) {
    if (cur ->  courseID == courseID) {

      CourseClass * courseclass = cur ->  courseclass;

      while (courseclass != NULL) {
        DeleteCourseScheduleStudent(courseclass ->  students, courseID, courseclass ->  Outsider, Class);
        DeleteCourseScheduleClass(Class, courseID, courseclass ->  classID);
        courseclass = courseclass ->  next;
      }

      pre ->  next = cur ->  next;
      Courses * tmp = cur ->  next;
      cur = NULL;
      cur = tmp;
      return true;
    }
    pre = cur;
    cur = cur ->  next;
  }
  return false;

}

void RemovedStudentFromCourseClass(Courses * & course, string courseID, string classID, string studentID) {
  Courses * curCourse = course;
  while (curCourse ->  courseID != courseID)
    curCourse = curCourse ->  next;
  CourseClass * courseclass = curCourse ->  courseclass;
  while (courseclass ->  classID != classID)
    courseclass = courseclass ->  next;
  int i = 0;
  Students * students = courseclass ->  students;
  while (students ->  studentID != studentID)
    i++;
  courseclass ->  BitAttend -= 1 >> i;
  DeleteCourseOfCheckin(students ->  checkincourse, courseID);
  RemoveCourseOfScheduleStudent(students ->  schedule, courseID);

  //1 inside
  //0 outsie
}

bool AddStudentToCourseClass(Courses * & course, Classes * & Class, string courseID, string classID, string classIDOut, string studentID) {

  Courses * curCourse = course;
  while (curCourse ->  courseID != courseID)
    curCourse = curCourse ->  next;
  CourseClass * courseclass = curCourse ->  courseclass;
  while (courseclass ->  classID != classID)
    courseclass = courseclass ->  next;
  ///
  int i = 0;
  Students * curST = courseclass ->  students;
  while (curST != NULL)
    if (curST ->  studentID == studentID)
      if ((courseclass ->  BitAttend >> i) % 2)
        return false;
      else {
        courseclass ->  BitAttend += 1 << i;
        break;
      }
  else
    curST = curST ->  next;

  ///

  OutsideStudent * Outsider = new OutsideStudent;
  Outsider ->  classID = classIDOut;
  Outsider ->  studentID = studentID;
  Outsider ->  next = courseclass ->  Outsider;
  courseclass ->  Outsider = Outsider;
  AddCourseToStudent(Class, studentID, classIDOut, courseID, courseclass ->  DayInWeek, courseclass ->  AtNth);
  return true;
}
void InitCourse(Courses * & course, Classes * Class) {

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

}
void AddCourse(Courses * & course, Classes * Class) {
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
      cin >> classID;
      AddClassToCourse(Class, classID, course, course ->  courseID);
      break;
    }
  }
  while (n != 2);

}

///
void RemoveStudentFromClass(Classes * & Class, string classID, string studentID) {
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

void UpdateBitAttend(string classID, Courses * & course) {
  Courses * curCS = course;
  while (curCS != NULL) {
    CourseClass * cur = curCS ->  courseclass;
    while (cur != NULL)
      if (cur ->  classID == classID) {
        cur ->  BitAttend =( cur ->  BitAttend)>>1 + 1;
        break;
      }
    else
      cur = cur ->  next;
    curCS = curCS ->  next;
  }
}
void ChangeStudentFromClassAtoB(Classes * & Class, string classAID, string classBID, string studentID, Courses * & course) {
  Classes * curCL = Class;
  Students * curST;
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

}
///
