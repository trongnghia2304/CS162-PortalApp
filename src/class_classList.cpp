#include "header.h"

//--------------------------------- Class & ClassList ----------------------------------------------
//--------------------------------------------------------------------------------------------------
Class createClass(string p_class_id, string p_head_teacher)
{
    Class new_class;
    new_class.class_id.assign(p_class_id);
    new_class.head_teacher.assign(p_head_teacher);
    return new_class;
}
ClassNode *initClassNode(Class p_new_class)
{
    ClassNode *new_class_node = new ClassNode;
    new_class_node->my_class = p_new_class;
    new_class_node->next = nullptr;
    return new_class_node;
}
ClassNode *searchClassNode(ClassNode *p_head, string p_class_id)
{
    if (!p_head)
    {
        cout << "Cannot find the searched class...\n";
        return nullptr;
    }
    ClassNode *temp = p_head;
    while (temp && temp->my_class.class_id != p_class_id)
    {
        temp = temp->next;
    }
    return temp;
}
void pushNewClassNode(ClassNode *&p_head, Class p_new_class)
{
    ClassNode *new_class_node = initClassNode(p_new_class);
    if (p_head==NULL)
    {
        p_head = new_class_node;
        return;
    }
    new_class_node->next = p_head;
    p_head = new_class_node;
}
void appendNewClassNode(ClassNode *p_head, Class p_new_class)
{
    ClassNode *new_class_node = initClassNode(p_new_class);
    if (p_head==NULL)
    {
        p_head = new_class_node;
        return;
    }
    else
    {
        ClassNode *temp = p_head;
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = new_class_node;
        return;
    }
}
void removeClassNode(ClassNode **p_head, string p_class_id)
{
    ClassNode *founded_class = searchClassNode(*p_head, p_class_id);
    if (!*p_head || !founded_class)
    {
        cout << "Cannot find the searched class...\n";
        return;
    }

    if ((*p_head)->my_class.class_id == p_class_id)
    {
        ClassNode *temp = *p_head;
        (*p_head) = (*p_head)->next;
        delete temp;
        return;
    }

    ClassNode *temp = *p_head;
    while (temp->next != founded_class)
    {
        temp = temp->next;
    }
    temp->next = founded_class->next;
    delete founded_class;
}
void addStudentToClass(ClassNode*&p_head_class, StudentNode*p_head_student) {
	ClassNode *tmp_class = p_head_class;
	StudentNode* tmp_student = p_head_student;
	while (tmp_class!=NULL) {
		while (tmp_student != NULL) {
			if (tmp_student->student.student_class == tmp_class->my_class.class_id) {
				appendNewStudentNode(tmp_class->my_class.student_list, tmp_student->student);
			}
			tmp_student = tmp_student->next;
		}
		tmp_student = p_head_student;
		tmp_class = tmp_class->next;
	}
}
//--------------------------------------------------------------------------------------------------
