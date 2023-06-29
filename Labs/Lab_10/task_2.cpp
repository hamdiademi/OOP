//
// Created by Hamdi on 5/23/2023.
//
#include<iostream>
#include<cstring>
using namespace std;
class InvalidTimeException{
public:
    void showMessage(){
        cout<<"The time is not valid"<<endl;
    }
};

class Race{
protected:
    char city [51];
    int year;
    int month;
    float bestTime;
    float length;

public:
   Race(char *city="", int year=0, int month=0, float bestTime=0.0, float length=0.0) : year(year), month(month),
                                                                          bestTime(bestTime), length(length) {
        strcpy(this->city,city);
    }

    virtual float heaviness(){
        return bestTime/length;
    }

    friend ostream &operator<<(ostream &os, Race &race) {
        os <<  race.city<<" " << race.month<<"." << race.year<< " " <<race.heaviness()<<endl;
        return os;
    }


};

class CarRace: public Race{

    float* bestTimes;
    int n;
    int numOfLaps;
    void copy(const CarRace &other){
        strcpy(this->city,city);
        this->year=other.year;
        this->month=other.month;
        this->bestTime=other.bestTime;
        this->length=other.length;
        this->numOfLaps=other.numOfLaps;
        this->bestTimes= new float[other.n];
        this->n=other.n;
        for (int i = 0; i < n; ++i) {
            this->bestTimes[i]=other.bestTimes[i];
        }
    }

public:
    static float CAR_COEF;
    CarRace(){

    }
    CarRace(char *city, int year, int month, float bestTime, float length, const float *bestTimes= nullptr, int n=0, int numOfLaps=0)
            : Race(city, year, month, bestTime, length), numOfLaps(numOfLaps) {
        this->n=n;
        this->bestTimes= new float[n];
        for (int i = 0; i < n; ++i) {
            this->bestTimes[i]=bestTimes[i];
        }
    }
    CarRace(const CarRace &other): Race(other){
        copy(other);
    }
    CarRace &operator=(const CarRace &other){
        if(this!=&other){
            delete[]bestTimes;
            copy(other);
        }
        return *this;
    }
    ~CarRace(){
        delete []bestTimes;

    }


    CarRace &operator+=(float newTime ){
        if (newTime<10){
            throw InvalidTimeException();
        }
        float *tmp= new float[n];

        for (int i = 0; i < n; ++i) {
            tmp[i]=this->bestTimes[i];
        }
        tmp[n++]=newTime;
        delete[]bestTimes;
        bestTimes=tmp;

        return *this;

    }


    float averageBestTime()const{
        float sum=0;
        for (int i = 0; i < n; ++i) {
            sum+=this->bestTimes[i];
        }
        return sum/(float)n;
    }

    float heaviness(){
        float total = Race::heaviness()+(averageBestTime()*CAR_COEF);
        if (numOfLaps>15){
            return  (total)*1.1;
        } else{
            return total;
        }


    }


   void setNumberLaps(int num) {
        numOfLaps = num;
    }


    static void setKoeficient(float carCoef){
        CAR_COEF = carCoef;
    }

};
float CarRace::CAR_COEF=0.3;


int main(){
    int testCase;
    cin >> testCase;
    char city[50];
    int year;
    int month;
    float bestTime;
    float length;
    float bestTimes[50];
    int n;
    int m;
    int izbor;
    int numberLaps;

    if (testCase == 1){
        cout << "===== Testing the classes ======" << endl;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin>>length;
        Race t(city, year, month, bestTime, length);
        cout<<t;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin>>length;
        cin>>numberLaps;
        cin>>n;
        for (int j = 0; j < n; j++)
            cin >> bestTimes[j];
        CarRace mgt(city, year, month, bestTime, length, bestTimes, n, numberLaps);
        cout << mgt;
        CarRace mgt2;
    }
    if (testCase == 2){
        cout << "===== Testing the operator += ======" << endl;
        Race **niza;
        cin >> m;
        niza = new Race *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> city;
            cin >> year;
            cin >> month;
            cin >> bestTime;
            cin >>length;
            if (izbor == 1){
                niza[i] = new Race(city, year, month, bestTime, length);
            }
            else{
                cin>>numberLaps;
                cin>>n;
                for (int j = 0; j < n; j++)
                    cin >> bestTimes[j];
                niza[i] = new CarRace(city, year, month, bestTime, length, bestTimes, n, numberLaps);
            }
        }
        // pecatenje na site Trki
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje novo najdobro vreme za prvata CarRace
        float best;
        cin >> best;
        int flag = 1;
        for (int i = 0; i < m; i++){
            CarRace* nn = dynamic_cast<CarRace*>(niza[i]);
            if (nn != 0){
                flag = 0;
                    (*nn) += best;
                break;
            }
        }


        // pecatenje na site Trki
        cout << "\nList of all races::\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 3){
        cout << "===== Testing the exceptions ======" << endl;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin>>length;
        cin>>numberLaps;
        CarRace mgt(city, year, month, bestTime, length);
        mgt.setNumberLaps(numberLaps);
        float vreme1,vreme2;
        cin>>vreme1>>vreme2;
        try{
            mgt+=vreme1;
            mgt+=vreme2;
        }
        catch(InvalidTimeException e)
        {
            e.showMessage();
        }
        cout<<mgt;
    }

    if (testCase == 5){
        cout << "===== Testing static members ======" << endl;
        Race **niza;
        cin >> m;
        niza = new Race *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> city;
            cin >> year;
            cin >> month;
            cin >> bestTime;
            cin >>length;
            if (izbor == 1){
                niza[i] = new Race(city, year, month, bestTime, length);
            }
            else{
                cin>>numberLaps;
                cin>>n;
                for (int j = 0; j < n; j++)
                    cin >> bestTimes[j];
                niza[i] = new CarRace(city, year, month, bestTime, length, bestTimes, n, numberLaps);
            }
        }
        // pecatenje na site Trki
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        CarRace::setKoeficient(0.7);
        // pecatenje na site Trki
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }



    return 0;
}