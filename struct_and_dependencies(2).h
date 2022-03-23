#pragma once
#include "struct_and_dependencies.h"

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
    string display_name;
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

struct ClassNode
{
    Class my_class;
    ClassNode* next;
};

struct Session
{
    int day_of_the_week; //1-sun, 2-mon
    int session_no;
};

struct Score
{
    int process;
    int mid;
    int fin;
};

struct Course
{
    string course_id;
    string course_name;
    string teacher_name;
    int num_credit;
    int max_students = 50;
    Session teaching_session[2];
    Session exam_session[2];
    StudentNode *student_list;
    Score score;
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
    MyCourse(CourseNode &a) : course(&a), next(nullptr) {};
};

struct Semester
{
    string semester_id;
    CourseNode *course_list;
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
    SemesterNode *list_sem;
};

struct YearNode
{
    Year school_year;
    YearNode* next;
};