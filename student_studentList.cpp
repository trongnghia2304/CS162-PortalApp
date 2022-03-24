#include "header.h"

//----------------------------- Student & StudentList --------------------------------------------
//--------------------------------------------------------------------------------------------------
Student createStudent(int p_num, string p_student_id, string p_first_name, string p_last_name, bool p_gender, string p_dob, string p_social_id)
{
    Student new_student;
    new_student.num = p_num;
    new_student.student_id.assign(p_student_id);
    new_student.first_name.assign(p_first_name);
    new_student.last_name.assign(p_last_name);
    new_student.gender = p_gender;
    new_student.dob.assign(p_dob);
    new_student.social_id.assign(p_social_id);

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
    if (!p_head || !founded_student)
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

            // Create new student data and append to current list
            Student new_student = createStudent(stoi(word[0]), word[1], word[2], word[3], (stoi(word[4]) ? true : false), word[5], word[6]);
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
//--------------------------------------------------------------------------------------------------