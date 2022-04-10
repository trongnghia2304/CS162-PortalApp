#include "header.h"

//----------------------------- Semester & SemesterList --------------------------------------------
//--------------------------------------------------------------------------------------------------
Semester createSemester(string p_semester_id)
{
	Semester new_sem;
	new_sem.semester_id = p_semester_id;
	return new_sem;
}
SemesterNode *initSemesterNode(Semester p_new_semester)
{
	SemesterNode *new_sem_node = new SemesterNode;
	new_sem_node->sem = p_new_semester;
	new_sem_node->next = nullptr;
	return new_sem_node;
}
SemesterNode *searchSemesterNode(SemesterNode *p_head, string p_semester_id)
{
	if (!p_head || stoi(p_semester_id) > 3)
	{
		cout << "Cannot find the searched semester...\n";
		return nullptr;
	}
	SemesterNode *temp = p_head;
	while (temp && temp->sem.semester_id != p_semester_id)
	{
		temp = temp->next;
	}
	return temp;
}
void pushNewSemesterNode(SemesterNode **p_head, Semester p_new_semester)
{
	SemesterNode *new_sem_node = initSemesterNode(p_new_semester);
	if (!(*p_head))
	{
		*p_head = new_sem_node;
		return;
	}
	new_sem_node->next = *p_head;
	*p_head = new_sem_node;
}
void appendNewSemesterNode(SemesterNode **p_head, Semester p_new_semester)
{
	SemesterNode *new_sem_node = initSemesterNode(p_new_semester);
	if (!(*p_head))
	{
		(*p_head) = new_sem_node;
		return;
	}
	SemesterNode *temp = *p_head;
	while (temp->next)
	{
		temp = temp->next;
	}
	temp->next = new_sem_node;
}
void removeSemesterNode(SemesterNode **p_head, string p_semester_id)
{
	SemesterNode *founded_semester = searchSemesterNode(*p_head, p_semester_id);
	if (!*p_head || !founded_semester)
	{
		cout << "Cannot find the searched semester...\n";
		return;
	}

	if ((*p_head)->sem.semester_id == p_semester_id)
	{
		SemesterNode *temp = *p_head;
		*p_head = (*p_head)->next;
		delete temp;
		return;
	}

	SemesterNode *temp = *p_head;
	while (temp->next != founded_semester)
	{
		temp = temp->next;
	}
	temp->next = founded_semester->next;
	delete founded_semester;
}

void deleteSemesterNode(SemesterNode *&p_head)
{
	while (p_head)
	{
		SemesterNode *cur = p_head;
		p_head = p_head->next;
		deleteCourseNode(cur->sem.course_list);
		delete cur;
	}
}
void readFromFileSemesterNode(ifstream &openFile, SemesterNode **p_head)
{
	if (openFile)
	{
		string line;
		for (int i = 0; i < 3; i++)
		{
			getline(openFile, line);
			Semester new_sem = createSemester("Semester " + to_string(i + 1));
			readFromFileCourseNode(openFile, &new_sem.course_list);
			appendNewSemesterNode(p_head, new_sem);
		}
	}
	return;
}
void writeToFileSemesterNode(ofstream &openFile, SemesterNode *p_head)
{
	if (openFile)
	{
		SemesterNode *temp = p_head;
		for (int i = 0; i < 3 && temp; i++)
		{
			openFile << temp->sem.semester_id << endl;
			writeToFileCourseNode(openFile, temp->sem.course_list);
			temp = temp->next;
		}
	}
	return;
}
//--------------------------------------------------------------------------------------------------