#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <conio.h>
#include <sstream>
#include <Windows.h>
#include <iostream>
#include <windows.h>
#include <io.h>
#include <string>
#include <string.h>
#include <fstream>
#include <iomanip>

using namespace std;

#define SPACE 32

void gotoxy(int x, int y)
{
	COORD Pos;
	Pos.X = 2 * x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// 회원
class Member
{
protected:
	string name;

public:
	Member(){}
	string getName();
	
	~Member() {}
	void setMember();
	void member_list();
	void member_modify();
};
string Member::getName()
{
	return name;
}

// 학생
class Student : public Member 
{
	int hakbun;

public:
	
	void setMember(string name, int hakbun);
	void member_list();
	void member_modify();
	void addMember(string name, int hakbun);


	int getHakbun();
	void setHakbun(int hakbun);

};

void Student::addMember(string name, int hakbun) {
	this->name = name;
	this->hakbun = hakbun;

}
void Student::setMember(string name, int hakbun){
	this->name = name;
	this->hakbun = hakbun;
}
void Student::member_list()
{
	//cout.setf(ios_base::left, ios_base::adjustfield);
	cout << name << "\t" << hakbun << endl;
}
void Student::member_modify()
{
	boolean flag = true;
	cin.ignore();
	cout << "이름을 입력해주세요 : ";
	getline(cin, name);

	cout << "학번을 입력해주세요 : ";
	cin >> hakbun;

	cout << "이름 : " << name << "\t학번 : " << hakbun << endl;
}

int Student::getHakbun()
{
	return hakbun;
}
void Student::setHakbun(int hakbun)
{
	this->hakbun = hakbun;
}


// 선생님
class Teacher : public Member
{
	string subject;
	int number;

public:
	void setMember(string name, string subject, int number);
	void member_list();
	void member_modify();
	string getSubject();
	int getNumber();
	void setNumber(int number);
};
void Teacher::setMember(string name, string subject, int number) {
	this->name = name;
	this->subject = subject;
	this->number = number;
}
void Teacher::member_list()
{
	//cout.setf(ios_base::left, ios_base::adjustfield);
	cout << name << "\t" << subject << "\t" << number << endl;
}
void Teacher::member_modify()
{
	cin.ignore();
	cout << "이름을 입력해주세요 : ";
	getline(cin, name);

	cout << "담당 과목을 입력해주세요 : ";
	getline(cin, subject);

	cout << "회원 번호를 입력해주세요 : ";
	cin >> number;

	cout << "이름 : " << name << "\t과목 : " << subject << "\t회원 번호 : " <<number << endl;

}
string Teacher::getSubject()
{
	return subject;
}
int Teacher::getNumber()
{
	return number;
}
void Teacher::setNumber(int number)
{
	this->number = number;
}

//책 한권에 대한 클래스
class Book
{
	string m_bookname;
	string writer;
	string publisher;
	int bookNum;
	int m_membernum;

public:
	Book();
	Book(string _bookname, string writer, string publisher);
	void setBook(int bookNum, string name, string writer, string publisher, int number);
	void addBook(int bookNum, string name, string writer, string publisher);

	void rentBook(int _number);
	void returnBook();
	void bookModify();
	void bookList();
	string getName();
	string getWriter();
	string getPublisher();
	int getMember();
	int getBookNum();
	
};

Book::Book()
{
	m_membernum = -1;//책을 대출할경우 맴버의 번호를 저장 합니다. -1이면 빌려가지 않은책
}

void Book::setBook(int bookNum, string name, string writer, string publisher, int number)
{
	this->bookNum = bookNum;
	m_bookname = name;
	this->writer = writer;
	this->publisher = publisher;
	m_membernum = number;
}

void Book::addBook(int bookNum, string name, string writer, string publisher)
{
	this->bookNum = bookNum;
	m_bookname = name;
	this->writer = writer;
	this->publisher = publisher;
}

void Book::rentBook(int _number)
{
	m_membernum = _number;
}

void Book::returnBook()
{
	m_membernum = -1;
}

void Book::bookModify()
{
	wcout.imbue(locale("kor"));
	wcin.imbue(locale("kor"));
	
	cin.ignore();
	cout << "도서 번호을 입력해주세요 : ";
	cin >> bookNum;
	
	cout << "도서 이름을 입력해주세요 : ";
	getline(cin, m_bookname);
	

	cout << "작가명을 입력해주세요 : ";
	getline(cin, writer);

	cout << "출판사를 입력해주세요 : ";
	getline(cin, publisher);



	cout << "도서 번호 : " << bookNum << "\t도서명 : " << m_bookname << "\t작가명 : " << writer << endl;
	
	m_membernum = 0;
}

void Book::bookList()
{
	
	cout << bookNum << "\t" << m_bookname << "\t"<<writer << "\t" << publisher << endl;
}

string Book::getName()
{
	return m_bookname;
}
string Book::getWriter()
{
	return writer;
}
string Book::getPublisher()
{
	return publisher;
}
int Book::getMember()
{
	return m_membernum;
}
int Book::getBookNum()
{
	return bookNum;
}


class Library
{
	Student student_member[360];
	int  student_count;
	
	Teacher teacher_member[360];
	int  teacher_count;

	Book m_book[360];
	int  m_bookCount;

public:
	Library();
	
	void loadData();
	void saveData();

	// 회원 추가
	void addMember();
	
	// 책 추가
	void addBook();

	//찾기
	void searchMember();
	void searchBook();

	void showStudentNOW();
	void showTeacherNOW();

	void modifyMember();

	void rentStudentBook();
	void rentTeacherBook();

	void returnStudentBook();
	void returnTeacherBook();

	void listBook();
	void listBookManager();
	void listMember();

	void deleteMember();

};
void Library::deleteMember() {
	string name, bookname, line;
	int bookNum, num, hakbun, delHakbun, delNumber, delBookNum, number, i, j, k, chk = 0, cnt = 1;
	boolean flag = false;
	int x = 10, y = 2;
	gotoxy(x, y); y++;
	cout << "====================================================";
	gotoxy(x, y); y++;
	cout << "1. 학생 회원 삭제";
	gotoxy(x, y); y++;
	cout << "2. 선생님 회원 삭제";
	gotoxy(x, y); y++;
	cout << "3. 도서 삭제";
	gotoxy(x, y); y++;
	y += 1;
	gotoxy(x, y); y++;
	cout << " >> ";
	cin >> num;

	if (num == 1) {
		gotoxy(x, y); y++;
		cout << "====================================================";
		gotoxy(x, y); y++;
		cout << "삭제할 학생 학번을 입력하세요 : ";
		cin >> delHakbun;


		for (i = 0; i < student_count; i++) {
			for (j = 0; j < m_bookCount; j++) {
				if (student_member[i].getHakbun() == delHakbun && m_book[j].getMember() == student_member[i].getHakbun()) {

					m_book[j].returnBook();

				}
			}
		}

		for (i = 0; i < student_count; i++) {
			if (student_member[i].getHakbun() == delHakbun) {
				student_member[i].setMember("삭제됨", 0);
			}
		}

		y += 1;

		gotoxy(x, y); y++;
		cout << delHakbun << "번 회원을 삭제함" << endl;
		gotoxy(x, y); y++;
		cout << "====================================================";

		cin.ignore();
		cin.get();
		return;
	}
	else if (num == 2) {
		gotoxy(x, y); y++;
		cout << "====================================================";
		gotoxy(x, y); y++;
		cout << "삭제할 선생님 학번을 입력하세요 : ";
		cin >> delNumber;


		for (i = 0; i < teacher_count; i++) {
			for (j = 0; j < m_bookCount; j++) {
				if (teacher_member[i].getNumber() == delNumber && m_book[j].getMember() == teacher_member[i].getNumber()) {

					m_book[j].returnBook();

				}
			}
		}

		for (i = 0; i < teacher_count; i++) {
			if (teacher_member[i].getNumber() == delNumber) {
				teacher_member[i].setMember("삭제됨", "삭제됨", 0);
			}
		}

		y += 1;

		gotoxy(x, y); y++;
		cout << delNumber << "번 회원을 삭제함" << endl;
		gotoxy(x, y); y++;
		cout << "====================================================";

		cin.ignore();
		cin.get();
		return;

	}
	else if (num == 3) {
		gotoxy(x, y); y++;
		cout << "====================================================";
		gotoxy(x, y); y++;
		cout << "삭제할 도서 번호를 입력하세요 : ";
		cin >> delBookNum;

		for (i = 0; i < m_bookCount; i++) {
			if (m_book[i].getBookNum() == delBookNum) {
				m_book[i].setBook(0, "삭제됨", "삭제됨", "삭제됨", 0);
			}
		}

		y += 1;

		gotoxy(x, y); y++;
		cout << delBookNum << "번 책을 삭제함" << endl;
		gotoxy(x, y); y++;
		cout << "====================================================";

		cin.ignore();
		cin.get();
		return;


	}
	else {
		gotoxy(x, y); y++;
		cout << "====================================================";
		gotoxy(x, y); y++;
		cout << "메뉴에 있는 숫자를 입력해주세요" << endl;
		gotoxy(x, y); y++;
		cout << "====================================================";

	}
}

Library::Library()
{
	student_count = 0;
	teacher_count = 0;
	m_bookCount = 0;
}
// 데이터를 불러오는 함수
void Library::loadData()
{
	ifstream fin("student.txt");
	ifstream fin2("teacher.txt");
	ifstream fin3("book.txt");
	string name, bookName, writer, subject, publisher, bookStr;
	int  hakbun, number, rent, bookNum, bookCnt, rb1, rb2, rb3, rCnt;

	//if (fp == 0) return;
	//if (fp2 == 0) return;
	
	while (fin >> name >> hakbun ) {
		if (name == "삭제됨") {

		}
		else {
			student_member[student_count].setMember(name, hakbun);
			student_count++;

		}
	}
	while (fin2 >> name >> subject >> number) {
			if (name == "삭제됨") {

			}
			else {
				teacher_member[teacher_count].setMember(name, subject, number);
				teacher_count++;

			}
	}
	while (getline(fin3, bookStr)) {

		char str_buff[500];
		
		strcpy(str_buff, bookStr.c_str());

		char* sArr[10] = { NULL, };
		int i = 0;
		int cnt = 0;

		char* ptr = strtok(str_buff, "\t\t");
		while(ptr != NULL)            // 자른 문자열이 나오지 않을 때까지 반복
		{
			sArr[i] = ptr;             // 문자열을 자른 뒤 메모리 주소를 문자열 포인터 배열에 저장
			i++;                       // 인덱스 증가

			ptr = strtok(NULL, "\t");   // 다음 문자열을 잘라서 포인터를 반환
		}

		for (int i = 0; i < 10; i++)
		{
			if (sArr[i] != NULL) { // 문자열 포인터 배열의 요소가 NULL이 아닐 때만
				if (i == 0) {
					bookNum = atoi(sArr[i]);
					
				}
				else if (i == 1) {
					bookName = sArr[i];
					
				}
				else if (i == 2) {
					writer = sArr[i];
					
				}
				else if (i == 3) {
					publisher = sArr[i];
					
				}
				else if (i == 4) {
					rent = atoi(sArr[i]);
					
				}
			}
		}
		if (!(name == "삭제됨"))
			m_book[m_bookCount].setBook(bookNum, bookName, writer, publisher, rent);
			m_bookCount++;
	}

	fin.close();
	fin2.close();
	fin3.close();
}

// 데이터를 저장하는 함수
void Library::saveData()
{
	ofstream fp("student.txt");
	ofstream fp2("teacher.txt");
	ofstream fp3("book.txt");
	
	string name, subject, bookStr;
	int  hakbun, number, rent, bookNum;

	for (int i = 0; i < student_count; i++)
	{
		if (student_member[i].getName() == "삭제됨") {

		}
		else {
			fp << student_member[i].getName() << setw(10) << student_member[i].getHakbun() << endl;
		}
	}
	for (int i = 0; i < teacher_count; i++)
	{
		if (teacher_member[i].getName() == "삭제됨") {

		}
		else {
			fp2 << teacher_member[i].getName() << setw(10) << teacher_member[i].getSubject() << setw(10) << teacher_member[i].getNumber() << endl;

		}
	}

	for (int i = 0; i < m_bookCount; i++)
	{
		bookStr = to_string(m_book[i].getBookNum()) + "\t\t" + m_book[i].getName() + "\t\t" + m_book[i].getWriter() + "\t\t" + m_book[i].getPublisher() + "\t\t" + to_string(m_book[i].getMember());
		fp3 << bookStr << endl;
	}

	fp.close();
	fp2.close();
	fp3.close();
}

// 회원 추가 - 완료
void Library::addMember()
{
	int num;
	string name, writer, subject;
	int  hakbun, number;
	boolean flag= true;

	cout << "\n\t\t====================================================\n";
	cout << "\t\t\t\t회원 추가 메뉴\n" << endl;

	cout << "\t\t1. 학생 회원 추가\n";
	cout << "\t\t2. 선생님 회원 추가\n";
	cout << "\n\t\t >> ";
	cin >> num;

	cout << "\n\t\t====================================================\n";

	if (num == 1) {
		cin.ignore();
		cout << "\n\t\t이름을 입력해주세요 : ";
		getline(cin, name);

		cout << "\t\t학번을 입력해주세요 : ";
		cin >> hakbun;

		cout << "\n\t\t====================================================\n";

		for (int i = 0; i < student_count; i++)
		{
			if (student_member[i].getName() == name && student_member[i].getHakbun() == hakbun){
				gotoxy(10, 14);
				student_member[i].member_list();
				cout << "\n\t\t\t이미 동일한 정보의 회원이 존재합니다!" << endl;
				flag = false;
			}
			else if (student_member[i].getHakbun() == hakbun)
			{
				gotoxy(10, 14);
				student_member[i].member_list();
				cout << "\n\t\t\t이미 동일한 학번의 회원이 존재합니다!" << endl;
				flag = false;
			}
		}

		if (flag == true) {

			student_member[student_count].addMember(name, hakbun);
			student_count++;
			cout << "\n\t\t이름 : " << name << "\t학번 : " << hakbun << endl;
			cout << "\n\t\t 회원이 추가 되었습니다!" << endl;
		}
	}
	else if (num == 2) {
		cin.ignore();
		cout << "\t\t이름을 입력해주세요 : ";
		getline(cin, name);

		cout << "\t\t담당 과목을 입력해주세요 : ";
		getline(cin, subject);

		cout << "\t\t회원 번호를 입력해주세요 : ";
		cin >> number;

		cout << "\n\t\t====================================================\n";

		for (int i = 0; i < teacher_count; i++)
		{
			if (teacher_member[i].getName() == name && teacher_member[i].getSubject() == subject && teacher_member[i].getNumber() == number)
			{
				gotoxy(10, 14);
				teacher_member[i].member_list();
				cout << "\n\t\t\t이미 동일한 정보의 회원이 존재합니다!" << endl;
				flag = false;
			}
			else if (teacher_member[i].getNumber() == number)
			{
				gotoxy(10, 14);
				teacher_member[i].member_list();
				cout << "\n\t\t\t이미 동일한 학번의 회원이 존재합니다!" << endl;
				flag = false;
			}
		}

		if (flag == true) {
			teacher_member[teacher_count].setMember(name, subject, number);
			teacher_count++;
			cout << "\n\t\t이름 : " << name << "\t과목 : " << subject << "\t회원 번호 : " << number << endl;
			cout << "\n\t\t 회원이 추가 되었습니다" << endl;
		}
	}
	else {
		cout << "\n\t\t1,2번 안에서 선택해주세요" << endl;
	}
	cout << "\n\t\t====================================================\n";

	cin.ignore();
	cin.get();
}

// 회원 찾기 - 완료
void Library::searchMember()
{
	string name, subject;
	int hakbun, num, number;
	boolean flag = false;

	int x = 10, y = 2;

	gotoxy(x, y); y++;
	cout << "====================================================";
	gotoxy(x, y); y++;
	cout << "회원 찾기 메뉴"<<endl;
	y += 1;
	gotoxy(x, y); y++;
	cout << "1. 학생 회원 찾기";
	gotoxy(x, y); y++;
	cout << "2. 선생님 회원 찾기";
	y += 1;
	gotoxy(x, y); y++;
	cout << " >> ";
	cin >> num;

	if (num == 1) {
		y += 1;
		gotoxy(x, y); y++;
		cout << "====================================================";
		gotoxy(x, y); y++;
		cout << "학생의 이름을 입력해주세요" << endl;
		y += 1;
		gotoxy(x, y); y++;
		cout << "이름을 입력해주세요 : ";
		cin >> name;
		gotoxy(x, y); y++;
		cout << "====================================================" << endl;

		y += 1;
		for (int i = 0; i < student_count; i++)
		{
			if (student_member[i].getName() == name)
			{
				gotoxy(x, y); y++;
				student_member[i].member_list();
				flag = true;
			}
		}
		
	}else if (num == 2) {
		y += 1;
		gotoxy(x, y); y++;
		cout << "====================================================";
		gotoxy(x, y); y++;
		cout << "선생님의 성함을 입력해주세요" << endl;
		y += 1;
		gotoxy(x, y); y++;
		cout << "이름을 입력해주세요 : ";
		cin >> name;
	
		gotoxy(x, y); y++;
		cout << "====================================================" << endl;


			y += 1;
			for (int i = 0; i < teacher_count; i++)
			{
				if (teacher_member[i].getName() == name)
				{
					gotoxy(x, y); y++;
					teacher_member[i].member_list();
					flag = true;
				}
			}

			
		
	}
	else {
		gotoxy(x, y); y++;
		cout << "1, 2번 중에서 선택해주세요" << endl;
		y += 1;
		gotoxy(x, y); y++;
		cout << "====================================================" << endl;
		flag = true;
	}

	if (flag == false) {

		
		y += 1;
		gotoxy(x, y); y++;
		cout << "====================================================" << endl;
		gotoxy(x, y); y++;
		cout << name << "회원이 존재하지 않습니다" << endl;
		gotoxy(x, y); y++;
		cout << "====================================================" << endl;
	}
	else {
		y += 1;
		gotoxy(x, y); y++;
		cout << "====================================================" << endl;
		gotoxy(x, y); y++;
		cout << "회원이 존재합니다!" << endl;
		gotoxy(x, y); y++;
		cout << "====================================================" << endl;

	}
	
	cin.ignore();
	cin.get();
}


// 회원 수정 - 완료
void Library::modifyMember()
{
	int num;
	string name, writer, subject;
	int  hakbun, number, nowNum;
	boolean flag = true, hakbunFlag = false;
	int result = 1;

	int x = 10, y = 2;
	gotoxy(x, y); y++;
	cout << "====================================================";
	gotoxy(x, y); y++;
	cout << "회원 수정 메뉴" << endl;
	y += 1;
	gotoxy(x, y); y++;
	cout << "1. 학생 정보 수정\n";
	gotoxy(x, y); y++;
	cout << "2. 선생님 정보 수정\n";
	gotoxy(x, y); y++;
	cout << ">> ";
	cin >> num;
	y += 1;
	if (num == 1) {
		gotoxy(x, y); y++;
		cout << "====================================================";
		gotoxy(x, y); y++;
		cout << "학번을 이용해 학생의 정보를 수정합니다" << endl;
		y += 1;
		gotoxy(x, y); y++;
		cout << "현재 학번 : ";
		cin >> nowNum;


		for (int i = 0; i < student_count; i++)
		{
			if (student_member[i].getHakbun() == nowNum)
			{
				
				result = 2;
				y += 1;
				gotoxy(x, y); y++;
				cout << "== 기존 정보 ==" << endl;
				gotoxy(x, y); y++;
				student_member[i].member_list();

				student_member[i].setHakbun(-1);
				
				y += 1;
				gotoxy(x, y); y++;
				cout << "== 바꾸실 정보 기입 ==" << endl;

				cin.ignore();
				gotoxy(x, y); y++;
				cout << "이름을 입력해주세요 : ";
				getline(cin, name);

				gotoxy(x, y); y++;
				cout << "학번을 입력해주세요 : ";
				cin >> hakbun;

				y += 1;
				gotoxy(x, y); y++;
				cout << "====================================================";

				for (int i = 0; i < student_count; i++)
				{
					if (student_member[i].getName() == name && student_member[i].getHakbun() == hakbun) {
						gotoxy(x, y); y++;
						student_member[i].member_list();
						gotoxy(x, y); y++;
						cout << "이미 동일한 정보의 회원이 존재합니다!" << endl;
						flag = false;
						gotoxy(x, y); y++;
						cout << "====================================================";
					}
					else if (student_member[i].getHakbun() == hakbun)
					{
						gotoxy(x, y); y++;
						student_member[i].member_list();
						gotoxy(x, y); y++;
						cout << "이미 동일한 학번의 회원이 존재합니다!" << endl;
						gotoxy(x, y); y++;
						cout << "====================================================";
						flag = false;
					}
				}

				if (flag == true) {

					student_member[i].addMember(name, hakbun);
					gotoxy(x, y); y++;
					cout << "이름 : " << name << "\t학번 : " << hakbun << endl;
					gotoxy(x, y); y++;
					cout << "회원 정보가 수정 되었습니다!" << endl;
					gotoxy(x, y); y++;
					cout << "====================================================";

					hakbunFlag == true;
				}
			}
		
		}
		if (result == 1) {
			gotoxy(x, y); y++;
			cout << "찾으시는 번호가 없습니다" << endl;
			gotoxy(x, y); y++;
			cout << "====================================================";
		}
	}
	else if (num == 2) {
		gotoxy(x, y); y++;
		cout << "====================================================";
		gotoxy(x, y); y++;
		cout << "회원 번호을 이용해 선생님의 정보를 수정합니다" << endl;
		y += 1;
		gotoxy(x, y); y++;
		cout << "현재 사용중인 회원 번호 : ";
		cin >> nowNum;

		for (int i = 0; i < teacher_count; i++)
		{
			if (teacher_member[i].getNumber() == nowNum)
			{
				result = 2;
				y += 1;
				gotoxy(x, y); y++;
				cout << "== 기존 정보 ==" << endl;
				gotoxy(x, y); y++;
				teacher_member[i].member_list();

				teacher_member[i].setNumber(-1);

				y += 1;
				gotoxy(x, y); y++;
				cout << "== 바꾸실 정보 기입 ==" << endl;

				cin.ignore();
				gotoxy(x, y); y++;
				cout << "이름을 입력해주세요 : ";
				getline(cin, name);

				gotoxy(x, y); y++;
				cout << "담당 과목을 입력해주세요 : ";
				getline(cin, subject);

				gotoxy(x, y); y++;
				cout << "회원 번호를 입력해주세요 : ";
				cin >> number;

				y += 1;
				gotoxy(x, y); y++;
				cout << "====================================================";

				for (int i = 0; i < teacher_count; i++)
				{
					
					if (teacher_member[i].getName() == name && teacher_member[i].getSubject() == subject && teacher_member[i].getNumber() == number) {
						gotoxy(x, y); y++;
						teacher_member[i].member_list();
						gotoxy(x, y); y++;
						cout << "이미 동일한 정보의 회원이 존재합니다!" << endl;
						flag = false;
						gotoxy(x, y); y++;
						cout << "====================================================";
					}
					else if (teacher_member[i].getNumber() == number)
					{
						gotoxy(x, y); y++;
						teacher_member[i].member_list();
						gotoxy(x, y); y++;
						cout << "이미 동일한 회원번호의 회원이 존재합니다!" << endl;
						flag = false; 
						gotoxy(x, y); y++;
						cout << "====================================================";
					}
				}

				if (flag == true) {
					teacher_member[i].setMember(name, subject, number);
					gotoxy(x, y); y++;
					cout << "이름 : " << name << "\t과목 : " << subject << "\t회원 번호 : " << number << endl;
					gotoxy(x, y); y++;
					cout << "회원정보가 수정되었습니다!" << endl;
					gotoxy(x, y); y++;
					cout << "====================================================";
					
				}
			}
		}
		if (result == 1) {
			y += 1;
			gotoxy(x, y); y++;
			cout << "찾으시는 번호가 없습니다" << endl;
			gotoxy(x, y); y++;
			cout << "====================================================";
		}
	}else{
			y += 1;
			gotoxy(x, y); y++;
			cout << "1, 2번만 지원합니다." << endl;	
			gotoxy(x, y); y++;
			cout << "====================================================";
	}

	
	cin.ignore();
	cin.get();
	
}
// 회원 목록 보기 - 완료
void Library::listMember()
{
	int x = 10, y = 2;
	gotoxy(x, y); y++;
	cout << "====================================================";
	gotoxy(x, y); y++;
	cout << "\t\t학생 회원 ( 이름 / 학번 )";
	gotoxy(x, y); y++;
	cout << "====================================================";


	for (int i = 0; i < student_count; i++)
	{
		gotoxy(x + 8, y); y++;
		student_member[i].member_list();
	}
	gotoxy(x, y); y++;
	cout << "====================================================";

	y += 2;
	gotoxy(x, y); y++;
	cout << "====================================================";
	gotoxy(x, y); y++;
	cout << "\t   선생님 회원 ( 이름 / 과목 / 회원 번호 )";
	gotoxy(x, y); y++;
	cout << "====================================================";

	for (int i = 0; i < teacher_count; i++)
	{
		gotoxy(x + 7, y); y++;
		teacher_member[i].member_list();
	}
	gotoxy(x, y); y++;
	cout << "====================================================";

	cin.ignore();
	cin.get();
}

// 책 추가 - 완료
void Library::addBook()
{
	int bookNum, bookCnt;
	string bookName, writer, publisher;
	boolean flag = true;

	int x = 10, y = 2;
	gotoxy(x, y); y++;
	cout << "====================================================";
	gotoxy(x, y); y++;
	cout << "\t\t도서 추가 메뉴" << endl;
	gotoxy(x, y); y++;
	cout << "====================================================";
	y += 1;

	cin.ignore();
	gotoxy(x, y); y++;
	cout << "도서 번호을 입력해주세요 : ";
	cin >> bookNum;

	for (int i = 0; i < m_bookCount; i++) {
		if (m_book[i].getBookNum() == bookNum) {
			y += 1;
			gotoxy(x, y); y++;
			cout << "====================================================";
			gotoxy(x, y); y++;
			m_book[i].bookList();
			gotoxy(x, y); y++;
			cout << "====================================================";
			gotoxy(x, y); y++;
			cout << "입력한 도서 번호는 사용 중입니다" << endl;
			gotoxy(x, y); y++;
			cout << "다른 도서번호를 입력해주세요" << endl;
			gotoxy(x, y); y++;
			cout << "====================================================";
			flag = false;
		}
	}


	if (flag == true) {
		cin.ignore();
		gotoxy(x, y); y++;
		cout << "도서 이름을 입력해주세요 : ";
		getline(cin, bookName);


		gotoxy(x, y); y++;
		cout << "작가명을 입력해주세요 : ";
		getline(cin, writer);

		gotoxy(x, y); y++;
		cout << "출판사를 입력해주세요 : ";
		getline(cin, publisher);


		y += 1;
		gotoxy(x, y); y++;
		cout << "====================================================";

		m_book[m_bookCount].addBook(bookNum, bookName, writer, publisher);
		gotoxy(x, y); y++;
		m_book[m_bookCount].bookList();
		m_bookCount++;
		y += 1;
		gotoxy(x, y); y++;
		cout << "도서를 등록했습니다" << endl;
		gotoxy(x, y); y++;
		cout << "====================================================";
	}
	cin.ignore();
	cin.get();
}

// 책 찾기 - 완료 
void Library::searchBook()
{
	int ch;
	int x = 10, y = 2;
	int bookNum;
	string bookName, writer, publisher;
	boolean flag = false;

	gotoxy(x, y); y++;
	cout << "====================================================";
	gotoxy(x, y); y++;
	cout << "도서 찾기 메뉴" << endl;
	gotoxy(x, y); y++;
	cout << "====================================================";
	y += 1;
	gotoxy(x, y); y++;
	cout << "1. 도서 번호로 찾기";
	gotoxy(x, y); y++;
	cout << "2. 도서 제목으로 찾기";
	gotoxy(x, y); y++;
	cout << "3. 작가로 찾기";
	gotoxy(x, y); y++;
	cout << "4. 출판사로 찾기";
	y += 1;
	gotoxy(x, y); y++;
	cout << " >> ";
	cin >> ch;

	y += 1;
	gotoxy(x, y); y++;
	cout << "====================================================";

	cin.ignore();

	switch (ch)
	{
	case 1:
		gotoxy(x, y); y++;
		cout << "도서 번호를 입력해주세요 : ";
		cin >> bookNum;
		y += 1;
		gotoxy(x, y); y++;
		cout << "====================================================";
		
		for (int i = 0; i < m_bookCount; i++)
		{
			if (m_book[i].getBookNum() == bookNum)
			{
				
				if (m_book[i].getMember() == -1) {
					gotoxy(x, y); y++;
					cout << m_book[i].getBookNum() << " / " << m_book[i].getName() << " / " << m_book[i].getWriter() << " / " << m_book[i].getPublisher()
						<< " / " << "대여 가능" << endl;
				}
				else if (m_book[i].getMember() == 0) {

				}
				else {
					gotoxy(x, y); y++;
					cout << m_book[i].getBookNum() << " / " << m_book[i].getName() << " / " << m_book[i].getWriter() << " / " << m_book[i].getPublisher()
						<< " / " << m_book[i].getMember() << endl;
				}
				flag = true;
			}
		}
		y += 1;
		gotoxy(x, y); y++;
		cout << "====================================================";
		break;
	case 2:
		gotoxy(x, y); y++;
		cout << "도서 제목을 입력해주세요 : ";
		getline(cin, bookName);

		y += 1;
		gotoxy(x, y); y++;
		cout << "====================================================";

		for (int i = 0; i < m_bookCount; i++)
		{
			if (m_book[i].getName() == bookName)
			{
				if (m_book[i].getMember() == -1) {
					gotoxy(x, y); y++;
					cout << m_book[i].getBookNum() << " / " << m_book[i].getName() << " / " << m_book[i].getWriter() << " / " << m_book[i].getPublisher()
						<< " / " << "대여 가능" << endl;
				}
				else if (m_book[i].getMember() == 0) {

				}
				else {
					gotoxy(x, y); y++;
					cout << m_book[i].getBookNum() << " / " << m_book[i].getName() << " / " << m_book[i].getWriter() << " / " << m_book[i].getPublisher()
						<< " / " << m_book[i].getMember() << endl;
				}
				flag = true;
			}
		}
		y += 1;
		gotoxy(x, y); y++;
		cout << "====================================================";
		break;
	case 3:
		gotoxy(x, y); y++;
		cout << "작가명을 입력해주세요 : ";
		getline(cin, writer);

		y += 1;
		gotoxy(x, y); y++;
		cout << "====================================================";

		for (int i = 0; i < m_bookCount; i++)
		{
			if (m_book[i].getWriter() == writer)
			{
				if (m_book[i].getMember() == -1) {
					gotoxy(x, y); y++;
					cout << m_book[i].getBookNum() << " / " << m_book[i].getName() << " / " << m_book[i].getWriter() << " / " << m_book[i].getPublisher()
						<< " / " << "대여 가능" << endl;
				}
				else if (m_book[i].getMember() == 0) {

				}
				else {
					gotoxy(x, y); y++;
					cout << m_book[i].getBookNum() << " / " << m_book[i].getName() << " / " << m_book[i].getWriter() << " / " << m_book[i].getPublisher()
						<< " / " << m_book[i].getMember() << endl;
				}
				flag = true;
			}
		}
		y += 1;
		gotoxy(x, y); y++;
		cout << "====================================================";
		break;
	case 4:
		gotoxy(x, y); y++;
		cout << "출판사를 입력해주세요 : ";
		getline(cin, publisher);

		y += 1;
		gotoxy(x, y); y++;
		cout << "====================================================";

		for (int i = 0; i < m_bookCount; i++)
		{
			if (m_book[i].getPublisher() == publisher)
			{
				if (m_book[i].getMember() == -1) {
					gotoxy(x, y); y++;
					cout << m_book[i].getBookNum() << " / " << m_book[i].getName() << " / " << m_book[i].getWriter() << " / " << m_book[i].getPublisher()
						<< " / " << "대여 가능" << endl;
				}
				else if (m_book[i].getMember() == 0) {

				}
				else {
					gotoxy(x, y); y++;
					cout << m_book[i].getBookNum() << " / " << m_book[i].getName() << " / " << m_book[i].getWriter() << " / " << m_book[i].getPublisher()
						<< " / " << m_book[i].getMember() << endl;
				}
				flag = true;
			}
		}
		y += 1;
		gotoxy(x, y); y++;
		cout << "====================================================";
		break;
	default:
		gotoxy(x, y); y++;
		cout << "제시된 번호를 입력해주세요"<<endl;
		y += 1;
		gotoxy(x, y); y++;
		cout << "====================================================";
	}

	if (flag == false) {
		gotoxy(x, y); y++;
		cout << "찾으시는 도서가 없습니다" << endl;
		y += 1;
		gotoxy(x, y); y++;
		cout << "====================================================";
	}
	cin.ignore();
	cin.get();
}

// 책 목록 보기 - 완료
void Library::listBook()
{
	int x = 10, y = 2;
	gotoxy(x, y); y++;
	cout << "====================================================\n";
	gotoxy(x, y); y++;
	cout << "\t 도서 목록 (도서명 / 작가 / 출판사 / 대여 정보) \n";
	gotoxy(x, y); y++;
	cout << "====================================================\n";

	for (int i = 0; i < m_bookCount; i++)
	{
		if (m_book[i].getMember() == -1) {
			gotoxy(x, y); y++;
			cout << m_book[i].getBookNum() << " / " << m_book[i].getName() << " / " << m_book[i].getWriter() << " / " << m_book[i].getPublisher()
				<< " / " << "대여 가능" << endl;
		}
		else if (m_book[i].getMember() == 0) {

		}
		else {
			gotoxy(x, y); y++;
			cout << m_book[i].getBookNum() << " / " << m_book[i].getName() << " / " << m_book[i].getWriter() << " / " << m_book[i].getPublisher()
				<< " / " << m_book[i].getMember() << endl;
		}
	}
	gotoxy(x, y); y++;
	cout << "====================================================\n";
	cin.ignore();
	cin.get();
}

void Library::listBookManager()
{
	int x = 10, y = 2;
	gotoxy(x, y); y++;
	cout << "====================================================\n";
	gotoxy(x, y); y++;
	cout << "\t 도서 목록 (도서명 / 작가 / 출판사 / 대여 정보) \n";
	gotoxy(x, y); y++;
	cout << "====================================================\n";

	for (int i = 0; i < m_bookCount; i++)
	{
		if (m_book[i].getMember() == -1) {
			gotoxy(x, y); y++;
			cout << m_book[i].getBookNum() << " / " << m_book[i].getName() << " / " << m_book[i].getWriter() << " / " << m_book[i].getPublisher()
				<< " / " << "대여 가능" << endl;
		}
		else if (m_book[i].getMember() == 0) {

		}
		else {
			gotoxy(x, y); y++;
			cout << m_book[i].getBookNum() << " / " << m_book[i].getName() << " / " << m_book[i].getWriter() << " / " << m_book[i].getPublisher()
				<< " / " << m_book[i].getMember() << endl;
		}
	}
	gotoxy(x, y); y++;
	cout << "====================================================\n";
	cin.ignore();
	cin.get();
}

//대출 내역 - 완료
void Library::showStudentNOW() {
	string name, bookname;
	int bookNum, num, hakbun, number, i, j, chk = 0, cnt = 1;
	boolean flag = false;


	int x = 10, y = 2;
	gotoxy(x, y); y++;
	cout << "====================================================";
	gotoxy(x, y); y++;
	cout << "대출 내역을 확인하고 싶은 학번을 입력하세요 : ";
	cin >> hakbun;

	for (i = 0; i < student_count; i++)
	{
		if (student_member[i].getHakbun() == hakbun)
		{

			gotoxy(x, y); y++;
			cout << "====================================================\n";
			gotoxy(x, y); y++;
			cout << "\t 대출 내역 (도서번호 / 도서명 / 작가 / 출판사) \n";
			gotoxy(x, y); y++;
			cout << "====================================================\n";

			for (j = 0; j < m_bookCount; j++) {
				if (student_member[i].getHakbun() == m_book[j].getMember()) {
					gotoxy(x, y); y++;
					cout << m_book[j].getBookNum() << " / " << m_book[j].getName() << " / " << m_book[j].getWriter() << " / " << m_book[i].getPublisher();

				}
			}
			gotoxy(x, y); y++;
			cout << "====================================================\n";
			flag = true;
		}
	}
	if (flag == false) {
		gotoxy(x, y); y++;
		cout << "\t찾으시는 학번이 없습니다 \n";
		gotoxy(x, y); y++;
		cout << "====================================================\n";
	}
	cin.ignore();
	cin.get();

}

void Library::showTeacherNOW() {
	string name, bookname;
	int bookNum, num, hakbun, number, i, j, chk = 0, cnt = 1;
	boolean flag = false;


	int x = 10, y = 2;
	gotoxy(x, y); y++;
	cout << "====================================================";
	gotoxy(x, y); y++;
	cout << "대출 내역을 확인하고 싶은 회원 번호를 입력하세요 : ";
	cin >> number;

	for (i = 0; i < teacher_count; i++)
	{
		if (teacher_member[i].getNumber() == number)
		{

			gotoxy(x, y); y++;
			cout << "====================================================\n";
			gotoxy(x, y); y++;
			cout << "\t 대출 내역 (도서번호 / 도서명 / 작가 / 출판사) \n";
			gotoxy(x, y); y++;
			cout << "====================================================\n";
		
			for (j = 0; j < m_bookCount; j++) {
				if (teacher_member[i].getNumber() == m_book[j].getMember()) {
					gotoxy(x, y); y++;
					cout << m_book[j].getBookNum() << " / " << m_book[j].getName() << " / " << m_book[j].getWriter() << " / " << m_book[i].getPublisher();
		
				}
			}
			gotoxy(x, y); y++;
			cout << "====================================================\n";
			flag = true;
		}
	}
	if (flag == false) {
		gotoxy(x, y); y++;
		cout << "\t찾으시는 번호가 없습니다 \n";
		gotoxy(x, y); y++;
		cout << "====================================================\n";
	}
	cin.ignore();
	cin.get();
}

// 학생대출 - 완료
void Library::rentStudentBook()
{
	
	string name, bookname;
	int bookNum, num, hakbun, number, i, j, chk = 0, cnt =1;

	int x = 10, y = 2;
	gotoxy(x, y); y++;
	cout << "====================================================\n";
	gotoxy(x, y); y++;
	cout << "\t 추천 도서 (도서번호 / 도서명 / 작가 / 출판사 / 대여 정보) \n";
	gotoxy(x, y); y++;
	cout << "====================================================\n";

	while(cnt<=2)
	{
		i = rand() % m_bookCount;
		if (m_book[i].getMember() == -1) {
			gotoxy(x, y); y++;
			cout << m_book[i].getBookNum() << " / " << m_book[i].getName() << " / " << m_book[i].getWriter() << " / " << m_book[i].getPublisher()
				<< " / " << "대여 가능" << endl;
		}
		else if (m_book[i].getMember() == 0) {

		}
		else {
			gotoxy(x, y); y++;
			cout << m_book[i].getBookNum() << " / " << m_book[i].getName() << " / " << m_book[i].getWriter() << " / " << m_book[i].getPublisher()
				<< " / " << m_book[i].getMember() << endl;
		}
		cnt++;
	}

	y += 1;
	gotoxy(x, y); y++;
	cout << "====================================================\n";
	gotoxy(x, y); y++;
	cout << "\t 도서 목록 (도서번호 / 도서명 / 작가 / 출판사 / 대여 정보) \n";
	gotoxy(x, y); y++;
	cout << "====================================================\n";

	for (int i = 0; i < m_bookCount; i++)
	{
		gotoxy(x, y); y++;
		if (m_book[i].getMember() == -1) {
			cout << m_book[i].getBookNum() << " / " << m_book[i].getName() << " / " << m_book[i].getWriter() << " / " << m_book[i].getPublisher()
				<< " / " << "대여 가능" << endl;
		}
	}

	gotoxy(x, y); y++;
	cout << "====================================================\n";

		gotoxy(x, y); y++;
		cout << "사용자의 학번을 입력하세요 : ";
		cin >> hakbun;

		for (i = 0; i < student_count; i++)
		{
			if (student_member[i].getHakbun() == hakbun)
			{
				gotoxy(x, y); y++;
				cout << "====================================================\n";
				gotoxy(x, y); y++;
				student_member[i].member_list();
				y += 1;
				gotoxy(x, y); y++;
				cout << "\t\t\t사용자의 정보가 확인되었습니다.";
				gotoxy(x, y); y++;
				cout << "====================================================\n";
				chk++;
				break;
			}
		}
		if (chk == 0){
			gotoxy(x, y); y++;
			cout << "====================================================\n";
			gotoxy(x, y); y++;
			cout << "\t\t사용자의 정보를 찾을 수 없습니다.";
			gotoxy(x, y); y++;
			cout << "====================================================\n";
			cin.ignore();
			cin.get();
			return;
		}

		y += 1;
		gotoxy(x, y); y++;
		cout << "대여할 도서 번호 : ";
		cin >> bookNum;

		int cnt1=0;
		
		for (j = 0; j < m_bookCount; j++) {
			if (student_member[i].getHakbun() == hakbun && m_book[j].getMember() == student_member[i].getHakbun()) {
				cnt1++;
			}
		}

		chk = 0;
		for (j = 0; j < m_bookCount; j++)
		{
			if (m_book[j].getBookNum() == bookNum &&  m_book[j].getMember() != -1)
			{
				gotoxy(x, y); y++;
				cout << "====================================================\n";
				gotoxy(x, y); y++;
				cout << "\t대출 중인 도서입니다.";
				gotoxy(x, y); y++;
				cout << "====================================================\n";
				chk++;
				cin.ignore();
				cin.get();
				return;
			}
			else if (m_book[j].getBookNum() == bookNum && cnt1 >2)
			{
				gotoxy(x, y); y++;
				cout << "====================================================\n";
				gotoxy(x, y); y++;
				cout << "\t빌릴 수 있는 도서는 최대 3권 입니다.";
				gotoxy(x, y); y++;
				cout << "====================================================\n";
				gotoxy(x, y); y++;
				cout << "\t 대출 내역 (도서번호 / 도서명 / 작가 / 출판사) \n";
				gotoxy(x, y); y++;
				cout << "====================================================\n";

				for (j = 0; j < m_bookCount; j++) {
					if (student_member[i].getHakbun() == m_book[j].getMember()) {
						gotoxy(x, y); y++;
						cout << m_book[j].getBookNum() << " / " << m_book[j].getName() << " / " << m_book[j].getWriter() << " / " << m_book[i].getPublisher();

					}
				}
				gotoxy(x, y); y++;
				cout << "====================================================\n";
				chk++;
				cin.ignore();
				cin.get();
				return;
			}
			else if ( m_book[j].getBookNum() == bookNum && m_book[j].getMember() == -1)
			{
				
				m_book[j].rentBook(student_member[i].getHakbun());
				y += 1;
				gotoxy(x, y); y++;
				cout << "====================================================\n";
				gotoxy(x, y); y++;
				cout << "\t\t대출이 완료되었습니다!" << endl;
				gotoxy(x, y); y++;
				cout << "====================================================\n";
				chk++;
				cin.ignore();
				cin.get();
				return;
			}
		}
		if (chk == 0)
		{
			gotoxy(x, y); y++;
			cout << "====================================================\n";
			gotoxy(x, y); y++;
			cout << "\t도서를 찾을 수 없습니다";
			gotoxy(x, y); y++;
			cout << "====================================================\n";
			cin.ignore();
			cin.get();
			return;
		}


	cin.ignore();
	cin.get();
	
}
void Library::rentTeacherBook()
{

	string name, bookname;
	int bookNum, num, hakbun, number, i, j, chk = 0, cnt = 1;

	int x = 10, y = 2;
	gotoxy(x, y); y++;
	cout << "====================================================\n";
	gotoxy(x, y); y++;
	cout << "\t 추천 도서 (도서번호 / 도서명 / 작가 / 출판사 / 대여 정보) \n";
	gotoxy(x, y); y++;
	cout << "====================================================\n";

	while (cnt <= 2)
	{
		i = rand() % m_bookCount;
		if (m_book[i].getMember() == -1) {
			gotoxy(x, y); y++;
			cout << m_book[i].getBookNum() << " / " << m_book[i].getName() << " / " << m_book[i].getWriter() << " / " << m_book[i].getPublisher()
				<< " / " << "대여 가능" << endl;
		}
		else if (m_book[i].getMember() == 0) {

		}
		else {
			gotoxy(x, y); y++;
			cout << m_book[i].getBookNum() << " / " << m_book[i].getName() << " / " << m_book[i].getWriter() << " / " << m_book[i].getPublisher()
				<< " / " << m_book[i].getMember() << endl;
		}
		cnt++;
	}

	y += 1;
	gotoxy(x, y); y++;
	cout << "====================================================\n";
	gotoxy(x, y); y++;
	cout << "\t 도서 목록 (도서번호 / 도서명 / 작가 / 출판사 / 대여 정보) \n";
	gotoxy(x, y); y++;
	cout << "====================================================\n";

	for (int i = 0; i < m_bookCount; i++)
	{
		if (m_book[i].getMember() == -1) {
			gotoxy(x, y); y++;
			cout << m_book[i].getBookNum() << " / " << m_book[i].getName() << " / " << m_book[i].getWriter() << " / " << m_book[i].getPublisher()
				<< " / " << "대여 가능" << endl;
		}
	}

	gotoxy(x, y); y++;
	cout << "====================================================\n";

	gotoxy(x, y); y++;
	cout << "회원 번호를 입력하세요 : ";
	cin >> number;

	for (i = 0; i < teacher_count; i++)
	{
		if (teacher_member[i].getNumber() == number)
		{
			gotoxy(x, y); y++;
			cout << "====================================================\n";
			gotoxy(x, y); y++;
			teacher_member[i].member_list();
			y += 1;
			gotoxy(x, y); y++;
			cout << "\t\t\t사용자의 정보가 확인되었습니다.";
			gotoxy(x, y); y++;
			cout << "====================================================\n";
			chk++;
			break;
		}
	}
	if (chk == 0) {
		gotoxy(x, y); y++;
		cout << "====================================================\n";
		gotoxy(x, y); y++;
		cout << "\t\t사용자의 정보를 찾을 수 없습니다.";
		gotoxy(x, y); y++;
		cout << "====================================================\n";
		cin.ignore();
		cin.get();
		return;
	}

	y += 1;
	gotoxy(x, y); y++;
	cout << "대여할 도서 번호 : ";
	cin >> bookNum;


	int cnt1 = 0;

	for (j = 0; j < m_bookCount; j++) {
		if (teacher_member[i].getNumber() == number && m_book[j].getMember() == teacher_member[i].getNumber()) {
			cnt1++;
		}
	}

	chk = 0;
	for (j = 0; j < m_bookCount; j++)
	{
		if (m_book[j].getBookNum() == bookNum && m_book[j].getMember() != -1)
		{
			gotoxy(x, y); y++;
			cout << "====================================================\n";
			gotoxy(x, y); y++;
			cout << "\t대출 중인 도서입니다.";
			gotoxy(x, y); y++;
			cout << "====================================================\n";
			chk++;
			cin.ignore();
			cin.get();
			return;
		}
		else if (m_book[j].getBookNum() == bookNum && cnt1 > 4)
		{
			gotoxy(x, y); y++;
			cout << "====================================================\n";
			gotoxy(x, y); y++;
			cout << "\t빌릴 수 있는 도서는 최대 5권 입니다.";
			gotoxy(x, y); y++;
			cout << "====================================================\n";
			gotoxy(x, y); y++;
			cout << "\t 대출 내역 (도서번호 / 도서명 / 작가 / 출판사) \n";
			gotoxy(x, y); y++;
			cout << "====================================================\n";

			for (j = 0; j < m_bookCount; j++) {
				if (student_member[i].getHakbun() == m_book[j].getMember()) {
					gotoxy(x, y); y++;
					cout << m_book[j].getBookNum() << " / " << m_book[j].getName() << " / " << m_book[j].getWriter() << " / " << m_book[i].getPublisher();

				}
			}
			gotoxy(x, y); y++;
			cout << "====================================================\n";
			chk++;
			cin.ignore();
			cin.get();
			return;
		}
		else if (m_book[j].getBookNum() == bookNum && m_book[j].getMember() == -1)
		{
			m_book[j].rentBook(teacher_member[i].getNumber());

			y += 1;
			gotoxy(x, y); y++;
			cout << "====================================================\n";
			gotoxy(x, y); y++;
			cout << "\t\t대출이 완료되었습니다!" << endl;
			gotoxy(x, y); y++;
			cout << "====================================================\n";
			chk++;
			cin.ignore();
			cin.get();
			return;
		}
	}
	if (chk == 0)
	{
		gotoxy(x, y); y++;
		cout << "====================================================\n";
		gotoxy(x, y); y++;
		cout << "\t도서를 찾을 수 없습니다";
		gotoxy(x, y); y++;
		cout << "====================================================\n";
		cin.ignore();
		cin.get();
		return;
	}


	cin.ignore();
	cin.get();
	

}

void Library::returnStudentBook()
{
	

	string name, bookname;
	int bookNum, num, hakbun, number, i, j, k, chk = 0, cnt = 1;
	boolean flag = false;


	int x = 10, y = 2;
	gotoxy(x, y); y++;
	cout << "====================================================";
	gotoxy(x, y); y++;
	cout << "반납 기능을 이용할 학번을 입력하세요 : ";
	cin >> hakbun;

	for (i = 0; i < student_count; i++)
	{
		if (student_member[i].getHakbun() == hakbun)
		{
			gotoxy(x, y); y++;
			cout << "====================================================\n";
			gotoxy(x, y); y++;
			cout << "\t 대출 내역 (도서번호 / 도서명 / 작가 / 출판사) \n";
			gotoxy(x, y); y++;
			cout << "====================================================\n";

			for (j = 0; j < m_bookCount; j++) {
				if (student_member[i].getHakbun() == m_book[j].getMember()) {
					gotoxy(x, y); y++;
					cout << m_book[j].getBookNum() << " / " << m_book[j].getName() << " / " << m_book[j].getWriter() << " / " << m_book[i].getPublisher();

				}
			}
			gotoxy(x, y); y++;
			cout << "====================================================\n";
			flag = true;
		}
	}
	if (flag == false) {
		gotoxy(x, y); y++;
		cout << "\t찾으시는 학번이 없습니다 \n";
		gotoxy(x, y); y++;
		cout << "====================================================\n";
		
		cin.ignore();
		cin.get();
		return;

	}

	flag = false;

	gotoxy(x, y); y++;
	cout << "====================================================";
	gotoxy(x, y); y++;
	cout << "반납할 도서의 도서 번호를 입력하세요 : ";
	cin >> bookNum;

	for (j = 0; j < m_bookCount; j++)
	{
		if (m_book[j].getBookNum() == bookNum)
		{
			
			m_book[j].returnBook();

			gotoxy(x, y); y++;
			cout << "== 반납이 완료되었습니다 ==";
			gotoxy(x, y); y++;
			cout << "====================================================\n";
			flag = true;
			break;
		}
	}
	if (flag == false) {
		gotoxy(x, y); y++;
		cout << "\t도서 번호 입력이 잘못되었습니다. \n";
		gotoxy(x, y); y++;
		cout << "====================================================\n";
		return;
		cin.ignore();
		cin.get();

	}


	cin.ignore();
	cin.get();

}

void Library::returnTeacherBook()
{

	string name, bookname;
	int bookNum, num, hakbun, number, i, j, chk = 0, cnt = 1;
	boolean flag = false;


	int x = 10, y = 2;
	gotoxy(x, y); y++;
	cout << "====================================================";
	gotoxy(x, y); y++;
	cout << "반납 기능을 이용할 회원 번호을 입력하세요 : ";
	cin >> number;

	for (i = 0; i < teacher_count; i++)
	{
		if (teacher_member[i].getNumber() == number)
		{

			gotoxy(x, y); y++;
			cout << "====================================================\n";
			gotoxy(x, y); y++;
			cout << "\t 대출 내역 (도서번호 / 도서명 / 작가 / 출판사) \n";
			gotoxy(x, y); y++;
			cout << "====================================================\n";

			for (j = 0; j < m_bookCount; j++) {
				if (teacher_member[i].getNumber() == m_book[j].getMember()) {
					gotoxy(x, y); y++;
					cout << m_book[j].getBookNum() << " / " << m_book[j].getName() << " / " << m_book[j].getWriter() << " / " << m_book[i].getPublisher();

				}
			}
			gotoxy(x, y); y++;
			cout << "====================================================\n";
			flag = true;
		}
	}
	if (flag == false) {
		gotoxy(x, y); y++;
		cout << "\t찾으시는 번호가 없습니다 \n";
		gotoxy(x, y); y++;
		cout << "====================================================\n";

		cin.ignore();
		cin.get();
		return;

	}

	flag = false;

	gotoxy(x, y); y++;
	cout << "====================================================";
	gotoxy(x, y); y++;
	cout << "반납할 도서의 도서번호를 입력하세요 : ";
	cin >> bookNum;

	for (j = 0; j < m_bookCount; j++)
	{
		if (m_book[j].getBookNum() == bookNum)
		{

			m_book[j].returnBook();
		
			gotoxy(x, y); y++;
			cout << "== 반납이 완료되었습니다 ==";
			gotoxy(x, y); y++;
			cout << "====================================================\n";
			flag = true;
			break;
		}
	}
	if (flag == false) {
		gotoxy(x, y); y++;
		cout << "\t도서 번호 입력이 잘못되었습니다. \n";
		gotoxy(x, y); y++;
		cout << "====================================================\n";
		return;
		cin.ignore();
		cin.get();

	}


	cin.ignore();
	cin.get();

}


void intro();	//function to write record in binary file
void startMenu(Library);
void studentMenu(Library);
void teacherMenu(Library);
void managerCheck(Library);
void managerMenu(Library);


int main()
{
	system("mode con cols=100 lines=30 | title MIRIM LIBRARY"); // 콘솔창 크기 및 제목 설정
	COORD newSize = { 100,9999 };
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), newSize);
	char ch, ch1;
	int num;

	Library data;

	data.loadData();
	
	intro();
	startMenu(data);
	

	return 0;
}


void intro()
{
	gotoxy(10, 5);
	cout << "====================================================";
	gotoxy(10, 8);
	cout << "\t미림도서관에 오신걸 환영합니다!";
	gotoxy(10, 10);
	cout << "\tWELCOME TO MIRIM LIBRARY";
	gotoxy(10, 13);
	cout << "\t\t\tenter키를 눌러서 시작하세요. . ";
	gotoxy(10, 14);
	cout << "====================================================";

	cin.get();
}

void startMenu(Library data) {

	int ch;

	system("cls");
	int x = 10, y = 4;
	gotoxy(x, y); y++;
	cout << "오늘도 희망찬 미림도서관!";
	gotoxy(x, y); y++;
	cout << "====================================================";
	y += 1;
	gotoxy(x, y); y++;
	cout << "\t원하시는 메뉴의 숫자를 입력해 접속해주세요.";
	y += 1;
	gotoxy(x, y); y++;
	cout << "====================================================";

	y += 1;
	gotoxy(x, y); y++;
	cout << " 1. 학생";
	gotoxy(x, y); y++;
	cout << " 2. 선생님";
	gotoxy(x, y); y++;
	cout << " 3. 관리자";
	gotoxy(x, y); y++;
	cout << " 4. 종료";
	y += 1;
	gotoxy(x, y); y++;
	cout << "====================================================";

	y += 1;
	gotoxy(x, y); y++;
	cout << " >> ";
	cin >> ch;

	switch (ch)
	{
	case 1:
		studentMenu(data);
		break;
	case 2:
		teacherMenu(data);
		break;
	case 3:
		managerCheck(data);
		break;
	case 4:
		cout << "\n도서관을 이용해주셔서 감사합니다" << endl;
		break;
	default:cout << "\a";
	}

}
void managerCheck(Library data) {

	int check_pw;
	int x = 10, y = 7, pw = 2020, input = 0;
	system("cls");
	gotoxy(x, y); y++;
	cout << "관리자 번호를 입력해주세요";
	gotoxy(x, y); y++;
	cout << " >> ";
	cin >> check_pw;

	if (check_pw == pw) {
		managerMenu(data);
	}
	else {
		system("cls");
		gotoxy(10, 6);
		cout << "!! 관리자 번호가 아닙니다 !!";
		gotoxy(10, 7);
		cout << "SPACE를 누르면 처음 화면으로 돌아갑니다" << endl;
		gotoxy(10, 8);
		cout << "아무 키를 누르면 도서관 시스템이 종료됩니다" << endl;

		input = _getch();
		if (input == SPACE) {
			startMenu(data);
		}
		else {
			gotoxy(10, 10);
			cout << "도서관을 이용해주셔서 감사합니다" << endl;
			gotoxy(10, 11);
			cout << "====================================================" << endl;
		}



	}
}

void studentMenu(Library data) {
	int ch;
	int input = 0;

	do {
		system("cls");
		int x = 10, y = 4;
		gotoxy(x, y); y++;
		cout << "미림도서관 - 학생 모드 접속 중";
		gotoxy(x, y); y++;
		cout << "====================================================";
		y += 1;
		gotoxy(x, y); y++;
		cout << "\t아래의 메뉴에서 원하는 기능을 선택하세요";
		y += 1;
		gotoxy(x, y); y++;
		cout << "====================================================";

		y += 1;

		gotoxy(x, y); y++;
		cout << " 1. 책 대출 하기";
		gotoxy(x, y); y++;
		cout << " 2. 책 반납 하기";
		gotoxy(x, y); y++;
		cout << " 3. 책 목록 보기";
		gotoxy(x, y); y++;
		cout << " 4. 도서 찾기";
		gotoxy(x, y); y++;
		cout << " 5. 대출 내역";
		gotoxy(x, y); y++;
		cout << " 6. 종료";
		y += 1;
		gotoxy(x, y); y++;
		cout << "====================================================";
		y += 1;
		gotoxy(x, y); y++;
		cout << " >> ";
		cin >> ch;

		system("cls");
		switch (ch)
		{
		case 1:
			data.rentStudentBook();
			data.saveData();
			break;

		case 2:
			data.returnStudentBook();
			data.saveData();
			break;
		case 3:
			data.listBook();
			break;

		case 4:
			data.searchBook();
			break;

		case 5:
			data.showStudentNOW();
			break;
		case 6:
			data.saveData();
			gotoxy(10, 5);
			cout << "=== 학생 모드 종료 ===" << endl;
			gotoxy(10, 7);
			cout << "SPACE를 누르면 처음 화면으로 돌아갑니다" << endl;
			gotoxy(10, 8);
			cout << "아무 키를 누르면 도서관 시스템이 종료됩니다" << endl;

			input = _getch();
			if (input == SPACE) {
				startMenu(data);
			}
			else {
				gotoxy(10, 10);
				cout << "도서관을 이용해주셔서 감사합니다" << endl;
				gotoxy(10, 11);
				cout << "====================================================" << endl;
				//cin.ignore();
			}
			break;
		default:
			gotoxy(x, y); y++;
			cout << "잘못된 번호 입력을 하셨습니다.";
			break;
		}
		
	} while (ch != 6);
}

void teacherMenu(Library data) {
	int ch;
	int input = 0;

	do {
		system("cls");
		int x = 10, y = 4;
		gotoxy(x, y); y++;
		cout << "미림도서관 - 선생님 모드 접속 중";
		gotoxy(x, y); y++;
		cout << "====================================================";
		y += 1;
		gotoxy(x, y); y++;
		cout << "\t아래의 메뉴에서 원하는 기능을 선택하세요";
		y += 1;
		gotoxy(x, y); y++;
		cout << "====================================================";

		y += 1;

		gotoxy(x, y); y++;
		cout << " 1. 책 대출 하기";
		gotoxy(x, y); y++;
		cout << " 2. 책 반납 하기";
		gotoxy(x, y); y++;
		cout << " 3. 책 목록 보기";
		gotoxy(x, y); y++;
		cout << " 4. 도서 찾기";
		gotoxy(x, y); y++;
		cout << " 5. 대출 내역";
		gotoxy(x, y); y++;
		cout << " 6. 종료";
		y += 1;
		gotoxy(x, y); y++;
		cout << "====================================================";
		y += 1;
		gotoxy(x, y); y++;
		cout << " >> ";
		cin >> ch;

		system("cls");
		switch (ch)
		{
		case 1:
			data.rentTeacherBook();
			data.saveData();
			break;

		case 2:
			data.returnTeacherBook();
			data.saveData();
			break;
		case 3:
			data.listBook();
			break;

		case 4:
			data.searchBook();
			break;
		case 5:
			data.showTeacherNOW();
			break;
		case 6:
			data.saveData();
			gotoxy(10, 5);
			cout << "=== 선생님 모드 종료 ===" << endl;
			gotoxy(10, 7);
			cout << "SPACE를 누르면 처음 화면으로 돌아갑니다" << endl;
			gotoxy(10, 8);
			cout << "아무 키를 누르면 도서관 시스템이 종료됩니다" << endl;

			input = _getch();
			if (input == SPACE) {
				startMenu(data);
			}
			else {
				gotoxy(10, 10);
				cout << "도서관을 이용해주셔서 감사합니다" << endl;
				gotoxy(10, 11);
				cout << "====================================================" << endl;
				//cin.ignore();
			}
			break;

		default:
			gotoxy(x, y); y++;
			cout << "잘못된 번호 입력을 하셨습니다.";
			break;
		}
	} while (ch != 6);
}
void managerMenu(Library data) {
	int ch;
	int input = 0;
	do {
		system("cls");
		int x = 10, y = 2;
		gotoxy(x, y); y++;
		cout << "== 관리자 모드 ==";
		y += 1;
		gotoxy(x, y); y++;
		cout << "아래의 메뉴에서 원하는 기능을 선택하세요 ";

		y += 1;

		gotoxy(x, y); y++;
		cout << " 1. 회원 추가";
		gotoxy(x, y); y++;
		cout << " 2. 회원 찾기"; 
		gotoxy(x, y); y++;
		cout << " 3. 회원 정보수정"; 
		gotoxy(x, y); y++;
		cout << " 4. 회원 목록 보기"; 
		gotoxy(x, y); y++;
		cout << " 5. 도서 추가 하기"; 
		gotoxy(x, y); y++; 
		cout << " 6. 도서 찾기";
		gotoxy(x, y); y++;
		cout << " 7. 도서 목록 보기";
		gotoxy(x, y); y++;
		cout << " 8. 도서관 정보 관련 삭제";
		gotoxy(x, y); y++;
		cout << " 9. 종료";
		y += 1;
		gotoxy(x, y); y++;
		cout << " >> ";
		cin >> ch;
		system("cls");
		switch (ch)
		{
		case 1:
			data.addMember();
			data.saveData();
			break;

		case 2:
			data.searchMember();
			break;

		case 3:
			data.modifyMember();
			data.saveData();
			break;

		case 4:
			data.listMember();
			break;
		case 5:
			data.addBook();
			data.saveData();
			break;
		case 6:
			data.searchBook();
			break;
		case 7:
			data.listBookManager();
			break;
		case 8:
			data.deleteMember();
			data.saveData();
			break;
		case 9:
			data.saveData();
			gotoxy(10, 5);
			cout << "=== 관리자 모드 종료 ===" << endl;
			gotoxy(10, 7);
			cout << "SPACE를 누르면 처음 화면으로 돌아갑니다" << endl;
			gotoxy(10, 8);
			cout << "아무 키를 누르면 도서관 시스템이 종료됩니다" << endl;

			input = _getch();
			if (input == SPACE) {
				startMenu(data);
			}
			else {
				gotoxy(10, 10);
				cout << "도서관을 이용해주셔서 감사합니다" << endl;
				gotoxy(10, 11);
				cout << "====================================================" << endl;
				//cin.ignore();
			}
			break;

		default:
			gotoxy(x, y); y++;
			cout << "잘못된 번호 입력을 하셨습니다.";
			break;
		}
		/*cin.ignore();
		cin.get();*/
	} while (ch != 9);
}
