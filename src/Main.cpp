#include "views.h"

int main()
{
#if defined(_DEBUG)
#endif
	//------------------ demo data-----------------------------
	// Student meme = createStudent(1, "21125011", "Nghia", "Nguyen Trong", 0, "12/12/2003", "123273862");
	// meme.password = "demo";
	// meme.student_class = "21CTT1 - APCS";
	// StudentNode* me = nullptr;
	// appendNewStudentNode(&me, meme);

	string class_input_path = "all_classes.csv";
	ClassNode* all_classes = nullptr;

	// Testing student & student list functions
	// string student_input_path = "student_sample_data.csv";
	// string student_output_path = "sample_student_output.csv";
	// StudentNode* new_list = nullptr;

	// readFromFileStudentNode(student_input_path, &new_list);
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
	int page = 5;

	// staff(1), student(0)
	bool is_staff;
	while (page > 0 && window.isOpen())
	{
		switch (page)
		{
			case 1: {
				Scene1(window, page, is_staff, scale);
				break;
			}
			case 2: {
				logIn(window, page, is_staff, scale);
				break;
			}
			case 3: {
				studentHome(window, page, scale);
				break;
			}
			case 4: {
				staffHome(window, page, scale);
				break;
			}
			case 5: {
				profile(window, page, scale, me);
			}
			default: {
				break;
			}
		}
	}

	deleteStudentList(me);
	return 0;
}
