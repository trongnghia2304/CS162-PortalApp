#include "../StudentList/student_list.h"
#pragma once

void checkMyClass(Class a);

Class createClass(string C_id, string H_Tea);

void AddStudenttoClass(Class &a, StudentNode* stu);

void deleteClass(ClassNode* head);