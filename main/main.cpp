/*
   The software pertaining to the source
   code below provides an integrated environments
   for the different departments of a hospitals,
   providing real-life functions and
   facilities.
   The facilities range from Consultations
   to In-Patient handling and side-by-side
   invoice generation.
*/

#include<iostream.h>
#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>


class Feedback
{

 public:

  char Grade;
  char Remarks[100];	        	//For additional remarks on
  //void initGrade();                   //staff and doctors
  //void giveRemarks(char []);
  //void giveGrade(char);

  Feedback()                      	//Set initial grade to 'A'
  {
    Grade = 'A';
  }

  void giveRemarks(char s[])     	//Set Remarks for staff and doctors
  {
    strcpy(Remarks,s);
  }

  void writeRemarks()			//Write remarks in binary file
  {
    fstream ff;
    ff.open("Remarks.dat",ios::in|ios::out|ios::app);
    ff.write((char *)&Remarks,sizeof(Remarks));
  }

};


class In_Patient_Dept : public Feedback //For In-Patients
{

  char Doctors[10][20];


 public:

  void setDoctors()

}ipd;


void bars()
{
  for(int i=0;i<79;i++) cout<<"=";
}


int main()
{
  clrscr();
  getch();
  return 0;
}
