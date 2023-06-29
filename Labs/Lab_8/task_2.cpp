//
// Created by Hamdi on 5/11/2023.
//
#include <iostream>
#include <cstring>
using namespace std;

class FoodItem{
protected:
    char*type;
    int num;
public:
    FoodItem(char*type,int num){
        this->type=new char[strlen(type)+1];
        strcpy(this->type,type);
        this->num=num;
    }

    ~FoodItem()
    {
        delete[] type;
    }

    virtual int getPrice()=0;
    virtual int getTime()=0;

    char *getType() const {
        return type;
    }

};

class Pizza : public FoodItem{
    char* dough;
public:
    Pizza(char *type, int num, char *dough): FoodItem(type,num){
        this->dough=new char[strlen(dough)+1];
        strcpy(this->dough,dough);
    }
    ~Pizza(){
        delete[] dough;
    }
     int getPrice() {

         if (strcmp(this->dough, "wholeWheat") == 0) {
             return 250 * num;
         } else {
             return 350 * num;
         }
     }


     int getTime(){
         return 25;
    }

};

class Steak : public FoodItem{
    bool cooked;
public:
    Steak(char *type, int num, bool cooked) : FoodItem(type, num), cooked(cooked) {}

    int getPrice(){
        return 1300*num;

    }

    int getTime(){
        if(cooked){
           return 20;
        } else
        {
            return 15;
        }

    }

};

//FoodItem *getMaxFoodItem(FoodItem *pItem[], int n){
//    FoodItem* item = pItem[0];
//    int maxPrice = pItem[0]->getPrice();
//
//    for(int i = 0; i < n; i++) {
//        if(maxPrice < pItem[i]->getPrice()) {
//            maxPrice = pItem[i]->getPrice();
//            item = pItem[i];
//        }
//    }
//
//    return item;
//}
FoodItem *getMaxFoodItem(FoodItem *pItem[], int n){

    int maxPrice = 0;
    int j=-1;

    for(int i = 0; i < n; i++) {
        if(maxPrice < pItem[i]->getPrice()) {
            maxPrice = pItem[i]->getPrice();
            j=i;
        }
    }

    return pItem[j];
}

int main() {
    FoodItem *p;
    int n;
    cin>>n;

    char type[30];
    char dough[30];
    bool cooked;
    int size;

    FoodItem *items[n];

    for (int i = 0; i <n; ++i) {
        cin>>type;
        cin>>size;


        if(strcmp(type, "pizza")==0 ) {
            cin>>dough;
            items[i] = new Pizza(type, size, dough);
        }else{
            cin>>cooked;
            items[i] = new Steak(type, size, cooked);
        }


    }

    FoodItem *it = getMaxFoodItem(items, n);
    cout<<"Type: "<<it->getType()<<endl;
    cout<<"The max price is: "<<it->getPrice()<<endl;
    cout<<"Time to cook: "<<it->getTime();
    return 0;
}

