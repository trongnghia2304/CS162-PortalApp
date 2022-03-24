#include "class.h"
#include "student_list.h"
void checkMyClass(Class a){
    printStudentNode(a.student_list);
}
Class createClass(string C_id, string H_Tea ) {
	Class new_Class;
	new_Class.class_id.assign(C_id);
	new_Class.head_teacher.assign(H_Tea);
	
	return new_Class;
}
void AddStudenttoClass(Class &a, StudentNode* stu) {
	a.student_list = NULL;
	StudentNode*tmp,* copy;
	while (stu->next != NULL)
	{
		if (stu->student.student_class == a.class_id)
		{
			copy = a.student_list;
		tmp = initStudentNode(stu->student);
			
			if (copy == NULL) {
				a.student_list = copy;
			}
			else {
				while (copy->next != NULL)
					copy = copy->next;
				copy->next = tmp;
			}
		}
	}
}

void deleteClass(ClassNode* head){
	while(head){
		ClassNode* cur = head;
		deleteStudentList(cur->my_class.student_list);
		head = head->next;
		delete cur;
	}
}

