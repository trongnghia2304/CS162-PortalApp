#pragma once
#include "struct_and_dependencies.h"

// -- TO DO --
//--------------------------------- Year & YearList ----------------------------------------------
//--------------------------------------------------------------------------------------------------
Year createYear(string p_Year_id, string p_head_teacher);
YearNode* initYearNode(Year p_new_Year);
YearNode* searchYearNode(YearNode* p_head, string p_Year_id);
void appendNewYearNode(YearNode** p_head, Year p_new_Year);
void pushNewYearNode(YearNode** p_head, Year p_new_Year);
void removeYearNode(YearNode** p_head, string p_Year_id);
//--------------------------------------------------------------------------------------------------

//--------------------------------- Class & ClassList ----------------------------------------------
//--------------------------------------------------------------------------------------------------
Class createClass(string p_class_id, string p_head_teacher);
ClassNode* initClassNode(Class p_new_class);
ClassNode* searchClassNode(ClassNode* p_head, string p_class_id);
void appendNewClassNode(ClassNode** p_head, Class p_new_class);
void pushNewClassNode(ClassNode** p_head, Class p_new_class);
void removeClassNode(ClassNode** p_head, string p_class_id);
//--------------------------------------------------------------------------------------------------

//------------------------------- Course & CourseList ----------------------------------------------
//--------------------------------------------------------------------------------------------------
Course createCourse(string p_course_id, string p_course_name, string p_teacher_name, int p_num_credit, int p_max_students, int p_day1, int p_sess1, int p_day2, int p_sess2);
void printCourse(Course p_course);
CourseNode* initCourseNode(Course p_new_course);
CourseNode* searchCourseNode(CourseNode* p_head, string p_id);
void appendNewCourseNode(CourseNode** p_head, Course p_new_course);
void pushNewCourseNode(CourseNode** p_head, Course p_new_course);
void removeCourseNode(CourseNode** p_head, string p_course_id);
void readFromFileCourseNode(string p_course_file_path, CourseNode** p_head);
void writeToFileCourseNode(string p_course_file_path, CourseNode* p_head);
void updateCourseInfo(CourseNode** p_head, string p_course_id, string p_course_name, string p_teacher_name);
void deleteCourseNode(CourseNode*& head);
void printCourseNode(CourseNode* p_head); // Used for checking outputs <----- can omit
//--------------------------------------------------------------------------------------------------

//----------------------------- Semester & SemesterList --------------------------------------------
//--------------------------------------------------------------------------------------------------
Semester createSemester(string p_semester_id);
SemesterNode* initSemesterNode(Semester p_new_semester);
SemesterNode* searchSemesterNode(SemesterNode* p_head, string p_semester_id);
void appendNewSemesterNode(SemesterNode** p_head, Semester p_new_semester);
void pushNewSemesterNode(SemesterNode** p_head, Semester p_new_semester);
void removeSemesterNode(SemesterNode** p_head, string p_semester_id);
//--------------------------------------------------------------------------------------------------

//----------------------------- Student & StudentList --------------------------------------------
//--------------------------------------------------------------------------------------------------
Student createStudent(int p_num, string p_student_id, string p_first_name, string p_last_name, bool p_gender, string p_dob, string p_social_id);
StudentNode* initStudentNode(Student p_new_student);
StudentNode* searchStudentNode(StudentNode* p_head, string p_student_id);
void appendNewStudentNode(StudentNode** p_head, Student p_new_student);
void pushNewStudentNode(StudentNode** p_head, Student p_new_student);
void removeStudentNode(StudentNode** p_head, string p_student_id);
void readFromFileStudentNode(string p_student_file_path, StudentNode** p_head);
void writeToFileStudentNode(string p_student_file_path, StudentNode* p_head);
int countStudentNode(StudentNode* p_head);
void deleteStudentList(StudentNode*& p_head);
void printStudent(Student p_student);
void printStudentNode(StudentNode* p_head);
//--------------------------------------------------------------------------------------------------

//--------------------------------------- Views  ---------------------------------------------------
//--------------------------------------------------------------------------------------------------
void changePassword(Student& me);
void changeStudent(Student& me);
void checkMyCourse(Student me);
void subscribeCourse(Student& me, CourseNode& a);
void unsubscribeCourse(Student& me, CourseNode& a);
void timeTable(Student me);
int tuitionFee(Student me);
void viewScore(Student me);
void viewListOfClass(ClassNode* Class_head);
//--------------------------------------------------------------------------------------------------
