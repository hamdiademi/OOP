// Created by Hamdi on 3/29/2023.
//
#include <iostream>
#include <cstring>
using namespace std;

class Pasta{
    char *name;
    float price;
    int discount;
    int calories;
    void copy(const Pasta &other){
        this->name=new char[strlen(other.name)+1];
        strcpy(this->name,other.name);
        this->price=other.price;
        this->calories=other.calories;
        this->discount=other.discount;
    }
public:
    Pasta(char *name="", float price=0, int calories=0){
        this->name=new char[strlen(name)+1];
        strcpy(this->name,name);
        this->price=price;
        this->calories=calories;
        this->discount=0;
    }
    Pasta(const Pasta &other){
        copy(other);
    }
    Pasta &operator=(const Pasta &other){
        if (this!=&other){
            delete[] name;
            copy(other);
        }
        return *this;
    }
    void print(){
        cout<<name<<" "<<calories<<" "<<price;
        if (discount>0){

            cout<<" ("<<price-(price*discount/100)<<")";
        }
    }

    int dby5(){
        return discount=5;
    }
    Pasta light(int cal){
        int index=0;
        char *tmp=new char[strlen(name)+6];
        char light [6]="Light";
        for (int i = 0; i < strlen(name); ++i) {
            tmp[index++]=name[i];
        }
        for (int i = 0; i < strlen(light); ++i) {
            tmp[index++]=light[i];
        }

        delete[] name;
        name=tmp;

        calories-=cal;
        price-=price*0.2;
        discount=0;
        return *this;
    }

    void setName(char *n) {
        name = n;
    }

    void setStudentDiscount(int dis) {
        discount = dis;
    }
    ~Pasta(){
       // delete[] titleM;
    }

};

class ItalianRestaurant{
    char name[51];
    Pasta *pastas;
    int n;
    void copy(const ItalianRestaurant &other){
        strcpy(this->name,other.name);
        this->n=other.n;
        this->pastas=new Pasta[other.n];
        for (int i = 0; i < n; ++i) {
            this->pastas[i]=other.pastas[i];
        }
    }
public:
     ItalianRestaurant(char *name=""){
        strcpy(this->name,name);
         this->n=0;
         this->pastas=new Pasta[n];
    }

    ItalianRestaurant(const ItalianRestaurant &other){
        copy(other);
    }

    ItalianRestaurant &operator=(const ItalianRestaurant &other){
        if (this!=&other){
            delete[] pastas;
            copy(other);
        }
        return *this;
    }
    ~ItalianRestaurant(){
        delete[] pastas;
    }

    ItalianRestaurant add(Pasta &p){
        Pasta *tmp=new Pasta[n+1];
        for (int i = 0; i < n; ++i) {
            tmp[i]=pastas[i];
        }
        tmp[n]=p;
        delete[]pastas;
        pastas=tmp;
        n++;
        return *this;
    }

    void print(){
        cout<<name<<endl;
        for (int i = 0; i < n; ++i) {
            pastas[i].print();
            cout<<endl;
        }

    }

    void setPasta(int i, Pasta &p) {
       pastas[i]=p;
    }

};

int main() {
    char name[100];
    float price;
    int discount;
    int calories;

    int testCase;

    cin >> testCase;

    if(testCase == 1) {
        cout << "====== TESTING Pasta CLASS ======" << endl;
        cin >> name;
        cin >> price;
        cin >> discount;
        cin >> calories;
        cout << "CONSTRUCTOR" << endl;
        Pasta c1(name, price, calories);
        c1.setStudentDiscount(discount);
        cin >> name;
        cin >> price;
        cin >> discount;
        cin >> calories;
        Pasta c2(name, price, calories);
        c2.setStudentDiscount(discount);
        cout << "Print" << endl;
        c1.print();
        cout << endl;
        c2.print();
        cout << endl;
        cout << "Decrease by 5" << endl;
        c1.dby5();
        c1.print();
        cout << endl;
        cout << "Calories" << endl;
        int ca;
        cin >> ca;
        Pasta c3 = c1.light(ca);
        c3.print();
        cout << endl;
    } else if(testCase == 2) {
        cout << "====== TESTING Pasta CONSTRUCTORS ======" << endl;
        cin >> name;
        cin >> price;
        cin >> discount;
        cin >> calories;
        cout << "CONSTRUCTOR" << endl;
        Pasta c1(name, price, calories);
        c1.print();
        cout << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        Pasta c2(c1);
        cin >> name;
        c2.setName(name);
        c1.print();
        cout << endl;
        c2.print();
        cout << endl;
        cout << "OPERATOR =" << endl;
        c1 = c2;
        cin >> name;
        c2.setName(name);
        c1.print();
        cout << endl;
        c2.print();
        cout << endl;

    } else if(testCase == 3) {
        cout << "====== TESTING Italian Restaurant ======" << endl;
        char csName[50];
        cin >> csName;
        cout << "CONSTRUCTOR" << endl;
        ItalianRestaurant cs(csName);
        int n;
        cin >> n;
        cout << "Add" << endl;
        for(int i = 0; i < n; ++i) {
            cin >> name;
            cin >> price;
            cin >> calories;
            Pasta c(name, price, calories);
            cs.add(c);
        }
        cs.print();
        cout << endl;

    } else if(testCase == 4) {
        cout << "====== TESTING Italian Restaurant CONSTRUCTORS ======" << endl;
        char csName[50];
        cin >> csName;
        ItalianRestaurant cs(csName);
        int n;
        cin >> n;
        for(int i = 0; i < n; ++i) {
            cin >> name;
            cin >> price;
            cin >> calories;
            Pasta c(name, price, calories);
            cs.add(c);
        }
        Pasta x("Funghi", 260, 275);
        ItalianRestaurant cp = cs;
        cs.setPasta(0, x);
        cs.print();
        cout << endl;
        cp.print();
        cout << endl;
    }


    return 0;
}