#include "Course.h"

void checkMyCourse(Student me){
    cout << "Pick a year: ";
    int year;
    cin >> year;
    cout << "Pick a semester: ";
    int sem;
    cin >> sem;
    cout << "id, course, teacher, credit, timetable";
    while (me.my_course->course->year != year && me.my_course->course->semester_id != sem) me.my_course = me.my_course->next;
    for (MyCourse* cur = me.my_course; cur && cur->course->semester_id == sem; cur = cur->next){
        cout << cur->course->course.course_id << "  " << cur->course->course.course_name << "  " << cur->course->course.teacher_name << "  " << cur->course->course.num_credit << "  ";
        for (int i = 0; i < 2; i++){
            switch (cur->course->course.teaching_session[i].day_of_the_week){
                case 1:
                    cout << "Sun";
                    break;
                case 2:
                    cout << "Mon";
                    break;
                case 3:
                    cout << "Tue";
                    break;
                case 4:
                    cout << "Wed";
                    break;
                case 5:
                    cout << "Thu";
                    break;
                case 6:
                    cout << "Fri";
                    break;
                default:
                    cout << "Sat";
                    break;
            }
            cout << "-" << cur->course->course.teaching_session[i].session_no << "  ";
        }
        cout << endl;
    }
}