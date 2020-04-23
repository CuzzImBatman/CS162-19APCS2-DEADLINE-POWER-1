#include"function.h"
int numberOfDay(Date x, Date y);
{
    if (x.month < 3)
    {
        x.year--;
        x.month += 12;
    }
    return 365 * x.year + x.year / 4 - x.year / 100 + x.year / 400 + (153 * x.month - 457) / 5 + x.day - 307-(365 * y.year + y.year / 4 - y.year / 100 + y.year / 400 + (153 * y.month - 457) / 5 + y.day - 307)+1;
}

void memset(short int&checkinList[][],int x,int  y)
{
    for(int i=1; i<=x; i++)
        for(int j=1; j<=y; j++)
            checkinList[i][j]=0;
}
bool Tick(int week, string Course,ViewCheckin *&checkin )
{
    ViewCheckin *cur=checkin;

    int i=1;
    string *x=new string(Course+" X");
    string *v=new string(Course+" Y");

    while(cur!=NULL&& i!=week)
    {
        cur=cur->next;
        i++;
    }
    for(i=1; i<=6; i++)
        for(j=1; j<=4; j++)
            if(*x==cur->viewWeek[i][j])
            {
                cur->viewWeek[i][j]=*v;
                return true;
            }
            else if(*v==cur->viewWeek[i][j])
            {
                cout<<"You've already checked in";
                return false;
            }
    cout<<"Cannot check  in Course";
    return false




}
void viewCheckIn(string &checkinWeek[][], int week)
{
    cout<<"Week: "<<week<<endl;
    cout<<setw(10);
    cout<<"Monay";
    cout<<setw(10);
    cout<<"Tueseday";
    cout<<setw(10);
    cout<<"Wednesday";
    cout<<setw(10);
    cout<<"Thursday";
    cout<<setw(10);
    cout<<"Friday";
    cout<<setw(10);
    cout<<"Saturday";
    cout<<setw(10);

    for(int i=1; i<=6; i++)
        for(int j=1; j<=4; j++ )

            cout<<setw(10)<<checkInWeek[i][j];


}
}
void viewSchedule(Classes *Class)
{
    cout<<setw(10);
    cout<<"Monay";
    cout<<setw(10);
    cout<<"Tueseday";
    cout<<setw(10);
    cout<<"Wednesday";
    cout<<setw(10);
    cout<<"Thursday";
    cout<<setw(10);
    cout<<"Friday";
    cout<<setw(10);
    cout<<"Saturday";
    cout<<setw(10);

    for(int i=1; i<=6; i++)
        for(int j=1; j<=4; j++ )

            cout<<setw(10)<<Class->schedule[i][j];

}
void viewScoreCourse(Students *&student,string course)
{
    Scoreboards scoreboard=student->scoreboards;
    while(scoreboard->courseName!=course)
        scoreboard=scoreboard->next
                   //cout
    }

void changeCheckinList(ViewCheckin *&checkinList,int day,int nth,string courseID)
{
    ViewCheckin *cur=checkinList;
    string *x=new string(courseID+" X");
    string *v=new string(courseID+" Y");
    while(cur!=NULL)
    {
        for(int i=1; i<=6; i++)
            for(int j=1; j<=4; j++)
                if(cur[i][j]== *v)
                    break;
                else if(cur->viewWeek[i][j]== *x)
                {
                    cur->viewWeek[i][j]="//";
                    cur->viewWeek[day][nth]=*x;
                    break;
                }
        cur=cur->next;
    }
}
void EditScheduleCourseOfClass(Course*& course,string classID,string courseID,Classes *&Class)
{
    Classes *curClass=Class;
    Course* curCourse=course;
    while(curClass->classID!=classID)
        curClass=curClass->next;
    while(curCourse->courseID!=courseID)
        curCourse=curCourse->next;

    int day,nth,day0,nth0;
    cout<<"Day in week: ";
    cin>>day0;
    cout<<"nth: ";
    cin>>nth0;
    //change schedule
    for(int i=1; i<=6; i++)
        for(int j=1; j<=4; j++)
            if(curClass->schedule[i][j]==courseID)
            {
                curClass->schedule[i][j]=="//";
                day=i;
                nth=j;
                break;
            }
    schedule[day0][nth0]=courseID;


    Students *student=curClass->students;
    while(student!= NULL)
    {
        changeCheckinList(student->checkinList,day0,nth0,courseID);
        student=student->next;
    }

// change schedule chechou base in courseClass of Course


}
EditCourseId(Course*& course,string NewID,string OldID)
{
    Course*cur=course;
    while(cur->courseID!=OldID)
        cur->next;
    cur->courseID=NewID;
}
EditCourseroom(Course*& course,string courseID,string room)
{
    Course*cur=course;

    while(cur->courseID!=courseID)
        cur->next;
    cur->room=room;
}
EditCourseLecture(Course*& course,string name,string courseID)
{
    Course*cur=course;
    while(cur->courseID!=courseID)
        cur->next;
    cur->LectureName=name;

}

void EditCourse(Course*& course,Classes *&Class)
{
    cin>>n;
    switch(n)
    {
    case 1:
        string NewID,OldID;
        cin>>OldID;
        cin>>NewID;
        EditCourseId(course,NewID,,OldID);
    case 2:
        string ID,room;
        cin>>ID;
        cin>>room;
        EditCourseroom( course, ID, room);
    case 3:

        string classID,courseID;
        cin>>classID;
        cin>>courseID;
        EditScheduleCourseOfClass(course,classID,courseID,Class)
    case 4:
        string courseID;
        string name;
        EditCourseLecture(course,name,courseID);



    }


}
void DeleteCourseSchedule(Classes *&Class,string courseID,string classID)
{
    Classes*cur=Class;
    while(cur!=NULL)
    {
        if(cur->classID==classID)
        {
            for(int i=1; i<=6; i++)
                for(int j=1; j<=4; j++)
                    if(cur->schedule[i][j]==courseID)
                        cur->schedule[i][j]="//";
        }
        cur=cur->next;
    }

}
bool RemoveCourse(Course*& course,string courseID,Classes *&Class)
{
    Course*cur=course;
    course*tmp=new Course;
    course*pre=new Course;
    if(cur->courseID==courseID)
    {
        cur=cur->next;
        course=NULL;
        course=cur;
    }
    while(cur!=NULL)
    {
        if(cur->courseID==courseID)
        {
            while(cur->CourseClass!=NULL)
                DeleteCourseSchedule(Class,courseID,cur->CourseClass->ClassID);
            pre->next=cur->next;
            Node* tmp=cur->next;
            cur=NULL;
            cur=tmp;
            return true
        }
        pre= cur;
        cur=cur->next;
    }
    return false;

}
void RemovedStudentFromCourseClass(Course*& course,string courseID,string classID,int studentID )
{
    Course* curCourse= course;
    while(curCourse->coutseID!=c ourseID)
        curCourse = curCourse->next;
    CourseClass* courseclass = curCourse->courseclass;
    while(courseclass->classID != classID)
        courseclass = courseclass->next;
        int i=0;
        Students* students= courseclass->students;
        while(students->studentID != studentID)i++;
        courseclass->BitAttend -= 2>>i;
}


