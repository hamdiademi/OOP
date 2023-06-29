// Created by Hamdi on 3/29/2023.
//
#include <stdio.h>
#include <string.h>
typedef struct s{
    char name[50];
    int max;
    int func;
}Skilift;
void readskilift(Skilift*s){
    scanf("%s %d %d",s->name,&s->max,&s->func);
}

typedef struct sk{
    char name[50];
    char country[50];
    int nrlift;
    Skilift skilift[20];
}Skicenter;
void readskiCenter(Skicenter*s){
    scanf("%s %s %d",s->name,s->country,&s->nrlift);
    for (int i = 0; i < s->nrlift; ++i) {
        readskilift(&s->skilift[i]);
    }
}

int BiggestCapacity(Skicenter sc){
    int sum=0;
    for (int i = 0; i < sc.nrlift; ++i) {
        if(sc.skilift[i].func==1){
            sum+=sc.skilift[i].max;
        }
    }
    return sum;
}

int main() {
    int n;
    scanf("%d",&n);
    Skicenter skicenter[100];
    for (int i = 0; i < n; ++i) {
        readskiCenter(&skicenter[i]);
    }
//    int max=0;
//    char titleM[50],country[50];
//    for (int i = 0; i < n; ++i) {
//        int biggest=BiggestCapacity(skicenter[i]);
//        if(biggest>max){
//            max=biggest;
//            strcpy(titleM,skicenter[i].titleM);
//            strcpy(country,skicenter[i].country);
//        }
//        else if(biggest==max){
//            if(skicenter[i-1].nrlift>skicenter[i].nrlift) {
//                strcpy(titleM, skicenter[i - 1].titleM);
//                strcpy(country, skicenter[i - 1].country);
//            }
//            else {
//                strcpy(titleM, skicenter[i].titleM);
//                strcpy(country, skicenter[i].country);
//            }
//        }
//    }
    int max=0;
    char name[50],country[50];
    for (int i = 0; i < n; ++i) {
        int biggest=BiggestCapacity(skicenter[i]);
        if(biggest==max){
            if(skicenter[i-1].nrlift>skicenter[i].nrlift) {
                strcpy(name, skicenter[i - 1].name);
                strcpy(country, skicenter[i - 1].country);
            }
        }
        if(biggest>=max){
            max=biggest;
            strcpy(name,skicenter[i].name);
            strcpy(country,skicenter[i].country);
        }

    }
    printf("%s\n%s\n%d\n",name,country,max);

    return 0;
}

