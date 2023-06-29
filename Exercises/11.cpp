// Created by Hamdi on 3/29/2023.
//
#include <iostream>
#include <cstring>
using namespace std;

class Exception{
    int value;
public:
   Exception(int value) : value(value) {}
    void showMessage(){
       cout<<"Invalid discount value: "<<value<<endl;
   }
};

class IceCream{
    char *name;
    char ingr[101];
    float price;
    int discount;
    void copy(const IceCream &other){
        this->name=new char [strlen(other.name)+1];
        strcpy(this->name,other.name);
        strcpy(this->ingr,other.ingr);
        this->price=other.price;
        this->discount=other.discount;
    }
public:

    IceCream(const char *name="", char *ingr="", float price=0){
        this->name=new char [strlen(name)+1];
        strcpy(this->name,name);
        strcpy(this->ingr,ingr);
        this->price=price;
        this->discount=0;
    }

    IceCream(const IceCream &other){
        copy(other);
    }
    IceCream &operator=(const IceCream &other){
        if (this!=&other){
            delete[]name;
            copy(other);
        }
        return *this;
    }

    IceCream operator++(){
        discount+=5;
        return *this;
    }

    IceCream &operator+(char *add){
        char *tmp=new char[strlen(name) + strlen(add)+4];
        int index=0;
        for (int i = 0; i < strlen(name); ++i) {
            tmp[index++]=name[i];
        }
        tmp[index++]=' ';
        tmp[index++]='+';
        tmp[index++]=' ';
        for (int i = 0; i <strlen(add) ; ++i) {
            tmp[index++]=add[i];
        }
        tmp[index] = '\0';
        delete[]name;
        name=tmp;
        price+=10;
        return *this;
    }

     void setStudentDiscount(int dis){
         if (dis < 0 || dis >100){
             throw Exception(dis);
         }
         discount += dis;
    }

    void setName(char *name){
        delete[] this->name;
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }


    friend ostream &operator<<(ostream &os, const IceCream &cream){
        os << cream.name<<": " << cream.ingr<< " " << cream.price;
        if (cream.discount){
            os<<" ("<<cream.price-(cream.price*cream.discount/100)<<")";
        }
        return os;
    }

    ~IceCream(){
//        if (titleM != nullptr) {
//            delete[] titleM;
//        }
    }


};
///

class IceCreamShop{
    char name[51];
    IceCream* icecreams;
    int n;
    void copy(const IceCreamShop &other){
        strcpy(this->name,other.name);
        this->n=other.n;
        this->icecreams=new IceCream[other.n];
        for (int i = 0; i < n; ++i) {
            this->icecreams[i]=other.icecreams[i];
        }
    }
public:
     IceCreamShop(char *name=""){
        strcpy(this->name,name);
         this->n=0;
         this->icecreams=new IceCream[n];
    }
    IceCreamShop(const IceCreamShop &other){
        copy(other);
    }
    IceCreamShop &operator=(const IceCreamShop &other){
        if (this!=&other){
            delete[]icecreams;
            copy(other);
        }
        return *this;
    }

    IceCreamShop &operator+=(IceCream &ic){
        IceCream *tmp=new IceCream[n+1];

        for (int i = 0; i < n; ++i) {
          tmp[i]=icecreams[i];
        }
        tmp[n]=ic;
        n++;
        delete[] icecreams;
        icecreams=tmp;
        return *this;

    }

    friend ostream &operator<<(ostream &os, const IceCreamShop &shop) {
        os  << shop.name<<endl;
        for (int i = 0; i < shop.n; ++i) {
            os<<shop.icecreams[i]<<endl;
        }
        return os;
    }

    ~IceCreamShop(){
     //   delete[]icecreams;
    }
};


// DO NOT CHANGE THE MAIN FUNCTION, EXCEPT THE MARKED PART FOR HANDLING WITH THE EXCEPTION
int main() {
    char name[100];
    char ingr[100];
    float price;
    int discount;

    int testCase;

    cin >> testCase;
    cin.get();
    if(testCase == 1) {
        cout << "====== TESTING IceCream CLASS ======" << endl;
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        cin >> discount;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        ic1.setStudentDiscount(discount);
        cin.get();
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        cin >> discount;
        IceCream ic2(name, ingr, price);
        ic2.setStudentDiscount(discount);
        cout << "OPERATOR &lt;&lt;" << endl;
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR ++" << endl;
        ++ic1;
        cout << ic1 << endl;
        cout << "OPERATOR +" << endl;
        IceCream ic3 = ic2 + "chocolate";
        cout << ic3 << endl;
    } else if(testCase == 2) {
        cout << "====== TESTING IceCream CONSTRUCTORS ======" << endl;
        cin.getline(name, 100);
        cin.getline(ingr, 100);
        cin >> price;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        cout << ic1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        IceCream ic2(ic1);
        cin.get();
        cin.getline(name, 100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR =" << endl;
        ic1 = ic2;
        cin.getline(name, 100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "TESTING EXCEPTION" << endl;

        // your exception handling code

        cin >> discount;
        try {
            ic1.setStudentDiscount(discount);
        }catch (Exception &e){
            e.showMessage();
        }

    }
     else if(testCase == 3) {
        cout << "====== TESTING IceCreamShop ======" << endl;
        char icsName[50];
        cin.getline(icsName,100);
        cout << "CONSTRUCTOR" << endl;
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        cout << "OPERATOR +=" << endl;
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,100);
            cin.getline(ingr,100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        cout << ics;
    } else if(testCase == 4) {
        cout << "====== TESTING IceCreamShop CONSTRUCTORS ======" << endl;
        char icsName[50];
        cin.getline(icsName,100);
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,100);
            cin.getline(ingr,100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        IceCream x("FINKI fruits", "strawberry ice cream, raspberry ice cream, blueberry ice cream", 60);
        IceCreamShop icp = ics;
        ics+=x;
        cout << ics << endl;
        cout << icp << endl;
    }


    return 0;
}