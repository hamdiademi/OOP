// Created by Hamdi on 3/29/2023.
//
#include <stdio.h>
#include <string.h>
#define WEEKS 4
#define DAYS 5

// here the struct WorkingWeek
typedef struct WorkingWeek{
    int hours[DAYS];
}WW;

// here the struct Worker
typedef struct Worker{
    char name[50];
    WW weeks[DAYS];
} W;
// here the functions
int maxWeek(W *w){
    int max = 0;
    int index = 0;
    int s;

    for (int i = 0; i < WEEKS; i++)
    {
        s = 0;

        for (int j = 0; j < DAYS; j++)
            s += w->weeks[i].hours[j];

        if (max < s)
        {
            max = s;
            index = i;
        }
    }

    return index + 1;

}

void table(W *w, int n){
    int a[WEEKS];
    int total;

    printf("Wor\t1\t2\t3\t4\tTotal\n");

    for (int i = 0; i < n; i++)
    {
        total = 0;

        for (int j = 0; j < WEEKS; j++)
            a[j] = 0;

        for (int j = 0; j < WEEKS; j++)
            for (int k = 0; k < DAYS; k++)
                a[j] += w[i].weeks[j].hours[k];

        printf("%s\t", w[i].name);
        for (int j = 0; j < WEEKS; j++)
        {
            total += a[j];
            printf("%d\t", a[j]);
        }
        printf("%d\n", total);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    W workers[n];
    int i;
    for (i = 0; i < n; ++i) {
        scanf("%s", workers[i].name);
        int j;
        for (j = 0; j < WEEKS; ++j) {
            int k;
            for (k = 0; k < DAYS; ++k) {
                scanf("%d", &workers[i].weeks[j].hours[k]);
            }

        }
    }
    printf("TABLE\n");
    table(workers, n);
    printf("MAX WEEK OF WORKER: %s\n", workers[n / 2].name);
    printf("%d\n", maxWeek(&workers[n / 2]));
    return 0;
}
