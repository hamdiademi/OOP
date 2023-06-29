// Created by Hamdi on 3/29/2023.
//
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

class Camera{
    char producer[21];
    char model[21];
    int year;
    float resolution;
public:
    Camera(char *producer="", char *model="", int year=0, float resolution=0) : year(year),resolution(resolution) {
        strcpy(this->producer,producer);
        strcpy(this->model,model);
    }
    ~Camera(){}

//Functions:
    virtual float price()=0;
    virtual float rentalPrice(int)=0;

    friend class PhotoCamera;
    friend class VideoCamera;
    friend class FilmCamera;

    char* getModel() {
        return model;
    }
};

/// 1
class PhotoCamera : public Camera{
    bool raw;
public:
    PhotoCamera(char *producer, char *model, int year, float resolution,bool raw= false) : Camera(producer,model,year,resolution),raw(raw) {}
    ~PhotoCamera() {}

//Functions:

    float price() override {
        float price=100+resolution*20;
        if(raw){
            price+=50;
        }
        return price;
    }

    float rentalPrice(int days) override {
       float rental= (price()/100)*(float)days;
        if (days>7){
            rental= rental*(1-0.20);
        }
        return rental;
    }
    bool operator<( PhotoCamera &rhs)  {

        return price() < rhs.price();
    }

};

/// 2
class VideoCamera : public Camera{
    int length;
public:
    VideoCamera(char *producer, char *model, int year, float resolution,int length=0) :  Camera(producer,model,year,resolution),length(length) {}


    float price() override {
        float price=resolution*80;
        if (length>3600){
             price*=1.4;
        }
        return price;
    }

    float rentalPrice(int days) override {
        float rental= (price()/100)*(float)days;
        if (days>7){
            rental= rental*(1-0.20);
        }
        return rental;
    }
    bool operator<( VideoCamera &rhs)  {

        return price() < rhs.price();
    }


};

/// 3
class FilmCamera : public Camera{
    int fps;
public:
     FilmCamera(char *producer, char *model, int year, float resolution,int fps=0) :  Camera(producer,model,year,resolution),fps(fps) {}
     ~FilmCamera() {}

//Functions:

    float price() override {
         float price=5000;
        if (fps>30){
            int n=fps-30;
            for (int i = 0; i < n; ++i) {
                price+=5000;
            }
        }
        return price;

    }

    float rentalPrice(int days) override {
            float rental=500*days;
        if (fps>60){
            rental*=2;
        }
        return rental;
    }

    bool operator<( FilmCamera &rhs)  {

        return price() < rhs.price();
    }

};



float production(Camera** cameras, int numCameras, int days) {
    float totalPrice = 0;
    for (int i = 0; i < numCameras; i++) {
        totalPrice += cameras[i]->rentalPrice(days);
    }
    return totalPrice;
}


char *mostExpensiveCamera(Camera **camera, int n){
    float max=camera[0]->price();
    int index=0;
    for(int i=0 ; i<n ; i++){
        if(camera[i]->price()>max){
            max=camera[i]->price();
            index=i;
        }
    }
    return camera[index]->getModel();
}



int main(int argc, char *argv[])
{
    // Variables for reading input
    char model[20], producer[20];
    int year, length, fps, n;
    float resolution;
    bool raw;

    int t;

    // Array of cameras
    Camera *c [10];

    // Read number of cameras
    cin>>n;

    for(int i = 0; i < n; ++i){

        // Camera type: 1 - Photo, 2 - Video, 3 - Film
        cin>>t;

        if (t==1){
            cin >> producer >> model >> year >> resolution;
            cin >> raw;
            c[i] = new PhotoCamera(producer, model, year, resolution, raw);
        }
        else if (t==2){
            cin >> producer >> model >> year >> resolution;
            cin >> length;
            c[i] = new VideoCamera(producer, model, year, resolution, length);
        }
        else if (t==3){
            cin >> producer >> model >> year >> resolution;
            cin >> fps;
            c[i] = new FilmCamera(producer, model, year, resolution, fps);
        }
    }


    // Production days
    int days;
    cin >> days;


    cout << "Price of production is: " << production(c, n, days);
    cout<<"\n" << "Most expensive camera used in production is: " << mostExpensiveCamera(c, n);


    return 0;
}


