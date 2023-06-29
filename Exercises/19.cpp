// Created by Hamdi on 3/29/2023.
//
#include <iostream>
#include <cstring>
using namespace std;

class Parcel{
protected:
    int id;

public:
    static int Price;
    Parcel(int id=0) : id(id) {
    }

    static void setProcessingPrice(int price){
        Price = price;
    }

    int getId() const {
        return id;
    }


};
int Parcel::Price=150;



class Envelope: public Parcel{
    char receiver[51];
    int width;
    int heigh;
public:
    Envelope(int id=0, char *receiver="", int width=0, int heigh=0) : Parcel(id), width(width), heigh(heigh) {
        strcpy(this->receiver,receiver);
    }

    const char *getReceiver() const {
        return receiver;
    }

     int price() {

        return Price+heigh*width*0.3;
    }

};

class PostOffice{
    Envelope envelops[100];
    int n;
public:

    PostOffice() {
        this->n=0;
    }

    int sendEnvelope(int id, char* receiver, int length, int width){
        envelops[n]={id,receiver,width,length};
        n++;
        return envelops[n-1].price();
    }

    void printEnvelopsTo(char* receiver){
        cout<<"For "<<receiver<<" are envelops with ids: ";
        for (int i = 0; i < n; ++i) {
            if (strcmp(receiver,envelops[i].getReceiver())==0){
                cout<<envelops[i].getId()<<" ";
            }

        }
        cout<<endl;
    }
};


int main() {

    int type;
    int n;
    int price;
    int id;
    int height, width;
    char receiver[50];

    PostOffice p;

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> type;
        if (type == 1) { // send envelope
            cin >> id >> receiver >> width >> height;
            cout << "The price of sending envelope with id " << id << " is:" << p.sendEnvelope(id, receiver, width, height) << endl;
        } else if (type == 2) { // print envelops to
            cin >> receiver;
            p.printEnvelopsTo(receiver);
        } else if (type == 3) { // set processing price
            cin >> price;
            Parcel::setProcessingPrice(price);
        } else if (type == 4) { // Parcel
            cin >> id;
            Parcel p1(id);
            cout << "Parcel with id [" << p1.getId() << "] is created" << endl;
        } else {// Envelope
            cin >> id >> receiver >> width >> height;
            Envelope p2(id, receiver, width, height);
            cout << "Price of sending envelope with ID: " << p2.getId() << " To: " << p2.getReceiver() << " is: " << p2.price() << endl;
        }
    }
    return 0;
}
