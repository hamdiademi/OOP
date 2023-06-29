// Created by Hamdi on 3/28/2023.

#include <iostream>
#include <cstring>
using namespace std;

class MobilePhone{
private:
    char model[20];
    int modelnum;
    int year;
public:
    MobilePhone(){
        model[0]='\0';
        modelnum=0;
        year=0;

    }
    MobilePhone(const char*model,int modelnum,int year){
        strcpy(this->model,model);
        this->model[19]='\0';
        this->modelnum=modelnum;
        this->year=year;

    }
    ~MobilePhone(){
        //TODO
    }

    void setmodel(const char* _model){
        strcpy(this->model,_model);
        model[0]='\0';
    }
    void setmodelnum(const int _modelnum){
        this->modelnum=_modelnum;
    }
    void setyear(const int _year){
        this->year=_year;
    }

    const char* getmodel(){
        return model;
    }
    int getmodelnum(){
        return modelnum;
    }
    int getyear(){
        return year;
    }



    void print(){
        cout<<model<<" "<<modelnum<<" release year: "<<year<<endl;
    }
};

class Owner{
private:
    char firstname[20];
    char lastname[20];
    MobilePhone mobilePhone;
public:
    Owner(){
        firstname[0]='\0';
        lastname[0]='\0';
    }
    Owner(const char* name,char*surname,MobilePhone& mobilePhone){
        strcpy(this->firstname, name);
        this->firstname[19]='\0';
        strcpy(this->lastname, surname);
        this->lastname[19]='\0';
        this->mobilePhone=mobilePhone;
    }
    ~Owner(){
        //TODO
    }

    void setname(const char* _name){
        strcpy(firstname, _name);
        firstname[19]='\0';
    }
    void setsurname(const char* _surname){
        strcpy(lastname, _surname);
        lastname[19]='\0';
    }
    void setphone(const MobilePhone& phone){
        mobilePhone=phone;
    }

    const char* getname()const{
        return firstname;
    }
    const char* getsurname()const{
        return lastname;
    }
    const MobilePhone& getphone(){
        return mobilePhone;
    }

    void print(){
        cout << firstname << " " << lastname << " has a mobile phone:\n";
        mobilePhone.print();
    }


};

int main() {
    int n;
    cin >> n;

    Owner owners[100];

    for (int i = 0; i < n; i++) {
        char model[100 + 1];
        int modelNumber, yearOfRelease;
        char firstname[100 + 1], lastname[100 + 1];

        cin >> model >> modelNumber >> yearOfRelease;
        cin >> firstname >> lastname;

        MobilePhone phone(model, modelNumber, yearOfRelease);
        Owner owner(firstname, lastname, phone);
        owners[i] = owner;
    }

    for (int i = 0; i < n; i++) {
        owners[i].print();
    }
    return 0;
}
