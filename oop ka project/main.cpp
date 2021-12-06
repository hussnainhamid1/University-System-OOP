#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<string.h>
using namespace std;

class Person
{
public:
	Person()
	{

	}
	virtual void print()
	{

	}
	~Person()
	{

	}
};
 

class Employee: public Person
{
	int no;
public:
	Employee();
	Employee(int number)
	{
		no = number;
	}
	void print()
	{
		cout << " the Employyee number is   "<<no;
	}
	int getEmployeeNo()
	{
		return no;
	}
	~Employee()
	{

	}
};


class Registration
{
	char* attendence;
	int* marks;
	char* grade;       
public:
	Registration()
	{
		marks = nullptr;
		grade = new char[2];
		attendence = new char[30];
		for (int i = 0; i < 30; i++)
			attendence[i] = 'N';
		grade[0] = 'N';
		grade[1] = '0';
	}
	Registration(char a[], int m[],char g[])
	{
		grade = new char[2];
		attendence = new char[30];
		marks = new int[5];
		for (int i = 0; i < 30; i++)
			attendence[i] = a[i];
		for (int i = 0; i < 5; i++)
			marks[i] = m[i];
		for (int i = 0; i < 2; i++)
			grade[i] = g[i];
	}
	void print()
	{
		cout << attendence << endl;
		for (int i = 0; i < 5; i++)
			cout << marks[i] << endl;
	}
	char* getAttendence()
	{
		return attendence;
	}
	int* getMarks()
	{
		return marks;
	}
	void withDraw()
	{
		if (grade[0] == 'N')
		{
			int flag = 0;
			for (int i = 0; i < 26; i++)
			{
				if (attendence[i] == 'N')
					flag = 1;
			}
			if (flag == 0)
			{
				grade[0] = 'W';
				grade[1] = '0';
				cout << grade[0]<<endl;
			}
			if (flag == 1)
				cout << "you can not with draw course now, because you can withdraw course only in the last two weaks" << endl;
		}
		else
			cout << "Time to withdraw the course has passed" << endl;
	}
	int unregister()
	{
		if (attendence[4] == 'N')
			return 1;
		return 0;
	}
	void viewGrades()
	{
		cout << "N means unregisterd course" << endl << "W means withdrawn course" << endl;
		/*if (grade[0] == 'N')
		{
			cout << grade[0];
		}
		else if (grade[0] == 'W')
		{
			cout << grade[0];
		}
		else
		{
			cout << grade;
		}*/
		cout << grade;
	}
	~Registration()
	{
		delete[]attendence;
		delete[]marks;
	}
};

class Course
{
	char* courseCode;
	char* name;
	Registration** listOfRegistration;
	int noOfRegistration;
	int currentNoOfRegistration;
	int* listOfStudent;
public:
	Course() {}
	Course(char cc[], char n[])
	{
		currentNoOfRegistration = 0;
		int a = strlen(cc) + 1;
		courseCode = new char[a];
		for (int i = 0; i < a; i++)
			courseCode[i] = cc[i];
		int r = strlen(n) + 1;
		name = new char[r];
		for (int i = 0; i < r; i++)
			name[i] = n[i];
	}
	char* getCourseName()
	{
		return name;
	}
	int getNoOfRegistration()
	{
		return noOfRegistration;
	}
	char** getAttendenceofStuednts()
	{
		char** attendence = new char* [noOfRegistration];
		for (int i = 0; i < noOfRegistration; i++)
		{
			attendence[i] = listOfRegistration[i]->getAttendence();
		}
			
		return attendence;
	}
	int** getMarks()
	{
		this->print();
		int** marks = new int*[noOfRegistration];
		for (int i = 0; i < noOfRegistration; i++)
			marks[i] = listOfRegistration[i]->getMarks();
		return marks;
	}
	void setNoOfRegistration(int n)
	{
		noOfRegistration = n;
		listOfRegistration = new Registration * [noOfRegistration];
	}
	void addRegistration(Registration* registration)
	{
		listOfRegistration[currentNoOfRegistration] = registration;
		currentNoOfRegistration++;
	}
	void addListOfStudents(int nor, int stdArr[])
	{
		cout << "here are the roll numbers of the students" << endl;
		listOfStudent = new int[nor];
		for (int i = 0; i < nor; i++)
		{
			listOfStudent[i] = stdArr[i];
			cout << listOfStudent[i]<<endl;
		}
	
	}
	void print()
	{
		cout << "the code of the course is   " << courseCode << endl;
		cout << "the name of the course is   " << name << endl;

		for (int i = 0; i < noOfRegistration; i++)
			cout << listOfRegistration[i]->getAttendence()<<endl;

	}
	void viewGrades()
	{
		for (int i = 0; i < noOfRegistration; i++)
		{
			listOfRegistration[i]->viewGrades();
			cout << endl;
		}
	}
	~Course()
	{
		delete[]name;
		delete[]courseCode;
		delete[]listOfStudent;
		for (int i = 0; i < noOfRegistration; i++)
			delete listOfRegistration[i];
		delete[]listOfRegistration;
	}
};

class Course;
class Teacher: public Employee
{
	char* name;
	int noOfCourses;
	Course** listOfCourses;
	int currentNoOfCourses;

public:
	Teacher();
	Teacher(int number, char n[]) : Employee(number)
	{
		currentNoOfCourses = 0;
		int r = strlen(n) + 1;
		name = new char[r];
		for (int i = 0; i < r; i++)
			name[i] = n[i];
	}
	void setNoOfCourses(int n)
	{
		noOfCourses = n;
		listOfCourses = new Course * [noOfCourses];
	}
	void addcourse(Course* course)
	{
		listOfCourses[currentNoOfCourses] = course;
		currentNoOfCourses++;
	}
	void addCourseThroughHOD(Course* course)
	{
		int tempNo = noOfCourses;
		tempNo++;
		Course** temp = new Course * [tempNo];
		for (int i = 0; i < noOfCourses; i++)
			temp[i] = listOfCourses[i];
		temp[noOfCourses] = course;
		for (int i = 0; i < tempNo; i++)
			listOfCourses[i] = temp[i];
		delete[]temp;
		noOfCourses++;
		for (int i = 0; i < noOfCourses; i++)
			cout<<listOfCourses[i]->getCourseName()<<endl;
	}
	char* getNameOfTeacher()
	{
		return name;
	}
	int getEmployeeNo()
	{
		return Employee::getEmployeeNo();
	}
	int getNoOfCourse()
	{
		return noOfCourses;
	}
	char** getcourseName()
	{
		char** coursesName = new char* [noOfCourses];
		for (int i = 0; i < noOfCourses; i++)
			coursesName[i] = listOfCourses[i]->getCourseName();
		return coursesName;
	}
	void viewAttendence()
	{
		int size;
		char** attendence;
		char cname[90];   //course name
		cout << "enter the course name which you want to view attendence" << endl;
		cin >> cname;
		for (int i = 0; i < noOfCourses; i++)
		{
			if (strcmp(cname, listOfCourses[i]->getCourseName()) == 0)
			{
				size=listOfCourses[i]->getNoOfRegistration();
				attendence = new char* [size];
				attendence= listOfCourses[i]->getAttendenceofStuednts();
				for (int i = 0; i < size; i++)
					cout << attendence[i] << endl;
				//listOfCourses[i]->print();
			}
		}
	}
	void viewMarks()
	{
		char cname[90];
		cout << "enter the course name which you want to view attendence" << endl;
		cin >> cname;
		int** marks;
		int size;
		for (int i = 0; i < noOfCourses; i++)
		{
			if (strcmp(cname, listOfCourses[i]->getCourseName()) == 0)
			{
				size = listOfCourses[i]->getNoOfRegistration();
				marks = new int*[size];
				marks = listOfCourses[i]->getMarks();
				for (int i = 0; i < size; i++)
					cout << marks[i];
			}
		}
	}
	void print()
	{
		Employee::print();
		cout << "the name of the Teacher is   "<<name<<endl;
		cout << "the no of courses are   " << noOfCourses<<endl;
	}
	~Teacher()
	{
		delete[]name;
		delete[]listOfCourses;
	}
};





class Student: public Person
{
	int rollno;
	char* name;
	int noOfRegistrations;
	int currentNoOfRegistrations;
	Registration** listOfRegistration;
public:
	Student();
	Student(int rn, const char n[]) : rollno(rn)
	{
		currentNoOfRegistrations = 0;
		noOfRegistrations = 5;  //a student can register only 6 courses at a time
		listOfRegistration = new Registration * [5];
		int r = strlen(n) + 1;
		name = new char[r];
		for (int i = 0; i < r; i++)
			name[i] = n[i];
	}

	int getRollNoOfStudent()
	{
		return rollno;
	}

	void addRegistration(Registration* R)
	{
		if (currentNoOfRegistrations < 5)
		{
			listOfRegistration[currentNoOfRegistrations] = R;
			//cout<<listOfRegistration[currentNoOfRegistrations]->getAttendence();
			currentNoOfRegistrations++;
		}

	}
	void viewAttendence()
	{
		for (int i = 0; i < currentNoOfRegistrations; i++)
		{
			cout << listOfRegistration[i]->getAttendence()<<endl;
		}
	}
	void viewMarks()
	{
		int* marks=new int[5];
		for (int i = 0; i < currentNoOfRegistrations; i++)
		{
			marks=listOfRegistration[i]->getMarks();
			for (int j = 0; j < 5; j++)
				cout<<marks[j]<<"   ";
			cout << endl;
		}
			
	}
	void withDraw()
	{
		int courseNo;
		cout << "you have registerd " << currentNoOfRegistrations << " courses" << endl<<"Enter the course number you want to withdraw"<<endl;
		cin >> courseNo;
		courseNo--;
		listOfRegistration[courseNo]->withDraw();
	}
	void unregister()
	{
		int courseNo;
		cout << "you have registerd " << currentNoOfRegistrations << " courses" << endl << "Enter the course number you want to unregister" << endl;
		cin >> courseNo;
		courseNo--;
		for (int i = courseNo; i < noOfRegistrations; i++)
		{
			courseNo++;
			listOfRegistration[i] = listOfRegistration[courseNo];
		}
		currentNoOfRegistrations--;
		listOfRegistration[noOfRegistrations] = nullptr;
	}
	void print()
	{
		cout << " the roll number of the student is   " << rollno << endl;
		cout << "the name of the student is   " << name << endl;
	}

	char* getStudentName()
	{
		return name;
	}

	~Student()
	{
		delete[]name;
	}
};


class ITManager : public Employee
{
	char* name;
public:
	ITManager();
	ITManager(int number, char n[]) : Employee(number)
	{
		int r = strlen(n) + 1;
		name = new char[r];
		for (int i = 0; i < r; i++)
			name[i] = n[i];
	}
	int getEmployeeNo()
	{
		return Employee::getEmployeeNo();
	}

	Teacher* createTeacherAccount()
	{
		int employeeNo;
		char c[90];
		cout << "enter the name of the Faculty member" << endl;
		cin >> c;
		employeeNo = 1289;
		Teacher* teacher = new Teacher(employeeNo, c);
		return teacher;


		//First call the create a random number for employee number
		//IT manager will send this teacher object to his department and it will grows the array of teacher and add the teacher
		//make a function in department tor reload the data into the file of the 
		
	}

	Student* createStudentAccount()
	{
		int rollNo;
		char c[90];
		cout << "enter the name of the Faculty member" << endl;
		cin >> c;
		rollNo = 1212;
		Student* student = new Student(rollNo, c);
		return student;
	}

	void print()
	{
		cout << name << endl;
		Employee::print();
		cout << endl;
	}
	~ITManager()
	{
		delete[]name;
	}
};










class TA: public Student, public Teacher
{
public:

};

class Department
{
	char* name;
	int noOfCourses;
	int currentNoOfCourses=0;
	Course** listOfCourses;
	ITManager* itmanager;
	int noOfStudent;
	int currentNoOfStudent;
	Student** listOfStudent;
	int noOfteachers;
	int currentNoOfTeachers;
	Teacher** listOfTeachers;
public:
	Department() {
		currentNoOfStudent = 0;
		currentNoOfTeachers = 0;
	}

	Department(char na[])
	{
		currentNoOfCourses = 0;
		int r = 0;
		r = strlen(na) + 1;
		name = new char[r];
		for (int i = 0; i < r; i++)
			name[i] = na[i];
		

		//adding courses
		//ifstream fin;
		//fin.open("department.txt");
		//char c[90];
		//	  fin.getline(c, 90);
		//	  if (strcmp(c, name) == 0)
		//	  {
		//		  fin >> noOfCourses;   
		//		  listOfCourses = new Course * [noOfCourses];
		//		  fin.ignore();
		//		  char a[90], b[90];
		//		  for (int i = 0; i < noOfCourses; i++)
		//		  {
		//			  fin.getline(a, 90);
		//			  fin.getline(b, 90);
		//			  Course* newCourseObject = new Course(a, b);
		//			  listOfCourses[i] = newCourseObject;
		//		  }
		//	  }
	}

	void setNoOfCourses(int noc)
	{
		noOfCourses = noc;
		listOfCourses = new Course*[noOfCourses];
	}

	void addCourse(char cc[], char cn[])
	{
		Course* newCourseObject = new Course(cc, cn);
		listOfCourses[currentNoOfCourses] = newCourseObject;
		currentNoOfCourses++;

	}

	void addITManager(ITManager* i)
	{
		itmanager = i;
	}

	void setNoOfStudents(int ns)
	{
		noOfStudent = ns;
		listOfStudent = new Student*[noOfStudent];
		//cout << "the number of students are   " << noOfStudent;
	}

	void addStudent(Student* student)
	{
		listOfStudent[currentNoOfStudent] = student;
		currentNoOfStudent++;
	}

	void setNoOfTeacher(int n)
	{
		noOfteachers = n;
		listOfTeachers = new Teacher * [noOfteachers];
	
	}

	void addTeacher(Teacher* t)
	{
		listOfTeachers[currentNoOfTeachers] = t;
		currentNoOfTeachers++;
	}

	Course* assignCourseToTeacher(char c[])
	{
		for (int i = 0; i < noOfCourses; i++)
		{
			char a[90];
			if (strcmp(c, listOfCourses[i]->getCourseName()) == 0)
			{
				return listOfCourses[i];
			}
		}
		cout << "course is not assigned" << endl;
	}

	char* getNameOfTheDepartment()
	{
		return name;
	}

	int getNoOfCourses()
	{
		return noOfCourses;
	}

	void addRegistration(int r, Registration* R)
	{
		for (int i = 0; i < noOfStudent; i++)
		{
			if (r == listOfStudent[i]->getRollNoOfStudent())
			{
				listOfStudent[i]->addRegistration(R);
			}
		}
	}

	void setNoOfRegistrationInCourses(int n,char course[])
	{
		for (int i = 0; i < noOfCourses; i++)
		{
			if (strcmp(listOfCourses[i]->getCourseName(), course) == 0)
			{
				listOfCourses[i]->setNoOfRegistration(n);
			}
		}
	}

	void addRegistrationInCourse(Registration* registration, char course[])
	{
		for (int i = 0; i < noOfCourses; i++)
		{
			if (strcmp(listOfCourses[i]->getCourseName(), course) == 0)
			{
				listOfCourses[i]->addRegistration(registration);
			}
		}
	}

	void addStudentListInCourse(int nor,int student[], char course[])
	{
		for (int i = 0; i < noOfCourses; i++)
		{
			if (strcmp(listOfCourses[i]->getCourseName(), course) == 0)
			{
				listOfCourses[i]->addListOfStudents(nor,student);
			}
		}
	}

	int teacherMayExist(int r)
	{
		for (int i = 0; i < noOfteachers; i++)
		{
			if (r == listOfTeachers[i]->getEmployeeNo())
				return 1;
		}
		return 0;
	}

	Teacher* getTeacher(int r)
	{
		for (int i = 0; i < noOfteachers; i++)
		{
			if (r == listOfTeachers[i]->getEmployeeNo())
				return listOfTeachers[i];
		}
	}

	int ITmanagerMayExist(int r)
	{
		if (r == itmanager->getEmployeeNo())
			return 1;
		return 0;
	}

	ITManager* getItmanager()
	{
		return itmanager;
	}

	int studentMayExist(int r)
	{
		for (int i = 0; i < noOfStudent; i++)
		{
			if (listOfStudent[i]->getRollNoOfStudent() == r)
				return 1;
		}
		return 0;
	}

	Student* getStudent(int r)
	{
		for (int i = 0; i < noOfStudent; i++)
		{
			if (listOfStudent[i]->getRollNoOfStudent() == r)
				return listOfStudent[i];
		}
	}

	void CreateTeacherAccount(Teacher* teacher)
	{
		int tempNoOfTeachers = noOfteachers + 1;
		Teacher** temp = new Teacher*[tempNoOfTeachers];
		for (int i = 0; i < noOfteachers; i++)
			temp[i] = listOfTeachers[i];
		temp[noOfteachers] = teacher;

		cout << noOfteachers << endl;

		delete[]listOfTeachers;
		noOfteachers++;
		listOfTeachers = new Teacher * [noOfteachers];
		for (int i = 0; i < noOfteachers; i++)
			listOfTeachers[i] = temp[i];
		delete[]temp;
		tempNoOfTeachers = noOfteachers - 1;
		cout << listOfTeachers[tempNoOfTeachers]->getEmployeeNo()<<endl;
	}

	void deleteTeacherAccount(int eNo)
	{
		int ref;
		for (int i = 0; i < noOfteachers; i++)
		{
			if (listOfTeachers[i]->getEmployeeNo() == eNo)
			{
				ref = i;
			}
		}
		noOfteachers--;
		for (int i = ref; i < noOfteachers; i++)
		{
			ref++;
			listOfTeachers[i] = listOfTeachers[ref];
		}
		listOfTeachers[noOfteachers] = nullptr;
	}

	void CreateStudentAccount(Student* student)
	{
		int tempNoOfStudents = noOfStudent + 1;
		Student** temp = new Student * [tempNoOfStudents];
		for (int i = 0; i < noOfStudent; i++)
			temp[i] = listOfStudent[i];
		temp[noOfStudent] = student;

		cout << noOfStudent << endl;

		delete[]listOfStudent;
		noOfStudent++;
		listOfStudent = new Student * [noOfStudent];
		for (int i = 0; i < noOfStudent; i++)
			listOfStudent[i] = temp[i];
		delete[]temp;
		tempNoOfStudents = noOfStudent - 1;
		cout << listOfStudent[tempNoOfStudents]->getRollNoOfStudent() << endl;
	}

	void deleteStudentAccount(int rollNo)
	{
		int ref;
		for (int i = 0; i < noOfStudent; i++)
		{
			if (listOfStudent[i]->getRollNoOfStudent() == rollNo)
			{
				ref = i;
			}
		}
		noOfStudent--;
		for (int i = ref; i < noOfStudent; i++)
		{
			ref++;
			listOfStudent[i] = listOfStudent[ref];
		}
		listOfStudent[noOfStudent] = nullptr;
	}

	void print()
	{
		cout << "the name of the department is  " << name << endl;
	}

	void printDataInFile(ofstream& fout)
	{
		//ofstream fout;
	/*	fout.open("hi.txt", ios::app);
		if (fout.is_open())
		{
			fout << name << endl;
			fout << this->noOfteachers << endl;
			fout.close();
		}
		else
			cout << "Unable to open file in printDataInFile" << endl;*/

		int noc;  //number of courses of teacher
		char** namesOfCourses;
		fout << name << endl;
		fout << noOfteachers << endl;
		for (int i = 0; i < noOfteachers; i++)
		{
			fout << listOfTeachers[i]->getEmployeeNo() << endl;
			fout << listOfTeachers[i]->getNameOfTeacher() << endl;
			fout << listOfTeachers[i]->getNoOfCourse()<<endl;
			noc = listOfTeachers[i]->getNoOfCourse();
			namesOfCourses = new char* [noc];
			namesOfCourses= listOfTeachers[i]->getcourseName();
			for (int j = 0; j < noc; j++)
				fout << namesOfCourses[j]<<endl;
		}
	}

	void loadStudentData(ofstream& fout)
	{
		fout << name<<endl;
		fout << noOfStudent<<endl;
		for (int i = 0; i < noOfStudent;i++)
		{
			fout << listOfStudent[i]->getRollNoOfStudent() << endl;
			fout << listOfStudent[i]->getStudentName()<<endl;
		}
	}

	

	void addCourseByHOD(int en)
	{
		if (en == listOfTeachers[0]->getEmployeeNo())
		{
			int no,cn;
			cout << "here is the list of teachers, type the number of that teacher which you want to select" << endl;
			for (int i = 0; i < noOfteachers; i++)
				cout<<i<<". "<< listOfTeachers[i]->getEmployeeNo()<<endl;
			cin >> no;
			cout << "here is the list of courses, type the number of that course which you want to select" << endl;
			for (int i = 0; i < noOfCourses; i++)
				cout << i << ". " << listOfCourses[i]->getCourseName()<<endl;
			cin >> cn;
			listOfTeachers[no]->addCourseThroughHOD(listOfCourses[cn]);
		}
		else
			cout << "You are not an HOD" << endl;
	}

	void addRegistrationByHOd(int en)
	{
		if (en == listOfTeachers[0]->getEmployeeNo())
		{
			int no, cn;
			cout << "here is the list of students, type the number of that student which you want to select" << endl;
			for (int i = 0; i < noOfStudent; i++)
				cout << i << ". " << listOfStudent[i]->getRollNoOfStudent() << endl;
			cin >> no;
			cout << "here is the list of courses, type the number of that course which you want to select" << endl;
			for (int i = 0; i < noOfCourses; i++)
				cout << i << ". " << listOfCourses[i]->getCourseName() << endl;
			cin >> cn;
			Registration* registration = new Registration();
			listOfStudent[no]->addRegistration(registration);
			listOfCourses[cn]->addRegistration(registration);
		}
		else
			cout << "You are not an HOD" << endl;
	}

	void unregisterByHOd(int en)
	{
		if (en == listOfTeachers[0]->getEmployeeNo())
		{
			int no;
			cout << "here is the list of students, type the number of that student which you want to select" << endl;
			for (int i = 0; i < noOfStudent; i++)
				cout << i << ". " << listOfStudent[i]->getRollNoOfStudent() << endl;
			cin >> no;
			listOfStudent[no]->unregister();
		}
		else
			cout << "You are not an HOD" << endl;
	}

	void viewGrades(int en)
	{
		if (en == listOfTeachers[0]->getEmployeeNo())
		{
			int cn;
			cout << "here is the list of courses, type the number of that course which you want to select" << endl;
			for (int i = 0; i < noOfCourses; i++)
				cout << i << ". " << listOfCourses[i]->getCourseName() << endl;
			cin >> cn;
			listOfCourses[cn]->viewGrades();
		}
		else
			cout << "You are not an HOD" << endl;
	}

	~Department()
	{
		delete[]name;
		for (int i = 0; i < noOfCourses; i++)
			delete listOfCourses[i];
		delete[]listOfCourses;
		for (int i = 0; i < noOfStudent; i++)
			delete listOfStudent[i];
		delete[]listOfStudent;
		for (int i = 0; i < noOfteachers; i++)
			delete listOfTeachers[i];
		delete[]listOfTeachers;
		delete itmanager;
	}
};



class University
{
	int noOfDepartments;
	Department** listOfDepartments;
	char* name;
public:
	University()
	{
		//adding university
		ifstream fin;
		fin.open("university.txt");
		if (fin.is_open())
		{
			name = new char[100];
			fin.getline(name, 100);
		}
		else
			cout << "file is not open/n";
		fin >> noOfDepartments;
		listOfDepartments = new Department*[noOfDepartments];

		fin.ignore();
		char a[100];
	    
		int noc; //number of courses in the department 
		char courseCode[90];
		char courseName[90];
		for (int i = 0; i < noOfDepartments;i++)
		{
			fin.getline(a, 100);
			Department *newDepartmentObject = new Department(a);
			listOfDepartments[i] = newDepartmentObject;
			fin >> noc;
			fin.ignore();
			listOfDepartments[i]->setNoOfCourses(noc);
			for (int j = 0; j < noc; j++)
			{
				fin.getline(courseCode, 90);
				fin.getline(courseName, 90);
				listOfDepartments[i]->addCourse(courseCode, courseName);
			}
		}
		


	}

	void addITManager(char c[], ITManager* it)
	{
		for (int i = 0; i < noOfDepartments; i++)
		{
			if (strcmp(listOfDepartments[i]->getNameOfTheDepartment(), c) == 0)
			{
				listOfDepartments[i]->addITManager(it);
			}
		}
	}

	void setNoOfStudents(char c[], int ns)
	{
		for (int i = 0; i < noOfDepartments; i++)
		{
			if (strcmp(c, listOfDepartments[i]->getNameOfTheDepartment()) == 0)
			{
				listOfDepartments[i]->setNoOfStudents(ns);
			}
		}
	}

	void addStudent(char c[], Student* student)
	{
		for (int i = 0; i < noOfDepartments; i++)
		{
			if (strcmp(c, listOfDepartments[i]->getNameOfTheDepartment()) == 0)
			{
				listOfDepartments[i]->addStudent(student);
			}
		}
	}

	void setNoOfTeachers(char c[], int n)
	{
		for (int i = 0; i < noOfDepartments; i++)
		{
			if (strcmp(c, listOfDepartments[i]->getNameOfTheDepartment()) == 0)
			{
				listOfDepartments[i]->setNoOfTeacher(n);
			}
		}
	}

	void addTeacher(char c[],Teacher* t)
	{
		for (int i = 0; i < noOfDepartments; i++)
		{
			if (strcmp(c, listOfDepartments[i]->getNameOfTheDepartment()) == 0)
			{
				listOfDepartments[i]->addTeacher(t);
			}
		}
	}

	Course* assignCourseToTeacher(char a[],char c[])
	{
		for (int i = 0; i < noOfDepartments; i++)
		{
			if (strcmp(a, listOfDepartments[i]->getNameOfTheDepartment()) == 0)
			{
				return listOfDepartments[i]->assignCourseToTeacher(c);
			}
		}
	}

	University(const char n[])
	{
		int r = 0;
		r = strlen(n) + 1;
		name = new char[r];
		for (int i = 0; i < r; i++)
			name[i] = n[i];
	}

	int getNoOfDepartments()
	{
		return noOfDepartments;
	}

	int getNoOfCourses(char c[])
	{
		for (int i = 0; i < noOfDepartments;i++)
		{
			if (strcmp(c, listOfDepartments[i]->getNameOfTheDepartment()) == 0)
			{
				return listOfDepartments[i]->getNoOfCourses();
			}
		}
	}

	void assignRegistrationToStudent(char c[], int r, Registration* R)
	{
		for (int i = 0; i < noOfDepartments; i++)
		{
			if (strcmp(c, listOfDepartments[i]->getNameOfTheDepartment()) == 0)
			{
				listOfDepartments[i]->addRegistration(r, R);
			}
		}
	}

	void setNoOfRegistrationInCourses(int n, char course[], char dptName[])
	{
		for (int i = 0; i < noOfDepartments; i++)
		{
			if (strcmp(listOfDepartments[i]->getNameOfTheDepartment(), dptName) == 0)
				listOfDepartments[i]->setNoOfRegistrationInCourses(n, course);
		}
	}

	void addREgistrationInCourses(Registration* registration, char course[], char dptName[])
	{
		for (int i = 0; i < noOfDepartments; i++)
		{
			if (strcmp(listOfDepartments[i]->getNameOfTheDepartment(), dptName) == 0)
				listOfDepartments[i]->addRegistrationInCourse(registration, course);
		}
	}

	void addStudentLisInCourses(int nor,int student[], char course[], char dptName[])
	{
		for (int i = 0; i < noOfDepartments; i++)
		{
			if (strcmp(listOfDepartments[i]->getNameOfTheDepartment(), dptName) == 0)
				listOfDepartments[i]->addStudentListInCourse(nor,student,course);
		}
	}

	Teacher* getTeacher(int r)
	{
		for (int i = 0; i < noOfDepartments; i++)
		{
			if (listOfDepartments[i]->teacherMayExist(r) == 1)
			{
				return listOfDepartments[i]->getTeacher(r);
			}
		}
	}

	ITManager* getITmanager(int r)
	{
		for (int i = 0; i < noOfDepartments; i++)
		{
			if (listOfDepartments[i]->ITmanagerMayExist(r) == 1)
			{
				return listOfDepartments[i]->getItmanager();
			}
		}
	}

	Student* getStudent(int r)
	{
		for (int i = 0; i < noOfDepartments; i++)
		{
			if (listOfDepartments[i]->studentMayExist(r) == 1)
			{
				return listOfDepartments[i]->getStudent(r);
			}
		}
	}

	void createTeacherAccount(int employeeno, Teacher* teacher)
	{
		for (int i = 0; i < noOfDepartments; i++)
			if (listOfDepartments[i]-> ITmanagerMayExist(employeeno) == 1)
				listOfDepartments[i]->CreateTeacherAccount(teacher);
	}

	void deleteTeacherAccount(int employeeno,int teacherEmployeeNo)
	{
		for (int i = 0; i < noOfDepartments; i++)
			if (listOfDepartments[i]->ITmanagerMayExist(employeeno) == 1)
				listOfDepartments[i]->deleteTeacherAccount(teacherEmployeeNo);
	}

	void createStudentAccount(int employeeno, Student* student)
	{
		for (int i = 0; i < noOfDepartments; i++)
			if (listOfDepartments[i]->ITmanagerMayExist(employeeno) == 1)
				listOfDepartments[i]->CreateStudentAccount(student);
	}

	void deleteStudentAccount(int employeeno, int rollNo)
	{
		for (int i = 0; i < noOfDepartments; i++)
			if (listOfDepartments[i]->ITmanagerMayExist(employeeno) == 1)
				listOfDepartments[i]->deleteStudentAccount(rollNo);
	}

	char* getStudentDept(int r)
	{
		for (int i = 0; i < noOfDepartments; i++)
		{
			if (listOfDepartments[i]->studentMayExist(r) == 1)
				return listOfDepartments[i]->getNameOfTheDepartment();
		}
	}

	void print() {
		cout << "the name of the university is    " << name<<endl;
	}

	void printDepData()
	{
		ofstream fout;
		fout.open("teacher.txt");
		if (fout.is_open())
		{
			for (int i = 0; i < noOfDepartments; i++)
				listOfDepartments[i]->printDataInFile(fout);
		}


	/*	if (fout.is_open())
		{
			fout << '\0';
			fout.close();
		}
		else
			cout << "Unable to open file in printDepData" << endl;
		for (int i = 0; i < noOfDepartments; i++)
		{
			listOfDepartments[i]->printDataInFile();
		}*/
	}

	void loadStudentData()
	{
		ofstream fout;
		fout.open("student.txt");
		if (fout.is_open())
		{
			for (int i = 0; i < noOfDepartments; i++)
				listOfDepartments[i]->loadStudentData(fout);
		}
	}

	

	void addCourseByHOD(int en)
	{
		for (int i = 0; i < noOfDepartments; i++)
		{
			if (listOfDepartments[i]->teacherMayExist(en) == 1)
			{
				listOfDepartments[i]->addCourseByHOD(en);
			}
		}
	}

	void addRegistrationByHOD(int en)
	{
		for (int i = 0; i < noOfDepartments; i++)
		{
			if (listOfDepartments[i]->teacherMayExist(en) == 1)
			{
				listOfDepartments[i]->addRegistrationByHOd(en);
			}
		}
	}

	void unregisterByHOD(int en)
	{
		for (int i = 0; i < noOfDepartments; i++)
		{
			if (listOfDepartments[i]->teacherMayExist(en) == 1)
			{
				listOfDepartments[i]->unregisterByHOd(en);
			}
		}
	}

	void viewGrades(int en)
	{
		for (int i = 0; i < noOfDepartments; i++)
		{
			if (listOfDepartments[i]->teacherMayExist(en) == 1)
			{
				listOfDepartments[i]->viewGrades(en);
			}
		}
	}

	~University()
	{
		delete[]name;
		for (int i = 0; i < noOfDepartments; i++)
			delete listOfDepartments[i];
		delete[]listOfDepartments;
		//delete department;
	}
};



int main()
{
	//todos: make destructor of all the object in by the end of main by getting the information through university, delete all the other objects like int and char, function of teacher is ready use it in the main, assign name and random number to object created through it manager

	int tarr[100], tcount = 0, itarr[100], itcount = 0, sarr[100], scount = 0;  //include the concept of memory grow not the static size of arr


	//student belongs to a specific dept. 


	University university;


	//IT Manager
	int noOfDepartments = university.getNoOfDepartments();
	ifstream fin;
	fin.open("itmanager.txt");
	for (int i = 0; i < noOfDepartments; i++)
	{
		int employeeNo;
		char name[90], department[90];
		fin.getline(department, 90);
		fin >> employeeNo;
		itarr[itcount] = employeeNo;
		itcount++;
		fin.ignore();
		fin.getline(name, 90);
		ITManager* itmanager = new ITManager(employeeNo, name);
		university.addITManager(department, itmanager);
		//itmanager->print();
	}


	//student
	Student** listOfStudent;
	int noOfStudent;
	char y[90];
	int rollNo;
	char d[90];
	int noOfDepartment=university.getNoOfDepartments();
	ifstream f;
	f.open("student.txt");
		for (int k = 0; k < noOfDepartment; k++)
		{
			f.getline(y, 90);
			f >> noOfStudent;
			listOfStudent = new Student * [noOfStudent];
			university.setNoOfStudents(y,noOfStudent);
			for (int i = 0; i < noOfStudent; i++)
			{
				f >> rollNo;
				sarr[scount] = rollNo;
				scount++;
				f.ignore();
				f.getline(d, 90);
				listOfStudent[i] = new Student(rollNo, d);
				university.addStudent(y, listOfStudent[i]);

			}
		}
	





	//teacher
	int noOfTeachers;
	int employeeNo;
	char e[90];
	char z[90];
	int noc;   //number of course
	ifstream fi;
	fi.open("teacher.txt");
		for(int k=0;k<noOfDepartment;k++)
		{
			fi.getline(z, 90);
			fi >> noOfTeachers;
			university.setNoOfTeachers(z,noOfTeachers);
			fi.ignore();
			Teacher** listOfTeacher = new Teacher * [noOfTeachers];
			for (int i = 0; i < noOfTeachers; i++)
			{
				fi >> employeeNo;
				tarr[tcount] = employeeNo;
				tcount++;
				fi.ignore();
				fi.getline(e, 90);
				Teacher* newTeacherObject = new Teacher(employeeNo, e);
				//make a new teacher in dept
				university.addTeacher(z,newTeacherObject);
				fi >> noc;
				newTeacherObject->setNoOfCourses(noc);
				fi.ignore();
				for (int i = 0; i < noc; i++)
				{
					fi.getline(e, 90);
					newTeacherObject->addcourse(university.assignCourseToTeacher(z,e));
				}
			}
		}
	

	//Registration
		Registration** listOfRegistration;
		int stdarr[50];
		int count=0;
		char x[90];      //department name
		char c[90];      //course name
		char a[30];      //attendence
		char grade[90];
		int m[5];        //marks   mid1, mid2, assignment, quiz, final 
		int n;           //number of courses
		int r;           //roll number of the student
		int numberOfRegistration;
		ifstream fif;
		fif.open("registration.txt");
		for (int i = 0; i < noOfDepartment; i++)
		{
			fif.getline(x, 90);
			n=university.getNoOfCourses(x);
			for (int j = 0; j < n; j++)
			{
				fif.getline(c, 90);
				fif >> numberOfRegistration;
				listOfRegistration = new Registration*[numberOfRegistration];
				fif.ignore();
				for (int l = 0; l < numberOfRegistration; l++)
				{
					fif >> r;
					stdarr[count] = r;
					fif.ignore();
					fif.getline(a, 31);
					for (int k = 0; k < 5; k++)
					{
						fif >> m[k];
						fif.ignore();
					}
					fif.getline(grade, 90);
					listOfRegistration[l] = new Registration(a, m,grade);
					university.assignRegistrationToStudent(x, r, listOfRegistration[l]);
					university.setNoOfRegistrationInCourses(numberOfRegistration, c, x);
					university.addREgistrationInCourses(listOfRegistration[l], c, x);
				}	
				university.addStudentLisInCourses(numberOfRegistration, stdarr, c, x);
				count = 0;
			}
		}
		





		for (int i = 0; i < itcount; i++)
			cout << itarr[i]<<endl;
		for (int i = 0; i < tcount; i++)
			cout << tarr[i] << endl;
		for (int i = 0; i < scount; i++)			



		system("CLS");


		int login;
		//add password in teacher and student and itmanager
		int number, loginNo, flag = 0, operation;
		cout << "enter 1 if you login as an IT Manager" <<endl<< "2 as Teacher" << endl << "3 as Student" << endl;
		cin >> number;
		
		system("CLS");



			if (number == 1)
			{
				cout << "enter your employee number" << endl;
				cin >> loginNo;
				for (int j = 0; j < itcount; j++)
				{
					if(flag==0)
					{
						if (itarr[j] == loginNo)
						{
							ITManager* newObject = university.getITmanager(loginNo);
							cout << newObject->getEmployeeNo() << endl;
							system("CLS");

							cout << "enter 1 to create Faculty member account" << endl << "2 to delete Faculty member account" << endl << "enter 3 to create Student account" << endl << "4 to delete Student account" << endl;
							cin >> operation;
							if (operation == 1)
							{
								university.createTeacherAccount(newObject->getEmployeeNo(), newObject->createTeacherAccount());
								system("CLS");
								cout << "Account of teacher is created" << endl;
								university.printDepData();
							}
							if (operation == 2)
							{
								int teacherEmployeeNo;
								cout << "enter the employee number of the teacher" << endl;
								cin >> teacherEmployeeNo;
								university.deleteTeacherAccount(newObject->getEmployeeNo(), teacherEmployeeNo);
								system("CLS");
								cout << "the account of the teacher is deleted" << endl;
								university.printDepData();
							}
							if (operation == 3)
							{
								university.createStudentAccount(newObject->getEmployeeNo(), newObject->createStudentAccount());
								system("CLS");
								cout << "account of student is created<<endl";
								//university.printDepData();
								university.loadStudentData();
							}
							if (operation == 4)
							{
								int rollNo;
								cout << "enter the roll number of the teacher" << endl;
								cin >> rollNo;
								university.deleteStudentAccount(newObject->getEmployeeNo(), rollNo);
								system("CLS");
								cout << "account of the student is deleted" << endl;
								//university.printDepData();
								university.loadStudentData();
							}
							flag = 1;
							// teacher

						}
						else
						{
							cout << "wrong employee ID" << endl;
							flag = 1;
						}
					}
				}
			}
			if (number == 2)
			{
				cout << "enter your employee number" << endl;
				cin >> loginNo;
				for (int j = 0; j < tcount; j++)
				{
					if (flag == 0)
					{

						if (tarr[j] == loginNo)
						{
							Teacher* newObject = university.getTeacher(loginNo);
							cout << newObject->getEmployeeNo() << endl;
							cout << "enter 1 if you want to view attendence," << endl << "2 if you want to manage attendence," << endl << " 3 if you want to view marks," << endl << "4 if you want to manage marks" << endl << "if you are HOD" << endl << "enter 5 to assign course to the teacher" << endl << "6 if you want to register a course for student" << endl << "7 if you want to unregister a course for the student" << endl << "8 if you want to view the grades" << endl;
							cin >> operation;
							if (operation == 1)
							{
								newObject->viewAttendence();
							}

							if (operation == 3)
							{
								newObject->viewMarks();
							}
							if (operation == 5)
							{
								university.addCourseByHOD(newObject->getEmployeeNo());
								system("CLS");
								cout << "course is assigned to the teacher bythe HOD"<<endl;
								university.printDepData();
							}
							if (operation == 6)
							{
								university.addRegistrationByHOD(newObject->getEmployeeNo());
								system("CLS");
								cout << "course is registered for the student" << endl;
							}
							if (operation == 7)
							{
								university.unregisterByHOD(newObject->getEmployeeNo());
							}
							if (operation == 8)
							{
								university.viewGrades(newObject->getEmployeeNo());
							}
							flag = 1;
						}
					}
				}
				if(flag==0)
				   cout << "wrong employee ID" << endl;
			}
			if (number == 3)
			{
				cout << "enter your roll number" << endl;
				cin >> loginNo;
				for (int j = 0; j < scount; j++)
				{
					if (flag == 0)
					{
						if (sarr[j] == loginNo)
						{
							Student* newObject = university.getStudent(loginNo);
							cout << newObject->getRollNoOfStudent() << endl;
							system("CLS");
							cout << "enter 1 to register a course"<<endl<<"enter 2 to view attendence"<<endl<<" 3 to view marks" << endl<<"enter 4 to widthdraw course"<<endl<<"enter 5 to unregister course"<<endl;
							cin >> operation;
							if (operation == 1)
							{
								char course[90];
								cout << "enter the name of the course you want to registration" << endl;
								cin >> course;
								char* dptName;
								dptName=university.getStudentDept(newObject->getRollNoOfStudent());
								Registration* registration=new Registration;
								newObject->addRegistration(registration);
								university.addREgistrationInCourses(registration, course, dptName);
								system("CLS");
								cout << "registration is added successfuly" << endl;
							}
							if (operation == 2)
							{
								newObject->viewAttendence();

							}
							if (operation == 3)
							{
								newObject->viewMarks();
							}
							if (operation == 4)
							{
								newObject->withDraw();
							}
							if (operation == 5)
							{
								newObject->unregister();
								system("CLS");
								cout << "the course is unregistered" << endl;
							}
							flag = 1;
						}
					}
				}
				if (flag == 0)
					cout << "wrong roll number" << endl;
			}

	system("pause");
}