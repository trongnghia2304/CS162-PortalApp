#include "views.h"

Object createObject(string s, float x, float y)
{
	Object me;
	me.txt.loadFromFile(s);
	me.draw.setTexture(me.txt);
	me.draw.setPosition(x, y);
	me.bound = me.draw.getGlobalBounds();
	return me;
}

Object *createObjectTest(string s, float x, float y)
{
	Object *me = new Object;
	me->txt.loadFromFile(s);
	me->draw.setTexture(me->txt);
	me->draw.setPosition(x, y);
	me->bound = me->draw.getGlobalBounds();
	return me;
}

Object createObject(string s)
{
	Object me;
	me.txt.loadFromFile(s);
	me.draw.setTexture(me.txt);
	me.bound = me.draw.getGlobalBounds();
	return me;
}

Object *createObjectTest(string s)
{
	Object *me = new Object;
	me->txt.loadFromFile(s);
	me->draw.setTexture(me->txt);
	me->bound = me->draw.getGlobalBounds();
	return me;
}

bool isHere(FloatRect &bound, Vector2f &mouse)
{
	return bound.contains(mouse);
}

Info createInfo(string s, float x, float y, float size)
{
	Info a;
	a.font.loadFromFile(s);
	a.text.setFont(a.font);
	a.text.setCharacterSize(size);
	a.text.setPosition(x, y);
	a.text.setFillColor(Color(46, 68, 112, 255));
	a.bound = a.text.getGlobalBounds();
	return a;
}

Info createInfo(string s, string info, float x, float y, float size)
{
	Info a;
	a.font.loadFromFile(s);
	a.text.setFont(a.font);
	a.text.setCharacterSize(size);
	a.text.setPosition(x, y);
	a.text.setFillColor(Color(46, 68, 112, 255));
	a.text.setString(info);
	a.bound = a.text.getGlobalBounds();
	return a;
}

Info *createInfoTest(string s, string info, float x, float y, float size)
{
	Info *a = new Info;
	a->font.loadFromFile(s);
	a->text.setFont(a->font);
	a->text.setCharacterSize(size);
	a->text.setPosition(x, y);
	a->text.setFillColor(Color(46, 68, 112, 255));
	a->text.setString(info);
	a->bound = a->text.getGlobalBounds();
	return a;
}

bool drawWhich(RenderWindow &window, Object a, Object b, Vector2f &mouse)
{
	if (isHere(a.bound, mouse))
	{
		window.draw(a.draw);
		return true;
	}
	window.draw(b.draw);
	return false;
}

bool drawWhich(RenderWindow &window, Object *a, Object *b, Vector2f &mouse)
{
	if (isHere(a->bound, mouse))
	{
		window.draw(a->draw);
		return true;
	}
	window.draw(b->draw);
	return false;
}

bool switchPage(FloatRect &bound, Vector2f &mouse, int k, int &page)
{
	if (isHere(bound, mouse))
	{
		page = k;
		return true;
	}
	return false;
}

void changePos(Object *a, Object *b, float x, float y)
{
	a->draw.setPosition(x, y);
	a->bound = a->draw.getGlobalBounds();
	b->draw.setPosition(x, y);
	b->bound = b->draw.getGlobalBounds();
}

void changePos(Object *a, float x, float y)
{
	a->draw.setPosition(x, y);
	a->bound = a->draw.getGlobalBounds();
}

void changePos(Info *a, float x, float y)
{
	a->text.setPosition(x, y);
	a->bound = a->text.getGlobalBounds();
}

void texting(Info &text, Uint32 unicode, unsigned int limit)
{
	if (text.check && (text.s.size() < limit || unicode == 8))
	{
		if (unicode == 8)
		{
			if (!text.s.empty())
				text.s.pop_back();
		}
		else
		{
			text.s += unicode;
		}
		text.text.setString(text.s);
	}
}

void texting(Info *&text, Uint32 unicode, unsigned int limit)
{
	if (text->check && (text->s.size() < limit || unicode == 8))
	{
		if (unicode == 8)
		{
			if (!text->s.empty())
				text->s.pop_back();
		}
		else
		{
			text->s += unicode;
		}
		text->text.setString(text->s);
	}
}

bool changePassword(Student &me, const string &oldPw, const string &newPw)
{
	if (oldPw == me.password)
	{
		me.password = newPw;
		return true;
	}
	else
		return false;
}

// percent ex. : 20, 30 (%)
float calculateOverallScore(MyCourse *course, float midterm_percent, float final_percent)
{
	course->score.overall = (midterm_percent * course->score.mid + final_percent * course->score.fin + (100 - midterm_percent - final_percent) * course->score.process) / 100;
	return course->score.overall;
}

float calculateGPA(Student me, string year, string sem)
{
	float res = 0, k = 0;
	for (MyCourse *cur = me.my_course; cur; cur = cur->next)
	{
		if (cur->year == year && cur->sem == sem)
		{
			k++;
			res += cur->score.overall;
		}
	}
	if (k == 0)
		return 0;
	else
		return res / k;
}

float calculateGPA(Student me)
{
	float res = 0, k = 0;
	for (MyCourse *cur = me.my_course; cur; cur = cur->next)
	{
		k++;
		res += cur->score.overall;
	}
	return (k == 0 ? 0 : res / k);
}

bool checkInputCourse(Info *inf[], int n, CourseNode *&course)
{
	// id, name, name, num, stu, s1, s2, d1, d2
	int num = 0, stu = 0, d1, d2, s1, s2;
	if (!checkWeekday(inf[4]->s, d1) || !checkWeekday(inf[5]->s, d2))
		return false;
	if (!checkSession(inf[7]->s, s1) || !checkSession(inf[8]->s, s2))
		return false;
	stringstream num_check(inf[3]->s), stu_check(inf[6]->s);
	num_check >> num;
	stu_check >> stu;
	if (!num || !stu)
		return false;
	Course new_course = createCourse(inf[0]->s, inf[1]->s, inf[2]->s, num, stu, d1, s1, d2, s2);
	appendNewCourseNode(&course, new_course);
	return true;
}

bool checkInputCourse_change(Info *inf[], int n, CourseNode *&course)
{
	// id, name, name, num, stu, s1, s2, d1, d2
	int num = 0, stu = 0, d1, d2, s1, s2;
	if (!checkWeekday(inf[4]->s, d1) || !checkWeekday(inf[5]->s, d2))
		return false;
	if (!checkSession(inf[7]->s, s1) || !checkSession(inf[8]->s, s2))
		return false;
	stringstream num_check(inf[3]->s), stu_check(inf[6]->s);
	num_check >> num;
	stu_check >> stu;
	if (!num || !stu)
		return false;
	course->course.course_id = inf[0]->s;
	course->course.course_name = inf[1]->s;
	course->course.teacher_name = inf[2]->s;
	course->course.num_credit = num;
	course->course.max_students = stu;
	course->course.teaching_session[0].day_of_the_week = d1;
	course->course.teaching_session[0].session_no = s1;
	course->course.teaching_session[1].day_of_the_week = d2;
	course->course.teaching_session[1].session_no = d2;
	return true;
}

bool checkSession(string s, int &x)
{
	if (s.size() < 2 || !(s[0] == 's' || s[0] == 'S') || s[1] < '0' || s[1] > '9')
	{
		return false;
	}
	x = int(s[1] - '0');
	return true;
}

bool checkWeekday(string s, int &x)
{
	for (int i = 0; i < s.size(); i++)
	{
		s[i] = toupper(s[i]);
	}
	if (s == "MON")
		x = 2;
	else if (s == "TUE")
		x = 3;
	else if (s == "WED")
		x = 4;
	else if (s == "THU")
		x = 5;
	else if (s == "FRI")
		x = 6;
	else if (s == "SAT")
		x = 7;
	else if (s == "SUN")
		x = 8;
	else
		return false;
	return true;
}

void deleteEvent_course(CourseNode *&list_course, CourseNode *course, ClassNode *list_class)
{
	string id = course->course.course_id;
	for (StudentNode *cur = course->student_list; cur; cur = cur->next)
	{
		ClassNode *cur_class = searchClassNode(list_class, cur->student.student_class);
		StudentNode *stu = searchStudentNode(cur_class->my_class.student_list, cur->student.student_id);
		removeMyCourses(stu, course);
	}
	removeCourseNode(&list_course, id);
}
void deleteEvent_student(StudentNode *&list_student, StudentNode *me)
{
	string id = me->student.student_id;
	for (MyCourse *cur = me->student.my_course; cur; cur = cur->next)
	{
		removeStudentNode(&cur->course->student_list, id);
	}
	removeStudentNode(&list_student, id);
}

void deleteEvent_class(ClassNode *&list_class, ClassNode *my_class)
{
	StudentNode *cur = my_class->my_class.student_list, *pre = nullptr;
	while (cur)
	{
		pre = cur;
		cur = cur->next;
		deleteEvent_student(my_class->my_class.student_list, pre);
	}
	removeClassNode(&list_class, my_class->my_class.class_id);
}

StudentNode *copyForCourse(StudentNode *me, int k)
{
	StudentNode *new_stu = new StudentNode;
	new_stu->student = createStudent(k, me->student.student_id, me->student.first_name, me->student.last_name, me->student.gender, me->student.dob, me->student.social_id, "", me->student.student_class);
	new_stu->next = nullptr;
	return new_stu;
}

void importCSVFile(ifstream open_file, StudentNode* student_list, string subject_code)
{
	string line, word[9];
	while (getline(open_file, line))
	{
		stringstream ss(line);
		for (int i = 0; i < 9; i++)
		{
			getline(ss, word[i], ',');
		}
		StudentNode* temp = searchStudentNode(student_list, word[1]);
		MyCourse* cur = temp->student.my_course;
		
		while (cur && cur->subject_code != subject_code)
			cur = cur->next;
		
		istringstream(word[3]) >> cur->score.process;
		istringstream(word[4]) >> cur->score.mid;
		istringstream(word[5]) >> cur->score.fin;
		istringstream(word[6]) >> cur->score.overall;
	}
}

string session_convert(Session a)
{
	string s = day_convert(a) + "-" + no_convert(a);
	return s;
}

bool checkDOB(string s)
{
	stringstream check(s);
	int day = 0, mon = 0, year = 0;
	char c1, c2;
	check >> day >> c1 >> mon >> c2 >> year;
	if (!(day & mon & year)) return false;
	if (day < 32 && day > 0 && mon > 0 && mon < 13) return true;
	else return false;
}

bool checkID(string s)
{
	stringstream check(s);
	int id;
	check >> id;
	return to_string(id) == s;
}

// //--------------------------------------- Views ----------------------------------------------------
// //--------------------------------------------------------------------------------------------------
// void viewListOfClass(ClassNode *Class_head)
// {
//     ClassNode *pClass = Class_head;
//     while (pClass != NULL)
//     {
//         cout << pClass->my_class.class_id << " " << pClass->my_class.head_teacher;
//         pClass = pClass->next;
//     }
// }
// void checkMyCourse(Student me)
// {
//     cout << "Pick a year: ";
//     int year;
//     cin >> year;
//     cout << "Pick a semester: ";
//     int sem;
//     cin >> sem;
//     cout << "id, course, teacher, credit, timetable";

//     while (me.my_course->course->year != year && me.my_course->course->semester_id != sem)
//         me.my_course = me.my_course->next;

//     for (MyCourse *cur = me.my_course; cur && cur->course->semester_id == sem; cur = cur->next)
//     {
//         cout << cur->course->course.course_id << "  " << cur->course->course.course_name << "  " << cur->course->course.teacher_name << "  " << cur->course->course.num_credit << "  ";
//         for (int i = 0; i < 2; i++)
//         {
//             switch (cur->course->course.teaching_session[i].day_of_the_week)
//             {
//             case 1:
//                 cout << "Sun";
//                 break;
//             case 2:
//                 cout << "Mon";
//                 break;
//             case 3:
//                 cout << "Tue";
//                 break;
//             case 4:
//                 cout << "Wed";
//                 break;
//             case 5:
//                 cout << "Thu";
//                 break;
//             case 6:
//                 cout << "Fri";
//                 break;
//             default:
//                 cout << "Sat";
//                 break;
//             }
//             cout << "-" << cur->course->course.teaching_session[i].session_no << "  ";
//         }
//         cout << endl;
//     }
// }
// void subscribeCourse(Student &me, CourseNode &a)
// {
//     // subscribe in student's my_course
//     MyCourse *cur = me.my_course, *pre = new MyCourse(a);
//     if (cur)
//     {
//         while (cur->next)
//             cur = cur->next;
//         cur->next = pre;
//     }
//     else
//     {
//         me.my_course = pre;
//     }
//     // add student to the course's list
//     appendNewStudentNode(&a.course.student_list, me);
// }
// void unsubscribeCourse(Student &me, CourseNode &a)
// {
//     // unsubscribe in student's my_course
//     if (me.my_course->course == &a)
//         me.my_course->course = me.my_course->course->next;
//     else
//     {
//         MyCourse *cur = me.my_course;
//         while (cur->next->course != &a)
//             cur = cur->next;
//         MyCourse *a = cur->next;
//         cur = cur->next->next;
//         delete a;
//     }
//     // delete the student from the course list
//     removeStudentNode(&a.course.student_list, me.student_id);
// }
// void timeTable(Student me)
// {

//     cout << "id, course, teacher, credit, timetable \n";
//     Student you = me;
//     while (you.my_course->course->next != nullptr)
//         you.my_course = you.my_course->next;
//     int sem = you.my_course->course->semester_id;
//     int year = you.my_course->course->year;

//     while (me.my_course->course->year != year && me.my_course->course->semester_id != sem)
//         me.my_course = me.my_course->next;
//     for (MyCourse *cur = me.my_course; cur && cur->course->semester_id == sem; cur = cur->next)
//     {
//         cout << cur->course->course.course_id << "  " << cur->course->course.course_name << "  " << cur->course->course.teacher_name << "  " << cur->course->course.num_credit << "  ";
//         for (int i = 0; i < 2; i++)
//         {
//             switch (cur->course->course.teaching_session[i].day_of_the_week)
//             {
//             case 1:
//                 cout << "Sun";
//                 break;
//             case 2:
//                 cout << "Mon";
//                 break;
//             case 3:
//                 cout << "Tue";
//                 break;
//             case 4:
//                 cout << "Wed";
//                 break;
//             case 5:
//                 cout << "Thu";
//                 break;
//             case 6:
//                 cout << "Fri";
//                 break;
//             default:
//                 cout << "Sat";
//                 break;
//             }
//             cout << "-" << cur->course->course.teaching_session[i].session_no << "  ";
//         }
//         cout << endl;
//     }
// }
// int tuitionFee(Student me)
// {
//     cout << "Pick a year: ";
//     int year;
//     cin >> year;
//     cout << "Pick a semester: ";
//     int sem;
//     cin >> sem;

//     int sum = 0;
//     while (me.my_course->course->year != year && me.my_course->course->semester_id != sem)
//         me.my_course = me.my_course->next;
//     for (MyCourse *cur = me.my_course; cur && cur->course->semester_id == sem; cur = cur->next)
//     {
//         sum += cur->course->course.num_credit;
//     }

//     sum = sum * 500000;

//     return sum;
// }
// void viewScore(Student me)
// {
//     cout << "Pick a year: ";
//     int year;
//     cin >> year;
//     cout << "Pick a semester: ";
//     int sem;
//     cin >> sem;
//     cout << "id, course, process score, midterm score, final score: \n";
//     while (me.my_course->course->year != year && me.my_course->course->semester_id != sem)
//         me.my_course = me.my_course->next;
//     for (MyCourse *cur = me.my_course; cur && cur->course->semester_id == sem; cur = cur->next)
//     {
//         cout << cur->course->course.course_id << "  " << cur->course->course.course_name << "  " << cur->course->course.score.process << "  " << cur->course->course.score.mid << "  " << cur->course->course.score.fin;
//     }
//     cout << endl;
// }

// bool checkLogin(StudentNode *p_head, string username, string password)
// {
//     StudentNode *founded_student = searchStudentNode(pHead, username);
//     if(founded_student == nullptr)
//     {
//         cout << "Wrong username";
//         return false;
//     }
//     if(founded_student.student.password != password)
//     {
//         cout << "Wrong password";
//         return false;
//     }
//     return true;

// }
// //--------------------------------------------------------------------------------------------------
