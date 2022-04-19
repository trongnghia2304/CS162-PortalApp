#include "header.h"
Year createYear(string p_year_id)
{
	Year new_year;
	new_year.year_id.assign(p_year_id);
	return new_year;
}
YearNode *initYearNode(Year p_new_year)
{
	YearNode *new_year_node = new YearNode;
	new_year_node->school_year = p_new_year;
	new_year_node->next = NULL;
	return new_year_node;
}
void appendNewYearNode(YearNode **p_head, Year p_new_year)
{
	YearNode *new_year = initYearNode(p_new_year);
	YearNode *tmp = *p_head;
	if (tmp == NULL)
		(*p_head) = new_year;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_year;
	}
	return;
}
void pushNewYearNode(YearNode *&p_head, Year p_new_year)
{
	YearNode *new_year_node = initYearNode(p_new_year);
	if (p_head == NULL)
	{
		p_head = new_year_node;
		return;
	}
	new_year_node->next = p_head;
	p_head = new_year_node;
}
YearNode *searchYearNode(YearNode *p_head, string find_year_id)
{
	if (p_head == NULL)
	{
		cout << "Cannot find the searched year ..." << endl;
		return NULL;
	}
	YearNode *tmp = p_head;
	while (tmp != NULL && tmp->school_year.year_id != find_year_id)
	{
		tmp = tmp->next;
	}
	return tmp;
}
void removeYearNode(YearNode *&p_head, string p_Year_id)
{
	YearNode *tmp = p_head;
	YearNode *founded_year = searchYearNode(p_head, p_Year_id);
	if (p_head == NULL || founded_year == NULL)
	{
		cout << "Cannot find the searched year..." << endl;
		return;
	}
	if (p_head->school_year.year_id == p_Year_id)
	{
		p_head = p_head->next;
		delete tmp;
	}
	else
	{
		while (tmp->next != founded_year)
			tmp = tmp->next;
		tmp->next = founded_year->next;
		delete founded_year;
	}
}

void deleteYearNode(YearNode *&p_head)
{
	while (p_head)
	{
		YearNode *cur = p_head;
		p_head = p_head->next;
		deleteSemesterNode(cur->school_year.list_sem);
		delete cur;
	}
}

void readFromFileYearNode(string p_year_file_path, YearNode **p_head)
{
	ifstream openFile(p_year_file_path);
	string year;
	if (openFile)
	{
		while (getline(openFile, year))
		{
			Year new_year = createYear(year);
			readFromFileSemesterNode(openFile, &new_year.list_sem);
			appendNewYearNode(p_head, new_year);
		}
		openFile.close();
	}
	return;
}
void writeToFileYearNode(string p_year_file_path, YearNode *p_head)
{
	ofstream openFile(p_year_file_path);
	if (openFile)
	{
		YearNode *temp = p_head;
		while (temp)
		{
			openFile << temp->school_year.year_id << endl;
			writeToFileSemesterNode(openFile, temp->school_year.list_sem);
			temp = temp->next;
		}
		openFile.close();
	}
	return;
}
