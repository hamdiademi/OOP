// Created by Hamdi on 3/29/2023.
//
#include <iostream>
#include <cstring>
using namespace std;

class InvalidTeamName{
    char team[51];
public:
     InvalidTeamName(char *team){
        strcpy(this->team,team);
    }
   char* what(){
       return team;
     }

};

class Goal{
    char *player;
    int time;
    char team[51];

    void copy(const Goal &other){
        this->player=new char[strlen(other.player)+1];
        strcpy(this->player,other.player);
        this->time=other.time;
        strcpy(this->team,other.team);
    }
public:

    Goal(const char *player="", int time=0, const char *team="") {
        this->player=new char[strlen(player)+1];
        strcpy(this->player,player);
        this->time=time;
        strcpy(this->team,team);
    }

    Goal(const Goal &other){
        copy(other);
    }

    Goal &operator=(const Goal &other){
        if (this!=&other){
            delete[]player;
            copy(other);
        }
        return *this;
    }

    friend ostream &operator<<(ostream &os, const Goal &goal) {
        os << goal.time <<" "<< goal.player<<endl;
        return os;
    }

    ~Goal(){
        delete[]player;
    }

    friend  class Game;
};

class Game{
    Goal *goals;
    int n;
    char team1[51];
    char team2[51];
    void copy(const Game &other){
        strcpy(this->team1,other.team1);
        strcpy(this->team2,other.team2);
        this->n=other.n;
        this->goals=new Goal[other.n];
        for (int i = 0; i < n; ++i) {
            this->goals[i]=other.goals[i];
        }
    }
public:
    Game(char *team1="", char *team2="") {
    strcpy(this->team1,team1);
    strcpy(this->team2,team2);
        this->n=0;
        this->goals=new Goal[n];
    }

    Game(const Game &other){
        copy(other);
    }

    Game &operator=(const Game &other){
        if (this!=&other){
            delete[]goals;
            copy(other);
        }
        return *this;
    }


    Game &operator+=(Goal &g){
        if (strcmp(g.team, team1) != 0 && strcmp(g.team, team2) != 0) {
            throw InvalidTeamName(g.team);
        }

        Goal *tmp=new Goal[n+1];
        for (int i = 0; i < n; ++i) {
            tmp[i]=goals[i];
        }
        tmp[n]=g;
        n++;
        delete[]goals;
        goals=tmp;
        return *this;
    }

    friend ostream &operator<<(ostream &os, const Game &game) {
        os << game.team1 <<" - " << game.team2<<endl;
        for (int i = 0; i < game.n; ++i) {
            os << game.goals[i];
        }
        return os;
    }
    ~Game(){
       delete[]goals;
    }

};

int main() {
    char team1[50];
    char team2[50];
    cin >> team1;
    cin >> team2;
    Game n(team1, team2);
    int x;
    cin >> x;
    char player[100];
    int m;
    for(int i = 0; i < x; ++i) {
        cin >> player;
        cin >> m;
        cin >> team1;
        Goal g(player, m, team1);
        try {
            n += g;
        } catch(InvalidTeamName &e) {
            cout << "Invalid team titleM: " << e.what() << endl;
        }
    }
    cout << n << endl;
    return 0;
}
