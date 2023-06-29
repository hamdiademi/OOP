#include <stdio.h>

typedef struct Point{
    int x;
    int y;
}Point;

void readpoint(Point * p){
    scanf("%d %d",&p->x,&p->y);
}

typedef struct Circle{
    Point centre;
    int radius;
}Circle;

void readcircle(Circle * c){
    readpoint(&c->centre);
    scanf("%d",&c->radius);
}
void printcircle(Circle c){

    printf("Largest circle has area of: %.2f with centre:(%d,%d) ",(c.radius*c.radius)*3.14,c.centre.x,c.centre.y);
}


int main() {
    int n ;
    scanf("%d",&n);
    Circle c[100];
    for (int i = 0; i < n; ++i) {
        readcircle(&c[i]);
    }
    int max=0,j;
    for (int i = 0; i < n; ++i) {
        if(c[i].radius>max){
            max=c[i].radius;
            j=i;
        }
    }
    printcircle(c[j]);





    return 0;
}
