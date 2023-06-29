// Created by Hamdi on 3/29/2023.
//
#include<iostream>
#include<cstring>
#include <string>
using namespace std;

class Exception{
public:
    void showMessages(){
        cout<<"The bill already exists"<<endl;
    }
};

class Bill{
    char* number;
    int expense;
    char date [20];
    bool status;
public:
    Bill(char *number="", int expense=0, char *date="", bool status= false){

       this->number=new char[strlen(number)+1];
       strcpy(this->date,date);
       this->expense=expense;
       strcpy(this->number,number);
       this->status=status;
    }

    bool operator==(const Bill &rhs) const {
        return !strcmp(rhs.number,number);
    }

    friend ostream &operator<<(ostream &os, const Bill &bill) {
        os <<  bill.number << "(" << bill.date << ") - " << bill.expense<<endl;
        return os;
    }

    const char *getMonth() {
        char month[3];
        for (int i = 0; i < 2; ++i) {
            month[i]=date[i];
        }
        return month;
    }

    const char *getYear()  {
        char year[5];
        int j=0;
        for (int i = 4; i < 8; ++i) {
            year[j]=date[i];
            j++;
        }
        return year;
    }

    const char *getDate() const {
        return date;
    }

    bool isStatus() const {
        return status;
    }

    int getExpense() const {
        return expense;
    }

    char *getNumber() const {
        return number;
    }
};

class UserProfile{
    char username[31];
    Bill bills[30];
    int n;
public:
    UserProfile(char *username){
        strcpy(this->username,username);
        this->n=0;
        for (int i = 0; i < n; ++i) {
            this->bills[i]=bills[i];
        }
    }



    UserProfile &operator+=(const Bill& newBill){
        for (int i = 0; i < n; ++i) {
            if (strcmp(bills[i].getNumber(), newBill.getNumber()) == 0) {
                throw Exception();
            }
        }

        if(n==0){
            bills[n] = newBill;
            n++;
            return *this;
        }
        bills[n] = newBill;
        n++;
       return *this;
       }

//    UserProfile &operator+=(const Bill& newBill){
//        for (int i = 0; i < n; ++i) {
//            if (strcmp(bills[i].getNumber(), newBill.getNumber()) == 0) {
//                throw Exception();
//            }
//        }
//
//        if(n==0){
//            bills[n] = newBill;
//            n++;
//            return *this;
//        }else {
//            if (strcmp(bills[n-1].getNumber(), newBill.getNumber()) == 0) {
//                throw Exception();
//            }else {
//                bills[n] = newBill;
//                n++;
//                return *this;
//            }
//        }
//       }

    friend ostream &operator<<(ostream &os, const UserProfile &profile) {
        os << "Unpaid bills of user " << profile.username << " are:" <<endl;
        for (int i = 0; i < profile.n; ++i) {


            if(!profile.bills[i].isStatus()) {
                cout<<profile.bills[i];

            }
        }
        return os;

    }

    int totalDue( int month, int year){
        int totalprice=0;
        for (int i = 0; i < n; ++i) {
            const char* date = bills[i].getDate();

            int billmonth = atoi(date);
            int billYear = atoi(date + 3);

            if (month==billmonth && year==billYear){
                totalprice += bills[i].getExpense();
            }
        }
        return totalprice;
    }
};
int main() {
    char number[50], month[8], name[50];
    int price, n;
    bool status;


    int type;
    cin >> type;

    if (type == 1) {
        cout << "-----Test Bill & operator &lt;&lt;-----" << endl ;
        cin >> number >> price >> month >> status;
        Bill b(number, price, month, status);
        cout << b;
    } else if (type == 2) {
        cout << "-----Test Bill & operator == -----" << endl ;
        cin >> number >> price >> month >> status;
        Bill b1(number, price, month, status);
        cin >> number >> price >> month >> status;
        Bill b2(number, price, month, status);
        if (b1 == b2) cout << "Equal" << endl;
        else cout << "Not equal" << endl;

    } else if (type == 3) {
        cout << "-----Test UserProfile & operator += &&lt;&lt; -----" << endl ;
        cin >> name >> n;
        UserProfile up(name);
        for (int i = 0; i < n; i++) {
            cin >> number >> price >> month >> status;
            Bill s(number, price, month, status);
            up += s;
        }
        cout << up;
    } else if (type == 4) {
        cout << "-----Test UserProfile & operator += & totalDue -----" << endl ;
        cin >> name >> n;
        UserProfile up(name);
        for (int i = 0; i < n; i++) {
            cin >> number >> price >> month >> status;
            Bill s(number, price, month, status);
            up += s;
        }
        int m, y;
        cin >> m >> y;
        cout << "Total due for month " << m << " and year " << y << " is:";
        cout << up.totalDue(m, y) << endl;
    } else if (type == 5) {
        cout << "-----Test all -----" << endl ;
        cin >> name >> n;

            UserProfile up(name);
            for (int i = 0; i < n; i++) {
                cin >> number >> price >> month >> status;
                try {
                    Bill s(number, price, month, status);
                    up += s;
                } catch(Exception &e) {
                    e.showMessages();
                }
            }

        cout << up;
        int m, y;
        cin >> m >> y;
        cout << "Total due for month " << m << " and year " << y << " is:";
        cout << up.totalDue(m, y) << endl;

    }

    return 0;
}
