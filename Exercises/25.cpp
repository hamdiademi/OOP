// Created by Hamdi on 3/29/2023.
//
#include <iostream>
#include <cstring>
using namespace std;

class Tickets{
protected:
    int id[13];
    char event[100];
    float price;
public:
     int static discount;
    Tickets(const int *id= nullptr,const char *event="", float price=0) {
        strcpy(this->event,event);
        this->price=price;
        for (int i = 0; i < 12; ++i) {
            this->id[i]=id[i];
        }
    }
      virtual float computeprice()=0;

    friend ostream &operator<<(ostream &os,  Tickets &tickets) {
        for (int i = 0; i < 12; ++i) {
            os<< tickets.id[i];
        }
        os << "-"<<tickets.event;
        os << "-"<<tickets.computeprice();
        return os;
}
    bool falsifikat(int from, int to){
        int fourdig=0;
        for (int i = 8; i < 12; ++i) {
            fourdig*=10;
            fourdig+=id[i];
        }
       return fourdig>=from&&fourdig<=to;

    }

    static void changeDiscount(int i){
        discount=i;
    }
};
int Tickets::discount=0;



class Online: public Tickets {
    bool premium;
public:
    Online(int *id, char *event, float price, bool premium = false) : Tickets(id, event, price), premium(premium) {}

    float computeprice() {
        float total=price;
        if (premium) {
            total -= price * 0.15;
        }
        if (discount > 0) {
            total -= price * (discount / 100.);
        }
        return total;
    }


    };

    class Offline : public Tickets {
        bool reservation;
    public:
        Offline(int *id, char *event, float price, bool reservation = false) : Tickets(id, event, price),
                                                                               reservation(reservation) {}

        float computeprice() {
            float total=price;
            if (reservation) {
                total += price * 0.1;
            }
            if (discount > 0) {
                total -= price * (discount / 100.);
            }
            return total;
        }

    };

    void vkupenPrihod(Tickets **pTickets, int n, int from, int to) {
        float sum = 0;
        for (int i = 0; i < n; ++i) {
            if (pTickets[i]->falsifikat(from, to)) {
                sum += pTickets[i]->computeprice();
            }
        }
        cout << sum;

    }

// DO NOT CHANGE THE MAIN FUNCTION
    int main() {
        int testCase;
        cin >> testCase;
        int ID[12];
        char event[100];
        float price;
        bool premium;
        bool rezervacija;
        int od, doo;

        if (testCase == 1) {
            cout << "===== TESTING CONSTRUCTORS ======" << endl;
            for (int i = 0; i < 12; i++)
                cin >> ID[i];
            cin >> event;
            cin >> price;
            cin >> premium;
            Online o1(ID, event, price, premium);
            cout << o1 << endl;
            for (int i = 0; i < 12; i++)
                cin >> ID[i];
            cin >> event;
            cin >> price;
            cin >> rezervacija;
            Offline o2(ID, event, price, rezervacija);
            cout << o2 << endl;

        } else if (testCase == 2) {
            cout << "===== TESTING METHOD vkupenPrihod()  ======" << endl;
            int n;
            cin >> n;
            Tickets **t = new Tickets *[n];
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < 12; j++)
                    cin >> ID[j];
                cin >> event;
                cin >> price;

                if (i % 2 == 0) {
                    cin >> premium;
                    t[i] = new Online(ID, event, price, premium);
                } else {
                    cin >> rezervacija;
                    t[i] = new Offline(ID, event, price, rezervacija);
                }
            }
            cin >> od;
            cin >> doo;
            vkupenPrihod(t, n, od, doo);
            for (int i = 0; i < n; ++i) {
                delete t[i];
            }
            delete[] t;
        } else if (testCase == 3) {
            cout << "===== TESTING DISCOUNT STATIC ======" << endl;
            int n;
            cin >> n;
            //cout<<n<<endl;
            Tickets **t = new Tickets *[n];
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < 12; ++j)
                    cin >> ID[j];
                cin >> event;
                //cout<<event<<endl;
                cin >> price;
                //cout<<price<<endl;
                if (i % 2 == 0) {
                    cin >> premium;
                    t[i] = new Online(ID, event, price, premium);
                } else {
                    cin >> rezervacija;
                    //cout<<rezervacija<<endl;
                    t[i] = new Offline(ID, event, price, rezervacija);
                }
            }
            int d;
            cin >> d;
            Tickets::changeDiscount(d);
            for (int i = 0; i < n; ++i)
                cout << *t[i] << endl;

        }
        return 0;
    }
