#include "StudentList/student_list.h"
#include "Student/student.h"

using namespace std;

int main()
{

    
    
    string path = "student_sample_data.csv";
    StudentNode *new_list = nullptr;

    readFromFileStudentNode(path, &new_list);
    printStudentNode(new_list);

    removeStudentNode(&new_list, "18125030");

    string output_path = "sample_student_output.csv";
    new_list->student.password = "TrTRTR";
    writeToFileStudentNode(output_path, new_list);
    return 0;
}