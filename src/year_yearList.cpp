#include "header.h"
Year createYear(string p_year_id)
{
	Year new_year;
	new_year.year_id.assign(p_year_id);
	return new_year;
}
YearNode* initYearNode(Year p_new_year)
{
	YearNode* new_year_node = new YearNode;
	new_year_node->school_year = p_new_year;
	new_year_node->next = NULL;
	return new_year_node;
}
YearNode* appendNewYearNode(YearNode*& p_head, Year p_new_year)
{
	YearNode* new_year = initYearNode(p_new_year);
	YearNode* tmp = p_head;
	if (tmp == NULL)
		p_head = new_year;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_year;
	}
	return p_head;
}
void pushNewYearNode(YearNode*& p_head, Year p_new_year)
{
	YearNode* new_year_node = initYearNode(p_new_year);
	if (p_head == NULL)
	{
		p_head = new_year_node;
		return;
	}
	new_year_node->next = p_head;
	p_head = new_year_node;
}
YearNode* searchYearNode(YearNode* p_head, string find_year_id)
{
	if (p_head == NULL)
	{
		cout << "Cannot find the searched year ..." << endl;
		return NULL;
	}
	YearNode* tmp = p_head;
	while (tmp != NULL && tmp->school_year.year_id != find_year_id)
	{
		tmp = tmp->next;
	}
	return tmp;
}
void removeYearNode(YearNode*& p_head, string p_Year_id)
{
	YearNode* tmp = p_head;
	YearNode* founded_year = searchYearNode(p_head, p_Year_id);
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
