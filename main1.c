#include <stdlib.h>
#include <stdio.h>        
#include <stdbool.h>     
#include <string.h>  
#include <stdint.h>     
#include <math.h> 
#include <time.h>  
#include "mtwist-1.5/mtwist.c"
#include "mtwist-1.5/mtwist.h"

int random_number(int min_num, int max_num)
{
    int result = 0, low_num = 0, hi_num = 0;
    if (min_num == max_num) return min_num;
    if (min_num < max_num)
    {
      low_num = min_num;
      hi_num = max_num + 1; // include max_num in output
    } 
    else 
    {
      low_num = max_num; // include max_num in output
      hi_num = min_num + 1;
    }
      srand(time(NULL));
      result = (rand() % (hi_num - low_num)) + low_num;
      return result;
}

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
    double count = 0;
    // int p1start = 5;
    for (int topCard = 50; topCard <= 50; topCard++)
    {
        for (int p1start = 1; p1start < 50; p1start++) {
        for (int i = 0; i < 10000; i++)
        {
            mt_seed();
            count += warMoves(p1start, topCard);
        }
        printp1p2(topCard, p1start);
        printf("Moves: ");
        printf("%f\n", count / 10000);
        count = 0;
        }
    }
    return 0;
}