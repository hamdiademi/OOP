#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

class Employee{
private:
    char name[101];
    char surname[101];
    int salary;
    void copy(const Employee &other){
        strcpy(this->name,other.name);
        strcpy(this->surname,other.surname);
        this->salary=other.salary;
    }
public:
    Employee() {}

    Employee(const char* name,const char* surname,int salary){
        strcpy(this->name,name);
        strcpy(this->surname,surname);
        this->salary=salary;
    }
    Employee(const Employee &other){
        copy(other);
    }


    // Get method for the salary of the Employee
    int getSalary() const {
        return salary;
    }

    // Set method for the salary of the Employee
    void setSalary(int salary) {
        this->salary = salary;
    }
    void printEmployee(){
        cout<<"Employee name: "<<name<<endl;
        cout<<"Employee surname: "<<surname<<endl;
        cout<<"Employee salary: "<<salary<<endl;
    }
};

class TechCompany {
private:
    char name[101];
    int numofemp;
    Employee employee[100];

    void copy(const TechCompany &other){
        strcpy(this->name, other.name);
        this->name[100] = '\0';
        this->numofemp = other.numofemp;
        for (int i = 0; i < numofemp; ++i) {
            employee[i] = other.employee[i];
        }
    }
public:
    TechCompany() {}

    TechCompany(const char *name) {
        strcpy(this->name, name);
        numofemp = 0;
    }
    TechCompany (const TechCompany &other){
        copy(other);
    }

//    TechCompany(char string[100]) {
//        strcpy(string, name);
//        name[100] = '\0';
//    }


    void setName(const char *name) {
        strcpy(this->name, name);
    }
    const char* getName() const {
        return name;
    }
    int getNumEmployees() const {
        return numofemp;
    }
    const Employee& getEmployee(int i) const {
        return employee[i];
    }
//
    void addEmployee(const Employee& employees) {
        if (numofemp < 20)
            employee[numofemp++] = employees;

    }

    double getAverageOfEmployeeSalary() {
        double totalSalary = 0;
        for (int i = 0; i < numofemp; i++) {
            totalSalary += employee[i].getSalary();
        }
        if (numofemp > 0) {
            return totalSalary / numofemp;
        } else {
            return 0;
        }
    }
    void print(){
        cout<<"Tech company name: "<<name<<endl;
        cout<<"Number of employees: "<<numofemp<<endl;
    }



};

//outside classes



TechCompany printCompanyWithHighestAverageSalary(TechCompany companies[], int numCompanies) {
    int highestIndex = -1;
    double highestAverageSalary = -1;

    for (int i = 0; i < numCompanies; i++) {
        double averageSalary = companies[i].getAverageOfEmployeeSalary();

        if (averageSalary > highestAverageSalary) {
            highestAverageSalary = averageSalary;
            highestIndex = i;
        }
    }
    return companies[highestIndex];
}

TechCompany printCompanyWithHighestStdSalary(TechCompany companies[], int numCompanies) {
    int highestIndex = -1;
    double highestStdSalary = -1;

    for (int i = 0; i < numCompanies; i++) {
        int numEmployees = companies[i].getNumEmployees();

        double meanSalary = companies[i].getAverageOfEmployeeSalary();
        double variance = 0.0;

        for (int j = 0; j < numEmployees; j++) {
            double diff = companies[i].getEmployee(j).getSalary() - meanSalary;
            variance += diff * diff;
        }

        double stdSalary = std::sqrt(variance / (numEmployees-1));

        if (stdSalary > highestStdSalary) {
            highestStdSalary = stdSalary;
            highestIndex = i;
        }
    }

    return companies[highestIndex];
}




bool isSameCompany(TechCompany company1, TechCompany company2) {
    return strcmp(company1.getName(), company2.getName()) == 0;
}


int main() {
    const int MAX_COMPANIES = 10;
    const int MAX_EMPLOYEES = 20;

    TechCompany companies[MAX_COMPANIES];

    int n;
    std::cin >> n;

    for (int i = 0; i < n; i++) {
        char name[100];
        std::cin >> name;

        TechCompany company(name);

        int m;
        std::cin >> m;

        for (int j = 0; j < m; j++) {
            char name[100];
            char surname[100];
            int salary;

            std::cin >> name;

            std::cin >> surname;

            std::cin >> salary;

            Employee employee(name, surname, salary);

            company.addEmployee(employee);
        }

        companies[i] = company;
    }

    TechCompany copy = companies[0];

    std::cout<<"-->Testing get and set methods for one object and copy constructor"<<std::endl;
    copy.setName("copy");
    std::cout << copy.getName() << std::endl;


    std::cout<<"-->Testing addEmployee function"<<std::endl;
    Employee newEmployee("John", "Doe", 5000);
    copy.addEmployee(newEmployee);
    std::cout << "Number of employees in copy: " << copy.getNumEmployees() << std::endl;


    std::cout<<"-->Testing copy of first employee"<<std::endl;
    Employee firstEmployee = copy.getEmployee(0);
    firstEmployee.printEmployee();


    std::cout<<"-->Testing methods"<<std::endl;
    TechCompany t = printCompanyWithHighestAverageSalary(companies, n);
    TechCompany t1 = printCompanyWithHighestStdSalary(companies, n);

    std::cout << "Tech company with the highest average salary: " << t.getName() << std::endl;
    std::cout << "Tech company with the highest standard deviation for salaries: " <<t1.getName() << std::endl;

    if (isSameCompany(t, t1)){
        std::cout<<"The tech company: "<<t.getName()<<" has the highest standard deviation and highest average salary"<<std::endl;
    }

    return 0;
}
