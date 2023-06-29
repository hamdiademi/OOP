#include <iostream>
#include <cstring>
using namespace std;

class Country{
private:
    char name[100];
    char capital[100];
    double area;
    double population;
public:
    Country(){};
    Country(char *_name,char *_capital,double _area,double _population){
        strcpy(name,_name);
        strcpy(capital,_capital);
        area=_area;
        population=_population;
    };
    ~Country(){};

    void setName(char *_name){
        strcpy(name,_name);
    }
    void setCapital(char *_capital){
        strcpy(capital,_capital);
    }
    void setArea(double _area){
        area=_area;
    }
    void setPopulation(double _population){
        population=_population;
    }

    char* getname(){
        return name;
    }
    char* getcapital(){
        return capital;
    }
    double getarea(){
        return area;
    }
    double getpopupulation(){
        return population;
    }

    void display(){
        cout<<"Country :"<<getname()<<"\nCapital: "<<getcapital()<<"\nArea: "<<getarea()<<"\nPopulation: "<<getpopupulation()<<endl;
    }

};
//outside class
void sortCountries(Country* countries,int n){
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n-1; ++j) {

            if(countries[j].getarea()>countries[j+1].getarea()){
                Country temp = countries[j];
                countries[j] = countries[j+1];
                countries[j+1] = temp;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        cout<<"Country :"<<countries[i].getname()<<"\nCapital: "<<countries[i].getcapital()<<"\nArea: "<<countries[i].getarea()<<"\nPopulation: "<<countries[i].getpopupulation()<<endl;
    }
}

int main() {
    int n;
    cin >> n;
    Country countries[100];

    char name[100];
    char capital[100];
    double area;
    double population;

    for (int i = 0; i < n-1; i++)  {
        cin>>name;
        cin >> capital;
        cin >> area;
        cin>>population;

        // testing constructor with arguments
        countries[i] = Country(name, capital, area, population);

    }


    // testing set methods and display for last element
    cin>>name;
    cin >> capital;
    cin >> area;
    cin>>population;
    countries[n-1].setName(name);
    countries[n-1].setCapital(capital);
    countries[n-1].setArea(area);
    countries[n-1].setPopulation(population);

    cout<<"-->Testing set methods and display()"<<endl;
    countries[n-1].display();
    cout<<endl;

    cout<<"-->Testing sortCountries()"<<endl;
    sortCountries(countries,n);
    return 0;
}
