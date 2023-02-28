#include <stdlib.h>
#include <stdio.h>        
#include <stdbool.h>     
#include <string.h>  
#include <stdint.h>     
#include <math.h> 
#include <time.h>  
#include "mtwist-1.5/mtwist.c"
#include "queue.h"

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

void printp1p2(int p1num, int topCard)
{
    int* firstarray = calloc(sizeof(int), topCard);
    int* secondarray = calloc(sizeof(int), topCard);
    queue* first = queue_new();
    queue* second = queue_new();
    int count = 0;
    int p1cur = p1num;
    int p2cur = topCard - p1cur;
    firstarray[0] = topCard;
    for (int i = 1; i < p1cur; i++) firstarray[i] = i;
    for (int j = 0; j < p2cur; j++) secondarray[j] = topCard - p2cur + j;
    while (p1cur > 0)
    {
        int randIndex = abs(mt_lrand()) % p1cur;
        int randNum = firstarray[randIndex];
        firstarray[randIndex] = firstarray[p1cur - 1];
        enq(first, randNum);
        p1cur--;
    }
    while (p2cur > 0)
    {
        int randIndex = abs(mt_lrand()) % p2cur;
        int randNum = secondarray[randIndex];
        secondarray[randIndex] = secondarray[p2cur - 1];
        enq(second, randNum);
        p2cur--;
    }
    printf("p1 cards: ");
    queue_print(first);
    printf(", p2 cards: ");
    queue_print(second);
}

int warMoves(int p1num, int topCard)
{
    int* firstarray = calloc(sizeof(int), topCard);
    int* secondarray = calloc(sizeof(int), topCard);
    queue* first = queue_new();
    queue* second = queue_new();
    int count = 0;
    int p1cur = p1num;
    int p2cur = topCard - p1cur;
    firstarray[0] = topCard;
    for (int i = 1; i < p1cur; i++) firstarray[i] = i;
    for (int j = 0; j < p2cur; j++) secondarray[j] = topCard - p2cur + j;
    while (p1cur > 0)
    {
        int randIndex = abs(mt_lrand()) % p1cur;
        int randNum = firstarray[randIndex];
        firstarray[randIndex] = firstarray[p1cur - 1];
        enq(first, randNum);
        p1cur--;
    }
    while (p2cur > 0)
    {
        int randIndex = abs(mt_lrand()) % p2cur;
        int randNum = secondarray[randIndex];
        secondarray[randIndex] = secondarray[p2cur - 1];
        enq(second, randNum);
        p2cur--;
    }
    while (!queue_empty(second))
    {
        int topFirst = deq(first);
        int topSecond = deq(second);
        if (topFirst > topSecond)
        {
            if (abs(mt_lrand()) % 2 == 1)
            {
                enq(first, topFirst);
                enq(first, topSecond);
            }
            else
            {
                enq(first, topSecond);
                enq(first, topFirst);
            }
        }
        else
        {
            if (abs(mt_lrand()) % 2 == 1)
            {
                enq(second, topFirst);
                enq(second, topSecond);
            }
            else
            {
                enq(second, topSecond);
                enq(second, topFirst);
            }
        }
        count++;
    }
    return count;
}

int main()
{
    mt_seed();
    double count = 0;
    int p1start = 5;
    int trials = 500;
    for (int topCard = 10; topCard <= 50; topCard++)
    {
        for (int i = 0; i < trials; i++)
        {
            count += warMoves(p1start, topCard);
        }
        printf("topCard: %d", topCard);
        printf(", Moves: ");
        printf("%f\n", count / trials);
        count = 0;
    }
    return 0;
}