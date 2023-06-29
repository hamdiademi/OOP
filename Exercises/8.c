//
// Created by Hamdi on 3/29/2023.
//
#include <stdio.h>

typedef struct driver{
    char name[50];
    int sec;
}Driver;

void readdriver(Driver*d){
    scanf("%s %d",d->name,&d->sec);
}

typedef struct race{
    char location[100];
    int nrDrivers;
    Driver Drivers[100];
}Race;

void readRace(Race*r){
    scanf("%s %d",r->location,&r->nrDrivers);
    for (int i = 0; i < r->nrDrivers; ++i) {
        readdriver(&r->Drivers[i]);
    }
}

void Bubblesort(Race*r) {

    for (int i = 0; i < r->nrDrivers; ++i) {
        for (int j = 0; j < r->nrDrivers - 1; ++j) {

            if (r->Drivers[j].sec > r->Drivers[j + 1].sec) {
                Driver tmp = r->Drivers[j];
                r->Drivers[j] = r->Drivers[j + 1];
                r->Drivers[j + 1] = tmp;
            }

        }
    }
    for (int i = 0; i < 3; ++i) {
        int sec=r->Drivers[i].sec;
        printf("%d. %s %2d:%02d\n",i+1,r->Drivers[i].name, sec / 60, sec % 60);
    }
}
int main() {
    int n;
    scanf("%d",&n);
    Race race[n];

    for (int i = 0; i < n; ++i) {
        readRace(&race[i]);
    }
    for (int i = 0; i < n; ++i) {
        printf("%s (%d Drivers)\n",race[i].location,race[i].nrDrivers);
        Bubblesort(&race[i]);

    }

    return 0;
}

