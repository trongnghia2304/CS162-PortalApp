#include "header.h"

//----------------------------- Student & StudentList --------------------------------------------
//--------------------------------------------------------------------------------------------------
Student createStudent(int p_num, string p_student_id, string p_first_name, string p_last_name, bool p_gender, string p_dob, string p_social_id, string p_password, string p_class)
{
	Student new_student;
	new_student.num = p_num;
	new_student.student_id.assign(p_student_id);
	new_student.first_name.assign(p_first_name);
	new_student.last_name.assign(p_last_name);
	new_student.gender = p_gender;
	new_student.dob.assign(p_dob);
	new_student.social_id.assign(p_social_id);
	new_student.password.assign(p_password);
	new_student.student_class.assign(p_class);

	return new_student;
}
StudentNode *initStudentNode(Student p_new_student)
{
	StudentNode *new_student_node = new StudentNode;
	new_student_node->student = p_new_student;
	new_student_node->next = nullptr;
	return new_student_node;
}
StudentNode *searchStudentNode(StudentNode *p_head, string p_student_id)
{
	if (!p_head)
	{
		cout << "Empty student list...";
		return nullptr;
	}
	else
	{
		StudentNode *temp = p_head;
		while (temp && temp->student.student_id != p_student_id)
		{
			temp = temp->next;
		}
		return temp;
	}
}
void appendNewStudentNode(StudentNode **p_head, Student p_new_student)
{
	StudentNode *new_student_node = initStudentNode(p_new_student);
	if (!(*p_head))
	{
		(*p_head) = new_student_node;
		return;
	}

	else
	{
		StudentNode *temp = *p_head;
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = new_student_node;
		return;
	}
}
void pushNewStudentNode(StudentNode **p_head, Student p_new_student)
{
	StudentNode *new_student_node = initStudentNode(p_new_student);
	if (!(*p_head))
	{
		*p_head = new_student_node;
		return;
	}

	new_student_node->next = *p_head;
	*p_head = new_student_node;
}
void removeStudentNode(StudentNode **p_head, string p_student_id)
{
	StudentNode *founded_student = searchStudentNode(*p_head, p_student_id);
	if (!(*p_head) || !founded_student)
	{
		cout << "Empty student list...";
		return;
	}

	// If the required student is at the top of the list
	if ((*p_head)->student.student_id == p_student_id)
	{
		StudentNode *temp = *p_head;
		*p_head = (*p_head)->next;
		delete temp;
		return;
	}

	StudentNode *temp = *p_head;
	while (temp->next != founded_student)
	{
		temp = temp->next;
	}
	temp->next = founded_student->next;
	deleteMyCourse(founded_student->student.my_course);
	delete founded_student;
}
void readFromFileStudentNode(string p_student_file_path, StudentNode **p_head)
{
	ifstream openFile(p_student_file_path);
	if (!openFile)
	{
		cout << "Read from file failed...";
		return;
	}

	else
	{
		string line, word[9];
		while (getline(openFile, line))
		{
			stringstream ss(line);
			for (int i = 0; i < 9; i++)
			{
				getline(ss, word[i], ',');
			}
			int id, gender;
			istringstream(word[0]) >> id;
			istringstream(word[4]) >> gender;
			// Create new student data and append to current list
			// Student new_student = createStudent(stoi(word[0]), word[1], word[2], word[3], (stoi(word[4]) ? false : true), word[5], word[6], word[7], word[8]);
			Student new_student = createStudent(id, word[1], word[2], word[3], gender, word[5], word[6], word[7], word[8]);
			appendNewStudentNode(p_head, new_student);
		}
		openFile.close();
		return;
	}
}
void writeToFileStudentNode(string p_student_file_path, StudentNode *p_head)
{
	ofstream openFile(p_student_file_path);
	if (!openFile)
	{
		cout << "File open failed...";
		return;
	}

	else
	{
		StudentNode *temp = p_head;
		while (temp)
		{
			openFile << temp->student.num << ",";
			openFile << temp->student.student_id << ",";
			openFile << temp->student.first_name << ",";
			openFile << temp->student.last_name << ",";
			openFile << temp->student.gender << ",";
			openFile << temp->student.dob << ",";
			openFile << temp->student.social_id << ",";
			openFile << temp->student.password << ",";
			openFile << temp->student.student_class;
			openFile << endl;
			temp = temp->next;
		}
	}
	openFile.close();
	return;
}
int countStudentNode(StudentNode *p_head)
{
	if (!p_head)
		return 0;
	int count = 0;
	StudentNode *temp = p_head;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	return count;
}
void deleteStudentList(StudentNode *&p_head)
{
	while (p_head)
	{
		StudentNode *cur = p_head;
		p_head = p_head->next;
		delete (cur->student.my_course);
		delete cur;
	}
}
void printStudent(Student p_student)
{
	cout << p_student.num << endl;
	cout << p_student.student_id << endl;
	cout << p_student.first_name << endl;
	cout << p_student.last_name << endl;
	p_student.gender ? cout << "Female\n" : cout << "Male\n";
	cout << p_student.dob << endl;
	cout << p_student.social_id << endl;
}
void printStudentNode(StudentNode *p_head)
{
	if (!p_head)
	{
		cout << "Empty list....";
		return;
	}

	StudentNode *temp = p_head;
	while (temp)
	{
		printStudent(temp->student);
		cout << endl;
		temp = temp->next;
	}
}
void readFromFileStudentNode(ifstream &openFile, StudentNode **p_head)
{
	if (openFile)
	{
		string line, word[9];
		while (getline(openFile, line) && line[0] != '*')
		{
			stringstream ss(line);
			for (int i = 0; i < 9; i++)
			{
				getline(ss, word[i], ',');
			}

			// Create new student data and append to current list
			// Student new_student = createStudent(stoi(word[0]), word[1], word[2], word[3], (stoi(word[4]) ? false : true), word[5], word[6], word[7], word[8]);
			int id, gender;
			istringstream(word[0]) >> id;
			istringstream(word[4]) >> gender;
			// Student new_student = createStudent(id, word[1], word[2], word[3], (gender ? false : true), word[5], word[6], word[7], word[8]);
			Student new_student = createStudent(id, word[1], word[2], word[3], gender, word[5], word[6], word[7], word[8]);
			appendNewStudentNode(p_head, new_student);
		}
	}
	return;
}
void writeToFileStudentNode(ofstream &openFile, StudentNode *p_head)
{
	if (openFile)
	{
		StudentNode *temp = p_head;
		while (temp)
		{
			openFile << temp->student.num << ",";
			openFile << temp->student.student_id << ",";
			openFile << temp->student.first_name << ",";
			openFile << temp->student.last_name << ",";
			openFile << temp->student.gender << ",";
			openFile << temp->student.dob << ",";
			openFile << temp->student.social_id << ",";
			openFile << temp->student.password << ",";
			openFile << temp->student.student_class;
			openFile << endl;
			temp = temp->next;
		}
		return;
	}
}
void readFromFileStudentNode1(ifstream &openFile, StudentNode **p_head)
{
	if (openFile)
	{
		string line, word[9];
		while (getline(openFile, line) && line[0] != '*')
		{
			stringstream ss(line);
			for (int i = 0; i < 9; i++)
			{
				getline(ss, word[i], ',');
			}
			// Create new student data and append to current list

			int id, gender;
			istringstream(word[0]) >> id;
			istringstream(word[4]) >> gender;

			Student new_student = createStudent(id, word[1], word[2], word[3], gender, word[5], word[6], word[7], word[8]);
			MyCourse *cur = nullptr;
			while (getline(openFile, line) && line[0] != '>')
			{
				MyCourse *temp = new MyCourse;
				if (!cur)
				{
					new_student.my_course = temp;
					cur = temp;
				}
				else
				{
					cur->next = temp;
					cur = cur->next;
				}
				cur->next = nullptr;
				stringstream ss(line);
				for (int i = 0; i < 7; i++)
				{
					getline(ss, word[i], ',');
				}
				cur->subject_code = word[0];
				cur->year = word[1];
				cur->sem = word[2];
				istringstream(word[3]) >> cur->score.process;
				istringstream(word[4]) >> cur->score.mid;
				istringstream(word[5]) >> cur->score.fin;
				istringstream(word[6]) >> cur->score.overall;
			}
			appendNewStudentNode(p_head, new_student);
		}
	}
	return;
}
void writeToFileStudentNode1(ofstream &openFile, StudentNode *p_head)
{
	if (openFile)
	{
		StudentNode *temp = p_head;
		while (temp)
		{
			openFile << temp->student.num << ",";
			openFile << temp->student.student_id << ",";
			openFile << temp->student.first_name << ",";
			openFile << temp->student.last_name << ",";
			openFile << temp->student.gender << ",";
			openFile << temp->student.dob << ",";
			openFile << temp->student.social_id << ",";
			openFile << temp->student.password << ",";
			openFile << temp->student.student_class << "\n";
			MyCourse *cur = temp->student.my_course;
			while (cur)
			{
				openFile << cur->subject_code << ",";
				openFile << cur->year << ",";
				openFile << cur->sem << ",";
				openFile << cur->score.process << ",";
				openFile << cur->score.mid << ",";
				openFile << cur->score.fin << ",";
				openFile << cur->score.overall << endl;
				cur = cur->next;
			}
			openFile << ">" << endl;
			temp = temp->next;
		}
		return;
	}
}

void findMyCourses(StudentNode **p_student, YearNode *year)
{
	MyCourse *cur = (*p_student)->student.my_course;
	while (cur)
	{
		YearNode *cur_year = searchYearNode(year, cur->year);
		SemesterNode *cur_sem = searchSemesterNode(cur_year->school_year.list_sem, cur->sem);
		cur->course = searchCourseNode(cur_sem->sem.course_list, cur->subject_code);
		cur = cur->next;
	}
}

MyCourse *searchMyCourse(StudentNode *p_student, CourseNode *course)
{
	MyCourse *cur = p_student->student.my_course;
	while (cur && cur->course != course)
		cur = cur->next;
	return cur;
}

void setupMyCourses(ClassNode *p_class, YearNode *year)
{
	while (p_class)
	{
		StudentNode *cur = p_class->my_class.student_list;
		while (cur)
		{
			findMyCourses(&cur, year);
			cur = cur->next;
		}
		p_class = p_class->next;
	}
}

void removeMyCourses(StudentNode *p_head, CourseNode *course)
{
	MyCourse *founded_course = searchMyCourse(p_head, course);
	if (!p_head || !founded_course)
	{
		return;
	}
	if (founded_course == p_head->student.my_course)
	{
		MyCourse *temp = founded_course;
		p_head->student.my_course = p_head->student.my_course->next;
		delete temp;
		return;
	}
	MyCourse *temp = p_head->student.my_course;
	while (temp->next != founded_course)
		temp = temp->next;
	temp->next = temp->next->next;
	delete founded_course;
	return;
}

void deleteMyCourse(MyCourse *&p_head)
{
	MyCourse *cur;
	while (p_head)
	{
		cur = p_head;
		p_head = p_head->next;
		delete cur;
	}
}

void appendNewMyCourse(StudentNode *me, MyCourse *new_course)
{
	if (!me->student.my_course)
	{
		me->student.my_course = new_course;
		return;
	}
	MyCourse *cur = me->student.my_course;
	while (cur->next)
		cur = cur->next;
	cur->next = new_course;
	return;
}

MyCourse *createMyCourse(CourseNode *course)
{
	MyCourse *me = new MyCourse;
	me->next = nullptr;
	me->course = course;
	me->sem = course->semester_id;
	me->year = course->year_id;
	me->subject_code = course->course.course_id;
	return me;
}


//--------------------------------------------------------------------------------------------------
