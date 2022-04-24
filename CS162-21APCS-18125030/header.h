#pragma once
#include "struct_and_dependencies.h"

// -- TO DO --
//--------------------------------- Year & YearList ----------------------------------------------
//--------------------------------------------------------------------------------------------------
Year createYear(string p_year_id);
YearNode *initYearNode(Year p_new_year);
void appendNewYearNode(YearNode **p_head, Year p_new_year);
void pushNewYearNode(YearNode *&p_head, Year p_new_year);
YearNode *searchYearNode(YearNode *p_head, string find_year_id);
void removeYearNode(YearNode *&p_head, string p_Year_id);
void deleteYearNode(YearNode *&p_head);
void readFromFileYearNode(string p_year_file_path, YearNode **p_head);
void writeToFileYearNode(string p_year_file_path, YearNode *p_head);
//--------------------------------------------------------------------------------------------------

//--------------------------------- Class & ClassList ----------------------------------------------
//--------------------------------------------------------------------------------------------------
Class createClass(string p_class_id, string p_head_teacher);
ClassNode *initClassNode(Class p_new_class);
ClassNode *searchClassNode(ClassNode *p_head, string p_class_id);
void appendNewClassNode(ClassNode *&p_head, Class p_new_class);
void pushNewClassNode(ClassNode *&p_head, Class p_new_class);
void removeClassNode(ClassNode **p_head, string p_class_id);
void addStudentToClass(ClassNode *&p_head_class, StudentNode *p_head_student);
void deleteClassNode(ClassNode *&p_head);
void readFromFileClassNode(string p_class_file_path, ClassNode *&p_head);
void writeToFileClassNode(string p_class_file_path, ClassNode *p_head);
void readFromFileClassNode1(string p_class_file_path, ClassNode *&p_head);
void writeToFileClassNode1(string p_class_file_path, ClassNode *p_head);

//--------------------------------------------------------------------------------------------------

//------------------------------- Course & CourseList ----------------------------------------------
//--------------------------------------------------------------------------------------------------
Course createCourse(string p_course_id, string p_course_name, string p_teacher_name, int p_num_credit, int p_max_students, int p_day1, int p_sess1, int p_day2, int p_sess2);
void printCourse(Course p_course);
CourseNode *initCourseNode(Course p_new_course);
CourseNode *searchCourseNode(CourseNode *p_head, string p_id);
void appendNewCourseNode(CourseNode **p_head, Course p_new_course);
void appendNewCourseNode(CourseNode **p_head, Course p_new_course, const string &sem, const string &year, StudentNode *students);
void pushNewCourseNode(CourseNode **p_head, Course p_new_course);
void removeCourseNode(CourseNode **p_head, string p_course_id);
void readFromFileCourseNode(string p_course_file_path, CourseNode **p_head);
void writeToFileCourseNode(string p_course_file_path, CourseNode *p_head);
void readFromFileCourseNode(ifstream &openFile, CourseNode **p_head);
void writeToFileCourseNode(ofstream &openFile, CourseNode *p_head);
void updateCourseInfo(CourseNode **p_head, string p_course_id, string p_course_name, string p_teacher_name);
void deleteCourseNode(CourseNode *&head);
void readFromFileCourseNode(ifstream &openFile, CourseNode **p_head);
void writeToFileCourseNode(ofstream &openFile, CourseNode *p_head);
bool checkCourseWithMyCourse(Course a, CourseNode *course_list);
bool checkCourseCollision(Course a, Course b);
void printCourseNode(CourseNode *p_head); // Used for checking outputs <----- can omit
string day_convert(Session a);
string no_convert(Session a);
string session_convert(Session a);
//--------------------------------------------------------------------------------------------------

//----------------------------- Semester & SemesterList --------------------------------------------
//--------------------------------------------------------------------------------------------------
Semester createSemester(string p_semester_id);
SemesterNode *initSemesterNode(Semester p_new_semester);
SemesterNode *searchSemesterNode(SemesterNode *p_head, string p_semester_id);
void appendNewSemesterNode(SemesterNode **p_head, Semester p_new_semester);
void pushNewSemesterNode(SemesterNode **p_head, Semester p_new_semester);
void readFromFileSemesterNode(ifstream &openFile, SemesterNode **p_head);
void writeToFileSemesterNode(ofstream &openFile, SemesterNode *p_head);
void removeSemesterNode(SemesterNode **p_head, string p_semester_id);
void deleteSemesterNode(SemesterNode *&p_head);
//--------------------------------------------------------------------------------------------------

//----------------------------- Student & StudentList --------------------------------------------
//--------------------------------------------------------------------------------------------------
Student createStudent(int p_num, string p_student_id, string p_first_name, string p_last_name, bool p_gender, string p_dob, string p_social_id, string p_password, string p_class);
StudentNode *initStudentNode(Student p_new_student);
StudentNode *searchStudentNode(StudentNode *p_head, string p_student_id);
void appendNewStudentNode(StudentNode **p_head, Student p_new_student);
void pushNewStudentNode(StudentNode **p_head, Student p_new_student);
void removeStudentNode(StudentNode **p_head, string p_student_id);
void readFromFileStudentNode(string p_student_file_path, StudentNode **p_head);
void readFromFileStudentNode(ifstream &openFile, StudentNode **p_head);
void readFromFileStudentNode1(ifstream &openFile, StudentNode **p_head);
void writeToFileStudentNode(string p_student_file_path, StudentNode *p_head);
void writeToFileStudentNode(ofstream &openFile, StudentNode *p_head);
void writeToFileStudentNode1(ofstream &openFile, StudentNode *p_head);
int countStudentNode(StudentNode *p_head);
void deleteStudentList(StudentNode *&p_head);
void printStudent(Student p_student);
void printStudentNode(StudentNode *p_head);
MyCourse *searchMyCourse(StudentNode *p_student, CourseNode *course);
void setupMyCourses(ClassNode *p_class, YearNode *year);
void findMyCourses(StudentNode **p_student, YearNode *year);
void removeMyCourses(StudentNode *p_head, CourseNode *course);
void deleteMyCourse(MyCourse *&p_head);
void appendNewMyCourse(StudentNode *me, MyCourse* new_course);
MyCourse *createMyCourse(CourseNode *course);
//--------------------------------------------------------------------------------------------------

//--------------------------------------- Views  ---------------------------------------------------
//--------------------------------------------------------------------------------------------------
bool changePassword(Student &me, const string &oldPw, const string &newPw);
float calculateOverallScore(MyCourse *course, float midterm_percent, float final_percent);
float calculateGPA(Student me, string year, string sem);
float calculateGPA(Student me);
StudentNode* copyForCourse(StudentNode* me, int k);
void importCSVFile(ifstream open_file, StudentNode* student_list, string subject_code);
void view_schedule(YearNode* school, RenderWindow& window, int& page, const float& scale, RegistrationSession& data, StudentNode* user);
// void changeStudent(Student& me);
// void checkMyCourse(Student me);
// void subscribeCourse(Student& me, CourseNode& a);
// void unsubscribeCourse(Student& me, CourseNode& a);
// void timeTable(Student me);
// int tuitionFee(Student me);
// void viewScore(Student me);
// void viewListOfClass(ClassNode* Class_head);
// bool checkLogin(StudentNode* p_head, string username, string password);
//--------------------------------------------------------------------------------------------------

//----------------------Registration---------------------------
string getCurrentDate();
string *splitDate(string str, char seperator);
//< = > (-1 0 1)
int compareDate(string date_1, string date_2);
void readFromFileRegSess(string filepath, RegistrationSession &new_session);
void writeToFileRegSess(string filepath, RegistrationSession new_session);
