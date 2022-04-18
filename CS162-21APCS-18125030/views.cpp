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
