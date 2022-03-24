#include "Year.h"
YearNode*createYear(YearNode*&Year_head,ClassNode *Class_head,SemesterNode *Semester_head) {
	YearNode* pYear = new YearNode;
	cout << " Please enter name of the year (XXXX-YYYY) :";
	getline(cin, pYear->school_year.year_id);
	pYear->school_year.list_class = Class_head;
	pYear->school_year.list_sem = Semester_head;
	pYear->next = NULL;
	YearNode* p = Year_head;
	if (p != NULL)
		Year_head = pYear;
	else {
		while (p->next != NULL)
			p = p->next;
		p->next = pYear;
	}
	return Year_head;
}
