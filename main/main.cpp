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
    strcpy(Remarks, s);
  }

  void writeRemarks()			//Write remarks in binary file
  {
    fstream ff;
    ff.open("Remarks.dat", ios::in|ios::out|ios::ate);
    ff.seekg(0);
    ff.write((char *) &Remarks, sizeof(Remarks));
  }

  void giveGrade(char g)
  {
    Grade = g;
  }

  void showGrade()
  {
    cout << Grade << nl;
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
    ff.open("Doctors.dat", ios::in|ios::out|ios::ate);
    ff.seekg(0);
    cout << "Enter doctor's name: ";
    gets(Doctor[i++]);
    ff.write((char *) &Doctors, sizeof(Doctors));		//Store as you input
    cout << "Are there more doctors? (y/n): ";
    cin >> ch;
    while(ch == 'y' || ch == 'Y')
    {
      if(i == 10)                       //No more slots available
      {                                 //for more doctors
	      cout << "No more slots available for more doctors." << nl;
	      break;
      }
      cout << "Enter doctor's name: ";
      gets(Doctor[i++]);
      ff.write((char *) &Doctors, sizeof(Doctors));
      cout << "Are there more doctors? (y/n): ";
      cin >> ch;
    }
    cout << "All doctors initialised. Initialising the list." << nl;
    ff.close();
    for(int i = 0; i < 4; i++)		//for visualisation purposes
    {
       cout << ".";
       delay(1000);
    }
    cout << "Initialisation done." << nl;
  }

  void showDoctors()
  {
    fstream ff;
    ff.open("Doctors.dat", ios::in | ios::out);
    while(ff)
    {
      ff.read((char *) &Doctors, sizeof(Doctors));
      puts(Doctors);
      cout << nl;
    }
  }

  bool newPatient()                     //returns true if a bed is
  {                                     //available for new patients
    if(!availableBeds)                  //else, returns false
    {
      cout << "No beds available!" << nl;
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


class Out_Patient_Dept : public Feedback
{
  struct appointment
  {
    char name[20];
    char sex;
    char treatment[20];
  };
  appointment ap;
  fstream ff;
  ff.open("Appointees.dat", ios::in | ios::out | ios::app);
  void addAppointment()
  {
    char ch = 'n';
    loop:;
    cout << "Enter appointee name: ";
    gets(ap.name);
    cout << "Enter gender (m/f): ";
    cin >> ap.sex;
    cout << "Enter treatment: ";
    gets(ap.treatment);
    ff.write((char *) &ap, sizeof(ap));
    cout << "Do you want to enter more? (y/n): ";
    cin >> ch;
    if(ch == 'y' || ch == 'Y')
      goto loop;
  }
  
}opd;

void bars()
{
  for(int i=0;i<80;i++)
    cout << "=";
}

void welcomeScreen()
{
  bars();
  gotoxy(39, 0);
  cout << "~ WELCOME TO ABC HOSPITAL ~" << nl;
  bars();
}

//Driver code below

int main()
{
  clrscr();
  welcomeScreen();
  getch();
  return 0;
}
