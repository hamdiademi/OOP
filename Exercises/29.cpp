//
// Created by Hamdi on 6/6/2023.
//
#include<iostream>
#include<cstring>
using namespace std;
class Sneakers {
private:
    char model[50];
    int size;
    float price;

public:
    Sneakers(const char *model = "", int size = 38, float price = 1000) : size(size), price(price) {
        strncpy(this->model, model, 49);
        this -> model[49] = 0;
    }

    friend istream &operator>>(istream &in, Sneakers &s) {
        return in >> s.model >> s.size >> s.price;
    }

    friend ostream &operator<<(ostream &out, const Sneakers &s) {
        return out << "Model: " << s.model << " Size: " << s.size << " Price: " << s.price;
    }

    Sneakers &operator+=(float increment) {
        price += increment;
        return *this;
    }

    Sneakers &operator*=(float coefficient) {
        price *= coefficient;
        return *this;
    }

    bool operator==(Sneakers &s) {
        return strcmp(this->model, s.model) == 0 && this->size == s.size;
    }

    char *getModel() {
        return model;
    }

    int getSize() const {
        return size;
    }

    void setSize(int size) {
        this->size = size;
    }

    float getPrice() const {
        return price;
    }

    void setPrice(float price) {
        this->price = price;
    }
};
////////////
class SneakersShop{
protected:
    char storename[50];
    Sneakers* sneakerss;
    int n;
private:
    static int increasement;
    void copy(const SneakersShop &other){
        strcpy(this->storename,other.storename);
        this->n=other.n;
        this->sneakerss=new Sneakers[other.n];
        for (int i = 0; i < n; ++i) {
            this->sneakerss[i]=other.sneakerss[i];
        }
    }
public:
    SneakersShop(char *storename){
        strcpy(this->storename,storename);
        this->n=0;
        this->sneakerss=new Sneakers[n];
    }
    SneakersShop(const SneakersShop &other){
        copy(other);
    }
    SneakersShop &operator=(const SneakersShop &other){
        if (this!=&other){
            delete[]sneakerss;
            copy(other);
        }
        return *this;
    }
    SneakersShop &operator+=(Sneakers &s){
        Sneakers *tmp=new Sneakers[n+1];
        for (int i = 0; i < n; ++i) {
            tmp[i]=sneakerss[i];
        }
        tmp[n]=s;
        n++;
        delete[]sneakerss;
        sneakerss=tmp;
        return *this;
    }
     virtual float checkItemAvailability(char* model, int size){
         for (int i = 0; i < n; ++i) {
             if (strcmp(sneakerss[i].getModel(),model) && sneakerss[i].getSize()==size){
                 return sneakerss[i].getPrice();
             }
         }
         return 0;

    }
    SneakersShop &operator++(){
        for (int i = 0; i < n; ++i) {
            sneakerss[i].setPrice(sneakerss[i].getPrice()+sneakerss[i].getPrice()*((float )increasement/100));///
        }
        return *this;
    }

    friend ostream &operator<<(ostream &os, const SneakersShop &shop) {
        os << "Sneakers shop: " << shop.storename << endl << "List of sneakers:\n";
        if (shop.n==0){
            cout << "EMPTY" << endl;
        } else {
            for (int i=0;i<shop.n;i++){
                cout << i+1 << ". " << shop.sneakerss[i] << endl;
            }
        }
        return os;
    }

    static void setIncreasePercentage(int inc){
        increasement=inc;
    }


};
int SneakersShop::increasement=5;



class OnlineSneakersShop: public SneakersShop{
    char url[51];
    static const int discount;
public:
    OnlineSneakersShop(char *storename, char *url) : SneakersShop(storename) {
        strcpy(this->url,url);
    }

    float checkItemAvailability(char* model, int size){

        for (int i = 0; i < n; ++i) {
            if (strcmp(sneakerss[i].getModel(),model) && sneakerss[i].getSize()==size){
                return sneakerss[i].getPrice()-sneakerss[i].getPrice()*(discount/100);
            }
        }
        return 0;
    }
    friend ostream &operator<<(ostream &os, const OnlineSneakersShop &shop) {
        os << "Online sneakers shop: " << shop.storename << " URL: " << shop.url << endl << "List of sneakers:\n";
        if (shop.n==0){
            cout << "EMPTY" << endl;
        } else {
            for (int i=0;i<shop.n;i++){
                cout << i+1 << ". " << shop.sneakerss[i] << endl;
            }
        }
        return os;
    }

};
int const OnlineSneakersShop::discount=10;

void printShop(SneakersShop *shop) {
    OnlineSneakersShop *casted = dynamic_cast<OnlineSneakersShop *>(shop);
    if (casted) {
        cout << (*casted);
    } else {
        cout << (*shop);
    }
}

int main() {
    int testCase;
    cin >> testCase;
    char name[100];
    char url[100];

    if (testCase == 1) {
        cout << "TESTING CLASS SneakersShop: CONSTRUCTOR AND OPERATOR <<" << endl;
        cin >> name;
        SneakersShop shop(name);
        cout << shop;
    } else if (testCase == 2) {
        cout << "TESTING CLASS OnlineSneakersShop: CONSTRUCTOR AND OPERATOR <<" << endl;
        cin >> name >> url;
        OnlineSneakersShop shop(name, url);
        cout << shop;
    } else if (testCase == 3) {
        cout << "TESTING CLASS SneakersShop, CONSTRUCTOR, += and <<" << endl;
        cin >> name;
        SneakersShop shop(name);
        cout << shop;
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            Sneakers s;
            cin >> s;
            shop += s;
        }
        cout << shop;
    } else if (testCase == 4) {
        cout << "TESTING CLASS OnlineSneakersShop, CONSTRUCTOR, += and <<" << endl;
        cin >> name >> url;
        OnlineSneakersShop shop(name, url);
        cout << shop;
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            Sneakers s;
            cin >> s;
            shop += s;
        }
        cout << shop;
    } else if (testCase == 5) {
        cout << "TESTING METHOD checkItemAvailability" << endl;
        int typeOfShop;
        cin >> typeOfShop >> name; //0 = regular, 1 = online
        SneakersShop *shop;
        if (typeOfShop == 0) {
            shop = new SneakersShop(name);
        } else {
            cin >> url;
            shop = new OnlineSneakersShop(name, url);
        }
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            Sneakers s;
            cin >> s;
            (*shop) += s;
        }
        char model[100];
        int size;
        cin >> model >> size;
        cout << "Price for model " << model << " with size: " << size << " is: "
             << shop->checkItemAvailability(model, size) << endl;
    } else if (testCase == 6) {
        cout << "TESTING OPERATOR ++" << endl;
        int typeOfShop;
        cin >> typeOfShop >> name; //0 = regular, 1 = online
        SneakersShop *shop;
        if (typeOfShop == 0) {
            shop = new SneakersShop(name);
        } else {
            cin >> url;
            shop = new OnlineSneakersShop(name, url);
        }
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            Sneakers s;
            cin >> s;
            (*shop) += s;
        }
        cout << "BEFORE ++ IS CALLED" << endl;
        printShop(shop);
        ++(*shop);
        cout << "AFTER ++ IS CALLED" << endl;
        printShop(shop);
    } else if (testCase == 7) {
        cout << "TESTING OPERATOR ++ AND CHANGE OF STATIC MEMBER" << endl;
        int typeOfShop;
        cin >> typeOfShop >> name; //0 = regular, 1 = online
        SneakersShop *shop;
        if (typeOfShop == 0) {
            shop = new SneakersShop(name);
        } else {
            cin >> url;
            shop = new OnlineSneakersShop(name, url);
        }
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            Sneakers s;
            cin >> s;
            (*shop) += s;
        }

        cout << "BEFORE ++ IS CALLED" << endl;
        printShop(shop);
        ++(*shop);
        cout << "AFTER ++ IS CALLED" << endl;
        printShop(shop);

        cout <<"CHANGING INCREASE PERCENTAGE IN SneakersShop" << endl;
        SneakersShop::setIncreasePercentage(17);

        cout << "BEFORE ++ IS CALLED" << endl;
        printShop(shop);
        ++(*shop);
        cout << "AFTER ++ IS CALLED" << endl;
        printShop(shop);

    }


}