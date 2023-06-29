#include <iostream>
#include <cstring>
using namespace std;

class Film{
private:
    char name[50];
    double rating;
    double revenue;
public:
    Film(){};
    Film(char *_name,double _rating,double _revenue){
        strcpy(name,_name);
        rating=_rating;
        revenue=_revenue;
    }
    ~Film(){};

     void setName(char *_name){
         strcpy(name,_name);
    }
    void setRating(double _rating){
        rating=_rating;
    }
    void setRevenue(double _revenue){
        revenue=_revenue;
    }

     char* getname(){
        return name;
     }

     double getrating(){
         return rating;
     }
     double getrevenue(){
         return revenue;
     }



    void display(){
         cout<<"Name of film: "<<getname()<<"\nRating: "<<getrating()<<"\nRevenue: "<<getrevenue()<<endl;
     }

};
//outside class

void printMostPopularFilm(Film *films,int n){
    double max=0;
    char name[50];
    double rating;
    double revenue;
    for (int i = 0; i < n; ++i) {
        if(films[i].getrevenue()>max){
            max=films[i].getrevenue();
            strcpy(name,films[i].getname());
            rating=films[i].getrating();
            revenue=films[i].getrevenue();
        }
    }
    cout<<"Name of film: "<<name<<"\nRating: "<<rating<<"\nRevenue: "<<revenue<<endl;

}



// DO NOT CHANGE THE MAIN FUNCTION
int main() {
    int n;
    cin >> n;
    Film films[100];

    char name[100];
    double rating;
    double revenue;

    for (int i = 0; i < n-1; i++)  {
        cin>>name;
        cin >> rating;
        cin >> revenue;

        // testing constructor with arguments
        films[i] = Film(name, rating, revenue);

    }


    // testing set methods and display for last element
    cin>>name;
    cin >> rating;
    cin >> revenue;
    films[n-1].setName(name);
    films[n-1].setRating(rating);
    films[n-1].setRevenue(revenue);

    cout<<"-->Testing set methods and display()"<<endl;
    films[n-1].display();
    cout<<endl;

    cout<<"-->Testing printMostPopularFilm()"<<endl;
    printMostPopularFilm(films , n);
    return 0;
}
