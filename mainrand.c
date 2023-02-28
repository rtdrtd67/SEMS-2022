#include <stdlib.h>
#include <stdio.h>        
#include <stdbool.h>     
#include <string.h>  
#include <stdint.h>     
#include <math.h> 
#include <time.h>  
#include "mtwist-1.5/mtwist.c"
#include "mtwist-1.5/mtwist.h"

void printintarray(int n, int* arr)
{
    printf("[");
    for (int i = 0; i < n; i++)
    {
        printf("%d", arr[i]);
        if (i != n - 1) printf(", ");
    }
    printf("]\n");
}

int warMoves(int p1num, int topCard)
{
    int* first = calloc(sizeof(int), topCard);
    int* second = calloc(sizeof(int), topCard);
    int count = 0;
    int p1cur = p1num;
    int p2cur = topCard - p1cur;
    first[0] = topCard;
    for (int i = 1; i < p1cur; i++) first[i] = i;
    for (int j = 0; j < p2cur; j++) second[j] = topCard - p2cur + j;
    while (first[topCard-1] == 0)
    {
        int randOne = abs(mt_lrand()) % p1cur;
        int randTwo = abs(mt_lrand()) % p2cur;
        int topfirst = first[randOne];
        int topsecond = second[randTwo];
        if (topfirst > topsecond) 
        {
            first[p1cur] = topsecond;
            second[randTwo] = second[p2cur - 1];
            second[p2cur - 1] = 0;
            p1cur++;
            p2cur--;
        }
        else
        {
            second[p2cur] = topfirst;
            first[randOne] = first[p1cur - 1];
            first[p1cur - 1] = 0;
            p2cur++;
            p1cur--;
        }
        // printintarray(topCard, first);
        // printintarray(topCard, second);
        count++;
    }
    return count;
}

int countOne(int p1num, int topCard)
{
    int* first = calloc(sizeof(int), topCard);
    int* second = calloc(sizeof(int), topCard);
    int count = 0;
    int p1cur = p1num;
    int p2cur = topCard - p1cur;
    first[0] = topCard;
    for (int i = 1; i < p1cur; i++) first[i] = i;
    for (int j = 0; j < p2cur; j++) second[j] = topCard - p2cur + j;
    second[0] = 2;
    first[2] = 3;
    while (first[topCard-1] == 0)
    {
        int randOne = abs(mt_lrand()) % p1cur;
        int randTwo = abs(mt_lrand()) % p2cur;
        int topfirst = first[randOne];
        int topsecond = second[randTwo];
        if (topfirst == 1 || topsecond == 1) count++;
        if (topfirst > topsecond) 
        {
            first[p1cur] = topsecond;
            second[randTwo] = second[p2cur - 1];
            second[p2cur - 1] = 0;
            p1cur++;
            p2cur--;
        }
        else
        {
            second[p2cur] = topfirst;
            first[randOne] = first[p1cur - 1];
            first[p1cur - 1] = 0;
            p2cur++;
            p1cur--;
        }
        // printintarray(topCard, first);
        // printintarray(topCard, second);
    }
    return count;
}

void printp1p2(int top, int split)
{
    printf("p1 cards: {"); 
    if (split > 5)
    {
        printf("%d", 1);
        printf(",...,");
        printf("%d", split-1);
        printf(", ");
    }
    else
    {    
        for (int i = 1; i < split; i++)
        {
            printf("%d", i);
            printf(", ");
        }
    }
    printf("%d", top);
    printf("}");
    printf(", p2 cards: {");
    printf("%d", split);
    printf(",...,");
    printf("%d", top - 1);   
    printf("}");
    printf(", ");       
}

int main()
{
    mt_seed();
    double count = 0;
    for (int topCard = 4; topCard <= 4; topCard++)
    {
        int p1start = topCard-1;
        for (int i = 0; i < 10000000; i++)
        {
            count += countOne(p1start, topCard);
        }
        printp1p2(topCard, p1start);
        printf("1 Swaps: ");
        printf("%f\n", count / 10000000);
        count = 0;
    }
    return 0;
}