// Created by Hamdi on 3/28/2023.

#include <iostream>
#include <cstring>
using namespace std;

class SpaceObject{
private:
    char name[101];
    char type[101];
    int distanceFromEarth;
public:
    SpaceObject(){
        name[0] = '\0';
        type[0] = '\0';
        distanceFromEarth = 0;
    };
    SpaceObject(const char* name,const char* type,int distanceFromEarth){
        strcpy(this->name,name);
        this->name[100]='\0';
        strcpy(this->type,type);
        this->type[100]='\0';
        this->distanceFromEarth=distanceFromEarth;
    }
    ~SpaceObject(){}

    void setName(const char* name) {
        strcpy(this->name, name);
        this->name[100] = '\0';
    }
    void setType(const char* type) {
        strcpy(this->type, type);
        this->type[100] = '\0';
    }
    void setDistance(int distanceFromEarth) {
        this->distanceFromEarth = distanceFromEarth;
    }

    const char* getname()const{
        return name;
    }
    const char* gettype()const{
        return type;
    }
    int getdistance()const{
        return distanceFromEarth;
    }
    void print() const {
        cout << name << " (" << type << ") - distance: " << distanceFromEarth << " light years away from Earth" << endl;
    }

};

class Alien {
private:
    char name[101];
    int age;
    char homePlanet[101];
    int numobj;
    SpaceObject spaceObject[100];
public:
    Alien() {
        name[0] = '\0';
        age = 0;
        homePlanet[0] = '\0';
        numobj = 0;
    };

    Alien(const char *name, int age, const char *homePlanet, int numobj, SpaceObject *spaceobj) {
        strcpy(this->name, name);
        this->name[100] = '\0';
        this->age = age;
        strcpy(this->homePlanet, homePlanet);
        this->homePlanet[100] = '\0';
        this->numobj = numobj;
        for (int i = 0; i < numobj; ++i) {
            spaceObject[i] = spaceobj[i];
        }
    }
    //copy construction
    Alien(const Alien& obj) {
        strcpy(this->name, obj.name);
        this->name[100] = '\0';
        this->age = obj.age;
        strcpy(this->homePlanet, obj.homePlanet);
        this->homePlanet[100] = '\0';
        this->numobj = obj.numobj;
        for (int i = 0; i < numobj; ++i) {
            spaceObject[i] = obj.spaceObject[i];
        }
    }

    ~Alien() {
        //delete[]spaceObject;
    }
    void setName(const char *name) {
        strcpy(this->name, name);
        this->name[100] = '\0';
    }

    void setAge(int age) {
        this->age = age;
    }

    void setHomePlanet(const char *homePlanet) {
        strcpy(this->homePlanet, homePlanet);
        this->homePlanet[100] = '\0';
    }

    void setNumObj(int numObj) {
        this->numobj = numObj;
    }

    void setSpaceObjects(SpaceObject *spaceObjects, int numObj) {
        for (int i = 0; i < numObj; ++i) {
            this->spaceObject[i] = spaceObjects[i];
        }
    }

    const char *getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }

    const char *getHomePlanet() const {
        return homePlanet;
    }

    int getNumObj() const {
        return numobj;
    }

    SpaceObject *getSpaceObjects() {
        return spaceObject;
    }




    SpaceObject getObjectClosestToEarth() {
            SpaceObject closest;
            int minDistance =spaceObject[0].getdistance();

            for (int i = 0; i < numobj; i++) {
                if (spaceObject[i].getdistance() < minDistance) {
                    closest = spaceObject[i];
                    minDistance = spaceObject[i].getdistance();
                }
            }

            return closest;
    }

    void print() {
            cout << "Alien name: " << name << endl;
            cout << "Alien age: " << age << endl;
            cout << "Alien home planet: " << homePlanet << endl;
            cout << "Favorite space object closest to earth: ";
            getObjectClosestToEarth().print();
    }
};
    int main() {

        return 0;
    }

