#include <iostream>

using namespace std;

class Human {
private:
	int age;
	char name[10];
	char hobby[20];
public:
	Human(int _age, char * _name, char * _hobby) : age(_age)
	{
		strcpy(name, _name);
		strcpy(hobby, _hobby);
	}
	void getup()
	{
		cout << "기상!" << endl;
	}
	void sleep()
	{
		cout << "취침!" << endl;
	}
	void eat()
	{
		cout << "식사!" << endl;
	}
	void study()
	{
		cout << "공부!" << endl;
	}
	void showInfo()
	{
		cout << "이름: " << name << endl;
		cout << "나이: " << age << endl;
		cout << "취미: " << hobby << endl;
	}
};

class Student : public Human {
private:
	char school[30];
public:
	Student(int _age, char * _name, char * _hobby, char * _school) : Human(_age, _name, _hobby)
	{
		strcpy(school, _school);
	}
	void schoolInfo()
	{
		showInfo();
		cout << "소속 학교: " << school << endl;
	}
};

int main()
{
	Student stu(18, "김철수", "프로그래밍", "자바고등학교");

	stu.schoolInfo();
	stu.getup();
	stu.eat();
	stu.study();
	stu.sleep();

	return 0;
}