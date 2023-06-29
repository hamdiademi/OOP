// Created by Hamdi on 3/29/2023.
//
#include <iostream>
#include <cstring>
using namespace std;
//TO DO
class AlcoholicDrink{
protected:
    char name[101];
    char country[101];
    float prcAlcohol;
    float baseprice;
    static int discount;
public:
    AlcoholicDrink(char *name="", char* countryOfOrigin="", float prcAlcohol=0.0, float baseprice=0.0){
        strcpy(this->name,name);
        strcpy(this->country, countryOfOrigin);
        this->prcAlcohol=prcAlcohol;
        this->baseprice=baseprice;
    }
    virtual double computeprice()=0;

    static void changeDiscount(int d) {
        discount = d;
    }

    static void total(AlcoholicDrink** ad, int n) {
        double totalPrice = 0.0;
        double totalPriceWithDiscount = 0.0;

        for (int i = 0; i < n; i++) {
            totalPrice += ad[i]->computeprice();
            totalPriceWithDiscount += ad[i]->computeprice() * (1 - (discount / 100.0));
        }

        cout << "Total price: " << totalPrice << endl;
        cout << "Total price with discount: " << totalPriceWithDiscount << endl;
    }
};
int AlcoholicDrink::discount = 5;

//class Beer
class Beer : public AlcoholicDrink {
    bool ingredients;
public:
    Beer( float prcAlcohol = 0,char *name = "", char *country = "", float baseprice = 0.0,bool ingredients = false): AlcoholicDrink(name, country, prcAlcohol, baseprice), ingredients(ingredients) {};

     double computeprice(){
        double price = baseprice;
        if(strcmp(country,"Germany")==0){
           price+=baseprice*0.5;
        }else if(ingredients==0){
            price+=baseprice*0.10;
        }
        return price;
    }

    friend ostream &operator<<(ostream &out,Beer &beer) {
        out << beer.name << " " << beer.country << " " << beer.computeprice();
        return out;
    }

        bool operator<(const Beer &rhs) const {
            if ( this->baseprice < rhs.baseprice) {
                return true;
            }
            if ( this->baseprice > rhs.baseprice) {
                return false;
            }
            return baseprice < rhs.baseprice;
        }
};

//class wine
class Wine: public AlcoholicDrink{
    int yearOfManu;
    char grapesType[21];
public:
    Wine( float prcAlcohol = 0,char *name = "", char *country = "", float baseprice = 0.0,int yearOfManu=0, char *grapesType=""): AlcoholicDrink(name, country, prcAlcohol, baseprice), yearOfManu(yearOfManu) {
        strcpy(this->grapesType,grapesType);
    };
    double computeprice() {
        double price = baseprice;
        if(strcmp(country,"Italy")==0){
            price*=0.5;
        }else if(yearOfManu<2005){
            price+= baseprice*0.15;
        }
        return price;
    }

    friend ostream &operator<<(ostream &out,Wine &wine) {
        out << wine.name << " " << wine.country<<" "<< wine.computeprice();
        return out;
    }

    bool operator<(const Wine &rhs) const {
        if ( this->baseprice < rhs.baseprice)
            return true;
        if ( this->baseprice > rhs.baseprice)
            return false;
        return baseprice < rhs.baseprice;
    }
};


    void lowestPrice(AlcoholicDrink ** a, int n){
        float minPrice=a[0]->computeprice();
        int minIndex = -1;

        for (int i = 0; i < n; i++) {

            float price = a[i]->computeprice();
            if (price < minPrice) {
                minPrice = price;
                minIndex = i;
            }
        }

        if (minIndex != -1) {
            Beer* beer = dynamic_cast<Beer*>(a[minIndex]);
            Wine* wine = dynamic_cast<Wine*>(a[minIndex]);

            if (beer != nullptr) {
                cout << *beer << endl;
            } else if (wine != nullptr) {
                cout << *wine << endl;
            }
        }
    }

//DO NOT CHANGE MAIN
int main(){

    int testCase;
    cin >> testCase;
    float p;
    char name[100];
    char country[100];
    float price;
    bool mainI;
    int year;
    char grape [20];
    if(testCase == 1) {
        cout << "===== TESTING CONSTRUCTORS ======" << endl;
        cin >> p;
        cin >> name;
        cin >> country;
        cin >> price;
        cin >> mainI;
        Beer b(p, name, country, price, mainI);
        cout << b << endl;
        cin >> p;
        cin >> name;
        cin >> country;
        cin >> price;
        cin >> year;
        cin >> grape;
        Wine w(p, name, country, price, year, grape);
        cout << w << endl;

    } else if(testCase == 2) {
        cout << "===== TESTING LOWEST PRICE ======" << endl;
        int n;
        cin >> n;
        AlcoholicDrink** ad = new AlcoholicDrink*[n];
        for(int i = 0; i < n; ++i) {
            cin >> p;
            cin >> name;
            cin >> country;
            cin >> price;

            if(i % 2 == 1){
                cin >> mainI;
                ad[i] = new Beer(p, name, country, price, mainI);
            }
            else {
                cin >> year;
                cin >> grape;
                ad[i] = new Wine(p, name, country, price, year, grape);
            }
        }

        lowestPrice(ad, n);
        for(int i = 0; i < n; ++i) {
            delete ad[i];
        }
        delete [] ad;
    }
     else if(testCase == 3) {
        cout << "===== TESTING DISCOUNT STATIC ======" << endl;
        int n;
        cin >> n;
        AlcoholicDrink** ad = new AlcoholicDrink*[n];
        for(int i = 0; i < n; ++i) {
            cin >> p;
            cin >> name;
            cin >> country;
            cin >> price;
            if(i % 2 == 1){
                cin >> mainI;
                ad[i] = new Beer(p, name, country, price, mainI);
            }
            else {
                cin >> year;
                cin >> grape;
                ad[i] = new Wine(p, name, country, price, year, grape);
            }
        }
        AlcoholicDrink::total(ad, n);
        int d;
        cin >> d;
        AlcoholicDrink::changeDiscount(d);
        AlcoholicDrink::total(ad, n);
        for(int i = 0; i < n; ++i) {
            delete ad[i];
        }
        delete [] ad;
    }

    return 0;
}