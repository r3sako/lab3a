#include "func.h"

const char *msgs[] = {"0. Quit", "1. Add", "2. Find", "3. Delete", "4. Show"};
const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);
const char *errmsgs[] = {"Ok", "Duplicate key", "Table overflow"};

int find(Table ptab, int k){
    int i = 0, s = 0, j = ptab.n - 1;

    while (i<=j){
        s = (i+j)/2;
        if (ptab.first[s].key == k)
        return s;
        if (ptab.first[s].key < k)
        i = s + 1;
        if (ptab.first[s].key > k)
        j = s - 1;
    }
    return -1;
}

int find_add(Table *ptab, int k){
    int i = 0, s = 0, j = ptab->n - 1;

    while (i<=j){
        s = (i+j)/2;
        if (ptab->first[s].key == k)
        return -1;
        if (ptab->first[s].key < k)
        i = s + 1;
        if (ptab->first[s].key > k)
        j = s - 1;
    }
    return i;
}

int insert(Table *ptab, int k, char *info){
    int r = find_add(ptab, k);

    if(r == -1)
    return 1;

    if (ptab->n == 0 || (r == (ptab->n))){
	ptab->first[ptab->n].name = (char*) malloc(sizeof(char)*(strlen(info) + 1));
        ptab->first[r].key = k;
        *strcpy(ptab->first[r].name, info);
    }else{
        int i = r, j = ptab->n-1;
        for(j = ptab->n-1; j >= i; j--){
	    ptab->first[j+1].name = (char*) malloc(sizeof(char)*(strlen(ptab->first[j].name) + 1));
            ptab->first[j+1].key = ptab->first[j].key;
            *strcpy(ptab->first[j+1].name, ptab->first[j].name);
	    free(ptab->first[j].name);
        }
	ptab->first[r].name = (char*) malloc(sizeof(char)*(strlen(info) + 1));
        ptab->first[r].key = k;
        *strcpy(ptab->first[r].name, info);
    }
    ++(ptab->n);
    return 0;
}

int getInt(int *a){
    int e;

    do{
        e = scanf("%d", a);
        if (e < 0){
            return 0;
        }
        if (e == 0){
            printf("%s\n", "Error! Repeat input");
            scanf("%*c");
        }
    } while (e == 0);
    return 1;
}

int D_Show(Table *ptab){
    int i;
    int j = (ptab->n);

    for (i = 0; i < j; i++)
    printf("key: %d | name: %s\n", ptab->first[i].key, ptab->first[i].name);
    return 1;
}

int D_Find(Table *ptab){
    int k, c, res;

    printf("Enter key: \n");
    c = getInt(&k);
    if(c == 0)
    return 0;

    res = find(*ptab, k);
    if (res >= 0)
    printf("key = %d, name = %s\n", k, ptab->first[res].name);
    else
    printf("Item %d was not found\n", k);
    return 1;
}

int D_Del(Table *ptab){
    int k, c, res;

    printf("Enter key: \n");
    c = getInt(&k);
    if(c == 0)
    return 0;

    res = find(*ptab, k);
    if (res >= 0){
        int i, j = (ptab->n)-1 ;
        for(i = res; i < j; i++){
	    free(ptab->first[i].name);
	    ptab->first[i].name = (char*) malloc(sizeof(char)*(strlen(ptab->first[i+1].name) + 1));
            ptab->first[i].key = ptab->first[i+1].key;
            *strcpy(ptab->first[i].name, ptab->first[i+1].name);
        }
	free(ptab->first[i].name);
        printf("Item %d was successfully deleted\n", k);
        --(ptab->n);
    }else{
        printf("Item %d was not found\n", k);
    }
    return 1;
}

int hash(char *info){
    int s = 0, i = 0, res = 0, j = strlen(info);

    for(i = 0; i < j; i++){
    	s = s + info[i];
    }
    res = s % 60;
    return res;
}

int D_Add(Table *ptab){
    int k, rc;
    char *info;
    ptab->first = (Item*) realloc(ptab->first, (ptab->n + 1) * sizeof(Item));
    info = readline("Enter name: ");
    k = hash(info);
    rc = insert(ptab, k, info);

    free(info);
    printf("%s: %d\n", errmsgs[rc], k);
    return 1;
}

void del(Table *ptab){
    int i , j = ptab->n;

    for (i = 0; i < j; i++)
    free(ptab->first[i].name);
    free(ptab->first);
    free(ptab);
}

int dialog(const char *msgs[], int N){
    char *errmsg = "";
    int rc;
    int i, n;

    for(i = 0; i < N; ++i)
    puts(msgs[i]);

    do{
        puts(errmsg);
        errmsg = "You are wrong. Repeate, please!";
        puts("Make your choice: ");
        n = getInt(&rc);
        if(n == 0)
        rc = 0;
    } while(rc < 0 || rc >= N);

    return rc;
}

