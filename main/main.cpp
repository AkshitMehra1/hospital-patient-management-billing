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
//for basic input/output (cin, cout)

#include<fstream.h>
//for Data file handling for doctors and patients

#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<dos.h>
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

 public:

  char Doctors[10];			//Will temporary store doctors'
  int availableBeds;                    //names in this variable
  int patientCounter;

  In_Patient_Dept()    			//Constructor for IPD Data
  {
    availableBeds =  50;
    patientCounter = 0;
  }

  void showDoctors();
  void setDoctors();

  int newPatient()                      //returns true if a bed is
  {                                     //available for new patients
    if(!availableBeds)                  //else, returns false
    {
      cout << "No beds available!" << nl;
      return 0;
    }
    else
    {
      ++patientCounter;
      --availableBeds;
      return 1;
    }
  }

}ipd;

void In_Patient_Dept::showDoctors()
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

struct Docs
{
  char Doctor[10];
};

void In_Patient_Dept::setDoctors()
  {
    char ch = 'y';
    Docs Doctors[10];
    int i = 0;
    fstream ff;
    ff.open("Doctors.dat", ios::in|ios::out|ios::ate);
    ff.seekg(0);
    cout << "Enter doctor's name: ";
    gets(Doctors[i++].Doctor);
    ff.write((char *) &Doctors[i], sizeof(Doctors[i]));		//Store as you input
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
      gets(Doctors[i++].Doctor);
      ff.write((char *) &Doctors, sizeof(Doctors));
      cout << "Are there more doctors? (y/n): ";
      cin >> ch;
    }
    cout << "All doctors initialised. Initialising the list." << nl;
    ff.close();
    for(i = 0; i < 4; i++)		//for visualisation purposes
    {
       cout << ".";
       delay(1000);
    }
    cout << "Initialisation done." << nl;
  }

class Out_Patient_Dept : public Feedback
{

 public:

  struct appointment
  {
    char name[20];
    char sex;
    char treatment[20];
  }ap;

  void addAppointment();

}opd;

void Out_Patient_Dept::addAppointment()
{
  fstream ff("Appointees.dat", ios::in | ios::out | ios::app);
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
  goto loop;
}

void bars()
{
  for(int i=0;i<80;i++)
    cout << "=";
}

void welcomeScreen()
{
  bars();
  cout << "                          ~ WELCOME TO ABC HOSPITAL ~" << nl;
  bars();
  cout << nl;
}

//Driver code below

int main()
{
  clrscr();
  code1:;
  welcomeScreen();
  int MenuChoice;
  cout << " | Menu | " << nl;
  cout << "1. In Patient" << nl;
  cout << "2. Out Patient" << nl;
  cout << nl;
  cout << "Enter choice: ";
  cin >> MenuChoice;
  switch(MenuChoice)
  {
    case 1: code:;
	    cout << "You are in the IN-PATIENT-DEPARTMENT" << nl;
	    cout << " | Menu | " << nl;
	    cout << "1. Add doctors" << nl;
	    cout << "2. Show doctors" << nl;
	    cout << "3. Check if new patient accomodable" << nl;
	    cout << "4. Enter feedback" << nl;
	    cout << nl;
	    cout << "Enter choice: ";
	    cin >> MenuChoice;
	    switch(MenuChoice)
	    {
	      case 1: ipd.setDoctors();
		      break;
	      case 2: ipd.showDoctors();
		      break;
	      case 3: if(ipd.newPatient() == 1)
		      {
			cout << "New Patient Accomodable" << nl;
		      }
		      break;
	      case 4: char grade, remarks[50];
		      cout << "Enter grade for the department: ";
		      cin >> grade;
		      ipd.giveGrade(grade);
		      cout << "Enter remarks: ";
		      gets(remarks);
		      ipd.giveRemarks(remarks);
		      ipd.writeRemarks();
		      break;
	      default: cout << "Invalid choice!!" << nl;
		       goto code;
	    }
	    break;
    case 2: code2:;
	    cout << "You are in the OUT-PATIENT-DEPARTMENT" << nl;
	    cout << " | Menu | " << nl;
	    cout << "1. Add Appointment" << nl;
	    cout << "2. Enter feedback" << nl;
	    cout << nl;
	    cout << "Enter choice: ";
	    cin >> MenuChoice;
	    switch(MenuChoice)
	    {
	      case 1: opd.addAppointment();
		      break;
	      case 2: char grade, remarks[50];
		      cout << "Enter grade for the department: ";
		      cin >> grade;
		      opd.giveGrade(grade);
		      cout << "Enter remarks: ";
		      gets(remarks);
		      opd.giveRemarks(remarks);
		      opd.writeRemarks();
		      break;
	      default: cout << "Wrong choice!!" << nl;
		       goto code;
	    }
  }
  char ch;
  cout << nl;
  cout << "Do you want to continue? (y/n): ";
  cin >> ch;
  if(ch == 'y' || ch == 'Y')
    goto code1;
  getch();
  return 0;
}
