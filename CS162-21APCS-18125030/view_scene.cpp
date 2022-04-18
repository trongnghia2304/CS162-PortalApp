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
void studentHome(RenderWindow &window, int &page, const float &scale)
{
	Event event;
	Object screen = createObject("content/Student.png");
	Object *b[6], *a[6];
	Object out = createObject("content/logout.png", 866.0f * scale, 106.0f * scale);
	Object out_here = createObject("content/logout1.png", 866.0f * scale, 106.0f * scale);

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
					switchPage(out.bound, mouse, 1, page);
					switchPage(a[0]->bound, mouse, 5, page);
					switchPage(a[1]->bound, mouse, 7, page);
					switchPage(a[3]->bound, mouse, 8, page);
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
			for (int j = 0; j < 6; j++)
			{
				drawWhich(window, b[j], a[j], mouse);
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
				switchPage(a[0]->bound, mouse, 5, page);
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

void view_class(RenderWindow &window, int &page, const float &scale, ClassNode *class_list, StudentNode *user, const bool &is_staff)
{
	Event event;
	Object screen = createObject("content/Student/my_class.png");
	Object out = createObject("content/logout.png", 866.0f * scale, 106.0f * scale);
	Object out_here = createObject("content/logout1.png", 866.0f * scale, 106.0f * scale);
	Object back = createObject("content/return.png", 80.0f * scale, 106.0f * scale);
	Object back_here = createObject("content/return1.png", 80.0f * scale, 106.0f * scale);
	Object add_student = createObject("content/Student/add.png", 682.0f * scale, 273.0f * scale);
	Object add_student_here = createObject("content/Student/add1.png", 682.0f * scale, 273.0f * scale);
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
					// is_staff: true -> switch to the class
					switchPage(back.bound, mouse, 5, page);
					if (isHere(add_student.bound, mouse) && is_staff)
					{
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
		inf[i][1] = createInfoTest("content/Oswald-Medium.ttf", "demo_text", (185.0f + 220.0f * i) * scale, 378.0f * scale, 12.5f * scale);
		inf[i][2] = createInfoTest("content/Oswald-Medium.ttf", "demo_text", (185.0f + 220.0f * i) * scale, 400.0f * scale, 12.5f * scale);
		inf[i][3] = createInfoTest("content/Oswald-Medium.ttf", "demo_text", (185.0f + 220.0f * i) * scale, 422.0f * scale, 12.5f * scale);
	}
	for (int i = 3; i < 6; i++)
	{
		course[i] = nullptr;
		square[i] = createObjectTest("content/Student/course.png", (172.0f + 220.0f * (i - 3)) * scale, 480.0f * scale);
		square_here[i] = createObjectTest("content/Student/course_here.png", (172.0f + 220.0f * (i - 3)) * scale, 480.0f * scale);
		inf[i][0] = createInfoTest("content/Oswald-Medium.ttf", "demo_text", (243.0f + 220.0f * (i - 3)) * scale, 485.0f * scale, 25.0f * scale);
		inf[i][1] = createInfoTest("content/Oswald-Medium.ttf", "demo_text", (185.0f + 220.0f * (i - 3)) * scale, 532.0f * scale, 12.5f * scale);
		inf[i][2] = createInfoTest("content/Oswald-Medium.ttf", "demo_text", (185.0f + 220.0f * (i - 3)) * scale, 554.0f * scale, 12.5f * scale);
		inf[i][3] = createInfoTest("content/Oswald-Medium.ttf", "demo_text", (185.0f + 220.0f * (i - 3)) * scale, 576.0f * scale, 12.5f * scale);
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
							page = 10;
							course_student(window, page, scale, course[i]);
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
		else if (count >= count - 6)
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
					inf[i][3]->text.setString("Credit: " + to_string(cur->course->course.num_credit));
					inf[i][0]->text.setPosition(Vector2f(square[i]->bound.left + (square[i]->bound.width - inf[i][0]->text.getGlobalBounds().width) / 2, square[i]->bound.top + 13.0f));
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
			if (drawWhich(window, square_here[i], square[i], mouse))
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
void view_course(RenderWindow &window, int &page, const float &scale, CourseNode *my_course, const bool &is_staff)
{
	Event event;
	Object *screen = createObjectTest("content/Staff/course_staff.png");
	Object out = createObject("content/logout.png", 866.0f * scale, 106.0f * scale);
	Object out_here = createObject("content/logout1.png", 866.0f * scale, 106.0f * scale);
	Object back = createObject("content/return.png", 80.0f * scale, 106.0f * scale);
	Object back_here = createObject("content/return1.png", 80.0f * scale, 106.0f * scale);
	Object add_course = createObject("content/Student/add_course.png", 680.0f * scale, 272.0f * scale);
	Object add_course_here = createObject("content/Student/add_course_here.png", 680.0f * scale, 272.0f * scale);
	Object left = createObject("content/Staff/Class/Asset 57.png", 492.0f * scale, 644.0f * scale);
	Object left_valid = createObject("content/Staff/Class/Asset 55.png", 492.0f * scale, 644.0f * scale);
	Object left_here = createObject("content/Staff/Class/Asset 91.png", 492.0f * scale, 644.0f * scale);
	Object right = createObject("content/Staff/Class/Asset 56.png", 510.0f * scale, 644.0f * scale);
	Object right_here = createObject("content/Staff/Class/Asset 90.png", 510.0f * scale, 644.0f * scale);
	Object right_valid = createObject("content/Staff/Class/Asset 54.png", 510.0f * scale, 644.0f * scale);
	Info sub_header = createInfo("content/VNI-Vari.TTF", my_course->year_id, 160.0f * scale, 158.0f * scale, 28.0f * scale);
	sub_header.text.setFillColor(Color(101, 159, 235));
	Info header = createInfo("content/VNI-Vari.TTF", my_course->semester_id, 160.0f * scale, 200.0f * scale, 43.0f * scale);
	Info *inf[6][4];
	Object *square[6], *square_here[6];
	CourseNode *course[6];
	for (int i = 0; i < 3; i++)
	{
		square[i] = createObjectTest("content/Student/course.png", (172.0f + 220.0f * i) * scale, 322.0f * scale);
		square_here[i] = createObjectTest("content/Student/course_here.png", (172.0f + 220.0f * i) * scale, 322.0f * scale);
		inf[i][0] = createInfoTest("content/Oswald-Medium.ttf", "demo_text", (243.0f + 220.0f * i) * scale, 330.0f * scale, 25.0f * scale);
		inf[i][1] = createInfoTest("content/Oswald-Medium.ttf", "demo_text", (185.0f + 220.0f * i) * scale, 378.0f * scale, 12.5f * scale);
		inf[i][2] = createInfoTest("content/Oswald-Medium.ttf", "demo_text", (185.0f + 220.0f * i) * scale, 400.0f * scale, 12.5f * scale);
		inf[i][3] = createInfoTest("content/Oswald-Medium.ttf", "demo_text", (185.0f + 220.0f * i) * scale, 422.0f * scale, 12.5f * scale);
	}
	for (int i = 3; i < 6; i++)
	{
		course[i] = nullptr;
		square[i] = createObjectTest("content/Student/course.png", (172.0f + 220.0f * (i - 3)) * scale, 480.0f * scale);
		square_here[i] = createObjectTest("content/Student/course_here.png", (172.0f + 220.0f * (i - 3)) * scale, 480.0f * scale);
		inf[i][0] = createInfoTest("content/Oswald-Medium.ttf", "demo_text", (243.0f + 220.0f * (i - 3)) * scale, 485.0f * scale, 25.0f * scale);
		inf[i][1] = createInfoTest("content/Oswald-Medium.ttf", "demo_text", (185.0f + 220.0f * (i - 3)) * scale, 532.0f * scale, 12.5f * scale);
		inf[i][2] = createInfoTest("content/Oswald-Medium.ttf", "demo_text", (185.0f + 220.0f * (i - 3)) * scale, 554.0f * scale, 12.5f * scale);
		inf[i][3] = createInfoTest("content/Oswald-Medium.ttf", "demo_text", (185.0f + 220.0f * (i - 3)) * scale, 576.0f * scale, 12.5f * scale);
	}
	int count = 0, change = 0;
	bool trigger_page = true;
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
						// add new course
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
					for (int i = 0; i < 6; i++)
					{
						if (isHere(square[i]->bound, mouse) && course[i])
						{
							page = 10;
							course_student(window, page, scale, course[i]);
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
		else if (count >= count - 6)
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
					inf[i][3]->text.setString("Credit: " + to_string(cur->course.num_credit));
					inf[i][0]->text.setPosition(Vector2f(square[i]->bound.left + (square[i]->bound.width - inf[i][0]->text.getGlobalBounds().width) / 2, square[i]->bound.top + 13.0f));
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
			if (drawWhich(window, square_here[i], square[i], mouse))
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

void course_student(RenderWindow &window, int &page, const float &scale, CourseNode *course)
{
	Event event;
	Object export1 = createObject("content/Staff/Create elements/export.png", 680.0f * scale, 272.0f * scale);
	Object export1_here = createObject("content/Staff/Create elements/export_here.png", 680.0f * scale, 272.0f * scale);
	Object screen = createObject("content/Student/my_class.png");
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
	for (StudentNode *cur = course->student_list; cur; cur = cur->next)
	{
		count++;
	}
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

void view_year(RenderWindow &window, int &page, const float &scale, YearNode *year, StudentNode *user, const bool &is_staff)
{
	YearNode *cur_year = year;
	Event event;
	Object *screen;
	if (is_staff)
		screen = createObjectTest("content/year_staff.png");
	else
	{
		MyCourse *cur = user->student.my_course;
		while (cur_year && cur_year->school_year.year_id != cur->year)
			cur_year = cur_year->next;
		screen = createObjectTest("content/year.png");
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
					// is_staff: true -> switch to the courses
					switchPage(back.bound, mouse, (is_staff ? 4 : 3), page);
					if (isHere(add_year.bound, mouse))
					{
						// add new year
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
							view_semester(window, page, scale, a_year[i], user, is_staff);
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
		else if (count >= count - 4)
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
		for (int i = 0; i < 6; i++)
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

void view_semester(RenderWindow &window, int &page, const float &scale, YearNode *cur_year, StudentNode *user, const bool &is_staff)
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
		square[i] = createObjectTest("content/Student/Asset " + to_string(104 + i) + ".png", (172.0f + 225.0f * i) * scale, 368.0f * scale);
		square_here[i] = createObjectTest("content/Student/Asset " + to_string(107 + i) + ".png", (172.0f + 225.0f * i) * scale, 368.0f * scale);
	}
	int count = 0, change = 0;
	bool trigger_page = true;
	for (SemesterNode *cur = cur_year->school_year.list_sem; cur; cur = cur->next)
		count++;
	Info count_course = createInfo("content/Oswald-Regular.ttf", "Total: " + to_string(count) + " Semesters", 200.0f * scale, 279.0f * scale, 15.0f * scale);
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
							if (is_staff)
								view_course(window, page, scale, a_sem[i]->sem.course_list, is_staff);
							else
							{
								string year = cur_year->school_year.year_id;
								string sem = a_sem[i]->sem.semester_id;
								view_course(window, page, scale, user, is_staff, sem, year);
							}
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
	float k = count_gpa / (float)count_course;
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
					switchPage(split.bound, mouse, 9, page);
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
		drawWhich(window, out_here, out, mouse);
		drawWhich(window, back_here, back, mouse);
		drawWhich(window, split_here, split, mouse);
		window.draw(header.text);
		window.draw(sub_header.text);
		window.draw(count_student.text);
		window.draw(gpa_here.text);
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
	string sem = "";
	bool trigger_page = true;
	float gpa_count = 0.0f, k;
	for (MyCourse *cur = user->student.my_course; cur; cur = cur->next)
	{
		if (cur->sem != sem)
		{
			sem = cur->sem;
			sub_page++;
		}
	}
	sem = user->student.my_course->sem;
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
					if (isHere(next[0]->bound, mouse) && change <= sub_page)
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
			window.draw(pre[3]->draw);
			drawWhich(window, next[1], next[2], mouse);
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
			MyCourse *cur = user->student.my_course;
			for (int i = 0; i < change - 1; i++)
			{
				string tmp = cur->sem;
				while (cur->sem == sem)
					cur = cur->next;
				sem = tmp;
			}
			sem = cur->sem;
			header.text.setString(cur->year + " " + sem);
			count = 0;
			for (int i = 0; i < 8; i++)
			{
				if (cur && cur->sem == sem)
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