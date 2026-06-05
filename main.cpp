#include <iostream>
#include <fstream>
#include <vector>
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

    void display() {
        cout << "\nRoll No: " << rollNo;
        cout << "\nName: " << name;
        cout << "\nMarks: " << marks << endl;
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

    string line;

    cout << "\n===== STUDENT RECORDS =====\n";

    while (getline(file, line)) {
        cout << line << endl;
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
    char delimiter;

    bool found = false;

    while (file >> r) {
        file >> delimiter;
        getline(file, name, '|');
        file >> marks;

        if (r == roll) {
            cout << "\nStudent Found\n";
            cout << "Roll No: " << r << endl;
            cout << "Name: " << name << endl;
            cout << "Marks: " << marks << endl;
            found = true;
        }

        file.ignore();
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

int main() {
    int choice;

    do {
        cout << "\n\n===== STUDENT MANAGEMENT SYSTEM =====";
        cout << "\n1. Add Student";
        cout << "\n2. View Students";
        cout << "\n3. Search Student";
        cout << "\n4. Delete Student";
        cout << "\n5. Exit";
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
            cout << "\nThank You!\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 5);

    return 0;
}