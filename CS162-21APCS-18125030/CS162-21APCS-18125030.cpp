#include "views.h"

int main()
{
	//------------------ demo data-----------------------------
	string staff_input_path = "./csv/staff_input.csv";
	string staff_output_path = "./csv/staff_output.csv";
	string school_input_path = "./csv/schoolyear_input.csv";
	string school_output_path = "./csv/schoolyear_output.csv";
	string student_input_path = "./csv/student_input.csv";
	string student_output_path = "./csv/student_output.csv";
	string registration_input_path = "./csv/registration_day.csv";
	string registration_output_path = "./csv/registration_day_output.csv";

	YearNode *school = nullptr;
	StudentNode *all_staffs = nullptr;
	ClassNode *all_classes1 = nullptr;
	RegistrationSession data;

	readFromFileStudentNode(staff_input_path, &all_staffs);
	readFromFileYearNode(school_input_path, &school);
	readFromFileClassNode1(student_input_path, all_classes1);
	readFromFileRegSess(registration_input_path, data);

	setupMyCourses(all_classes1, school);
	// ----------------------------------------------------------

	RenderWindow window;
	Image icon;
	icon.loadFromFile("content/icon.png");
	float scale = 1.5f;
	window.create(VideoMode(1000.0f * scale, 750.0f * scale), "CS162-Project", Style::Close);
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	int page = 1;
	StudentNode *user = NULL;
	bool is_staff;
	string year = "2021-2022", semester = "Semester 2";

	while (page > 0 && window.isOpen())
	{
		switch (page)
		{
		case 1:
		{
			Scene1(window, page, is_staff, scale);
			break;
		}
		case 2:
		{
			logIn(window, page, is_staff, scale, all_classes1, all_staffs, user);
			break;
		}
		case 3:
		{
			studentHome(data, window, page, scale);
			break;
		}
		case 4:
		{
			staffHome(window, page, scale);
			break;
		}
		case 5:
		{
			profile(window, page, scale, user, is_staff);
			break;
		}
		case 6:
		{
			view_class(window, page, scale, all_classes1, user, is_staff);
			break;
		}
		case 7:
		{
			view_year(window, page, scale, school, user, is_staff, all_classes1);
			break;
		}
		case 8:
		{
			while (page == 8 || page == 9)
			{
				if (page == 8)
					view_score(window, page, scale, user, is_staff);
				else
					view_score2(window, page, scale, user, is_staff);
			}
			break;
		}
		case 9:
		{
			view_class_list(year, semester, window, page, scale, all_classes1, is_staff);
			break;
		}
		case 11:
		{
			if (is_staff)
				view_registration_staff(school, window, page, scale, data, is_staff);
			else
				view_registration_student(school, window, page, scale, data, is_staff, user);
			break;
		}
		default:
		{
			break;
		}
		}
	}
	// save all data
	writeToFileStudentNode(staff_output_path, all_staffs);
	writeToFileYearNode(school_output_path, school);
	writeToFileClassNode1(student_output_path, all_classes1);
	writeToFileRegSess(registration_output_path, data);

	// delete all SLL
	deleteStudentList(all_staffs);
	deleteClassNode(all_classes1);
	deleteYearNode(school);
	deleteCourseNode(data.list_of_courses);
	return 0;
}