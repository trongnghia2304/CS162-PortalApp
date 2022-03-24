#include "Year.h"
YearNode* createYear() {
	YearNode* pYear = new YearNode;
	cout << " Please enter name of the year (XXXX-YYYY) :";
	getline(cin, pYear->school_year.year_id);
	pYear->school_year.list_class = NULL;
	pYear->school_year.list_sem = NULL;
	pYear->next = NULL;
	return pYear;
}
