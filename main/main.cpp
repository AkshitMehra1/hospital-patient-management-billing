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
//for basic input/output (cin,cout)

#include<fstream.h>
//for Data file handling for doctors and patients

#include<conio.h>
#include<stdio.h>
#include<string.h>
#define nl '\n'
//for smooth I/O operations

class Feedback
{

 public:

  char Grade;                           //For additional remarks on
  char Remarks[50];	        	//staff and doctors
  //void initGrade();
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
    ff.open("Remarks.dat",ios::in|ios::out|ios::ate);
    ff.seekg(0);
    ff.write((char *)&Remarks,sizeof(Remarks));
  }

  //void

  void giveGrade(char g)
  {
    Grade = g;
  }

  void showGrade()
  {
    cout<<Grade<<nl;
  }

};


class In_Patient_Dept : public Feedback //For In-Patients
{

  char Doctors[10];			//Will temporary store doctors'
  int availableBeds;                    //names in this variable
  int patientCounter;

 public:

  In_Patient_Dept()    			//Constructor for IPD Data
  {
    availableBeds =  50;
    patientCounter = 0;
  }

  void setDoctors()
  {
    char ch = 'y';
    int i = 0;
    fstream ff;
    ff.open("Doctors.dat",ios::in|ios::out|ios::ate);
    ff.seekg(0);
    cout<<"Enter doctor's name: ";
    gets(Doctor[i++]);
    ff.write((char *)&Doctors,sizeof(Doctors));		//Store as you input
    cout<<"Are there more doctors? (y/n): ";
    cin>>ch;
    while(ch == 'y' || ch == 'Y')
    {
      if(i == 10)                       //No more slots available
      {                                 //for more doctors
	cout<<"No more slots available for more doctors."<<nl;
	break;
      }
      cout<<"Enter doctor's name: ";
      gets(Doctor[i++]);
      ff.write((char *)&Doctors,sizeof(Doctors));
      cout<<"Are there more doctors? (y/n): ";
      cin>>ch;
    }
    cout<<"All doctors initialised. Initialising the list.\n";
    ff.close();
    for(int i=0;i<4;i++)
    {
       cout<<".";                   //for visualisation purposes
       delay(1000);
    }
    cout<<"Initialisation done.\n";
  }

  void showDoctors()
  {
    fstream ff;
    ff.open("Doctors.dat",ios::in|ios::out);
    while(ff)
    {
      ff.read((char *)&Doctors,sizeof(Doctors));
      puts(Doctors);
      cout<<nl;
    }
  }

  bool newPatient()                     //returns true if a bed is
  {                                     //available for new patient
    if(!availableBeds)                  //else, return false
    {
      cout<<"No beds available!"<<nl;
      return false;
    }
    else
    {
      ++patientCounter;
      --availableBeds;
      return true;
    }
  }

}ipd;

void bars()
{
  for(int i=0;i<80;i++) cout<<"=";
}

//Driver code below

int main()
{
  clrscr();
  bars();
  getch();
  return 0;
}
