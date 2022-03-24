#include "class.h"
#include "student_list.h"
void checkMyClass(Class a){
    printStudentNode(a.student_list);
}
ClassNode* Create_List_Class(ClassNode* &Class_head,string class_name,string head_teacher) {
	ClassNode* pClass = new ClassNode;
	pClass->my_class.class_id = class_name;
	pClass->my_class.head_teacher = head_teacher;
	pClass->next = NULL;
	ClassNode* tmp = Class_head;
	if (tmp == NULL)
		Class_head = pClass;
	else {
		while (tmp->next != NULL) {
			tmp = tmp->next;
		}tmp->next = pClass;
	}
	return Class_head;
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
