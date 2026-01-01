#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Student {
public:
    int roll;
    string name;
    float marks;

    void input() {
        cout << "Enter Roll Number: ";
        cin >> roll;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Marks: ";
        cin >> marks;
    }

    void display() const {
        cout << roll << "\t" << name << "\t" << marks << endl;
    }
};

void addStudent() {
    Student s;
    ofstream file("students.txt", ios::app);

    s.input();
    file << s.roll << "|" << s.name << "|" << s.marks << endl;

    file.close();
    cout << "Student added successfully!\n";
}

void viewStudents() {
    ifstream file("students.txt");
    Student s;
    char ch;

    cout << "\nRoll\tName\tMarks\n";
    cout << "---------------------------\n";

    while (file >> s.roll >> ch) {
        getline(file, s.name, '|');
        file >> s.marks;
        file.ignore();

        s.display();
    }
    file.close();
}

void searchStudent() {
    ifstream file("students.txt");
    int roll;
    bool found = false;
    Student s;
    char ch;

    cout << "Enter roll number to search: ";
    cin >> roll;

    while (file >> s.roll >> ch) {
        getline(file, s.name, '|');
        file >> s.marks;
        file.ignore();

        if (s.roll == roll) {
            cout << "Record Found:\n";
            s.display();
            found = true;
            break;
        }
    }
    file.close();

    if (!found)
        cout << "Student not found!\n";
}

void deleteStudent() {
    ifstream file("students.txt");
    ofstream temp("temp.txt");
    int roll;
    Student s;
    char ch;

    cout << "Enter roll number to delete: ";
    cin >> roll;

    while (file >> s.roll >> ch) {
        getline(file, s.name, '|');
        file >> s.marks;
        file.ignore();

        if (s.roll != roll)
            temp << s.roll << "|" << s.name << "|" << s.marks << endl;
    }

    file.close();
    temp.close();
    remove("students.txt");
    rename("temp.txt", "students.txt");

    cout << "Student deleted successfully!\n";
}

int main() {
    int choice;

    do {
        cout << "\n=== Student Management System ===\n";
        cout << "1. Add Student\n";
        cout << "2. View Students\n";
        cout << "3. Search Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: addStudent(); break;
        case 2: viewStudents(); break;
        case 3: searchStudent(); break;
        case 4: deleteStudent(); break;
        case 5: cout << "Exiting...\n"; break;
        default: cout << "Invalid choice!\n";
        }
    } while (choice != 5);

    return 0;
}
