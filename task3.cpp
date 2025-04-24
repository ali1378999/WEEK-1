#include <iostream>
#include <string>
#include <limits>
using namespace std;

class person
{
private:
    string name;
    int age;

public:
    person(string name = "", int age = 0)
    {
        this->name = name;
        this->age = age;
    }

    void display() const
    {
        cout << "Name: " << name << endl
             << "Age: " << age << endl;
    }

    friend ostream &operator<<(ostream &out, const person &p);
};

ostream &operator<<(ostream &out, const person &p)
{
    out << "Name: " << p.name <<endl<< "Age: " << p.age << endl;
    return out;
}

class student : public person
{
private:
    int id;
    float gpa;
    string email;
    string phone;

public:
    student(string name = "", int age = 0, int id = 0, float gpa = 0, string email = "", string phone = "")
        : person(name, age)
    {
        this->id = id;
        this->gpa = gpa;
        this->email = email;
        this->phone = phone;
    }

    void display() const
    {
        person::display();
        cout << "ID: " << id << endl
             << "GPA: " << gpa << endl
             << "Email: " << email << endl
             << "Phone: " << phone << endl;
    }

    int getID() const { return id; }
    float getGPA() const { return gpa; }

    friend ostream &operator<<(ostream &out, const student &s);
};

ostream &operator<<(ostream &out, const student &s)
{
    out << static_cast<const person &>(s);
    out << "ID: " << s.id <<endl<< "GPA: " << s.gpa
        <<endl<<"Email: " << s.email <<endl<<"Phone: " << s.phone << endl;
    return out;
}

class System
{
private:
    student *students;
    int studentCounter;
    int capacity;

    void expandCapacity()
    {
        capacity *= 2;
        student *newArr = new student[capacity];
        for (int i = 0; i < studentCounter; i++)
        {
            newArr[i] = students[i];
        }
        delete[] students;
        students = newArr;
    }

public:
    System(int initialCapacity = 2) : studentCounter(0), capacity(initialCapacity)
    {
        students = new student[capacity];
    }

    ~System()
    {
        delete[] students;
    }

    void CreateStudent()
    {
        string name, email, phone;
        int age, id;
        float gpa;

        cout << "Enter Name: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, name);

        cout << "Enter Age: ";
        cin >> age;
        cout << "Enter ID: ";
        cin >> id;
        cout << "Enter GPA: ";
        cin >> gpa;

        cout << "Enter Email: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, email);

        cout << "Enter Phone: ";
        getline(cin, phone);

        if (studentCounter == capacity)
            expandCapacity();

        students[studentCounter++] = student(name, age, id, gpa, email, phone);
        cout << "Student added successfully"<<endl;
    }

    void DisplayAll() const
    {
        if (studentCounter == 0)
        {
            cout << "No students found."<<endl;
            return;
        }

        for (int i = 0; i < studentCounter; i++)
        {
            cout << i + 1 <<endl
                 << students[i] << endl;
        }
    }

    int findStudentByID(int id) const
    {
        for (int i = 0; i < studentCounter; i++)
        {
            if (students[i].getID() == id)
                return i;
        }
        return -1;
    }

    int CompareStudents(int st1_ID, int st2_ID) const
    {
        int i = findStudentByID(st1_ID);
        int j = findStudentByID(st2_ID);

        if (i == -1 || j == -1)
        {
            cout << "ID not found.";
            return -2;
        }

        if (students[i].getGPA() > students[j].getGPA())
            return 1;
        else if (students[i].getGPA() == students[j].getGPA())
            return 0;
        else
            return -1;
    }
};

int main()
{
    System sys;

    int choice;
    do
    {
        cout << "\n--- Menu ---"<<endl;
        cout << "1. Create Student"<<endl;
        cout << "2. Display All Students"<<endl;
        cout << "3. Compare Two Students"<<endl;
        cout << "4. Exit"<<endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            sys.CreateStudent();
            break;
        case 2:
            sys.DisplayAll();
            break;
        case 3:
        {
            int id1, id2;
            cout << "Enter ID of Student 1: ";
            cin >> id1;
            cout << "Enter ID of Student 2: ";
            cin >> id2;

            int result = sys.CompareStudents(id1, id2);
            if (result == 1)
                cout << "Student 1 has higher GPA."<<endl;
            else if (result == 0)
                cout << "Both students have equal GPA."<<endl;
            else if (result == -1)
                cout << "Student 2 has higher GPA."<<endl;
            break;
        }
        case 0:
            cout << "Exiting"<<endl;
            break;
        default:
            cout << "Invalid choice. Try again."<<endl;
        }
    } while (choice != 0);

    return 0;
}
