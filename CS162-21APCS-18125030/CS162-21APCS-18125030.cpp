#include "views.h"

int main()
{
	//------------------ demo data-----------------------------
	// Student meme = createStudent(1, "21125011", "Nghia", "Nguyen Trong", 0, "12/12/2003", "123273862");
	// meme.password = "demo";
	// meme.student_class = "21CTT1 - APCS";
	// StudentNode* me = nullptr;
	// appendNewStudentNode(&me, meme);

	string class_input_path = "./csv/class_input.csv";
	string class_output_path = "./csv/class_output.csv";

	ClassNode *all_classes = nullptr;
	// readFromFileClassNode(class_input_path, all_classes);
	readFromFileClassNode(class_input_path, all_classes);

	string staff_input_path = "./csv/staff_input.csv";
	string staff_output_path = "./csv/staff_output.csv";
	StudentNode *all_staffs = nullptr;

	readFromFileStudentNode(staff_input_path, &all_staffs);

	string school_input_path = "./csv/schoolyear_input.csv";
	string school_output_path = "./csv/schoolyear_output.csv";

	YearNode *school = nullptr;
	readFromFileYearNode(school_input_path, &school);

	string student_input_path = "./csv/student_input.csv";
	string student_output_path = "./csv/student_output.csv";
	ClassNode *all_classes1 = nullptr;

	readFromFileClassNode1(student_input_path, all_classes1);

	// Testing student & student list functions

	// if (new_list)
	// {
	// 	removeStudentNode(&new_list, "18125030");
	// 	new_list->student.password = "TrTRTR";
	// 	writeToFileStudentNode(student_output_path, new_list);
	// }

	// // // Testing course and course list functions
	// string course_input_path = "sample_course_data.csv";
	// string course_output_path = "sample_course_output.csv";
	// CourseNode* new_course_list = nullptr;
	// readFromFileCourseNode(course_input_path, &new_course_list);
	// if (new_course_list)
	// {
	// 	removeCourseNode(&new_course_list, "PHY101");
	// 	writeToFileCourseNode(course_output_path, new_course_list);
	// }
	// ------------------------------------------------------------

	RenderWindow window;
	Image icon;
	icon.loadFromFile("content/icon.png");
	float scale = 1.5f;
	window.create(VideoMode(1000.0f * scale, 750.0f * scale), "CS162-Project", Style::Close);
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	int page = 1;

	StudentNode *user = NULL;
	bool is_staff;

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
			if (!is_staff)
				findMyCourses(&user, school);
			break;
		}
		case 3:
		{
			studentHome(window, page, scale);
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
			view_year(window, page, scale, school, user, is_staff);

			break;
		}
		case 8:
		{
			break;
		}
		case 9:
		{
			break;
		}
		default:
		{
			break;
		}
		}
	}

	// save all data
	writeToFileClassNode(class_output_path, all_classes);
	writeToFileStudentNode(staff_output_path, all_staffs);
	writeToFileYearNode(school_output_path, school);
	writeToFileClassNode1(student_output_path, all_classes1);

	// delete all SLL
	deleteClassNode(all_classes);
	deleteStudentList(all_staffs);
	deleteClassNode(all_classes1);

	// deleteStudentList(me);
	return 0;
}
