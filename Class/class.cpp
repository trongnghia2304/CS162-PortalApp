#include "class.h"

void checkMyClass(Class a){
    printStudentNode(a.student_list);
}
Class createClass(string C_id, string H_Tea, StudentNode* StuLis) {
	Class new_Class;
	new_Class.class_id.assign(C_id);
	new_Class.head_teacher.assign(H_Tea);
	new_Class.student_list = StuLis;
	return new_Class;
}
