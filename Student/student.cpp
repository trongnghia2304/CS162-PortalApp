#include "student.h"

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

void changePassword(Student me)
{
    string s1;

    cout << "Type your old Password:\n";
    getline(cin,s1,'\n');
    if(s1 == me.password)
    {
        cout << "Type your new password:\n";
        getline(cin,me.password,'\n');
        cout << "Change password successfully!";
    }
    else cout << "Wrong old password!!";
}
