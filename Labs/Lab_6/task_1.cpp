//
// Created by Hamdi on 4/29/2023.
//
#include <iostream>
#include <cstring>
using namespace std;
class DisciplinaryAction{
    char * name;
    int index;
    char * reason;
    int session;
    void copy(const DisciplinaryAction &other){
        this->name=new char[strlen(other.name)+1];    strcpy(this->name, other.name);
        this->index=other.index;
        this->reason= new char[strlen(other.reason)+1]; strcpy(this->reason, other.reason);
        this->session=other.session;
    }
public:
    DisciplinaryAction(char *name="", int index=0, char *reason="", int session=0): index(index), session(session){
        this->name=new char[strlen(name)+1];    strcpy(this->name, name);
        this->reason= new char[strlen(reason)+1]; strcpy(this->reason, reason);
    }

    DisciplinaryAction(const DisciplinaryAction &other){
        copy(other);
    }

    ~DisciplinaryAction(){
        delete[]name;
        delete[]reason;
    }
    void setIndex(int id){
        index=id;
    }
//    int getIndex(){
//        return index;
//    }

    DisciplinaryAction &operator=(const DisciplinaryAction &other){
        if(this!=&other){
            delete[]name;
            delete[]reason;
            copy(other);
        }
        return *this;
    }
//operator <<
friend ostream & operator<<(ostream & out, const DisciplinaryAction & d){
        out<<"Student: "<<d.name<<endl;
        out<<"Student's index: "<<d.index<<endl;
        out<<"Reason: "<<d.reason<<endl;
        out<<"Sessions: "<<d.session<<endl;
        return out;
    }

    //operator ++
    DisciplinaryAction &operator++(){
        ++session;
        return *this;
    }

    //operator >=
   bool operator>=(const DisciplinaryAction &other)const{
        return session >= other.session;

    }


};

int main() {
    int n;
    cin >> n;

    /// Testing Default constructor and equal operator
    /// Array input

    DisciplinaryAction arr[n];

    for (int i = 0; i < n; i++) {
        char name[100];
        char reason[100];
        int index;
        int sessions;

        cin >> name >> index >> reason >> sessions;

        arr[i] = DisciplinaryAction(name, index, reason, sessions);
    }

    cout << "-- Testing operator = & operator <<  --\n";
    cout << arr[0];

    /// Testing copy constructor & set index

    DisciplinaryAction merka(arr[0]);
    merka.setIndex(112233);

    cout << "\n-- Testing copy constructor & set index --\n";
    cout << "-------------\n";
    cout << "Source:\n";
    cout << "-------------\n";
    cout << arr[0];

    cout << "\n-------------\n";
    cout << "Copied and edited:\n";
    cout << "-------------\n";
    cout << merka;

    /// Testing if array is OK

    cout << "\n-- Testing if array was inputted correctly --\n";

    for (int i = 0; i < n; i++)
        cout << arr[i];


    cout << "\nTesting operator ++ and <<" << endl;
    for (int i = 0; i < n; i++)
        cout << (++arr[i]);


    cout << "\nTesting operator >=" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                cout << i << " " << ((arr[i] >= arr[j]) ? ">= " : "< ") << j << endl;
            }
        }
    }

    return 0;
}