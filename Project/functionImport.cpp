#include "function.h"
void ScoreBoardImport(Students* st,  char semes, string year)
{
	Scoreboards* SB = st->scoreboards;
	ofstream out("Yr" + year + "_Sem" + semes + "_StudentID" + st->studentID + "ScoreBoard.txt");
	
	while (SB)
	{
		out << SB->courseName << " " << SB->labScore << " " << SB->midtermScore << " " << SB->finalScore << " " << SB->bonusScore << endl;
		SB = SB->next;
	}

}
void CourseImport(Courses* course, char semes, string year)
{
	ofstream out("Yr" + year + "_Sem" + semes + "_CourseDB.txt");
	
	int i = 0;
	Courses* cs = course;
	while (cs)
	{
		i++;
		cs = cs->next;
	}
	out << i << endl;
	while (course)
	{
		out << course->courseID<<endl;
		out << course->courseName<<endl;
		out << course->LectureName<<endl;
		CourseClass* CL = course->courseclass;
		i = 0;
		while (CL)
		{
			i++;
			CL = CL->next;
		}
		out << i << endl;
		CL = course->courseclass;
		while (CL)
		{
			out << CL->classID;
			out << CL->BitAttend;
			OutsideStudent* OS = CL->Outsider;
			i = 0;
			while (OS) 
			{
				i++; 
				OS = OS->next;
			}
			out << i << endl;
			OS = CL->Outsider;
			while (OS)
			{
				out << OS->studentID;
				out << OS->classID;
				out << endl;
			}
			CL = CL->next;

		}
		course = course->next;
	}

}
void StudentImport(Students* student, string Class, string year)
{
	Students* st = student;
	ofstream out("Yr" + year + "_Cl" + Class + "_StudentDB.txt");
	
	int i = 0;
	while (st)
	{
		i++;
		st = st->next;
	}
	out << i << endl;
	while (st)
	{
		out << st->studentID<<endl;
		for (int i = 0; i < 8; i++)
			out << st->account->pwd.state[i];
		out << st->account->firstname << endl;
		out << st->account->lastname << endl;
		out << st->account->gender << endl;
		out << st->account->doB->day << endl;
		out << st->account->doB->month << endl;
		out << st->account->doB->year << endl;
	}


}