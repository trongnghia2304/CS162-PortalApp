#include "views.h"

void Scene1(RenderWindow &window, int &page, bool &is_staff, const float &scale)
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
			case Event::Closed:
			{
				window.close();
				break;
			}
			case Event::MouseButtonReleased:
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					if (isHere(o1.bound, mouse))
					{
						is_staff = true;
						page = 2;
					}
					else if (isHere(o2.bound, mouse))
					{
						is_staff = false;
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

void logIn(RenderWindow &window, int &page, bool is_staff, const float &scale, ClassNode *class_list, StudentNode *staff_list, StudentNode *&user)
{
	Event event;
	bool see = false, entered = false, change = false, wrong_password = false;
	Object screen = createObject("content/Log in.png");
	Object l1 = createObject("content/Login1.png", 400.0f * scale, 516.0f * scale);
	Object l2 = createObject("content/Login.png", 400.0f * scale, 516.0f * scale);
	Object eye = createObject("content/eye.png", 640.0f * scale, 450.0f * scale);
	Object close = createObject("content/closedeye.png", 640.0f * scale, 450.0f * scale);
	Object out = createObject("content/logout.png", 866.0f * scale, 106.0f * scale);
	Object out_here = createObject("content/logout1.png", 866.0f * scale, 106.0f * scale);
	Info username = createInfo("content/Oswald-Light.ttf", "sample_text", 430.0f * scale, 380.0f * scale, 26.25f * scale);
	Info pw = createInfo("content/Oswald-Light.ttf", "12345678", 430.0f * scale, 447.0f * scale, 26.25f * scale);
	Info pw2 = createInfo("content/Oswald-Light.ttf", "********", 430.0f * scale, 450.0f * scale, 26.25f * scale);
	Info wrong = createInfo("content/Oswald-Light.ttf", "Wrong username/password, please try again!", 355.0f * scale, 497.5f * scale, 20.0f * scale);
	wrong.text.setFillColor(Color(118, 36, 2, 255));
	ClassNode *check_class = nullptr;
	while (window.isOpen() && page == 2)
	{
		Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
			{
				window.close();
				break;
			}
			case Event::MouseButtonReleased:
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					switchPage(out.bound, mouse, 1, page);
					wrong_password = false;
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
			case Event::TextEntered:
			{
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

		if (change && !wrong_password)
		{
			if (is_staff)
			{
				user = searchStudentNode(staff_list, username.s);
				if (user && user->student.password == pw.s)
				{
					page = 4;
					wrong_password = false;
				}
				else
					wrong_password = true;
			}
			else
			{
				check_class = class_list;
				user = nullptr;
				while (!user && check_class)
				{
					user = searchStudentNode(check_class->my_class.student_list, username.s);
					check_class = check_class->next;
				}
				if (user && user->student.password == pw.s)
				{
					wrong_password = false;
					page = 3;
				}
				else
					wrong_password = true;
			}
		}
		else if (wrong_password)
		{
			change = false;
			window.draw(wrong.text);
		}
		drawWhich(window, out_here, out, mouse);
		window.display();
	}
}
void studentHome(RegistrationSession data, RenderWindow &window, int &page, const float &scale)
{
	Event event;
	Object screen = createObject("content/Student.png");
	Object *b[6], *a[6];
	Object out = createObject("content/logout.png", 866.0f * scale, 106.0f * scale);
	Object return1 = createObject("content/Staff/Create elements/a7.png", 444.0f * scale, 484.0f * scale);
	Object return1_here = createObject("content/Staff/Create elements/b7.png", 444.0f * scale, 484.0f * scale);
	Object invalid = createObject("content/Staff/Create elements/not_time.png", 316.0f * scale, 386.0f * scale);
	Object out_here = createObject("content/logout1.png", 866.0f * scale, 106.0f * scale);
	bool fail = false;
	for (int i = 0; i < 3; i++)
	{
		b[i] = createObjectTest("content/Asset " + to_string(i + 27) + ".png", (256.5f + 170.0f * i) * scale, 296.0f * scale);
		a[i] = createObjectTest("content/Asset " + to_string(i + 33) + ".png", (256.5f + 170.0f * i) * scale, 296.0f * scale);
	}
	for (int i = 3; i < 6; i++)
	{
		b[i] = createObjectTest("content/Asset " + to_string(i + 27) + ".png", (256.5f + 170.f * (i - 3)) * scale, 476.0f * scale);
		a[i] = createObjectTest("content/Asset " + to_string(i + 33) + ".png", (256.5f + 170.f * (i - 3)) * scale, 476.0f * scale);
	}
	while (window.isOpen() && page == 3)
	{
		Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
			{
				window.close();
				break;
			}
			case Event::MouseButtonReleased:
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					if (!fail)
					{
						switchPage(out.bound, mouse, 1, page);
						switchPage(a[0]->bound, mouse, 5, page);
						switchPage(a[1]->bound, mouse, 7, page);
						switchPage(a[2]->bound, mouse, 13, page);
						switchPage(a[3]->bound, mouse, 8, page);
					}
					if (isHere(a[5]->bound, mouse))
					{
						string s = getCurrentDate();
						if (compareDate(data.start_date, s) <= 0 && compareDate(s, data.end_date) <= 0)
						{
							page = 11;
							return;
						}
						else
						{
							fail = true;
						}
					}
					if (fail && isHere(return1.bound, mouse))
						fail = false;
				}
				break;
			}
			default:
			{
				break;
			}
			}

			window.clear();
			window.draw(screen.draw);
			if (fail)
			{
				for (int i = 0; i < 6; i++)
					window.draw(a[i]->draw);
				window.draw(invalid.draw);
				drawWhich(window, return1_here, return1, mouse);
			}
			else
			{
				for (int j = 0; j < 6; j++)
				{
					drawWhich(window, b[j], a[j], mouse);
				}
			}
			drawWhich(window, out_here, out, mouse);
			window.display();
		}
	}
	for (int j = 0; j < 6; j++)
	{
		delete (a[j]);
		delete (b[j]);
	}
}

void staffHome(RenderWindow &window, int &page, const float &scale)
{
	Object out = createObject("content/logout.png", 866.0f * scale, 106.0f * scale);
	Object out_here = createObject("content/logout1.png", 866.0f * scale, 106.0f * scale);

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
			case Event::Closed:
			{
				window.close();
				break;
			}
			case Event::MouseButtonReleased:
			{
				switchPage(out.bound, mouse, 1, page);
				switchPage(a[1]->bound, mouse, 9, page);
				switchPage(a[0]->bound, mouse, 5, page);
				switchPage(a[1]->bound, mouse, 9, page);
				switchPage(a[2]->bound, mouse, 11, page);
				switchPage(a[3]->bound, mouse, 7, page);
				// for (int j = 0; j < 3; j++)
				// {
				// 	if (isHere(a[j]->bound, mouse))
				// 	{
				// 		// staff functions
				// 	}
				// }

				break;
			}
			default:
			{
				break;
			}
			}

			window.clear();
			window.draw(screen.draw);
			for (int j = 0; j < 4; j++)
			{
				drawWhich(window, b[j], a[j], mouse);
			}
			drawWhich(window, out_here, out, mouse);
			window.display();
		}
	}
	for (int j = 0; j < 4; j++)
	{
		delete (a[j]);
		delete (b[j]);
	}
}

void profile(RenderWindow &window, int &page, const float &scale, StudentNode *student, bool is_staff)
{
	string text[7];
	text[0] = student->student.student_id;
	text[1] = student->student.first_name;
	text[2] = student->student.last_name;
	text[3] = student->student.student_class;
	text[4] = student->student.dob;
	text[6] = student->student.password;
	text[5] = "";
	for (unsigned int i = 0; i < text[6].size(); i++)
	{
		text[5] += "*";
	}

	Info *inf[6];
	for (int i = 0; i < 6; i++)
		inf[i] = createInfoTest("content/Oswald-Light.ttf", text[i], 318.0f * scale, (303.0f + 56.0f * i) * scale, 20.0f * scale);
	changePos(inf[4], 318.0f * scale, (303.0f + 56.0f * 5) * scale);
	changePos(inf[5], 593.0f * scale, (303.0f + 56.0f * 5) * scale);
	changePos(inf[3], 318.0f * scale, (303.0f + 56.0f * 4) * scale);
	Object back = createObject("content/return.png", 80.0f * scale, 106.0f * scale);
	Object back_here = createObject("content/return1.png", 80.0f * scale, 106.0f * scale);
	Object screen = createObject("content/General/MyProfile.png");
	Object change = createObject("content/General/change.png", 316.0f * scale, 386.0f * scale);
	Object success = createObject("content/General/success.png", 316.0f * scale, 386.0f * scale);
	Object enter = createObject("content/General/enter.png", 316.0f * scale, 386.0f * scale);
	Object invalid = createObject("content/General/invalid.png", 316.0f * scale, 386.0f * scale);
	Object out = createObject("content/logout.png", 866.0f * scale, 106.0f * scale);
	Object out_here = createObject("content/logout1.png", 866.0f * scale, 106.0f * scale);
	Object *a[7], *b[7];
	for (int i = 0; i < 7; i++)
	{
		a[i] = createObjectTest("content/General/a" + to_string(i + 1) + ".png", 0 * scale, 0 * scale);
		b[i] = createObjectTest("content/General/b" + to_string(i + 1) + ".png", 0 * scale, 0 * scale);
	}
	changePos(a[0], b[0], 444.0f * scale, 484.0f * scale);
	// return button
	changePos(a[6], b[6], 444.0f * scale, 484.0f * scale);
	changePos(a[2], b[2], 376.0f * scale, 470.0f * scale);
	changePos(a[1], b[1], 506.0f * scale, 470.0f * scale);
	changePos(a[3], b[3], 480.0f * scale, 522.0f * scale);
	changePos(a[4], b[4], 750.0f * scale, 580.0f * scale);
	changePos(a[5], 322.0f * scale, 477.5f * scale);
	changePos(b[5], 426.0f * scale, 477.5f * scale);
	Info pw = createInfo("content/Oswald-Light.ttf", "Enter your new password here", 400.0f * scale, 455.0f * scale, 15.0f * scale);
	Info pw_old = createInfo("content/Oswald-Light.ttf", "Enter your old password here", 400.0f * scale, 415.0f * scale, 15.0f * scale);
	bool view_my_class = true, password_window = false, change_success = false, gender = student->student.gender;
	// switch subpage in "change password" (under_working(1), normal(0), changed(2))
	int password_status = 0;
	Event event;
	// only student can view their own class, not the staff
	if (text[3] == "")
	{
		view_my_class = false;
		b[3]->draw.setTexture(a[3]->txt);
	}

	while (window.isOpen() && page == 5)
	{
		Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
			{
				window.close();
				break;
			}
			case Event::MouseButtonReleased:
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					switchPage(out.bound, mouse, 1, page);
					switchPage(back.bound, mouse, (is_staff ? 4 : 3), page);
					if (view_my_class && isHere(a[3]->bound, mouse))
					{
						page = 6;
						break;
					}
					if (!password_window && isHere(a[4]->bound, mouse))
						password_window = true;

					if (password_window)
					{
						switch (password_status)
						{
						case 1:
						{
							if (isHere(a[0]->bound, mouse))
							{
								password_status++;
								if (changePassword(student->student, pw_old.s, pw.s))
								{
									change_success = true;
									text[5] = "";
									for (unsigned int i = 0; i < pw.s.size(); i++)
										text[5] += "*";
									inf[5]->text.setString(text[5]);
								}
							}
							if (isHere(pw.bound, mouse))
							{
								pw.check = true;
								pw_old.check = false;
							}
							if (isHere(pw_old.bound, mouse))
							{
								pw.check = false;
								pw_old.check = true;
							}
							break;
						}
						case 2:
						{
							if (isHere(a[6]->bound, mouse))
							{
								if (change_success)
								{
									password_status = 0;
									password_window = false;
								}
								else
								{
									password_status = 1;
									pw.text.setString("Enter your new password here");
									pw_old.text.setString("Enter your old password here");
									pw.s = "";
									pw_old.s = "";
								}
								change_success = false;
							}
							break;
						}
						default:
						{
							if (isHere(a[1]->bound, mouse))
							{
								password_status = 1;
								pw.text.setString("Enter your new password here");
								pw_old.text.setString("Enter your old password here");
								pw.s = "";
								pw_old.s = "";
							}
							else if (isHere(a[2]->bound, mouse))
							{
								password_status = 0;
								password_window = false;
							}
							break;
						}
						}
					}
				}
			}
			break;
			case Event::TextEntered:
			{
				if (password_status == 1)
				{
					texting(pw, event.text.unicode, 10);
					texting(pw_old, event.text.unicode, 10);
				}
				break;
			}
			default:
			{
				break;
			}
			}
		}
		window.clear();
		window.draw(screen.draw);
		for (int i = 0; i < 6; i++)
			window.draw(inf[i]->text);
		window.draw((gender ? a[5]->draw : b[5]->draw));
		if (password_window)
		{
			window.draw(a[3]->draw);
			window.draw(a[4]->draw);

			if (password_window)
			{
				switch (password_status)
				{
				case 1:
				{
					window.draw(enter.draw);
					window.draw(pw_old.text);
					window.draw(pw.text);
					drawWhich(window, b[0], a[0], mouse);
					break;
				}
				case 2:
				{
					if (change_success)
					{
						window.draw(success.draw);
						drawWhich(window, b[6], a[6], mouse);
					}
					else
					{
						window.draw(invalid.draw);
						drawWhich(window, b[6], a[6], mouse);
					}
					break;
				}
				default:
				{
					window.draw(change.draw);
					drawWhich(window, b[1], a[1], mouse);
					drawWhich(window, b[2], a[2], mouse);
					break;
				}
				}
			}
		}
		else
		{
			drawWhich(window, b[3], a[3], mouse);
			drawWhich(window, b[4], a[4], mouse);
		}
		drawWhich(window, out_here, out, mouse);
		drawWhich(window, back_here, back, mouse);
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

// student
void view_class(RenderWindow &window, int &page, const float &scale, ClassNode *class_list, StudentNode *user, const bool &is_staff)
{
	Event event;
	Object screen = createObject("content/Student/my_class.png");
	Object out = createObject("content/logout.png", 866.0f * scale, 106.0f * scale);
	Object out_here = createObject("content/logout1.png", 866.0f * scale, 106.0f * scale);
	Object export_1 = createObject("content/Staff/Create elements/export.png", 600.0f * scale, 272.0f * scale);
	Object export_here_1 = createObject("content/Staff/Create elements/export_here.png", 600.0f * scale, 272.0f * scale);
	Object back = createObject("content/return.png", 80.0f * scale, 106.0f * scale);
	Object back_here = createObject("content/return1.png", 80.0f * scale, 106.0f * scale);
	Object add_student = createObject("content/Student/add.png", 682.0f * scale, 272.0f * scale);
	Object add_student_here = createObject("content/Student/add1.png", 682.0f * scale, 272.0f * scale);
	Object left = createObject("content/Staff/Class/Asset 57.png", 492.0f * scale, 644.0f * scale);
	Object left_valid = createObject("content/Staff/Class/Asset 55.png", 492.0f * scale, 644.0f * scale);
	Object left_here = createObject("content/Staff/Class/Asset 91.png", 492.0f * scale, 644.0f * scale);
	Object right = createObject("content/Staff/Class/Asset 56.png", 510.0f * scale, 644.0f * scale);
	Object right_here = createObject("content/Staff/Class/Asset 90.png", 510.0f * scale, 644.0f * scale);
	Object right_valid = createObject("content/Staff/Class/Asset 54.png", 510.0f * scale, 644.0f * scale);
	ClassNode *my_class = searchClassNode(class_list, user->student.student_class);
	Info sub_header = createInfo("content/VNI-Vari.TTF", "Class - " + my_class->my_class.head_teacher, 160.0f * scale, 158.0f * scale, 28.0f * scale);
	sub_header.text.setFillColor(Color(101, 159, 235));
	Info header = createInfo("content/VNI-Vari.TTF", my_class->my_class.class_id, 160.0f * scale, 200.0f * scale, 43.0f * scale);
	Info *inf[8][6];
	for (int i = 0; i < 8; i++)
	{
		inf[i][0] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 184.0f * scale, (370.0f + 30.0f * i) * scale, 17.5f * scale);
		inf[i][1] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 232.0f * scale, (370.0f + 30.0f * i) * scale, 17.5f * scale);
		inf[i][2] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 347.0f * scale, (370.0f + 30.0f * i) * scale, 17.5f * scale);
		inf[i][3] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 515.0f * scale, (370.0f + 30.0f * i) * scale, 17.5f * scale);
		inf[i][4] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 633.0f * scale, (370.0f + 30.0f * i) * scale, 17.5f * scale);
		inf[i][5] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 715.0f * scale, (370.0f + 30.0f * i) * scale, 17.5f * scale);
		for (int j = 0; j < 6; j++)
			inf[i][j]->text.setFillColor(Color::Black);
	}
	int count = 0, change = 0;
	bool trigger_page = true;
	for (StudentNode *cur = my_class->my_class.student_list; cur; cur = cur->next)
	{
		count++;
	}
	Info count_student = createInfo("content/Oswald-Regular.ttf", "Total: " + to_string(count) + " Students", 181.0f * scale, 280.0f * scale, 15.0f * scale);
	count_student.text.setFillColor(Color::White);
	while (window.isOpen() && page == 6)
	{
		Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
			{
				window.close();
				break;
			}
			case Event::MouseButtonReleased:
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					switchPage(out.bound, mouse, 1, page);

					if (!is_staff)
						switchPage(back.bound, mouse, 5, page);
					else
						switchPage(back.bound, mouse, 9, page);
					if (isHere(add_student.bound, mouse) && is_staff)
					{
						page = 2;
						int k = student_profile(window, page, scale, my_class->my_class.student_list, is_staff, true, my_class->my_class.class_id);
						count += k;
						count_student.text.setString("Total: " + to_string(count) + " Students");
						trigger_page = true;
						// add new student to the class
					}
					if (isHere(right.bound, mouse) && change <= count - 8)
					{
						trigger_page = true;
						change += 8;
					}
					if (isHere(left.bound, mouse) && change != 0)
					{
						trigger_page = true;
						change -= 8;
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
		if (is_staff)
			drawWhich(window, add_student_here, add_student, mouse);
		drawWhich(window, out_here, out, mouse);
		drawWhich(window, back_here, back, mouse);
		if (is_staff)
			drawWhich(window, export_here_1, export_1, mouse);
		window.draw(header.text);
		window.draw(sub_header.text);
		window.draw(count_student.text);
		if (change == 0 && change >= count - 8)
		{
			window.draw(right.draw);
			window.draw(left.draw);
		}
		else if (change == 0)
		{
			window.draw(left.draw);
			drawWhich(window, right_here, right_valid, mouse);
		}
		else if (count >= count - 8)
		{
			window.draw(right.draw);
			drawWhich(window, left_here, left_valid, mouse);
		}
		else
		{
			drawWhich(window, right_here, right_valid, mouse);
			drawWhich(window, left_here, left_valid, mouse);
		}
		if (trigger_page)
		{
			StudentNode *cur = my_class->my_class.student_list;
			for (int i = 0; i < change; i++)
			{
				cur = cur->next;
			}
			for (int i = 0; i < 8; i++)
			{
				if (cur)
				{
					inf[i][0]->text.setString(to_string(cur->student.num));
					inf[i][1]->text.setString(cur->student.student_id);
					inf[i][2]->text.setString(cur->student.last_name + " " + cur->student.first_name);
					inf[i][4]->text.setString(cur->student.gender ? "F" : "M");
					inf[i][3]->text.setString(cur->student.dob);
					inf[i][5]->text.setString(cur->student.social_id);
					cur = cur->next;
				}
				else
				{
					for (int j = 0; j < 6; j++)
						inf[i][j]->text.setString("");
				}
			}
			trigger_page = false;
		}
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 6; j++)
				window.draw(inf[i][j]->text);
		}
		window.display();
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 6; j++)
			delete inf[i][j];
	}
}

// staff
void view_class(const string& year, const string& semester, string cur_class, string cur_teacher, RenderWindow& window, int& page, const float& scale, ClassNode* class_list, StudentNode* user, const bool& is_staff)
{
	Event event;

	Object export_success = createObject("content/Staff/Create elements/Asset 115.png", 316.0f * scale, 386.0f * scale);
	Object return1 = createObject("content/Staff/Create elements/a7.png", 440.0f * scale, 484.0f * scale);
	Object return1_here = createObject("content/Staff/Create elements/b7.png", 440.0f * scale, 484.0f * scale);
	Object return3 = createObject("content/Staff/Create elements/a7.png", 400.0f * scale, 484.0f * scale);
	Object return3_here = createObject("content/Staff/Create elements/b7.png", 400.0f * scale, 484.0f * scale);
	Object screen = createObject("content/Student/my_class.png");
	Object out = createObject("content/logout.png", 866.0f * scale, 106.0f * scale);
	Object out_here = createObject("content/logout1.png", 866.0f * scale, 106.0f * scale);
	Object export_1 = createObject("content/Staff/Create elements/export.png", 600.0f * scale, 272.0f * scale);
	Object export_here_1 = createObject("content/Staff/Create elements/export_here.png", 600.0f * scale, 272.0f * scale);
	Object back = createObject("content/return.png", 80.0f * scale, 106.0f * scale);
	Object back_here = createObject("content/return1.png", 80.0f * scale, 106.0f * scale);
	Object add_student = createObject("content/Student/add.png", 682.0f * scale, 272.0f * scale);
	Object add_student_here = createObject("content/Student/add1.png", 682.0f * scale, 272.0f * scale);
	Object left = createObject("content/Staff/Class/Asset 57.png", 492.0f * scale, 644.0f * scale);
	Object left_valid = createObject("content/Staff/Class/Asset 55.png", 492.0f * scale, 644.0f * scale);
	Object left_here = createObject("content/Staff/Class/Asset 91.png", 492.0f * scale, 644.0f * scale);
	Object right = createObject("content/Staff/Class/Asset 56.png", 510.0f * scale, 644.0f * scale);
	Object right_here = createObject("content/Staff/Class/Asset 90.png", 510.0f * scale, 644.0f * scale);
	Object right_valid = createObject("content/Staff/Class/Asset 54.png", 510.0f * scale, 644.0f * scale);
	Object split_here = createObject("content/Student/split_here.png", 324.0f * scale, 272.0f * scale);
	Object split = createObject("content/Student/split.png", 324.0f * scale, 272.0f * scale);
	Object del = createObject("content/Staff/Create elements/del.png", 400.0f * scale, 272.0f * scale);
	Object del_here = createObject("content/Staff/Create elements/del_here.png", 400.0f * scale, 272.0f * scale);
	Object sure = createObject("content/Staff/Create elements/sure.png", 316.0f * scale, 386.0f * scale);
	Object del_success = createObject("content/Staff/Create elements/Asset 115.png", 316.0f * scale, 386.0f * scale);
	Object nah = createObject("content/General/a3.png", 376.0f * scale, 484.0f * scale);
	Object nah_here = createObject("content/General/b3.png", 376.0f * scale, 484.0f * scale);
	Object ofcourse = createObject("content/General/a2.png", 506.0f * scale, 484.0f * scale);
	Object ofcourse_here = createObject("content/General/b2.png", 506.0f * scale, 484.0f * scale);
	Object return2 = createObject("content/General/a7.png", 386.0f * scale, 484.0f * scale);
	Object return2_here = createObject("content/General/b7.png", 386.0f * scale, 484.0f * scale);
	Object ok = createObject("content/General/a1.png", 516.0f * scale, 484.0f * scale);
	Object ok_here = createObject("content/General/b1.png", 516.0f * scale, 484.0f * scale);
	Object enter = createObject("content/Staff/Create elements/enter.png", 316.0f * scale, 386.0f * scale);
	Info student_id = createInfo("content/Oswald-Light.ttf", "Enter Student ID", 400.0f * scale, 415.0f * scale, 16.0f * scale);
	Info student_name = createInfo("content/Oswald-Light.ttf", "Enter Student name", 400.0f * scale, 455.0f * scale, 16.0f * scale);
	ClassNode* my_class = searchClassNode(class_list, cur_class);
	Info sub_header = createInfo("content/VNI-Vari.TTF", "Class - " + cur_teacher, 160.0f * scale, 158.0f * scale, 28.0f * scale);
	sub_header.text.setFillColor(Color(101, 159, 235));
	Info header = createInfo("content/VNI-Vari.TTF", cur_class, 160.0f * scale, 200.0f * scale, 43.0f * scale);
	Info* inf[8][6];
	StudentNode* tmp = NULL;
	for (int i = 0; i < 8; i++)
	{
		inf[i][0] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 184.0f * scale, (370.0f + 30.0f * i) * scale, 17.5f * scale);
		inf[i][1] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 232.0f * scale, (370.0f + 30.0f * i) * scale, 17.5f * scale);
		inf[i][2] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 347.0f * scale, (370.0f + 30.0f * i) * scale, 17.5f * scale);
		inf[i][3] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 515.0f * scale, (370.0f + 30.0f * i) * scale, 17.5f * scale);
		inf[i][4] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 633.0f * scale, (370.0f + 30.0f * i) * scale, 17.5f * scale);
		inf[i][5] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 715.0f * scale, (370.0f + 30.0f * i) * scale, 17.5f * scale);
		for (int j = 0; j < 6; j++)
			inf[i][j]->text.setFillColor(Color::Black);
	}
	int count = 0, change = 0;
	bool trigger_page = true, success = false, is_del = false, sure_check = false, success2 = false, sure_check2 = false;
	for (StudentNode* cur = my_class->my_class.student_list; cur; cur = cur->next)
	{
		count++;
	}
	Info count_student = createInfo("content/Oswald-Regular.ttf", "Total: " + to_string(count) + " Students", 181.0f * scale, 280.0f * scale, 15.0f * scale);
	count_student.text.setFillColor(Color::White);
	while (window.isOpen() && page == 6)
	{
		Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
			{
				window.close();
				break;
			}
			case Event::MouseButtonReleased:
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					if (isHere(del.bound, mouse))is_del = true;
					if (is_del)
					{
						if (sure_check2)
						{
							if (isHere(ofcourse.bound, mouse))
							{
								tmp = searchStudentNode(class_list->my_class.student_list, student_id.s);
								deleteEvent_student(class_list->my_class.student_list, tmp);
								success2 = true;
								sure_check2 = false;
								trigger_page = true;
								count--;
								count_student.text.setString("Total: " + to_string(count) + " Students");
							}
							if (isHere(nah.bound, mouse))
							{
								sure_check2 = false;
							}
						}
						if (isHere(return3.bound, mouse)) {
							is_del = false;
							success2 = false;
						}
						else if (isHere(ok.bound, mouse)) {
							sure_check2 = true;
						}

						if (isHere(student_name.bound, mouse))
						{
							student_name.check = true;
							student_id.check = false;
						}
						if (isHere(student_id.bound, mouse))
						{
							student_name.check = false;
							student_id.check = true;
						}
						
					}
						switchPage(out.bound, mouse, 1, page);

						if (!is_staff)
						{
							switchPage(back.bound, mouse, 5, page);
						}
						else
						{
							switchPage(split.bound, mouse, 22, page);
							view_class_score(year, semester, cur_class, cur_teacher, window, page, scale, class_list, user, is_staff);
							switchPage(back.bound, mouse, 9, page);
							if (success && isHere(return1.bound, mouse))
								success = false;
							if (isHere(export_1.bound, mouse))
							{
								success = true;
								string exported_student = "./csv/exported/" + my_class->my_class.class_id + "_" + my_class->my_class.head_teacher + ".csv";
								ofstream fout;
								fout.open(exported_student);
								writeToFileStudentNode(fout, my_class->my_class.student_list);
								fout.close();
							}
						}
						if (isHere(add_student.bound, mouse) && is_staff)
						{
							page = 2;
							int k = student_profile(window, page, scale, my_class->my_class.student_list, is_staff, true, my_class->my_class.class_id);
							count += k;
							count_student.text.setString("Total: " + to_string(count) + " Students");
							trigger_page = true;
						}
						if (isHere(right.bound, mouse) && change <= count - 8)
						{
							trigger_page = true;
							change += 8;
						}
						if (isHere(left.bound, mouse) && change != 0)
						{
							trigger_page = true;
							change -= 8;
						}
					}
				
					break;
				}
			case Event::TextEntered:
			{
				texting(student_id, event.text.unicode, 10);
				texting(student_name, event.text.unicode, 30);
				break;
			}
			default:
				break;
			}
			}

			window.clear();
			window.draw(screen.draw);
			if (is_staff)
			{
				drawWhich(window, add_student_here, add_student, mouse);
				drawWhich(window, export_here_1, export_1, mouse);
				drawWhich(window, split_here, split, mouse);
			}
			drawWhich(window, del_here, del, mouse);
			drawWhich(window, out_here, out, mouse);
			drawWhich(window, back_here, back, mouse);
			window.draw(header.text);
			window.draw(sub_header.text);
			window.draw(count_student.text);
			if (change == 0 && change >= count - 8)
			{
				window.draw(right.draw);
				window.draw(left.draw);
			}
			else if (change == 0)
			{
				window.draw(left.draw);
				drawWhich(window, right_here, right_valid, mouse);
			}
			else if (count >= count - 8)
			{
				window.draw(right.draw);
				drawWhich(window, left_here, left_valid, mouse);
			}
			else
			{
				drawWhich(window, right_here, right_valid, mouse);
				drawWhich(window, left_here, left_valid, mouse);
			}
			if (trigger_page)
			{
				StudentNode* cur = my_class->my_class.student_list;
				for (int i = 0; i < change; i++)
				{
					cur = cur->next;
				}
				for (int i = 0; i < 8; i++)
				{
					if (cur)
					{
						inf[i][0]->text.setString(to_string(cur->student.num));
						inf[i][1]->text.setString(cur->student.student_id);
						inf[i][2]->text.setString(cur->student.last_name + " " + cur->student.first_name);
						inf[i][4]->text.setString(cur->student.gender ? "F" : "M");
						inf[i][3]->text.setString(cur->student.dob);
						inf[i][5]->text.setString(cur->student.social_id);
						cur = cur->next;
					}
					else
					{
						for (int j = 0; j < 6; j++)
							inf[i][j]->text.setString("");
					}
				}
				trigger_page = false;
			}
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 6; j++)
					window.draw(inf[i][j]->text);
			}
			if (success)
			{
				window.draw(export_success.draw);
				drawWhich(window, return1_here, return1, mouse);
			}
		
			if (is_staff && is_del) {
				window.draw(enter.draw);
				window.draw(student_id.text);
				window.draw(student_name.text);
				drawWhich(window, return3_here, return3, mouse);
				drawWhich(window, ok_here, ok, mouse);
				
			}	if (sure_check2)
			{
				window.draw(sure.draw);
				drawWhich(window, nah_here, nah, mouse);
				drawWhich(window, ofcourse_here, ofcourse, mouse);
if (success2)
			{
				
				window.draw(del_success.draw);
				drawWhich(window, return1_here, return1, mouse);
			}
			}
			window.display();
		}
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 6; j++)
				delete inf[i][j];
		}
	}



void view_class_score(const string &year, const string &semester, string cur_class, string cur_teacher, RenderWindow &window, int &page, const float &scale, ClassNode *class_list, StudentNode *user, const bool &is_staff)
{
	Event event;
	Object export_success = createObject("content/Staff/Create elements/Asset 115.png", 316.0f * scale, 386.0f * scale);
	Object return1 = createObject("content/Staff/Create elements/a7.png", 444.0f * scale, 484.0f * scale);
	Object return1_here = createObject("content/Staff/Create elements/b7.png", 444.0f * scale, 484.0f * scale);
	Object screen = createObject("content/my_class_score.png");
	Object out = createObject("content/logout.png", 866.0f * scale, 106.0f * scale);
	Object out_here = createObject("content/logout1.png", 866.0f * scale, 106.0f * scale);
	Object export_1 = createObject("content/Staff/Create elements/export.png", 600.0f * scale, 272.0f * scale);
	Object export_here_1 = createObject("content/Staff/Create elements/export_here.png", 600.0f * scale, 272.0f * scale);
	Object back = createObject("content/return.png", 80.0f * scale, 106.0f * scale);
	Object back_here = createObject("content/return1.png", 80.0f * scale, 106.0f * scale);
	Object add_student = createObject("content/Student/add.png", 682.0f * scale, 272.0f * scale);
	Object add_student_here = createObject("content/Student/add1.png", 682.0f * scale, 272.0f * scale);
	Object left = createObject("content/Staff/Class/Asset 57.png", 492.0f * scale, 644.0f * scale);
	Object left_valid = createObject("content/Staff/Class/Asset 55.png", 492.0f * scale, 644.0f * scale);
	Object left_here = createObject("content/Staff/Class/Asset 91.png", 492.0f * scale, 644.0f * scale);
	Object right = createObject("content/Staff/Class/Asset 56.png", 510.0f * scale, 644.0f * scale);
	Object right_here = createObject("content/Staff/Class/Asset 90.png", 510.0f * scale, 644.0f * scale);
	Object right_valid = createObject("content/Staff/Class/Asset 54.png", 510.0f * scale, 644.0f * scale);
	Object split_here = createObject("content/Student/total_here.png", 324.0f * scale, 272.0f * scale);
	Object split = createObject("content/Student/total.png", 324.0f * scale, 272.0f * scale);
	ClassNode *my_class = searchClassNode(class_list, cur_class);
	Info sub_header = createInfo("content/VNI-Vari.TTF", "Class - " + cur_teacher, 160.0f * scale, 158.0f * scale, 28.0f * scale);
	sub_header.text.setFillColor(Color(101, 159, 235));
	Info header = createInfo("content/VNI-Vari.TTF", cur_class, 160.0f * scale, 200.0f * scale, 43.0f * scale);
	Info *inf[8][6];
	for (int i = 0; i < 8; i++)
	{
		inf[i][0] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 184.0f * scale, (370.0f + 30.0f * i) * scale, 17.5f * scale);
		inf[i][1] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 232.0f * scale, (370.0f + 30.0f * i) * scale, 17.5f * scale);
		inf[i][2] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 347.0f * scale, (370.0f + 30.0f * i) * scale, 17.5f * scale);
		inf[i][3] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 602.0f * scale, (370.0f + 30.0f * i) * scale, 17.5f * scale);
		inf[i][4] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 740.0f * scale, (370.0f + 30.0f * i) * scale, 17.5f * scale);
		inf[i][5] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 715.0f * scale, (370.0f + 30.0f * i) * scale, 17.5f * scale);
		for (int j = 0; j < 6; j++)
			inf[i][j]->text.setFillColor(Color::Black);
	}
	int count = 0, change = 0;
	float gpa1[8], gpa_tt[8];
	bool trigger_page = true, success = false;
	for (StudentNode *cur = my_class->my_class.student_list; cur; cur = cur->next)
	{
		count++;
	}
	Info count_student = createInfo("content/Oswald-Regular.ttf", "Total: " + to_string(count) + " Students", 181.0f * scale, 280.0f * scale, 15.0f * scale);
	count_student.text.setFillColor(Color::White);
	while (window.isOpen() && page == 22)
	{
		Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
			{
				window.close();
				break;
			}
			case Event::MouseButtonReleased:
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					switchPage(out.bound, mouse, 1, page);

					if (!is_staff)
					{
						switchPage(back.bound, mouse, 5, page);
					}
					else
					{
						switchPage(back.bound, mouse, 9, page);
						switchPage(split.bound, mouse, 6, page);
						if (success && isHere(return1.bound, mouse))
							success = false;
						if (isHere(export_1.bound, mouse))
						{
							success = true;
							string exported_student = "./csv/exported/" + my_class->my_class.class_id + "_" + my_class->my_class.head_teacher + ".csv";
							ofstream fout;
							fout.open(exported_student);
							writeToFileStudentNode(fout, my_class->my_class.student_list);
							fout.close();
						}
					}
					if (isHere(add_student.bound, mouse) && is_staff)
					{
						page = 2;
						int k = student_profile(window, page, scale, my_class->my_class.student_list, is_staff, true, my_class->my_class.class_id);
						count += k;
						count_student.text.setString("Total: " + to_string(count) + " Students");
						trigger_page = true;
					}
					if (isHere(right.bound, mouse) && change <= count - 8)
					{
						trigger_page = true;
						change += 8;
					}
					if (isHere(left.bound, mouse) && change != 0)
					{
						trigger_page = true;
						change -= 8;
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
		if (is_staff)
		{
			drawWhich(window, add_student_here, add_student, mouse);
			drawWhich(window, export_here_1, export_1, mouse);
			drawWhich(window, split_here, split, mouse);
		}
		drawWhich(window, out_here, out, mouse);
		drawWhich(window, back_here, back, mouse);
		window.draw(header.text);
		window.draw(sub_header.text);
		window.draw(count_student.text);
		if (change == 0 && change >= count - 8)
		{
			window.draw(right.draw);
			window.draw(left.draw);
		}
		else if (change == 0)
		{
			window.draw(left.draw);
			drawWhich(window, right_here, right_valid, mouse);
		}
		else if (count >= count - 8)
		{
			window.draw(right.draw);
			drawWhich(window, left_here, left_valid, mouse);
		}
		else
		{
			drawWhich(window, right_here, right_valid, mouse);
			drawWhich(window, left_here, left_valid, mouse);
		}
		if (trigger_page)
		{
			StudentNode *cur = my_class->my_class.student_list;
			for (int i = 0; i < change; i++)
			{
				cur = cur->next;
			}
			for (int i = 0; i < 8; i++)
			{
				if (cur)
				{
					gpa1[i] = 0.0f;
					gpa_tt[i] = 0.0f;
					inf[i][0]->text.setString(to_string(cur->student.num));
					inf[i][1]->text.setString(cur->student.student_id);
					inf[i][2]->text.setString(cur->student.last_name + " " + cur->student.first_name);
					inf[i][5]->text.setString(cur->student.social_id);
					int num_course = 0, num_total = 0;
					for (MyCourse *cur_course = cur->student.my_course; cur_course; cur_course = cur_course->next)
					{
						num_total++;
						gpa_tt[i] += cur_course->score.overall;
						if (cur_course->course->semester_id == semester && cur_course->course->year_id == year)
						{
							num_course++;
							gpa1[i] += cur_course->score.overall;
						}
					}
					if (num_total)
						gpa_tt[i] = gpa_tt[i] / (float)num_total;
					if (num_course)
						gpa1[i] = gpa1[i] / (float)num_course;
					stringstream a, b;
					a << fixed << setprecision(1) << gpa_tt[i];
					b << fixed << setprecision(1) << gpa1[i];
					inf[i][4]->text.setString(a.str());
					inf[i][3]->text.setString(b.str());
					cur = cur->next;
				}
				else
				{
					for (int j = 0; j < 6; j++)
						inf[i][j]->text.setString("");
				}
			}
			trigger_page = false;
		}
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 5; j++)
				window.draw(inf[i][j]->text);
		}
		if (success)
		{
			window.draw(export_success.draw);
			drawWhich(window, return1_here, return1, mouse);
		}
		window.display();
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 6; j++)
			delete inf[i][j];
	}
}

// student
void view_course(RenderWindow &window, int &page, const float &scale, StudentNode *user, const bool &is_staff, const string &sem, const string &year)
{
	MyCourse *initial = user->student.my_course;
	while (initial && (initial->year != year || initial->sem != sem))
	{
		initial = initial->next;
	}
	Event event;
	Object *screen = createObjectTest("content/Student/my_course.png");
	Object out = createObject("content/logout.png", 866.0f * scale, 106.0f * scale);
	Object out_here = createObject("content/logout1.png", 866.0f * scale, 106.0f * scale);
	Object back = createObject("content/return.png", 80.0f * scale, 106.0f * scale);
	Object back_here = createObject("content/return1.png", 80.0f * scale, 106.0f * scale);
	Object left = createObject("content/Staff/Class/Asset 57.png", 492.0f * scale, 644.0f * scale);
	Object left_valid = createObject("content/Staff/Class/Asset 55.png", 492.0f * scale, 644.0f * scale);
	Object left_here = createObject("content/Staff/Class/Asset 91.png", 492.0f * scale, 644.0f * scale);
	Object right = createObject("content/Staff/Class/Asset 56.png", 510.0f * scale, 644.0f * scale);
	Object right_here = createObject("content/Staff/Class/Asset 90.png", 510.0f * scale, 644.0f * scale);
	Object right_valid = createObject("content/Staff/Class/Asset 54.png", 510.0f * scale, 644.0f * scale);
	Info *inf[6][4];
	Object *square[6], *square_here[6];
	CourseNode *course[6];
	for (int i = 0; i < 3; i++)
	{
		square[i] = createObjectTest("content/Student/course.png", (172.0f + 220.0f * i) * scale, 322.0f * scale);
		square_here[i] = createObjectTest("content/Student/course_here.png", (172.0f + 220.0f * i) * scale, 322.0f * scale);
		inf[i][0] = createInfoTest("content/Oswald-Medium.ttf", "demo_text", (243.0f + 220.0f * i) * scale, 330.0f * scale, 25.0f * scale);
		for (int j = 1; j < 4; j++)
			inf[i][j] = createInfoTest("content/Oswald-Medium.ttf", "demo_text", (185.0f + 220.0f * i) * scale, (356.0f + 22.0f * j) * scale, 12.5f * scale);
	}
	for (int i = 3; i < 6; i++)
	{
		course[i] = nullptr;
		square[i] = createObjectTest("content/Student/course.png", (172.0f + 220.0f * (i - 3)) * scale, 480.0f * scale);
		square_here[i] = createObjectTest("content/Student/course_here.png", (172.0f + 220.0f * (i - 3)) * scale, 480.0f * scale);
		inf[i][0] = createInfoTest("content/Oswald-Medium.ttf", "demo_text", (243.0f + 220.0f * (i - 3)) * scale, 485.0f * scale, 25.0f * scale);
		for (int j = 1; j < 4; j++)
			inf[i][j] = createInfoTest("content/Oswald-Medium.ttf", "demo_text", (185.0f + 220.0f * (i - 3)) * scale, (518.0f + 22.0f * j) * scale, 12.5f * scale);
	}
	int count = 0, change = 0;
	bool trigger_page = true;
	for (MyCourse *cur = initial; cur; cur = cur->next)
	{
		if (cur->sem == sem && cur->year == year)
			count++;
	}
	Info count_course = createInfo("content/Oswald-Regular.ttf", "Total: " + to_string(count) + " Courses", 200.0f * scale, 279.0f * scale, 15.0f * scale);
	count_course.text.setFillColor(Color::White);
	while (window.isOpen() && page == 9)
	{
		Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
			{
				window.close();
				break;
			}
			case Event::MouseButtonReleased:
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					switchPage(out.bound, mouse, 1, page);
					switchPage(back.bound, mouse, 8, page);
					if (isHere(right.bound, mouse) && change <= count - 6)
					{
						trigger_page = true;
						change += 6;
					}
					if (isHere(left.bound, mouse) && change != 0)
					{
						trigger_page = true;
						change -= 6;
					}
					for (int i = 0; i < 6; i++)
					{
						if (isHere(square[i]->bound, mouse) && course[i])
						{
							//
						}
					}
				}
				break;
			}
			default:
				break;
			}
		}

		window.clear();
		window.draw(screen->draw);
		drawWhich(window, out_here, out, mouse);
		drawWhich(window, back_here, back, mouse);
		window.draw(count_course.text);
		if (change == 0 && change >= count - 6)
		{
			window.draw(right.draw);
			window.draw(left.draw);
		}
		else if (change == 0)
		{
			window.draw(left.draw);
			drawWhich(window, right_here, right_valid, mouse);
		}
		else if (change >= count - 6)
		{
			window.draw(right.draw);
			drawWhich(window, left_here, left_valid, mouse);
		}
		else
		{
			drawWhich(window, right_here, right_valid, mouse);
			drawWhich(window, left_here, left_valid, mouse);
		}
		if (trigger_page)
		{
			MyCourse *cur = initial;
			for (int i = 0; i < change; i++)
			{
				cur = cur->next;
			}
			for (int i = 0; i < 6; i++)
			{
				while (cur && (cur->sem != sem || cur->year != year))
					cur = cur->next;
				if (cur)
				{
					course[i] = cur->course;
					inf[i][0]->text.setString(cur->course->course.course_id);
					inf[i][1]->text.setString(cur->course->course.course_name);
					inf[i][2]->text.setString(cur->course->course.teacher_name);
					inf[i][3]->text.setString("Credit: " + to_string(cur->course->course.num_credit) + "    " + session_convert(cur->course->course.teaching_session[0]) + ", " + session_convert(cur->course->course.teaching_session[1]));
					inf[i][0]->text.setPosition(square[i]->bound.left + (square[i]->bound.width - inf[i][0]->text.getGlobalBounds().width) / 2, square[i]->bound.top + 16.0f);
					cur = cur->next;
				}
				else
				{
					course[i] = nullptr;
					for (int j = 0; j < 4; j++)
						inf[i][j]->text.setString("");
				}
			}
			trigger_page = false;
		}
		for (int i = 0; i < 6; i++)
		{
			if (inf[i][0]->text.getString() == "")
				break;
			window.draw(square[i]->draw);
			for (int j = 0; j < 4; j++)
				window.draw(inf[i][j]->text);
		}
		window.display();
	}
	for (int i = 0; i < 6; i++)
	{
		delete square[i], square_here[i];
		for (int j = 0; j < 4; j++)
			delete inf[i][j];
	}
	delete screen;
}

// staff
void view_course(RenderWindow &window, int &page, const float &scale, CourseNode *&my_course, const bool &is_staff, ClassNode *all_class, const string &year, const string &sem)
{
	Event event;
	Object *screen = createObjectTest("content/Staff/course_staff.png");
	Object out = createObject("content/logout.png", 866.0f * scale, 106.0f * scale);
	Object out_here = createObject("content/logout1.png", 866.0f * scale, 106.0f * scale);
	Object back = createObject("content/return.png", 80.0f * scale, 106.0f * scale);
	Object back_here = createObject("content/return1.png", 80.0f * scale, 106.0f * scale);
	Object add_course = createObject("content/Student/add_course.png", 680.0f * scale, 272.0f * scale);
	Object add_course_here = createObject("content/Student/add_course_here.png", 680.0f * scale, 272.0f * scale);
	Object del_course = createObject("content/Staff/Create elements/del.png", 500.0f * scale, 272.0f * scale);
	Object del_course_here = createObject("content/Staff/Create elements/del_here.png", 500.0f * scale, 272.0f * scale);
	Object left = createObject("content/Staff/Class/Asset 57.png", 492.0f * scale, 644.0f * scale);
	Object left_valid = createObject("content/Staff/Class/Asset 55.png", 492.0f * scale, 644.0f * scale);
	Object left_here = createObject("content/Staff/Class/Asset 91.png", 492.0f * scale, 644.0f * scale);
	Object right = createObject("content/Staff/Class/Asset 56.png", 510.0f * scale, 644.0f * scale);
	Object right_here = createObject("content/Staff/Class/Asset 90.png", 510.0f * scale, 644.0f * scale);
	Object right_valid = createObject("content/Staff/Class/Asset 54.png", 510.0f * scale, 644.0f * scale);
	Object sure = createObject("content/Staff/Create elements/sure.png", 316.0f * scale, 386.0f * scale);
	Object del_success = createObject("content/Staff/Create elements/Asset 115.png", 316.0f * scale, 386.0f * scale);
	Object return1 = createObject("content/Staff/Create elements/a7.png", 444.0f * scale, 484.0f * scale);
	Object return1_here = createObject("content/Staff/Create elements/b7.png", 444.0f * scale, 484.0f * scale);
	Object nah = createObject("content/General/a3.png", 376.0f * scale, 484.0f * scale);
	Object nah_here = createObject("content/General/b3.png", 376.0f * scale, 484.0f * scale);
	Object ofcourse = createObject("content/General/a2.png", 506.0f * scale, 484.0f * scale);
	Object ofcourse_here = createObject("content/General/b2.png", 506.0f * scale, 484.0f * scale);
	Info sub_header = createInfo("content/VNI-Vari.TTF", year, 160.0f * scale, 158.0f * scale, 28.0f * scale);
	Info header = createInfo("content/VNI-Vari.TTF", sem, 160.0f * scale, 200.0f * scale, 43.0f * scale);
	sub_header.text.setFillColor(Color(101, 159, 235));
	Info *inf[6][4];
	Object *square[6], *square_here[6], *rem[6], *rem_here[6];
	CourseNode *course[6], *tmp = nullptr;
	for (int i = 0; i < 3; i++)
	{
		square[i] = createObjectTest("content/Student/course.png", (172.0f + 220.0f * i) * scale, 322.0f * scale);
		square_here[i] = createObjectTest("content/Student/course_here.png", (172.0f + 220.0f * i) * scale, 322.0f * scale);
		rem[i] = createObjectTest("content/Staff/Create elements/rem.png", (172.0f + 220.0f * i) * scale, 322.0f * scale);
		rem_here[i] = createObjectTest("content/Staff/Create elements/rem_here.png", (172.0f + 220.0f * i) * scale, 322.0f * scale);
		inf[i][0] = createInfoTest("content/Oswald-Medium.ttf", "demo_text", (243.0f + 220.0f * i) * scale, 330.0f * scale, 25.0f * scale);
		for (int j = 1; j < 4; j++)
			inf[i][j] = createInfoTest("content/Oswald-Medium.ttf", "demo_text", (185.0f + 220.0f * i) * scale, (356.0f + 22.0f * j) * scale, 12.5f * scale);
	}
	for (int i = 3; i < 6; i++)
	{
		course[i] = nullptr;
		square[i] = createObjectTest("content/Student/course.png", (172.0f + 220.0f * (i - 3)) * scale, 480.0f * scale);
		rem[i] = createObjectTest("content/Staff/Create elements/rem.png", (172.0f + 220.0f * (i - 3)) * scale, 480.0f * scale);
		rem_here[i] = createObjectTest("content/Staff/Create elements/rem_here.png", (172.0f + 220.0f * (i - 3)) * scale, 480.0f * scale);
		square_here[i] = createObjectTest("content/Student/course_here.png", (172.0f + 220.0f * (i - 3)) * scale, 480.0f * scale);
		inf[i][0] = createInfoTest("content/Oswald-Medium.ttf", "demo_text", (243.0f + 220.0f * (i - 3)) * scale, 485.0f * scale, 25.0f * scale);
		for (int j = 1; j < 4; j++)
			inf[i][j] = createInfoTest("content/Oswald-Medium.ttf", "demo_text", (185.0f + 220.0f * (i - 3)) * scale, (518.0f + 22.0f * j) * scale, 12.5f * scale);
	}
	int count = 0, change = 0;
	bool trigger_page = true, del = false, sure_check = false, success = false, tick = false;
	for (CourseNode *cur = my_course; cur; cur = cur->next)
	{
		count++;
	}
	Info count_course = createInfo("content/Oswald-Regular.ttf", "Total: " + to_string(count) + " Courses", 200.0f * scale, 279.0f * scale, 15.0f * scale);
	count_course.text.setFillColor(Color::White);
	while (window.isOpen() && page == 9)
	{
		Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
			{
				window.close();
				break;
			}
			case Event::MouseButtonReleased:
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					switchPage(out.bound, mouse, 1, page);
					switchPage(back.bound, mouse, 8, page);
					if (isHere(add_course.bound, mouse))
					{
						page = 12;
						if (add_new_course(window, page, scale, my_course, year, sem))
						{
							trigger_page = true;
							count++;
							count_course.text.setString("Total: " + to_string(count) + " Courses");
						}
						page = 9;
					}
					if (isHere(right.bound, mouse) && change <= count - 6)
					{
						trigger_page = true;
						change += 6;
					}
					if (isHere(left.bound, mouse) && change != 0)
					{
						trigger_page = true;
						change -= 6;
					}
					if (isHere(del_course.bound, mouse))
					{
						del = !del;
						sure_check = false;
						success = false;
					}
					if (success && isHere(return1.bound, mouse))
						success = false;
					if (del)
					{
						if (sure_check)
						{
							if (isHere(ofcourse.bound, mouse))
							{
								deleteEvent_course(my_course, tmp, all_class);
								success = true;
								sure_check = false;
								trigger_page = true;
								count--;
								count_course.text.setString("Total: " + to_string(count) + " Courses");
							}
							if (isHere(nah.bound, mouse))
							{
								sure_check = false;
							}
						}
						else if (!success)
						{
							for (int i = 0; i < 6; i++)
							{
								if (isHere(square[i]->bound, mouse) && course[i])
								{
									sure_check = true;
									tmp = course[i];
								}
							}
						}
					}
					else
					{
						for (int i = 0; i < 6; i++)
							if (isHere(square[i]->bound, mouse) && course[i])
							{
								page = 10;
								while (page == 10 || page == 11)
								{
									if (page == 10)
										course_student(1, window, page, scale, course[i]);
									else
										course_student2(window, page, scale, course[i], all_class);
								}
							}
					}
				}
				if (event.mouseButton.button == Mouse::Right)
				{
					for (int i = 0; i < 6; i++)
					{
						if (isHere(square[i]->bound, mouse) && course[i])
						{
							page = 12;
							if (change_course_info(window, page, scale, course[i], year, sem))
							{
								trigger_page = true;
							}
							page = 9;
						}
					}
				}
				break;
			}
			default:
				break;
			}
		}

		window.clear();
		window.draw(screen->draw);
		window.draw(sub_header.text);
		window.draw(header.text);
		drawWhich(window, add_course_here, add_course, mouse);
		drawWhich(window, out_here, out, mouse);
		drawWhich(window, back_here, back, mouse);

		window.draw(count_course.text);
		if (change == 0 && change >= count - 6)
		{
			window.draw(right.draw);
			window.draw(left.draw);
		}
		else if (change == 0)
		{
			window.draw(left.draw);
			drawWhich(window, right_here, right_valid, mouse);
		}
		else if (change >= count - 6)
		{
			window.draw(right.draw);
			drawWhich(window, left_here, left_valid, mouse);
		}
		else
		{
			drawWhich(window, right_here, right_valid, mouse);
			drawWhich(window, left_here, left_valid, mouse);
		}
		if (trigger_page)
		{
			CourseNode *cur = my_course;
			for (int i = 0; i < change; i++)
			{
				cur = cur->next;
			}
			for (int i = 0; i < 6; i++)
			{
				course[i] = cur;
				if (cur)
				{
					inf[i][0]->text.setString(cur->course.course_id);
					inf[i][1]->text.setString(cur->course.course_name);
					inf[i][2]->text.setString(cur->course.teacher_name);
					inf[i][3]->text.setString("Credit: " + to_string(cur->course.num_credit) + "    " + session_convert(cur->course.teaching_session[0]) + ", " + session_convert(cur->course.teaching_session[1]));
					inf[i][0]->text.setPosition(Vector2f(square[i]->bound.left + (square[i]->bound.width - inf[i][0]->text.getGlobalBounds().width) / 2, square[i]->bound.top + 16.0f));
					cur = cur->next;
				}
				else
				{
					for (int j = 0; j < 4; j++)
						inf[i][j]->text.setString("");
				}
			}
			trigger_page = false;
		}
		for (int i = 0; i < 6; i++)
		{
			if (inf[i][0]->text.getString() == "")
				break;
			Object *border_here, *border;
			if (success || sure_check)
			{
				window.draw(rem[i]->draw);
				for (int j = 0; j < 4; j++)
				{
					inf[i][j]->text.setFillColor(Color(46, 48, 112));
					window.draw(inf[i][j]->text);
				}
			}
			else
			{
				if (del)
				{
					border_here = rem_here[i];
					border = rem[i];
				}
				else
				{
					border_here = square_here[i];
					border = square[i];
				}
				if (drawWhich(window, border_here, border, mouse))
				{
					for (int j = 0; j < 4; j++)
					{
						inf[i][j]->text.setFillColor(Color(118, 36, 2));
						window.draw(inf[i][j]->text);
					}
				}
				else
				{
					for (int j = 0; j < 4; j++)
					{
						inf[i][j]->text.setFillColor(Color(46, 68, 112));
						window.draw(inf[i][j]->text);
					}
				}
			}
		}
		if (del)
		{
			window.draw(del_course_here.draw);
			if (sure_check)
			{
				window.draw(sure.draw);
				drawWhich(window, nah_here, nah, mouse);
				drawWhich(window, ofcourse_here, ofcourse, mouse);
			}
			if (success)
			{
				window.draw(del_success.draw);
				drawWhich(window, return1_here, return1, mouse);
			}
		}
		else
			drawWhich(window, del_course_here, del_course, mouse);
		window.display();
	}
	for (int i = 0; i < 6; i++)
	{
		delete square[i], square_here[i], rem[i], rem_here[i];
		for (int j = 0; j < 4; j++)
			delete inf[i][j];
	}
	delete screen;
}

void course_student(int k, RenderWindow &window, int &page, const float &scale, CourseNode *course)
{
	Event event;
	Object export1 = createObject("content/Staff/Create elements/export.png", 680.0f * scale, 272.0f * scale);
	Object export1_here = createObject("content/Staff/Create elements/export_here.png", 680.0f * scale, 272.0f * scale);
	Object screen = createObject("content/Student/my_class.png");
	Object out = createObject("content/logout.png", 866.0f * scale, 106.0f * scale);
	Object out_here = createObject("content/logout1.png", 866.0f * scale, 106.0f * scale);
	Object back = createObject("content/return.png", 80.0f * scale, 106.0f * scale);
	Object back_here = createObject("content/return1.png", 80.0f * scale, 106.0f * scale);
	Object split_here = createObject("content/Student/split_here.png", 324.0f * scale, 272.0f * scale);
	Object split = createObject("content/Student/split.png", 324.0f * scale, 272.0f * scale);
	Object left = createObject("content/Staff/Class/Asset 57.png", 492.0f * scale, 644.0f * scale);
	Object left_valid = createObject("content/Staff/Class/Asset 55.png", 492.0f * scale, 644.0f * scale);
	Object left_here = createObject("content/Staff/Class/Asset 91.png", 492.0f * scale, 644.0f * scale);
	Object right = createObject("content/Staff/Class/Asset 56.png", 510.0f * scale, 644.0f * scale);
	Object right_here = createObject("content/Staff/Class/Asset 90.png", 510.0f * scale, 644.0f * scale);
	Object right_valid = createObject("content/Staff/Class/Asset 54.png", 510.0f * scale, 644.0f * scale);
	Info sub_header = createInfo("content/VNI-Vari.TTF", course->course.course_name, 160.0f * scale, 158.0f * scale, 28.0f * scale);
	Object export_success = createObject("content/Staff/Create elements/Asset 115.png", 316.0f * scale, 386.0f * scale);
	Object return1 = createObject("content/Staff/Create elements/a7.png", 444.0f * scale, 484.0f * scale);
	Object return1_here = createObject("content/Staff/Create elements/b7.png", 444.0f * scale, 484.0f * scale);
	sub_header.text.setFillColor(Color(101, 159, 235));
	Info header = createInfo("content/VNI-Vari.TTF", course->course.course_id, 160.0f * scale, 200.0f * scale, 43.0f * scale);
	Info *inf[8][6];
	for (int i = 0; i < 8; i++)
	{
		inf[i][0] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 184.0f * scale, (370.0f + 30.0f * i) * scale, 17.5f * scale);
		inf[i][1] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 232.0f * scale, (370.0f + 30.0f * i) * scale, 17.5f * scale);
		inf[i][2] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 347.0f * scale, (370.0f + 30.0f * i) * scale, 17.5f * scale);
		inf[i][3] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 515.0f * scale, (370.0f + 30.0f * i) * scale, 17.5f * scale);
		inf[i][4] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 633.0f * scale, (370.0f + 30.0f * i) * scale, 17.5f * scale);
		inf[i][5] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 715.0f * scale, (370.0f + 30.0f * i) * scale, 17.5f * scale);
		for (int j = 0; j < 6; j++)
			inf[i][j]->text.setFillColor(Color::Black);
	}
	int count = 0, change = 0;
	bool trigger_page = true, export_done = false;
	count = countStudentNode(course->student_list);
	Info count_student = createInfo("content/Oswald-Regular.ttf", "Total: " + to_string(count) + " Students", 181.0f * scale, 280.0f * scale, 15.0f * scale);
	count_student.text.setFillColor(Color::White);
	while (window.isOpen() && page == 10)
	{
		Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
			{
				window.close();
				break;
			}
			case Event::MouseButtonReleased:
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					switchPage(out.bound, mouse, 1, page);
					switchPage(back.bound, mouse, 9, page);
					if (k == 1)
						switchPage(split.bound, mouse, 11, page);
					if (isHere(right.bound, mouse) && change <= count - 8)
					{
						trigger_page = true;
						change += 8;
					}
					if (isHere(left.bound, mouse) && change != 0)
					{
						trigger_page = true;
						change -= 8;
					}
					if (isHere(export1.bound, mouse))
					{
						string exported_student = "./csv/exported/" + course->course.course_id + "_" + course->course.teacher_name + ".csv";
						ofstream fout;
						fout.open(exported_student);
						writeToFileStudentNode(fout, course->student_list);
						fout.close();
						export_done = true;
					}
					if (isHere(return1.bound, mouse))
						export_done = false;
				}
				break;
			}
			default:
				break;
			}
		}

		window.clear();
		window.draw(screen.draw);
		drawWhich(window, out_here, out, mouse);
		drawWhich(window, back_here, back, mouse);
		drawWhich(window, export1_here, export1, mouse);
		if (k == 1)
			drawWhich(window, split_here, split, mouse);
		window.draw(header.text);
		window.draw(sub_header.text);
		window.draw(count_student.text);
		if (change == 0 && change >= count - 8)
		{
			window.draw(right.draw);
			window.draw(left.draw);
		}
		else if (change == 0)
		{
			window.draw(left.draw);
			drawWhich(window, right_here, right_valid, mouse);
		}
		else if (change >= count - 8)
		{
			window.draw(right.draw);
			drawWhich(window, left_here, left_valid, mouse);
		}
		else
		{
			drawWhich(window, right_here, right_valid, mouse);
			drawWhich(window, left_here, left_valid, mouse);
		}
		if (trigger_page)
		{
			StudentNode *cur = course->student_list;
			for (int i = 0; i < change; i++)
			{
				cur = cur->next;
			}
			for (int i = 0; i < 8; i++)
			{
				if (cur)
				{
					inf[i][0]->text.setString(to_string(cur->student.num));
					inf[i][1]->text.setString(cur->student.student_id);
					inf[i][2]->text.setString(cur->student.last_name + " " + cur->student.first_name);
					inf[i][4]->text.setString(cur->student.gender ? "F" : "M");
					inf[i][3]->text.setString(cur->student.dob);
					inf[i][5]->text.setString(cur->student.social_id);
					cur = cur->next;
				}
				else
				{
					for (int j = 0; j < 6; j++)
						inf[i][j]->text.setString("");
				}
			}
			trigger_page = false;
		}
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 6; j++)
				window.draw(inf[i][j]->text);
		}
		if (export_done)
		{
			window.draw(export_success.draw);
			drawWhich(window, return1_here, return1, mouse);
		}
		window.display();
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 6; j++)
			delete inf[i][j];
	}
}

void course_student2(RenderWindow &window, int &page, const float &scale, CourseNode *course, ClassNode *all_class)
{
	Event event;
	Object export1 = createObject("content/Staff/Create elements/export.png", 680.0f * scale, 272.0f * scale);
	Object export1_here = createObject("content/Staff/Create elements/export_here.png", 680.0f * scale, 272.0f * scale);
	Object screen = createObject("content/Student/my_class2.png");
	Object out = createObject("content/logout.png", 866.0f * scale, 106.0f * scale);
	Object out_here = createObject("content/logout1.png", 866.0f * scale, 106.0f * scale);
	Object back = createObject("content/return.png", 80.0f * scale, 106.0f * scale);
	Object back_here = createObject("content/return1.png", 80.0f * scale, 106.0f * scale);
	Object split_here = createObject("content/Student/total_here.png", 324.0f * scale, 272.0f * scale);
	Object split = createObject("content/Student/total.png", 324.0f * scale, 272.0f * scale);
	Object left = createObject("content/Staff/Class/Asset 57.png", 492.0f * scale, 644.0f * scale);
	Object left_valid = createObject("content/Staff/Class/Asset 55.png", 492.0f * scale, 644.0f * scale);
	Object left_here = createObject("content/Staff/Class/Asset 91.png", 492.0f * scale, 644.0f * scale);
	Object right = createObject("content/Staff/Class/Asset 56.png", 510.0f * scale, 644.0f * scale);
	Object right_here = createObject("content/Staff/Class/Asset 90.png", 510.0f * scale, 644.0f * scale);
	Object right_valid = createObject("content/Staff/Class/Asset 54.png", 510.0f * scale, 644.0f * scale);
	Info sub_header = createInfo("content/VNI-Vari.TTF", course->course.course_name, 160.0f * scale, 158.0f * scale, 28.0f * scale);
	Object export_success = createObject("content/Staff/Create elements/Asset 115.png", 316.0f * scale, 386.0f * scale);
	Object return1 = createObject("content/Staff/Create elements/a7.png", 444.0f * scale, 484.0f * scale);
	Object return1_here = createObject("content/Staff/Create elements/b7.png", 444.0f * scale, 484.0f * scale);
	sub_header.text.setFillColor(Color(101, 159, 235));
	Info header = createInfo("content/VNI-Vari.TTF", course->course.course_id, 160.0f * scale, 200.0f * scale, 43.0f * scale);
	Info *inf[8][7];
	for (int i = 0; i < 8; i++)
	{
		inf[i][0] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 184.0f * scale, (370.0f + 30.0f * i) * scale, 17.5f * scale);
		inf[i][1] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 232.0f * scale, (370.0f + 30.0f * i) * scale, 17.5f * scale);
		inf[i][2] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 347.0f * scale, (370.0f + 30.0f * i) * scale, 17.5f * scale);
		inf[i][3] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 578.0f * scale, (370.0f + 30.0f * i) * scale, 17.5f * scale);
		inf[i][4] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 650.0f * scale, (370.0f + 30.0f * i) * scale, 17.5f * scale);
		inf[i][5] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 720.0f * scale, (370.0f + 30.0f * i) * scale, 17.5f * scale);
		inf[i][6] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 774.0f * scale, (370.0f + 30.0f * i) * scale, 17.5f * scale);
		for (int j = 0; j < 7; j++)
			inf[i][j]->text.setFillColor(Color::Black);
	}
	int count = 0, change = 0;
	bool trigger_page = true, export_done = false;
	for (StudentNode *cur = course->student_list; cur; cur = cur->next)
	{
		count++;
	}
	Info count_student = createInfo("content/Oswald-Regular.ttf", "Total: " + to_string(count) + " Students", 181.0f * scale, 280.0f * scale, 15.0f * scale);
	count_student.text.setFillColor(Color::White);
	while (window.isOpen() && page == 11)
	{
		Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
			{
				window.close();
				break;
			}
			case Event::MouseButtonReleased:
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					switchPage(out.bound, mouse, 1, page);
					switchPage(back.bound, mouse, 9, page);
					switchPage(split.bound, mouse, 10, page);
					if (isHere(right.bound, mouse) && change <= count - 8)
					{
						trigger_page = true;
						change += 8;
					}
					if (isHere(left.bound, mouse) && change != 0)
					{
						trigger_page = true;
						change -= 8;
					}
					if (isHere(export1.bound, mouse))
					{
						string exported_student = "./csv/exported/" + course->course.course_id + "_" + course->course.teacher_name + ".csv";
						ofstream fout;
						fout.open(exported_student);
						writeToFileStudentNode(fout, course->student_list);
						fout.close();
						export_done = true;
					}
					if (isHere(return1.bound, mouse))
						export_done = false;
				}
				break;
			}
			default:
				break;
			}
		}

		window.clear();
		window.draw(screen.draw);
		drawWhich(window, out_here, out, mouse);
		drawWhich(window, back_here, back, mouse);
		drawWhich(window, export1_here, export1, mouse);
		drawWhich(window, split_here, split, mouse);
		window.draw(header.text);
		window.draw(sub_header.text);
		window.draw(count_student.text);
		if (change == 0 && change >= count - 8)
		{
			window.draw(right.draw);
			window.draw(left.draw);
		}
		else if (change == 0)
		{
			window.draw(left.draw);
			drawWhich(window, right_here, right_valid, mouse);
		}
		else if (change >= count - 8)
		{
			window.draw(right.draw);
			drawWhich(window, left_here, left_valid, mouse);
		}
		else
		{
			drawWhich(window, right_here, right_valid, mouse);
			drawWhich(window, left_here, left_valid, mouse);
		}
		if (trigger_page)
		{
			StudentNode *cur = course->student_list;
			for (int i = 0; i < change; i++)
			{
				cur = cur->next;
			}
			for (int i = 0; i < 8; i++)
			{
				if (cur)
				{
					inf[i][0]->text.setString(to_string(cur->student.num));
					inf[i][1]->text.setString(cur->student.student_id);
					inf[i][2]->text.setString(cur->student.last_name + " " + cur->student.first_name);
					ClassNode *find_class = searchClassNode(all_class, cur->student.student_class);
					StudentNode *tmp = searchStudentNode(find_class->my_class.student_list, cur->student.student_id);
					MyCourse *current = searchMyCourse(tmp, course);
					stringstream a, b, c, d;
					a << fixed << setprecision(1) << current->score.process;
					b << fixed << setprecision(1) << current->score.mid;
					c << fixed << setprecision(1) << current->score.fin;
					d << fixed << setprecision(1) << current->score.overall;
					inf[i][3]->text.setString(a.str());
					inf[i][4]->text.setString(b.str());
					inf[i][5]->text.setString(c.str());
					inf[i][6]->text.setString(d.str());

					cur = cur->next;
				}
				else
				{
					for (int j = 0; j < 7; j++)
						inf[i][j]->text.setString("");
				}
			}
			trigger_page = false;
		}
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 7; j++)
				window.draw(inf[i][j]->text);
		}
		if (export_done)
		{
			window.draw(export_success.draw);
			drawWhich(window, return1_here, return1, mouse);
		}
		window.display();
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 7; j++)
			delete inf[i][j];
	}
}

void view_year(RenderWindow &window, int &page, const float &scale, YearNode *year, StudentNode *user, const bool &is_staff, ClassNode *all_class)
{
	YearNode *cur_year = year;
	Event event;
	Object *screen;
	if (is_staff)
		screen = createObjectTest("content/year_staff.png");
	else
	{
		MyCourse *cur = user->student.my_course;
		while (cur && cur_year && cur_year->school_year.year_id != cur->year)
			cur_year = cur_year->next;
		screen = createObjectTest("content/year.png");
		if (!cur)
			cur_year = nullptr;
	}
	Object out = createObject("content/logout.png", 866.0f * scale, 106.0f * scale);
	Object out_here = createObject("content/logout1.png", 866.0f * scale, 106.0f * scale);
	Object back = createObject("content/return.png", 80.0f * scale, 106.0f * scale);
	Object back_here = createObject("content/return1.png", 80.0f * scale, 106.0f * scale);
	Object add_year = createObject("content/add_year.png", 680.0f * scale, 274.0f * scale);
	Object add_year_here = createObject("content/add_year_here.png", 680.0f * scale, 274.0f * scale);
	Object left = createObject("content/Staff/Class/Asset 57.png", 492.0f * scale, 644.0f * scale);
	Object left_valid = createObject("content/Staff/Class/Asset 55.png", 492.0f * scale, 644.0f * scale);
	Object left_here = createObject("content/Staff/Class/Asset 91.png", 492.0f * scale, 644.0f * scale);
	Object right = createObject("content/Staff/Class/Asset 56.png", 510.0f * scale, 644.0f * scale);
	Object right_here = createObject("content/Staff/Class/Asset 90.png", 510.0f * scale, 644.0f * scale);
	Object right_valid = createObject("content/Staff/Class/Asset 54.png", 510.0f * scale, 644.0f * scale);
	Info *inf[4];
	Object *square[4], *square_here[4];
	YearNode *a_year[4];
	for (int i = 0; i < 4; i++)
	{
		a_year[i] = nullptr;
		square[i] = createObjectTest("content/year_node.png", 266.0f * scale, (328.0f + 78.0f * i) * scale);
		square_here[i] = createObjectTest("content/year_node_here.png", 266.0f * scale, (328.0f + 78.0f * i) * scale);
		inf[i] = createInfoTest("content/Oswald-Medium.ttf", "demo_text", (243.0f + 220.0f * i) * scale, 330.0f * scale, 25.0f * scale);
	}
	int count = 0, change = 0;
	bool trigger_page = true;
	for (YearNode *cur = cur_year; cur; cur = cur->next)
		count++;
	Info count_course = createInfo("content/Oswald-Regular.ttf", "Total: " + to_string(count) + " Years", 200.0f * scale, 279.0f * scale, 15.0f * scale);
	count_course.text.setFillColor(Color::White);
	while (window.isOpen() && page == 7)
	{
		Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
			{
				window.close();
				break;
			}
			case Event::MouseButtonReleased:
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					switchPage(out.bound, mouse, 1, page);
					switchPage(back.bound, mouse, (is_staff ? 4 : 3), page);
					if (isHere(add_year.bound, mouse) && is_staff)
					{
						YearNode *cur = year;
						string s;
						if (!cur)
							s = "2021-2022";
						else
						{
							while (cur->next)
								cur = cur->next;
							s = cur->school_year.year_id;
							stringstream input(s);
							int year1, year2;
							char junk;
							input >> year1 >> junk >> year2;
							s = to_string(year1 + 1) + "-" + to_string(year2 + 1);
						}
						Year new_year = createYear(s);
						new_year.list_sem = nullptr;
						for (int i = 1; i < 4; i++)
						{
							Semester new_sem = createSemester("Semester " + to_string(i));
							new_sem.course_list = nullptr;
							appendNewSemesterNode(&new_year.list_sem, new_sem);
						}
						appendNewYearNode(&year, new_year);
						count++;
						count_course.text.setString("Total: " + to_string(count) + " Years");
						trigger_page = true;
					}
					if (isHere(right.bound, mouse) && change <= count - 4)
					{
						trigger_page = true;
						change += 4;
					}
					if (isHere(left.bound, mouse) && change != 0)
					{
						trigger_page = true;
						change -= 4;
					}
					for (int i = 0; i < 4; i++)
					{
						if (isHere(square[i]->bound, mouse) && a_year[i])
						{
							page = 8;
							view_semester(window, page, scale, a_year[i], user, is_staff, all_class);
						}
					}
				}
				break;
			}
			default:
				break;
			}
		}

		window.clear();
		window.draw(screen->draw);
		if (is_staff)
			drawWhich(window, add_year_here, add_year, mouse);
		drawWhich(window, out_here, out, mouse);
		drawWhich(window, back_here, back, mouse);
		window.draw(count_course.text);
		if (change == 0 && change >= count - 4)
		{
			window.draw(right.draw);
			window.draw(left.draw);
		}
		else if (change == 0)
		{
			window.draw(left.draw);
			drawWhich(window, right_here, right_valid, mouse);
		}
		else if (change >= count - 4)
		{
			window.draw(right.draw);
			drawWhich(window, left_here, left_valid, mouse);
		}
		else
		{
			drawWhich(window, right_here, right_valid, mouse);
			drawWhich(window, left_here, left_valid, mouse);
		}
		if (trigger_page)
		{
			YearNode *cur = cur_year;
			for (int i = 0; i < change; i++)
			{
				cur = cur->next;
			}
			for (int i = 0; i < 4; i++)
			{
				a_year[i] = cur;
				if (cur)
				{
					inf[i]->text.setString(a_year[i]->school_year.year_id);
					inf[i]->text.setPosition(Vector2f(square[i]->bound.left + (square[i]->bound.width - inf[i]->text.getGlobalBounds().width) / 2, square[i]->bound.top + 20.0f));
					cur = cur->next;
				}
				else
				{
					inf[i]->text.setString("");
				}
			}
			trigger_page = false;
		}
		for (int i = 0; i < 4; i++)
		{
			if (inf[i]->text.getString() == "")
				break;
			if (drawWhich(window, square_here[i], square[i], mouse))
				inf[i]->text.setFillColor(Color(118, 36, 2));
			else
				inf[i]->text.setFillColor(Color(46, 68, 112));
			window.draw(inf[i]->text);
		}
		window.display();
	}
	for (int i = 0; i < 4; i++)
	{
		delete square[i], square_here[i], inf[i];
	}
	delete screen;
}

void view_semester(RenderWindow &window, int &page, const float &scale, YearNode *cur_year, StudentNode *user, const bool &is_staff, ClassNode *all_class)
{
	Event event;
	Object *screen = createObjectTest("content/Staff/Class/semester.png");
	Object out = createObject("content/logout.png", 866.0f * scale, 106.0f * scale);
	Object out_here = createObject("content/logout1.png", 866.0f * scale, 106.0f * scale);
	Object back = createObject("content/return.png", 80.0f * scale, 106.0f * scale);
	Object back_here = createObject("content/return1.png", 80.0f * scale, 106.0f * scale);
	Info sub_header = createInfo("content/VNI-Vari.TTF", cur_year->school_year.year_id, 160.0f * scale, 158.0f * scale, 28.0f * scale);
	sub_header.text.setFillColor(Color(101, 159, 235));
	Info header = createInfo("content/VNI-Vari.TTF", "Semester List", 160.0f * scale, 200.0f * scale, 43.0f * scale);
	Object *square[3], *square_here[3];
	SemesterNode *a_sem[3];
	for (int i = 0; i < 3; i++)
	{
		a_sem[i] = nullptr;
		square[i] = createObjectTest("content/Student/Asset " + to_string(104 + i) + ".png", (172.0f + 226.0f * i) * scale, 368.0f * scale);
		square_here[i] = createObjectTest("content/Student/Asset " + to_string(107 + i) + ".png", (172.0f + 226.0f * i) * scale, 368.0f * scale);
	}
	int count = 0, change = 0;
	bool trigger_page = true;
	for (SemesterNode *cur = cur_year->school_year.list_sem; cur; cur = cur->next)
		count++;
	Info count_course = createInfo("content/Oswald-Regular.ttf", "Total: " + to_string(count) + " Semesters", 190.0f * scale, 279.0f * scale, 15.0f * scale);
	count_course.text.setFillColor(Color::White);
	while (window.isOpen() && page == 8)
	{
		Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
			{
				window.close();
				break;
			}
			case Event::MouseButtonReleased:
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					switchPage(out.bound, mouse, 1, page);
					switchPage(back.bound, mouse, 7, page);
					for (int i = 0; i < 3; i++)
					{
						if (isHere(square[i]->bound, mouse) && a_sem[i])
						{
							page = 9;
							string year = cur_year->school_year.year_id;
							string sem = a_sem[i]->sem.semester_id;
							if (is_staff)
								view_course(window, page, scale, a_sem[i]->sem.course_list, is_staff, all_class, year, sem);
							else
								view_course(window, page, scale, user, is_staff, sem, year);
						}
					}
				}
				break;
			}
			default:
				break;
			}
		}

		window.clear();
		window.draw(screen->draw);
		window.draw(count_course.text);
		window.draw(header.text);
		window.draw(sub_header.text);
		drawWhich(window, out_here, out, mouse);
		drawWhich(window, back_here, back, mouse);
		if (trigger_page)
		{
			SemesterNode *cur = cur_year->school_year.list_sem;
			for (int i = 0; i < 3; i++)
			{
				a_sem[i] = cur;
				if (cur)
					cur = cur->next;
			}
			trigger_page = false;
		}
		for (int i = 0; i < 3; i++)
			drawWhich(window, square_here[i], square[i], mouse);
		window.display();
	}
	for (int i = 0; i < 3; i++)
	{
		delete square[i], square_here[i];
	}
	delete screen;
}

void view_score(RenderWindow &window, int &page, const float &scale, StudentNode *user, const bool &is_staff)
{
	Event event;
	Object split_here = createObject("content/Student/split_here.png", 324.0f * scale, 272.0f * scale);
	Object split = createObject("content/Student/split.png", 324.0f * scale, 272.0f * scale);
	Object screen = createObject("content/score.png");
	Object out = createObject("content/logout.png", 866.0f * scale, 106.0f * scale);
	Object out_here = createObject("content/logout1.png", 866.0f * scale, 106.0f * scale);
	Object back = createObject("content/return.png", 80.0f * scale, 106.0f * scale);
	Object back_here = createObject("content/return1.png", 80.0f * scale, 106.0f * scale);
	Object left = createObject("content/Staff/Class/Asset 57.png", 492.0f * scale, 644.0f * scale);
	Object left_valid = createObject("content/Staff/Class/Asset 55.png", 492.0f * scale, 644.0f * scale);
	Object left_here = createObject("content/Staff/Class/Asset 91.png", 492.0f * scale, 644.0f * scale);
	Object right = createObject("content/Staff/Class/Asset 56.png", 510.0f * scale, 644.0f * scale);
	Object right_here = createObject("content/Staff/Class/Asset 90.png", 510.0f * scale, 644.0f * scale);
	Object right_valid = createObject("content/Staff/Class/Asset 54.png", 510.0f * scale, 644.0f * scale);
	Info sub_header = createInfo("content/VNI-Vari.TTF", user->student.last_name + " " + user->student.first_name, 160.0f * scale, 158.0f * scale, 28.0f * scale);
	sub_header.text.setFillColor(Color(101, 159, 235));
	Info header = createInfo("content/VNI-Vari.TTF", "My Score", 160.0f * scale, 200.0f * scale, 43.0f * scale);
	Info *inf[8][7];
	for (int i = 0; i < 8; i++)
	{
		inf[i][0] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 184.0f * scale, (370.0f + 30.0f * i) * scale, 17.5f * scale);
		inf[i][1] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 224.0f * scale, (370.0f + 30.0f * i) * scale, 17.5f * scale);
		inf[i][2] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 338.0f * scale, (370.0f + 30.0f * i) * scale, 17.5f * scale);
		inf[i][3] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 578.0f * scale, (370.0f + 30.0f * i) * scale, 17.5f * scale);
		inf[i][4] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 650.0f * scale, (370.0f + 30.0f * i) * scale, 17.5f * scale);
		inf[i][5] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 720.0f * scale, (370.0f + 30.0f * i) * scale, 17.5f * scale);
		inf[i][6] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 774.0f * scale, (370.0f + 30.0f * i) * scale, 17.5f * scale);
		for (int j = 0; j < 7; j++)
			inf[i][j]->text.setFillColor(Color::Black);
	}
	int count = 0, change = 0, count_course = 0;
	float count_gpa = 0.0f;
	bool trigger_page = true;
	for (MyCourse *cur = user->student.my_course; cur; cur = cur->next)
	{
		count += cur->course->course.num_credit;
		count_gpa += cur->score.overall;
		count_course++;
	}
	float k = 0.0f;
	if (count_course != 0)
		k = count_gpa / (float)count_course;
	user->student.total_gpa = k;
	stringstream gpa;
	gpa << fixed << setprecision(1) << k;
	Info gpa_here = createInfo("content/Oswald-Regular.ttf", "GPA: " + gpa.str(), 460.0f * scale, 280.0f * scale, 15.0f * scale);
	Info count_student = createInfo("content/Oswald-Regular.ttf", "Total: " + to_string(count) + " Credits", 181.0f * scale, 280.0f * scale, 15.0f * scale);
	count_student.text.setFillColor(Color::White);
	while (window.isOpen() && page == 8)
	{
		Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
			{
				window.close();
				break;
			}
			case Event::MouseButtonReleased:
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					switchPage(out.bound, mouse, 1, page);
					// is_staff: true -> switch to the class
					switchPage(back.bound, mouse, 3, page);
					if (user->student.my_course)
						switchPage(split.bound, mouse, 9, page);
					if (isHere(right.bound, mouse) && change <= count_course - 8)
					{
						trigger_page = true;
						change += 8;
					}
					if (isHere(left.bound, mouse) && change != 0)
					{
						trigger_page = true;
						change -= 8;
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
		drawWhich(window, out_here, out, mouse);
		drawWhich(window, back_here, back, mouse);
		if (user->student.my_course)
			drawWhich(window, split_here, split, mouse);
		window.draw(header.text);
		window.draw(sub_header.text);
		window.draw(count_student.text);
		window.draw(gpa_here.text);
		if (change == 0 && change >= count_course - 8)
		{
			window.draw(right.draw);
			window.draw(left.draw);
		}
		else if (change == 0)
		{
			window.draw(left.draw);
			drawWhich(window, right_here, right_valid, mouse);
		}
		else if (change >= count_course - 8)
		{
			window.draw(right.draw);
			drawWhich(window, left_here, left_valid, mouse);
		}
		else
		{
			drawWhich(window, right_here, right_valid, mouse);
			drawWhich(window, left_here, left_valid, mouse);
		}
		if (trigger_page)
		{
			MyCourse *cur = user->student.my_course;
			for (int i = 0; i < change; i++)
			{
				cur = cur->next;
			}
			for (int i = 0; i < 8; i++)
			{
				if (cur)
				{
					stringstream a, b, c, d;
					a << fixed << setprecision(1) << cur->score.process;
					b << fixed << setprecision(1) << cur->score.mid;
					c << fixed << setprecision(1) << cur->score.fin;
					d << fixed << setprecision(1) << cur->score.overall;
					inf[i][0]->text.setString(to_string(i + change + 1));
					inf[i][1]->text.setString(cur->subject_code);
					inf[i][2]->text.setString(cur->course->course.course_name);
					inf[i][3]->text.setString(a.str());
					inf[i][4]->text.setString(b.str());
					inf[i][5]->text.setString(c.str());
					inf[i][6]->text.setString(d.str());
					cur = cur->next;
				}
				else
				{
					for (int j = 0; j < 7; j++)
						inf[i][j]->text.setString("");
				}
			}
			trigger_page = false;
		}
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 7; j++)
				window.draw(inf[i][j]->text);
		}
		window.display();
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 7; j++)
			delete inf[i][j];
	}
}

void view_score2(RenderWindow &window, int &page, const float &scale, StudentNode *user, const bool &is_staff)
{
	Event event;
	Object screen = createObject("content/score.png");
	Object out = createObject("content/logout.png", 866.0f * scale, 106.0f * scale);
	Object out_here = createObject("content/logout1.png", 866.0f * scale, 106.0f * scale);
	Object back = createObject("content/return.png", 80.0f * scale, 106.0f * scale);
	Object back_here = createObject("content/return1.png", 80.0f * scale, 106.0f * scale);
	Object split_here = createObject("content/Student/total_here.png", 324.0f * scale, 272.0f * scale);
	Object split = createObject("content/Student/total.png", 324.0f * scale, 272.0f * scale);
	Object *pre[6], *next[6];
	for (int i = 0; i < 6; i++)
	{
		pre[i] = createObjectTest("content/Student/Asset " + to_string(126 + i) + ".png", 552.0f * scale, 274.0f * scale);
		next[i] = createObjectTest("content/Student/Asset " + to_string(132 + i) + ".png", 702.0f * scale, 274.0f * scale);
	}
	Info sub_header = createInfo("content/VNI-Vari.TTF", user->student.last_name + " " + user->student.first_name, 160.0f * scale, 158.0f * scale, 28.0f * scale);
	sub_header.text.setFillColor(Color(101, 159, 235));
	Info header = createInfo("content/VNI-Vari.TTF", user->student.my_course->year + " " + user->student.my_course->sem, 160.0f * scale, 200.0f * scale, 43.0f * scale);
	Info *inf[8][7];
	for (int i = 0; i < 8; i++)
	{
		inf[i][0] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 184.0f * scale, (370.0f + 30.0f * i) * scale, 17.5f * scale);
		inf[i][1] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 224.0f * scale, (370.0f + 30.0f * i) * scale, 17.5f * scale);
		inf[i][2] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 338.0f * scale, (370.0f + 30.0f * i) * scale, 17.5f * scale);
		inf[i][3] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 578.0f * scale, (370.0f + 30.0f * i) * scale, 17.5f * scale);
		inf[i][4] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 650.0f * scale, (370.0f + 30.0f * i) * scale, 17.5f * scale);
		inf[i][5] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 720.0f * scale, (370.0f + 30.0f * i) * scale, 17.5f * scale);
		inf[i][6] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 774.0f * scale, (370.0f + 30.0f * i) * scale, 17.5f * scale);
		for (int j = 0; j < 7; j++)
			inf[i][j]->text.setFillColor(Color::Black);
	}
	int count = 0, sub_page = 0, change = 1, count_course = 0;
	string sem = "", year = "";
	bool trigger_page = true;
	float gpa_count = 0.0f, k;
	for (MyCourse *cur = user->student.my_course; cur; cur = cur->next)
	{
		if (cur->sem != sem || cur->year != year)
		{
			sem = cur->sem;
			year = cur->year;
			sub_page++;
		}
	}
	sem = user->student.my_course->sem;
	year = user->student.my_course->year;
	Info count_student = createInfo("content/Oswald-Regular.ttf", "Total: 0 Credits", 181.0f * scale, 280.0f * scale, 15.0f * scale);
	Info gpa_here = createInfo("content/Oswald-Regular.ttf", "GPA:", 460.0f * scale, 280.0f * scale, 15.0f * scale);
	count_student.text.setFillColor(Color::White);
	while (window.isOpen() && page == 9)
	{
		Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
			{
				window.close();
				break;
			}
			case Event::MouseButtonReleased:
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					switchPage(out.bound, mouse, 1, page);
					// is_staff: true -> switch to the class
					switchPage(back.bound, mouse, 3, page);
					switchPage(split.bound, mouse, 8, page);
					if (isHere(next[0]->bound, mouse) && change < sub_page)
					{
						trigger_page = true;
						change++;
					}
					if (isHere(pre[0]->bound, mouse) && change != 1)
					{
						trigger_page = true;
						change--;
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
		drawWhich(window, out_here, out, mouse);
		drawWhich(window, back_here, back, mouse);
		drawWhich(window, split_here, split, mouse);
		window.draw(header.text);
		window.draw(sub_header.text);
		window.draw(count_student.text);
		window.draw(gpa_here.text);
		if (change == 1)
		{
			if (change == sub_page)
			{
				window.draw(pre[3]->draw);
				window.draw(next[3]->draw);
			}
			else
			{
				window.draw(pre[3]->draw);
				drawWhich(window, next[1], next[2], mouse);
			}
		}
		else if (change == sub_page)
		{
			window.draw(next[3]->draw);
			drawWhich(window, pre[1], pre[2], mouse);
		}
		else if (sem == "Semester 3")
		{
			drawWhich(window, pre[1], pre[2], mouse);
			drawWhich(window, next[4], next[5], mouse);
		}
		else if (sem == "Semester 1")
		{
			drawWhich(window, pre[4], pre[5], mouse);
			drawWhich(window, next[1], next[2], mouse);
		}
		else
		{
			drawWhich(window, pre[1], pre[2], mouse);
			drawWhich(window, next[1], next[2], mouse);
		}
		if (trigger_page)
		{
			gpa_count = 0.0f;
			count_course = 0;
			MyCourse *cur = user->student.my_course;
			for (int i = 0; i < change - 1; i++)
			{
				sem = cur->sem;
				year = cur->year;
				while (cur->sem == sem && cur->year == year)
					cur = cur->next;
			}
			sem = cur->sem;
			year = cur->year;
			header.text.setString(year + " " + sem);
			count = 0;
			for (int i = 0; i < 8; i++)
			{
				if (cur && cur->sem == sem && cur->year == year)
				{
					stringstream a, b, c, d;
					a << fixed << setprecision(1) << cur->score.process;
					b << fixed << setprecision(1) << cur->score.mid;
					c << fixed << setprecision(1) << cur->score.fin;
					d << fixed << setprecision(1) << cur->score.overall;
					inf[i][0]->text.setString(to_string(i + 1));
					inf[i][1]->text.setString(cur->subject_code);
					inf[i][2]->text.setString(cur->course->course.course_name);
					inf[i][3]->text.setString(a.str());
					inf[i][4]->text.setString(b.str());
					inf[i][5]->text.setString(c.str());
					inf[i][6]->text.setString(d.str());
					count += cur->course->course.num_credit;
					gpa_count += cur->score.overall;
					count_course++;
					cur = cur->next;
				}
				else
				{
					for (int j = 0; j < 7; j++)
						inf[i][j]->text.setString("");
				}
			}
			if (!count_course)
				k = 0.0f;
			else
				k = gpa_count / (float)count_course;
			stringstream gpa;
			gpa << fixed << setprecision(1) << k;
			count_student.text.setString("Total: " + to_string(count) + " Credits");
			gpa_here.text.setString("GPA: " + gpa.str());
			trigger_page = false;
		}
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 7; j++)
				window.draw(inf[i][j]->text);
		}
		window.display();
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 7; j++)
			delete inf[i][j];
	}
	for (int i = 0; i < 6; i++)
		delete pre[i], next[i];
}

bool add_new_course(RenderWindow &window, int &page, const float &scale, CourseNode *&course, const string &year, const string &sem)
{
	Info *inf[9];
	for (int i = 0; i < 9; i++)
		inf[i] = createInfoTest("content/Oswald-Light.ttf", "Add text", 308.0f * scale, (303.0f + 56.0f * i) * scale, 20.0f * scale);
	changePos(inf[6], 626.0f * scale, (303.0f + 56.0f * 3) * scale);
	changePos(inf[7], 550.0f * scale, (303.0f + 56.0f * 4) * scale);
	changePos(inf[8], 550.0f * scale, (303.0f + 56.0f * 5) * scale);
	inf[6]->s = "50";
	inf[6]->text.setString(inf[6]->s);
	Object back = createObject("content/return.png", 80.0f * scale, 106.0f * scale);
	Object back_here = createObject("content/return1.png", 80.0f * scale, 106.0f * scale);
	Object screen = createObject("content/Staff/Create elements/new course.png");
	Object change = createObject("content/General/change.png", 316.0f * scale, 386.0f * scale);
	Object out = createObject("content/logout.png", 866.0f * scale, 106.0f * scale);
	Object out_here = createObject("content/logout1.png", 866.0f * scale, 106.0f * scale);
	Object save = createObject("content/Staff/Create elements/save.png", 750.0f * scale, 580.0f * scale);
	Object save_here = createObject("content/Staff/Create elements/save_here.png", 750.0f * scale, 580.0f * scale);
	Info sub_header = createInfo("content/VNI-Vari.TTF", year + " - " + sem, 160.0f * scale, 158.0f * scale, 28.0f * scale);
	sub_header.text.setFillColor(Color(101, 159, 235));
	Info header = createInfo("content/VNI-Vari.TTF", "Create New Course", 160.0f * scale, 200.0f * scale, 43.0f * scale);
	Object success = createObject("content/Staff/Create elements/Asset 115.png", 316.0f * scale, 386.0f * scale);
	Object fail = createObject("content/Staff/Create elements/Asset 114.png", 316.0f * scale, 386.0f * scale);
	Object return1 = createObject("content/Staff/Create elements/a7.png", 444.0f * scale, 484.0f * scale);
	Object return1_here = createObject("content/Staff/Create elements/b7.png", 444.0f * scale, 484.0f * scale);
	Object ok = createObject("content/Staff/Create elements/a1.png", 444.0f * scale, 484.0f * scale);
	Object ok_here = createObject("content/Staff/Create elements/b1.png", 444.0f * scale, 484.0f * scale);
	Event event;
	bool check_fail = false, check_success = false;
	while (window.isOpen() && page == 12)
	{
		Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
			{
				window.close();
				break;
			}
			case Event::MouseButtonReleased:
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					switchPage(out.bound, mouse, 1, page);
					switchPage(back.bound, mouse, 9, page);
					if (isHere(save.bound, mouse))
					{
						if (checkInputCourse(inf, 9, course))
							check_success = true;
						else
							check_fail = true;
					}
					if (check_success)
						switchPage(ok.bound, mouse, 9, page);
					if (check_fail && isHere(ok.bound, mouse))
						check_fail = false;
					for (int i = 0; i < 9; i++)
					{
						FloatRect check_me = inf[i]->text.getGlobalBounds();
						if (isHere(check_me, mouse))
							inf[i]->check = true;
						else
							inf[i]->check = false;
					}
				}
				break;
			case Event::TextEntered:
			{
				for (int i = 0; i < 3; i++)
					texting(inf[i], event.text.unicode, 40);
				texting(inf[3], event.text.unicode, 3);
				texting(inf[4], event.text.unicode, 4);
				texting(inf[5], event.text.unicode, 5);
				texting(inf[6], event.text.unicode, 5);
				texting(inf[7], event.text.unicode, 20);
				texting(inf[8], event.text.unicode, 20);
				break;
			}
			default:
			{
				break;
			}
			}
			}
		}
		window.clear();
		window.draw(screen.draw);
		window.draw(header.text);
		window.draw(sub_header.text);
		for (int i = 0; i < 9; i++)
			window.draw(inf[i]->text);
		if (check_fail)
		{
			window.draw(fail.draw);
			drawWhich(window, return1_here, return1, mouse);
		}
		if (check_success)
		{
			window.draw(success.draw);
			drawWhich(window, ok_here, ok, mouse);
		}
		drawWhich(window, save_here, save, mouse);
		drawWhich(window, out_here, out, mouse);
		drawWhich(window, back_here, back, mouse);
		window.display();
	}
	for (int i = 0; i < 9; i++)
		delete (inf[i]);
	if (check_success)
		return true;
	else
		return false;
}

bool change_course_info(RenderWindow &window, int &page, const float &scale, CourseNode *&course, const string &year, const string &sem)
{
	string s[9];
	s[0] = course->course.course_id;
	s[1] = course->course.course_name;
	s[2] = course->course.teacher_name;
	s[3] = to_string(course->course.num_credit);
	s[4] = day_convert(course->course.teaching_session[0]);
	s[5] = day_convert(course->course.teaching_session[1]);
	s[6] = to_string(course->course.max_students);
	s[7] = no_convert(course->course.teaching_session[0]);
	s[8] = no_convert(course->course.teaching_session[0]);
	Info *inf[9];
	for (int i = 0; i < 9; i++)
	{
		inf[i] = createInfoTest("content/Oswald-Light.ttf", s[i], 308.0f * scale, (303.0f + 56.0f * i) * scale, 20.0f * scale);
		inf[i]->s = s[i];
	}
	changePos(inf[6], 626.0f * scale, (303.0f + 56.0f * 3) * scale);
	changePos(inf[7], 550.0f * scale, (303.0f + 56.0f * 4) * scale);
	changePos(inf[8], 550.0f * scale, (303.0f + 56.0f * 5) * scale);
	Object back = createObject("content/return.png", 80.0f * scale, 106.0f * scale);
	Object back_here = createObject("content/return1.png", 80.0f * scale, 106.0f * scale);
	Object screen = createObject("content/Staff/Create elements/new course.png");
	Object change = createObject("content/General/change.png", 316.0f * scale, 386.0f * scale);
	Object out = createObject("content/logout.png", 866.0f * scale, 106.0f * scale);
	Object out_here = createObject("content/logout1.png", 866.0f * scale, 106.0f * scale);
	Object save = createObject("content/Staff/Create elements/save.png", 750.0f * scale, 580.0f * scale);
	Object save_here = createObject("content/Staff/Create elements/save_here.png", 750.0f * scale, 580.0f * scale);
	Info sub_header = createInfo("content/VNI-Vari.TTF", year + " - " + sem, 160.0f * scale, 158.0f * scale, 28.0f * scale);
	sub_header.text.setFillColor(Color(101, 159, 235));
	Info header = createInfo("content/VNI-Vari.TTF", "Course Information", 160.0f * scale, 200.0f * scale, 43.0f * scale);
	Object success = createObject("content/Staff/Create elements/Asset 115.png", 316.0f * scale, 386.0f * scale);
	Object fail = createObject("content/Staff/Create elements/Asset 114.png", 316.0f * scale, 386.0f * scale);
	Object return1 = createObject("content/Staff/Create elements/a7.png", 444.0f * scale, 484.0f * scale);
	Object return1_here = createObject("content/Staff/Create elements/b7.png", 444.0f * scale, 484.0f * scale);
	Object ok = createObject("content/Staff/Create elements/a1.png", 444.0f * scale, 484.0f * scale);
	Object ok_here = createObject("content/Staff/Create elements/b1.png", 444.0f * scale, 484.0f * scale);
	Event event;
	bool check_fail = false, check_success = false, check = false;
	while (window.isOpen() && page == 12)
	{
		Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
			{
				window.close();
				break;
			}
			case Event::MouseButtonReleased:
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					switchPage(out.bound, mouse, 1, page);
					switchPage(back.bound, mouse, 9, page);
					if (isHere(save.bound, mouse))
					{
						if (checkInputCourse_change(inf, 9, course))
						{
							check_success = true;
							check = true;
						}
						else
							check_fail = true;
					}
					if (isHere(ok.bound, mouse))
					{
						if (check_fail)
							check_fail = false;
						if (check_success)
							check_success = false;
					}
					for (int i = 0; i < 9; i++)
					{
						FloatRect check_me = inf[i]->text.getGlobalBounds();
						if (isHere(check_me, mouse))
							inf[i]->check = true;
						else
							inf[i]->check = false;
					}
				}
				break;
			case Event::TextEntered:
			{
				for (int i = 0; i < 3; i++)
					texting(inf[i], event.text.unicode, 40);
				texting(inf[3], event.text.unicode, 3);
				texting(inf[4], event.text.unicode, 4);
				texting(inf[5], event.text.unicode, 5);
				texting(inf[6], event.text.unicode, 5);
				texting(inf[7], event.text.unicode, 20);
				texting(inf[8], event.text.unicode, 20);
				break;
			}
			default:
			{
				break;
			}
			}
			}
		}
		window.clear();
		window.draw(screen.draw);
		window.draw(header.text);
		window.draw(sub_header.text);
		for (int i = 0; i < 9; i++)
			window.draw(inf[i]->text);
		if (check_fail)
		{
			window.draw(fail.draw);
			drawWhich(window, return1_here, return1, mouse);
		}
		if (check_success)
		{
			window.draw(success.draw);
			drawWhich(window, ok_here, ok, mouse);
		}
		drawWhich(window, save_here, save, mouse);
		drawWhich(window, out_here, out, mouse);
		drawWhich(window, back_here, back, mouse);
		window.display();
	}
	for (int i = 0; i < 9; i++)
		delete (inf[i]);
	return check;
}

void view_class_list(const string &year, const string &semester, RenderWindow &window, int &page, const float &scale, ClassNode *&class_list, bool &is_staff)
{
	Event event;
	Info class_name = createInfo("content/Oswald-Light.ttf", "Enter Class ID", 400.0f * scale, 415.0f * scale, 16.0f * scale);
	Info teacher_name = createInfo("content/Oswald-Light.ttf", "Enter Teacher name", 400.0f * scale, 455.0f * scale, 16.0f * scale);
	Object screen = createObject("content/Staff/Class/ClassPage.png");
	Object out = createObject("content/logout.png", 866.0f * scale, 106.0f * scale);
	Object out_here = createObject("content/logout1.png", 866.0f * scale, 106.0f * scale);
	Object back = createObject("content/return.png", 80.0f * scale, 106.0f * scale);
	Object back_here = createObject("content/return1.png", 80.0f * scale, 106.0f * scale);
	Object add_class = createObject("content/Staff/Class/Asset 111.png", 682.0f * scale, 272.0f * scale);
	Object add_class_here = createObject("content/Staff/Class/Asset 110.png", 682.0f * scale, 272.0f * scale);
	Object del_course = createObject("content/Staff/Class/del.png", 500.0f * scale, 272.0f * scale);
	Object del_course_here = createObject("content/Staff/Class/del_here.png", 500.0f * scale, 272.0f * scale);
	Object total_class = createObject("content/Staff/Class/Asset 53.png", 160.0f * scale, 274.0f * scale);
	Object left = createObject("content/Staff/Class/Asset 57.png", 492.0f * scale, 644.0f * scale);
	Object left_valid = createObject("content/Staff/Class/Asset 55.png", 492.0f * scale, 644.0f * scale);
	Object left_here = createObject("content/Staff/Class/Asset 91.png", 492.0f * scale, 644.0f * scale);
	Object right = createObject("content/Staff/Class/Asset 56.png", 510.0f * scale, 644.0f * scale);
	Object right_here = createObject("content/Staff/Class/Asset 90.png", 510.0f * scale, 644.0f * scale);
	Object right_valid = createObject("content/Staff/Class/Asset 54.png", 510.0f * scale, 644.0f * scale);
	Object sure = createObject("content/Staff/Create elements/sure.png", 316.0f * scale, 386.0f * scale);
	Object del_success = createObject("content/Staff/Create elements/Asset 115.png", 316.0f * scale, 386.0f * scale);
	Object return1 = createObject("content/Staff/Create elements/a7.png", 444.0f * scale, 484.0f * scale);
	Object return1_here = createObject("content/Staff/Create elements/b7.png", 444.0f * scale, 484.0f * scale);
	Object nah = createObject("content/General/a3.png", 376.0f * scale, 484.0f * scale);
	Object nah_here = createObject("content/General/b3.png", 376.0f * scale, 484.0f * scale);
	Object ofcourse = createObject("content/General/a2.png", 506.0f * scale, 484.0f * scale);
	Object ofcourse_here = createObject("content/General/b2.png", 506.0f * scale, 484.0f * scale);
	Object return2 = createObject("content/General/a7.png", 386.0f * scale, 484.0f * scale);
	Object return2_here = createObject("content/General/b7.png", 386.0f * scale, 484.0f * scale);
	Object ok = createObject("content/General/a1.png", 516.0f * scale, 484.0f * scale);
	Object ok_here = createObject("content/General/b1.png", 516.0f * scale, 484.0f * scale);
	Object enter = createObject("content/Staff/Create elements/enter.png", 316.0f * scale, 386.0f * scale);
	int count = 0, change = 0;
	bool trigger_page = true, del = false, sure_check = false, success = false, add_new = false;
	for (ClassNode *cur = class_list; cur; cur = cur->next)
		count++;
	Info *inf[5], *num[5];
	Object *square[5], *square_here[5], *rem[5], *rem_here[5];
	ClassNode *a_class[5], *tmp = nullptr;
	for (int i = 0; i < 5; i++)
	{
		a_class[i] = nullptr;
		square[i] = createObjectTest("content/Staff/Class/Asset 141.png", 160.0f * scale, (328.0f + 60.0f * i) * scale);
		square_here[i] = createObjectTest("content/Staff/Class/Asset 142.png", 160.0f * scale, (328.0f + 60.0f * i) * scale);
		rem[i] = createObjectTest("content/Staff/Class/Asset 152.png", 160.0f * scale, (328.0f + 60.0f * i) * scale);
		rem_here[i] = createObjectTest("content/Staff/Class/Asset 151.png", 160.0f * scale, (328.0f + 60.0f * i) * scale);
		inf[i] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 210.0f * scale, (336.0f + 60.0f * i) * scale, 25.0f * scale);
		num[i] = createInfoTest("content/oswald-Regular.ttf", "demo_text", 0.0f, 0.0f, 25.0f * scale);
	}
	Info count_class = createInfo("content/Oswald-Regular.ttf", "Total: " + to_string(count) + " Classes", 189.0f * scale, 280.0f * scale, 15.0f * scale);
	count_class.text.setFillColor(Color::White);
	Object **border = rem, **border_here = rem_here;
	while (window.isOpen() && page == 9)
	{
		Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
			{
				window.close();
				break;
			}
			case Event::MouseButtonReleased:
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					if (!add_new)
					{
						if (del)
						{
							if (sure_check)
							{
								if (isHere(ofcourse.bound, mouse))
								{
									deleteEvent_class(class_list, tmp);
									success = true;
									sure_check = false;
									trigger_page = true;
									count--;
									count_class.text.setString("Total: " + to_string(count) + " Classes");
								}
								if (isHere(nah.bound, mouse))
								{
									sure_check = false;
								}
							}
							else if (!success)
							{
								for (int i = 0; i < 5; i++)
								{
									if (isHere(square[i]->bound, mouse) && a_class[i])
									{
										sure_check = true;
										tmp = a_class[i];
									}
								}
							}
						}
						else
						{
							for (int i = 0; i < 5; i++)
							{
								if (isHere(square[i]->bound, mouse) && a_class[i])
								{
									page = 6;
									view_class(year, semester, a_class[i]->my_class.class_id, a_class[i]->my_class.head_teacher, window, page, scale, a_class[i], a_class[i]->my_class.student_list, true);
									trigger_page = true;
								}
							}
						}
					}
					else
					{
						if (isHere(class_name.bound, mouse))
						{
							class_name.check = true;
							teacher_name.check = false;
						}
						if (isHere(teacher_name.bound, mouse))
						{
							class_name.check = false;
							teacher_name.check = true;
						}
						if (!success)
						{
							if (isHere(ok.bound, mouse))
								success = true;
							if (isHere(return2.bound, mouse))
								add_new = false;
						}
					}
					switchPage(out.bound, mouse, 1, page);
					switchPage(back.bound, mouse, 4, page);
					if (success && isHere(return1.bound, mouse))
					{
						success = false;
						if (add_new)
						{
							ClassNode *new_class = new ClassNode;
							new_class->next = nullptr;
							new_class->my_class.student_list = nullptr;
							new_class->my_class.head_teacher = teacher_name.s;
							new_class->my_class.class_id = class_name.s;
							if (!class_list)
								class_list = new_class;
							else
							{
								ClassNode *head = class_list;
								while (head->next)
									head = head->next;
								head->next = new_class;
							}
							count++;
							count_class.text.setString("Total: " + to_string(count) + " Classes");
							trigger_page = true;
							add_new = false;
						}
					}
					if (isHere(add_class.bound, mouse))
					{
						add_new = true;
					}
					if (isHere(right.bound, mouse) && change < count - 5)
					{
						trigger_page = true;
						change += 5;
					}
					if (isHere(left.bound, mouse) && change != 0)
					{
						trigger_page = true;
						change -= 5;
					}
					if (isHere(del_course.bound, mouse))
					{
						del = !del;
						sure_check = false;
						success = false;
					}
				}
				break;
			}
			case Event::TextEntered:
			{
				texting(class_name, event.text.unicode, 10);
				texting(teacher_name, event.text.unicode, 30);
				break;
			}
			default:
				break;
			}
		}
		window.clear();
		window.draw(screen.draw);
		drawWhich(window, add_class_here, add_class, mouse);
		if (change == 0 && change >= count - 5)
		{
			window.draw(right.draw);
			window.draw(left.draw);
		}
		else if (change == 0)
		{
			window.draw(left.draw);
			drawWhich(window, right_here, right_valid, mouse);
		}
		else if (change >= count - 5)
		{
			window.draw(right.draw);
			drawWhich(window, left_here, left_valid, mouse);
		}
		else
		{
			drawWhich(window, right_here, right_valid, mouse);
			drawWhich(window, left_here, left_valid, mouse);
		}
		if (trigger_page)
		{
			ClassNode *cur = class_list;
			for (int i = 0; i < change; i++)
			{
				cur = cur->next;
			}
			for (int i = 0; i < 5; i++)
			{
				a_class[i] = cur;
				if (cur)
				{
					inf[i]->text.setString(a_class[i]->my_class.class_id);
					num[i]->text.setString(a_class[i]->my_class.head_teacher);
					num[i]->text.setPosition(square[i]->bound.left + square[i]->bound.width - num[i]->text.getGlobalBounds().width - 100.0f, (336.0f + 60.0f * i) * scale);
					cur = cur->next;
				}
				else
				{
					inf[i]->text.setString("");
				}
			}
			trigger_page = false;
		}

		drawWhich(window, out_here, out, mouse);
		drawWhich(window, back_here, back, mouse);
		window.draw(total_class.draw);
		window.draw(count_class.text);
		if (!add_new)
		{
			for (int i = 0; i < 5; i++)
			{
				if (inf[i]->text.getString() == "")
					break;
				if (success || sure_check)
				{
					window.draw(rem[i]->draw);
					inf[i]->text.setFillColor(Color(46, 58, 112));
					num[i]->text.setFillColor(Color(46, 58, 112));
				}
				else
				{
					if (drawWhich(window, border_here[i], border[i], mouse))
					{
						inf[i]->text.setFillColor(Color(118, 36, 2));
						num[i]->text.setFillColor(Color(118, 36, 2));
					}
					else
					{
						inf[i]->text.setFillColor(Color(46, 58, 112));
						num[i]->text.setFillColor(Color(46, 58, 112));
					}
				}
				window.draw(inf[i]->text);
				window.draw(num[i]->text);
			}
			if (del)
			{
				(border) = rem;
				(border_here) = rem_here;
				window.draw(del_course_here.draw);
				if (sure_check)
				{
					window.draw(sure.draw);
					drawWhich(window, nah_here, nah, mouse);
					drawWhich(window, ofcourse_here, ofcourse, mouse);
				}
				if (success)
				{
					window.draw(del_success.draw);
					drawWhich(window, return1_here, return1, mouse);
				}
			}
			else
			{
				(border) = square;
				(border_here) = square_here;
				drawWhich(window, del_course_here, del_course, mouse);
			}
		}
		else
		{
			if (del)
			{
				border = rem;
				border_here = rem_here;
				window.draw(del_course_here.draw);
			}
			else
			{
				border = square;
				border = square_here;
				window.draw(del_course.draw);
			}
			for (int i = 0; i < 5; i++)
			{
				if (inf[i]->text.getString() == "")
					break;
				inf[i]->text.setFillColor(Color(46, 58, 112));
				num[i]->text.setFillColor(Color(46, 58, 112));
				window.draw(square[i]->draw);
				window.draw(inf[i]->text);
				window.draw(num[i]->text);
			}
			if (!success)
			{
				window.draw(enter.draw);
				window.draw(class_name.text);
				window.draw(teacher_name.text);
				drawWhich(window, ok_here, ok, mouse);
				drawWhich(window, return2_here, return2, mouse);
			}
			else
			{
				window.draw(del_success.draw);
				drawWhich(window, return1_here, return1, mouse);
			}
		}
		window.display();
	}
	for (int i = 0; i < 5; i++)
		delete square[i], square_here[i], inf[i], rem[i], rem_here[i];
}

void view_registration_staff(YearNode *school, RenderWindow &window, int &page, const float &scale, RegistrationSession &data, const bool &is_staff)
{
	YearNode *cur_year = searchYearNode(school, data.year);
	SemesterNode *cur_sem = searchSemesterNode(cur_year->school_year.list_sem, data.sem);
	CourseNode *cur = data.list_of_courses;
	while (cur)
	{
		string tmp = cur->course.course_id;
		CourseNode *pre = cur;
		cur = cur->next;
		CourseNode *temp = searchCourseNode(cur_sem->sem.course_list, tmp);
		if (!temp)
			removeCourseNode(&data.list_of_courses, tmp);
		else
		{
			pre->course = temp->course;
		}
	}
	Event event;
	Info class_name = createInfo("content/Oswald-Light.ttf", "Enter Course ID", 400.0f * scale, 415.0f * scale, 16.0f * scale);
	Info teacher_name = createInfo("content/Oswald-Light.ttf", "Enter Teacher name", 400.0f * scale, 455.0f * scale, 16.0f * scale);
	Object screen = createObject("content/Registration/register_student.png");
	Object out = createObject("content/logout.png", 866.0f * scale, 106.0f * scale);
	Object out_here = createObject("content/logout1.png", 866.0f * scale, 106.0f * scale);
	Object back = createObject("content/return.png", 80.0f * scale, 106.0f * scale);
	Object back_here = createObject("content/return1.png", 80.0f * scale, 106.0f * scale);
	Object *add_class, *add_class_here;
	Object return2 = createObject("content/General/a7.png", 386.0f * scale, 484.0f * scale);
	Object return2_here = createObject("content/General/b7.png", 386.0f * scale, 484.0f * scale);
	Object ok = createObject("content/General/a1.png", 516.0f * scale, 484.0f * scale);
	Object ok_here = createObject("content/General/b1.png", 516.0f * scale, 484.0f * scale);
	Object enter = createObject("content/Staff/Create elements/enter.png", 316.0f * scale, 386.0f * scale);
	Object invalid = createObject("content/Registration/invalid.png", 316.0f * scale, 386.0f * scale);
	Info sub_header = createInfo("content/VNI-Vari.TTF", "Course Registration", 160.0f * scale, 158.0f * scale, 28.0f * scale);
	sub_header.text.setFillColor(Color(101, 159, 235));
	Info header = createInfo("content/VNI-Vari.TTF", data.year + " " + data.sem, 160.0f * scale, 200.0f * scale, 43.0f * scale);
	if (is_staff)
	{
		add_class = createObjectTest("content/Registration/Asset 120.png", 686.0f * scale, 340.0f * scale);
		add_class_here = createObjectTest("content/Registration/Asset 119.png", 686.0f * scale, 340.0f * scale);
	}
	else
	{
		add_class = createObjectTest("content/Registration/sub.png", 686.0f * scale, 340.0f * scale);
		add_class_here = createObjectTest("content/Registration/sub_here.png", 686.0f * scale, 340.0f * scale);
	}
	Object del_course = createObject("content/Registration/unsub.png", 500.0f * scale, 340.0f * scale);
	Object del_course_here = createObject("content/Registration/unsub_here.png", 500.0f * scale, 340.0f * scale);
	Object total_class = createObject("content/Staff/Class/Asset 53.png", 160.0f * scale, 274.0f * scale);
	Object left = createObject("content/Staff/Class/Asset 57.png", 492.0f * scale, 644.0f * scale);
	Object left_valid = createObject("content/Staff/Class/Asset 55.png", 492.0f * scale, 644.0f * scale);
	Object left_here = createObject("content/Staff/Class/Asset 91.png", 492.0f * scale, 644.0f * scale);
	Object right = createObject("content/Staff/Class/Asset 56.png", 510.0f * scale, 644.0f * scale);
	Object right_here = createObject("content/Staff/Class/Asset 90.png", 510.0f * scale, 644.0f * scale);
	Object right_valid = createObject("content/Staff/Class/Asset 54.png", 510.0f * scale, 644.0f * scale);
	Object sure = createObject("content/Staff/Create elements/sure.png", 316.0f * scale, 386.0f * scale);
	Object del_success = createObject("content/Staff/Create elements/Asset 115.png", 316.0f * scale, 386.0f * scale);
	Object return1 = createObject("content/Staff/Create elements/a7.png", 444.0f * scale, 484.0f * scale);
	Object return1_here = createObject("content/Staff/Create elements/b7.png", 444.0f * scale, 484.0f * scale);
	Object nah = createObject("content/General/a3.png", 376.0f * scale, 484.0f * scale);
	Object nah_here = createObject("content/General/b3.png", 376.0f * scale, 484.0f * scale);
	Object ofcourse = createObject("content/General/a2.png", 506.0f * scale, 484.0f * scale);
	Object ofcourse_here = createObject("content/General/b2.png", 506.0f * scale, 484.0f * scale);
	int count = 0, change = 0;
	bool trigger_page = true, del = false, sure_check = false, fail = false, success = false, add_new = false;
	for (CourseNode *cur = data.list_of_courses; cur; cur = cur->next)
		count++;
	Info *inf[4], *num[4];
	Info start_date = createInfo("content/Oswald-Regular.ttf", data.start_date, 216.0f * scale, 284.0f * scale, 18.0f * scale);
	Info end_date = createInfo("content/Oswald-Regular.ttf", data.end_date, 568.0f * scale, 284.0f * scale, 18.0f * scale);
	start_date.s = data.start_date;
	end_date.s = data.end_date;
	Object *square[4], *square_here[4];
	CourseNode *a_class[4], *tmp = nullptr;
	for (int i = 0; i < 4; i++)
	{
		a_class[i] = nullptr;
		square[i] = createObjectTest("content/Registration/Asset 118.png", 174.0f * scale, (388.0f + 60.0f * i) * scale);
		square_here[i] = createObjectTest("content/Registration/Asset 124.png", 174.0f * scale, (388.0f + 60.0f * i) * scale);
		num[i] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 198.0f * scale, (396.0f + 60.0f * i) * scale, 25.0f * scale);
		inf[i] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 198.0f * scale, (396.0f + 60.0f * i) * scale, 25.0f * scale);
	}
	Info count_class = createInfo("content/Oswald-Regular.ttf", "Total: " + to_string(count) + " Courses", 190.0f * scale, 346.0f * scale, 15.0f * scale);
	count_class.text.setFillColor(Color::White);
	Object **border = square, **border_here = square_here;
	while (window.isOpen() && page == 11)
	{
		Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
			{
				window.close();
				break;
			}
			case Event::MouseButtonReleased:
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					switchPage(out.bound, mouse, 1, page);
					switchPage(back.bound, mouse, 4, page);
					if (isHere(add_class->bound, mouse))
					{
						add_new = true;
						class_name.s = "";
						teacher_name.s = "";
						class_name.text.setString("Enter Course ID");
						teacher_name.text.setString("Enter Teacher name");
					}
					if (!add_new)
					{
						if (isHere(right.bound, mouse) && change <= count - 4)
						{
							trigger_page = true;
							change += 4;
						}
						if (isHere(left.bound, mouse) && change != 0)
						{
							trigger_page = true;
							change -= 4;
						}
						for (int i = 0; i < 4; i++)
						{
							if (isHere(square[i]->bound, mouse))
							{
								page = 10;
								course_student(0, window, page, scale, a_class[i]);
								page = 11;
							}
						}
						teacher_name.check = false;
						class_name.check = false;
						start_date.check = isHere(start_date.bound, mouse);
						end_date.check = isHere(end_date.bound, mouse);
					}
					else
					{

						if (success || fail)
						{
							teacher_name.check = false;
							class_name.check = false;
						}
						else
						{
							add_new = !isHere(return2.bound, mouse);
							if (isHere(ok.bound, mouse))
							{
								YearNode *cur_year = searchYearNode(school, data.year);
								if (!cur_year)
									fail = true;
								else
								{
									SemesterNode *cur_sem = searchSemesterNode(cur_year->school_year.list_sem, data.sem);
									if (!cur_sem)
										fail = true;
									else
									{
										CourseNode *cur_course = searchCourseNode(cur_sem->sem.course_list, class_name.s);
										if (!cur_course)
											fail = true;
										else
										{
											if (teacher_name.s == cur_course->course.teacher_name)
											{
												CourseNode *check_course = searchCourseNode(data.list_of_courses, class_name.s);
												if (check_course)
													fail = true;
												else
												{
													success = true;
													Course new_registration = cur_course->course;
													appendNewCourseNode(&data.list_of_courses, new_registration);
													trigger_page = true;
												}
											}
											else
												fail = true;
										}
									}
								}
							}
							else
							{
								teacher_name.check = isHere(teacher_name.bound, mouse);
								class_name.check = isHere(class_name.bound, mouse);
							}
							start_date.check = false;
							end_date.check = false;
						}
						if (isHere(return1.bound, mouse) && (success || fail))
						{
							add_new = false;
							success = false;
							fail = false;
						}
					}
				}
				break;
			}
			case Event::TextEntered:
			{
				texting(start_date, event.text.unicode, 11);
				texting(end_date, event.text.unicode, 11);
				texting(teacher_name, event.text.unicode, 40);
				texting(class_name, event.text.unicode, 40);
				data.start_date = start_date.s;
				data.end_date = end_date.s;
				break;
			}
			default:
				break;
			}
		}
		window.clear();
		window.draw(screen.draw);
		window.draw(count_class.text);
		window.draw(header.text);
		window.draw(sub_header.text);
		drawWhich(window, add_class_here, add_class, mouse);
		if (add_new)
		{
			if (change == 0 && change >= count - 4)
			{
				window.draw(right.draw);
				window.draw(left.draw);
			}
			else if (change == 0)
			{
				window.draw(left.draw);
				window.draw(right_valid.draw);
			}
			else if (change >= count - 4)
			{
				window.draw(right.draw);
				window.draw(left_valid.draw);
			}
			else
			{
				window.draw(right_valid.draw);
				window.draw(left_valid.draw);
			}
			for (int i = 0; i < 4; i++)
			{
				if (inf[i]->text.getString() == "")
					break;
				window.draw(border[i]->draw);
				inf[i]->text.setFillColor(Color(46, 58, 112));
				num[i]->text.setFillColor(Color(46, 58, 112));

				window.draw(inf[i]->text);
				window.draw(num[i]->text);
			}
			if (success)
			{
				window.draw(del_success.draw);
				drawWhich(window, return1_here, return1, mouse);
			}
			else if (fail)
			{
				window.draw(invalid.draw);
				drawWhich(window, return1_here, return1, mouse);
			}
			else
			{
				window.draw(enter.draw);
				drawWhich(window, ok_here, ok, mouse);
				drawWhich(window, return2_here, return2, mouse);
				window.draw(teacher_name.text);
				window.draw(class_name.text);
			}
		}
		else
		{
			if (change == 0 && change >= count - 4)
			{
				window.draw(right.draw);
				window.draw(left.draw);
			}
			else if (change == 0)
			{
				window.draw(left.draw);
				drawWhich(window, right_here, right_valid, mouse);
			}
			else if (change >= count - 4)
			{
				window.draw(right.draw);
				drawWhich(window, left_here, left_valid, mouse);
			}
			else
			{
				drawWhich(window, right_here, right_valid, mouse);
				drawWhich(window, left_here, left_valid, mouse);
			}
			for (int i = 0; i < 4; i++)
			{
				if (inf[i]->text.getString() == "")
					break;
				if (drawWhich(window, border_here[i], border[i], mouse))
				{
					inf[i]->text.setFillColor(Color(118, 36, 2));
					num[i]->text.setFillColor(Color(118, 36, 2));
				}
				else
				{
					inf[i]->text.setFillColor(Color(46, 58, 112));
					num[i]->text.setFillColor(Color(46, 58, 112));
				}
				window.draw(inf[i]->text);
				window.draw(num[i]->text);
			}
		}
		if (trigger_page)
		{
			CourseNode *cur = data.list_of_courses;
			for (int i = 0; i < change; i++)
			{
				cur = cur->next;
			}
			for (int i = 0; i < 4; i++)
			{
				a_class[i] = cur;
				if (cur)
				{
					inf[i]->text.setString(a_class[i]->course.course_id + " - " + a_class[i]->course.teacher_name + " (" + day_convert(a_class[i]->course.teaching_session[0]) + "-" + no_convert(a_class[i]->course.teaching_session[0]) + ", " + day_convert(a_class[i]->course.teaching_session[1]) + "-" + no_convert(a_class[i]->course.teaching_session[1]) + ")");
					int stu = 0;
					for (StudentNode *cur_stu = a_class[i]->student_list; cur_stu; cur_stu = cur_stu->next)
					{
						stu++;
					}
					num[i]->text.setString(to_string(stu) + "/" + to_string(a_class[i]->course.max_students));
					num[i]->text.setPosition(square[i]->bound.left + square[i]->bound.width - num[i]->text.getGlobalBounds().width - 30.0f, (396.0f + 60.0f * i) * scale);
					cur = cur->next;
				}
				else
				{
					inf[i]->text.setString("");
					num[i]->text.setString("");
				}
			}
			trigger_page = false;
		}

		drawWhich(window, out_here, out, mouse);
		drawWhich(window, back_here, back, mouse);
		window.draw(count_class.text);
		window.draw(start_date.text);
		window.draw(end_date.text);
		window.display();
	}
	for (int i = 0; i < 4; i++)
		delete square[i], square_here[i], inf[i], num[i];
	delete add_class, add_class_here;
}
void view_registration_student(YearNode *school, RenderWindow &window, int &page, const float &scale, RegistrationSession data, const bool &is_staff, StudentNode *user)
{
	YearNode *cur_year = searchYearNode(school, data.year);
	SemesterNode *cur_sem = searchSemesterNode(cur_year->school_year.list_sem, data.sem);
	CourseNode *cur = data.list_of_courses;
	while (cur)
	{
		string tmp = cur->course.course_id;
		CourseNode *pre = cur;
		cur = cur->next;
		CourseNode *temp = searchCourseNode(cur_sem->sem.course_list, tmp);
		if (!temp)
			removeCourseNode(&data.list_of_courses, tmp);
		else
		{
			pre->course = temp->course;
		}
	}
	Event event;
	Object screen = createObject("content/Registration/register_student.png");
	Object out = createObject("content/logout.png", 866.0f * scale, 106.0f * scale);
	Object out_here = createObject("content/logout1.png", 866.0f * scale, 106.0f * scale);
	Object back = createObject("content/return.png", 80.0f * scale, 106.0f * scale);
	Object back_here = createObject("content/return1.png", 80.0f * scale, 106.0f * scale);
	Object *sub, *sub_here;
	Info sub_header = createInfo("content/VNI-Vari.TTF", "Course Registration", 160.0f * scale, 158.0f * scale, 28.0f * scale);
	sub_header.text.setFillColor(Color(101, 159, 235));
	Info header = createInfo("content/VNI-Vari.TTF", data.year + " " + data.sem, 160.0f * scale, 200.0f * scale, 43.0f * scale);
	if (is_staff)
	{
		sub = createObjectTest("content/Registration/Asset 120.png", 686.0f * scale, 340.0f * scale);
		sub_here = createObjectTest("content/Registration/Asset 119.png", 686.0f * scale, 340.0f * scale);
	}
	else
	{
		sub = createObjectTest("content/Registration/sub.png", 686.0f * scale, 340.0f * scale);
		sub_here = createObjectTest("content/Registration/sub_here.png", 686.0f * scale, 340.0f * scale);
	}
	Object unsub = createObject("content/Registration/unsub.png", 500.0f * scale, 340.0f * scale);
	Object unsub_here = createObject("content/Registration/unsub_here.png", 500.0f * scale, 340.0f * scale);
	Object total_class = createObject("content/Staff/Class/Asset 53.png", 160.0f * scale, 274.0f * scale);
	Object left = createObject("content/Staff/Class/Asset 57.png", 492.0f * scale, 644.0f * scale);
	Object left_valid = createObject("content/Staff/Class/Asset 55.png", 492.0f * scale, 644.0f * scale);
	Object left_here = createObject("content/Staff/Class/Asset 91.png", 492.0f * scale, 644.0f * scale);
	Object right = createObject("content/Staff/Class/Asset 56.png", 510.0f * scale, 644.0f * scale);
	Object right_here = createObject("content/Staff/Class/Asset 90.png", 510.0f * scale, 644.0f * scale);
	Object right_valid = createObject("content/Staff/Class/Asset 54.png", 510.0f * scale, 644.0f * scale);
	Object sure = createObject("content/Staff/Create elements/sure.png", 316.0f * scale, 386.0f * scale);
	Object del_success = createObject("content/Staff/Create elements/Asset 115.png", 316.0f * scale, 386.0f * scale);
	Object invalid = createObject("content/Registration/invalid.png", 316.0f * scale, 386.0f * scale);
	Object return1 = createObject("content/Staff/Create elements/a7.png", 444.0f * scale, 484.0f * scale);
	Object return1_here = createObject("content/Staff/Create elements/b7.png", 444.0f * scale, 484.0f * scale);
	Object nah = createObject("content/General/a3.png", 376.0f * scale, 484.0f * scale);
	Object nah_here = createObject("content/General/b3.png", 376.0f * scale, 484.0f * scale);
	Object ofcourse = createObject("content/General/a2.png", 506.0f * scale, 484.0f * scale);
	Object ofcourse_here = createObject("content/General/b2.png", 506.0f * scale, 484.0f * scale);
	int count = 0, change = 0, count_check = 0;
	bool trigger_page = true, stop = false, fail = false, success = false, sub_check = true;
	Info *inf[4], *num[4];
	for (CourseNode *cur = data.list_of_courses; cur; cur = cur->next)
		count++;
	for (MyCourse *cur = user->student.my_course; cur; cur = cur->next)
	{
		if (cur->year == data.year && cur->sem == data.sem)
		{
			count_check++;
		}
	}
	Info start_date = createInfo("content/Oswald-Regular.ttf", data.start_date, 216.0f * scale, 284.0f * scale, 18.0f * scale);
	Info end_date = createInfo("content/Oswald-Regular.ttf", data.end_date, 568.0f * scale, 284.0f * scale, 18.0f * scale);
	Object *square[4], *square_here[4], *square_del[4];
	CourseNode *a_class[4], *tmp = nullptr;
	for (int i = 0; i < 4; i++)
	{
		a_class[i] = nullptr;
		square[i] = createObjectTest("content/Registration/Asset 118.png", 174.0f * scale, (388.0f + 60.0f * i) * scale);
		square_here[i] = createObjectTest("content/Registration/Asset 124.png", 174.0f * scale, (388.0f + 60.0f * i) * scale);
		square_del[i] = createObjectTest("content/Registration/Asset 123.png", 174.0f * scale, (388.0f + 60.0f * i) * scale);
		num[i] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 198.0f * scale, (396.0f + 60.0f * i) * scale, 25.0f * scale);
		inf[i] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 198.0f * scale, (396.0f + 60.0f * i) * scale, 25.0f * scale);
	}
	Info count_class = createInfo("content/Oswald-Regular.ttf", to_string(count_check) + "/5 Courses", 200.0f * scale, 346.0f * scale, 15.0f * scale);
	count_class.text.setFillColor(Color::White);
	bool in_here[4], first_check = true;
	int current_students[4];
	Object **border = square, **border_here = square_here;
	while (window.isOpen() && page == 11)
	{
		Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
			{
				window.close();
				break;
			}
			case Event::MouseButtonReleased:
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					switchPage(out.bound, mouse, 1, page);
					switchPage(back.bound, mouse, 3, page);
					for (int i = 0; i < 4; i++)
					{
						if (isHere(square[i]->bound, mouse) && a_class[i])
						{
							if (!stop)
							{
								if (sub_check)
								{
									if (count_check >= 5 || in_here[i] || current_students[i] >= a_class[i]->course.max_students)
									{
										fail = true;
										stop = true;
									}
									else
									{
										bool collision = false;
										for (MyCourse *cur = user->student.my_course; cur; cur = cur->next)
										{
											if (data.year == cur->year && data.sem == cur->sem)
											{
												if (checkCourseCollision(cur->course->course, a_class[i]->course))
												{
													collision = true;
													fail = true;
													stop = true;
													break;
												}
											}
										}
										if (!collision)
										{
											int k = 2;
											count_check++;
											count_class.text.setString(to_string(count_check) + "/5 Courses");
											CourseNode *cur_course = searchCourseNode(cur_sem->sem.course_list, a_class[i]->course.course_id);
											MyCourse *new_cur = createMyCourse(cur_course);
											appendNewMyCourse(user, new_cur);
											StudentNode *head = a_class[i]->student_list, *head1 = cur_course->student_list;
											if (head)
											{
												while (head->next)
												{
													k++;
													head1 = head1->next;
													head = head->next;
												}
												head->next = copyForCourse(user, k);
												head1->next = copyForCourse(user, k);
											}
											else
											{
												a_class[i]->student_list = copyForCourse(user, 1);
												cur_course->student_list = copyForCourse(user, 1);
											}
											success = true;
											stop = true;
											trigger_page = true;
										}
									}
								}
								// unsub
								else if (in_here[i])
								{
									count_check--;
									count_class.text.setString(to_string(count_check) + "/5 Courses");
									YearNode *cur_year = searchYearNode(school, a_class[i]->year_id);
									SemesterNode *cur_sem = searchSemesterNode(cur_year->school_year.list_sem, a_class[i]->semester_id);
									CourseNode *cur_course = searchCourseNode(cur_sem->sem.course_list, a_class[i]->course.course_id);
									removeStudentNode(&cur_course->student_list, user->student.student_id);
									removeStudentNode(&a_class[i]->student_list, user->student.student_id);
									removeMyCourses(user, cur_course);
									success = true;
									stop = true;
									trigger_page = true;
								}
							}
						}
					}
					if (sub_check && isHere(unsub.bound, mouse))
						sub_check = false;
					if (!sub_check && isHere(sub->bound, mouse))
						sub_check = true;
					if (success && isHere(return1.bound, mouse))
					{
						success = false;
						stop = false;
					}
					if (fail && isHere(return1.bound, mouse))
					{
						fail = false;
						stop = false;
					}
					if (isHere(right.bound, mouse) && change <= count - 4)
					{
						trigger_page = true;
						change += 4;
					}
					if (isHere(left.bound, mouse) && change != 0)
					{
						trigger_page = true;
						change -= 4;
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
		window.draw(count_class.text);
		window.draw(header.text);
		window.draw(sub_header.text);
		if (sub_check)
		{
			window.draw(sub_here->draw);
			window.draw(unsub.draw);
		}
		else
		{
			window.draw(sub->draw);
			window.draw(unsub_here.draw);
		}
		if (change == 0 && change >= count - 4)
		{
			window.draw(right.draw);
			window.draw(left.draw);
		}
		else if (change == 0)
		{
			window.draw(left.draw);
			drawWhich(window, right_here, right_valid, mouse);
		}
		else if (change >= count - 4)
		{
			window.draw(right.draw);
			drawWhich(window, left_here, left_valid, mouse);
		}
		else
		{
			drawWhich(window, right_here, right_valid, mouse);
			drawWhich(window, left_here, left_valid, mouse);
		}
		if (trigger_page)
		{
			CourseNode *cur = data.list_of_courses;
			for (int i = 0; i < change; i++)
			{
				cur = cur->next;
			}
			for (int i = 0; i < 4; i++)
			{
				in_here[i] = false;
				current_students[i] = 0;
				a_class[i] = cur;
				if (cur)
				{
					inf[i]->text.setString(a_class[i]->course.course_id + " - " + a_class[i]->course.teacher_name + " (" + day_convert(a_class[i]->course.teaching_session[0]) + "-" + no_convert(a_class[i]->course.teaching_session[0]) + ", " + day_convert(a_class[i]->course.teaching_session[1]) + "-" + no_convert(a_class[i]->course.teaching_session[1]) + ")");
					int stu = 0;
					for (StudentNode *cur_stu = a_class[i]->student_list; cur_stu; cur_stu = cur_stu->next)
					{
						current_students[i]++;
						if (cur_stu->student.student_id == user->student.student_id)
							in_here[i] = true;
					}
					num[i]->text.setString(to_string(current_students[i]) + "/" + to_string(a_class[i]->course.max_students));
					num[i]->text.setPosition(square[i]->bound.left + square[i]->bound.width - num[i]->text.getGlobalBounds().width - 30.0f, (396.0f + 60.0f * i) * scale);
					cur = cur->next;
				}
				else
				{
					inf[i]->text.setString("");
					num[i]->text.setString("");
				}
			}
			trigger_page = false;
		}
		drawWhich(window, out_here, out, mouse);
		drawWhich(window, back_here, back, mouse);
		window.draw(count_class.text);
		// draw border
		if (sub_check)
		{
			for (int i = 0; i < 4; i++)
			{
				if (inf[i]->text.getString() == "")
					break;
				if (in_here[i])
				{
					window.draw(border_here[i]->draw);
					inf[i]->text.setFillColor(Color(118, 36, 2));
					num[i]->text.setFillColor(Color(118, 36, 2));
				}
				else if (stop)
				{
					window.draw(border[i]->draw);
					inf[i]->text.setFillColor(Color(46, 58, 112));
					num[i]->text.setFillColor(Color(46, 58, 112));
				}
				else
				{
					if (drawWhich(window, border_here[i], border[i], mouse))
					{
						inf[i]->text.setFillColor(Color(118, 36, 2));
						num[i]->text.setFillColor(Color(118, 36, 2));
					}
					else
					{
						inf[i]->text.setFillColor(Color(46, 58, 112));
						num[i]->text.setFillColor(Color(46, 58, 112));
					}
				}
				window.draw(inf[i]->text);
				window.draw(num[i]->text);
			}
		}
		else
		{
			for (int i = 0; i < 4; i++)
			{
				if (inf[i]->text.getString() == "")
					break;
				if (in_here[i])
				{
					if (stop)
					{
						window.draw(border_here[i]->draw);
						inf[i]->text.setFillColor(Color(118, 36, 2));
						num[i]->text.setFillColor(Color(118, 36, 2));
					}
					else
					{
						if (drawWhich(window, square_del[i], border_here[i], mouse))
						{
							inf[i]->text.setFillColor(Color::White);
							num[i]->text.setFillColor(Color::White);
						}
						else
						{
							inf[i]->text.setFillColor(Color(118, 36, 2));
							num[i]->text.setFillColor(Color(118, 36, 2));
						}
					}
				}
				else
				{
					window.draw(border[i]->draw);
					inf[i]->text.setFillColor(Color(46, 58, 112));
					num[i]->text.setFillColor(Color(46, 58, 112));
				}
				window.draw(inf[i]->text);
				window.draw(num[i]->text);
			}
		}
		if (stop)
		{
			if (success)
			{
				window.draw(del_success.draw);
				drawWhich(window, return1_here, return1, mouse);
			}
			if (fail)
			{
				window.draw(invalid.draw);
				drawWhich(window, return1_here, return1, mouse);
			}
		}
		window.draw(start_date.text);
		window.draw(end_date.text);
		window.display();
	}
	for (int i = 0; i < 4; i++)
		delete square[i], square_here[i], inf[i], num[i], square_del[i];
	delete sub, sub_here;
}

int student_profile(RenderWindow &window, int &page, const float &scale, StudentNode *&student, bool is_staff, bool is_new, string cur_class)
{
	int res = 0;
	string text[7];
	Info *header, *sub_header;
	bool gender;
	if (!is_new)
	{
		text[0] = student->student.student_id;
		text[1] = student->student.first_name;
		text[2] = student->student.last_name;
		text[3] = student->student.student_class;
		text[4] = student->student.dob;
		text[5] = student->student.password;
		text[6] = student->student.social_id;
		gender = student->student.gender;
		sub_header = createInfoTest("content/VNI-Vari.TTF", "Change Profile", 160.0f * scale, 158.0f * scale, 28.0f * scale);
		sub_header->text.setFillColor(Color(101, 159, 235));
		header = createInfoTest("content/VNI-Vari.TTF", student->student.last_name + " " + student->student.first_name, 160.0f * scale, 200.0f * scale, 43.0f * scale);
	}
	else
	{
		for (unsigned int i = 0; i < 7; i++)
			text[i] = "Enter text";
		text[3] = cur_class;
		gender = false;
		sub_header = createInfoTest("content/VNI-Vari.TTF", cur_class, 160.0f * scale, 158.0f * scale, 28.0f * scale);
		sub_header->text.setFillColor(Color(101, 159, 235));
		header = createInfoTest("content/VNI-Vari.TTF", "Add New Student", 160.0f * scale, 200.0f * scale, 43.0f * scale);
	}
	Info *inf[7];
	for (int i = 0; i < 7; i++)
		inf[i] = createInfoTest("content/Oswald-Light.ttf", text[i], 318.0f * scale, (303.0f + 56.0f * i) * scale, 20.0f * scale);
	changePos(inf[3], 318.0f * scale, (303.0f + 56.0f * 4) * scale);
	changePos(inf[4], 318.0f * scale, (303.0f + 56.0f * 5) * scale);
	changePos(inf[5], 594.0f * scale, (303.0f + 56.0f * 5) * scale);
	changePos(inf[6], 594.0f * scale, (303.0f + 56.0f * 4) * scale);
	Object back = createObject("content/return.png", 80.0f * scale, 106.0f * scale);
	Object back_here = createObject("content/return1.png", 80.0f * scale, 106.0f * scale);
	Object screen = createObject("content/Staff/Create elements/add new student_here.png");
	Object change = createObject("content/General/change.png", 316.0f * scale, 386.0f * scale);
	Object success = createObject("content/Staff/Create elements/Asset 115.png", 316.0f * scale, 386.0f * scale);
	Object enter = createObject("content/General/enter.png", 316.0f * scale, 386.0f * scale);
	Object invalid = createObject("content/Staff/Create elements/Asset 114.png", 316.0f * scale, 386.0f * scale);
	Object out = createObject("content/logout.png", 866.0f * scale, 106.0f * scale);
	Object out_here = createObject("content/logout1.png", 866.0f * scale, 106.0f * scale);
	Object *a[7], *b[7];
	for (int i = 0; i < 7; i++)
	{
		a[i] = createObjectTest("content/General/a" + to_string(i + 1) + ".png", 0 * scale, 0 * scale);
		b[i] = createObjectTest("content/General/b" + to_string(i + 1) + ".png", 0 * scale, 0 * scale);
	}
	changePos(a[0], b[0], 444.0f * scale, 484.0f * scale);
	// return button
	changePos(a[6], b[6], 444.0f * scale, 484.0f * scale);
	changePos(a[2], b[2], 376.0f * scale, 470.0f * scale);
	changePos(a[1], b[1], 506.0f * scale, 470.0f * scale);
	changePos(a[3], b[3], 480.0f * scale, 522.0f * scale);
	delete a[4], b[4];
	a[4] = createObjectTest("content/Staff/Create elements/save.png", 750.0f * scale, 580.0f * scale);
	b[4] = createObjectTest("content/Staff/Create elements/save_here.png", 750.0f * scale, 580.0f * scale);
	// left - right gender
	changePos(a[5], 322.0f * scale, 477.5f * scale);
	changePos(b[5], 426.0f * scale, 477.5f * scale);
	Info pw = createInfo("content/Oswald-Light.ttf", "Enter your new password here", 400.0f * scale, 455.0f * scale, 15.0f * scale);
	Info pw_old = createInfo("content/Oswald-Light.ttf", "Enter your old password here", 400.0f * scale, 415.0f * scale, 15.0f * scale);
	bool view_my_class = true, fail = false, change_success = false;
	// switch subpage in "change password" (under_working(1), normal(0), changed(2))
	int password_status = 0;
	Event event;
	// only student can view their own class, not the staff
	view_my_class = false;

	while (window.isOpen() && page == 2)
	{
		Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
			{
				window.close();
				break;
			}
			case Event::MouseButtonReleased:
			{
				if (event.mouseButton.button == Mouse::Left)
				{

					switchPage(out.bound, mouse, 1, page);
					switchPage(back.bound, mouse, 6, page);
				}
				if (!(change_success || fail))
				{
					if ((isHere(a[5]->bound, mouse) && !gender) || (gender && isHere(b[5]->bound, mouse)))
					{
						gender = !gender;
					}
					for (int i = 0; i < 7; i++)
					{
						FloatRect bounded = inf[i]->text.getGlobalBounds();
						if (isHere(bounded, mouse))
							inf[i]->check = true;
						else
							inf[i]->check = false;
					}
				}
				if (isHere(a[4]->bound, mouse))
				{
					for (int i = 0; i < 7; i++)
					{
						text[i] = inf[i]->text.getString();
					}
					if (checkDOB(text[4]) && checkID(text[0]))
					{
						if (!is_new)
						{
							student->student.student_id = text[0];
							student->student.first_name = text[1];
							student->student.last_name = text[2];
							student->student.student_class = text[3];
							student->student.dob = text[4];
							student->student.password = text[5];
							student->student.gender = gender;
							student->student.social_id = text[6];
						}
						else
						{
							int k = 2;
							StudentNode *head = student;
							if (!head)
							{
								StudentNode *new_stu = new StudentNode;
								new_stu->next = nullptr;
								new_stu->student = createStudent(1, text[0], text[1], text[2], gender, text[4], text[6], text[5], text[3]);
								student = new_stu;
							}
							else
							{
								while (head->next)
								{
									head = head->next;
									k++;
								}
								StudentNode *new_stu = new StudentNode;
								new_stu->next = nullptr;
								new_stu->student = createStudent(k, text[0], text[1], text[2], gender, text[4], text[6], text[5], text[3]);
								head->next = new_stu;
							}
							res++;
						}
						change_success = true;
					}
					else
						fail = true;
				}
				if (isHere(a[6]->bound, mouse))
				{
					if (change_success)
						change_success = false;
					if (fail)
						fail = false;
				}
			}
			break;
			case Event::TextEntered:
			{
				for (int i = 0; i < 7; i++)
				{
					if (i != 3)
						texting(inf[i], event.text.unicode, 40);
				}
			}
			default:
			{
				break;
			}
			}
		}
		window.clear();
		window.draw(screen.draw);
		window.draw(header->text);
		window.draw(sub_header->text);
		for (int i = 0; i < 7; i++)
			window.draw(inf[i]->text);
		window.draw((gender ? a[5]->draw : b[5]->draw));
		drawWhich(window, out_here, out, mouse);
		drawWhich(window, back_here, back, mouse);
		if (!(change_success || fail))
			drawWhich(window, b[4], a[4], mouse);
		else if (change_success)
		{
			window.draw(a[4]->draw);
			window.draw(success.draw);
			drawWhich(window, b[6], a[6], mouse);
		}
		else
		{
			window.draw(a[4]->draw);
			window.draw(invalid.draw);
			drawWhich(window, b[6], a[6], mouse);
		}
		window.display();
	}
	for (int j = 0; j < 7; j++)
	{
		delete (a[j]);
		delete b[j], inf[j];
	}
	delete header, sub_header;
	return res;
}
void view_schedule(YearNode* school, RenderWindow& window, int& page, const float& scale, RegistrationSession& data, StudentNode* user)
{
	YearNode* cur_year = searchYearNode(school, data.year);
	SemesterNode* cur_sem = searchSemesterNode(cur_year->school_year.list_sem, data.sem);
	CourseNode* cur = data.list_of_courses;
	while (cur)
	{
		string tmp = cur->course.course_id;
		CourseNode* pre = cur;
		cur = cur->next;
		CourseNode* temp = searchCourseNode(cur_sem->sem.course_list, tmp);
		if (!temp)
			removeCourseNode(&data.list_of_courses, tmp);
		else
		{
			pre->course = temp->course;
		}
	}
	Event event;
	Object screen = createObject("content/Registration/register_student.png");
	Object out = createObject("content/logout.png", 866.0f * scale, 106.0f * scale);
	Object out_here = createObject("content/logout1.png", 866.0f * scale, 106.0f * scale);
	Object back = createObject("content/return.png", 80.0f * scale, 106.0f * scale);
	Object back_here = createObject("content/return1.png", 80.0f * scale, 106.0f * scale);
	Info sub_header = createInfo("content/VNI-Vari.TTF", "Course Schedule", 160.0f * scale, 158.0f * scale, 28.0f * scale);
	sub_header.text.setFillColor(Color(101, 159, 235));
	Info header = createInfo("content/VNI-Vari.TTF", data.year + " " + data.sem, 160.0f * scale, 200.0f * scale, 43.0f * scale);
	Object *sub, *sub_here;
	sub = createObjectTest("content/Registration/sub.png", 686.0f * scale, 340.0f * scale);
	sub_here = createObjectTest("content/Registration/sub_here.png", 686.0f * scale, 340.0f * scale);

	Object unsub = createObject("content/Registration/unsub.png", 500.0f * scale, 340.0f * scale);
	Object unsub_here = createObject("content/Registration/unsub_here.png", 500.0f * scale, 340.0f * scale);
	Object total_class = createObject("content/Staff/Class/Asset 53.png", 160.0f * scale, 274.0f * scale);
	Object left = createObject("content/Staff/Class/Asset 57.png", 492.0f * scale, 644.0f * scale);
	Object left_valid = createObject("content/Staff/Class/Asset 55.png", 492.0f * scale, 644.0f * scale);
	Object left_here = createObject("content/Staff/Class/Asset 91.png", 492.0f * scale, 644.0f * scale);
	Object right = createObject("content/Staff/Class/Asset 56.png", 510.0f * scale, 644.0f * scale);
	Object right_here = createObject("content/Staff/Class/Asset 90.png", 510.0f * scale, 644.0f * scale);
	Object right_valid = createObject("content/Staff/Class/Asset 54.png", 510.0f * scale, 644.0f * scale);
	Object del_success = createObject("content/Staff/Create elements/Asset 115.png", 316.0f * scale, 386.0f * scale);
	Object invalid = createObject("content/Registration/invalid.png", 316.0f * scale, 386.0f * scale);
	Object return1 = createObject("content/Staff/Create elements/a7.png", 444.0f * scale, 484.0f * scale);
	Object return1_here = createObject("content/Staff/Create elements/b7.png", 444.0f * scale, 484.0f * scale);

	int count = 0, change = 0;
	bool trigger_page = true, del = false, sure_check = false, fail = false, success = false, add_new = false, sub_check = true, stop = false;
	for (CourseNode* cur = data.list_of_courses; cur; cur = cur->next)
		count++;
	Info* inf[4], * num[4];
	Info start_date = createInfo("content/Oswald-Regular.ttf", data.start_date, 216.0f * scale, 284.0f * scale, 18.0f * scale);
	Info end_date = createInfo("content/Oswald-Regular.ttf", data.end_date, 568.0f * scale, 284.0f * scale, 18.0f * scale);
	Object* square[4], * square_here[4], * square_del[4];
	start_date.s = data.start_date;
	end_date.s = data.end_date;
	CourseNode* a_class[4], * tmp = nullptr;
	int count_check = 0;
	Student me = user->student;
	Student you = me;
    
	while (you.my_course->course->next != nullptr)
        you.my_course = you.my_course->next;
    string sem = you.my_course->sem;
    string year = you.my_course->year;

    while (me.my_course->year != year && me.my_course->sem != sem)
        me.my_course = me.my_course->next;

	for (MyCourse* cur = user->student.my_course; cur; cur = cur->next)
	{
		if (cur->year == data.year && cur->sem == data.sem)
		{
			count_check++;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		a_class[i] = nullptr;
		square[i] = createObjectTest("content/Registration/Asset 118.png", 174.0f * scale, (388.0f + 60.0f * i) * scale);
		
		num[i] = createInfoTest("content/Oswald-Regular.ttf", "", 198.0f * scale, (396.0f + 60.0f * i) * scale, 25.0f * scale);
		inf[i] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 198.0f * scale, (396.0f + 60.0f * i) * scale, 25.0f * scale);
	}
	bool in_here[4], first_check = true;
	int current_students[4];
	Object** border = square;
	Info count_class = createInfo("content/Oswald-Regular.ttf", to_string(count_check) + "/5 Courses", 200.0f * scale, 346.0f * scale, 15.0f * scale);
	count_class.text.setFillColor(Color::White);

	while (window.isOpen() && page == 13)
	{
		Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
			{
				window.close();
				break;
			}
			case Event::MouseButtonReleased:
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					switchPage(out.bound, mouse, 1, page);
					switchPage(back.bound, mouse, 3, page);
					if (!add_new)
					{
						if (isHere(right.bound, mouse) && change <= count - 4)
						{
							trigger_page = true;
							change += 4;
						}
						if (isHere(left.bound, mouse) && change != 0)
						{
							trigger_page = true;
							change -= 4;
						}
						start_date.check = isHere(start_date.bound, mouse);
						end_date.check = isHere(end_date.bound, mouse);
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
		window.draw(header.text);
		window.draw(sub_header.text);
		if (change == 0 && change >= count - 4)
		{
			window.draw(right.draw);
			window.draw(left.draw);
		}
		else if (change == 0)
		{
			window.draw(left.draw);
			drawWhich(window, right_here, right_valid, mouse);
		}
		else if (change >= count - 4)
		{
			window.draw(right.draw);
			drawWhich(window, left_here, left_valid, mouse);
		}
		else
		{
			drawWhich(window, right_here, right_valid, mouse);
			drawWhich(window, left_here, left_valid, mouse);
		}
		if (trigger_page)
		{
			MyCourse *temp = me.my_course;
			CourseNode* cur = temp->course;
			/*for (int i = 0; i < change; i++)
			{
				cur = cur->next;
			}*/
			for (int i = 0; i < 4; i++)
			{
				cur = temp->course;
				a_class[i] = cur;
				if (temp)
				{
					inf[i]->text.setString(a_class[i]->course.course_id + " - " + a_class[i]->course.teacher_name + " (" + day_convert(a_class[i]->course.teaching_session[0]) + "-" + no_convert(a_class[i]->course.teaching_session[0]) + ", " + day_convert(a_class[i]->course.teaching_session[1]) + "-" + no_convert(a_class[i]->course.teaching_session[1]) + ")");
					
					num[i]->text.setPosition(square[i]->bound.left + square[i]->bound.width - num[i]->text.getGlobalBounds().width - 30.0f, (396.0f + 60.0f * i) * scale);
					temp = temp->next;
				}
				else
				{
					inf[i]->text.setString("");
					num[i]->text.setString("");
				}
			}
			trigger_page = false;
		}

		drawWhich(window, out_here, out, mouse);
		drawWhich(window, back_here, back, mouse);
		// draw border
		if (sub_check)
		{
			for (int i = 0; i < 4; i++)
			{
				if (inf[i]->text.getString() == "")
					break;
				
				if (stop)
				{
					window.draw(border[i]->draw);
					inf[i]->text.setFillColor(Color(46, 58, 112));
					num[i]->text.setFillColor(Color(46, 58, 112));
				}
				else
				{				
					{
						inf[i]->text.setFillColor(Color(46, 58, 112));
						num[i]->text.setFillColor(Color(46, 58, 112));
					}
				}
				window.draw(inf[i]->text);
				window.draw(num[i]->text);
			}
		}
		else
		{
			for (int i = 0; i < 4; i++)
			{
				if (inf[i]->text.getString() == "")
					break;
				if (in_here[i])
				{
					{
						{
							inf[i]->text.setFillColor(Color(118, 36, 2));
							num[i]->text.setFillColor(Color(118, 36, 2));
						}
					}
				}
				else
				{
					window.draw(border[i]->draw);
					inf[i]->text.setFillColor(Color(46, 58, 112));
					num[i]->text.setFillColor(Color(46, 58, 112));
				}
				window.draw(inf[i]->text);
				window.draw(num[i]->text);
			}
		}
		if (stop)
		{
			if (success)
			{
				window.draw(del_success.draw);
				drawWhich(window, return1_here, return1, mouse);
			}
			if (fail)
			{
				window.draw(invalid.draw);
				drawWhich(window, return1_here, return1, mouse);
			}
		}
		window.draw(start_date.text);
		window.draw(end_date.text);
		window.display();
	}
	for (int i = 0; i < 4; i++)
		delete square[i], square_here[i], inf[i], num[i];
}