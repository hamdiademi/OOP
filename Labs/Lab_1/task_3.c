#include <stdio.h>
typedef struct E{
    char name[50];
    char id[50];
    int salary;
}Employee;

void reademp(Employee*e){
    scanf("%s %s %d",e->name,e->id,&e->salary);
}
void printemp(Employee e){
    printf("%s %s %d\n",e.name,e.id,e.salary);
}

typedef struct C{
    char name[50];
    int employees;
    Employee Employee[50];
}Company;

void read(Company *c){
    scanf("%s %d",c->name,&c->employees);
    for (int i = 0; i < c->employees; ++i) {
        reademp(&c->Employee[i]);
    }
}

//

int average(Company c,Employee e){
    int sum=0;
    for (int i = 0; i < c.employees; ++i) {
        sum+=c.Employee[i].salary;
    }
    return sum;
}


void PrintAverageSalary(Company c,int sum) {
    for (int i = 0; i < c.employees; ++i) {
        if (c.Employee[i].salary < sum) {
            printemp(c.Employee[i]);
        }
    }
}


    void PrintHighSalary(Company c, int sum) {
        for (int i = 0; i < c.employees; ++i) {
            if (c.Employee[i].salary > sum) {
                printemp(c.Employee[i]);
            }
        }

    }


    int main() {
        int n;
        scanf("%d", &n);
        Company cc[100];
        Employee ee[100];
        int sum = 0, count = 0;

        for (int i = 0; i < n; ++i) {
            read(&cc[i]);
            count += cc[i].employees;
            sum += average(cc[i], ee[i]);


        }
        sum /= count;
        printf("Employees with salary below average:\n");
        for (int i = 0; i < n; ++i) {
            PrintAverageSalary(cc[i], sum);
        }
        printf("\nEmployees with highest salary:\n");
        for (int i = 0; i < n; ++i) {
            PrintHighSalary(cc[i],sum);
        }


        return 0;
    }
