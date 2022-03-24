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
void InputClassFromFile(ifstream& ifs, ClassNode* &Class_head) {
	ClassNode* tmp=new ClassNode;
	while (!ifs.eof()) {
		getline(ifs, tmp->my_class.class_id);
		getline(ifs, tmp->my_class.head_teacher);
		Create_List_Class(Class_head, tmp->my_class.class_id, tmp->my_class.head_teacher);
	}delete tmp;
}
void Add_Student_to_1_Class(Class &a, StudentNode* Student_head) {
	a.student_list = NULL;
	StudentNode* pStudent = Student_head,*pClass=a.student_list;
	while (pStudent != NULL && pStudent->next != NULL) {
		if (pStudent->student.student_class == a.class_id) {
			if (pClass == NULL) {
				a.student_list = initStudentNode(pStudent->student);
			}
			else {
				while (pClass->next != NULL)
					pClass = pClass->next;
				pClass->next = initStudentNode(pStudent->student);
			}pStudent = pStudent->next;
		}
	}
}
void Add_Student_to_all_Class(ClassNode* Class_head, StudentNode* Student_head) {
	ClassNode* pClass = Class_head;
	StudentNode* pStudent = Student_head;
	while (pClass != NULL && pClass->next != NULL) {
		Add_Student_to_1_Class(pClass->my_class, pStudent);
		pClass = pClass->next;
		pStudent = Student_head;
	}
}
void View_Student_in_Class(ClassNode* Class_head) {
	ClassNode* pClass = Class_head;
	StudentNode* pStudent = pClass->my_class.student_list;
	string class_name;
	cout << "What class you want to view Student List ? ";
	getline(cin, class_name);
	while (pClass != NULL && pClass->next != NULL) {
		if (pClass->my_class.class_id == class_name) {
			printStudentNode(pClass->my_class.student_list);
		}pClass = pClass->next;
	}
}
void View_List_of_Class(ClassNode* Class_head) {
	ClassNode* pClass = Class_head;
	while (pClass != NULL) {
		cout << pClass->my_class.class_id << " " << pClass->my_class.head_teacher;
		pClass = pClass->next;
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

