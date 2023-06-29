// Created by Hamdi on 3/29/2023.
//
#include <iostream>
#include <cstring>
using namespace std;
class Exception{
public:
    void message(){
        cout<<"Invalid Time"<<endl;
    }
};
class Race{
protected:
    char city[50];
    int year;
    int month;
    float besttime;
    float km;
public:
    Race(char *city="", int year=0, int month=0, float besttime=0, float km=0) :  year(year), month(month),
                                                                      besttime(besttime), km(km) {
        strcpy(this->city,city);
    }
    virtual float complexity()const{
        return besttime/km;
    }

    friend ostream &operator<<(ostream &os, const Race &race) {
        os << race.city << " " << race.month<<"."<< race.year << " " << race.complexity()<<endl;
        return os;
    }
};

class MotoGPRace: public Race{
    float* bestTimes;
    int n;
    int numOfLaps;
    static float koeficient;
public:

    MotoGPRace(){}
    MotoGPRace(char *city, int year, int month, float besttime, float km, float *bestTimes= nullptr, int n=0, int numOfLaps=0)
            : Race(city, year, month, besttime, km), n(n), numOfLaps(numOfLaps) {
        this->bestTimes= new float[n];
        for (int i = 0; i < n; ++i) {
            this->bestTimes[i]=bestTimes[i];
        }
    }

    void setNumberLaps(int numberLaps){
        numOfLaps=numberLaps;
    }

    int getNumberLaps() const{
        return numOfLaps;
    }

    static void setK(float koef){
        koeficient=koef;
    }

    float complexity() const override {

        float sum=0;
        for (int i = 0; i < n; ++i) {
            sum += bestTimes[i];
        }
        float avg = sum / (float)n * koeficient;

        float complexity = avg + Race::complexity();

        if (numOfLaps > 22){
            complexity *= 1.2;
        }
        return complexity;
    }

    MotoGPRace operator+=(float time){
        if(time<9.5){
            throw Exception();
        }
            float *tmp = new float[n + 1];
            for (int i = 0; i < n; ++i) {
                tmp[i] = bestTimes[i];
            }
            tmp[n] = time;
            n++;
            delete[]bestTimes;
            bestTimes = tmp;
            return *this;

    }

    MotoGPRace operator++(int){
        MotoGPRace copy = *this;
        ++numOfLaps;
        return copy;
    }


};
float MotoGPRace::koeficient=0.4;



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
    int choice;
    int numberLaps;

    if (testCase == 1){
        cout << "===== Testing - classes ======" << endl;
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
        MotoGPRace mgt(city, year, month, bestTime, length,bestTimes, n, numberLaps);
        cout << mgt;
        MotoGPRace mgt2;
    }
    if (testCase == 2){
        cout << "===== Testing - operatorot += ======" << endl;
        Race **rArray;
        cin >> m;
        rArray = new Race *[m];
        for (int i = 0; i<m; i++){
            cin >> choice;
            cin >> city;
            cin >> year;
            cin >> month;
            cin >> bestTime;
            cin >>length;
            if (choice == 1){
                rArray[i] = new Race(city, year, month, bestTime, length);
            }
            else{
                cin>>numberLaps;
                cin>>n;
                for (int j = 0; j < n; j++)
                    cin >> bestTimes[j];
                rArray[i] = new MotoGPRace(city, year, month, bestTime, length,bestTimes, n, numberLaps);
            }
        }
        // print the races
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];

        // add a new best time
        float best;
        cin >> best;
        int flag = 1;
        for (int i = 0; i < m; i++){
            MotoGPRace* nn = dynamic_cast<MotoGPRace*>(rArray[i]);
            if (nn != 0){
                flag = 0;
                (*nn) += best;
                break;
            }
        }

        // print the races
        cout << "\nLista na site Trki:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];
    }
    if (testCase == 3){
        cout << "===== Testing - exceptions ======" << endl;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin>>length;
        cin>>numberLaps;
        MotoGPRace mgt(city, year, month, bestTime, length);
        mgt.setNumberLaps(numberLaps);
        float time1,time2;
        cin>>time1>>time2;
        try {
            mgt += time1;
            mgt += time2;
        }catch(Exception &e){
            e.message();
        }
        cout<<mgt;
    }
    if (testCase == 4){
        cout <<"===== Testing - operator++ ======"<<endl;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin>>length;
        cin>>numberLaps;
        cin>>n;
        for (int j = 0; j < n; j++)
            cin >> bestTimes[j];

        MotoGPRace mgt(city, year, month, bestTime, length,bestTimes,n,numberLaps);
        float v,koef2;
        cout<<(mgt++).getNumberLaps()<<endl;
        cout<<mgt;
        mgt++;
        cout<<mgt;
    }
    if (testCase == 5){
        cout << "===== Testing - coefficient ======" << endl;
        Race **rArray;
        cin >> m;
        rArray = new Race *[m];
        for (int i = 0; i<m; i++){
            cin >> choice;
            cin >> city;
            cin >> year;
            cin >> month;
            cin >> bestTime;
            cin >>length;
            if (choice == 1){
                rArray[i] = new Race(city, year, month, bestTime, length);
            }
            else{
                cin>>numberLaps;
                cin>>n;
                for (int j = 0; j < n; j++)
                    cin >> bestTimes[j];
                rArray[i] = new MotoGPRace(city, year, month, bestTime, length,bestTimes, n, numberLaps);
            }
        }
        // print the races
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];

        MotoGPRace::setK(0.7);
        // print the races
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];
    }

    if (testCase == 6){
        cout << "===== Testing - full functionality ======" << endl;
        Race **rArray;
        cin >> m;
        rArray = new Race *[m];
        for (int i = 0; i<m; i++){
            cin >> choice;
            cin >> city;
            cin >> year;
            cin >> month;
            cin >> bestTime;
            cin >>length;
            if (choice == 1){
                rArray[i] = new Race(city, year, month, bestTime, length);
            }
            else{
                cin>>numberLaps;
                cin>>n;
                for (int j = 0; j < n; j++)
                    cin >> bestTimes[j];
                rArray[i] = new MotoGPRace(city, year, month, bestTime, length,bestTimes, n, numberLaps);
            }
        }
        // print the races
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];
        float newCoef;
        cin>>newCoef;
        MotoGPRace::setK(newCoef);
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];
        // print the races
        float newBest;
        cin>>newBest;
        int flag = 1;
        for (int i = 0; i < m; i++){
            MotoGPRace * pok= dynamic_cast<MotoGPRace *>(rArray[i]);
            if(pok!=0)
            {
                try {
                    (*pok)++;
                    (*pok) += newBest;
                }catch(Exception &e){
                    e.message();
                }
                if(flag==1)
                {
                    flag = 0;
                    try {
                        *pok += 1.4;
                    }catch(Exception &e){
                        e.message();
                    }
                }
            }
        }
        cout << "\nList of the races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];
    }

    return 0;
}
