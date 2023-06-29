//
// Created by Hamdi on 5/3/2023.
//
#include <iostream>
#include <cstring>

using namespace std;

// YOUR CODE STARTS HERE
class Vehicle{
protected:
    char brand[101];
    char model[101];
    int yearProd;
    int rentalPrice;
    void copy(const Vehicle &other){
        strcpy(this->brand,other.brand);
        strcpy(this->model,other.model);
        this->yearProd=other.yearProd;
        this->rentalPrice=other.rentalPrice;
    }
public:
    Vehicle(char *brand="",char *model="", int yearProd=0,int rentalPrice=0){
        strcpy(this->brand,brand);
        strcpy(this->model,model);
        this->yearProd=yearProd;
        this->rentalPrice=rentalPrice;
    }
    Vehicle(const Vehicle &other){
        copy(other);
    }
    Vehicle &operator=(const Vehicle &other){
        if(this!=&other){
            copy(other);
        }
        return *this;
    }

    int getRentalPrice() const {
        return rentalPrice;
    }
    void print(){
        cout<<brand<<" - "<<model;
    }
    ~Vehicle(){

    }
};

class PassengerVehicle:public Vehicle{
    int nrOfSeats;
    int nrOfDoors;
public:
    //def!!!
    PassengerVehicle(const Vehicle &other, int nrOfSeats, int nrOfDoors) : Vehicle(other), nrOfSeats(nrOfSeats),
                                                                           nrOfDoors(nrOfDoors) {}

    double getRentPricePerHour(){
        return getRentalPrice()+getRentalPrice()*0.1;
    }
    void print(){
        cout<<brand<<" - "<<model<<" - "<<nrOfSeats<<" - "<<getRentPricePerHour()<<" euros"<<endl;
    }
};

class FreightVehicle: public Vehicle{
    int cargoCapacity;
    int hp;
public:
    FreightVehicle(const Vehicle &other, int cargoCapacity, int hp) : Vehicle(other), cargoCapacity(cargoCapacity),
                                                                      hp(hp) {}

    double getRentPricePerHour(){
        return getRentalPrice()+getRentalPrice()*0.5;
    }
    void print(){
        cout<<brand<<" - "<<model<<" - "<<cargoCapacity<<" - "<<getRentPricePerHour()<<" euros"<<endl;
    }
};


// DO NOT CHANGE THE MAIN FUNCTION
int main() {
    int n;
    cin >> n;
    char manufacturer[100];
    char model[100];
    int productionYear;
    int rentalPricePerHour;

    for (int i = 0; i < n; i++) {
        cin >> manufacturer;
        cin >> model;
        cin >> productionYear;
        cin >> rentalPricePerHour;

        Vehicle v = Vehicle(manufacturer, model, productionYear, rentalPricePerHour);

        if (i % 2) {
            int cargoCapacity;
            int horsePower;
            cin >> cargoCapacity;
            cin >> horsePower;
            FreightVehicle fv = FreightVehicle(v, cargoCapacity, horsePower);
            fv.print();
        } else {
            int numSeats;
            int numDoors;
            cin >> numSeats;
            cin >> numDoors;
            PassengerVehicle pv = PassengerVehicle(v, numSeats, numDoors);
            pv.print();
        }
    }


    return 0;
}