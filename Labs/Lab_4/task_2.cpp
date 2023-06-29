// Created by Hamdi on 3/28/2023.
//
#include <iostream>
#include <cstring>
using namespace std;
class Student{
private:
    char* name;
    int age;
    char* major;
    void copy(const Student &other){
        this->name = new char [strlen(other.name)+1];strcpy(this->name,other.name);
        this->age=other.age;
        this->major=new char [strlen(other.major)+1];strcpy(this->major,other.major);
    }
public:
    Student(char *name="", int age=0, char *major=""){
        this->name = new char [strlen(name)+1];strcpy(this->name,name);
        this->age=age;
        this->major=new char [strlen(major)+1];strcpy(this->major,major);
    }

    Student(const Student &other){
        copy(other);
    }

    Student operator=(const Student &other)  {
        if(this==&other){
            return *this;
        }
        delete[]name;
        delete[]major;
        copy(other);
        return *this;
    }
    ~Student(){
        delete[]name;
        delete[]major;
    }

    char *getname() const {
        return name;
    }

    int getage() const {
        return age;
    }

    char *getmajor() const {
        return major;
    }
};

//

class Classroom {
private:
    Student *students;
    int numStudents;
    int capacity;

    void copy(const Classroom &other) {
        this->students = new Student[other.numStudents];
        this->numStudents = other.numStudents;
        this->capacity = other.capacity;
        for (int i = 0; i < other.numStudents; i++) {
            this->students[i] = Student(other.students[i]);
        }
    }

public:
    Classroom(Student* students = nullptr, int numStudents = 0, int capacity = 0) {
        this->students = new Student[numStudents];
        this->numStudents = numStudents;
        this->capacity = capacity;
        for (int i = 0; i < numStudents; i++) {
            this->students[i] = Student(students[i]);
        }
    }

    Classroom(const Classroom &other){
        copy(other);
    }
    ~Classroom() {
        delete[] students;
    }

    Student *getStudents() const {
        return students;
    }

    int getnumStudents() const {
        return numStudents;
    }

    void add(Student student) {
        if (numStudents == capacity) {

            if (capacity == 0) {
                capacity = 1;
            } else {
                capacity = capacity * 2;
            }

            Student* tmp = new Student[capacity];
            for (int i = 0; i < numStudents; i++) {
                tmp[i] = students[i];
            }
            delete[] students;
            students = tmp;
        }
        students[numStudents++] = student;
    }
    void remove(char* name) {
        int index = -1;
        for(int i = 0; i < numStudents; i++) {
            if(strcmp(students[i].getname(), name) == 0) {
                index = i;
                break;
            }
        }
        if(index == -1) return;

        for(int i = index ; i < numStudents - 1; i++) {
            students[i] = students[i + 1];
        }
        numStudents--;
    }


    void printStudents(){
        for(int i=0; i<numStudents; i++){
            cout << students[i].getname() << " (" << students[i].getage() << "," << " " << students[i].getmajor() << ")" << endl;
        }
        cout<<endl;
    }



};
//outside class
double findMedianAge(Classroom classroom) {
    Student* students = classroom.getStudents();
    int n = classroom.getnumStudents() / 2;
    double median = students[n].getage();

    if(classroom.getnumStudents() % 2 == 0)
        median = (students[n].getage() + students[n - 1].getage()) / 2.0;

    return median;
}
///DO NOT CHANGE
int main() {
    int numClassrooms, numStudents;
    cin >> numClassrooms;
    Classroom classrooms[100];
    Student students[100];

    // Testing add method
    for (int i = 0; i < numClassrooms; i++) {
        cin >> numStudents;
        for (int j = 0; j < numStudents; j++) {
            char name[100], major[100];
            int age;
            cin >> name >> age >> major;
            Student student(name, age, major);
            classrooms[i].add(student);
            students[i*numStudents + j] = student;
        }
        cout<<"Classroom "<<i<<endl;
        classrooms[i].printStudents();
    }


    // Testing findMedianAge method
    int targetClassroom;
    cin >> targetClassroom;
    double medianAge = findMedianAge(classrooms[targetClassroom]);
    cout << "The median age in classroom " << targetClassroom << " is: " << medianAge << endl;
    cout<<"After removing the elements:"<<endl; // Added
    // Testing remove method
    cin >> numStudents;
    for (int j = 0; j < numStudents; j++) {
        char name[100];
        cin >> name;
        for (int i = 0; i < numClassrooms; i++) {
            classrooms[i].remove(name);
        }
    }
    for (int i = 0; i < numClassrooms; i++) {
        cout<<"Classroom "<<i<<endl;
        classrooms[i].printStudents();
    }

    return 0;
}