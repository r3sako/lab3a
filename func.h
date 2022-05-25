#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *msgs[] ;
const int NMsgs ;
const char *errmsgs[] ;

typedef struct Item{
    int key;
    char *name;
}Item;

typedef struct Table{
    int n;
    Item *first;
}Table;

void del(Table *ptab);
int hash(char *info);
int find(Table ptab, int k);
int find_add(Table *ptab, int k);
int insert(Table *ptab, int k, char info[]);
int getInt(int *a);
int D_Del(Table *ptab);
int D_Add(Table *ptab);
int D_Find(Table *ptab);
int D_Show(Table *ptab);
int dialog(const char *msgs[], int N);


#endif // FUNC_H_INCLUDED

