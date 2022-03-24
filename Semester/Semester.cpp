#include "struct_and_dependencies.h"
SemesterNode* Create_Semester_List(SemesterNode*&Semester_head,CourseNode*Course_head) {
	SemesterNode* pSemester = new SemesterNode;
	cout << " Please input the name of the Semester : ";
	getline(cin, pSemester->sem.semester_id);
	pSemester->sem.course_list = Course_head;
	pSemester->next = NULL;
	SemesterNode* p = Semester_head;
	if (p == NULL)
		Semester_head = pSemester;
	else {
		while (p->next != NULL)
			p = p->next;
		p->next = pSemester;
	}
	return Semester_head;
}
