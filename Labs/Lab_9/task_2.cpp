//
// Created by Hamdi on 5/15/2023.
//
#include <iostream>
#include <cstring>
using namespace std;

class Game{
protected:
    char title[50];
public:
    Game() {}//
    Game(char *title){
        strcpy(this->title,title);
    }
    virtual void displayInfo()=0;
    virtual int complexity()=0;
};

class BoardGame: virtual public Game{
protected:
    int maxPlayers;
public:
    BoardGame() {}//
    BoardGame(char *title, int maxPlayers) : Game(title), maxPlayers(maxPlayers) {}

    void displayInfo() override {
        cout<<"Game: "<<title<<endl;
        cout<<"Max players: "<<maxPlayers<<endl;
        cout<<"Complexity: "<<complexity()<<endl;

    }

    int complexity() override {
        if(maxPlayers>6){
            return 10;
        }else if(maxPlayers>3 && maxPlayers<6){
            return 5;
        } else {
            return 3;
        }
    }
};
class CardGame: virtual public Game{
protected:
    int numCards;
public:
    CardGame() {}//
    CardGame(char *title, int numCards) : Game(title), numCards(numCards) {}

    void displayInfo() override {
        cout<<"Game: "<<title<<endl;
        cout<<"Number of cards: "<<numCards<<endl;
        cout<<"Complexity: "<<complexity()<<endl;

    }

    int complexity() override {
        if (numCards>20){
            return 10;
        }else if(numCards>10 && numCards<20){
            return 5;
        }else{
            return 3;
        }
    }
};

class BoardCardGame: public BoardGame,public CardGame{
public:
    BoardCardGame(){}//
    BoardCardGame(char *title, int maxPlayers, int numCards) : BoardGame(title, maxPlayers),CardGame(title, numCards), Game(title) {}

    void displayInfo() override {
        cout<<"Game: "<<title<<endl;
        cout<<"Complexity: "<<complexity()<<endl;
    }

    int complexity() override {
        return (CardGame::complexity()+BoardGame::complexity())/2;
    }


};

Game *mostComplexCardGame(Game ** games,int n){
    CardGame *mostComplexCardGame, *tmpGame;
    int index=-1;
    for(int i=0;i<n;i++)
    {
        tmpGame = dynamic_cast<CardGame *>(games[i]);


        if(tmpGame){
            if(index == -1)
            {
                index = i;
                mostComplexCardGame = tmpGame;
            }
            else if(mostComplexCardGame->complexity() < tmpGame->complexity())
            {
                mostComplexCardGame = tmpGame;
            }
        }


    }


    return mostComplexCardGame;
}
int main() {
    char title[50];
    int maxPlayers;
    int numCards;
    int n;
    int choice;


    cin>>choice;
    if(choice==1)
    {
        cin>>title;
        BoardCardGame boardCardGame(title, 8, 15);
        boardCardGame.displayInfo();
    }
    else {


        cin >> n;


        Game **g = new Game *[n];
        for (int i = 0; i < n; i++) {
            cin >> choice;
            if (choice == 1) {
                cin >> title >> maxPlayers;


                g[i] = new BoardGame(title, maxPlayers);
            } else {
                cin >> title >> numCards;


                g[i] = new CardGame(title, numCards);
            }


        }


       mostComplexCardGame(g,n)->displayInfo();


    }



    return 0;
}