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
StudentNode* initStudentNode(Student p_new_student)
{
	StudentNode* new_student_node = new StudentNode;
	new_student_node->student = p_new_student;
	new_student_node->next = nullptr;
	return new_student_node;
}
StudentNode* searchStudentNode(StudentNode* p_head, string p_student_id)
{
	if (!p_head)
	{
		cout << "Empty student list...";
		return nullptr;
	}
	else
	{
		StudentNode* temp = p_head;
		while (temp && temp->student.student_id != p_student_id)
		{
			temp = temp->next;
		}
		return temp;
	}
}
void appendNewStudentNode(StudentNode** p_head, Student p_new_student)
{
	StudentNode* new_student_node = initStudentNode(p_new_student);
	if (!(*p_head))
	{
		(*p_head) = new_student_node;
		return;
	}

	else
	{
		StudentNode* temp = *p_head;
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = new_student_node;
		return;
	}
}
void pushNewStudentNode(StudentNode** p_head, Student p_new_student)
{
	StudentNode* new_student_node = initStudentNode(p_new_student);
	if (!(*p_head))
	{
		*p_head = new_student_node;
		return;
	}

	new_student_node->next = *p_head;
	*p_head = new_student_node;
}
void removeStudentNode(StudentNode** p_head, string p_student_id)
{
	StudentNode* founded_student = searchStudentNode(*p_head, p_student_id);
	if (!p_head || !founded_student)
	{
		cout << "Empty student list...";
		return;
	}

	// If the required student is at the top of the list
	if ((*p_head)->student.student_id == p_student_id)
	{
		StudentNode* temp = *p_head;
		*p_head = (*p_head)->next;
		delete temp;
		return;
	}

	StudentNode* temp = *p_head;
	while (temp->next != founded_student)
	{
		temp = temp->next;
	}
	temp->next = founded_student->next;
	delete founded_student;
}
void readFromFileStudentNode(string p_student_file_path, StudentNode** p_head)
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
void writeToFileStudentNode(string p_student_file_path, StudentNode* p_head)
{
	ofstream openFile(p_student_file_path);
	if (!openFile)
	{
		cout << "File open failed...";
		return;
	}

	else
	{
		StudentNode* temp = p_head;
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
int countStudentNode(StudentNode* p_head)
{
	if (!p_head)
		return 0;
	int count = 0;
	StudentNode* temp = p_head;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	return count;
}
void deleteStudentList(StudentNode*& p_head)
{
	while (p_head)
	{
		StudentNode* cur = p_head;
		p_head = p_head->next;
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
void printStudentNode(StudentNode* p_head)
{
	if (!p_head)
	{
		cout << "Empty list....";
		return;
	}

	StudentNode* temp = p_head;
	while (temp)
	{
		printStudent(temp->student);
		cout << endl;
		temp = temp->next;
	}
}
void readFromFileStudentNode(ifstream& openFile, StudentNode** p_head)
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
void writeToFileStudentNode(ofstream& openFile, StudentNode* p_head)
{
	if (openFile)
	{
		StudentNode* temp = p_head;
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
void readFromFileStudentNode1(ifstream& openFile, StudentNode** p_head)
{
	if (openFile)
	{
		string line, word[10];
		while (getline(openFile, line) && line[0] != '*')
		{
		    if(line[0] == '>') continue;
			stringstream ss(line);
			for (int i = 0; i < 10; i++)
			{
				getline(ss, word[i], ',');
			}
			// Create new student data and append to current list

			int id, gender;
			istringstream(word[0]) >> id;
			istringstream(word[4]) >> gender;

			Student new_student = createStudent(id, word[1], word[2], word[3], gender, word[5], word[6], word[7], word[8]);
			new_student.subject_amount = stoi(word[9]);

            MyCourse *cur;
			for(int i = 1; i <= new_student.subject_amount; i++)
            {
                MyCourse *temp = new MyCourse;
                if(i == 1)
                {
                    new_student.my_course = temp;
                    cur = temp;
                }
                else
                {
                    cur->next = temp;
                    cur = cur->next;
                }
                getline(openFile, line);
                stringstream ss(line);
                for(int i = 0; i < 5; i++)
                {
                    getline(ss, word[i], ',');
                }
                cur->subject_code = word[0];
                istringstream(word[1]) >> cur->score.process;
                istringstream(word[2]) >> cur->score.mid;
                istringstream(word[3]) >> cur->score.fin;
                istringstream(word[4]) >> cur->score.overall;

            }
			appendNewStudentNode(p_head, new_student);
		}
	}
	return;
}
void writeToFileStudentNode1(ofstream& openFile, StudentNode* p_head)
{
	if (openFile)
	{
		StudentNode* temp = p_head;
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
			openFile << ">";
			openFile << endl;
			temp = temp->next;
		}
		return;
	}
}

//--------------------------------------------------------------------------------------------------
