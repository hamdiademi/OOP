#include <iostream>
using namespace std;

class Basketbalplayer{
public:
    char name[20];
    char surname[20];
    int number;
    int points_first;
    int points_second;
    int points_third;

     double avg_points(){
         return (points_first+points_second+points_third)/3.0;
    }
    void read(){
        cin>>name>>surname>>number>>points_first>>points_second>>points_third;
     }
    void print(){
         cout<<"Player: "<< name <<" "<< surname <<" with number: "<<number<< " has "<<avg_points()<<" points in average"<<endl;
     }

};

int main() {
Basketbalplayer player{};

    player.read();
    player.print();

    return 0;
}
