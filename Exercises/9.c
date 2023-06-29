// Created by Hamdi on 3/29/2023.
//
#include <stdio.h>
#include <string.h>
typedef struct Film{
    char title[50];
    int duration;
    float price;
    int discount;
}Film;
void readfilm(Film*f){
    scanf("%s %d %f %d",f->title,&f->duration,&f->price,&f->discount);
}
void printfilm(Film f){
    printf("%s %d %.2f\n",f.title,f.duration,f.price);
}

typedef struct Festival{
    char name[50];
    char place[100];
    int nrlist;
    Film list[100];
}Festival;

void readfestival(Festival*f){
    scanf("%s %s %d",f->name,f->place,&f->nrlist);
    for (int i = 0; i < f->nrlist; ++i) {
        readfilm(&f->list[i]);
    }
}
void printfestival(Festival f){
    printf("%s %s\n",f.name,f.place);
    for (int i = 0; i < f.nrlist; ++i) {
        printfilm(f.list[i]);
    }
}

int bestfestival(Festival *f ){
    int count=0;
    for (int j = 0; j < f->nrlist; ++j) {
        if(f->list[j].discount==1){
            count++;
        }
    }
    return count;

}

int main() {
    int n;
    scanf("%d",&n);
    Festival festival[100];
    for (int i = 0; i < n; ++i) {
        readfestival(&festival[i]);
    }
    for (int i = 0; i < n; ++i) {
        printfestival(festival[i]);
    }

    char name[50],place[50];
    int max=0;
    for (int i = 0; i < n; ++i) {

        int best=bestfestival(&festival[i]);
        if(best>max){
            max=best;
            strcpy(name,festival[i].name);
            strcpy(place,festival[i].place);
        }

    }

    printf("bestfestival: %s %s\n",name,place);


    return 0;
}

