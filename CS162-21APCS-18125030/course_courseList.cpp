#include "header.h"

//------------------------------- Course & CourseList ----------------------------------------------
//--------------------------------------------------------------------------------------------------
Course createCourse(string p_course_id, string p_course_name, string p_teacher_name, int p_num_credit, int p_max_students, int p_day1, int p_sess1, int p_day2, int p_sess2)
{
    Course new_course;
    new_course.course_id.assign(p_course_id);
    new_course.course_name.assign(p_course_name);
    new_course.teacher_name.assign(p_teacher_name);
    new_course.num_credit = p_num_credit;
    p_max_students > 0 ? new_course.max_students = p_max_students : true;
    new_course.teaching_session[0].day_of_the_week = p_day1;
    new_course.teaching_session[0].session_no = p_sess1;
    new_course.teaching_session[1].day_of_the_week = p_day2;
    new_course.teaching_session[1].session_no = p_sess2;

    return new_course;
}

string day_convert(Session a)
{
    int k = a.day_of_the_week;
    switch (k)
    {
    case 2:
        return "MON";
    case 3:
        return "TUE";
    case 4:
        return "WED";
    case 5:
        return "THU";
    case 6:
        return "FRI";
    case 7:
        return "SAT";
    default:
        return "SUN";
    }
}
string no_convert(Session a)
{
    int k = a.session_no;
    return "S" + to_string(k);
}

void printCourse(Course p_course)
{
    cout << p_course.course_id << endl;
    cout << p_course.course_name << endl;
    cout << p_course.teacher_name << endl;
    cout << p_course.num_credit << endl;
    cout << p_course.max_students << endl;
    cout << p_course.teaching_session[0].day_of_the_week << endl;
    cout << p_course.teaching_session[0].session_no << endl;
    cout << p_course.teaching_session[1].day_of_the_week << endl;
    cout << p_course.teaching_session[1].session_no << endl;
}

CourseNode *initCourseNode(Course p_new_course)
{
    CourseNode *new_course_node = new CourseNode;
    new_course_node->course = p_new_course;
    new_course_node->next = nullptr;
    return new_course_node;
}
CourseNode *searchCourseNode(CourseNode *p_head, string p_course_id)
{
    if (!p_head)
    {
        return nullptr;
    }
    else
    {
        CourseNode *temp = p_head;
        while (temp && temp->course.course_id != p_course_id)
        {
            temp = temp->next;
        }
        return temp;
    }
}

void appendNewCourseNode(CourseNode **p_head, Course p_new_course)
{
    CourseNode *new_course_node = initCourseNode(p_new_course);
    if (!(*p_head))
    {
        (*p_head) = new_course_node;
        return;
    }

    else
    {
        CourseNode *temp = *p_head;
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = new_course_node;
        return;
    }
}
void appendNewCourseNode(CourseNode **p_head, Course p_new_course, const string &sem, const string &year, StudentNode *students)
{
    CourseNode *new_course_node = initCourseNode(p_new_course);
    new_course_node->year_id = year;
    new_course_node->semester_id = sem;
    new_course_node->student_list = students;
    if (!(*p_head))
    {
        (*p_head) = new_course_node;
        new_course_node->year_id = year;
        new_course_node->semester_id = sem;
    }

    else
    {
        CourseNode *temp = *p_head;
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = new_course_node;
    }
    return;
}

void pushNewCourseNode(CourseNode **p_head, Course p_new_course)
{
    CourseNode *new_course_node = initCourseNode(p_new_course);
    if (!(*p_head))
    {
        *p_head = new_course_node;
        return;
    }

    CourseNode *temp = new_course_node;
    temp->next = *p_head;
    *p_head = temp;
}
void removeCourseNode(CourseNode **p_head, string p_course_id)
{
    CourseNode *founded_course = searchCourseNode(*p_head, p_course_id);
    if (!p_head || !founded_course)
    {
        cout << "Cannot find the searched course...\n";
        return;
    }

    // If the required course is at the top of the list
    if ((*p_head)->course.course_id == p_course_id)
    {
        CourseNode *temp = *p_head;
        *p_head = (*p_head)->next;
        delete temp;
        return;
    }

    CourseNode *temp = *p_head;
    while (temp->next != founded_course)
    {
        temp = temp->next;
    }
    temp->next = founded_course->next;
    delete founded_course;
}
void readFromFileCourseNode(string p_course_file_path, CourseNode **p_head)
{
    ifstream openFile(p_course_file_path);
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

            // Create new course data and append to current list
            Course new_course = createCourse(word[0], word[1], word[2], stoi(word[3]), (word[4].empty() ? false : stoi(word[4])), stoi(word[5]), stoi(word[6]), stoi(word[7]), stoi(word[8]));
            appendNewCourseNode(p_head, new_course);
        }
        openFile.close();
        return;
    }
}
void writeToFileCourseNode(string p_course_file_path, CourseNode *p_head)
{
    ofstream openFile(p_course_file_path);
    if (!openFile)
    {
        cout << "File open failed...";
        return;
    }

    else
    {
        CourseNode *temp = p_head;
        while (temp)
        {
            openFile << temp->course.course_id << ",";
            openFile << temp->course.course_name << ",";
            openFile << temp->course.teacher_name << ",";
            openFile << temp->course.num_credit << ",";
            openFile << temp->course.max_students << ",";
            openFile << temp->course.teaching_session[0].day_of_the_week << ",";
            openFile << temp->course.teaching_session[0].session_no << ",";
            openFile << temp->course.teaching_session[1].day_of_the_week << ",";
            openFile << temp->course.teaching_session[1].session_no;
            openFile << endl;

            temp = temp->next;
        }
    }
    openFile.close();
    return;
}
void updateCourseInfo(CourseNode **p_head, string p_course_id, string p_course_name, string p_teacher_name)
{
    if (!(*p_head))
    {
        cout << "Course NOT EXISTED..." << endl;
        return;
    }

    if (!(p_course_id).empty())
        (*p_head)->course.course_id.assign(p_course_id);
    if (!(p_course_name).empty())
        (*p_head)->course.course_name.assign(p_course_name);
    if (!(p_teacher_name).empty())
        (*p_head)->course.teacher_name.assign(p_teacher_name);
}
void deleteCourseNode(CourseNode *&head)
{
    while (head)
    {
        CourseNode *cur = head;
        deleteStudentList(cur->student_list);
        head = head->next;
        delete cur;
    }
}
void printCourseNode(CourseNode *p_head)
{
    if (!p_head)
    {
        cout << "Empty list....";
        return;
    }

    CourseNode *temp = p_head;
    while (temp)
    {
        printCourse(temp->course);
        cout << endl;
        temp = temp->next;
    }
}

void readFromFileCourseNode(ifstream &openFile, CourseNode **p_head)
{
    if (openFile)
    {
        string line, word[11];
        while (getline(openFile, line) && line[0] != '&')
        {
            stringstream ss(line);
            for (int i = 0; i < 11; i++)
            {
                getline(ss, word[i], ',');
            }

            // Create new course data and append to current list
            Course new_course = createCourse(word[0], word[1], word[2], stoi(word[3]), (word[4].empty() ? false : stoi(word[4])), stoi(word[5]), stoi(word[6]), stoi(word[7]), stoi(word[8]));
            StudentNode *course_student = nullptr;
            readFromFileStudentNode(openFile, &course_student);
            appendNewCourseNode(p_head, new_course, word[9], word[10], course_student);
        }
    }
    return;
}
void writeToFileCourseNode(ofstream &openFile, CourseNode *p_head)
{
    if (openFile)
    {
        CourseNode *temp = p_head;
        while (temp)
        {
            openFile << temp->course.course_id << ",";
            openFile << temp->course.course_name << ",";
            openFile << temp->course.teacher_name << ",";
            openFile << temp->course.num_credit << ",";
            openFile << temp->course.max_students << ",";
            openFile << temp->course.teaching_session[0].day_of_the_week << ",";
            openFile << temp->course.teaching_session[0].session_no << ",";
            openFile << temp->course.teaching_session[1].day_of_the_week << ",";
            openFile << temp->course.teaching_session[1].session_no << ",";
            openFile << temp->semester_id << ",";
            openFile << temp->year_id;
            openFile << endl;
            writeToFileStudentNode(openFile, temp->student_list);
            openFile << "*" << endl;
            temp = temp->next;
        }
        openFile << "&" << endl;
    }
    return;
}
bool checkCourseCollision(Course a, Course b)
{
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (a.teaching_session[i].day_of_the_week == b.teaching_session[i].day_of_the_week && a.teaching_session[j].session_no == b.teaching_session[j].session_no)
            {
                cout << a.teaching_session[i].day_of_the_week << a.teaching_session[i].session_no << endl;
                return true;
            }
        }
    }
    return false;
}
bool checkCourseWithMyCourse(Course a, CourseNode *course_list)
{
    if (!course_list)
        return false;
    if (a.max_students < 1)
        return true;

    CourseNode *temp = course_list;
    while (temp)
    {
        if (checkCourseCollision(a, temp->course))
            return true;
        temp = temp->next;
    }
    return false;
}

//--------------------------------------------------------------------------------------------------