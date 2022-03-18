#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <math.h>
#include <sstream>

using namespace std;

struct Student
{
    int num;
    string student_id;
    string first_name;
    string last_name;
    bool gender;
    string dob;
    string social_id;
    string password;
    string student_class;
    MyCourse *my_course;
};

struct StudentNode
{
    Student student;
    StudentNode *next;
};

struct Class
{
    string class_id;
    string head_teacher;
    StudentNode *student_list;
};

struct Session
{
    int day_of_the_week; //1-sun, 2-mon
    int session_no;
};

struct Course
{
    string course_id;
    string course_name;
    string teacher_name;
    int num_credit;
    int max_students = 50;
    Session teaching_session[2];
    StudentNode *student_list;
};

struct CourseNode
{
    int semester_id;
    int year;
    Course course;
    CourseNode *next;
};

struct MyCourse
{
    CourseNode *course;
    MyCourse *next;
};