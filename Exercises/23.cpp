// Created by Hamdi on 3/29/2023.
//
#include <iostream>
#include <cstring>
using namespace std;

// Your code here!!!


class MonthlyInvoice{
protected:
    char userName[101];
    int userNumber;
    float basic_price;
    int spent_gigabytes;
public:
    MonthlyInvoice(char *userName="", int userNumber=0, float basicPrice=0, int spentGigabytes=0) :userNumber(userNumber),basic_price(basicPrice),spent_gigabytes(spentGigabytes) {
        strcpy(this->userName,userName);
    }
    virtual float total_price()=0;

    friend ostream &operator<<(ostream &os, const MonthlyInvoice &invoice) {
        os  << invoice.userNumber << " - " << invoice.userName << ", "<< invoice.basic_price<<endl;
        return os;
    }
};
///1
class BusinessInvoice: public MonthlyInvoice{
    bool optical;
    int free_gigabytes;
public:
    BusinessInvoice(char *userName, int userNumber, float basicPrice, int spentGigabytes, bool optical = false, int freeGigabytes=0):
    MonthlyInvoice(userName, userNumber, basicPrice, spentGigabytes),optical(optical), free_gigabytes(freeGigabytes){}

    int overfreeGB()const{
        if (spent_gigabytes>free_gigabytes){
            return spent_gigabytes-free_gigabytes;
        }
        else return 0;
    }


    float total_price()override{ //may be error in free gigabytes and adding 50% to basic price or to total price???
        float total=basic_price;
        if (optical){
            total+=basic_price*0.5;
        }
        total=total+(float )overfreeGB()*100.0;

          return total;
    }
    BusinessInvoice &operator++(int){
        BusinessInvoice tmp=*this;
        ++spent_gigabytes;
        return tmp;
    }

    friend ostream &operator<<(ostream &os, const BusinessInvoice &invoice) {
        os << static_cast<const MonthlyInvoice &>(invoice);
        if (invoice.optical){
            os<<"optical link, ";
        } else{os<<"cable link, ";}
        os<<invoice.overfreeGB()<<endl;
        return os;
    }
};


///2
class PrivateInvoice: public MonthlyInvoice{
    char id[14];
    int* movies;
    int n;
    void copy(const PrivateInvoice &other){
        strcpy(this->userName,other.userName);
        this->userNumber=other.userNumber;
        this->basic_price=other.basic_price;
        this->spent_gigabytes=other.spent_gigabytes;
        strcpy(this->id,other.id);
        this->n=other.n;
        this->movies=new int[other.n];
        for (int i = 0; i < n; ++i) {
            this->movies[i]=other.movies[i];
        }
    }
public:
    PrivateInvoice(char *userName, int userNumber, float basicPrice, int spentGigabytes) : MonthlyInvoice(userName, userNumber, basicPrice, spentGigabytes) {
        this->n=0;
        this->movies=new int[n];
    }
    PrivateInvoice(const PrivateInvoice &other){
        copy(other);
    }
    PrivateInvoice &operator=(const PrivateInvoice &other){
        if (this!=&other){
            delete[]movies;
            copy(other);
        }
        return *this;
    }

    int gb_watched_movies()const{
        int sum=0;
        for (int i = 0; i < n; ++i) {
            sum+=movies[i];
        }
        return sum;
    }
    float total_price() override{// may be error at gb watched movies???
        float total;
        total=basic_price+spent_gigabytes*50.0+(float)gb_watched_movies()*10;
        return total;
    }

    int operator[](int i){
        if (i>n){
            return -1;
        }else{
            return movies[i];
        }
    }

    PrivateInvoice &operator+=(int &m){
        int *tmp=new int[n+1];
        for (int i = 0; i < n; ++i) {
            tmp[i]=movies[i];
        }
        tmp[n]=m;
        n++;
        delete[]movies;
        movies=tmp;
        return *this;
    }

    PrivateInvoice &operator++(int){
        PrivateInvoice copy(*this);
        ++spent_gigabytes;
        return copy;
    }
    int getMoviesNo() {
        return n;
    }

    friend ostream &operator<<(ostream &os, const PrivateInvoice &invoice) {
        os << static_cast<const MonthlyInvoice &>(invoice);
        os<< invoice.spent_gigabytes<<endl;
        os<<invoice.n<<", "<<invoice.gb_watched_movies()<<endl;
        return os;
    }
};

MonthlyInvoice &biggestInvoice(MonthlyInvoice **pInvoice, int n) {
    float highest;
    int index;
    for (int i = 0; i < n; ++i) {
        if (pInvoice[i]->total_price()>highest){
            highest=pInvoice[i]->total_price();
            index=i;
        }
    }
    return *pInvoice[index];
}

// Testing the program!!!
int main(){
    int test_case;
    char username[101];
    int userNumber;
    float basic_price;
    int spent_gigabytes;
    bool optical;
    int free_gigabytes;
    int num_inc;

    cin>>test_case;
    if (test_case == 1){
        // Test Case Business Invoice - Constructor, operator <<
        cin>>username>>userNumber>>basic_price>>spent_gigabytes;
        cin>>optical>>free_gigabytes;
        BusinessInvoice bi(username, userNumber,basic_price, spent_gigabytes, optical, free_gigabytes);
        cout<<"BusinessInvoice Created:\n";
        cout<<bi;
    }
    else if (test_case == 2) {
        // Test Case Business Invoice - Constructor, operators <<, ++
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        cin >> optical >> free_gigabytes;
        BusinessInvoice bi(username, userNumber, basic_price, spent_gigabytes, optical, free_gigabytes);
        cout << "BusinessInvoice:\n";
        cout << bi;
        cout << "testing operator++\n";

        // Additional spent gigabytes
        cin >> num_inc;
        for (int i=0; i<num_inc; ++i) {
            bi++;
        }
        cout << bi;
    }
    else if (test_case == 3) {
        // Test Case Business Invoice - Constructor, total_price, operators <<, ++,
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        cin >> optical >> free_gigabytes;
        BusinessInvoice bi(username, userNumber, basic_price, spent_gigabytes, optical, free_gigabytes);
        cout << "Testing total_price()\n";
        cout << bi;
        cout<<bi.total_price()<<endl;
        bi++;
        cout << bi;
        cout<<bi.total_price()<<endl;
    }
    else if (test_case == 4){
        // Test Case Private Invoice - Constructor, operator <<
        cin>>username>>userNumber>>basic_price>>spent_gigabytes;

        PrivateInvoice pi(username, userNumber,basic_price, spent_gigabytes);
        cout<<"Private Invoice Created:\n";
        cout<<pi;
    }
    else if (test_case == 5) {
        // Test Case Private Invoice - Constructor, operators <<, ++
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        PrivateInvoice pi(username, userNumber,basic_price, spent_gigabytes);
        cin >> num_inc;
        for (int i=0; i<num_inc; ++i) {
            pi++;
        }
        cout << pi;
    }
    else if (test_case == 6) {
        // Test Case Private Invoice - Constructor, operators <<, +=
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        PrivateInvoice pi(username, userNumber,basic_price, spent_gigabytes);
        cin >> num_inc;
        int film_length;
        for (int i=0; i<num_inc; ++i) {
            cin>>film_length;
            pi+=film_length;
        }
        cout << pi;
    }
    else if (test_case == 7) {
        // Test Case Private Invoice - Constructor, operators <<, +=, []
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        PrivateInvoice pi(username, userNumber,basic_price, spent_gigabytes);
        cin >> num_inc;
        int film_length;
        for (int i=0; i<num_inc; ++i) {
            cin>>film_length;
            pi+=film_length;
        }
        cout << pi;
        cout << "Movie sizes: [";
        for (int i=0; i<pi.getMoviesNo(); ++i){
            cout << pi[i] << " ";
        }
        cout << "]" << endl;
    }
    else if (test_case == 8) {
        // Test Case Private Invoice - Constructor, total_price
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        PrivateInvoice pi(username, userNumber,basic_price, spent_gigabytes);
        cout<<pi;
        cout<< pi.total_price() <<endl;
        cin >> num_inc;
        int film_length;
        for (int i=0; i<num_inc; ++i) {
            cin>>film_length;
            pi+=film_length;
        }
        cin >> num_inc;
        for (int i=0; i<num_inc; ++i){
            pi++;
        }
        cout << pi;
        cout<< pi.total_price() <<endl;
    }
    else if (test_case == 9) {
        // Test Case

        int num_invoices;
        int invoice_type;

        cin >>num_invoices;
        MonthlyInvoice ** mi = new MonthlyInvoice*[num_invoices];
        for (int j=0;j<num_invoices; ++j) {

            cin >> invoice_type;
            if (invoice_type == 1){
                cin >> username >> userNumber >> basic_price >> spent_gigabytes;
                cin >> optical >> free_gigabytes;
                BusinessInvoice * bip;
                bip = new BusinessInvoice(username, userNumber, basic_price, spent_gigabytes, optical, free_gigabytes);
                cin >> num_inc;
                for (int i=0; i<num_inc; ++i) {
                    (*(bip))++;
                }
                cout << *(bip);
                cout<<bip->total_price()<<endl;

                mi[j] = bip;
            }
            if (invoice_type == 2) {
                cin >> username >> userNumber >> basic_price >> spent_gigabytes;
                PrivateInvoice* pip = new PrivateInvoice(username, userNumber, basic_price, spent_gigabytes);
                cin >> num_inc;
                int film_length;
                for (int i = 0; i < num_inc; ++i) {
                    cin >> film_length;
                    (*pip) += film_length;
                }
                cin >> num_inc;
                for (int i = 0; i < num_inc; ++i) {
                    (*pip)++;
                }
                cout << (*pip);
                cout << pip->total_price() << endl;
                mi[j] = pip;
            }
        }

        cout << "The biggest invoice is:\n";
        MonthlyInvoice& invoice = biggestInvoice(mi, num_invoices);

        MonthlyInvoice* m = &invoice;
        BusinessInvoice* bip;
        PrivateInvoice* pip;
        if (dynamic_cast<BusinessInvoice *> (m)){
            bip = dynamic_cast<BusinessInvoice *> (m);
            cout<<*bip << bip->total_price();
        }
        if (dynamic_cast<PrivateInvoice *> (m)){
            pip = dynamic_cast<PrivateInvoice *> (m);
            cout<<*pip << pip->total_price();
        }

    }
    return 0;
}