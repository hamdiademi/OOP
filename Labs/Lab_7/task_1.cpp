//
// Created by Hamdi on 5/3/2023.
//
#include<iostream>
#include<cstring>
using namespace std;

class Square{
protected:
    double a;
public:
    Square(double a=0.0){
        this->a=a;
    }
    Square(const Square &other){
        this->a=other.a;
    }
    double perimeter()const{
        return a*4;
    }
    double area()const{
        return a*a;
    }
    void print(){
        cout<<"Square with side a="<< a <<" has area P="<<area()<<" and perimeter L="<<perimeter()<<endl;
    }
};
class Rectangle: public Square{
    double x,y;
public:
    Rectangle(const Square &a=0.0, double x=0.0, double y=0.0): Square(a){
        this->x=x;
        this->y=y;
    }
    Rectangle(const Rectangle &other){
        this->a=other.a;
        this->x=other.x;
        this->y=other.y;
    }


    double perimeter(){
        if (x==y){
            return a=x*4;
        } else{
        return x*2+y*2;
        }
    }
    double area(){
        if (x==y){
            return a=x*y;
        } else{
            return x*y;
        }
    }
    void print() {
        if (x == y) {
            Square::print();
        } else {
            cout << "Rectangle with sides: " << x << " and " << y << "  P=" << area() << " and perimeter L="<< perimeter() << endl;
        }
    }

};

int main() {
    int n;
    double a,x,y;
    Square * kvadrati;
    Rectangle * pravoagolnici;

    cin>>n;

    kvadrati = new Square [n];
    pravoagolnici = new Rectangle [n];

    for (int i=0;i<n;i++){
        cin>>a;

        kvadrati[i] = Square(a);
    }

    for (int i=0;i<n;i++){
        cin>>x>>y;

        pravoagolnici[i]=Rectangle(kvadrati[i], x, y);
    }

    int testCase;
    cin>>testCase;

    if (testCase==1){
        cout<<"===Testing class Square==="<<endl;
        for (int i=0;i<n;i++)
            kvadrati[i].print();
    }
    else {
        cout<<"===Testing class Rectangle==="<<endl;
        for (int i=0;i<n;i++)
            pravoagolnici[i].print();
    }
}