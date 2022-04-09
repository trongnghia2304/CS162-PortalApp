#include "views.h"

void Scene1(RenderWindow& window, int& page, bool& is_staff, const float& scale)
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

void logIn(RenderWindow& window, int& page, bool is_staff, const float& scale, ClassNode* class_list, StudentNode* staff_list, StudentNode*& user)
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
	ClassNode* check_class = nullptr;
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
				while (!user || check_class)
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
void studentHome(RenderWindow& window, int& page, const float& scale)
{
	Event event;
	Object screen = createObject("content/Student.png");
	Object *b[6], *a[6];
	Object out = createObject("content/logout.png", 866.0f * scale, 106.0f * scale);
	Object out_here = createObject("content/logout1.png", 866.0f * scale, 106.0f * scale);

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
					if (event.mouseButton.button == Mouse::Left)
					{
						switchPage(out.bound, mouse, 1, page);
						switchPage(a[0]->bound, mouse, 5, page);
						for (int i = 0; i < 6; i++)
						{
							if (isHere(a[i]->bound, mouse))
							{
								// each functions
							}
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

void staffHome(RenderWindow& window, int& page, const float& scale)
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
				case Event::Closed: {
					window.close();
					break;
				}
				case Event::MouseButtonReleased: {
					if (isHere(out.bound, mouse))
					{
						page = 1;
						break;
					}
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

void profile(RenderWindow& window, int& page, const float& scale, StudentNode* student, bool is_staff)
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

	Info* inf[6];
	for (int i = 0; i < 6; i++)
		inf[i] = createInfoTest("content/Oswald-Light.ttf", text[i], 318.0f * scale, (303.0f + 56.0f * i) * scale, 20 * scale);
	changePos(inf[4], 318.0f * scale, (303.0f + 56.0 * 5) * scale);
	changePos(inf[5], 593.0f * scale, (303.0f + 56.0 * 5) * scale);
	changePos(inf[3], 318.0f * scale, (303.0f + 56.0 * 4) * scale);
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
				case Event::Closed: {
					window.close();
					break;
				}
				case Event::MouseButtonReleased: {
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
								case 1: {
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
								case 2: {
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
								default: {
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
				case Event::TextEntered: {
					if (password_status == 1)
					{
						texting(pw, event.text.unicode, 10);
						texting(pw_old, event.text.unicode, 10);
					}
					break;
				}
				default: {
					break;
				}
			}
		}
		window.clear();
		window.draw(screen.draw);
		for (int i = 0; i < 6; i++)
			window.draw(inf[i]->text);
		window.draw((gender ? a[5]->draw : b[5]->draw));
		if (view_my_class || password_window)
		{
			window.draw(a[3]->draw);
			window.draw(a[4]->draw);

			if (password_window)
			{
				switch (password_status)
				{
					// case -1: {
					// 	password_window = false;
					// 	break;
					// }
					case 1: {
						window.draw(enter.draw);
						window.draw(pw_old.text);
						window.draw(pw.text);
						drawWhich(window, b[0], a[0], mouse);
						break;
					}
					case 2: {
						// cout << "here";
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
					default: {
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

void view_class(RenderWindow& window, int& page, const float& scale, ClassNode* class_list, StudentNode* user)
{
	Event event;
	Object screen = createObject("content/Student/my_class.png");
	Object out = createObject("content/logout.png", 866.0f * scale, 106.0f * scale);
	Object out_here = createObject("content/logout1.png", 866.0f * scale, 106.0f * scale);
	Object back = createObject("content/return.png", 80.0f * scale, 106.0f * scale);
	Object back_here = createObject("content/return1.png", 80.0f * scale, 106.0f * scale);
	Object add_student = createObject("content/Student/add.png", 682.0f * scale, 273.0f * scale);
	Object add_student_here = createObject("content/Student/add1.png", 682.0f * scale, 273.0f * scale);
	Object left = createObject("content/Staff/Class/Asset 57.png", 493.0f * scale, 542.0f * scale);
	Object left_here = createObject("content/Staff/Class/Asset 55.png", 493.0f * scale, 542.0f * scale);
	Object right = createObject("content/Staff/Class/Asset 56.png", 493.0f * scale, 542.0f * scale);
	Object right_here = createObject("content/Staff/Class/Asset 54.png", 510.0f * scale, 542.0f * scale);
	ClassNode* my_class = searchClassNode(class_list, user->student.student_class);
	Info sub_header = createInfo("content/VNI-Vari.TTF", "Class - " + my_class->my_class.head_teacher, 160.0f * scale, 158.0f * scale, 28.0f * scale);
	Info header = createInfo("content/VNI-Vari.TTF", my_class->my_class.class_id, 160.0f * scale, 200.0f * scale, 43.0f * scale);
	Info* inf[8][6];
	for (int i = 0; i < 6; i++)
	{
		inf[i][0] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 184.0f * scale, (370.0f + 30.0f * i) * scale, 17.5 * scale);
		inf[i][1] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 224.0f * scale, (370.0f + 30.0f * i) * scale, 17.5 * scale);
		inf[i][2] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 345.0f * scale, (370.0f + 30.0f * i) * scale, 17.5 * scale);
		inf[i][3] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 515.0f * scale, (370.0f + 30.0f * i) * scale, 17.5 * scale);
		inf[i][4] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 633.0f * scale, (370.0f + 30.0f * i) * scale, 17.5 * scale);
		inf[i][5] = createInfoTest("content/Oswald-Regular.ttf", "demo_text", 715.0f * scale, (370.0f + 30.0f * i) * scale, 17.5 * scale);
		for (int j = 0; j < 6; j++)
			inf[i][j]->text.setFillColor(Color::Black);
	}
	int count = 0, change = 0;
	bool trigger_page = false;
	for (StudentNode* cur = my_class->my_class.student_list; cur; cur = cur->next)
	{
		count++;
	}
	Info count_student = createInfo("content/Oswald-Regular.ttf", "Total: " + to_string(count) + " Students", 180.0f * scale, 280.0f * scale, 15.0f * scale);
	count_student.text.setFillColor(Color::White);
	while (window.isOpen() && page == 6)
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
						switchPage(out.bound, mouse, 1, page);
						switchPage(back.bound, mouse, 5, page);
						if (isHere(add_student.bound, mouse))
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
			drawWhich(window, right_here, right, mouse);
		}
		else if (count >= count - 8)
		{
			window.draw(right.draw);
			drawWhich(window, left_here, left, mouse);
		}
		else
		{
			drawWhich(window, right_here, right, mouse);
			drawWhich(window, left_here, left, mouse);
		}
		if (trigger_page)
		{
			StudentNode* cur = my_class->my_class.student_list;
			for (int i = 0; i < change * 8; i++)
			{
				cur = cur->next;
			}
			for (int i = 0; i < 8; i++)
			{
				if (cur)
				{
					inf[i][0]->text.setString(to_string(cur->student.num));
					inf[i][1]->text.setString(to_string(cur->student.num));
					inf[i][2]->text.setString(to_string(cur->student.num));
					inf[i][3]->text.setString(to_string(cur->student.num));
					inf[i][4]->text.setString(to_string(cur->student.num));
					inf[i][5]->text.setString(to_string(cur->student.num));
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