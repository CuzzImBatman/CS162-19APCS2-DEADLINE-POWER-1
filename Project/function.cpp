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

bool Tick(int week, string Course,viewCheckin *&checkin )
{
    int i=1;
    string *x=new string(Course+" X");
    string *v=new string(Course+" Y");
    viewCheckin *cur=checkin;
    while(cur!=NULL&& i!=week)
        cur=cur->next;
    for(i=1; i<=6; i++)
        for(j=1; j<=4; j++)
            if(x==cur->viewWeek[i][j])
            {
                cur->viewWeek[i][j]=*v;
                return true;
            }
            else if(v==cur->viewWeek[i][j])
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
void viewScoreCourse(Students *student ,string course)
{
    Scoreboards scoreboard=student->scoreboards;
    while(scoreboard->courseName!=course)scoreboard=scoreboard->next
        //cout
}
void EditScheduleCourseOfClass(Course*& course,Classes *&Class)
{
    string courseID = course->courseID;
    int day,nth;
    cout<<"Day in week: ";
    cin>>day;
    cout<<"nth: ";
    cin>>n;


}
void EditCourse()
