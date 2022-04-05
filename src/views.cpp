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

Info* createInfoTest(string s, string info, float x, float y, float size)
{
	Info* a = new Info;
	a->font.loadFromFile(s);
	a->text.setFont(a->font);
	a->text.setCharacterSize(size);
	a->text.setPosition(x, y);
	a->text.setFillColor(Color(46, 68, 112, 255));
	a->text.setString(info);
	a->bound = a->text.getGlobalBounds();
	return a;
}

void drawWhich(RenderWindow& window, Object a, Object b, Vector2f& mouse)
{
	if (isHere(a.bound, mouse))
		window.draw(a.draw);
	else
		window.draw(b.draw);
}

void drawWhich(RenderWindow& window, Object* a, Object* b, Vector2f& mouse)
{
	if (isHere(a->bound, mouse))
		window.draw(a->draw);
	else
		window.draw(b->draw);
}

void switchPage(FloatRect& bound, Vector2f& mouse, int k, int& page)
{
	if (isHere(bound, mouse))
		page = k;
}

void changePos(Object* a, Object* b, float x, float y)
{
	a->draw.setPosition(x, y);
	a->bound = a->draw.getGlobalBounds();
	b->draw.setPosition(x, y);
	b->bound = b->draw.getGlobalBounds();
}

void changePos(Object* a, float x, float y)
{
	a->draw.setPosition(x, y);
	a->bound = a->draw.getGlobalBounds();
}

void changePos(Info* a, float x, float y)
{
	a->text.setPosition(x, y);
	a->bound = a->text.getGlobalBounds();
}
void texting(Info& text, Uint32 unicode, unsigned int limit)
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

void texting(Info*& text, Uint32 unicode, unsigned int limit)
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
	Object l1 = createObject("content/Login1.png", 400.0f * scale, 516.0f * scale);
	Object l2 = createObject("content/Login.png", 400.0f * scale, 516.0f * scale);
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
					texting(username, event.text.unicode, 15);

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
				drawWhich(window, b[j], a[j], mouse);
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
	Object *a[4], *b[4];
	for (int i = 0; i < 4; i++)
	{
		a[i] = createObjectTest("content/Asset " + to_string(i + 45) + ".png", (140.0f + 180.0f * i) * scale, 360.0f * scale);
		b[i] = createObjectTest("content/Asset " + to_string(i + 41) + ".png", (140.0f + 180.0f * i) * scale, 360.0f * scale);
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
					switchPage(a[0]->bound, mouse, 5, page);
					// for (int j = 0; j < 3; j++)
					// {
					// 	if (isHere(a[j]->bound, mouse))
					// 	{
					// 		// staff functions
					// 	}
					// }

					break;
				}
				default: {
					break;
				}
			}

			window.clear();
			window.draw(screen.draw);
			for (int j = 0; j < 4; j++)
			{
				drawWhich(window, b[j], a[j], mouse);
			}
			window.display();
		}
	}
	for (int j = 0; j < 4; j++)
	{
		delete (a[j]);
		delete (b[j]);
	}
}

void profile(RenderWindow& window, int& page, const float& scale, StudentNode* student)
{

	Object screen = createObject("content/General/MyProfile.png");
	Object change = createObject("content/General/change.png", 316.0f * scale, 386.0f * scale);
	Object change2 = createObject("content/General/change2.png", 316.0f * scale, 386.0f * scale);
	Object enter = createObject("content/General/enter.png", 316.0f * scale, 386.0f * scale);
	Object *a[7], *b[7];
	for (int i = 0; i < 7; i++)
	{
		a[i] = createObjectTest("content/General/a" + to_string(i + 1) + ".png", 0 * scale, 0 * scale);
		b[i] = createObjectTest("content/General/b" + to_string(i + 1) + ".png", 0 * scale, 0 * scale);
	}
	changePos(a[0], b[0], 440.0f * scale, 484.0f * scale);
	changePos(a[6], b[6], 440.0f * scale, 484.0f * scale);
	changePos(a[2], b[2], 376.0f * scale, 470.0f * scale);
	changePos(a[1], b[1], 506.0f * scale, 470.0f * scale);
	changePos(a[3], b[3], 480.0f * scale, 522.0f * scale);
	changePos(a[4], b[4], 750.0f * scale, 580.0f * scale);
	changePos(a[5], 322.0f * scale, 477.5f * scale);
	changePos(b[5], 426.0f * scale, 477.5f * scale);

	string text[6];
	text[0] = student->student.student_id;
	text[1] = student->student.first_name;
	text[2] = student->student.last_name;
	text[3] = student->student.student_class;
	text[4] = student->student.dob;
	text[5] = student->student.password;

	Info* inf[6];
	for (int i = 0; i < 6; i++)
		inf[i] = createInfoTest("content/Oswald-Light.ttf", text[i], 318.0f * scale, (303.0f + 56.0f * i) * scale, 20 * scale);
	changePos(inf[4], 318.0f * scale, (303.0f + 56.0 * 5) * scale);
	changePos(inf[5], 593.0f * scale, (303.0f + 56.0 * 5) * scale);
	changePos(inf[3], 318.0f * scale, (303.0f + 56.0 * 4) * scale);
	Info pw = createInfo("content/Oswald-Light.ttf", "Enter your new password here", 400.0f * scale, 455.0f * scale, 15.0f * scale);
	bool check1 = false, check2 = false, checkChange = false, gender = student->student.gender;
	int nah = 0;
	Event event;

	while (window.isOpen() && page == 5)
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
						if (!check1 && isHere(a[3]->bound, mouse))
							check1 = true;
						if (!check2 && isHere(a[4]->bound, mouse))
							check2 = true;

						if (check2)
						{
							if (nah == 0)
							{
								if (isHere(a[1]->bound, mouse))
									nah = 1;
								else if (isHere(a[2]->bound, mouse))
									nah = -1;
							}
							else if (nah > 0)
							{
								if (isHere(a[0]->bound, mouse))
								{
									nah++;
									checkChange = true;
									// change password function
								}
								if (nah == 1 && isHere(pw.bound, mouse))
									pw.check = true;
								else if (nah > 2)
								{
									nah = 0;
									checkChange = false;
									check2 = false;
								}
							}
						}
					}
					break;
					case Event::TextEntered: {
						if (nah == 1)
						{
							texting(pw, event.text.unicode, 10);
						}
						break;
					}
				}
				default:
					break;
			}
		}

		window.clear();
		window.draw(screen.draw);
		for (int i = 0; i < 6; i++)
			window.draw(inf[i]->text);
		window.draw((gender ? a[5]->draw : b[5]->draw));
		if (check1 || check2)
		{
			if (check2)
			{
				if (checkChange)
				{
					window.draw(change2.draw);
					drawWhich(window, b[6], a[6], mouse);
				}
				else
				{
					if (!nah)
					{
						window.draw(change.draw);
						drawWhich(window, b[1], a[1], mouse);
						drawWhich(window, b[2], a[2], mouse);
					}
					else
					{
						if (nah == -1)
						{
							nah = 0;
							check2 = false;
						}
						else
						{
							window.draw(enter.draw);
							window.draw(pw.text);
							drawWhich(window, b[0], a[0], mouse);
						}
					}
				}
			}
			window.draw(a[3]->draw);
			window.draw(a[4]->draw);
		}
		else
		{
			drawWhich(window, b[3], a[3], mouse);
			drawWhich(window, b[4], a[4], mouse);
		}
		window.display();
	}
	for (int j = 0; j < 7; j++)
	{
		delete (a[j]);
		delete (b[j]);
	}
	for (int i = 0; i < 6; i++)
		delete (inf[i]);
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
