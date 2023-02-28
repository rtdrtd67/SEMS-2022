#include <stdlib.h>
#include <stdio.h>        
#include <stdbool.h>     
#include <string.h>  
#include <stdint.h>     
#include <math.h> 
#include <time.h>  
#include "stack.c"
#include "mtwist-1.5/mtwist.c"
#include "mtwist-1.5/mtwist.h"
#include "graph.c"

// tuple_t *permutation(int n)
// {
//     tuple_t *perm = malloc(sizeof(tuple_t)*n);
//     for (int i = 0; i < n; i++) 
//     {
//         perm[i] = malloc(sizeof(tuple));
//         perm[i]->value = i + 1;
//     }
//     for (int i = n - 1; i > 0; i--)
//     {
//         int index = abs(mt_lrand()) % n;
//         tuple_t num = perm[index];
//         perm[index] = perm[i];
//         perm[i] = num;
//     }
//     for (int i = 0; i < n; i++)
//     {
//         perm[i]->index = i;
//     }
//     return perm;
// }

void freetuplestar(tuple_t *a, int n)
{
    for (int i = 0; i < n; i++) free(a[i]);
    free(a);
}

void freetuplestack(istack_t s)
{
    while (!empty(s))
    {
        free(ipop(s));
    }
    free(s);
}

void printArr(tuple_t *a, int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]->value);
    printf("\n");
}

void printArrInt(int *a, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
        if (i % 30 == 29) printf("\n");
    }
    printf("\n");
}


void copyArray(int *a, tuple_t **b, int idx, int n)
{
    for (int i = 0; i < n; i++) 
    {
        tuple_t pair = malloc(sizeof(tuple_t));
        pair->value = a[i];
        pair->index = i;
        (b[idx])[i] = pair;
    }
}

int *longestAlmostMonotone(tuple_t *fullperm, int len, tuple_t *perm, int n)
{
    istack_t *stacks = calloc(sizeof(istack_t), n+1);
    for (int i = 0; i < n+1; i++) stacks[i] = istack_new();
    for (int i = 0; i < n; i++)
    {
        tuple_t cur = perm[i];
        for (int j = 0; j < n; j++)
        {
            istack_t stack = stacks[j];
            if (empty(stack))
            {
                ipush(stack, cur);
                break;
            }
            else if (cur->value < peek(stack)->value)
            {
                ipush(stack, cur);
                break;
            }
            else
            {
               continue; 
            }
        }
    }
    tuple_t lastNum = malloc(sizeof(tuple));
    int lastIndex = 0;
    for (int i = 0; i < n + 1; i++) 
    {
        if (empty(stacks[i])) 
        {
            lastIndex = i-1;
            lastNum = peek(stacks[lastIndex]);
            break;
        }
    }
    int index = lastNum->index;
    // for (int i = 0; i <= lastIndex; i++) printf("%d\n", peek(stacks[i])->value);
    int *increasing = calloc(sizeof(int), lastIndex + 3);
    increasing[lastIndex] = lastNum->value;
    increasing[lastIndex + 2] = 0;
    for (int i = lastIndex - 1; i >= 0; i--)
    {
        istack_t stack = stacks[i];
        while (!empty(stack))
        {
            tuple_t top = ipop(stack);
            if (top->index < index)
            {
                increasing[i] = top->value;
                index = top->index;
                break;
            }
        }
    }
    for (int i = n; i < len; i++)
    {
        if (fullperm[i]->value < increasing[lastIndex])
        {
            increasing[lastIndex + 1] = fullperm[i]->value;
            break;
        }
    }
    return increasing;
}

tuple_t *reverse(tuple_t *perm, int n)
{
    tuple_t *reversed = calloc(sizeof(tuple_t), n);
    for (int i = 0; i < n; i++)
    {
        reversed[i] = perm[n - i - 1];
    }
    return reversed;
}

int **heapIterative(int *A, int n, tuple_t **acc, int ordperm)
{
  
  int *idx = calloc(sizeof(int), n);
  copyArray(A, acc, 0, n);
  // heap's algorithm, iterative version
  int count = 1;
  for (int i=1; i < n;) {
    if (idx[i] < i) {
      int swap = i % 2 * idx[i];
      int tmp = A[swap];
      A[swap] = A[i];
      A[i] = tmp;
      copyArray(A, acc, count, n);
      count++;
      idx[i]++;
      i = 1;
    } else {
      idx[i++] = 0;
    }
  }
  free(idx);
}

tuple_t *subseq(tuple_t *full, int n)
{
    tuple_t *sub = malloc(sizeof(tuple_t)*n);
    for (int i = 0; i < n; i++)
    {
        sub[i] = full[i];
    }
    return sub;
}

int **allInc(graph_t G, int num)
{
    for (int i = 0; i < G->size; i++)
    {
        tuple_t cur = G->adj[i]->vert;
        if (cur->snum == num)
        {
            neighbors* nbors = graph_get_neighbors(G, cur);
        }
    }
}

int longestAlmostMonotoneLen(tuple_t *perm, int n)
{
    graph_t G = graph_new(n);
    istack_t *stacks = calloc(sizeof(istack_t), n+1);
    for (int i = 0; i < n; i++)
    {
        G->adj[i]->vert = perm[i];
    }
    for (int i = 0; i < n+1; i++) 
    {
        stacks[i] = istack_new();
    }
    for (int i = 0; i < n; i++)
    {
        tuple_t cur = perm[i];
        for (int j = 0; j < n; j++)
        {
            istack_t stack = stacks[j];
            if (empty(stack))
            {
                cur->snum = j;
                ipush(stack, cur);
                break;
            }
            else if (cur->value < peek(stack)->value)
            {
                cur->snum = j;
                ipush(stack, cur);
                break;
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        tuple_t 1st = perm[i]
        for (int j = i + 1; j < n; j++)
        {
            tuple_t 2nd = perm[j];
            if ((1st->value < 2nd->value && 1st->snum == 2nd->snum - 1) ||
                 2nd->value < 1st->value && 2nd->snum == 1st->snum - 1)
            {
                graph_addedge(G, 1st, 2nd);
            }
        }
    }
    tuple_t lastNum;
    int lastIndex = 0;
    for (int i = 0; i < n + 1; i++) 
    {
        if (empty(stacks[i])) 
        {

            lastIndex = i-1;
            lastNum =  peek(stacks[lastIndex]);
            break;
        }
    }
    int **all = allInc(G, lastNum->snum);
    int index = lastNum->index;
    int *increasing = calloc(sizeof(int), lastIndex + 1);
    increasing[lastIndex] = lastNum->value;
    for (int i = lastIndex - 1; i >= 0; i--)
    {
        istack_t stack = stacks[i];
        while (!empty(stack))
        {
            tuple_t top = ipop(stack);
            if (top->index < index)
            {               
                increasing[i] = top->value;
                index = top->index;
                break;
            }
        }
    }
    int length = lastIndex + 1;
    free(increasing);
    for (int i = 0; i < n + 1; i++)
    {
        stack_free(stacks1[i]);
    }
    free(stacks);
    return length;
}

int find_min(int *a, int n)
{
    int min = 10;
    int index = 0;
    for (int i = 0; i < n; i++)
    {
        if (a[i] < min) 
        {
            min = a[i];
            index = i;
        }
    }
    printf("Minimum Index: %d\n", index);
    return min;
}

int main()
{
    int min = 10;
    int minidx = 0;
    int ord = 5;
    int ordperm = 120;
    int erdkeres = 3;
    tuple_t **acc = calloc(sizeof(tuple_t*), ordperm);
    int *acclen = calloc(sizeof(int), ordperm);
    for (int i = 0; i < ordperm; i++)
    {
        acc[i] = calloc(sizeof(tuple_t), ord);
    }
    int *a = malloc(sizeof(int)*ord);
    for (int i = 0; i < ord; i++)
    {
        a[i] = i + 1;
    }
    heapIterative(a, ord, acc, ordperm);
    free(a);
    for (int i = 0; i < ordperm; i++)
    {
        tuple_t *curperm = acc[i];
        if (i == 1590173) printArr(curperm, ord);
        for (int j = erdkeres; j <= ord; j++)
        {
            int len = longestAlmostMonotoneLen(curperm, ord, j);
            if (acclen[i] < len) acclen[i] = len;
        }
        if (acclen[i] < min) 
        {
            min = acclen[i];
            minidx = i;
        }
        freetuplestar(curperm, ord);
    }
    printf("Minimum-Length Almost Monotone: %d\n", min);
    printf("Minimum Index: %d\n", minidx);
    free(acclen);
    free(acc);
    return 0;
}