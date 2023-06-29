// Created by Hamdi on 3/29/2023.
//
#include<iostream>
#include <cstring>
using namespace std;

class Exeption{
    int n;
public:
    explicit Exeption(int n) : n(n) {}

    void message() {
        if (n){
            cout<<"The id number has more than 9 characters"<<endl;
        }
        else{
            cout<<"The id number has a non-digit character"<<endl;
        }
    }
};

class  DonationAction{
    char* name;
    char id[100];
    int collected;
    int needed;
    void copy(const DonationAction &other){
        this->name=new char[strlen(other.name)+1];
        strcpy(this->name,other.name);
        strcpy(this->id,other.id);
        this->needed=other.needed;
        this->collected=other.collected;
    }
public:
    DonationAction(char *name="", char *id="", int needed=0){
        this->name=new char[strlen(name)+1];
        strcpy(this->name,name);

        if (strlen(id)>9) {
            throw Exeption(1);
        }
        else {
            for (int i = 0; i < strlen(id); ++i) {
                if (!isdigit(id[i])) {
                    throw Exeption(0);
                }
            }
        }

        strcpy(this->id,id);
        this->needed=needed;
        this->collected=0;
    }
    DonationAction(const DonationAction &other){
        copy(other);
    }
    DonationAction &operator=(const DonationAction &other){
        if (this!=&other){
            delete[]name;
            copy(other);
        }
        return *this;
    }
    ~DonationAction(){
        delete[]name;
    }

    friend ostream &operator<<(ostream &os, const DonationAction &action) {
        int diff=action.needed-action.collected;
        if (diff>0) {
            os << action.id << " " << action.name << " " << action.needed - action.collected
               << " more denars are needed"<<endl;
        }else{
            os << action.id << " " << action.name << " collected" <<endl;

        }

        return os;
    }
    DonationAction &operator+=(int c){
        collected+=c;
        return *this;
    }


    const char *getId() const {
        return id;
    }
    int getdiff()const{
        return needed-collected;
    }
private:


};

class  DonationSociety{
    char name[30];
    DonationAction* actions;
    int n;
    void copy(const DonationSociety &other){
        strcpy(this->name,other.name);
        this->n=other.n;
        this->actions=new DonationAction[other.n];
        for (int i = 0; i < n; ++i) {
            this->actions[i]=other.actions[i];
        }
    }
public:
     DonationSociety(char *name) {
        strcpy(this->name,name);
         this->n=0;
        this->actions=new DonationAction[n];
    }
    DonationSociety(const DonationSociety &other){
        copy(other);
    }
    DonationSociety &operator=(const DonationSociety &other){
        if (this!=&other){
            delete[] actions;
            copy(other);
        }
        return *this;
    }

    bool takeDonation (char id[], int donatedFund){
        for (int i = 0; i < n; i++) {
            if (strcmp(actions[i].getId(), id) == 0) {
                actions[i] += donatedFund;
                return true;
            }
        }
        return false;
    }

    void operator+=(DonationAction &a){
        for (int i = 0; i < n; ++i) {
            if (strcmp(actions[i].getId(),a.getId())==0){
                return;
            }
        }
        DonationAction *tmp=new DonationAction[n+1];
        for (int i = 0; i < n; ++i) {
            tmp[i]=actions[i];
        }
        tmp[n]=a;
        n++;
        delete[]actions;
        actions=tmp;
    }

    friend ostream &operator<<(ostream &os, const DonationSociety &society) {
        for (int i = 0; i < society.n-1; i++) {
            if (society.actions[i].getdiff() <= society.actions[i+1].getdiff()) {
                swap(society.actions[i], society.actions[i+1]);
            }
        }
        for (int i = 0; i < society.n; ++i) {
            os<<society.actions[i];
        }

        os << "President:" << society.name<<endl;
        return os;
    }
};

int main() {


    DonationSociety donacii("Velko Velkovski");
    int n;
    char name[50], id[50];
    int needed, collected;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin.get();
        cin.getline(name, 50);
        cin >> id >> needed;
        try {
            DonationAction edna(name, id, needed);
            donacii += edna;
        }catch (Exeption &e){
            e.message();
        }
    }

    //donation
    cin >> n;
    for (int i = 0; i < n; i++) {

        cin >> id >> collected;
            if (!donacii.takeDonation(id, collected))
                cout << "The donation is not taken. Wrong ID." << endl;
    }
    cout << "===============" << endl;
    cout << donacii;
}