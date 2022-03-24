#include "student_studentList.cpp"
#include "course_CourseList.cpp"

using namespace std;

int main()
{
    // Testing student & student list functions
    string student_input_path = "student_sample_data.csv";
    string student_output_path = "sample_student_output.csv";
    StudentNode *new_list = nullptr;

    readFromFileStudentNode(student_input_path, &new_list);
    if (new_list)
    {
        removeStudentNode(&new_list, "18125030");
        new_list->student.password = "TrTRTR";
        writeToFileStudentNode(student_output_path, new_list);
    }

    // // Testing course and course list functions
    string course_input_path = "sample_course_data.csv";
    string course_output_path = "sample_course_output.csv";
    CourseNode *new_course_list = nullptr;
    readFromFileCourseNode(course_input_path, &new_course_list);
    if (new_course_list)
    {
        removeCourseNode(&new_course_list, "PHY101");
        writeToFileCourseNode(course_output_path, new_course_list);
    }

    return 1;
}