// Created by Hamdi on 3/29/2023.
//
#include <iostream>
#include <cstring>
#include <stdlib.h>
using namespace std;
class Piano{
    char serialno[25];
    float price;
    int year;
public:
    Piano(char *serialno="", float price=0, int year=0) : price(price), year(year) {
        strcpy(this->serialno,serialno);
    }

    bool equals( Piano &rhs)  {
        return !strcmp(serialno,rhs.serialno);
    }
    void print(){
        cout<<serialno<<" "<<year<<" "<<price<<endl;
    }


    void setSerial(const char *string) {
        strcpy(serialno,string);
    }

     Piano getSerial()  {
        return serialno;
    }

    friend class PShop;
};
class PShop{
    char name[50];
    Piano* pianos;
    int n;
    void copy(const PShop &other){
        strcpy(this->name,other.name);
        this->n=other.n;
        this->pianos=new Piano[other.n];
        for (int i = 0; i < n; ++i) {
            this->pianos[i]=other.pianos[i];
        }
    }
public:
      PShop(char *name=""){
        strcpy(this->name,name);
        this->n=0;
        this->pianos=new Piano[n];
      }
      PShop(const PShop &other){
          copy(other);
    }
    PShop &operator=(const PShop &other){
        if (this!=&other){
            delete[]pianos;
            copy(other);
        }
        return *this;
    }
    void add (Piano p){
        Piano *tmp=new Piano[n+1];
        for (int i = 0; i < n; ++i) {
            tmp[i]=pianos[i];
        }
        tmp[n]=p;
        n++;
        delete[]pianos;
        pianos=tmp;
    }
    void sell (Piano p){
        Piano *tmp=new Piano[n];
        int count=n;
        int index=0;
        for (int i = 0; i < n; ++i) {
            if (strcmp(p.serialno,pianos[i].serialno)==0){
                count--;
            } else{
                tmp[index++]=pianos[i];
            }
        }
        n=count;
        delete[]pianos;
        pianos=tmp;

    }
    void print() {
        cout<<name<<endl;
        for (int i = 0; i < n; ++i) {
            cout << i+1 << ". ";
            pianos[i].print();
        }
    }
    double value (){
        double sum=0;
        for (int i = 0; i < n; ++i) {
            sum+=pianos[i].price;
        }
        return sum;
    }

    Piano getP(int i) {

        if(i>=0&&i<n)
            return pianos[i];
        exit(1);
    }
};
//

int main() {

    int n;
    cin >> n;


    if(n == 1) {
        cout << "---Class Piano---" << endl;
        char serialNo[25];
        int pYear;
        float price;
        cin>>serialNo>>price>>pYear;
        Piano p(serialNo,price,pYear);
        p.print();
    } else if(n == 2) {
        cout << "---Equals---" << endl;
        char serialNo[25];
        int pYear;
        float price;
        cin>>serialNo>>price>>pYear;
        Piano p1(serialNo,price,pYear);
        Piano p2(p1);
        if (p1.equals(p2))
            cout<<"Equality"<<endl;
        else
            cout<<"Inequality"<<endl;
        p2.setSerial("12344");
        if (p1.equals(p2))
            cout<<"Equality"<<endl;
        else
            cout<<"Inequality"<<endl;
   }
     else if(n == 3) {
        cout << "---Class PShop---" << endl;
        char name[50];
        cin >> name;
        PShop ps(name);
        ps.print();
    } else if(n == 4) {
        cout << "---Add method---" << endl;
        char name[50];
        cin >> name;
        int no;
        cin>>no;
        PShop ps(name);
        char serialNo[25];
        int pYear;
        float price;
        for (int i=0;i<no;i++) {
            cin>>serialNo>>price>>pYear;
            Piano p(serialNo,price,pYear);
            ps.add(p);
        }
        ps.print();
    } else if(n == 5) {
        cout << "---Add method---" << endl;
        char name[50];
        cin >> name;
        int no;
        cin>>no;
        PShop ps(name);
        char serialNo[25];
        int pYear;
        float price;
        for (int i=0;i<no;i++) {
            cin>>serialNo>>price>>pYear;
            Piano p(serialNo,price,pYear);
            ps.add(p);
        }
        PShop ps2(ps), ps3;

        cin>>serialNo>>price>>pYear;
        Piano p1(serialNo,price,pYear);
        ps2.add(p1);

        ps.print();
        ps2.print();

        ps3 = ps;
        cin>>serialNo>>price>>pYear;
        Piano p2(serialNo,price,pYear);
        ps3.add(p2);

        ps.print();
        ps3.print();

    } else if(n == 6) {
        cout << "---value method---" << endl;
        char name[50];
        cin >> name;
        int no;
        cin>>no;
        PShop ps(name);
        char serialNo[25];
        int pYear;
        float price;
        for (int i=0;i<no;i++) {
            cin>>serialNo>>price>>pYear;
            Piano p(serialNo,price,pYear);
            ps.add(p);
        }
        cout<<"Total price: "<<ps.value()<<endl;
    }
    else if(n == 7) {
        cout << "---sell method---" << endl;
        char name[50];
        cin >> name;
        int no;
        cin>>no;
        PShop ps(name);
        char serialNo[25];
        int pYear;
        float price;
        for (int i=0;i<no;i++) {
            cin>>serialNo>>price>>pYear;
            Piano p(serialNo,price,pYear);
            ps.add(p);
        }
        int d;
        cin>>d;
        Piano p1(ps.getP(d).getSerial());
        ps.sell(p1);
        ps.print();
    } else if(n == 8) {
        cout << "---Full Test---" << endl;
        char name[50];
        cin >> name;
        int no;
        cin>>no;
        PShop ps(name);
        char serialNo[25];
        int pYear;
        float price;
        for (int i=0;i<no;i++) {
            cin>>serialNo>>price>>pYear;
            Piano p(serialNo,price,pYear);
            ps.add(p);
        }
        ps.print();

        cout<<endl;

        PShop ps2(ps), ps3;

        cin>>serialNo>>price>>pYear;
        Piano p1(serialNo,price,pYear);
        ps2.add(p1);

        ps.print();
        ps2.print();

        ps3 = ps;
        cin>>serialNo>>price>>pYear;
        Piano p2(serialNo,price,pYear);
        ps3.add(p2);

        ps.print();
        ps3.print();

        cout<<endl;

        cout<<"Total price: "<<ps.value()<<endl;

        cout<<endl;

        int d;
        cin>>d;
        Piano p3(ps.getP(d).getSerial());
        ps.sell(p3);
        ps.print();

        cout<<"Total price: "<<ps.value()<<endl;
    }
    return 0;
}
