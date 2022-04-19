#include "struct_and_dependencies.h"

string getCurrentDate()
{
    string current_date = "";
    time_t ttime = time(0);
    tm *local_time = localtime(&ttime);

    string year = to_string(1900 + local_time->tm_year);
    string month = to_string(1 + local_time->tm_mon);
    string day = to_string(local_time->tm_mday);

    current_date += (day + "/" + month + "/" + year);
    return current_date;
}

string *splitDate(string str, char seperator)
{
    int currIndex = 0, i = 0;
    int startIndex = 0, endIndex = 0;
    string *strings = new string[3];
    while (i <= str.length())
    {
        if (str[i] == seperator || i == str.length())
        {
            endIndex = i;
            string subStr = "";
            subStr.append(str, startIndex, endIndex - startIndex);
            strings[currIndex] = subStr;
            currIndex += 1;
            startIndex = endIndex + 1;
        }
        i++;
    }
    return strings;
}

int compareDate(string date_1, string date_2)
{
    if (!date_1.compare(date_2))
        return 0;
    else
    {
        string *day_month_year1 = splitDate(date_1, '/');
        string *day_month_year2 = splitDate(date_2, '/');

        int day1 = stoi(day_month_year1[0]);
        int month1 = stoi(day_month_year1[1]);
        int year1 = stoi(day_month_year1[2]);

        int day2 = stoi(day_month_year2[0]);
        int month2 = stoi(day_month_year2[1]);
        int year2 = stoi(day_month_year2[2]);

        if (year1 > year2)
            return 1;
        else if (year1 < year2)
            return -1;
        else
        {
            if (month1 > month2)
                return 1;
            else if (month1 < month2)
                return -1;
            else
            {
                if (day1 > day2)
                    return 1;
                else
                    return -1;
            }
        }
    }
}

void readFromFileRegSess(string filepath, RegistrationSession &new_session)
{
    ifstream openFile(filepath);
    if (openFile)
    {
        string line, word[9];
        getline(openFile, line);
        new_session.start_date.assign(line);
        getline(openFile, line);
        new_session.end_date.assign(line);
        while (getline(openFile, line))
        {
            stringstream ss(line);
            for (int i = 0; i < 9; i++)
            {
                getline(ss, word[i], ',');
            }

            // Create new course data and append to current list
            Course new_course = createCourse(word[0], word[1], word[2], stoi(word[3]), (word[4].empty() ? false : stoi(word[4])), stoi(word[5]), stoi(word[6]), stoi(word[7]), stoi(word[8]));
            appendNewCourseNode(&(new_session.list_of_courses), new_course);
        }
        openFile.close();
    }
}

void writeToFileRegSess(string filepath, RegistrationSession new_session)
{
    ofstream openFile(filepath);
    if (openFile)
    {
        openFile << new_session.start_date;
        openFile << endl;
        openFile << new_session.end_date;
        openFile << endl;
        CourseNode *temp = new_session.list_of_courses;
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
        openFile.close();
    }
    return;
}