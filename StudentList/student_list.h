#pragma once
#include "../Student/student.h"

// CRUD - Create/Read/Update/Delete student from List
StudentNode *initStudentNode(Student p_new_student);
StudentNode *searchStudentNode(StudentNode *p_head, string p_student_id);
void appendNewStudentNode(StudentNode **p_head, Student p_new_student);
void pushNewStudentNode(StudentNode **p_head, Student p_new_student);
void removeStudentNode(StudentNode **p_head, string p_student_id);
void readFromFileStudentNode(string p_student_file_path, StudentNode **p_head);
void writeToFileStudentNode(string p_student_file_path, StudentNode *p_head);
int countStudentNode(StudentNode *p_head);

// Used for checking outputs <----- can omit
void printStudentNode(StudentNode *p_head);