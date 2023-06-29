//
// Created by ssara on 4/10/2023.
//
#include <stdio.h>
#include <string.h>

typedef struct Transaction{
    int day, month, year;
    int amount;
    char currency[4];
}Transaction;
int main(){
    int n;

    scanf("%d",&n);
    Transaction transaction[1000];
    for (int i = 0; i < n; ++i) {

       scanf("%s %d %d/%d/%d",transaction[i].currency,&transaction[i].amount,&transaction[i].day,&transaction[i].month,&transaction[i].year);
    }
    int j=1,sum=0;
    for (int i = 0; i < n; ++i) {

        if (strcmp(transaction[i].currency,"USD")==0) {
            if (transaction[i].amount < 5000 && transaction[i].month < 4) {
                printf("%d. %02d/%02d/%d %d %s \n",j, transaction[i].day, transaction[i].month, transaction[i].year,
                       transaction[i].amount, transaction[i].currency);
                sum+=transaction[i].amount;
                j++;
            }
        }
    }
    printf("Total: %d USD",sum);
    return 0;
}