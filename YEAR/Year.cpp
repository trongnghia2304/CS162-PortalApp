#include "Year.h"
YearNode*createYear(YearNode*&Year_head) {
	YearNode* pYear = new YearNode;
	cout << " Please enter name of the year (XXXX-YYYY) :";
	getline(cin, pYear->school_year.year_id);
	pYear->school_year.list_class =NULL;
	pYear->school_year.list_sem = NULL;
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
