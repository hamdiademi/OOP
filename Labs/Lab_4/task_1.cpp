// Created by Hamdi on 3/28/2023.

#include <iostream>
#include <cstring>
using namespace std;

class DisciplinaryAction{
private:
    char* name;
    int id;
    char* reason;
    void copy(const DisciplinaryAction &other){
        this->name=new char[strlen(other.name)+1];strcpy(this->name,other.name);
        this->id=other.id;
        this->reason= new char[strlen(other.reason)+1];strcpy(this->reason,other.reason);
    }
public:
    DisciplinaryAction(char *name="", int id=0, char *reason=""){
        this->name=new char[strlen(name)+1];strcpy(this->name,name);
        this->id=id;
        this->reason= new char[strlen(reason)+1];strcpy(this->reason,reason);
    }
    DisciplinaryAction(const DisciplinaryAction &other){
        copy(other);
    }
    DisciplinaryAction & operator=(const DisciplinaryAction & other){
        if(this==&other){
            return *this;
        }
        delete[] name;
        delete[] reason;
        copy(other);
        return *this;
    }
    ~DisciplinaryAction(){
        delete[]name;
        delete[]reason;
    }

    void setIndex(int id) {
        this->id = id;
    }
    void print(){
        cout<<"Student: "<<name<<endl;
        cout<<"Student's index: "<<id<<endl;
        cout<<"Reason: "<<reason<<endl;
    }


};

///Do not change the main
int main() {
    int n;
    cin >> n;

    /// Testing Default constructor and equal operator
    /// Array input

    DisciplinaryAction arr[n];

    for(int i = 0; i < n; i++) {
        char name[100];
        char reason[100];
        int index;

        cin >> name >> index >> reason;

        arr[i] = DisciplinaryAction(name, index, reason);
    }

    cout << "-- Testing operator = & print() --\n";
    arr[0].print();

    /// Testing copy constructor & set index

    DisciplinaryAction merka(arr[0]);
    merka.setIndex(112233);

    cout << "\n-- Testing copy constructor & set index --\n";
    cout << "-------------\n";
    cout << "Source:\n";
    cout << "-------------\n";
    arr[0].print();

    cout << "\n-------------\n";
    cout << "Copied and edited:\n";
    cout << "-------------\n";
    merka.print();

    /// Testing if array is OK

    cout << "\n-- Testing if array was inputted correctly --\n";

    for(int i = 0; i < n; i++)
        arr[i].print();

    return 0;
}
