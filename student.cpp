#include "C:/Users/plmtr/OneDrive/Desktop/Lab/Project/dependencies.h"

struct Student
{
    string id;
    string first_name;
    string last_name;
    bool gender;
    string dob;
    string social_id;
};

Student initStudent(string pid, string pfirst_name, string plast_name, bool pgender, string pdob, string psocial_id)
{
    Student new_student;
    new_student.id.assign(pid);
    new_student.first_name.assign(pfirst_name);
    new_student.last_name.assign(plast_name);
    new_student.gender = pgender;
    new_student.dob.assign(pdob);
    new_student.social_id.assign(psocial_id);

    return new_student;
}

void printStudent(Student A)
{
    cout << A.id << endl;
    cout << A.first_name << endl;
    cout << A.last_name << endl;
    A.gender ? cout << "Male\n" : cout << "Female\n";
    cout << A.dob << endl;
    cout << A.social_id << endl;
}
