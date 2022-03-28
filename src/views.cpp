#include "views.h"

Object createObject(string s, int x, int y)
{
	Object me;
	me.txt.loadFromFile(s);
	me.draw.setTexture(me.txt);
	me.draw.setPosition(x, y);
	me.bound = me.draw.getGlobalBounds();
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

void Scene1(RenderWindow& window, int& page)
{
	Texture first, student, staff, staff1, student1;
	first.loadFromFile("content/First.png");
	student.loadFromFile("content/Student.png");
	student1.loadFromFile("content/Student1.png");
	staff.loadFromFile("content/Staff.png");
	staff1.loadFromFile("content/Staff1.png");

	Sprite screen(first);
	Object o1 = createObject("content/Staff1.png", 180.0f, 300.0f);
	Object a1 = createObject("content/Staff2.png", 180.0f, 300.0f);
	Object o2 = createObject("content/Student1.png", 540.0f, 300.0f);
	Object a2 = createObject("content/Student2.png", 540.0f, 300.0f);

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
							cout << "I'm a staff\n";
							page = 2;
						}
						else if (isHere(o2.bound, mouse))
						{
							cout << "I'm a student\n";
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
		window.draw(screen);
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

void logIn(RenderWindow& window, int& page)
{
	Event event;
	bool see = false;
	Object screen = createObject("content/Log in.png");
	Object l1 = createObject("content/Login1.png", 400.0f, 515.0f);
	Object l2 = createObject("content/Login.png", 400.0f, 515.0f);
	Object eye = createObject("content/eye.png", 640.0f, 450.0f);
	Object close = createObject("content/closedeye.png", 640.0f, 450.0f);
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
						}
						else if (isHere(eye.bound, mouse))
						{
							see = !see;
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

		if (isHere(l1.bound, mouse))
			window.draw(l2.draw);
		else
			window.draw(l1.draw);

		if (see)
		{
			window.draw(eye.draw);
		}
		else
		{
			window.draw(close.draw);
		}
		window.display();
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
