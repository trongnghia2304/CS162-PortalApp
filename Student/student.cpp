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

void changePassword(Student& me)
{
    string s1;

    cout << "Type your old Password:\n";
    getline(cin, s1, '\n');
    if(s1 == me.password)
    {
        cout << "Type your new password:\n";
        getline(cin, me.password, '\n');
        cout << "Change password successfully!";
    }
    else cout << "Wrong old password!!";
    // When we upload to UI, we should implement "Return" button to cancel the changing.
}
void changeDisplayname(Student& me)
{
    cout << "Your current name:\n" << me.display_name;
    cout << "Type name you want to change into:\n";
    getline(cin, me.display_name, '\n');
    cout << "Change display name successfully!";
}

void changeStudent(Student &me){
    cout << "Which information would you like to change:\n";
    cout << "   1. First name\n";
    cout << "   2. Last name\n";
    cout << "   3. Gender\n";
    cout << "   4. Date of birth\n";
    cout << "   5. Class\n";
    cout << "   6. ID\n";
    cout << "   7. Global ID\n";
    cout << "   8. Password\n";
    cout << "   9. Return\n";
    int k;
    bool check = true;
    cin >> k;
    do {
    switch (k){
        case 1:
        {
            cout << "Your first name is: " << me.first_name;
            cout << "\nYou want to change into: ";
            cin >> me.first_name;
            cout << "Change successfully! New data: " << me.first_name;
            break;
        }

        case 2:
        {
            cout << "Your last name is: " << me.last_name;
            cout << "\nYou want to change into: ";
            cin >> me.last_name;
            cout << "Change successfully! New data: " << me.last_name;
            break;
        }

        case 3:
        {
            cout << "Your gender is: ";
            me.gender ? cout << "Female" : cout << "Male";
            cout << "\nYou want to change into (f for female, m for male): ";
            char c;
            cin >> c;
            while (c != 'f' && c != 'm'){
                cout << "Invalid! Try again (f for female, m for male): ";
                cin >> c;
            }
            me.gender = (c == 'f' ? true : false);
            cout << "Change successfully! New data is: ";
            me.gender ? cout << "Female" : cout << "Male";
            break;
        }

        case 4:
        {
            string s = "", a;
            cout << "Your date of birth is: " << me.dob;
            cout << "\nYou want to change into: ";
            cout << "\nInput day: ";
            cin >> a;
            s += a + "/";
            cout << "Input month: ";
            cin >> a;
            s += a + "/";
            cout << "Input year: ";
            cin >> a;
            s += a;
            cout << "Change successfully! New data is: " << me.dob;
            break;
        }

        case 5:
        {
            cout << "Your class is: " << me.student_class;
            cout << "\nYou want to change into: ";
            cin >> me.student_class;
            cout << "Change successfully! New data is: " << me.student_class;
            break;
        }

        case 6:
        {
            cout << "Your ID is: " << me.student_id;
            cout << "\nYou want to change into: ";
            cin >> me.student_id;
            cout << "Change successfully! New data is: " << me.student_id;
            break;
        }

        case 7:
        {
            cout << "Your social ID is: " << me.social_id;
            cout << "\nYou want to change into: ";
            cin >> me.social_id;
            cout << "Change successfully! New data is: " << me.social_id;
            break;
        }

        case 8:
            changePassword(me);
        default:
            break;
    }
    if (k < 9 && k > 0){
        cout << "\nDo another change?\n";
        cout << "   0. Yes\n";
        cout << "   1. No\n";
        cin >> check;
    }
    } while(!check);
}