Year createYear(ClassNode* ClassList,SemesterNode *SemList) {
	Year new_year;
	cout << "Please enter the name of Year : ";
	getline(cin, new_year.year_id);
	new_year.list_class = ClassList;
	new_year.list_sem = SemList;
	return new_year;
}
