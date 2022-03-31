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

Object* createObjectTest(string s, float x, float y)
{
	Object* me = new Object;
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

bool isHere(FloatRect& bound, Vector2f& mouse)
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

void Scene1(RenderWindow& window, int& page, bool& role, const float& scale)
{
	Object screen = createObject("content/First.png");
	Object o1 = createObject("content/Staff1.png", 180.0f * scale, 300.0f * scale);
	Object a1 = createObject("content/Staff2.png", 180.0f * scale, 300.0f * scale);
	Object o2 = createObject("content/Student1.png", 540.0f * scale, 300.0f * scale);
	Object a2 = createObject("content/Student2.png", 540.0f * scale, 300.0f * scale);

	Event event;

	while (window.isOpen() && page == 1)
	{
		Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case Event::Closed: {
					window.close();
					break;
				}
				case Event::MouseButtonReleased: {
					if (event.mouseButton.button == Mouse::Left)
					{
						if (isHere(o1.bound, mouse))
						{
							role = true;
							page = 2;
						}
						else if (isHere(o2.bound, mouse))
						{
							role = false;
							page = 2;
						}
					}
					break;
				}
				default:
					break;
			}
		}

		window.clear();
		window.draw(screen.draw);
		if (isHere(o1.bound, mouse))
		{
			window.draw(o2.draw);
			window.draw(a1.draw);
		}
		else if (isHere(o2.bound, mouse))
		{
			window.draw(o1.draw);
			window.draw(a2.draw);
		}
		else
		{
			window.draw(o1.draw);
			window.draw(o2.draw);
		}
		window.display();
	}
}

void logIn(RenderWindow& window, int& page, bool role, const float& scale)
{
	Event event;
	bool see = false, entered = false, change = false;
	Object screen = createObject("content/Log in.png");
	Object l1 = createObject("content/Login1.png", 400.0f * scale, 515.0f * scale);
	Object l2 = createObject("content/Login.png", 400.0f * scale, 515.0f * scale);
	Object eye = createObject("content/eye.png", 640.0f * scale, 450.0f * scale);
	Object close = createObject("content/closedeye.png", 640.0f * scale, 450.0f * scale);
	Info username = createInfo("content/Oswald-Light.ttf", "sample_text", 430.0f * scale, 380.0f * scale, 26.25f * scale);
	Info pw = createInfo("content/Oswald-Light.ttf", "12345678", 430.0f * scale, 447.0f * scale, 26.25f * scale);
	Info pw2 = createInfo("content/Oswald-Light.ttf", "********", 430.0f * scale, 450.0f * scale, 26.25f * scale);
	Info wrong = createInfo("content/Oswald-Light.ttf", "Wrong username/password, please try again!", 355.0f * scale, 497.5f * scale, 20.0f * scale);
	wrong.text.setFillColor(Color(118, 36, 2, 255));
	while (window.isOpen() && page == 2)
	{
		Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case Event::Closed: {
					window.close();
					break;
				}
				case Event::MouseButtonReleased: {
					if (event.mouseButton.button == Mouse::Left)
					{
						if (isHere(l1.bound, mouse))
						{
							change = true;
						}
						else if (isHere(eye.bound, mouse))
						{
							see = !see;
						}

						if (isHere(username.bound, mouse))
						{
							username.check = true;
							pw.check = false;
						}
						else if (isHere(pw.bound, mouse))
						{
							pw.check = true;
							username.check = false;
						}
						else
						{
							pw.check = false;
							username.check = false;
						}
					}

					break;
				}
				case Event::KeyReleased: {
					if (event.key.code == 58)
					{
						entered = true;
						change = true;
					}
					break;
				}
				case Event::TextEntered: {
					if (username.check && (username.s.size() < 15 || event.text.unicode == 8))
					{
						if (event.text.unicode == 8)
						{
							if (!username.s.empty())
								username.s.pop_back();
						}
						else
						{
							username.s += event.text.unicode;
						}
						username.text.setString(username.s);
					}

					if (pw.check && (pw.s.size() < 10 || event.text.unicode == 8))
					{
						if (event.text.unicode == 8)
						{
							if (!pw.s.empty())
							{
								pw.s.pop_back();
								pw2.s.pop_back();
							}
						}
						else
						{
							pw.s += event.text.unicode;
							pw2.s += "*";
						}
						pw.text.setString(pw.s);
						pw2.text.setString(pw2.s);
					}
					break;
				}
				default:
					break;
			}
		}

		window.clear();
		window.draw(screen.draw);
		window.draw(username.text);
		if (isHere(l1.bound, mouse) || entered)
			window.draw(l2.draw);
		else
			window.draw(l1.draw);

		if (see)
		{
			window.draw(pw.text);
			window.draw(eye.draw);
		}
		else
		{
			window.draw(pw2.text);
			window.draw(close.draw);
		}
		if (change)
		{
			// check if the password/username is correct
			// in this case, it it correct
			page = (role ? 4 : 3);
			// if (role)
			// 	cout << "staff";
			// in this case, it is incorrect
			//window.draw(wrong.text);
		}
		window.display();
	}
}

void studentHome(RenderWindow& window, int& page, const float& scale)
{
	Event event;
	Object screen = createObject("content/Student.png");
	Object *b[6], *a[6];
	for (int i = 0; i < 3; i++)
	{
		b[i] = createObjectTest("content/Asset " + to_string(i + 27) + ".png", (256.5 + 170 * i) * scale, 296.0f * scale);
		a[i] = createObjectTest("content/Asset " + to_string(i + 33) + ".png", (256.5 + 170 * i) * scale, 296.0f * scale);
	}
	for (int i = 3; i < 6; i++)
	{
		b[i] = createObjectTest("content/Asset " + to_string(i + 27) + ".png", (256.5 + 170 * (i - 3)) * scale, 476.0f * scale);
		a[i] = createObjectTest("content/Asset " + to_string(i + 33) + ".png", (256.5 + 170 * (i - 3)) * scale, 476.0f * scale);
	}
	while (window.isOpen() && page == 3)
	{
		Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case Event::Closed: {
					window.close();
					break;
				}
				case Event::MouseButtonReleased: {
					for (int i = 0; i < 6; i++)
					{
						if (isHere(a[i]->bound, mouse))
						{
							// each functions
						}
					}
					break;
				}
				default: {
					break;
				}
			}

			window.clear();
			window.draw(screen.draw);
			for (int j = 0; j < 6; j++)
			{
				if (isHere(a[j]->bound, mouse))
					window.draw(b[j]->draw);
				else
					window.draw(a[j]->draw);
			}
			window.display();
		}
	}
	for (int j = 0; j < 6; j++)
	{
		delete (a[j]);
		delete (b[j]);
	}
}

void staffHome(RenderWindow& window, int& page, const float& scale)
{
	float k = scale;
	k--;
	Event event;
	Object screen = createObject("content/Staff.png");
	Object *a[3], *b[3];
	for (int i = 0; i < 3; i++)
	{
		a[i] = createObjectTest("content/Asset " + to_string(i + 45) + ".png", (165.0f + 240.0f * i) * scale, 330.0f * scale);
		b[i] = createObjectTest("content/Asset " + to_string(i + 42) + ".png", (165.0f + 240.0f * i) * scale, 330.0f * scale);
	}
	while (window.isOpen() && page == 4)
	{
		Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case Event::Closed: {
					window.close();
					break;
				}
				case Event::MouseButtonReleased: {
					for (int j = 0; j < 3; j++)
					{
						if (isHere(a[j]->bound, mouse))
						{
							// staff functions
						}
					}
					break;
				}
				default: {
					break;
				}
			}

			window.clear();
			window.draw(screen.draw);
			for (int j = 0; j < 3; j++)
			{
				if (isHere(a[j]->bound, mouse))
					window.draw(b[j]->draw);
				else
					window.draw(a[j]->draw);
			}
			window.display();
		}
	}
	for (int j = 0; j < 3; j++)
	{
		delete (a[j]);
		delete (b[j]);
	}
}

// void loadAllFiles()
// {
// }

// #include "header.h"

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
// //--------------------------------------------------------------------------------------------------
