#include "../StudentList/student_list.h"
#pragma once

void checkMyClass(Class a);

ClassNode* Create_List_Class(ClassNode* &Class_head,string class_name,string head_teacher);
void InputClassFromFile(ifstream& ifs, ClassNode* &Class_head);

void Add_Student_to_1_Class(Class &a, StudentNode* Student_head);
void Add_Student_to_all_Class(ClassNode* Class_head, StudentNode* Student_head);
void deleteClass(ClassNode* head);
