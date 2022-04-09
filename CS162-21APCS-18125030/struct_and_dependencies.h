#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <math.h>
#include <sstream>
#include <string.h>
#include <string>

using namespace sf;
using namespace std;

struct Student;
struct StudentNode;
struct Class;
struct ClassNode;
struct Score;
struct Course;
struct CourseNode;
struct MyCourse;
struct Semester;
struct SemesterNode;
struct Year;
struct YearNode;

struct Student
{
	int num;
	string student_id;
	string first_name;
	string last_name;
	bool gender; // male(0), female(1)
	string dob;
	string social_id;
	string password;
	string student_class;
	int subject_amount = 0;
	MyCourse* my_course;
};

struct StudentNode
{
	Student student;
	StudentNode* next;
};

struct Class
{
	string class_id;
	string head_teacher;
	StudentNode* student_list = nullptr;
};

struct ClassNode
{
	Class my_class;
	ClassNode* next;
};

struct Session
{
	int day_of_the_week;
	int session_no;
};

struct Score
{
	float process;
	float mid;
	float fin;
	float overall;
};

struct Course
{
	string course_id;
	string course_name;
	string teacher_name;
	int num_credit;
	int max_students = 50;
	Session teaching_session[2];
};

struct MyCourse
{
	Score score;
	string subject_code;
	CourseNode* course;
	MyCourse* next;
	//MyCourse(CourseNode& a) :
	//	course(&a),
	//	subject_code(""),
	//	next(nullptr) {};
};

struct CourseNode
{
	int semester_id;
	int year;
	Course course;
	StudentNode* student_list;
	CourseNode* next;
};

struct Semester
{
	string semester_id;
	CourseNode* course_list;
};

struct SemesterNode
{
	Semester sem;
	SemesterNode* next;
};

struct Year
{
	string year_id;
	ClassNode* list_class;
	SemesterNode* list_sem;
};

struct YearNode
{
	Year school_year;
	YearNode* next;
};