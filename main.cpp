#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Student {
public:
    int rollNo;
    string name;
    float marks;

    void input() {
        cout << "\nEnter Roll Number: ";
        cin >> rollNo;

        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Marks: ";
        cin >> marks;
    }
};

void addStudent() {
    Student s;
    ofstream file("students.txt", ios::app);

    s.input();

    file << s.rollNo << "|"
         << s.name << "|"
         << s.marks << endl;

    file.close();

    cout << "\nStudent Added Successfully!\n";
}

void viewStudents() {
    ifstream file("students.txt");

    int roll;
    string name;
    float marks;

    cout << "\n-------------------------------------------------\n";
    cout << "Roll\tName\t\tMarks\tGrade\n";
    cout << "-------------------------------------------------\n";

    while (file >> roll) {
        file.ignore();
        getline(file, name, '|');
        file >> marks;
        file.ignore();

        char grade;

        if (marks >= 90)
            grade = 'A';
        else if (marks >= 75)
            grade = 'B';
        else if (marks >= 60)
            grade = 'C';
        else
            grade = 'D';

        cout << roll << "\t"
             << name << "\t\t"
             << marks << "\t"
             << grade << endl;
    }

    file.close();
}

void searchStudent() {
    ifstream file("students.txt");

    int roll;
    cout << "\nEnter Roll Number to Search: ";
    cin >> roll;

    int r;
    string name;
    float marks;
    bool found = false;

    while (file >> r) {
        file.ignore();
        getline(file, name, '|');
        file >> marks;
        file.ignore();

        if (r == roll) {
            char grade;

            if (marks >= 90)
                grade = 'A';
            else if (marks >= 75)
                grade = 'B';
            else if (marks >= 60)
                grade = 'C';
            else
                grade = 'D';

            cout << "\nStudent Found\n";
            cout << "-------------------------\n";
            cout << "Roll No : " << r << endl;
            cout << "Name    : " << name << endl;
            cout << "Marks   : " << marks << endl;
            cout << "Grade   : " << grade << endl;

            found = true;
        }
    }

    if (!found)
        cout << "\nStudent Not Found!\n";

    file.close();
}

void deleteStudent() {
    ifstream file("students.txt");
    ofstream temp("temp.txt");

    int roll;
    cout << "\nEnter Roll Number to Delete: ";
    cin >> roll;

    string line;
    bool found = false;

    while (getline(file, line)) {
        int storedRoll = stoi(line.substr(0, line.find('|')));

        if (storedRoll != roll)
            temp << line << endl;
        else
            found = true;
    }

    file.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout << "\nStudent Deleted Successfully!\n";
    else
        cout << "\nStudent Not Found!\n";
}

void updateStudent() {
    ifstream file("students.txt");
    ofstream temp("temp.txt");

    int roll;
    cout << "\nEnter Roll Number to Update: ";
    cin >> roll;

    int r;
    string name;
    float marks;
    bool found = false;

    while (file >> r) {
        file.ignore();
        getline(file, name, '|');
        file >> marks;
        file.ignore();

        if (r == roll) {
            cout << "\nEnter New Name: ";
            cin.ignore();
            getline(cin, name);

            cout << "Enter New Marks: ";
            cin >> marks;

            found = true;
        }

        temp << r << "|" << name << "|" << marks << endl;
    }

    file.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout << "\nStudent Updated Successfully!\n";
    else
        cout << "\nStudent Not Found!\n";
}

void totalStudents() {
    ifstream file("students.txt");

    int count = 0;
    string line;

    while (getline(file, line))
        count++;

    cout << "\nTotal Students: " << count << endl;

    file.close();
}

int main() {
    int choice;

    do {
        cout << "\n\n===== STUDENT MANAGEMENT SYSTEM =====";
        cout << "\n1. Add Student";
        cout << "\n2. View Students";
        cout << "\n3. Search Student";
        cout << "\n4. Delete Student";
        cout << "\n5. Update Student";
        cout << "\n6. Total Students";
        cout << "\n7. Exit";
        cout << "\nEnter Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addStudent();
            break;

        case 2:
            viewStudents();
            break;

        case 3:
            searchStudent();
            break;

        case 4:
            deleteStudent();
            break;

        case 5:
            updateStudent();
            break;

        case 6:
            totalStudents();
            break;

        case 7:
            cout << "\nThank You!\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 7);

    return 0;
}