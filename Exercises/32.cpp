//
// Created by Hamdi on 6/7/2023.
//
#include <iostream>
#include <cstring>
using namespace std;
class OperationNotSupported{
    char msg[100];
public:
     OperationNotSupported(char *msg){
        strcpy(this->msg,msg);
    }
    void showMessage(){
    cout<<msg<<endl;
    }
};
class User {
    char *username;
    char *companyName;
    int position;

    void copy(const User &u) {
        this->username = new char[strlen(u.username) + 1];
        strcpy(this->username, u.username);
        this->companyName = new char[strlen(u.companyName) + 1];
        strcpy(this->companyName, u.companyName);
        this->position = u.position;
    }

public:
    User(char *username = "", char *companyName = "", int position = 0) {
        this->username = new char[strlen(username) + 1];
        strcpy(this->username, username);
        this->companyName = new char[strlen(companyName) + 1];
        strcpy(this->companyName, companyName);
        this->position = position;
    }

    User(const User &u) {
        copy(u);
    }

    User &operator=(const User &u) {
        if (this != &u) {
            delete[] username;
            delete[] companyName;
            copy(u);
        }
        return *this;
    }

    ~User() {
        delete[] username;
        delete[] companyName;
    }

    char *getUsername() const {
        return username;
    }

    void setUsername(char *username) {
        this->username = new char[strlen(username) + 1];
        strcpy(this->username, username);
    }

    char *getCompanyName() const {
        return companyName;
    }

    void setCompanyName(char *companyName) {
        this->companyName = new char[strlen(companyName) + 1];
        strcpy(this->companyName, companyName);
    }

    int getPosition() const {
        return position;
    }

    void setPosition(int position) {
        this->position = position;
    }


    friend ostream &operator<<(ostream &os, const User &user) {
        return os << "Username: " << user.username
                  << " Company name: " << user.companyName
                  << " Position: " << user.position;
    }

    friend istream &operator>>(istream &in, User &user) {
        return in >> user.username >> user.companyName >> user.position;
    }

    bool operator==(User &u) {
        return strcmp(this->username, u.username) == 0;
    }
};

class Group{
protected:
    User* users;
    int n;
    char name[50];
    void copy(const Group &other){
        strcpy(this->name,other.name);
        this->n=other.n;
        this->users=new User[other.n];
        for (int i = 0; i < n; ++i) {
            this->users[i]=other.users[i];
        }
    }
public:
     Group(char *name){
         strcpy(this->name,name);
         this->n=0;
         this->users=new User[n];
     }
     Group(const Group &other){
         copy(other);
    }
    Group &operator=(const Group &other){
        if (this!=&other){
            delete[]users;
            copy(other);
        }
        return *this;
    }
    virtual void addMember(User &u){
         for (int i = 0; i < n; ++i) {
             if (strcmp(users[i].getUsername(),u.getUsername())==0){
                 throw OperationNotSupported("Username already exists");
             }
         }
         User *tmp=new User[n+1];
         for (int i = 0; i < n; ++i) {
             tmp[i]=users[i];
         }
         tmp[n]=u;
         n++;
         delete[]users;
         users=tmp;
     }
     double avgPosition(){
         double sum=0;
         for (int i = 0; i < n; ++i) {
             sum+=users[i].getPosition();
         }
         return sum/n;
     }
     virtual double rating(){
         //(10 - average_level_of_positions_of_the_members) * number_of_members / 100.
         return (10-avgPosition())*n/100.0;
     }

    friend ostream & operator << (ostream & out,  Group & g){
        out << "Group: " << g.name << endl;
        out << "Members: " << g.n << endl;
        out << "Rating: " << g.rating() << endl;
        out << "Members list:" << endl;
        if (g.n==0) {
            return out << "EMPTY";
        } else {
            for (int i=0;i<g.n;i++){
                out << i+1 << ". " << g.users[i] << endl;
            }
            return out;
        }
    }
};
class PrivateGroup: public Group{
    static int capacity;
public:
    PrivateGroup(char *name) : Group(name) {}

    void addMember(User &u) override{
        if (n>capacity){
            throw OperationNotSupported("The group’s capacity has been exceeded.");
        }
        addMember(u);
    }

    double rating() override{
        return (10-avgPosition())*((float )n/(float )capacity)*0.8;
    }

    friend ostream & operator << (ostream & out, const PrivateGroup & pg) {
        out << "Private ";
        Group g (pg);
        return out << g;
    }

    static int getCapacity(){
        return capacity;
    }


    static void setCapacity(int capacity){
        PrivateGroup::capacity = capacity;
    }
};
int PrivateGroup::capacity=10;




int main() {
    int testCase;
    cin >> testCase;
    if (testCase == 1) {
        cout << "TESTING CLASS GROUP: CONSTRUCTOR AND OPERATOR <<" << endl;
        Group g("test");
        cout << g;
    } else if (testCase == 2) {
        cout << "TESTING CLASS PRIVATE GROUP: CONSTRUCTOR AND OPERATOR <<" << endl;
        PrivateGroup pg("private test");
        cout << pg;
    } else if (testCase == 3) {
        cout << "TESTING CLASS GROUP: CONSTRUCTOR, METHOD ADD_MEMBER AND OPERATOR <<" << endl;
        Group *g = new Group("FINKI students");
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            User u;
            cin >> u;
            g->addMember(u);
        }
        cout << *g;
        delete g;
    } else if (testCase == 4) {
        cout << "TESTING CLASS PRIVATE_GROUP: CONSTRUCTOR, METHOD ADD_MEMBER AND OPERATOR <<" << endl;
        Group *g = new PrivateGroup("FINKI students");
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            User u;
            cin >> u;
            g->addMember(u);
        }
        cout << *g;
        delete g;
    } else if (testCase == 5) {
        cout << "TESTING CLASS GROUP: CONSTRUCTOR, METHOD ADD_MEMBER, EXCEPTION AND OPERATOR <<" << endl;
        Group *g = new Group("FINKI students");
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            User u;
            cin >> u;
            try {
                g->addMember(u);
            } catch (OperationNotSupported e) {
                e.showMessage();
            }

        }
        cout << *g;
        delete g;
    } else if (testCase == 6) {
        cout << "TESTING CLASS PRIVATE GROUP: CONSTRUCTOR, METHOD ADD_MEMBER, EXCEPTION AND OPERATOR <<" << endl;
        Group *g = new PrivateGroup("FINKI");
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            User u;
            cin >> u;
            try {
                g->addMember(u);
            } catch (OperationNotSupported e) {
                e.showMessage();
            }

        }
        cout << *g;
        delete g;
    } else if (testCase == 7) {
        cout << "TESTING CLASS PRIVATE GROUP: CONSTRUCTOR, METHOD ADD_MEMBER AND CHANGE OF STATIC MEMBER"
             << endl;
        Group *g = new PrivateGroup("DevOps");
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            User u;
            cin >> u;
            g->addMember(u);
        }
        cout << "RATING BEFORE CHANGE" << endl;
        cout << g->rating();
        PrivateGroup::setCapacity(20);
        cout << "RATING AFTER CHANGE" << endl;
        cout << g->rating();
        delete g;
    } else if (testCase == 8) {
        cout << "TESTING CLASS PRIVATE GROUP: CONSTRUCTOR, METHOD ADD_MEMBER, EXCEPTION AND CHANGE OF STATIC MEMBER"
             << endl;

        Group *g = new PrivateGroup("FINKI");
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            User u;
            cin >> u;

            g->addMember(u);

            int capacity = PrivateGroup::getCapacity();
            cout << "Increasing capacity from " << capacity << " to " << capacity + 1 << endl;
            PrivateGroup::setCapacity(capacity + 1);
            try {
                g->addMember(u);
            }catch(OperationNotSupported &e){
                e.showMessage();
            }
            cout << g->rating() << endl;

        }

    } else {
        cout << "INTEGRATION TEST" << endl;
        char name[50];
        int nGroups;
        cin >> nGroups;
        Group **groups = new Group *[nGroups];
        for (int i = 0; i < nGroups; i++) {
            int type;
            cin >> type;
            cin >> name;
            if (type == 1) { //normal group
                groups[i] = new Group(name);
            } else { //private group
                groups[i] = new PrivateGroup(name);
            }
            int nUsers;
            cin >> nUsers;
            for (int j = 0; j < nUsers; j++) {
                User u;
                cin >> u;
                try {
                    groups[i]->addMember(u);
                }catch(OperationNotSupported &e){
                    e.showMessage();
                }

            }
        }

        cout << "BEFORE CHANGE OF PRIVATE GROUP COEFFICIENT" << endl;
        for (int i = 0; i < nGroups; ++i) {
            cout << *groups[i];
        }
        PrivateGroup::setCapacity(15);
        cout << "AFTER CHANGE OF PRIVATE GROUP COEFFICIENT" << endl;
        for (int i = 0; i < nGroups; ++i) {
            cout << *groups[i];
        }
    }
}