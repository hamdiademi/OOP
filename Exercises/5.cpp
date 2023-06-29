// Created by Hamdi on 3/29/2023.
//
#include<iostream>
using namespace std;

struct Player{
    char name[15];
    int level;
    int points;
};
struct ComputerGame{
    char name[20];
    int n;
    Player player[50];
};

void bestPlayer(ComputerGame *array, int n) {
    int maxPoints = 0;
    int maxLevel = 0;
    int gameIndex = 0;
    int playerIndex = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < array[i].n; ++j) {
            if (array[i].player[j].points > maxPoints) {
                maxPoints = array[i].player[j].points;
                maxLevel = array[i].player[j].level;
                gameIndex = i;
                playerIndex = j;
            }
            else if (array[i].player[j].points == maxPoints && array[i].player[j].level > maxLevel) {
                maxLevel = array[i].player[j].level;
                gameIndex = i;
                playerIndex = j;
            }
        }
    }
    cout << "Najdobar igrac e igracot so korisnicko ime " << array[gameIndex].player[playerIndex].name
         << " koj ja igra igrata " << array[gameIndex].name << endl;
}



int main() {
    int n,m;
    char name[20];
    cin>>n;
    //create an array of max 100 computer games;
    ComputerGame poleigri[100];

    for (int i=0; i<n; i++) {
        ComputerGame nova;
        cin>>nova.name>>nova.n;
        Player pole[30];
        for (int j=0; j<nova.n; j++) {
            Player nov;
            cin>>nov.name>>nov.level>>nov.points;
            nova.player[j]=nov;
        }
        poleigri[i]=nova;
    }
    bestPlayer(poleigri,n);


    return 0;
}
