#include <stdio.h>

typedef struct Transaction{
    int id;
    int commission;
    int sum;
    int type;
}Transaction;

void read(Transaction * t){
    scanf("%d %d %d %d",&t->id,&t->commission,&t->sum,&t->type);
}
void print(Transaction t){
    printf("%d %d\n",t.id,t.commission+t.sum);
}

int main() {
    Transaction t;
    int n,flag=0;
    scanf("%d",&n);
    for (int i = 0; i < n; ++i) {
        read(&t);
        if(t.type){
            print(t);
            flag=1;
        }
    }
    if(!flag){
        printf("No credit card transaction");
    }

    return 0;
}
