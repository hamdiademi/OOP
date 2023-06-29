// Created by Hamdi on 3/29/2023.
//
#include <iostream>
#include <cstring>
using namespace std;

//
class Cinema{
protected:
    char name[21];
    int no;
    float ticketPrice;
    static float discount;
public:

    Cinema(const char *name="", int no=0, float ticketPrice=0) :  no(no), ticketPrice(ticketPrice) {
        strcpy(this->name,name);
    }

    const char *getname() const {
        return name;
    }

    static void setStudentDiscount(float dis){
        discount = dis;
    }

    static float getStudentDiscount() {
        return discount;
    }

    virtual float price(bool isStudent){
        if (isStudent){
            return ticketPrice * (1 - discount);///
        } else{
            return ticketPrice;
        }

    }

};
float Cinema::discount=0.17;



class ThreeDCinema: public Cinema{
    char* movieName;
    float hours;
    bool premiere;
public:
    ThreeDCinema(char *name, int no, float ticketPrice, char *movieName= nullptr, float hours=0, bool premiere= false) : Cinema(name, no,ticketPrice),hours(hours),premiere(premiere) {
        this->movieName=new char[strlen(movieName)+1];
        strcpy(this->movieName,movieName);
    }
    float price(bool isStudent){
        float total= Cinema::price(isStudent);
       if(hours>3.0){

           total+=70;

       } else if (hours>2.5){

           total+=50;

       } if (premiere){
            total+=60;
        }
        return total;
    }


    bool getpremiere() const {
        return premiere;
    }

};

///GLOBAL
void cheapestCinema(Cinema ** halls, int n,bool isStudent)
{
    int ThreeD=0;
    float min =halls[0]->price(isStudent);
    int minIndex =0;
    for(int i=0;i<n;i++)
    {
        if(halls[i]->price(isStudent)<min)
        {
            min = halls[i]->price(isStudent);
            minIndex = i;
        }

        if(dynamic_cast<ThreeDCinema *>(halls[i])!=0)
        {
            ThreeD++;
        }
    }
    cout<<"Cheapest movie hall: ";
    cout<<halls[minIndex]->getname()<<" "<<halls[minIndex]->price(isStudent)<<endl;
    cout<<"3D cinema halls: "<<ThreeD<<" from total "<<n<<endl;
}

bool searchCinema(Cinema ** halls,int n, const char * name, bool premiere, bool isStudent)
{
    bool found = false;

    for(int i=0;i<n;i++)
    {
        ThreeDCinema * s = dynamic_cast<ThreeDCinema *>(halls[i]);
        if(premiere && strcmp(halls[i]->getname(),name)==0 && s!=0 && s->getpremiere()==true)
        {
            found = true;
            cout<<halls[i]->getname()<<" "<<halls[i]->price(isStudent)<<endl;

        }
        else
        {
            if(strcmp(halls[i]->getname(),name)==0)
            {
                found = true;
                cout<<halls[i]->getname()<<" "<<halls[i]->price(isStudent)<<endl;
            }
        }
    }

    return found;
}


int main(){

    int tip,n;
    char name[100], movieName[40];
    int no;
    bool premiere;
    float ticketPrice;
    float hours;
    bool isStudent;

    cin>>tip;
    if (tip==1){//Cinema
        cin>>name>>no>>ticketPrice;
        Cinema k1(name,no,ticketPrice);
        cout<<"Cinema created with titleM: "<<k1.getname()<<endl;
    }
    else if (tip==2){//price - Cinema
        cin>>name>>no>>ticketPrice>>isStudent;
        Cinema k1(name,no,ticketPrice);
        cout<<"Initial price for the cinema with titleM "<<k1.getname()<< " is: " <<k1.price(isStudent)<<endl;
    }
    else if (tip==3){//3D Cinema
        cin>>name>>no>>ticketPrice>>movieName>>hours>>premiere;
        ThreeDCinema s(name,no,ticketPrice,movieName,hours,premiere);
        cout<<"Cinema created with titleM "<<s.getname()<<" and discount "<<s.getStudentDiscount()<<endl;
    }
    else if (tip==4){//price - 3DCinema
        cin>>name>>no>>ticketPrice>>movieName>>hours>>premiere>>isStudent;
        ThreeDCinema s(name,no,ticketPrice,movieName,hours,premiere);
        cout<<"The price for the cinema "<<s.getname()<<" is: "<<s.price(isStudent)<<endl;
    }
    else if (tip==5) {//cheapest Cinema
        Cinema ** halls = new Cinema *[5];
        int n;
        halls[0] = new Cinema("Cineplexx1",1,350);
        halls[1] = new ThreeDCinema("Milenium3D",44,285,"Shrek",2.5,false);
        halls[2] = new ThreeDCinema("Vardar",12,333,"StarWars",4,true);
        halls[2] = new ThreeDCinema("Home",44,299,"Godfather",5,false);
        halls[3] = new Cinema("Cineplexx2",2,333);
        halls[4] = new ThreeDCinema("Cinedays",1,310,"ManInBlack",5,true);
        cheapestCinema(halls,5,true);
    }
    else if (tip==6){//search
        Cinema ** halls = new Cinema *[5];
        halls[0] = new Cinema("Cineplexx1",1,350);
        halls[1] = new ThreeDCinema("Milenium3D",44,285,"Shrek",2.5,false);
        halls[2] = new ThreeDCinema("Vardar",12,333,"StarWars",4,true);
        halls[3] = new Cinema("Cineplexx2",2,333);
        halls[4] = new ThreeDCinema("Cinedays",1,310,"ManInBlack",5,true);

        if(searchCinema(halls,5, "Milenium3D",true,true))
            cout<<"Found"<<endl;
        else cout<<"Not found"<<endl;

        if(searchCinema(halls,5, "CinePlexx1",false,false))
            cout<<"Found"<<endl;
        else cout<<"Not found"<<endl;

    }
    else if (tip==7){//change price
        Cinema ** halls = new Cinema *[5];
        halls[0] = new Cinema("Cineplexx1",1,350);
        halls[1] = new ThreeDCinema("Milenium3D",44,285,"Shrek",2.5,false);
        halls[2] = new ThreeDCinema("Vardar",12,333,"StarWars",4,true);
        halls[2] = new ThreeDCinema("Domasno",44,299,"Godfather",5,false);
        halls[3] = new Cinema("Cineplexx2",2,333);
        halls[4] = new ThreeDCinema("Cinedays",1,310,"ManInBlack",5,true);
        halls[2] -> setStudentDiscount(0.9);
        cheapestCinema(halls,4,true);
    }

    return 0;
}

