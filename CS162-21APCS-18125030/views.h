#pragma once
#include "header.h"

struct Object
{
	Sprite draw;
	Texture txt;
	FloatRect bound;
};

struct Info
{
	Font font;
	Text text;
	FloatRect bound;
	bool check = false;
	string s = "";
};

//-------------------Objects/Text to draw-----------------

Object createObject(string s, float x, float y);
Object *createObjectTest(string s, float x, float y);
Object createObject(string s);
Object *createObjectTest(string s);
Info createInfo(string s, float x, float y, float size);
Info createInfo(string s, string info, float x, float y, float size);
Info *createInfoTest(string s, string info, float x, float y, float size);

//--------------------Scenes---------------------------

void Scene1(RenderWindow &window, int &page, bool &role, const float &scale);
void logIn(RenderWindow &window, int &page, bool role, const float &scale, ClassNode *class_list, StudentNode *staff_list, StudentNode *&user);
void studentHome(RegistrationSession data, RenderWindow &window, int &page, const float &scale);
void staffHome(RenderWindow &window, int &page, const float &scale);
void profile(RenderWindow &window, int &page, const float &scale, StudentNode *student, bool is_staff);
void view_class(const string &year, const string &semester, string cur_class, string cur_teacher, RenderWindow &window, int &page, const float &scale, ClassNode *class_list, StudentNode *user, const bool &is_staff);
void view_class_score(const string &year, const string &semester, string cur_class, string cur_teacher, RenderWindow &window, int &page, const float &scale, ClassNode *class_list, StudentNode *user, const bool &is_staff);
void view_class(RenderWindow &window, int &page, const float &scale, ClassNode *class_list, StudentNode *user, const bool &is_staff);
void course_student(int k, RenderWindow &window, int &page, const float &scale, CourseNode *course);
void course_student2(RenderWindow &window, int &page, const float &scale, CourseNode *course, ClassNode *all_class);
void view_year(RenderWindow &window, int &page, const float &scale, YearNode *year, StudentNode *user, const bool &is_staff, ClassNode *all_class);
void view_semester(RenderWindow &window, int &page, const float &scale, YearNode *cur_year, StudentNode *user, const bool &is_staff, ClassNode *all_class);
void view_course(RenderWindow &window, int &page, const float &scale, CourseNode *&my_course, const bool &is_staff, ClassNode *all_class, const string &year, const string &sem);
void view_course(RenderWindow &window, int &page, const float &scale, StudentNode *user, const bool &is_staff, const string &sem, const string &year);
void view_score(RenderWindow &window, int &page, const float &scale, StudentNode *user, const bool &is_staff);
void view_score2(RenderWindow &window, int &page, const float &scale, StudentNode *user, const bool &is_staff);
void view_class_list(const string& year, const string& semester, RenderWindow &window, int &page, const float &scale, ClassNode *&class_list, bool &is_staff);
bool change_course_info(RenderWindow &window, int &page, const float &scale, CourseNode *&course, const string &year, const string &sem);
bool add_new_course(RenderWindow &window, int &page, const float &scale, CourseNode *&course, const string &year, const string &sem);
void view_registration_staff(YearNode *school, RenderWindow &window, int &page, const float &scale, RegistrationSession &data, const bool &is_staff);
void view_registration_student(YearNode *school, RenderWindow &window, int &page, const float &scale, RegistrationSession data, const bool &is_staff, StudentNode *user);
int student_profile(RenderWindow &window, int &page, const float &scale, StudentNode *&student, bool is_staff, bool is_new, string cur_class);
//-----------------Other features--------------------------

bool isHere(FloatRect &bound, Vector2f &mouse);
bool drawWhich(RenderWindow &window, Object a, Object b, Vector2f &mouse);
bool drawWhich(RenderWindow &window, Object *a, Object *b, Vector2f &mouse);
bool switchPage(FloatRect &bound, Vector2f &mouse, int k, int &page);
void changePos(Object *a, Object *b, float x, float y);
void changePos(Object *a, float x, float y);
void changePos(Info *a, float x, float y);
void texting(Info &text, Uint32 unicode, unsigned int limit);
void texting(Info *&text, Uint32 unicode, unsigned int limit);
bool checkWeekday(string s, int &x);
bool checkSession(string s, int &x);
bool checkInputCourse(Info *inf[], int n, CourseNode *&course);
bool checkInputCourse_change(Info *inf[], int n, CourseNode *&course);
void deleteEvent_course(CourseNode *&list_course, CourseNode *course, ClassNode *list_class);
void deleteEvent_student(StudentNode *&list_student, StudentNode *me);
void deleteEvent_class(ClassNode *&list_class, ClassNode *my_class);
bool checkDOB(string s);
bool checkID(string s);
void checkPos(float& x, float& y, int day, int no, const float& scale);
