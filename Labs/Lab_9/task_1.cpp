//
// Created by Hamdi on 5/15/2023.
//
#include <iostream>
#include <cstring>
using namespace std;
class Employee{
protected:
    Employee() {}
    char name[50];
    int age;
public:
    Employee(char *name,int age) : age(age) {
        strcpy(this->name,name);
    }
    virtual void displayInfo()=0;
};
//
class Payable{
protected:
    double salary;
public:
    Payable() {}
    Payable(double salary) : salary(salary) {}

    virtual double calculateSalary()=0;
};
//
//
//
class Developer: public Employee, public Payable{
private:
    char progLanguage[30];
public:
  Developer() {}

    Developer(char *name, int age, double salary, char *progLanguage) : Employee(name,age), Payable(salary) {
        strcpy(this->progLanguage,progLanguage);
    }

    void displayInfo() override {
        cout << "-- Developer Information --" << endl;
      cout<<"Name: "<<name<<endl;
      cout<<"Age: "<<age<< endl;
      cout<<"Salary: $"<<calculateSalary()<<endl;
      cout<<"Programming Language: "<<progLanguage<<endl;

    }

    double calculateSalary() override {
        return salary-(salary*0.1);
    }
};

//

class Manager: public Employee, public Payable{
private:
    int numOfDep;
public:
    Manager() {}
    Manager(char *name, int age, double salary, int numOfDep) : Employee(name, age), Payable(salary),numOfDep(numOfDep) {}

    void displayInfo() override {
        cout << "-- Manager Information --" << endl;
        cout<<"Name: "<<name<<endl;
        cout<<"Age: "<<age<< endl;
        cout<<"Salary: $"<<calculateSalary()<<endl;
        cout<<"Number of Departments: "<<numOfDep<<endl;
    }

    double calculateSalary() override {
        return salary+(salary*0.05*numOfDep);
    }

};
double biggestSalary(Payable* payable[], int n){
    double max=0;
    int index=-1;
    for (int i = 0; i < n; ++i) {
        if(payable[i]->calculateSalary()>max){
            max=payable[i]->calculateSalary();
            index=i;
        }
    }
    return payable[index]->calculateSalary();
}

int main()
{
    Payable* payable[5];
    Developer developers[5];
    Manager managers[5];
    int j=0, k=0;
    for(int i=0; i<5; i++)
    {
        char name[50];
        int age;
        double salary;
        cin>>name>>age>>salary;
        if(i%2==0)
        {
            char programmingLanguage[50];
            cin>>programmingLanguage;
            developers[j]=Developer(name, age, salary, programmingLanguage);
            developers[j].displayInfo();
            payable[i]=&developers[j];
            j++;
        }
        else {
            int numberOfDepartments;
            cin>>numberOfDepartments;
            managers[k]=Manager(name, age, salary, numberOfDepartments);
            managers[k].displayInfo();
            payable[i]=&managers[k];
            k++;
        }
    }
   cout<<endl<<"Biggest Salary: "<<biggestSalary(payable, 5);
    return 0;
}